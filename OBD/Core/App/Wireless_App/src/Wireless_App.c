#include "Wireless_App.h"
#include "HandlingBluetooth.h"
#include "HandlingMqtt.h"
#include "Vehicle_App.h"
#include "MQTTSim800.h"
#include "QueueInterface.h"
#include "MemManager.h"
#include "string.h"




/**
 * @brief global counter to catch if no FF char received on bluetooth
 * 
 */
u32_t GLOB_u32_No_FF_Counter = 0;

/**
 * @brief global counter to catch if no new requests received on bluetooth
 * 
 */
u32_t GLOB_u32_NoRequests_Counter = 0;

/**
 * @brief event flag, if 1 means no requests received for more than 15mins
 * 
 */
u8_t  GLOB_u8_NoRequests_Event = 0;

/**
 * @brief event flag, if 1 means string READY has been sent (must be sent only once)
 * 
 */
u8_t  GLOB_u8READY_isSent_forBluetooth = 0;

/**
 * @brief event flag, if 1 means string READY has been sent (must be sent only once)
 * 
 */
u8_t  GLOB_u8READY_isSent_forMqtt = 0;

/**
 * @brief event flag, if 1 means that a byte has been received
 * 
 */
u8_t  GLOB_u8byteReceived = 0;

/**
 * @brief event flag, if 1 means that FF char has been received
 * 
 */
u8_t  GLOB_u8ffReceived = 0;




PRIVATE u8_t GLOB_u8switchToNormalMode = 0;
PRIVATE u8_t GLOB_u8variant = 0;
PRIVATE u8_t GLOB_u8request_lock = 0;
PRIVATE u8_t GLOB_arrStaticData[250] = {0};
PRIVATE u8_t GLOB_u8_StaticDataResponseReceived = 0;


PRIVATE void vid_setupMode(void);
PRIVATE void vid_normalMode(void);
PRIVATE void vid_VehicleResponseCallbackFunction(u8_t* response_message, u32_t message_size, u8_t notification_type);
PRIVATE void vid_VehicleResponseToStaticData(u8_t* response_message, u32_t message_size, u8_t notification_type);
PRIVATE void vid_WirelessSend(u8_t *pData, u32_t Size);
PRIVATE void vid_schedulingEvents(void);
PRIVATE void routeRequestToVehicleApp(Vehicle_RequestTypedef* request, u8_t* data);
PRIVATE void processIncomingRequests(void);
PRIVATE void processOutgoingRequests(void);
PRIVATE void handleIncomingRequest(u8_t* data);
PRIVATE void handleValidServiceRequest(Vehicle_RequestTypedef* request, u8_t* data);
PRIVATE void routeRequestToVehicleApp(Vehicle_RequestTypedef* request, u8_t* data);
PRIVATE u8_t u8_isServiceWithinRange(u8_t service);


void vid_WirelessApp_Init(void){

    vid_Bluetooth_setCallback(vid_HandlingBluetooth_Callback);
    vid_HandlingBluetooth_Listen();

    vid_Mqtt_SetCallback(vid_HandlingMqtt_Callback);
    u8_Mqtt_Subscribe(SUBSCRIBE_TOPIC);
}

void vid_WirelessApp_Manage(void){

    if(GLOB_u8switchToNormalMode == 0){
        vid_setupMode();
    }else{
        vid_normalMode();
    }

}

/**
 * @brief normal mode flow chart actions
 * 
 */
PRIVATE void vid_normalMode(void){

    vid_schedulingEvents();

    processIncomingRequests();

    processOutgoingRequests();

}

/**
 * @brief setup mode flow chart actions
 * 
 */
PRIVATE void vid_setupMode(void){

#if ENABLE_SETUP_MODE == 1
    PRIVATE u8_t LOC_u8_checkBluetooth = 1;
    PRIVATE enumRetMemMang_e LOC_enum_deviceInfoCheck = NOT_VALID_MEM_MANG;
    PRIVATE VehicleApp_StatusTypeDef LOC_enum_staticDataCheck = VEHICLE_APP_ERROR;
    u8_t LOC_u8_arrdeviceInfoBuffer[128] = {0};
    Vehicle_RequestTypedef  LOC_strstaticDataRequest = {0};

    // bluetooth configurations
    if(LOC_u8_checkBluetooth == 0){
        LOC_u8_checkBluetooth = u8_HandlingBluetooth_updateConfigurations();
    }

    // read device info
    if(LOC_enum_deviceInfoCheck == NOT_VALID_MEM_MANG){
        LOC_enum_deviceInfoCheck = enum_MemMngReadDevInfo(LOC_u8_arrdeviceInfoBuffer);
    }

    // request static data from Vehicle App.
    if((LOC_enum_staticDataCheck == VEHICLE_APP_ERROR) || (GLOB_u8_StaticDataResponseReceived == 0)){
        LOC_strstaticDataRequest.service = STATIC_DATA_REQUEST_SERVICE;
        LOC_strstaticDataRequest.callback = vid_VehicleResponseToStaticData;
        LOC_enum_staticDataCheck = enum_VehicleApp_Request(&LOC_strstaticDataRequest);
    }

    // if request static and store in memory successed, switch to normal mode.
    if((LOC_u8_checkBluetooth == 1) && (LOC_enum_deviceInfoCheck == VALID_MEM_MANG) && (LOC_enum_staticDataCheck == VEHICLE_APP_OK) && (GLOB_u8_StaticDataResponseReceived == 1)){
        GLOB_u8switchToNormalMode = 1;
    }else{
        // stay in this mode
    }
#else
    GLOB_u8switchToNormalMode = 1;
#endif

}

/**
 * @brief chooses which wireless variant to send data over it
 * 
 * @param pData data that will be sent over bluetooth
 * @param Size size of the data
 * @note CCO-CDD-326 CCO-CDD-327 CCO-CDD-323 CCO-CDD-331 CCO-CDD-312
 */
PRIVATE void vid_WirelessSend(u8_t *pData, u32_t Size){

    switch (GLOB_u8variant)
    {
    case BLUEOOTH_VARIANT:
        u8_HandlingBluetooth_Send(pData, Size);
        break;
    case MQTT_VARIANT:
        u8_HandlingMqtt_Send(pData, Size);
        break;
    case BLUETOOTH_AND_MQTT_VARIANT:
        u8_HandlingBluetooth_Send(pData, Size);
        u8_HandlingMqtt_Send(pData, Size);
        break;

    default:
        // error in variant, do nothing
    }
} 




PRIVATE void processIncomingRequests(void) {
    u8_t LOC_arr_incomingRequest[10] = {0};
    u8_t LOC_u8_queueReturn = u8_QueueIF_Pop(WIRELESS_RECV_HANDLER, LOC_arr_incomingRequest);

    if (LOC_u8_queueReturn == 1) {
        GLOB_u32_NoRequests_Counter = 0; // reset no requests counter
        handleIncomingRequest(LOC_arr_incomingRequest);
    }
}

PRIVATE void handleIncomingRequest(u8_t* data) {
    Vehicle_RequestTypedef LOC_str_newRequest = {0};

    LOC_str_newRequest.service = data[0];

    if (u8_isServiceWithinRange(LOC_str_newRequest.service) == 1) {
        handleValidServiceRequest(&LOC_str_newRequest, data);
    } else {
        vid_WirelessSend("SNS", 4); // Service Not Supported
    }
}


PRIVATE void handleValidServiceRequest(Vehicle_RequestTypedef* request, u8_t* data) {
    u8_t LOC_u8_motorState = u8_VehicleApp_getMotorState();

    if ((LOC_u8_motorState == MOTOR_OFF) && (request->service == DYNAMIC_DATA_REQUEST_SERVICE)) {
        vid_WirelessSend("E-OFF", 6);
    } else {
        routeRequestToVehicleApp(request, data);
    }
}


PRIVATE void routeRequestToVehicleApp(Vehicle_RequestTypedef* request, u8_t* data) {
    request->callback = vid_VehicleResponseCallbackFunction;

    if (request->service == UDS_REQUEST) {
        request->uds_can_id = data[1];
        request->uds_sid    = data[2];
        request->uds_did1   = data[3];
        request->uds_did2   = data[4];
    } else {
        request->obd_mode   = data[1];
        request->obd_pid    = data[2];
    }

    enum_VehicleApp_Request(request);
}


PRIVATE void processOutgoingRequests(void) {
    Wireless_RequestTypedef LOC_str_newRequest = {0};
    u8_t LOC_u8_queueReturn = u8_QueueIF_Pop(WIRELESS_SEND_HANDLER, &LOC_str_newRequest);

    if (LOC_u8_queueReturn == 1) {

        vid_WirelessSend(LOC_str_newRequest.pData, LOC_str_newRequest.size);
        if (LOC_str_newRequest.callback != NULLPTR) {
            LOC_str_newRequest.callback(LOC_str_newRequest.pData, LOC_str_newRequest.size, 1);
        }
    }
}

void vid_setVariant(u8_t value){
    GLOB_u8variant = value;
}


WirelessApp_StatusTypeDef enum_WirelessApp_Request(Wireless_RequestTypedef *request){
    u8_t LOC_u8_queueReturn = 0;
    WirelessApp_StatusTypeDef LOC_enum_returnVal = 0;

    if(GLOB_u8request_lock == 1){
        return WIRELESS_APP_BUSY;
    }

    GLOB_u8request_lock = 1; // lock the API

    if(request == NULLPTR){
        LOC_enum_returnVal = WIRELESS_APP_ERROR;
    }else{

        // save in the queue.
        LOC_u8_queueReturn = u8_QueueIF_Push(WIRELESS_SEND_HANDLER, request);
        
        if(LOC_u8_queueReturn == 1){
            LOC_enum_returnVal = WIRELESS_APP_OK;
        }else{
            LOC_enum_returnVal = WIRELESS_APP_ERROR;
        }
    }

    GLOB_u8request_lock = 0; // unlock the API
    return LOC_enum_returnVal;
}



/**
 * @brief response call back function, given to other applicaitons
 * 
 * @param response_message 
 * @param message_size 
 * @param notification_type 
 * @note CCO-CDD-323 CCO-CDD-331
 */
PRIVATE void vid_VehicleResponseCallbackFunction(u8_t* response_message, u32_t message_size, u8_t notification_type){
    // according to the notification type, do the action

    if(response_message != NULLPTR){

        if(notification_type == 1){
            // 1 success
            vid_WirelessSend(response_message, message_size);
        }else if(notification_type == 2){
            // 2 wrong request parameters ex: invalid range of OBD mode or pid
            vid_WirelessSend("Invalid Request", 16);
        }
        else{
            // 0 error
            vid_WirelessSend("Error", 6);
        }
    }
}


/**
 * @brief checks on the received service correctness
 * 
 * @param service 
 * @return uint8_t 1 if correct, 0 if not correct
 */
PRIVATE u8_t u8_isServiceWithinRange(u8_t service){

    u8_t isServiceWithinRange = (service >= MANUAL_REQUEST_SERVICE) && (service <= DEVICE_INFO_SERVICE);

    return isServiceWithinRange;

}


/**
 * @brief scheduling and catching events
 * @note CCO-CDD-324 CCO-CDD-325 CCO-CDD-326 CCO-CDD-327 CCO-CDD-328 CCO-CDD-329
 */
PRIVATE void vid_schedulingEvents(void){
    u8_t bluetooth_checkConnect = 0;
    u8_t mqtt_checkConnect = 0;
    
    bluetooth_checkConnect = 1; // TODO bluetooth_checkConnect = u8_Bluetooth_getConnectivityStatus();
    mqtt_checkConnect = u8_Mqtt_isConnnected();

    // once bluetooth connected, send "READY" one time
    if((bluetooth_checkConnect == 1) && (GLOB_u8READY_isSent_forBluetooth == 0)){
        u8_HandlingBluetooth_Send("READY", 6);
        GLOB_u8READY_isSent_forBluetooth = 1;
    }
    if(bluetooth_checkConnect == 0){
        GLOB_u8READY_isSent_forBluetooth = 0;
    }

    // once Mqtt connected and subscribed to the queued topics, send "READY" one time
    if((mqtt_checkConnect == 1) && (GLOB_u8READY_isSent_forMqtt == 0)){
        GLOB_u8READY_isSent_forMqtt = u8_MQTT_Publish(PUBLISH_TOPIC, "READY", 6);
    }
    if(mqtt_checkConnect == 0){
        GLOB_u8READY_isSent_forMqtt = 0;
    }

    // no requests for more than 15ms, catch this event
    if(GLOB_u32_NoRequests_Counter >= 3){
        GLOB_u8_NoRequests_Event = 1;
    }else{
        GLOB_u8_NoRequests_Event = 0;
    }
    ++GLOB_u32_NoRequests_Counter;


    // no FF for more 500ms, send "Request Incomplete"
    if(GLOB_u8byteReceived == 1){
        ++GLOB_u32_No_FF_Counter;
    }
    if(GLOB_u8ffReceived == 1){
        GLOB_u32_No_FF_Counter = 0;
        GLOB_u8byteReceived = 0;
        GLOB_u8ffReceived = 0;
    }
    if(GLOB_u32_No_FF_Counter >= 16){
        GLOB_u32_No_FF_Counter = 0;
        GLOB_u8byteReceived = 0;
        GLOB_u8ffReceived = 0;
        vid_WirelessSend("Request Incomplete", 19);
        vid_HandlingBluetooth_resetAfterRequest(); // reset bluetooth buffer
        vid_Bluetooth_AbortReceive();  // cancel any receive operation
        vid_HandlingBluetooth_Listen();            // let the bluetooth listen to new message
    }
}


u8_t u8_isWirelessCommActive(void){
    return GLOB_u8_NoRequests_Event;
}

PRIVATE void vid_VehicleResponseToStaticData(u8_t* response_message, u32_t message_size, u8_t notification_type){
    // store the static data (done in response callback) in Memory using Memory Manager component.
    if(notification_type == 1){
        memcpy(GLOB_arrStaticData, response_message, message_size);
        GLOB_u8_StaticDataResponseReceived = 1;
    }else{
        GLOB_u8_StaticDataResponseReceived = 0;
    }
}
