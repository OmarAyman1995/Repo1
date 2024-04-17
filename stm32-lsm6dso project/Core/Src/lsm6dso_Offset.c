/*
 ******************************************************************************
 * @file    _offset.c
 * @author  Sensors Software Solution Team
 * @brief   This file show the simplest way to get data from sensor.
 *
*/



/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "lsm6dso_reg.h"


#include "stm32f1xx_hal.h"



/* Private macro -------------------------------------------------------------*/
#define    BOOT_TIME      10
#define SENSOR_BUS     hi2c1
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static int16_t data_raw_acceleration[3];
static int16_t data_raw_angular_rate[3];
static int16_t data_raw_temperature;
static float acceleration_mg[3];
static float angular_rate_mdps[3];
static float temperature_degC;
static uint8_t whoamI, rst;
static uint8_t tx_buffer[1000];

/* Extern variables ----------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

/* Private functions ---------------------------------------------------------*/

/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
extern int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
extern int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
extern void tx_com( uint8_t *tx_buffer, uint16_t len );
extern void platform_delay(uint32_t ms);
extern void platform_init(void);

/* Main Example --------------------------------------------------------------*/
void lsm6dso_offset(void)
{
  stmdev_ctx_t dev_ctx;
  /* Example of XL offset to apply to acc. output */
  uint8_t offset[3] = { 0x30, 0x40, 0x7E };
  /* Initialize mems driver interface */
  dev_ctx.write_reg = (stmdev_write_ptr)platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.mdelay = platform_delay;
  dev_ctx.handle = &SENSOR_BUS;
  /* Init test platform */
  platform_init();
  /* Wait sensor boot time */
  platform_delay(10);
  /* Check device ID */
  lsm6dso_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LSM6DSO_ID)
    while (1);

  /* Restore default configuration */
  lsm6dso_reset_set(&dev_ctx, PROPERTY_ENABLE);

  do {
    lsm6dso_reset_get(&dev_ctx, &rst);
  } while (rst);

  /* Disable I3C interface */
  lsm6dso_i3c_disable_set(&dev_ctx, LSM6DSO_I3C_DISABLE);
  /* Enable Block Data Update */
  lsm6dso_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
  /* Weight of XL user offset to 2^(-10) g/LSB */
  lsm6dso_xl_offset_weight_set(&dev_ctx, LSM6DSO_LSb_1mg);
  /* Accelerometer X,Y,Z axis user offset correction expressed
   * in two’s complement. Set X to 48mg, Y tp 64 mg, Z to -127 mg
   */
  lsm6dso_xl_usr_offset_x_set(&dev_ctx, &offset[0]);
  lsm6dso_xl_usr_offset_y_set(&dev_ctx, &offset[1]);
  lsm6dso_xl_usr_offset_z_set(&dev_ctx, &offset[2]);
  lsm6dso_xl_usr_offset_set(&dev_ctx, PROPERTY_ENABLE);
  /* Set Output Data Rate */
  lsm6dso_xl_data_rate_set(&dev_ctx, LSM6DSO_XL_ODR_12Hz5);
  lsm6dso_gy_data_rate_set(&dev_ctx, LSM6DSO_GY_ODR_12Hz5);
  /* Set full scale */
  lsm6dso_xl_full_scale_set(&dev_ctx, LSM6DSO_2g);
  lsm6dso_gy_full_scale_set(&dev_ctx, LSM6DSO_2000dps);
  /* Configure filtering chain(No aux interface). */
  /* Accelerometer - LPF1 + LPF2 path */
  lsm6dso_xl_hp_path_on_out_set(&dev_ctx, LSM6DSO_LP_ODR_DIV_100);
  lsm6dso_xl_filter_lp2_set(&dev_ctx, PROPERTY_ENABLE);

  /* Read samples in polling mode (no int). */
  while (1) {
    uint8_t reg;
    /* Read output only if new xl value is available */
    lsm6dso_xl_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
      /* Read acceleration field data */
      memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
      lsm6dso_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
      acceleration_mg[0] =
        lsm6dso_from_fs2_to_mg(data_raw_acceleration[0]);
      acceleration_mg[1] =
        lsm6dso_from_fs2_to_mg(data_raw_acceleration[1]);
      acceleration_mg[2] =
        lsm6dso_from_fs2_to_mg(data_raw_acceleration[2]);
      sprintf((char *)tx_buffer,
              "Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
              acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
      tx_com(tx_buffer, strlen((char const *)tx_buffer));
      platform_delay(500);
    }

    lsm6dso_gy_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
      /* Read angular rate field data */
      memset(data_raw_angular_rate, 0x00, 3 * sizeof(int16_t));
      lsm6dso_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate);
      angular_rate_mdps[0] =
        lsm6dso_from_fs2000_to_mdps(data_raw_angular_rate[0]);
      angular_rate_mdps[1] =
        lsm6dso_from_fs2000_to_mdps(data_raw_angular_rate[1]);
      angular_rate_mdps[2] =
        lsm6dso_from_fs2000_to_mdps(data_raw_angular_rate[2]);
      sprintf((char *)tx_buffer,
              "Angular rate [mdps]:%4.2f\t%4.2f\t%4.2f\r\n",
              angular_rate_mdps[0], angular_rate_mdps[1], angular_rate_mdps[2]);
      tx_com(tx_buffer, strlen((char const *)tx_buffer));
      platform_delay(500);
    }

    lsm6dso_temp_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
      /* Read temperature data. */
      memset(&data_raw_temperature, 0x00, sizeof(int16_t));
      lsm6dso_temperature_raw_get(&dev_ctx, &data_raw_temperature);
      temperature_degC = lsm6dso_from_lsb_to_celsius(
                           data_raw_temperature);
      sprintf((char *)tx_buffer,
              "Temperature [degC]:%6.2f\r\n", temperature_degC);
      tx_com(tx_buffer, strlen((char const *)tx_buffer));
      platform_delay(500);
    }
    tx_com((uint8_t *)"\r\n\r\n\r\n", strlen("\r\n\r\n\r\n"));
  }
}

