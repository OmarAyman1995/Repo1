#include "LEDDriver.h"
#include "LEDDriverCnfg.h"
#include "mock_GPIO.h"
#include "mock_CmsisAbstract.h"
#include "unity.h"


extern LedConfig_t GLOB_StrPowerLedConfig;         
extern LedConfig_t GLOB_StrIndicatorLedConfig;       
extern u32_t GLOB_u16PowerLedStateTimeCounter;           
extern u32_t GLOB_u16PowerLedToggleTimeCount;          
extern u32_t GLOB_u16IndicatorLedStateTimeCounter;    
extern u32_t GLOB_u16IndicatorLedToggleTimeCount;     



extern LedDrvErrorState_e enum_RefreshPowerLedState(const LedConfig_t *desiredConfig);
extern LedDrvErrorState_e enum_RefreshIndicatorLedState(const LedConfig_t *desiredConfig);

extern LedDrvErrorState_e enum_PowerLedHandle(const LedConfig_t *LedConfig);
extern LedDrvErrorState_e enum_IndicatorLedHandle(const LedConfig_t *LedConfig);



/*______________________________________________enum_RefreshIndicatorLedState()___________________________*/
/*______________________________________________________________________________________________*/
/// @brief GPIO returns OK, LED State is Valid,  API return Ok
void test_CCO_TC_UT_0131(void)
{
   
   // Setup
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_ON};
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);


  
    // Act
    ReturnValue=enum_RefreshIndicatorLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);

 
    // Cleanup
 
}

/*______________________________________________________________________________________________*/
/// @brief GPIO returns not OK, LED State is Valid,  API return Failed
void test_CCO_TC_UT_0132(void)
{
   
   // Setup
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_ON};
   enum_GpioWritePin_CMockIgnoreAndReturn(1,NOT_VALID_GPIO);


  
    // Act
    ReturnValue=enum_RefreshIndicatorLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);

 
    // Cleanup
 
}

/*______________________________________________________________________________________________*/
/// @brief GPIO returns not OK, LED State is Valid,  API return Failed
void test_CCO_TC_UT_0133(void)
{
   
   // Setup
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_OFF};
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);


  
    // Act
    ReturnValue=enum_RefreshIndicatorLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);

 
    // Cleanup
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns OK, LED State is Valid, Toggle period is reached, API return Success and Toggle count is reset
void test_CCO_TC_UT_0134(void)
{
   
   // Setup
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_TOGGLE,
                         .u16TogglePeriod=500};
   enum_GpioTogglePin_CMockIgnoreAndReturn(1,VALID_GPIO);
   GLOB_u16IndicatorLedToggleTimeCount=500;


  
    // Act
    ReturnValue=enum_RefreshIndicatorLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(0,GLOB_u16IndicatorLedToggleTimeCount);
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);

 
    // Cleanup
    GLOB_u16IndicatorLedToggleTimeCount=0;
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns OK, LED State is Valid, Toggle period is not reached, API return Success and Toggle count is incremented 
void test_CCO_TC_UT_0135(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_TOGGLE,
                         .u16TogglePeriod=500};
   GLOB_u16IndicatorLedToggleTimeCount=250;


  
    // Act
    ReturnValue=enum_RefreshIndicatorLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(250+LED_MANAGE_PERIODICITY,GLOB_u16IndicatorLedToggleTimeCount);
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);

 
    // Cleanup
    GLOB_u16IndicatorLedToggleTimeCount=0;
}


/*______________________________________________________________________________________________*/
/// @brief testing default case in the switch case - GPIO returns OK, LED State is not valid, API returns failed 
void test_CCO_TC_UT_0143(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=600,};


  
    // Act
    ReturnValue=enum_RefreshIndicatorLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);

 
    // Cleanup

}



/*______________________________________________enum_RefreshPowerLedState()___________________________*/
/*______________________________________________________________________________________________*/
/// @brief GPIO returns OK, LED State is Valid,  API return Ok
void test_CCO_TC_UT_0136(void)
{
   
   // Setup
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_ON};
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);


  
    // Act
    ReturnValue=enum_RefreshPowerLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);

 
    // Cleanup
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns not OK, LED State is Valid,  API return Failed
void test_CCO_TC_UT_0137(void)
{
   
   // Setup
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_ON};
   enum_GpioWritePin_CMockIgnoreAndReturn(1,NOT_VALID_GPIO);


  
    // Act
    ReturnValue=enum_RefreshPowerLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);

 
    // Cleanup
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns not OK, LED State is Valid,  API return Failed
void test_CCO_TC_UT_0138(void)
{
   
   // Setup
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_OFF};
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);


  
    // Act
    ReturnValue=enum_RefreshPowerLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);

 
    // Cleanup
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns OK, LED State is Valid, Toggle period is reached, API return Success and Toggle count is reset
void test_CCO_TC_UT_0139(void)
{
   
   // Setup
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_TOGGLE,
                         .u16TogglePeriod=500};
   enum_GpioTogglePin_CMockIgnoreAndReturn(1,VALID_GPIO);
   GLOB_u16PowerLedToggleTimeCount=500;


  
    // Act
    ReturnValue=enum_RefreshPowerLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(0,GLOB_u16PowerLedToggleTimeCount);
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);

 
    // Cleanup
    GLOB_u16PowerLedToggleTimeCount=0;
 
}


/*______________________________________________________________________________________________*/
/// @brief GPIO returns OK, LED State is Valid, Toggle period is not reached, API return Success and Toggle count is incremented 
void test_CCO_TC_UT_0140(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=LED_TOGGLE,
                         .u16TogglePeriod=500};
   GLOB_u16PowerLedToggleTimeCount=250;


  
    // Act
    ReturnValue=enum_RefreshPowerLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(250+LED_MANAGE_PERIODICITY,GLOB_u16PowerLedToggleTimeCount);
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);

 
    // Cleanup
    GLOB_u16PowerLedToggleTimeCount=0;
}


/*______________________________________________________________________________________________*/
/// @brief testing default case in the switch case - GPIO returns OK, LED State is not valid, API returns failed 
void test_CCO_TC_UT_0141(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={.enumState=600,};


  
    // Act
    ReturnValue=enum_RefreshPowerLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);

 
    // Cleanup

}

/*______________________________________________enum_IndicatorLedHandle()___________________________*/
/*______________________________________________________________________________________________*/
/// @brief  GPIO API return OK, enumState Time count equals enumState time in the configuration 
/// @result API return ok, counter is reset and enumState is set to off in the global configuration of Power led 
void test_CCO_TC_UT_0145(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={
    .enumState=LED_ON,
    .u16StateTime=1000};
   GLOB_u16IndicatorLedStateTimeCounter=1000;
   vid_DisableIrq_CMockIgnore();
   vid_EnableIrq_CMockIgnore();
  
    // Act
    ReturnValue=enum_IndicatorLedHandle(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);
    TEST_ASSERT_EQUAL_INT(0,GLOB_u16IndicatorLedStateTimeCounter);
    TEST_ASSERT_EQUAL_INT(LED_OFF,GLOB_StrIndicatorLedConfig.enumState); 
 
    // Cleanup
    GLOB_u16IndicatorLedStateTimeCounter=0;

}


/*______________________________________________________________________________________________*/
/// @brief  GPIO API return OK, enumState Time count doesn't equal enumState time in the configuration 
/// @result API return ok, counter is incremented
void test_CCO_TC_UT_0146(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={
    .enumState=LED_ON,
    .u16StateTime=1000};
   GLOB_u16IndicatorLedStateTimeCounter=500;
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
  
    // Act
    ReturnValue=enum_IndicatorLedHandle(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);
    TEST_ASSERT_EQUAL_INT(500+LED_MANAGE_PERIODICITY,GLOB_u16IndicatorLedStateTimeCounter);
 
    // Cleanup
   GLOB_u16IndicatorLedStateTimeCounter=0;
}


/*______________________________________________________________________________________________*/
/// @brief  GPIO API return NOK, enumState Time count doesn't equal enumState time in the configuration 
/// @result API return NOK
void test_CCO_TC_UT_0147(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={
    .enumState=LED_ON,
    .u16StateTime=1000};
   GLOB_u16IndicatorLedStateTimeCounter=500;
   enum_GpioWritePin_CMockIgnoreAndReturn(1,NOT_VALID_GPIO);
  
    // Act
    ReturnValue=enum_IndicatorLedHandle(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);
 
    // Cleanup
   GLOB_u16IndicatorLedStateTimeCounter=0;
}


/*______________________________________________enum_PowerLedHandle()___________________________*/
/*______________________________________________________________________________________________*/
/// @brief  GPIO API return OK, enumState Time count equals enumState time in the configuration 
/// @result API return ok, counter is reset and enumState is set to off in the global configuration of Power led 
void test_CCO_TC_UT_0148(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={
    .enumState=LED_ON,
    .u16StateTime=1000};
   GLOB_u16PowerLedStateTimeCounter=1000;
   vid_DisableIrq_CMockIgnore();
   vid_EnableIrq_CMockIgnore();
  
    // Act
    ReturnValue=enum_PowerLedHandle(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);
    TEST_ASSERT_EQUAL_INT(0,GLOB_u16PowerLedStateTimeCounter);
    TEST_ASSERT_EQUAL_INT(LED_OFF,GLOB_StrPowerLedConfig.enumState); 
 
    // Cleanup
    GLOB_u16PowerLedStateTimeCounter=0;

}

/*______________________________________________________________________________________________*/
/// @brief  GPIO API return OK, enumState Time count doesn't equal enumState time in the configuration 
/// @result API return ok, counter is incremented
void test_CCO_TC_UT_0149(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={
    .enumState=LED_ON,
    .u16StateTime=1000};
   GLOB_u16PowerLedStateTimeCounter=500;
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
  
    // Act
    ReturnValue=enum_PowerLedHandle(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);
    TEST_ASSERT_EQUAL_INT(500+LED_MANAGE_PERIODICITY,GLOB_u16PowerLedStateTimeCounter);
 
    // Cleanup
   GLOB_u16PowerLedStateTimeCounter=0;
}


/*______________________________________________________________________________________________*/
/// @brief  GPIO API return NOK, enumState Time count doesn't equal enumState time in the configuration 
/// @result API return NOK
void test_CCO_TC_UT_0150(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={
    .enumState=LED_ON,
    .u16StateTime=1000};
   GLOB_u16PowerLedStateTimeCounter=500;
   enum_GpioWritePin_CMockIgnoreAndReturn(1,NOT_VALID_GPIO);
  
    // Act
    ReturnValue=enum_PowerLedHandle(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);
 
    // Cleanup
   GLOB_u16PowerLedStateTimeCounter=0;
}

/*_________________________________________________enum_SetIndicatorLedState()___________________*/
/*______________________________________________________________________________________________*/
/// @brief  Input is NULL
/// @result API return NOK
void test_CCO_TC_UT_0151(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t *config=NULL;
   vid_DisableIrq_CMockIgnore();
   vid_EnableIrq_CMockIgnore();

    // Act
    ReturnValue=enum_SetIndicatorLedState(config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);
 
    // Cleanup

}


/*______________________________________________________________________________________________*/
/// @brief  Input is not NULL
/// @result API return OK
void test_CCO_TC_UT_0152(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={0};
   vid_DisableIrq_CMockIgnore();
   vid_EnableIrq_CMockIgnore();

    // Act
    ReturnValue=enum_SetIndicatorLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);
 
    // Cleanup

}

/*_________________________________________________enum_SetPowerLedState()___________________*/
/*______________________________________________________________________________________________*/
/// @brief  Input is NULL
/// @result API return NOK
void test_CCO_TC_UT_0153(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t *config=NULL;

    // Act
    ReturnValue=enum_SetPowerLedState(config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);
 
    // Cleanup

}

/*______________________________________________________________________________________________*/
/// @brief  Input is not NULL
/// @result API return OK
void test_CCO_TC_UT_0154(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config={0};
   vid_DisableIrq_CMockIgnore();
   vid_EnableIrq_CMockIgnore();

    // Act
    ReturnValue=enum_SetPowerLedState(&config);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);
 
    // Cleanup

}


/*_____________________________________enum_LedDrvInit_____________________________*/
/*______________________________________________________________________________________________*/
/// @brief  Input is NULL
/// @result API return OK
void test_CCO_TC_UT_0155(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t *config1=NULL;
   LedConfig_t config2={0};

    // Act
    ReturnValue=enum_LedDrvInit(config1,&config2);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);
 
    // Cleanup

}

/*______________________________________________________________________________________________*/
/// @brief  Input is NULL
/// @result API return OK
void test_CCO_TC_UT_0156(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config1={0};
   LedConfig_t *config2=NULL;

    // Act
    ReturnValue=enum_LedDrvInit(&config1,config2);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);
 
    // Cleanup

}

/*______________________________________________________________________________________________*/
/// @brief  Input is Not NULL
/// @result API return OK
void test_CCO_TC_UT_0157(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   LedConfig_t config1={0};
   LedConfig_t config2={0};

    // Act
    ReturnValue=enum_LedDrvInit(&config1,&config2);

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);
 
    // Cleanup

}


/*_______________________________________________________________enum_LedDrvManage()________________________*/
/*______________________________________________________________________________________________*/
/// @brief  PowerLedHandle returns error 
/// @result API return failed
void test_CCO_TC_UT_0158(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   GLOB_StrPowerLedConfig.enumState=LED_ON;
   GLOB_StrPowerLedConfig.u16StateTime=3000;

   GLOB_StrIndicatorLedConfig.enumState=LED_ON;
   GLOB_StrIndicatorLedConfig.u16StateTime=3000;

   enum_GpioWritePin_CMockIgnoreAndReturn(1,NOT_VALID_GPIO);
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
    // Act
    ReturnValue=enum_LedDrvManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);
 
    // Cleanup
    GLOB_StrPowerLedConfig.enumState=LED_ON;
   GLOB_StrPowerLedConfig.u16StateTime=0;

   GLOB_StrIndicatorLedConfig.enumState=LED_ON;
   GLOB_StrIndicatorLedConfig.u16StateTime=0;

}

/*______________________________________________________________________________________________*/
/// @brief  Indicator led handle returns error
/// @result API return failed
void test_CCO_TC_UT_0159(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   GLOB_StrPowerLedConfig.enumState=LED_ON;
   GLOB_StrPowerLedConfig.u16StateTime=3000;

   GLOB_StrIndicatorLedConfig.enumState=LED_ON;
   GLOB_StrIndicatorLedConfig.u16StateTime=3000;

   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
   enum_GpioWritePin_CMockIgnoreAndReturn(1,NOT_VALID_GPIO);
    // Act
    ReturnValue=enum_LedDrvManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_NOK,ReturnValue);
 
    // Cleanup
   GLOB_StrPowerLedConfig.enumState=LED_ON;
   GLOB_StrPowerLedConfig.u16StateTime=0;

   GLOB_StrIndicatorLedConfig.enumState=LED_ON;
   GLOB_StrIndicatorLedConfig.u16StateTime=0;

}

/*______________________________________________________________________________________________*/
/// @brief  both handle return OK
/// @result API return OK
void test_CCO_TC_UT_0160(void)
{
   
   // ___________Setup_____________
   LedDrvErrorState_e ReturnValue=0;
   GLOB_StrPowerLedConfig.enumState=LED_ON;
   GLOB_StrPowerLedConfig.u16StateTime=3000;

   GLOB_StrIndicatorLedConfig.enumState=LED_ON;
   GLOB_StrIndicatorLedConfig.u16StateTime=3000;

   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
   enum_GpioWritePin_CMockIgnoreAndReturn(1,VALID_GPIO);
    // Act
    ReturnValue=enum_LedDrvManage();

    // Assert
    TEST_ASSERT_EQUAL_INT(LED_DRV_OK,ReturnValue);
 
    // Cleanup
   GLOB_StrPowerLedConfig.enumState=LED_ON;
   GLOB_StrPowerLedConfig.u16StateTime=0;

   GLOB_StrIndicatorLedConfig.enumState=LED_ON;
   GLOB_StrIndicatorLedConfig.u16StateTime=0;

}