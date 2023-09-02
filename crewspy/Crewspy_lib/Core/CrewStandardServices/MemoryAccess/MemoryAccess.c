#include "MemoryAccess.h"



/**
 * @brief Access a Memory Address and get the value inside
 * 
 * @param address Desired Address to be Accessed
 * @return Value inside the Address 
 */
uint32_t AccessMemoryRead(uint32_t address){
    uint32_t* ptr = (uint32_t*)address;
    return *ptr;
}


/**
 * @brief Access a Memory Address and Write Single Byte Value
 * 
 * @param address Desired Address to be Accessed
 * @param value Value to be put inside the Address 
 * @param byte_number which byte value will be written at
 */
void AccessMemoryWrite(uint32_t address, uint8_t value, uint32_t byte_number){
    uint8_t* ptr = (uint8_t*)address;
    ptr[byte_number] = value;

}


/**
 * @brief function that can write in perpheral register
 * 
 * @param address takes the address of the register
 * @param value takes the value to be writen in the register.
 */
void AccessRegisterWrite(uint32_t address, uint32_t value) {
    uint32_t* ptr = (uint32_t*)address;
    *ptr = value;
}


/**
 * @brief function that can write in specific bit in peripheral register
 * 
 * @param address takes address of the register
 * @param bit_number takes the bit number that will be writen
 * @param bit_value  takes the bit value that will be writen 
 */
void AccessBitWrite(uint32_t address, uint32_t bit_number, uint32_t bit_value) {
    uint32_t* ptr = (uint32_t*)address;
    uint32_t reg_value = *ptr;
    if (bit_value != 0) {
        reg_value |= (1 << bit_number); // Set the bit to 1
    } else {
        reg_value &= ~(1 << bit_number); // Set the bit to 0
    }
    *ptr = reg_value;
}


/**
 * @brief function that read general purpose register
 * 
 * @param reg_Name refer to redisster name which will be readed 
 * @return uint32_t the value of the register 
 */
uint32_t ReadGeneralRegister(const uint8_t* reg_Name) {
    uint32_t result = 0;
    uint8_t reg_num = reg_Name[0] - '0'; // Subtract 48 to convert from ASCII to decimal

  switch (reg_num)
  {
  case 0:                           //r0 
    __asm__ volatile (
       "mov %0, r0\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 1:                         //r1
    __asm__ volatile (
       "mov %0, r1\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 2:                         //r2
    __asm__ volatile (
       "mov %0, r2\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 3:                         //r3
    __asm__ volatile (
       "mov %0, r3\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 4:                         //r4
    __asm__ volatile (
       "mov %0, r4\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 5:                         //r5
    __asm__ volatile (
       "mov %0, r5\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 6:                         //r6
    __asm__ volatile (
       "mov %0, r6\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 7:                         //r7
    __asm__ volatile (
       "mov %0, r7\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 8:                         //r8
    __asm__ volatile (
       "mov %0, r8\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 9:                         //r9
    __asm__ volatile (
       "mov %0, r9\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 10:                        //r10
    __asm__ volatile (
       "mov %0, r10\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 11:                        //r11
    __asm__ volatile (
       "mov %0, r11\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;
    case 12:                        //r12
    __asm__ volatile (
       "mov %0, r12\n"
       : "=r" (result)
       : "r" (reg_num)
    );
    break;

  
  default:
    break;
  }

    return result;
}


/**
 * @brief clock enable for all periperal
 * 
 */
void clock_Peripherals_Init(void)
{
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT2_IOPAEN);                   
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT3_IOPBEN);                  
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT4_IOPCEN);                  
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT5_IOPDEN);                  
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT6_IOPEEN);                   
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT7_IOPFEN);                  
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT8_IOPGEN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT9_ADC1EN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT10_ADC2EN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT11_TIM1EN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT12_SPI1EN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT13_TIM8EN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT14_USART1EN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT15_ADC3EN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT19_TIM9EN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT20_TIM10EN);
   SET_BIT(RCC_APB2ENR_REG,RCC_APB2ENR_REG_BIT21_TIM11EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT0_TIM2EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT1_TIM3EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT2_TIM4EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT3_TIM5EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT4_TIM6EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT5_TIM7EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT6_TIM12EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT7_TIM13EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT8_TIM14EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT11_WWDGEN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT14_SPI2EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT15_SPI3EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT17_USART2EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT18_USART3EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT19_UART4EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT20_UART5EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT21_I2C1EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT22_I2C2EN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT23_USBEN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT25_CANEN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT27_BKPEN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT28_PWREN);
   SET_BIT(RCC_AHB1ENR_REG,RCC_APB1ENR_REG_BIT29_DACEN);
   SET_BIT(RCC_AHBENR_REG,RCC_APBENR_REG_BIT0_DMA1EN);
   SET_BIT(RCC_AHBENR_REG,RCC_APBENR_REG_BIT1_DMA2EN);
   SET_BIT(RCC_AHBENR_REG,RCC_APBENR_REG_BIT2_SRAMEN);
   SET_BIT(RCC_AHBENR_REG,RCC_APBENR_REG_BIT4_FLITFEN);
   SET_BIT(RCC_AHBENR_REG,RCC_APBENR_REG_BIT6_CRCEN);
   SET_BIT(RCC_AHBENR_REG,RCC_APBENR_REG_BIT8_FSMCEN);
   SET_BIT(RCC_AHBENR_REG,RCC_APBENR_REG_BIT10_SDIOEN);
}