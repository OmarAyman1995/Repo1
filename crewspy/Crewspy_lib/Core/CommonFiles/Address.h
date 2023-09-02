#ifndef __ADDRESS_H
#define __ADDRESS_H

/****__________________________________________________  USART DRIVER  ______________________________________________________****/
/**-------------------   NVIC configuration   --------------------**/
#define NVIC_ISER0_REG				        	(  ( volatile uint32_t * ) ( 0xE000E100 ) )
#define NVIC_ISPR0_REG					        (  ( volatile uint32_t * ) ( 0xE000E200 ) )

/*AFIO register MAPR  */
#define AFIO_MAPR_REG                                 ( * ( volatile uint32_t * ) ( 0x40010000 + 0x04 ) )
#define AFIO_MAPR_REG_BIT2_USART1_REMAP               2

/**-------------------   RCC configuration   ---------------------**/
#define RCC_BASE_ADDR                                  0x40021000
#define RCC_APB2ENR_REG                                ( * ( volatile uint32_t * ) ( RCC_BASE_ADDR + 0x18 ))	
#define RCC_AHBENR_REG 	                                   ( * ( volatile  uint32_t* ) ( RCC_BASE_ADDR + 0x14 ))
#define RCC_AHB1ENR_REG                                    ( * ( volatile  uint32_t* ) ( RCC_BASE_ADDR + 0x1C ))

/*APB2 peripheral clock enable register*/
#define RCC_APB2ENR_REG_BIT2_IOPAEN                    2
#define RCC_APB2ENR_REG_BIT3_IOPBEN                    3
#define RCC_APB2ENR_REG_BIT4_IOPCEN                    4
#define RCC_APB2ENR_REG_BIT5_IOPDEN                    5
#define RCC_APB2ENR_REG_BIT6_IOPEEN                    6
#define RCC_APB2ENR_REG_BIT7_IOPFEN                    7
#define RCC_APB2ENR_REG_BIT8_IOPGEN                    8
#define RCC_APB2ENR_REG_BIT9_ADC1EN                    9                  
#define RCC_APB2ENR_REG_BIT10_ADC2EN                   10                   
#define RCC_APB2ENR_REG_BIT11_TIM1EN                   11                   
#define RCC_APB2ENR_REG_BIT12_SPI1EN                   12                   
#define RCC_APB2ENR_REG_BIT13_TIM8EN                   13                   
#define RCC_APB2ENR_REG_BIT14_USART1EN                 14                   
#define RCC_APB2ENR_REG_BIT15_ADC3EN                   15                  
#define RCC_APB2ENR_REG_BIT19_TIM9EN                   19                   
#define RCC_APB2ENR_REG_BIT20_TIM10EN                  20                   
#define RCC_APB2ENR_REG_BIT21_TIM11EN                  21                   

 /*APB1 peripheral clock enable register*/
#define RCC_APB1ENR_REG_BIT0_TIM2EN                    0                                 
#define RCC_APB1ENR_REG_BIT1_TIM3EN                    1                                 
#define RCC_APB1ENR_REG_BIT2_TIM4EN                    2                                 
#define RCC_APB1ENR_REG_BIT3_TIM5EN                    3                                 
#define RCC_APB1ENR_REG_BIT4_TIM6EN                    4                                 
#define RCC_APB1ENR_REG_BIT5_TIM7EN                    5                                 
#define RCC_APB1ENR_REG_BIT6_TIM12EN                   6                                 
#define RCC_APB1ENR_REG_BIT7_TIM13EN                   7                                 
#define RCC_APB1ENR_REG_BIT8_TIM14EN                   8                                 
#define RCC_APB1ENR_REG_BIT11_WWDGEN                   11                                 
#define RCC_APB1ENR_REG_BIT14_SPI2EN                   14                                 
#define RCC_APB1ENR_REG_BIT15_SPI3EN                   15                                 
#define RCC_APB1ENR_REG_BIT17_USART2EN                 17                                 
#define RCC_APB1ENR_REG_BIT18_USART3EN                 18                                 
#define RCC_APB1ENR_REG_BIT19_UART4EN                  19                                 
#define RCC_APB1ENR_REG_BIT20_UART5EN                  20               
#define RCC_APB1ENR_REG_BIT21_I2C1EN                   21
#define RCC_APB1ENR_REG_BIT22_I2C2EN                   22
#define RCC_APB1ENR_REG_BIT23_USBEN                    23
#define RCC_APB1ENR_REG_BIT25_CANEN                    25
#define RCC_APB1ENR_REG_BIT27_BKPEN                    27
#define RCC_APB1ENR_REG_BIT28_PWREN                    28
#define RCC_APB1ENR_REG_BIT29_DACEN                    29

 /*APB peripheral clock enable register*/
 #define RCC_APBENR_REG_BIT0_DMA1EN                    0                                 
 #define RCC_APBENR_REG_BIT1_DMA2EN                    1                                    
 #define RCC_APBENR_REG_BIT2_SRAMEN                    2                                    
 #define RCC_APBENR_REG_BIT4_FLITFEN                   4                  
 #define RCC_APBENR_REG_BIT6_CRCEN                     6                                   
 #define RCC_APBENR_REG_BIT8_FSMCEN                    8                                    
 #define RCC_APBENR_REG_BIT10_SDIOEN                   10                                   
                                 
/**-------------------   GPIO configuration   --------------------**/
#define GPIOA_CRH_REG                                  ( * ( volatile uint32_t * ) ( 0x40010800 + 0x04 ) )

/****__________________________________________________  CrewServices DRIVER  ______________________________________________________****/
#define SCB_AIRCR_REGISTER_ADDR                        (uint32_t*)0xE000ED0C
#define STACK_RANGE                                    (uint32_t)0x20004FFC

/****__________________________________________________ GlobalCnfg    ______________________________________________________****/
/* the starting of stack pointer and the stack size will be congiured by user*/
#define STARTING_OF_STACK_POINTER                      (uint8_t*)0x20004FFF
#define SIZE_OF_STACK                                  (uint32_t)0x400
#define ENDING_OF_STACK_POINTER                        (uint32_t*)0x20004C00

/****__________________________________________________ Responder  ______________________________________________________****/
#define DBGMCU_IDCODE                                  (*(volatile uint32_t*) ( 0xE0042000))
#define CPUID_REG                                      (*(volatile uint32_t*) ( 0xE000ED00))

#endif
