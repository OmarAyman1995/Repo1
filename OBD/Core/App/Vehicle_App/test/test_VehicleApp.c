#include "unity.h"
#include "string.h"


#include "mock_ComM.h"
#include "mock_ProcessingRequest.h"
#include "mock_QueueInterface.h"
#include "mock_OfferedServices.h"
#include "mock_services.h"
#include "mock_OBDIIHandler.h"
#include "Vehicle_App.h"


extern u8_t GLOB_arrVinNumber[20];
extern u8_t GLOB_u8fuelSystemStatus;
extern u32_t GLOB_u32scheduling_counter;
extern u8_t GLOB_u8switchToNormalMode;
extern u8_t GLOB_u8request_lock ;
extern u8_t GLOB_u8check_vinNumber_request;
extern u8_t GLOB_u8check_pidsUpdate_request;
extern Vehicle_RequestTypedef LOC_str_fuelSystemRequest;



void setUp(void){
    OBDII_DetectVehicleProtocol_IgnoreAndReturn(1);
    vid_Processing_Reset_Ignore();
}
// test request with null parameter
void test_case_0001(void){
    // setup
    VehicleApp_StatusTypeDef returnCheck = 0;
    Vehicle_RequestTypedef request = {0};

    // act
    returnCheck = enum_VehicleApp_Request(NULL);

    // assert
    TEST_ASSERT_EQUAL_INT(VEHICLE_APP_ERROR, returnCheck);
    
    // cleanup

}


// test request speed
void test_case_0002(void){
    // setup
    cpy_array_Ignore();
    u8_QueueIF_Push_IgnoreAndReturn(1);
    VehicleApp_StatusTypeDef returnCheck = 0;
    Vehicle_RequestTypedef request = {.service=MANUAL_REQUEST, .obd_mode=OBD_MODE_1, .obd_pid=0x0d};

    void ResponseCallback(u8_t* pdata,u32_t sizeofdata, u8_t notification){
    }
    request.callback = ResponseCallback;
    // act
    returnCheck = enum_VehicleApp_Request(&request);

    // assert
    TEST_ASSERT_EQUAL_INT(VEHICLE_APP_OK, returnCheck);
    
    // cleanup

}


// test request but queue is fill
void test_case_0003(void){
    // setup
    cpy_array_Ignore();
    u8_QueueIF_Push_IgnoreAndReturn(0); // queue is full, push fails
    VehicleApp_StatusTypeDef returnCheck = 0;
    Vehicle_RequestTypedef request = {.service  = MANUAL_REQUEST,
                                      .obd_mode = OBD_MODE_1,
                                      .obd_pid  = 0x0d};

    void ResponseCallback(u8_t* pdata,u32_t sizeofdata, u8_t notification){
    }
    request.callback = ResponseCallback;

    // act
    returnCheck = enum_VehicleApp_Request(&request);

    // assert
    TEST_ASSERT_EQUAL_INT(VEHICLE_APP_ERROR, returnCheck);
    
    // cleanup

}


// test request but enum_VehicleApp_Request is busy (another context have it)
void test_case_0077(void){
    // setup
    cpy_array_Ignore();
    u8_QueueIF_Push_IgnoreAndReturn(1);
    VehicleApp_StatusTypeDef returnCheck = 0;
    Vehicle_RequestTypedef request = {.service  = MANUAL_REQUEST,
                                      .obd_mode = OBD_MODE_1,
                                      .obd_pid  = 0x0d};

    void ResponseCallback(u8_t* pData, u32_t sizeofdata, u8_t notification){
    }
    request.callback = ResponseCallback;
    GLOB_u8request_lock = 1; // Request API is busy
    // act
    returnCheck = enum_VehicleApp_Request(&request);

    // assert
    TEST_ASSERT_EQUAL_INT(VEHICLE_APP_BUSY, returnCheck);
    
    // cleanup

}

// test get motor state
void test_case_0004(void){
    // setup
    u8_t returnCheck = 0;

    // act
    returnCheck = u8_VehicleApp_getMotorState();

    // assert
    TEST_ASSERT_EQUAL_INT(0, returnCheck);
    
    // cleanup

}


// test init valid scenario
void test_case_0005(void){
    // setup

    // act
    vid_VehicleApp_Init();

    // assert
    
    // cleanup

}


// test requesting vin number and update pids database at setup mode
void test_case_0007(void){
    // setup
    GLOB_u8switchToNormalMode = 0;
    u8_t *vinNumber = "VSS12345678911111";
    u8_Process_Request_IgnoreAndReturn(1);
    p_getResponseMessage_IgnoreAndReturn(vinNumber);
    u32_getResponseSize_IgnoreAndReturn(17);

    // act
    vid_VehicleApp_Manage();

    // assert
    TEST_ASSERT_EQUAL_STRING(GLOB_arrVinNumber,vinNumber);
    TEST_ASSERT_EQUAL_CHAR(1, GLOB_u8switchToNormalMode);
    
    // cleanup
    GLOB_u8switchToNormalMode = 0;
    memset(GLOB_arrVinNumber, 0 , 20);
    GLOB_u8check_pidsUpdate_request = 0;
    GLOB_u8check_vinNumber_request = 0;
}

// test requesting vin number and update pids database at setup mode but vehicle don't respond
void test_case_0008(void){
    // setup
    
    u8_t *vinNumber = "VSS12345678911111";
    u8_Process_Request_IgnoreAndReturn(0);
    p_getResponseMessage_IgnoreAndReturn(vinNumber);
    u32_getResponseSize_IgnoreAndReturn(17);

    // act
    vid_VehicleApp_Manage();

    // assert
    TEST_ASSERT_EQUAL_STRING("",GLOB_arrVinNumber);
    TEST_ASSERT_EQUAL_CHAR(0, GLOB_u8switchToNormalMode);
    
    // cleanup
    GLOB_u8switchToNormalMode = 0;

}


// test normal mode with empty requests queue (idle state)
void test_case_0009(void){
    // setup
    
    u8_QueueIF_Pop_IgnoreAndReturn(0); // empty requests
    GLOB_u8switchToNormalMode = 1;

    // act
    vid_VehicleApp_Manage();

    // assert
        // nothing to assert here the test has been implemented to satisfy the 100% MCDC
    // cleanup
    GLOB_u8switchToNormalMode = 0;

}


// test normal mode with a stored request = vehicle speed 
void test_case_0010(void){
    // setup
    void ResponseCallback(u8_t* pData, u32_t sizeofdata, u8_t notification){
        TEST_ASSERT_EQUAL_STRING("testData",pData);
        TEST_ASSERT_EQUAL_UINT32(strlen("testData"), sizeofdata);
        TEST_ASSERT_EQUAL_CHAR(1, notification);
    }

    Vehicle_RequestTypedef myRequest = {.service = MANUAL_REQUEST,.obd_mode = OBD_MODE_1, .obd_pid = 0x0d,.callback = ResponseCallback};

    u8_t u8_QueueIF_Pop_stubber(QHandler handler, void *request, int x){
        memcpy(request, &myRequest, sizeof(Vehicle_RequestTypedef));
        return 1;
    }

    uint8_t u8_Process_Request_stubber(RequestType service, Vehicle_RequestTypedef *request, int x){
        TEST_ASSERT_EQUAL_MEMORY(request, &myRequest, sizeof(Vehicle_RequestTypedef));
        TEST_ASSERT_EQUAL_INT(MANUAL_REQUEST, service);
        return 1;
    }

    u8_QueueIF_Pop_Stub(u8_QueueIF_Pop_stubber);
    u8_Process_Request_Stub(u8_Process_Request_stubber);
    p_getResponseMessage_IgnoreAndReturn("testData");
    u32_getResponseSize_IgnoreAndReturn(strlen("testData"));
    vid_Processing_Reset_Ignore();
    GLOB_u8switchToNormalMode = 1;

    // act
    vid_VehicleApp_Manage();

    // assert
        // all assertions are in the stubber functions
        
    // cleanup
    GLOB_u8switchToNormalMode = 0;

}

// test requesting system fuel state after counter reached its point
void test_case_0011(void){
    // setup
    GLOB_u32scheduling_counter = 10001;

    void ResponseCallback(u8_t* pData, u32_t sizeofdata, u8_t notification){
        TEST_ASSERT_EQUAL_STRING("testData",pData);
        TEST_ASSERT_EQUAL_UINT32(strlen("testData"), sizeofdata);
        TEST_ASSERT_EQUAL_CHAR(1, notification);
    }


    uint8_t u8_QueueIF_Pop_stubber(QHandler handler, void *request, int x){
        memcpy(request, &LOC_str_fuelSystemRequest, sizeof(Vehicle_RequestTypedef));
        return 1;
    }

    uint8_t u8_Process_Request_stubber(RequestType service, Vehicle_RequestTypedef *request, int x){
        TEST_ASSERT_EQUAL_INT(MANUAL_REQUEST, service);
        TEST_ASSERT_EQUAL_INT(OBD_MODE_1, request->obd_mode);
        TEST_ASSERT_EQUAL_CHAR(3, request->obd_pid);
        return 1;
    }

    u8_QueueIF_Pop_Stub(u8_QueueIF_Pop_stubber);
    u8_QueueIF_Push_IgnoreAndReturn(1);
    u8_Process_Request_Stub(u8_Process_Request_stubber);
    p_getResponseMessage_IgnoreAndReturn("testData");
    u32_getResponseSize_IgnoreAndReturn(strlen("testData"));
    vid_Processing_Reset_Ignore();
    GLOB_u8switchToNormalMode = 1;

    // act
    vid_VehicleApp_Manage();

    // assert
        // all assertions are in the stubber functions

    // cleanup
    GLOB_u8switchToNormalMode = 0;

}


