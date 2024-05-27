#include "Vehicle_App.h"
#include "ProcessingRequest.h"
#include "QueueInterface.h"
#include "OBDIIHandler.h"
#include "string.h"

#define FUEL_SYSTEM_STATUS_PID 0x03
#define VIN_NUMBER_PID 0x02
#define ESCAPE_ASII 48


u8_t GLOB_arrVinNumber[20] = {0};
u8_t GLOB_u8fuelSystemStatus = 0;
u32_t GLOB_u32scheduling_counter = 0;
u8_t GLOB_u8switchToNormalMode = 0;
u8_t GLOB_u8request_lock = 0;
u8_t GLOB_u8check_vinNumber_request = 0;
u8_t GLOB_u8check_pidsUpdate_request = 0;
/**
 * @brief handling all events that depends on scheduling ticks
 * 
 */
static void vid_schedulingEvents(void);

/**
 * @brief the response callback of requesting System Fuel from vehicle app
 * 
 * @param return_message response 
 * @param message_size response size
 * @param notification notification number
 */
static void vid_SystemFuelRequestCallback(u8_t *return_message, u32_t message_size, u8_t notification);


/**
 * @brief prestored request of the fuel system status
 * 
 */
Vehicle_RequestTypedef LOC_str_fuelSystemRequest = {
    .service = MANUAL_REQUEST,
    .obd_mode = OBD_MODE_1,
    .obd_pid = FUEL_SYSTEM_STATUS_PID,
    .callback = vid_SystemFuelRequestCallback,

    .uds_can_id = 0,
    .uds_sid = 0,
    .uds_did1 = 0,
    .uds_did2 = 0
};

/**
 * @brief setup mode actions
 * 
 */
static void vid_setupMode(void);

/**
 * @brief normal mode actions
 * 
 */
static void vid_normalMode(void);


void vid_VehicleApp_Init(void){
    // initialize all global variables
    GLOB_u8switchToNormalMode = 0;
}


static void vid_setupMode(void){
#if VEHICLE_ENABLE_SETUP_MODE == 1
    Vehicle_RequestTypedef LOC_str_vinRequest = {0};
    Vehicle_RequestTypedef LOC_str_updateDatabaseRequest = {0};
    u8_t *Loc_ptr_vinNumber = NULLPTR;
    u32_t LOC_u32_vinNumberSize = 0;
    static u8_t isProtocolDetected = 0;


    // decide which OBD protocol the vehicle responds to.
    if(isProtocolDetected == 0){
        isProtocolDetected = OBDII_DetectVehicleProtocol();
    }
    if(isProtocolDetected == 1){

        // request VIN and store it.
        if(GLOB_u8check_vinNumber_request == 0){
            LOC_str_vinRequest.service  = MANUAL_REQUEST;
            LOC_str_vinRequest.obd_mode = OBD_MODE_9;
            LOC_str_vinRequest.obd_pid  = VIN_NUMBER_PID;
            GLOB_u8check_vinNumber_request = u8_Process_Request(MANUAL_REQUEST, &LOC_str_vinRequest);
            if(GLOB_u8check_vinNumber_request == 0){
                // vehicle not responding.
            }else{

                // store the vin number globally.
                Loc_ptr_vinNumber = p_getResponseMessage();
                LOC_u32_vinNumberSize = u32_getResponseSize();
                memcpy(GLOB_arrVinNumber, Loc_ptr_vinNumber, LOC_u32_vinNumberSize);
                vid_Processing_Reset();
            }
        }

        // request updating pids database.
        if(GLOB_u8check_pidsUpdate_request == 0){
            GLOB_u8check_pidsUpdate_request = u8_Process_Request(UPDATE_SUPPORT_TYPE_REQUEST, &LOC_str_updateDatabaseRequest);
            if(GLOB_u8check_pidsUpdate_request == 0){
                // vehicle didn't respond to all PIDs Supported requests.
            }
        }
    }

    // if everything successed in setup mode, switch to normal forever.
    if((GLOB_u8check_pidsUpdate_request & GLOB_u8check_vinNumber_request) == 1){
        GLOB_u8switchToNormalMode = 1;
    }else{
        GLOB_u8switchToNormalMode = 0;
    }
#else
    GLOB_u8switchToNormalMode = 1;
#endif
}


static void vid_normalMode(void){
    u8_t LOC_u8_queueReturn = 0;
    Vehicle_RequestTypedef LOC_str_storedRequest = {0};
    ResponseCallback LOC_ptr_userCallback = NULLPTR;
    u8_t *LOC_ptr_responseMessage = NULLPTR;
    u32_t LOC_u32_responseSize = 0;
    u8_t LOC_u8_returnOfProcessing = 0;
    u8_t LOC_u8_desiredService = 0;

    vid_schedulingEvents();

    // check requests queue
    LOC_u8_queueReturn = u8_QueueIF_Pop(VEHICLE_HANDLER, &LOC_str_storedRequest);
    if(LOC_u8_queueReturn == 1){

        // LOC_str_storedRequest.pData array information are [ (service id), (mode or sid) , (pid or did1) , (did2) ]
        LOC_ptr_userCallback   = LOC_str_storedRequest.callback;
        LOC_u8_desiredService = LOC_str_storedRequest.service;

        LOC_u8_returnOfProcessing = u8_Process_Request(LOC_u8_desiredService, &LOC_str_storedRequest);
        LOC_ptr_responseMessage  = p_getResponseMessage();
        LOC_u32_responseSize = u32_getResponseSize();

        LOC_ptr_userCallback(LOC_ptr_responseMessage, LOC_u32_responseSize , LOC_u8_returnOfProcessing);
        vid_Processing_Reset();

    }else{
        // no requests, do nothing
    }

}


void vid_VehicleApp_Manage(void){
    if(GLOB_u8switchToNormalMode == 0){
        vid_setupMode();
    }else{
        vid_normalMode();
    }
}


VehicleApp_StatusTypeDef enum_VehicleApp_Request(Vehicle_RequestTypedef *request){
    u8_t LOC_u8_queueReturn = 0;
    VehicleApp_StatusTypeDef LOC_str_returnVal = 0;

    if(GLOB_u8request_lock == 1){
        return VEHICLE_APP_BUSY;
    }

    GLOB_u8request_lock = 1; // lock the API

    // check arguments
    if(request != NULLPTR){
        if(request->callback != NULLPTR){
            // push the request in the queue.
            LOC_u8_queueReturn = u8_QueueIF_Push(VEHICLE_HANDLER, request);
        }

        if(LOC_u8_queueReturn == 1){
            LOC_str_returnVal = VEHICLE_APP_OK;
        }else{
            LOC_str_returnVal = VEHICLE_APP_ERROR;
        }
    }else{
        LOC_str_returnVal =  VEHICLE_APP_ERROR;
    }

    GLOB_u8request_lock = 0; // unlock the API

    return LOC_str_returnVal;
}


static void vid_SystemFuelRequestCallback(u8_t *return_message, u32_t message_size, u8_t notification){

    if(notification == 1){
        // success
        GLOB_u8fuelSystemStatus = return_message[0] - ESCAPE_ASII;
    }else{
        // fail
        GLOB_u8fuelSystemStatus = 0;
    }
}


u8_t u8_VehicleApp_getMotorState(void){
    return GLOB_u8fuelSystemStatus;
}



static void vid_schedulingEvents(void){
#if VEHICLE_ENABLE_SCHEDULING_EVENTS == 1
    // schedule 150ms to request FUEL_SYSTEM_STATUS
    if(GLOB_u32scheduling_counter >= FUEL_SYSTEM_STATUS_TIME){

        // put that request in vehicle queue
        if(u8_QueueIF_Push(VEHICLE_HANDLER, &LOC_str_fuelSystemRequest) == 1){
            GLOB_u32scheduling_counter = 0;
        }else{
            // keep entering this if untill push success.
        }
    }
    ++GLOB_u32scheduling_counter;
#else
    /*DO NOTHING*/
#endif
}
