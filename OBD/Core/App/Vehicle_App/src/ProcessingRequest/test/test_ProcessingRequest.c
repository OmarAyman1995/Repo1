#include "unity.h"
#include "mock_OfferedServices.h"
#include "services.h"
#include "mock_OBDIIHandler.h"
// #include "ConvUnits.h"
#include "mock_ConversionMngr.h"
#include "ProcessingRequest.h"

#include "string.h"

u8_t u8_ConvertOBDToPhysicalValue_Stubbing(u8_t pid, u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string, int cmock_num_calls){
    strcpy(output_string, "255");
}



void test_case_0001(void){
    // setup
    u8_make_manual_obd_request_IgnoreAndReturn(1);
    OBDII_Reset_Ignore();
    
    u8_t expectedResponse[5] = " 255";
    expectedResponse[0] = 3;

    u8_t returnCheck = 0;
    Vehicle_RequestTypedef request = {0};
    u8_t *receivedData;
    u8_t receivedData_OnOBD[8] = {8,1,13,255,255,255,255,255};
    OBDII_receive_IgnoreAndReturn(receivedData_OnOBD);
    OBDII_getReceivedSize_IgnoreAndReturn(8);
    u8_ConvertOBDToPhysicalValue_Stub(u8_ConvertOBDToPhysicalValue_Stubbing);
    u32_getConvertedSize_IgnoreAndReturn(3);
    // act
    request.service  = MANUAL_REQUEST;
    request.obd_mode = OBD_MODE_1;
    request.obd_pid  = VEHICLE_SPEED;
    returnCheck  = u8_Process_Request(MANUAL_REQUEST,&request);
    receivedData = p_getResponseMessage();

    // assert
    TEST_ASSERT_EQUAL_INT(1, returnCheck);
    TEST_ASSERT_EQUAL_STRING(expectedResponse, receivedData);
    // cleanup

}


void test_case_0002(void){
    // setup
    u8_make_manual_obd_request_IgnoreAndReturn(1);
    OBDII_Reset_Ignore();
    
    u8_t expectedResponse[5] = " 255";
    expectedResponse[0] = 3;

    u8_t returnCheck = 0;
    Vehicle_RequestTypedef request = {0};
    u8_t *receivedData;
    u8_t receivedData_OnOBD[8] = {8,1,13,255,255,255,255,255};
    OBDII_receive_IgnoreAndReturn(receivedData_OnOBD);
    OBDII_getReceivedSize_IgnoreAndReturn(8);
    u8_ConvertOBDToPhysicalValue_Stub(u8_ConvertOBDToPhysicalValue_Stubbing);
    u32_getConvertedSize_IgnoreAndReturn(3);

    // act
    request.service  = MANUAL_REQUEST;
    request.obd_mode = OBD_MODE_1;
    request.obd_pid  = VEHICLE_SPEED;
    returnCheck  = u8_Process_Request(MANUAL_REQUEST,&request);
    receivedData = p_getResponseMessage();

    // assert
    TEST_ASSERT_EQUAL_INT(1, returnCheck);
    TEST_ASSERT_EQUAL_STRING(expectedResponse, receivedData);
    
    // cleanup

}