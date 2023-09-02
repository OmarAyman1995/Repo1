#ifndef __CONFIGURATIONS_H
#define __CONFIGURATIONS_H
/**--------------------------------   Global Includes   --------------------------------**/
#include <stdint.h>
#include <stddef.h>

/**--------------------------------   Global Configurations   --------------------------------**/
#define SELECTED_UART USART1_PERIPHERAL
#define CONF_USART_MODE INTERRUPT

#define VERSION_MAJOR (uint8_t)1
#define VERSION_MINOR (uint8_t)4
#define VERSION_PATCH (uint8_t)0

/*Our Custom Services*/
#define STARTCOM_SERVICE_ID (uint8_t)0xFD
#define ENDCOM_SERVICE_ID (uint8_t)0xFC
#define READ_SERIVCE_ID (uint8_t)80
#define READ_REGISTER_SERIVCE_ID (uint8_t)70
#define WRITE_REGISTER_SERIVCE_ID (uint8_t)60
#define WRITE_BIT_SERIVCE_ID (uint8_t)90
#define READ_GENERAL_REGISTER_ID (uint8_t)150
#define WRITE_SERIVCE_ID (uint8_t)50
#define SOFTWARERESET_SERIVCE_ID (uint8_t)40
#define UNITTESTING_SERIVCE_ID (uint8_t)120
#define STACKCONSUMPTION_SERVICE_ID (uint8_t)130
#define EXECUTIONTIME_SERIVCE_ID (uint8_t)140
#define BREAKPOINT_INFO_SERIVCE_ID (uint8_t)2
#define BREAKPOINT_CONT_SERIVCE_ID (uint8_t)1

/*Protocol Information*/
#define NUM_OF_PARMS (uint8_t)10
#define USER_MAX_PARAMETERS (uint8_t)50
#define FRAME_MAX_SIZE USER_MAX_PARAMETERS + (uint8_t)1

#define NULLPTR (void *)0

#define PUBLIC extern
#define PRIVATE static

#define INVALID 0U
#define VALID 1U

#define TRUE (uint8_t)1
#define FALSE (uint8_t)0

typedef void (*function_ptr)(void);
typedef void (*function_ptr_d)(uint8_t data);

/* Response type table */
typedef enum
{
    NEGATIVE_RESPONSE,
    POSITIVE_RESPONSE
} enumRespType_t;

#define CONF_PRIVILEGE_FLAGE_SET 1
#define CONF_PRIVILEGE_FLAGE_RESET 0

/**--------------------------------   Component Configurations   --------------------------------**/
/*____________ UserInterface ____________*/
#define CONF_MAX_CALLBACKS 30

/*____________ SessionManager ____________*/
#define CONF_MAX_PARAM_IN_ONE_FRAME 10
#define CONF_MAX_PARAM_IN_TWO_FRAMES 20
#define CONF_MAX_PARAM_IN_THREE_FRAMES 30
#define CONF_MAX_PARAM_IN_FOUR_FRAMES 40
#define CONF_MAX_PARAM_IN_FIVE_FRAMES 50

/*____________ Parser ____________*/
#define CONF_IDX_SERVICEID 0
#define CONF_SERVICE_ERR 247

/*____________ Responder ____________*/
#define CONF_IDS_SIZE 11

/*____________ ServiceHandler ____________*/
#define MAX_SERVICES_NUM (uint8_t)20

/*____________ Breakpoint ____________*/
#define CONF_BREAK_SET 1
#define CONF_BREAK_NOTSET 0
#define CONF_BRKNAME_SIZE 20

/*____________ COMAdapter ____________*/

/*____________ UartTp ____________*/
#define CONF_ID (uint8_t)0x67
#define CONF_TARGET_ADDRESS (uint8_t)0x78
#define CONF_EOF (uint8_t)0x24
#define CONF_FRAME_SIZE (uint8_t)16
#define CONF_ID_INDEX (uint8_t)0
#define CONF_TARGET_ADDRESS_INDEX (uint8_t)1
#define CONF_SERVICE_ID_INDEX (uint8_t)2
#define CONF_FRAME_CONTROL_INDEX (uint8_t)3
#define CONF_PARM10_INDEX (uint8_t)13
#define CONF_CRC_IDEX (uint8_t)14
#define CONF_EOF_INDEX (uint8_t)15
#define CONF_THE_FIRST_FOUR_INDEXES (uint8_t)4
#define CONF_RESPONSE_TYPE_INDEX (uint8_t)3
#define CONF_SIZE_OF_U8BUFFERTP (uint8_t)100
#define CONF_SIZE_OF_u8READYBUFFERTP (uint8_t)55
#define CONF_FRAME_CONTROL_CONTINUE (uint8_t)1
#define CONF_FRAME_CONTROL_LAST_FRAME (uint8_t)0

/*____________ UartDriver ____________*/
#define CONF_USART1_PERIPHERAL 1
#define CONF_USART2_PERIPHERAL 2
#define CONF_USART3_PERIPHERAL 3
#define CONF_INTERRUPT 0
#define CONF_POLLING 1

/*____________ MemoryAccess ____________*/

/*____________ TimerDriver ____________*/
#define CONF_TIMER_PRES 8
#define CONF_TIMER_TOP 65000
#define CONF_TIMER_CHANNEL TIM_CHANNEL_1
#define CONF_TIMER_NUMBER TIM1

/*____________ CrewServices ____________*/
#define CONF_STACK_PATTERN (uint32_t)0xAB
#define CONF_STACK_PATTERN_FOURBYTES (uint32_t)0xABABABAB
#define CONF_ADDRESS_PARAMS (int8_t)8
#define CONF_DATA_SIZE_INDEX (uint8_t)8
#define CONF_THE_FIRST_PARM_INDEX (uint8_t)0
#define CONF_THE_SEC_PARM_INDEX (uint8_t)1
#define CONF_THE_THIRD_PARM_INDEX (uint8_t)2

#define CONF_VECT_KEY 0x5FAUL
#define CONF_VECT_KEY_POS 16UL
#define CONF_SOFTWARE_RESET_BIT_POS 2UL
#define CONF_HEX_CONVERT_VALUE 9
#define CONF_PERCENTAGE_VALUE 100
#define CONF_ELEMENT_SIZE (uint32_t)4
#define CONF_INDEX_ZERO 0
#define CONF_INDEX_ONE 1
#define CONF_INDEX_TWO 2

#define CONF_FIRST_BYTE 0
#define CONF_SECOND_BYTE 1
#define CONF_THIRD_BYTE 2
#define CONF_FOURTH_BYTE 3

/*____________ Services ____________*/
#define CONF_ZERO_CHAR '0'
#define CONF_NINE_CHAR '9'
#define CONF_HEX_BASE (uint8_t)16
#define CONF_DECIMAL_BASE (uint8_t)10
#define CONF_ASCII_DIGIT_OFFSET (uint8_t)48
#define CONF_ASCII_HEX_OFFSET (uint8_t)55
#define CONF_MAX_VALUE (uint8_t)87

/**--------------------------------   Hardware Configurations   --------------------------------**/
/*____________    NVIC configuration   ____________*/
#define NVIC_ISER0_REG ((volatile uint32_t *)(0xE000E100))
#define NVIC_ISPR0_REG ((volatile uint32_t *)(0xE000E200))

/*AFIO register MAPR  */
#define AFIO_MAPR_REG (*(volatile uint32_t *)(0x40010000 + 0x04))
#define AFIO_MAPR_REG_BIT2_USART1_REMAP 2

/*____________   RCC configuration   ____________*/
#define RCC_BASE_ADDR 0x40021000
#define RCC_APB2ENR_REG (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x18))
#define RCC_AHBENR_REG (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x14))
#define RCC_AHB1ENR_REG (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x1C))

/*APB2 peripheral clock enable register*/
#define RCC_APB2ENR_REG_BIT2_IOPAEN 2
#define RCC_APB2ENR_REG_BIT3_IOPBEN 3
#define RCC_APB2ENR_REG_BIT4_IOPCEN 4
#define RCC_APB2ENR_REG_BIT5_IOPDEN 5
#define RCC_APB2ENR_REG_BIT6_IOPEEN 6
#define RCC_APB2ENR_REG_BIT7_IOPFEN 7
#define RCC_APB2ENR_REG_BIT8_IOPGEN 8
#define RCC_APB2ENR_REG_BIT9_ADC1EN 9
#define RCC_APB2ENR_REG_BIT10_ADC2EN 10
#define RCC_APB2ENR_REG_BIT11_TIM1EN 11
#define RCC_APB2ENR_REG_BIT12_SPI1EN 12
#define RCC_APB2ENR_REG_BIT13_TIM8EN 13
#define RCC_APB2ENR_REG_BIT14_USART1EN 14
#define RCC_APB2ENR_REG_BIT15_ADC3EN 15
#define RCC_APB2ENR_REG_BIT19_TIM9EN 19
#define RCC_APB2ENR_REG_BIT20_TIM10EN 20
#define RCC_APB2ENR_REG_BIT21_TIM11EN 21

/*APB1 peripheral clock enable register*/
#define RCC_APB1ENR_REG_BIT0_TIM2EN 0
#define RCC_APB1ENR_REG_BIT1_TIM3EN 1
#define RCC_APB1ENR_REG_BIT2_TIM4EN 2
#define RCC_APB1ENR_REG_BIT3_TIM5EN 3
#define RCC_APB1ENR_REG_BIT4_TIM6EN 4
#define RCC_APB1ENR_REG_BIT5_TIM7EN 5
#define RCC_APB1ENR_REG_BIT6_TIM12EN 6
#define RCC_APB1ENR_REG_BIT7_TIM13EN 7
#define RCC_APB1ENR_REG_BIT8_TIM14EN 8
#define RCC_APB1ENR_REG_BIT11_WWDGEN 11
#define RCC_APB1ENR_REG_BIT14_SPI2EN 14
#define RCC_APB1ENR_REG_BIT15_SPI3EN 15
#define RCC_APB1ENR_REG_BIT17_USART2EN 17
#define RCC_APB1ENR_REG_BIT18_USART3EN 18
#define RCC_APB1ENR_REG_BIT19_UART4EN 19
#define RCC_APB1ENR_REG_BIT20_UART5EN 20
#define RCC_APB1ENR_REG_BIT21_I2C1EN 21
#define RCC_APB1ENR_REG_BIT22_I2C2EN 22
#define RCC_APB1ENR_REG_BIT23_USBEN 23
#define RCC_APB1ENR_REG_BIT25_CANEN 25
#define RCC_APB1ENR_REG_BIT27_BKPEN 27
#define RCC_APB1ENR_REG_BIT28_PWREN 28
#define RCC_APB1ENR_REG_BIT29_DACEN 29

/*APB peripheral clock enable register*/
#define RCC_APBENR_REG_BIT0_DMA1EN 0
#define RCC_APBENR_REG_BIT1_DMA2EN 1
#define RCC_APBENR_REG_BIT2_SRAMEN 2
#define RCC_APBENR_REG_BIT4_FLITFEN 4
#define RCC_APBENR_REG_BIT6_CRCEN 6
#define RCC_APBENR_REG_BIT8_FSMCEN 8
#define RCC_APBENR_REG_BIT10_SDIOEN 10

#define GPIOA_CRH_REG (*(volatile uint32_t *)(0x40010800 + 0x04))

/*USART CHANNELS*/
#define USART1 ((volatile USART_t *)0x40013800)
#define USART2 ((volatile USART_t *)0x40004400)
#define USART3 ((volatile USART_t *)0x40004800)

/*USART Register Definition*/
typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_t;

/*USART SR Register BITS Definition*/
enum USART_SR_REG
{
    USART_SR_REG_BIT0_PE,
    USART_SR_REG_BIT1_FE,
    USART_SR_REG_BIT2_NE,
    USART_SR_REG_BIT3_ORE,
    USART_SR_REG_BIT4_IDLE,
    USART_SR_REG_BIT5_RXNE,
    USART_SR_REG_BIT6_TC,
    USART_SR_REG_BIT7_TXE,
    USART_SR_REG_BIT8_LBD,
    USART_SR_REG_BIT9_CTS
};
/*USART CR1 Register BITS Definition*/
enum USART_CR1_REG
{
    USART_CR1_REG_BIT0_SBK,
    USART_CR1_REG_BIT1_RWU,
    USART_CR1_REG_BIT2_RE,
    USART_CR1_REG_BIT3_TE,
    USART_CR1_REG_BIT4_IDLEIE,
    USART_CR1_REG_BIT5_RXNEIE,
    USART_CR1_REG_BIT6_TCIE,
    USART_CR1_REG_BIT7_TXEIE,
    USART_CR1_REG_BIT8_PEIE,
    USART_CR1_REG_BIT9_PS,
    USART_CR1_REG_BIT10_PCE,
    USART_CR1_REG_BIT11_WAKE,
    USART_CR1_REG_BIT12_M,
    USART_CR1_REG_BIT13_UE

};

/*USART CR2 Register BITS Definition*/
enum USART_CR2_REG
{
    USART_CR2_REG_BIT0_ADD,
    USART_CR2_REG_BIT1_ADD,
    USART_CR2_REG_BIT2_ADD,
    USART_CR2_REG_BIT3_ADD,
    USART_CR2_REG_BIT4_RESERVED,
    USART_CR2_REG_BIT5_LBDL,
    USART_CR2_REG_BIT6_LBDIE,
    USART_CR2_REG_BIT7_RESERVED,
    USART_CR2_REG_BIT8_LBCL,
    USART_CR2_REG_BIT9_CPHA,
    USART_CR2_REG_BIT10_CPOL,
    USART_CR2_REG_BIT11_CLKEN,
    USART_CR2_REG_BIT12_STOP,
    USART_CR2_REG_BIT13_STOP,
    USART_CR2_REG_BIT14_LINEN

};

/*USART CR3 Register BITS Definition */
enum USART_CR3_REG
{
    USART_CR3_REG_BIT0_EIE,
    USART_CR3_REG_BIT1_IREN,
    USART_CR3_REG_BIT2_IRLP,
    USART_CR3_REG_BIT3_HDSEL,
    USART_CR3_REG_BIT4_NACK,
    USART_CR3_REG_BIT5_SCEN,
    USART_CR3_REG_BIT6_DMAR,
    USART_CR3_REG_BIT7_DMAT,
    USART_CR3_REG_BIT8_RTSE,
    USART_CR3_REG_BIT9_CTSE,
    USART_CR3_REG_BIT10_CTSIE
};

#define SCB_AIRCR_REGISTER_ADDR (uint32_t *)0xE000ED0C

#define STARTING_OF_STACK_POINTER (uint8_t *)0x20005000 - 1
#define SIZE_OF_STACK (uint32_t)0x400

#define DBGMCU_IDCODE (*(volatile uint32_t *)(0xE0042000))
#define CPUID_REG (*(volatile uint32_t *)(0xE000ED00))
#define MASKING_DEVICDEID_CPUID 0x0F

#define STARTOFPERPHERALS (uint32_t)1073741824
#define ENDOFPERIPHERALS (uint32_t)2684358655

#define STARTOFRAM (uint32_t)536870912
#define ENDOFRAM (uint32_t)537001984

/**********************************   Build Configurations   **********************************/
#define STM
#define AVR
#define TARGET_ARCH STM

#define stm32f103
#define atmega32
#define TARGET_MCU stm32f103

// Only if TARGET_ARCH is STM or ARM
#define TARGET_CORTEX 3

#define COMPILER_PATH D:/progs/Win/ARMgnu/bin/arm-none-eabi-

#define UART 0
#define SPI 1
#define I2C 2
#define CAN 3
#define COMMUNICATION_USED UART

#define YES
#define NO
#define BUILD_WITH_OUR_DRIVER YES

#define AVR_GNU
#define ARM_GNU
#define TOOLCHAIN ARM_GNU

#endif
