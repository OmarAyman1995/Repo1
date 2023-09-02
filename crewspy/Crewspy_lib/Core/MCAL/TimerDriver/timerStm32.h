/**
 * @file timerStm32.h
 * 
 * @author Omar Ayman (omar.ayman@crewteq.com)
 * @brief Header file of TimerX Stm32F103C8
 * @version 1.4.0
 * @date 2023-08-29
 * 
 * @copyright Copyright (crewteq.com) 2023
 * 
 */


#ifndef TIMER_STM32_H
#define TIMER_STM32_H


/*_____________________________________INCLUDES___________________________________*/
#include "stm32f103xb.h"
/*______________________________________MACROS___________________________________*/

//Timers in STM32F103C8
#define TIMER1          0U
#define TIMER2          1U
#define TIMER3          2U
#define TIMER4          3U

//CounterModes
#define UP_CNT          0x00U
#define DOWN_CNT        0x01U

//TimerIRQEnableDisable
#define TMRX_IRQ_EN      0x01U
#define TMRX_IRQ_DIS     0x00U

/*CREW TEQ naming convention ___ class type */
#define PUBLIC                          extern
#define PRIVATE                         static

#define NOT_YET                         0U
#define DONE                            1U
/*______________________________________STATIC FUNCTIONS___________________________________*/


/*______________________________________STATIC VARIABLES___________________________________*/

/*______________________________________USER DEFINED DATA TYPES___________________________________*/

typedef void(*ptrToFunction_t)(void);


typedef struct
{

  TIM_TypeDef* TIMx;                /*select timer TIM1 or TIM2 or TIM3 or TIM4*/
   

  uint8_t UpdateInterruptEnable;    /*to Enable / Disable Update Event interrupt ------- @ref: TimerIRQEnableDisable*/

  
  uint32_t Prescaler;               /*!< Specifies the prescaler value used to divide the TIM clock.
                                        from 1 to 65536 */

  uint32_t CounterMode;             /*!< Specifies the counter mode----------@ref: CounterModes */

  uint32_t OverFolwPeriod;         /*< Specifies the OverFolwPeriod value to be loaded into the active
                                     Auto-Reload Register (ARR) at the next update event.
                                      from 1 to 65536  */
  
  ptrToFunction_t callBackFunction; /*call back function called when interrupt happens*/



} TimerX_Config_t;



typedef enum
{
  returnError= 0,
  returnOk
}apisTmrRetType_t;

typedef struct 
{
  uint16_t  overFlow[4];
  uint16_t  period[4];
  uint8_t   initDone[4];
  uint8_t   startDone[4];
}timersInfo_t;

/*______________________________________APIs___________________________________*/

/// @brief this function initializes timerX module 
/// @param TimerConfigX structure contains all information about required initialization by the user
apisTmrRetType_t    enum_TIMxInit                   (const TimerX_Config_t* TimerConfigX);

/// @brief this function Deinit timerX module (disable IRQ , Disable fedded Clock to the module )
/// @param  TIMx TIM1 or TIM2 or TIM3 or TIM4
apisTmrRetType_t    enum_TIMxDeInit                 ( TIM_TypeDef* TIMx);

/// @brief this function make timerX starts counting.
/// @param  TIMx TIM1 or TIM2 or TIM3 or TIM4
apisTmrRetType_t    enum_TIMxStartCounting          ( TIM_TypeDef* TIMx);

/// @brief this function make timerX stops counting.
/// @param  TIMx TIM1 or TIM2 or TIM3 or TIM4
apisTmrRetType_t    enum_TIMxStopCounting           ( TIM_TypeDef* TIMx);

/// @brief this function returns the total counts of counter including overflows! 
/// @param  TIMx TIM1 or TIM2 or TIM3 or TIM4
/// @return the total counts of counter including overflows.
uint64_t   u64_GetTIMxCounter        ( TIM_TypeDef* TIMx);

/// @brief this function set the current value of the counter.
/// @param u16CounterUpdateVal : the new updated value assigned to CNT register.
/// @param   TIMx              : TIM1 or TIM2 or TIM3 or TIM4
apisTmrRetType_t    enum_SetTIMxCounter             ( TIM_TypeDef* TIMx,uint16_t u16CounterUpdateVal);
#endif