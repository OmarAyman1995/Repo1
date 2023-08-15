/*
 * lcd16.h
 *
 *  Created on: AUG 14th, 2023.
 *      Author: OMAR AYMAN @ crewTeq comp.
 *
 *      #####################Instructions##################
 *		0. do NOT forget to include your MCAL GPIO Driver!
 *		1. this driver supports the 8bit mode and 4bit Mode
 *			according to this MACRO definition :
 *				#define MODE8_4 (8U)      8Bit_Mode
 *				#define MODE8_4 (4U)      4Bit_Mode
 *
 *      2. control and data pins in our PANDA board are connected as follow:
 *      (11,8)      >>> (RS,EN)
 *      (12~15)     >>> (D7~D4)
 *      	IF you want to edit this connection, you should
 *      	edit the MACROs below @LCD CNTRL connections
 * 
 *      3. data and control pins of LCD should be initialized in
 *      	push pull output mode MCU pins .
 *      	(do NOT connect them to open drain output mode MCU pins).
 * 
 *      4. change (MCAL MACROs) as your MCAL GPIO Driver!
 *
 *
 */

#ifndef SRC_LCD16_H_
#define SRC_LCD16_H_


/****************you can edit those(0,1,2,3,4) as required ***************************************/
/* 0. do NOT forget to include your MCAL GPIO Driver! here I use Stm32IDE generated driver*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

#include "standards.h"
#include "commonMacros.h"
// 1. MODE :  4 bit or 8 bit mode
#define MODE8_4 						(4U)
// 2. LCD CNTRL connections (RS,EN)
#define EN_PIN 8
#define RS_PIN 11
/* 3. (in Application layer) data and control pins of LCD should be
       initialized in push pull output mode,
       don NOT connect them to (OPEN DRAIN pins).*/
// 4. MACAL MACROs


#define TUNE(data)						(((data & 0x8000)>>3) | ((data & 0x4000)>>1) | ((data & 0x2000)<<1) | ((data & 0x1000)<<3))

#define LCD_PIN_HIGH(pin)   			HAL_GPIO_WritePin(GPIOA, 1<<pin, GPIO_PIN_SET)
#define LCD_PIN_LOW(pin)   				HAL_GPIO_WritePin(GPIOA, 1<<pin, GPIO_PIN_RESET)
#define LCD_PORT_WRITE(data)			HAL_GPIO_WritePin(GPIOB, TUNE(data), GPIO_PIN_SET)
#define LCD_PORT_RESET_8DATA()			HAL_GPIO_WritePin(GPIOB, 0xff00, GPIO_PIN_RESET)
#define LCD_PORT_RESET_4DATA()			HAL_GPIO_WritePin(GPIOB, 0xf000, GPIO_PIN_RESET)


/************************!! DO NOT EDIT ALL BELLOW !!*************************/

/*Mode selection 4 or 8 bit mode*/
#if MODE8_4 == 8
#define LCD_PORT_HIGH(data) 			 LCD_PORT_RESET_8DATA();LCD_PORT_WRITE(data);LCD_PIN_LOW(RS_PIN); LCD_PIN_LOW(RW_PIN);
#define LCD_PORT_HIGH2(data) 			 LCD_PORT_RESET_8DATA();LCD_PORT_WRITE(data);LCD_PIN_HIGH(RS_PIN); LCD_PIN_LOW(RW_PIN)
#endif

#if MODE8_4 == 4
#define LCD_PORT_HIGH(data) 			LCD_PORT_RESET_4DATA();LCD_PORT_WRITE((data<<8) & 0xf000);LCD_PIN_LOW(RS_PIN); lcd_ENABLE_R_W_DATA();LCD_PORT_RESET_4DATA();LCD_PORT_WRITE(((data)<<12));LCD_PIN_LOW(RS_PIN)
#define LCD_PORT_HIGH2(data) 			LCD_PORT_RESET_4DATA();LCD_PORT_WRITE((data<<8) & 0xf000);LCD_PIN_HIGH(RS_PIN);lcd_ENABLE_R_W_DATA();LCD_PORT_RESET_4DATA();LCD_PORT_WRITE(((data)<<12));LCD_PIN_HIGH(RS_PIN)
#endif

// these MACROs used to initialize lcdConfig_t structure at the start of the LCD initialization
#define LCD_40DOTS                                                                         8U
#define LCD_50DOTS                                                                         10U
#define LCD_4BIT                                                                           4U
#define LCD_8BIT                                                                           8U
#define LCD_1LINE                                                                          1U
#define LCD_2LINE                                                                          2U

// these Macros used internally not by the user but by the lcdInit API itself .
#define LCD_5X8_DOTS_COMMAND								       (0x20U)
#define LCD_5X10_DOTS_COMMAND								       (0x24U)
#define LCD_1_LINE_COMMAND									       (0x20U)
#define LCD_2_LINES_COMMAND									       (0x28U)
#define LCD_4BIT_MODE										(0x20U)
#define LCD_8BIT_MODE										(0x30U)


//Macros used as an index of symbolsArray in lcdWriteSpecialChar to write special symbols on lcd 
#define LCD_UP_ARROW										(0U)
#define LCD_DOWN_ARROW										(1U)
#define LCD_AUTO_ARROW										(2U)
#define LCD_COLON											(3U)
#define LCD_DECIMAL_POINT									(4U)



//user defined dataTypes
typedef struct {
				s8_t s8Dots;
				s8_t s8Lines;
				s8_t s8Mode;
}lcdConfig_t;

typedef enum{
			LCD_CLR_COMMAND=0x01U,
			LCD_RET_HOME_COMMAND=0x02U,
			LCD_DATA_OFF_COMMAND =0x08U,
			LCD_CURS_OFF_COMMAND =0x08U,
			LCD_BLINK_OFF_COMMAND=0x08U,
			LCD_BLINK_ON_COMMAND= 0x09U,
			LCD_CURS_ON_DATA_OFF_COMMAND = 0x0aU,
			LCD_DATA_ON_COMMAND = 0x0cU,
			LCD_DATA_CURSOR_BLINKING_ALL_ON_COMMAND=0x0fU,
			LCD_SHIFT_CURS_L_COMMAND=0x10U,
			LCD_SHIFT_DATA_L_COMMAND=0x18U,
			LCD_SHIFT_DATA_R_COMMAND=0x1cU,
			LCD_SHIFT_CURS_R_COMMAND=0x14U,
			LCD_CURSOR_POS_1ST_LINE_COMMAND = 0x80U,
			LCD_CURSOR_POS_2ND_LINE_COMMAND =0xc0U
}lcdCommand_e;

//this array contains the 5 symbols we need to draw them on the LCD in our project 
PUBLIC const s8_t symbolsArray[5][8];


///@brief : This function initializes LCD HAL module
///@param strLcdConfigX : It is a user defined data type to determine dots, rows,
//Cursor on/off, Blinking on/off and Data on/off and so on
void lcdInit(const lcdConfig_t* strLcdConfigX);

///@brief This function used to send a specific command to lcd to set many thing in LCD 
//such as adjust position of characters , turn cursor and blinking 
//on and off and so on.
//For more details please read HD44780 Hitachi specs.
/// @param enumlcdCommand This enumeration contains different lcd commands
void lcdSendCommand(lcdCommand_e enumlcdCommand);


/// @brief This function sends a char to lcd.
/// @param s8CharToSend ascii characters the user may want to show on lcd
void lcdWriteChar(s8_t s8CharToSend);

/// @brief This function sends a special char to lcd.
/// @param s8SpecialCharToSend Special characters the user may want to show on lcd 
// one of these 5 .
//symbolsArray[ LCD_UP_ARROW_INDEX   ]
//symbolsArray[ LCD_DOWN_ARROW_INDEX ]
//symbolsArray[ LCD_AUTO_ARROW_INDEX ]
//symbolsArray[ LCD_COLON_INDEX      ]
//symbolsArray[ LCD_DECIMAL_POINT_INDEX ]
void lcdWriteSpecialChar(const s8_t *s8SpecialCharToSend);

/// @brief This function sends a string to lcd.
/// @param s8StringToSend pointer  to string you want to show on LCD.
void lcdWriteString(const s8_t *s8StringToSend);


#endif /* SRC_LCD16_H_ */
