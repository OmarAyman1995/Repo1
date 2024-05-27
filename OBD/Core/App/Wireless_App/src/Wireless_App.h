#ifndef __WIRELESS_APP_H
#define __WIRELESS_APP_H


#include "typedefs.h"



#define MOTOR_OFF 0
#define MOTOR_ON  1

#define BLUEOOTH_VARIANT    0
#define MQTT_VARIANT        1
#define BLUETOOTH_AND_MQTT_VARIANT  2

#define ENABLE_SETUP_MODE 0
/**
 * @brief wireless app request datatype
 * 
 */
typedef struct 
{
    u8_t *pData;
    u32_t size;
    ResponseCallback callback;
}Wireless_RequestTypedef;

/**
 * @brief services that user can request from wireless communication
 * 
 */
typedef enum 
{
    MANUAL_REQUEST_SERVICE = 0xA1,
    DYNAMIC_DATA_REQUEST_SERVICE,
    STATIC_DATA_REQUEST_SERVICE,
    UDS_REQUEST_SERVICE,
    DEVICE_INFO_SERVICE,
}Services_Typedef;

/**
 * @brief state of the request
 * 
 */
typedef enum{

WIRELESS_APP_BUSY,

WIRELESS_APP_OK,

WIRELESS_APP_ERROR

}WirelessApp_StatusTypeDef;

/**
 * @brief updates the variant (bluetooth or mqtt)
 * 
 * @param value either 0 for bluetooth or 1 for mqtt
 */
void vid_setVariant(u8_t value);

/**
 * @brief initialize function of wireless app
 * 
 */
void vid_WirelessApp_Init(void);

/**
 * @brief periodic function of wireless app
 * 
 */
void vid_WirelessApp_Manage(void);

/**
 * @brief sends data over wireless
 * 
 * @param request request object
 * @return WirelessApp_StatusTypeDef returns OK if the request successes
 */
WirelessApp_StatusTypeDef enum_WirelessApp_Request(Wireless_RequestTypedef *request);

/**
 * @brief if no requests for more than 15mins it returns 1 otherwise returns 0
 * 
 * @return u8_t 
 */
u8_t u8_isWirelessCommActive(void);

#endif

