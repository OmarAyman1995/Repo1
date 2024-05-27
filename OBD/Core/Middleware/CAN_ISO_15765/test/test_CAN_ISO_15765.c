#include "CAN_ISO_15765.h"
#include "CAN_ISO_Cnfg.h"
#include "mock_CANISO_UTFake.h"
#include "mock_services.h"
#include "unity.h"

extern u8_t  GLOB_u8CanIDType;

extern u32_t GLOB_u32DiagnosticCANID;

extern u8_t GLOB_ReceptionSuccessFlag;

extern u8_t GLOB_TransmitSuccessFlag;

extern u32_t GLOB_u32TimeoutCount;


extern enum_CanIsoErrorState enum_EchoFunctionalRequest(u32_t CAN_ID);

extern u8_t u8_CheckFlagState(u8_t *u8Flag);

extern enum_IsoCompliantState enum_VerifyCanID(u32_t CAN_ID);


extern u8_t u8_HandleResponse(void);

extern void vid_TransmitCallback(void);

extern void vid_ReceiveCallback(void);

     
/*_______________________________________enum_EchoFunctionalRequest()___________________________________*/
/*_______________________________________________________________________________________________________________________*/

/// @brief Can TransmitAPI returns error, API returns error 
void test_CCO_TC_UT_1300(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanTransmit_CMockIgnoreAndReturn(1,CANNOK);
    u32_t CAN_ID=3;

  
    // Act
   returnValue=enum_EchoFunctionalRequest(CAN_ID);



    // Assert
    TEST_ASSERT_EQUAL_INT(CAN_ISO_NOK,returnValue);
 
    // Cleanup
}


/// @brief Can TransmitAPI returns OK, API returns OK  
void test_CCO_TC_UT_1301(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);
    u32_t CAN_ID=3;

  
    // Act
   returnValue=enum_EchoFunctionalRequest(CAN_ID);



    // Assert
    TEST_ASSERT_EQUAL_INT(CAN_ISO_OK,returnValue);
 
    // Cleanup
}


/*_______________________________________u8_CheckForFlagState()___________________________________*/

/// @brief Transmisison Success flag isn't raised, Timeout occurs and function returns API Error
void test_CCO_TC_UT_1302(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;

    
  
    // Act
   returnValue=u8_CheckFlagState(&GLOB_TransmitSuccessFlag);



    // Assert
    TEST_ASSERT_EQUAL_INT(OPERATION_FAILED,returnValue);
 
    // Cleanup
    GLOB_u32TimeoutCount=0;
    GLOB_TransmitSuccessFlag=FLAG_CLEAR;
    GLOB_ReceptionSuccessFlag=FLAG_CLEAR;
}

/// @brief Transmisison Success flag is raised, API returns OK
void test_CCO_TC_UT_1303(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    vid_TransmitCallback();

    

    // Act
   returnValue=u8_CheckFlagState(&GLOB_TransmitSuccessFlag);


    // Assert
    TEST_ASSERT_EQUAL_INT(OPERATION_SUCCESS,returnValue);
 
    // Cleanup
    GLOB_u32TimeoutCount=0;
    GLOB_TransmitSuccessFlag=FLAG_CLEAR;
    GLOB_ReceptionSuccessFlag=FLAG_CLEAR;
}



/*_______________________________________enum_VerifyCanID()___________________________________*/
/// @brief Transmission Flag is not set, API returns 
void test_CCO_TC_UT_1304(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);

    // Act
    returnValue=enum_VerifyCanID(DIAGNOSTIC_CAN_ID_11BIT);


    // Assert
     TEST_ASSERT_EQUAL_INT(ISO15765_NOT_COMPLIANT,returnValue);
 
 
    // Cleanup
    GLOB_u32TimeoutCount=0;
    GLOB_TransmitSuccessFlag=FLAG_CLEAR;
    GLOB_ReceptionSuccessFlag=FLAG_CLEAR;
}

/// @brief Transmission Flag is set, but reception flag is not set, API returns not complaint
void test_CCO_TC_UT_1305(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);
    vid_TransmitCallback();


    // Act
    returnValue=enum_VerifyCanID(DIAGNOSTIC_CAN_ID_11BIT);


    // Assert
     TEST_ASSERT_EQUAL_INT(ISO15765_NOT_COMPLIANT,returnValue);
 
 
    // Cleanup
    GLOB_u32TimeoutCount=0;
    GLOB_TransmitSuccessFlag=FLAG_CLEAR;
    GLOB_ReceptionSuccessFlag=FLAG_CLEAR;

}

/// @brief Transmission Flag is set, reception flag is set, API returns Complaint
void test_CCO_TC_UT_1306(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);
    vid_TransmitCallback();
    vid_ReceiveCallback();
    


    // Act
    returnValue=enum_VerifyCanID(DIAGNOSTIC_CAN_ID_11BIT);


    // Assert
     TEST_ASSERT_EQUAL_INT(ISO15765_COMPLIANT,returnValue);
 
 
    // Cleanup
    GLOB_u32TimeoutCount=0;
}

/*_______________________________________enum_DetectCANComm ()___________________________________*/

/// @brief input argument is NULL, API fail
void test_CCO_TC_UT_1307(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanSetBitTiming_CMockIgnoreAndReturn(1,CAN_OK);
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);


    // Act
    returnValue=enum_DetectCANComm(NULL,3);


    // Assert
     TEST_ASSERT_EQUAL_INT(ERROR_IN_BAUDRATE_RECORD,returnValue);
 
 
    // Cleanup
    GLOB_u32TimeoutCount=0;
}


/// @brief baudrate record size is bigger than MAX_BAUDRATE_RECORD_SIZE,  API fail
void test_CCO_TC_UT_1308(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanSetBitTiming_CMockIgnoreAndReturn(1,CAN_OK);
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);
    u32_t baudrate[3]={0};


    // Act
    returnValue=enum_DetectCANComm(baudrate,MAX_BAUDRATE_RECORD_SIZE+1);


    // Assert
     TEST_ASSERT_EQUAL_INT(ERROR_IN_BAUDRATE_RECORD,returnValue);
 
 
    // Cleanup
    GLOB_u32TimeoutCount=0;
}




/// @brief input arguments is OK, verficiation of 11 bit CAN ID is compliant
void test_CCO_TC_UT_1311(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanSetBitTiming_CMockIgnoreAndReturn(1,CAN_OK);
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);
    vid_TransmitCallback();
    vid_ReceiveCallback();

    u32_t baudrate[3]={0};


    // Act
    returnValue=enum_DetectCANComm(baudrate,3);


    // Assert
     TEST_ASSERT_EQUAL_INT(ISO15765_COMPLIANT,returnValue);
     TEST_ASSERT_EQUAL_INT(STANDARD_ID,GLOB_u8CanIDType);
 
 
    // Cleanup
}





/*_______________________________________enum_CanIsoSendData()___________________________________*/

/// @brief input arguments has NULL, API not ok
void test_CCO_TC_UT_1312(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);
    u8_t *data=NULL;


    // Act
    returnValue=enum_CanIsoSendData(data,3);


    // Assert
     TEST_ASSERT_EQUAL_INT(CAN_ISO_NOK,returnValue);
 
 
    // Cleanup
}

/// @brief input arguments has NULL, API not ok
void test_CCO_TC_UT_1313(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);
    u8_t data[3]={0};


    // Act
    returnValue=enum_CanIsoSendData(data,MAX_CAN_FRAME_DATAPAYLOAD+1);


    // Assert
     TEST_ASSERT_EQUAL_INT(CAN_ISO_NOK,returnValue);
 
 
    // Cleanup
}


/// @brief input arguments has NULL, API not ok
void test_CCO_TC_UT_1314(void)
{
   
   // Setup
    enum_CanIsoErrorState returnValue=0;
    enum_CanTransmit_CMockIgnoreAndReturn(1,CAN_OK);
    cpy_array_CMockIgnore();
    u8_t data[3]={0};


    // Act
    returnValue=enum_CanIsoSendData(data,MAX_CAN_FRAME_DATAPAYLOAD);


    // Assert
     TEST_ASSERT_EQUAL_INT(CAN_ISO_OK,returnValue);
 
 
    // Cleanup
}

