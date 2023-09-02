#include "HWDepServices.h"
#include "UserInterface.h"
#include "GlobalCnfg.h"
#include "Address.h"
#include "Timer_Integration.h"


/* Location of Current UnitTesting Information in Response Parameters */
static uint8_t UnitTestingParameterIndex=0;

/* The Value of UnitTest information that will be stored in Response */
static uint8_t UnitTestInfo = 0;

/* Current Size of Parameters Added from a Service to be Sent to Tool */
extern uint8_t SizeOfParams;

/* Array of Parameters that will be Received from Tool */
extern uint8_t ServiceParamtersInRequest[USER_MAX_PARAMETERS];

/* Array of Parameters that will be sent to Tool */
extern uint8_t ServiceParametersInResponse[USER_MAX_PARAMETERS];

/* Current Response Type from a Service to be Sent to Tool */
extern volatile enumRespType_t ServiceResponseType;





/**
 * @brief we use this service to read any variable with any size
 *
 */
void Service_ReadVariable(void)
{
  uint8_t LoopOnBytes = 0;
  uint32_t RequestedAddress = 0;
  uint32_t ValueAtAddress = 0;
  uint8_t *PtrToValue = (uint8_t*)&ValueAtAddress;

  /* Address in Hex string format we need it Decimal to be Accessed */
  RequestedAddress=hextoi(ServiceParamtersInRequest);

  /* Check the address range */
  if((RequestedAddress >= STARTOFRAM) && (RequestedAddress <= ENDOFRAM))
  {
    /* Access Memory and Read Value Inside */
    ValueAtAddress = AccessMemoryRead(RequestedAddress);

    /* We got the Value from Address, now put it in Response Frame */
    for(LoopOnBytes=0 ; LoopOnBytes < ServiceParamtersInRequest[DATA_SIZE_INDEX] ; (LoopOnBytes++))
    {
      ServiceParametersInResponse[LoopOnBytes] = PtrToValue[LoopOnBytes];
    }

    /* Set Response to Positive */
    ServiceResponseType = POSITIVE_RESPONSE;
  }
  else
  {
    /* Set Response to Negative since address is Invalid */
    ServiceResponseType = NEGATIVE_RESPONSE;
  }
}


/**
 * @brief we use this service to know the version of the Library
 *
 */
void Service_GetVersion (void)
{
  /* Set Version in Parameters */
  ServiceParametersInResponse[THE_FIRST_PARM_INDEX] = VERSION_MAJOR;
  ServiceParametersInResponse[THE_SEC_PARM_INDEX] = VERSION_MINOR;
  ServiceParametersInResponse[THE_THIRD_PARM_INDEX] = VERSION_PATCH;
  /* Set Response */
  ServiceResponseType = POSITIVE_RESPONSE;
}


/**
 * @brief we will use this function to write a value in any variable
 *
 */
void Service_WriteVariable(void)
{
  uint8_t LoopOnbytes=0;
  uint32_t RequestedAddress=0;

  /* Address in Hex string format we need it Decimal to be Accessed */
  RequestedAddress=hextoi(ServiceParamtersInRequest);

  /* Check the address range */
  if((RequestedAddress >= STARTOFRAM) && (RequestedAddress <= ENDOFRAM))
  {
    /* Assign the value came from request frame to the requested address byte by byte */
    for(LoopOnbytes = 0; LoopOnbytes < ServiceParamtersInRequest[DATA_SIZE_INDEX]; (LoopOnbytes++))
    {
      AccessMemoryWrite(RequestedAddress, ServiceParamtersInRequest[ADDRESS_PARAMS+1+LoopOnbytes],LoopOnbytes);
    }

    /* Set response to Positive*/
    ServiceResponseType = POSITIVE_RESPONSE;
  }
  else
  {
    /* Set Response to Negative since address is Invalid */
    ServiceResponseType = NEGATIVE_RESPONSE;
  }
}


/**
 * @brief Put results of Unity Framework at Response Parameters to be Sent to Tool
 * 
 */
void SaveUnitTestResults(void)
{
  uint8_t testNameIndex=0;
  uint8_t lengthOfTest = (uint8_t)strlen(Unity.CurrentTestName) + 1;
  const uint8_t* const testName = (const uint8_t*)Unity.CurrentTestName;
  uint8_t testResult = (uint8_t)Unity.TestFailures;
  uint8_t allowableSpace = USER_MAX_PARAMETERS - UnitTestingParameterIndex;

  /*Check if there is space for that test in response paramaters*/
  if(lengthOfTest < allowableSpace){

    /*Save name of test to be sent in response frame*/
    while (testName[testNameIndex] != '\0'){
      ++SizeOfParams;
      ServiceParametersInResponse[UnitTestingParameterIndex] = testName[testNameIndex];
      ++testNameIndex;
      ++UnitTestingParameterIndex;
    }

    /*Save result of test to be sent in response frame*/
    if (UnitTestInfo != testResult){
      ServiceParametersInResponse[UnitTestingParameterIndex] = FALSE;
      UnitTestInfo=testResult;
    }else{
      ServiceParametersInResponse[UnitTestingParameterIndex] = TRUE;
    }

    ++UnitTestingParameterIndex;
  }
}


/**
 * @brief we will use this function to clear the value of UnitTestInfo
 */
void Unit_Testing_DeInit(void)
{
  UnitTestInfo=0;
  UnitTestingParameterIndex=0;
}




/**
 * @brief  dummy function must exist for Unity Framework
 *
 * @param c nothing
 * @return int nothing
 */
int putchar(int c) {
    /* Your custom implementation here*/

}

void __attribute__((weak)) UnitTestingEnvironment(void){
    /* User will override this function in UserConfigurations.c file*/
}
/**
 * @brief Unit Testing Service that Gets registered in CREWSPY_INIT
 * And call the unit testing function that holds all Logic of unit testing
 */
void Service_UnitTesting(void)
{
  UnitTestingEnvironment();
}




/**
 * @brief we use this service to read any peripheral register 
 */
void Service_ReadRegister(void)
{
  uint8_t  LoopOnBytes=0;
  uint32_t RequestedAddress=0;
  uint32_t ValueAtAddress = 0;
  uint8_t  *PtrToValue = (uint8_t*)&ValueAtAddress;
  
  /* Address in Hex string format we need it Decimal to be Accessed */
  RequestedAddress=hextoi(ServiceParamtersInRequest);

  /* Check the address range */
  if((RequestedAddress >= STARTOFPERPHERALS ) && (RequestedAddress <= ENDOFPERIPHERALS))
  {
    /* Access Memory and Read Value Inside */
    ValueAtAddress = AccessMemoryRead(RequestedAddress);

    /* We got the Value from Address, now put it in Response Frame */
    for(LoopOnBytes=0 ; LoopOnBytes < ServiceParamtersInRequest[DATA_SIZE_INDEX] ; (LoopOnBytes++))
    {
      ServiceParametersInResponse[LoopOnBytes] = PtrToValue[LoopOnBytes];
    }
    ServiceResponseType = POSITIVE_RESPONSE;
  }
  else
  {
    ServiceResponseType = NEGATIVE_RESPONSE;
  }
}


/**
 * @brief we will use this service to write a value in any register
 *
 */
void Service_WriteRegister(void)
{
  uint32_t RequestedAddress=0;

  /* Address in Hex string format we need it Decimal to be Accessed */
  RequestedAddress=hextoi(ServiceParamtersInRequest);

  /* Check the address range */
  if((RequestedAddress >= STARTOFPERPHERALS) && (RequestedAddress <= ENDOFPERIPHERALS))
  {
    /* We Need to Combine Requested Value in Request frame to uint32_t variable */
    uint32_t RequestedValue = ServiceParamtersInRequest[9] | (ServiceParamtersInRequest[10]<<8 | (ServiceParamtersInRequest[11])<<16 | (ServiceParamtersInRequest[12])<<24);
    
    /* Since we have the Value, Access the address and write The value inside it */
    AccessRegisterWrite(RequestedAddress, RequestedValue);
    
    ServiceResponseType = POSITIVE_RESPONSE;
  }
  else
  {
    ServiceResponseType = NEGATIVE_RESPONSE;
  }
}


/**
 * @brief service that writes a specific bit in any peripheral register
 * 
 */
void Service_WriteBit(void)
{
  uint32_t RequestedAddress=0;

  RequestedAddress=hextoi(ServiceParamtersInRequest);

  /* Check the address range */
  if((RequestedAddress >= STARTOFPERPHERALS) && (RequestedAddress <= ENDOFPERIPHERALS))
  {

    /* Get bit number and value from request frame*/
    uint8_t RequestedBitNumber = ServiceParamtersInRequest[8]; 
    uint8_t RequestedBitValue = ServiceParamtersInRequest[9];
    
    /* Access the address and write the required value in the required bit number */
    AccessBitWrite(RequestedAddress, RequestedBitNumber, RequestedBitValue);
    
    ServiceResponseType = POSITIVE_RESPONSE;
  }
  else
  {
    ServiceResponseType = NEGATIVE_RESPONSE;
  }
}
