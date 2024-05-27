#include "BuzzerDriver.h"
#include "BuzzerDriverCnfg.h"
#include "mock_GPIO.h"
#include "mock_CmsisAbstract.h"
#include "unity.h"


extern BuzzerConfig_t GLOB_buzzerConfig;             
extern u32_t GLOB_BuzzerStateTimeCounter;           
extern u32_t GLOB_BuzzerToggleTimeCount;          


extern BuzzerDrvErrorState_e enum_RefreshBuzzerState(const BuzzerConfig_t *desiredConfig);
extern BuzzerDrvErrorState_e enum_BuzzerHandle(const BuzzerConfig_t *BuzzerConfig);


/*______________________________________________enum_RefreshBuzzerState()___________________________*/
/*______________________________________________________________________________________________*/
/// @brief GPIO returns OK, BUZZER State is Valid,  API return Ok
void test_CCO_TC_UT_0170(void)
{
   
   // Setup
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={.enumState=BUZZER_ON};
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);


  
    // Act
    ReturnValue=enum_RefreshBuzzerState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_OK,ReturnValue);

 
    // Cleanup
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns not OK, BUZZER State is Valid,  API return Failed
void test_CCO_TC_UT_0137(void)
{
   
   // Setup
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={.enumState=BUZZER_ON};
   enum_GpioWritePin_CMockIgnoreAndReturn(1,NOT_VALID_GPIO);


  
    // Act
    ReturnValue=enum_RefreshBuzzerState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_NOK,ReturnValue);

 
    // Cleanup
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns not OK, BUZZER State is Valid,  API return Failed
void test_CCO_TC_UT_0138(void)
{
   
   // Setup
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={.enumState=BUZZER_OFF};
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);


  
    // Act
    ReturnValue=enum_RefreshBuzzerState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_OK,ReturnValue);

 
    // Cleanup
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns OK, BUZZER State is Valid, Toggle period is reached, API return Success and Toggle count is reset
void test_CCO_TC_UT_0139(void)
{
   
   // Setup
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={.enumState=BUZZER_TOGGLE,
                         .u16TogglePeriod=500};
   enum_GpioTogglePin_CMockIgnoreAndReturn(1,VALID_GPIO);
   GLOB_BuzzerToggleTimeCount=500;


  
    // Act
    ReturnValue=enum_RefreshBuzzerState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(0,GLOB_BuzzerToggleTimeCount);
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_OK,ReturnValue);

 
    // Cleanup
    GLOB_BuzzerToggleTimeCount=0;
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns OK, BUZZER State is Valid, Toggle period is not reached, API return Success and Toggle count is incremented 
void test_CCO_TC_UT_0140(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={.enumState=BUZZER_TOGGLE,
                         .u16TogglePeriod=500};
   GLOB_BuzzerToggleTimeCount=250;


  
    // Act
    ReturnValue=enum_RefreshBuzzerState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(250+BUZZER_MANAGE_PERIODICITY,GLOB_BuzzerToggleTimeCount);
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_OK,ReturnValue);

 
    // Cleanup
    GLOB_BuzzerToggleTimeCount=0;
}


/*______________________________________________________________________________________________*/
/// @brief testing default case in the switch case - GPIO returns OK, BUZZER State is not valid, API returns faiBUZZER 
void test_CCO_TC_UT_0141(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={.enumState=600,};


  
    // Act
    ReturnValue=enum_RefreshBuzzerState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_NOK,ReturnValue);

 
    // Cleanup

}


/*______________________________________________enum_BuzzerHandle()___________________________*/
/*______________________________________________________________________________________________*/
/// @brief  GPIO API return OK, enumState Time count equals enumState time in the configuration 
/// @result API return ok, counter is reset and enumState is set to off in the global configuration of Power BUZZER 
void test_CCO_TC_UT_0148(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={
    .enumState=BUZZER_ON,
    .u16StateTime=1000};
   GLOB_BuzzerStateTimeCounter=1000;
   vid_DisableIrq_CMockIgnore();
   vid_EnableIrq_CMockIgnore();
  
    // Act
    ReturnValue=enum_BuzzerHandle(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_OK,ReturnValue);
    TEST_ASSERT_EQUAL_INT(0,GLOB_BuzzerStateTimeCounter);
    TEST_ASSERT_EQUAL_INT(BUZZER_OFF,GLOB_buzzerConfig.enumState); 
 
    // Cleanup
    GLOB_BuzzerStateTimeCounter=0;

}

/*______________________________________________________________________________________________*/
/// @brief  GPIO API return OK, enumState Time count doesn't equal enumState time in the configuration 
/// @result API return ok, counter is incremented
void test_CCO_TC_UT_0149(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={
    .enumState=BUZZER_ON,
    .u16StateTime=1000};
   GLOB_BuzzerStateTimeCounter=500;
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
  
    // Act
    ReturnValue=enum_BuzzerHandle(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_OK,ReturnValue);
    TEST_ASSERT_EQUAL_INT(500+BUZZER_MANAGE_PERIODICITY,GLOB_BuzzerStateTimeCounter);
 
    // Cleanup
   GLOB_BuzzerStateTimeCounter=0;
}


/*______________________________________________________________________________________________*/
/// @brief  GPIO API return NOK, enumState Time count doesn't equal enumState time in the configuration 
/// @result API return NOK
void test_CCO_TC_UT_0150(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={
    .enumState=BUZZER_ON,
    .u16StateTime=1000};
   GLOB_BuzzerStateTimeCounter=500;
   enum_GpioWritePin_CMockIgnoreAndReturn(1,NOT_VALID_GPIO);
  
    // Act
    ReturnValue=enum_BuzzerHandle(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_NOK,ReturnValue);
 
    // Cleanup
   GLOB_BuzzerStateTimeCounter=0;
}


/*_________________________________________________enum_SetBuzzerState()___________________*/
/*______________________________________________________________________________________________*/
/// @brief  Input is NULL
/// @result API return NOK
void test_CCO_TC_UT_0153(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t *config=NULL;

    // Act
    ReturnValue=enum_SetBuzzerState(config);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_NOK,ReturnValue);
 
    // Cleanup

}

/*______________________________________________________________________________________________*/
/// @brief  Input is not NULL
/// @result API return OK
void test_CCO_TC_UT_0154(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config={0};
   vid_DisableIrq_CMockIgnore();
   vid_EnableIrq_CMockIgnore();

    // Act
    ReturnValue=enum_SetBuzzerState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_OK,ReturnValue);
 
    // Cleanup

}


/*_____________________________________enum_BuzzerDrvInit_____________________________*/
/*______________________________________________________________________________________________*/
/// @brief  Input is NULL
/// @result API return OK
void test_CCO_TC_UT_0155(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t *config1=NULL;

    // Act
    ReturnValue=enum_BuzzerDrvInit(config1);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_NOK,ReturnValue);
 
    // Cleanup

}


/*______________________________________________________________________________________________*/
/// @brief  Input is Not NULL
/// @result API return OK
void test_CCO_TC_UT_0157(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   BuzzerConfig_t config1={0};

    // Act
    ReturnValue=enum_BuzzerDrvInit(&config1);

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_OK,ReturnValue);
 
    // Cleanup

}


/*_______________________________________________________________enum_BuzzerDrvManage()________________________*/
/*______________________________________________________________________________________________*/
/// @brief  PowerBUZZERHandle returns error 
/// @result API return faiBUZZER
void test_CCO_TC_UT_0158(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   GLOB_buzzerConfig.enumState=BUZZER_ON;
   GLOB_buzzerConfig.u16StateTime=3000;


   enum_GpioWritePin_CMockIgnoreAndReturn(1,NOT_VALID_GPIO);
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
    // Act
    ReturnValue=enum_BuzzerDrvManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_NOK,ReturnValue);
 
    // Cleanup
    GLOB_buzzerConfig.enumState=BUZZER_ON;
   GLOB_buzzerConfig.u16StateTime=0;


}


/*______________________________________________________________________________________________*/
/// @brief  both handle return OK
/// @result API return OK
void test_CCO_TC_UT_0160(void)
{
   
   // ___________Setup_____________
   BuzzerDrvErrorState_e ReturnValue=0;
   GLOB_buzzerConfig.enumState=BUZZER_ON;
   GLOB_buzzerConfig.u16StateTime=3000;

   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
    // Act
    ReturnValue=enum_BuzzerDrvManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(BUZZER_DRV_OK,ReturnValue);
 
    // Cleanup
   GLOB_buzzerConfig.enumState=BUZZER_ON;
   GLOB_buzzerConfig.u16StateTime=0;


}