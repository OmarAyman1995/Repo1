#include "MQTT_Mcal_Interface.h"
#include "GPIO.h"
#include "UART.h"
#include "FreeRTOS.h"
#include "task.h"

extern UART_HandleTypeDef huart1;

#define UART_SIM800             &huart1
#define SIM800_RST_GPIO         GPIOA
#define SIM800_RST_PIN          GPIO_PIN_8


void vid_Mqtt_Delay(u32_t delay){
#if FREERTOS == 1
        vTaskDelay(delay);
#else
        HAL_Delay(delay);
#endif
}


u8_t u8_Mqtt_UartTransmit(u8_t *LOC_ptr_pData, u16_t LOC_u16_size, u32_t LOC_u32_timeout){
    u8_t LOC_enum_retval = 0;
    enumRetUart_e LOC_enum_checkUart = 0;

    if((LOC_ptr_pData != NULLPTR) && (LOC_ptr_pData != 0)){

        LOC_enum_checkUart = enum_Uart1SendData(LOC_ptr_pData, LOC_u16_size);
        if(LOC_enum_checkUart == VALID_UART){
            LOC_enum_retval = 1;
        }else{
            LOC_enum_retval = 0;
        }
    }else{
        LOC_enum_retval = 0;
    }

    return LOC_enum_retval;
}

u8_t u8_Mqtt_UartReceiveIT(u8_t *LOC_ptr_pData, u16_t LOC_u16_size){
    u8_t LOC_enum_retval = 0;
    enumRetUart_e LOC_enum_checkUart = 0;

    if((LOC_ptr_pData != NULLPTR) && (LOC_ptr_pData != 0)){

        LOC_enum_checkUart = enum_Uart1RecITData(LOC_ptr_pData, LOC_u16_size);

        if(LOC_enum_checkUart == VALID_UART){
            LOC_enum_retval = 1;
        }else{
            LOC_enum_retval = 0;
        }
    }else{
        LOC_enum_retval = 0;
    }

    return LOC_enum_retval;
}

void vid_Mqtt_GpioWrite_ResetPin(u8_t LOC_u8_level){
    if(LOC_u8_level == RESET_HIGH){
        enum_GpioWritePin(SIM800_RST_GPIO, SIM800_RST_PIN, GPIO_PIN_SET);
    }else{
        enum_GpioWritePin(SIM800_RST_GPIO, SIM800_RST_PIN, GPIO_PIN_RESET);
    }
}


void vid_Mqtt_SetUartCallback(MqttCallback callback){
    enum_UartSetCallbackForReception(&huart1, vid_Mqtt_Uart_Interrupt); // bluetooth register callback

}
