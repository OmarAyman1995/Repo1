#include "CANTp.h"
#include "CANConfig.h"
#include "mock_CmsisAbstract.h"
#include "mock_Can.h"
#include "mock_services.h"





/*************************************** before running unit test cases***************************/
/* - comment the calling of the callback functions lines ( GLOB_pCallbackfunc1() ) in the TpProcessing function 
     to avoid run time fault due to derefernceing a NULL pointer

   - make sure these two global variables are not static 
     to be able to extern them in the unit test: 
                                                - strCanDrvFrameInfo* receivedCanFrame
                                                - u8_t GLOB_ReceptionlFlag */



/*************************************** Test Data Varibales***************************/

#define UDS_REQUEST_CAN_ID    0x7E1
#define UDS_RESPONSE_CAN_ID   0x7E9


extern TpReceiveDataUnitInfo_t GLOB_strTpDataUnit;                            /*structure containing the data unit of the TP Module*/

extern void(*GLOB_pCallbackfunc1)(void);                                 /* pointer to function for reception callback function*/

extern void(*GLOB_pCallbackfunc2)(void);                                /*pointer to function for transmission callback function*/

extern u8_t GLOB_ReceptionFlag;                                         /*flag to indicate a a reception has occured*/

extern u8_t GLOB_DataUnitReadyFlag;                                    /*flag to indicate a data unit has been processed in tp and ready to deliver to upper layers*/

extern strCanDrvFrameInfo GLOB_ReceivedCanFrame;                       /*Structure for recieved CAN Frame*/

extern u8_t    GLOB_ConsecutiveFramesCounter;
extern IsoTpOption_e GLOB_u8IsoTpOption;     


extern u8_t u8_TpIsoProcessingSequence(const strCanDrvFrameInfo* frame);

extern u8_t u8_ConcectiveFrameResponseReception(const strCanDrvFrameInfo* frame, u16_t currentIndex,u16_t expectedNumOfFrames);

extern void CallbackPtrDefaultFunc(void);

void dummyFunction1 (void)
{

}

void dummyFunction2 (void)
{

}

/*************************************** u8_ConcectiveFrameResponseReception***************************/

/// @brief All concective frames are received, function returns "ALL_CONCECTIVE_FRAMES_RECEIVED"
void test_CCO_TC_UT_1400 (void)
{
    // Setup
    u8_t returnValue=0;
    strCanDrvFrameInfo frame={0};
    u16_t currentIndex=0;
    GLOB_ConsecutiveFramesCounter=1;
    u16_t expectedNumOfFrames=2;
    cpy_array_CMockIgnore();

    // Act
    returnValue=u8_ConcectiveFrameResponseReception(&frame,currentIndex,expectedNumOfFrames);
    

    // Assert
    TEST_ASSERT_EQUAL_INT(ALL_CONCECTIVE_FRAMES_RECEIVED,returnValue);

    // Cleanup
     GLOB_ConsecutiveFramesCounter=0;
}


/**
 * @brief All concective frames are not received, function returns "STILL_EXPECTING_CONCECTIVE_FRAME"
 * 
 */
void test_CCO_TC_UT_1401 (void)
{
    // Setup
    u8_t returnValue=0;
    strCanDrvFrameInfo frame={0};
    u16_t currentIndex=0;
    GLOB_ConsecutiveFramesCounter=0;
    u16_t expectedNumOfFrames=2;
    cpy_array_CMockIgnore();


    // Act
    returnValue=u8_ConcectiveFrameResponseReception(&frame,currentIndex,expectedNumOfFrames);
    

    // Assert
    TEST_ASSERT_EQUAL_INT(STILL_EXPECTING_CONCECTIVE_FRAME,returnValue);

    // Cleanup
     GLOB_ConsecutiveFramesCounter=0;
}

/*************************************** u8_TpIsoProcessingSequence()***************************/

/**
 * @brief Single Frame is received, function return single Frame
 * 
 */
void test_CCO_TC_UT_1402 (void)
{
    // Setup
    u8_t returnValue=0;
    strCanDrvFrameInfo frame={0};
    frame.data[DATA_PAYLOAD_BYTE0_INDEX]=SINGLE_FRAME_VALUE;

    cpy_array_CMockIgnore();
    enum_CanDrvTransmit_CMockIgnoreAndReturn(1,CAN_API_OK);
    vid_CanDrvSetReceiveCallPack_CMockIgnore();
    vid_CanDrvSetTransmitCallPack_CMockIgnore();
    vid_TpInit();


    // Act
    returnValue=u8_TpIsoProcessingSequence(&frame);
    

    // Assert
    TEST_ASSERT_EQUAL_INT(SINGLE_FRAME,returnValue);

    // Cleanup

}


/**
 * @brief first Frame is received, function return first Frame
 * 
 */
void test_CCO_TC_UT_1403 (void)
{
    // Setup
    
    u8_t returnValue=0;
    strCanDrvFrameInfo frame={0};
    frame.data[DATA_PAYLOAD_BYTE0_INDEX]=FIRST_FRAME_VALUE;
    cpy_array_CMockIgnore();
    enum_CanDrvTransmit_CMockIgnoreAndReturn(1,CAN_API_OK);
    vid_CanDrvSetReceiveCallPack_CMockIgnore();
    vid_CanDrvSetTransmitCallPack_CMockIgnore();
    vid_TpInit();


    // Act
    returnValue=u8_TpIsoProcessingSequence(&frame);
    

    // Assert
    TEST_ASSERT_EQUAL_INT(FIRST_FRAME,returnValue);

    // Cleanup

}

/**
 * @brief Concective Frame is received, function return Concective Frame
 * 
 */
void test_CCO_TC_UT_1404 (void)
{
    // Setup
    u8_t returnValue=0;
    strCanDrvFrameInfo frame={0};
    frame.data[DATA_PAYLOAD_BYTE0_INDEX]=CONCECTIVE_FRAME_VALUE;
    cpy_array_CMockIgnore();
    enum_CanDrvTransmit_CMockIgnoreAndReturn(1,CAN_API_OK);
    vid_CanDrvSetReceiveCallPack_CMockIgnore();
    vid_CanDrvSetTransmitCallPack_CMockIgnore();
    vid_TpInit();


    // Act
    returnValue=u8_TpIsoProcessingSequence(&frame);
    

    // Assert
    TEST_ASSERT_EQUAL_INT(CONCECTIVE_FRAME,returnValue);

    // Cleanup

}

/**
 * @brief Default case test,  unknown frame is received , function return Unknown Frame
 * 
 */
void test_CCO_TC_UT_1405 (void)
{
    // Setup
    u8_t returnValue=0;
    strCanDrvFrameInfo frame={0};
    frame.data[DATA_PAYLOAD_BYTE0_INDEX]=0x30;
    cpy_array_CMockIgnore();
    enum_CanDrvTransmit_CMockIgnoreAndReturn(1,CAN_API_OK);
    vid_CanDrvSetReceiveCallPack_CMockIgnore();
    vid_CanDrvSetTransmitCallPack_CMockIgnore();
    vid_TpInit();


    // Act
    returnValue=u8_TpIsoProcessingSequence(&frame);
    

    // Assert
    TEST_ASSERT_EQUAL_INT(UNKNOWN_FRAME,returnValue);

    // Cleanup

}



/*************************************** vid_TpTransmitDataUnit()***************************/

/**
 *  @brief Can API return Error while transmitting, API return Error
 * 
 */
void test_CCO_TC_UT_1410 (void)
{
    // Setup
    enumTpApiError_e returnValue;
    TpTransmitDataUnitInfo frame={0};
    enum_CanDrvTransmit_CMockIgnoreAndReturn(1,CAN_API_NOT_OK);
    cpy_array_CMockIgnore();



    // Act
    returnValue=vid_TpTransmitDataUnit(&frame);
    

    // Assert
   TEST_ASSERT_EQUAL_INT(CAN_API_NOT_OK,returnValue);

    // Cleanup

}


/**
 *  @brief Can API return ok , API return Ok
 * 
 */
void test_CCO_TC_UT_1411 (void)
{
    // Setup
    enumTpApiError_e returnValue;
    TpTransmitDataUnitInfo frame={0};
    enum_CanDrvTransmit_CMockIgnoreAndReturn(1,CAN_API_OK);
    cpy_array_CMockIgnore();



    // Act
    returnValue=vid_TpTransmitDataUnit(&frame);
    

    // Assert
   TEST_ASSERT_EQUAL_INT(CAN_API_OK,returnValue);

    // Cleanup
}



/*************************************** vid_TpSetTransmitCallBack()***************************/

/**
 *  @brief callback function is NULL, function does nothing and Global pointer is still NULL
 * 
 */
void test_CCO_TC_UT_1412 (void)
{
    // Setup
    GLOB_pCallbackfunc2=NULL;
    void (*ptr)(void)=NULL;

    // Act
    vid_TpSetTransmitCallBack(ptr);
    

    // Assert
   TEST_ASSERT_EQUAL_INT(NULL,GLOB_pCallbackfunc2);

    // Cleanup
    GLOB_pCallbackfunc2=NULL;
}


/**
 *  @brief callback function is not NULL and global pointer is NULL, function assigns callback function address to global pointer
 * 
 */
void test_CCO_TC_UT_1413 (void)
{
    // Setup
    GLOB_pCallbackfunc2=CallbackPtrDefaultFunc;
     
    // Act
    vid_TpSetTransmitCallBack(dummyFunction1);
    

    // Assert
   TEST_ASSERT_EQUAL_INT(dummyFunction1,GLOB_pCallbackfunc2);

    // Cleanup
    GLOB_pCallbackfunc2=NULL;
}


/*************************************** vid_TpSetReceiveCallBack()***************************/

/**
 *  @brief callback function is NULL, function does nothing and Global pointer is still NULL
 * 
 */
void test_CCO_TC_UT_1415 (void)
{
    // Setup
    GLOB_pCallbackfunc1=NULL;
    void (*ptr)(void)=NULL;

    // Act
    vid_TpSetReceiveCallBack(ptr);
    

    // Assert
   TEST_ASSERT_EQUAL_INT(NULL,GLOB_pCallbackfunc1);

    // Cleanup
    GLOB_pCallbackfunc1=NULL;
}


/**
 *  @brief callback function is not NULL and global pointer is NULL, function assigns callback function address to global pointer
 * 
 */
void test_CCO_TC_UT_1416 (void)
{
    // Setup
    GLOB_pCallbackfunc1=CallbackPtrDefaultFunc;
     
    // Act
    vid_TpSetReceiveCallBack(dummyFunction1);
    

    // Assert
   TEST_ASSERT_EQUAL_INT(dummyFunction1,GLOB_pCallbackfunc1);

    // Cleanup
    GLOB_pCallbackfunc1=NULL;
}

/**
 *  @brief callback function is not NULL and global pointer is NULL, function assigns callback function address to global pointer
 * 
 */
void test_CCO_TC_UT_1417 (void)
{
    // Setup
    GLOB_pCallbackfunc1=dummyFunction2;
    // Act
    vid_TpSetReceiveCallBack(dummyFunction1);
    

    // Assert
   TEST_ASSERT_EQUAL_INT(dummyFunction2,GLOB_pCallbackfunc1);

    // Cleanup
    GLOB_pCallbackfunc1=NULL;
}

/*************************************** vid_TpManage()***************************/


/**
 *  @brief iso TP option is disabled,Reception is found
 *         then processing occurs and Data Unit is ready
 * 
 */
void test_CCO_TC_UT_1418 (void)
{
    // Setup
    /*mock*/
    cpy_array_CMockIgnore();
    vid_CanDrvSetReceiveCallPack_CMockIgnore();
    vid_CanDrvSetTransmitCallPack_CMockIgnore();

    /*call init function*/
    vid_TpInit();

    /*iso TP option is disabled*/
    GLOB_u8IsoTpOption=ISO_TP_DISABLED;
    /*Reception is found*/
    GLOB_ReceptionFlag=RECEPTION_FOUND;

    // Act
    vid_TpManage();
    

    // Assert
   TEST_ASSERT_EQUAL_INT(DATA_UNIT_READY,GLOB_DataUnitReadyFlag);

    // Cleanup
    GLOB_u8IsoTpOption=ISO_TP_DISABLED;
    GLOB_ReceptionFlag=NO_DATA_UNIT;
}


/**
 *  @brief iso TP option is disabled,Reception not found
 *         then no processing , no data Unit ready
 * 
 */
void test_CCO_TC_UT_1419 (void)
{
    // Setup

     /*mock*/
    cpy_array_CMockIgnore();
    vid_CanDrvSetReceiveCallPack_CMockIgnore();
    vid_CanDrvSetTransmitCallPack_CMockIgnore();

    /*call init function*/
    vid_TpInit();

    /*iso TP option is disabled*/
    GLOB_u8IsoTpOption=ISO_TP_DISABLED;
    /*Reception is found*/
    GLOB_ReceptionFlag=NO_DATA_UNIT;


    // Act
    vid_TpManage();
    

    // Assert
   TEST_ASSERT_EQUAL_INT(NO_DATA_UNIT,GLOB_DataUnitReadyFlag);

    // Cleanup
    GLOB_u8IsoTpOption=ISO_TP_DISABLED;
    GLOB_ReceptionFlag=NO_DATA_UNIT;
}


    /**
 *  @brief iso TP option is disabled,Reception not found
 *         then no processing , no data Unit ready
 * 
 */
void test_CCO_TC_UT_1420 (void)
{
    // Setup

     /*mock*/
    cpy_array_CMockIgnore();
    vid_CanDrvSetReceiveCallPack_CMockIgnore();
    vid_CanDrvSetTransmitCallPack_CMockIgnore();

    /*call init function*/
    vid_TpInit();

    /*iso TP option is disabled*/
    GLOB_u8IsoTpOption=ISO_TP_ENABLED;
    /*Reception is found*/
    GLOB_ReceptionFlag=RECEPTION_FOUND;
    
    GLOB_ReceivedCanFrame.data[DATA_PAYLOAD_BYTE0_INDEX]=SINGLE_FRAME_VALUE;

    // Act
    vid_TpManage();
    

    // Assert
   TEST_ASSERT_EQUAL_INT(DATA_UNIT_READY,GLOB_DataUnitReadyFlag);

    // Cleanup
    GLOB_u8IsoTpOption=ISO_TP_DISABLED;
    GLOB_ReceptionFlag=NO_DATA_UNIT;
}



/**
 *  @brief default case of the switch case, iso TP option is unknown value, Reception found
 *         then no processing , no data Unit ready
 * 
 */
void test_CCO_TC_UT_1421 (void)
{
    // Setup

     /*mock*/
    cpy_array_CMockIgnore();
    vid_CanDrvSetReceiveCallPack_CMockIgnore();
    vid_CanDrvSetTransmitCallPack_CMockIgnore();

    /*call init function*/
    vid_TpInit();

    /*iso TP option is disabled*/
    GLOB_u8IsoTpOption=5;
    /*Reception is found*/
    GLOB_ReceptionFlag=RECEPTION_FOUND;

    // Act
    vid_TpManage();
    

    // Assert
   TEST_ASSERT_EQUAL_INT(NO_DATA_UNIT,GLOB_DataUnitReadyFlag);

    // Cleanup
    GLOB_u8IsoTpOption=ISO_TP_DISABLED;
    GLOB_ReceptionFlag=NO_DATA_UNIT;
}
