#include "UDSHandler.h"
#include "UDSHandlerConfig.h"
#include "mock_CANTp.h"
#include "mock_services.h"


extern UdsHandlerStatus_e     GLOB_UdsState; 
extern TpReceiveDataUnitInfo_t *GLOB_PtrToTpDataUnit;
extern UDSReceiveInfo_t         GLOB_SduDataUnit; 


extern enumUdsHandlerApiError_e UdsProcessing(const TpReceiveDataUnitInfo_t* DataPayload);
extern u8_t u8DecideSIDType(u8_t responseSID);



void dummyFunction(void)
{

}





/*______________________enum_RequestReadByIdentifier____________________________*/

/**
 * @brief service option smaller than Lower Limit, return Error
 * 
 */
void test_CCO_TC_UT_1450 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=READ_BY_IDENTIFIER_RANGE_L_LIMIT- 0x05
  };

    // Act
    retval=enum_RequestReadByIdentifier(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_ERROR_SERVICE_CODE_INVALID,retval);

    // Cleanup
}


/**
 * @brief service option equal Lower Limit, return OK
 * 
 */
void test_CCO_TC_UT_1451 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=READ_BY_IDENTIFIER_RANGE_L_LIMIT
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestReadByIdentifier(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_OK_TRANSMIT_PENDING,retval);

    // Cleanup
}


/**
 * @brief service option in range, return OK
 * 
 */
void test_CCO_TC_UT_1452 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=READ_BY_IDENTIFIER_RANGE_L_LIMIT + 0x05
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestReadByIdentifier(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_OK_TRANSMIT_PENDING,retval);

    // Cleanup
}


/**
 * @brief service option equals upper limit, return OK
 * 
 */
void test_CCO_TC_UT_1453 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=READ_BY_IDENTIFIER_RANGE_H_LIMIT
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestReadByIdentifier(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_OK_TRANSMIT_PENDING,retval);

    // Cleanup
}



/**
 * @brief service option equals upper limit, return OK
 * 
 */
void test_CCO_TC_UT_1454 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=READ_BY_IDENTIFIER_RANGE_H_LIMIT+ 0x05
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestReadByIdentifier(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_ERROR_SERVICE_CODE_INVALID,retval);

    // Cleanup
}

/**
 * @brief service option equals upper limit, Can TP API returns Not ok, API returns Error
 * 
 */
void test_CCO_TC_UT_1455 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=READ_BY_IDENTIFIER_RANGE_H_LIMIT
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_NOT_OK);

    // Act
    retval=enum_RequestReadByIdentifier(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_ERROR_REQUEST_SENDING_FAILED,retval);

    // Cleanup
}



/*_________________________________________________enum_RequestTesterPresent____________________________*/

/**
 * @brief service option equals on of the values, API return OK
 * 
 */
void test_CCO_TC_UT_1456 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=TESTER_PRESENT_SUB_VALUE_1
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestTesterPresent(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_OK_TRANSMIT_PENDING,retval);

    // Cleanup
}



/**
 * @brief service option equals on of the values, API return OK
 * 
 */
void test_CCO_TC_UT_1457 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=TESTER_PRESENT_SUB_VALUE_2
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestTesterPresent(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_OK_TRANSMIT_PENDING,retval);

    // Cleanup
}



/**
 * @brief service option doesn't equal none of the values, API return Error
 * 
 */
void test_CCO_TC_UT_1458 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=TESTER_PRESENT_SUB_VALUE_2 + 0x05
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestTesterPresent(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_ERROR_SERVICE_CODE_INVALID,retval);

    // Cleanup
}



/**
 * @brief service option equals on of the values, But CanTp Function returns error, API return Error
 * 
 */
void test_CCO_TC_UT_1459 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption=TESTER_PRESENT_SUB_VALUE_2
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_NOT_OK);

    // Act
    retval=enum_RequestTesterPresent(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_ERROR_REQUEST_SENDING_FAILED,retval);

    // Cleanup
}


/*_________________________________________________________enum_RequestEcuReset____________________________*/
/**
 * @brief service option equals limit, API return OK
 * 
 */
void test_CCO_TC_UT_1460 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption= ECU_RESET_RANGE_H_LIMIT
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestEcuReset(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_OK_TRANSMIT_PENDING,retval);

    // Cleanup
}


/**
 * @brief service option is lower than limit, API return OK
 * 
 */
void test_CCO_TC_UT_1461 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption= ECU_RESET_RANGE_H_LIMIT-1
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestEcuReset(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_OK_TRANSMIT_PENDING,retval);

    // Cleanup
}


/**
 * @brief service option is lower than limit, API return OK
 * 
 */
void test_CCO_TC_UT_1462 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption= ECU_RESET_RANGE_H_LIMIT+1
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_OK);

    // Act
    retval=enum_RequestEcuReset(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_ERROR_SERVICE_CODE_INVALID,retval);

    // Cleanup
}


/**
 * @brief service option is lower than limit, but CAN Tp api return error, API return Error
 * 
 */
void test_CCO_TC_UT_1463 (void)
{
  // Setup

  enumUdsHandlerApiError_e retval = 0;
  const UDSTransmitInfo_t inputStruct=
  {
    .ServiceOption= ECU_RESET_RANGE_H_LIMIT-1
  };

  vid_TpTransmitDataUnit_CMockIgnoreAndReturn(156,CAN_TP_API_NOT_OK);

    // Act
    retval=enum_RequestEcuReset(&inputStruct);

    // Assert
    TEST_ASSERT_EQUAL_INT(API_ERROR_REQUEST_SENDING_FAILED,retval);

    // Cleanup
}



/*_________________________________________________________vid_UDSHandlerManage____________________________*/
/**
 * @brief UDS State flag is set to request response Received, UDS processing is done and flag is set to Data ready
 * 
 */
void test_CCO_TC_UT_1464 (void)
{
  // Setup
  vid_TpSetReceiveCallBack_CMockIgnore();
  vid_TpSetTransmitCallBack_CMockIgnore();
  vid_UDSHandlerInit();
  linearSearch_CMockIgnoreAndReturn(1,NEGATIVE_SEARCH);
  cpy_array_CMockIgnore();
  GLOB_UdsState=REQUEST_RESPONSE_RECEIVED;
  TpReceiveDataUnitInfo_t TpDataUnit={0};
  GLOB_PtrToTpDataUnit=&TpDataUnit;


    // Act
    
    vid_UDSHandlerManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(DATA_READY,GLOB_UdsState);

    // Cleanup
    GLOB_UdsState=FREE;
}



/**
 * @brief UDS State flag is set to free, UDS processing is not done and state is still free
 * 
 */
void test_CCO_TC_UT_1465 (void)
{
  // Setup
  GLOB_UdsState=FREE;
   vid_TpSetReceiveCallBack_CMockIgnore();
   vid_TpSetTransmitCallBack_CMockIgnore();

  vid_UDSHandlerInit();

    // Act
    vid_UDSHandlerManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(FREE,GLOB_UdsState);

    // Cleanup
    GLOB_UdsState=FREE;
}




/*_________________________________________________________vid_ReceiveUdsData____________________________*/
/**
 * @brief UDS State flag is set to free , API returns NULL 
 * 
 */
void test_CCO_TC_UT_1466 (void)
{
  // Setup
  UDSReceiveInfo_t *ptrReturn=NULL;
  GLOB_UdsState=FREE;

    // Act
    
    ptrReturn=vid_ReceiveUdsData();

    // Assert
    TEST_ASSERT_EQUAL_INT(NULL,ptrReturn);

    // Cleanup
    GLOB_UdsState=FREE;
}



/**
 * @brief UDS State flag is set to request response Received, UDS processing is done and flag is set to Data ready
 * 
 */
void test_CCO_TC_UT_1467 (void)
{
  // Setup
  UDSReceiveInfo_t *ptrReturn=NULL;
  GLOB_UdsState=DATA_READY;

    // Act
    
    ptrReturn=vid_ReceiveUdsData();

    // Assert
    TEST_ASSERT_EQUAL_INT(&GLOB_SduDataUnit,ptrReturn);

    // Cleanup
    GLOB_UdsState=FREE;
}



/*_________________________________________________________vid_UdsHandlerSetTransmissionNotify____________________________*/
/**
 * @brief Callback function is NULL, Global variable is set to null
 * 
 */
void test_CCO_TC_UT_1468 (void)
{
  // Setup
 enumUdsHandlerApiError_e ReturnValue=0;

    // Act
    
    ReturnValue=enum_UdsHandlerSetTransmissionNotify(NULL);

    // Assert
    TEST_ASSERT_EQUAL_INT(UDS_HANDLER_API_NOK, ReturnValue);

    // Cleanup

}


/**
 * @brief Callback function is NULL, Global variable is set to null
 * 
 */
void test_CCO_TC_UT_1469 (void)
{
  // Setup
 enumUdsHandlerApiError_e ReturnValue=0;

    // Act
    
    ReturnValue=enum_UdsHandlerSetTransmissionNotify(dummyFunction);

    // Assert
    TEST_ASSERT_EQUAL_INT(UDS_HANDLER_API_OK, ReturnValue);

    // Cleanup

}

/*_________________________________________________________vid_UdsHandlerSetReceptionNotify____________________________*/

/**
 * @brief Callback function is NULL, function return error
 * 
 */
void test_CCO_TC_UT_1470 (void)
{
  // Setup
 enumUdsHandlerApiError_e ReturnValue=0;

    // Act
    
    ReturnValue=enum_UdsHandlerSetReceptionNotify(NULL);

    // Assert
    TEST_ASSERT_EQUAL_INT(UDS_HANDLER_API_NOK, ReturnValue);

    // Cleanup

}


/**
 * @brief Callback function is not NULL, function return OK
 * 
 */
void test_CCO_TC_UT_1471 (void)
{
  // Setup
 enumUdsHandlerApiError_e ReturnValue=0;

    // Act
    
    ReturnValue=enum_UdsHandlerSetReceptionNotify(dummyFunction);

    // Assert
    TEST_ASSERT_EQUAL_INT(UDS_HANDLER_API_OK, ReturnValue);

    // Cleanup

}



/*_________________________________________________________u8DecideSIDType____________________________*/

/**
 * @brief response SID is negative, fuction return Negative SID Type
 * 
 */
void test_CCO_TC_UT_1472 (void)
{
  // Setup
 u8_t ReturnValue=0;
 u8_t responseSID=NEGATIVE_SID_RESPONSE;
 linearSearch_CMockIgnoreAndReturn(1,NEGATIVE_SEARCH);

    // Act
    
    ReturnValue=u8DecideSIDType(responseSID);

    // Assert
    TEST_ASSERT_EQUAL_INT(NEGATIVE_SID_TYPE, ReturnValue);

    // Cleanup

}


/**
 * @brief response SID is Positive and search for SID with DID is negative,API return psotive SID with Sub function
 * 
 */
void test_CCO_TC_UT_1473 (void)
{
  // Setup
 u8_t ReturnValue=0;
 u8_t responseSID=NEGATIVE_SID_RESPONSE+4;
 linearSearch_CMockIgnoreAndReturn(1,NEGATIVE_SEARCH);

    // Act
    
    ReturnValue=u8DecideSIDType(responseSID);

    // Assert
    TEST_ASSERT_EQUAL_INT(POSITIVE_SID_SUB_FUNC_TYPE, ReturnValue);

    // Cleanup

}


/**
 * @brief response SID is Positive and search for SID with DID is Positive,API return psotive SID with DID
 * 
 */
void test_CCO_TC_UT_1474 (void)
{
  // Setup
 u8_t ReturnValue=0;
 u8_t responseSID=NEGATIVE_SID_RESPONSE+4;
 linearSearch_CMockIgnoreAndReturn(1,2);

    // Act
    
    ReturnValue=u8DecideSIDType(responseSID);

    // Assert
    TEST_ASSERT_EQUAL_INT(POSITIVE_SID_DID_TYPE, ReturnValue);

    // Cleanup

}


/*_________________________________________________________UdsProcessing____________________________*/

/// @todo Check RunTime error occuring with this test cases
/**
 * @brief response SID is negative, Function does the processing and return OK
 * 
 */
void test_CCO_TC_UT_1475 (void)
{
  // Setup
 u8_t ReturnValue=0;
 TpReceiveDataUnitInfo_t input={
 .u8DataPayloadSize=50};
 input.u8TpDataPayload[0]=NEGATIVE_SID_RESPONSE;
 linearSearch_CMockIgnoreAndReturn(1,NEGATIVE_SEARCH);
 cpy_array_CMockIgnore();

    // Act
    
    ReturnValue=UdsProcessing(&input);

    // Assert
    TEST_ASSERT_EQUAL_INT(UDS_HANDLER_API_OK, ReturnValue);

    // Cleanup

}


/**
 * @brief response SID is Positive with DID, Function does the processing and return OK 
 * 
 */
void test_CCO_TC_UT_1476 (void)
{
    // Setup
 u8_t ReturnValue=0;
 TpReceiveDataUnitInfo_t input={0};
   input.u8TpDataPayload[0]=NEGATIVE_SID_RESPONSE+3;
 linearSearch_CMockIgnoreAndReturn(1,2);
 cpy_array_CMockIgnore();

    // Act
    
    ReturnValue=UdsProcessing(&input);

    // Assert
    TEST_ASSERT_EQUAL_INT(UDS_HANDLER_API_OK, ReturnValue);

    // Cleanup


}


/**
 * @brief response SID is potitive with subfunction, Function does the processing and return OK 
 * 
 */
void test_CCO_TC_UT_1477 (void)
{
   // Setup
 u8_t ReturnValue=0;
TpReceiveDataUnitInfo_t input={0};
  input.u8TpDataPayload[0]= NEGATIVE_SID_RESPONSE+3;
 linearSearch_CMockIgnoreAndReturn(1,NEGATIVE_SEARCH);
 cpy_array_CMockIgnore();

    // Act
    
    ReturnValue=UdsProcessing(&input);

    // Assert
    TEST_ASSERT_EQUAL_INT(UDS_HANDLER_API_OK, ReturnValue);

    // Cleanup

}


// /**
//  * @brief test defaultfor the condition in this function, Not reachable and can't be covered !!
//  * 
//  */
// void test_CCO_TC_UT_1478 (void)
// {
//    // Setup
//  u8_t ReturnValue=0;
//  TpReceiveDataUnitInfo_t input={0};
//  input.u8TpDataPayload[0]= NEGATIVE_SID_RESPONSE+3;
//  linearSearch_CMockIgnoreAndReturn(1,2);
//  cpy_array_CMockIgnore();

//     // Act
    
//     ReturnValue=UdsProcessing(&input);

//     // Assert
//     TEST_ASSERT_EQUAL_INT(UDS_HANDLER_API_NOK, ReturnValue);

//     // Cleanup

// }








