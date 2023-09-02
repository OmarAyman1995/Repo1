#include "Timer_Integration.h"
#include "app.h"
#include "timerStm32.h"

TIM_HandleTypeDef GLOB_strhtim1;
TimerX_Config_t TimerXConfig;
/**
 * @brief Initialize Timer
 *
 */
void vid_Timer_Init(void){

  TimerXConfig.TIMx = TIMER_NUMBER;
  TimerXConfig.CounterMode = TIM_COUNTERMODE_UP;
  TimerXConfig.UpdateInterruptEnable = TMRX_IRQ_EN;
  TimerXConfig.OverFolwPeriod = TIMER_TOP;
  TimerXConfig.Prescaler = TIMER_PRES;
  enum_TIMxInit(&TimerXConfig);
}


/**
 * @brief Starts Timer
 *
 */
void vid_Timer_Start(void){
    enum_TIMxStartCounting(TIMER_NUMBER);
}



/**
 * @brief Stops Timer
 *
 */
void vid_Timer_Stop(void){
   enum_TIMxStopCounting(TIMER_NUMBER);
}


/**
 * @brief Deinitialize Timer
 *
 */
void vid_Timer_DeInit(void){
    enum_TIMxDeInit(TIMER_NUMBER);
}


/**
 * @brief Get Counter Value of the Timer
 *
 * @return uint32_t Counter Value
 */
uint64_t u64_Timer_GetCounts(void){
    return u64_GetTIMxCounter(TIMER_NUMBER);
}


/**
 * @brief set counts of timer
 * 
 * @param counts 
 */
void u16_Timer_SetCounts(uint16_t counts){
    enum_SetTIMxCounter(TIMER_NUMBER,counts);
}
