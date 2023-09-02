#include "HWDepServices.h"
#include "Timer_Integration.h"

/* Max Number of Callbacks user are restricted to register */
#define MAX_CALLBACKS 30

/* Current Number of Callbacks User has Registered to be Measured*/
uint8_t numberOfCallbacks = 0;

/* Invenvory that holds all Callbacks Information */
CrewServices_t InventoryOfCallbacks[30];

/* Current Size of Parameters Added from a Service to be Sent to Tool */
extern uint8_t SizeOfParams;

/* Array of Parameters that will be Received from Tool */
extern uint8_t ServiceParamtersInRequest[USER_MAX_PARAMETERS];

/* Array of Parameters that will be sent to Tool */
extern uint8_t ServiceParametersInResponse[USER_MAX_PARAMETERS];

/* Current Response Type from a Service to be Sent to Tool */
extern volatile enumRespType_t ServiceResponseType;

/* Current Response Type from a Service to be Sent to Tool */
static uint8_t isStackFilled = 0;


/**
 * @brief makes software reset of the target
 * 
 */
void Service_SoftwareReset(void)
{
  /*Write Your Code here*/
  /*System Control Block - Application Interrupt and Reset Control Register address */
  uint32_t *SCB_AIRCR =  SCB_AIRCR_REGISTER_ADDR;

  /* Disable interrupts */
  asm ("cpsid i");

  /*Ensure that all memory accesses have completed*/
  asm ("dsb 0xF":::"memory");

  /* Set the "software reset bit" in the System Reset Control Register */
  *SCB_AIRCR = (VECT_KEY << VECT_KEY_POS) | (1UL << SOFTWARE_RESET_BIT_POS);

  /*Set Response and Parameters*/
}


/**
 * @brief Determine Max Stack Usage in Percentage
 * 
 */
void Service_StackConsumption(void)
{
    uint8_t *stackPtr = (uint8_t *)STARTING_OF_STACK_POINTER;
    uint8_t *stackEnd = (STARTING_OF_STACK_POINTER - (SIZE_OF_STACK - 1));
    float maxUsage = 0;
    float maxUsagePercentage = 0;
    float maxUsagePartialPart = 0;

    if(isStackFilled != 1){
      /* Loop on all the Stack Region untill pattern is found */
      while (stackPtr >= stackEnd)
      {
          if ((STACK_PATTERN == stackPtr[FIRST_BYTE]) &&
              (STACK_PATTERN == stackPtr[SECOND_BYTE]) &&
              (STACK_PATTERN == stackPtr[THIRD_BYTE]) &&
              (STACK_PATTERN == stackPtr[FOURTH_BYTE]) )
          {
              break;
          }

          --stackPtr;
          ++maxUsage;
      }

      /* Since Pattern is Found, Calculate the Usage of Stack and Store in Response Frame */
      maxUsage -= ELEMENT_SIZE;
      maxUsagePercentage = (maxUsage * percentage_value) /SIZE_OF_STACK;
      ServiceParametersInResponse[INDEX_ZERO] = (uint8_t)maxUsagePercentage;
      ServiceParametersInResponse[INDEX_ONE] = '.';
      maxUsagePartialPart = (maxUsagePercentage - (uint32_t)maxUsagePercentage) * percentage_value;
      ServiceParametersInResponse[INDEX_TWO] = (uint8_t)maxUsagePartialPart;
      
      ServiceResponseType = POSITIVE_RESPONSE;
      
    }else{

      /* Stack not filled with the pattern */
      ServiceResponseType = NEGATIVE_RESPONSE;
    }
}



/**
 * @brief Must be Called in Startup Code to Fill all stack region with a specific Pattern
 * 
 */
void fillStackWithPattern(void) {
  /* Load the start address of the stack region*/
    uint32_t *stackEnd = ENDING_OF_STACK_POINTER;
    /* Load the size of the stack region*/
    uint32_t stackSize = 0x400;
    uint32_t i = 0;

    for ((i = 0); i < stackSize; i += ELEMENT_SIZE) { /* Loop until the entire stack region is filled*/
        if ((uint32_t)(stackEnd + (i/ELEMENT_SIZE)) >= STACK_RANGE) {
            /* Exit loop if current stack location is outside stack range*/
            break;
        }
        /* Store the pattern in the current stack location*/
        stackEnd[i/ELEMENT_SIZE] = STACK_PATTERN_FOURBYTES;
    }
    isStackFilled = 1;
}




/**
 * @brief we will use this function to calculate the execution time to any function
 */
void Service_ExecutionTime(void)
{
  volatile uint64_t u64executionTime = 0;
  volatile int8_t i = numberOfCallbacks - 1;
  volatile uint8_t indexOfParam = 0;
  volatile uint8_t sizeOfFuncName = 0;
  /* Disable interrupt */
  asm ("cpsid i" : : : "memory");
  
  ServiceParametersInResponse[indexOfParam++] = *((char*)&numberOfCallbacks);
  for(i = 0; i < numberOfCallbacks; i++){
    sizeOfFuncName = strlen(InventoryOfCallbacks[i].func_name);
    /*Check if it has a Place in Response Parameters*/
    if(indexOfParam >= (USER_MAX_PARAMETERS - sizeOfFuncName + 2 + 1) )
      break;

    /* Start timer1 */
    vid_Timer_Start();

    /* Calling the function */
    InventoryOfCallbacks[i].funcPtr();

    /* Stop timer1 */
    u64executionTime = u64_Timer_GetCounts();
    vid_Timer_Stop();

    /* Store Name of Callback*/
    /*Consists of Size of function and function name*/
    ServiceParametersInResponse[indexOfParam++] = sizeOfFuncName;
    strcpy((char*)(ServiceParametersInResponse) + indexOfParam,  (char*)InventoryOfCallbacks[i].func_name);
    indexOfParam += sizeOfFuncName;

    /* Store 2 bytes of u32executionTime as it is uint16 (max counts = 65535) */
    ServiceParametersInResponse[indexOfParam++] = *((char*)&u64executionTime);
    ServiceParametersInResponse[indexOfParam++] = *((char*)&u64executionTime + 1);

    /*Reset counter*/
    u16_Timer_SetCounts(0);
  }

  /* Enable interrupts */
  asm ("cpsie i" : : : "memory");

  ServiceResponseType = POSITIVE_RESPONSE;
  SizeOfParams = indexOfParam;
}





/**
 * @brief service that reads any general purpose register 
 * 
 */
void Service_ReadGPR(void)
{
  uint8_t NumberOfRegisterInAssembly[1] = {0};

  /* Registers in ARM: R0 - R12, Number in request frame must be 0 - 12 */
  NumberOfRegisterInAssembly[0] = ServiceParamtersInRequest[0];

  /* Get Value of Requested Register */
  uint32_t ValueOfRequestedRegister = ReadGeneralRegister(NumberOfRegisterInAssembly);

  /* Put the 4 bytes of the Value */
  ServiceParametersInResponse[0]=(uint8_t)ValueOfRequestedRegister;
  ServiceParametersInResponse[1]=(uint8_t)(ValueOfRequestedRegister>>8);
  ServiceParametersInResponse[2]=(uint8_t)(ValueOfRequestedRegister>>16);
  ServiceParametersInResponse[3]=(uint8_t)(ValueOfRequestedRegister>>24);
}