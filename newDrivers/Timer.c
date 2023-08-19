#include "Timer.h"


void vid_systickTimerInit(void)
{
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/10);//100ms
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	HAL_GPIO_TogglePin(LED_SYSTCK_ISR_GPIO_Port, LED_SYSTCK_ISR_Pin);
  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}