/**
 * @file BitsManager.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      source file of (Bits Manager) Component
 * @version    1.0.0
 * @date       2024-03-19
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*______________________INCLUDES________________________________*/
#include "BitsManager.h"
#include "GPIO.h"
/*__________________ -Macros- _________________*/

/*__________________ -Public- _________________*/
PUBLIC TIM_HandleTypeDef htim2;
PUBLIC u8_t  u8_arr_BufferSae1850[100];
/*_________________ - Privates _______________*/


/*___________________ - Implementations- _______________*/


enumRetBitsManager_e enum_BitsManagerSendHigh(u8_t u8BitsNumber)
{
    /* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    u8_t                 LOC_u8Counter  = 0;
    /*--- Actions Here!---*/
    
    if(u8BitsNumber>0)
    {
        LOC_enumRetVal = VALID_BITS_MANAGER;
        do
        {
            if(enum_TimerSetPeriod(SAE_HIGH) == NOT_VALID_TIMER)
            {
                LOC_enumRetVal = NOT_VALID_BITS_MANAGER;
                break;
            }
            LOC_u8Counter++;
        } while (LOC_u8Counter<u8BitsNumber);
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_BITS_MANAGER;
    }

    /*--- Return ---*/
    return LOC_enumRetVal ; 
}

enumRetBitsManager_e enum_BitsManagerSendLow(u8_t u8BitsNumber)
{
    /* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    u8_t                LOC_u8Counter  = 0;
    /*--- Actions Here!---*/
    if(u8BitsNumber>0)
    {
        LOC_enumRetVal = VALID_BITS_MANAGER;
        do
        {
            if(enum_TimerSetPeriod(SAE_LOW)==NOT_VALID_TIMER)
            {
                LOC_enumRetVal = NOT_VALID_BITS_MANAGER;
                break;
            }
            LOC_u8Counter++;
        } while (LOC_u8Counter<u8BitsNumber);
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_BITS_MANAGER;
    }
    

    /*--- Return ---*/
    return LOC_enumRetVal ; 
}

enumRetBitsManager_e enum_BitsManagerSendSOF(void)
{
     /* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = VALID_BITS_MANAGER;

    /*--- Actions Here!---*/
    
    /*set pin HIGH for 200us(this is the Start of frame condition according to SAE1850 protocol)*/
    if(enum_GpioWritePin(PANDA_GREEN_LED_GPIO_Port,PANDA_GREEN_LED_Pin,GPIO_PIN_SET)==VALID_GPIO)
    {
        for(u32_t i = 0;i<=1001;i++){/*----Wait some time---*/}  
        
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_BITS_MANAGER;
    }
    
    if((LOC_enumRetVal == VALID_BITS_MANAGER) && ( enum_GpioWritePin(PANDA_GREEN_LED_GPIO_Port,PANDA_GREEN_LED_Pin,GPIO_PIN_RESET)==VALID_GPIO))
    {
       /* ---- Do nothing ---- */ 
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_BITS_MANAGER;
    }
    /*--- Return ---*/
    return LOC_enumRetVal ; 
}

enumRetBitsManager_e enum_BitsManagerSendEOD(void)
{
    /* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;

    /*--- Actions Here!---*/
    
    /*turn off the timer to stop sending bits*/
    __HAL_TIM_DISABLE(&htim2);

     
    /*set pin lOW for 200us(this is the End of data condition according to SAE1850 protocol)*/
    if(enum_GpioWritePin(PANDA_GREEN_LED_GPIO_Port,PANDA_GREEN_LED_Pin,GPIO_PIN_RESET)==VALID_BITS_MANAGER)
    {
        for(u32_t i = 0;i<=1001;i++){/*----Wait some time---*/}
        LOC_enumRetVal = VALID_BITS_MANAGER;
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_BITS_MANAGER;
    }
     
    /*--- Return ---*/
    return LOC_enumRetVal ; 
}

enumRetBitsManager_e enum_BitsManagerGetBits(enumBitsManagerHL_e *enumRecBit)
{
    /* --- LOCALs ---*/
    enumRetBitsManager_e LOC_enumRetVal = UNKOWN_BITS_MANAGER;
    /*--- Actions Here!---*/
    LOC_enumRetVal = VALID_BITS_MANAGER; 
    if((enumRecBit!=NULL) && (enum_TimerWaitToGetPeriod() == VALID_TIMER))
    {
       for(u8_t u8Counter= 0 ;u8Counter<101;u8Counter++)
       {
            if(u8_arr_BufferSae1850[u8Counter] <=8 )
            {
              enumRecBit[u8Counter] =   HIGH_BIT_BITS_MANAGER;
            }
            else if (u8_arr_BufferSae1850[u8Counter] <= 17 )
            {
               enumRecBit[u8Counter] =  LOW_BIT_BITS_MANAGER ;
            }
            else if ((u8_arr_BufferSae1850[u8Counter] >=190) && (u8_arr_BufferSae1850[u8Counter]<=200))
            {
                enumRecBit[u8Counter] = SOF_BIT_BITS_MANAGER;
            }
            else 
            {
                LOC_enumRetVal = NOT_VALID_BITS_MANAGER; 
                break ; 
            }
       }
    } 
    else 
    {
        LOC_enumRetVal = NOT_VALID_BITS_MANAGER; 
    }

    /*---- Return ----*/
    return LOC_enumRetVal;
}
