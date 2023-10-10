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
#include "lcdServices.h"
// 1. MODE :  4 bit or 8 bit mode
#define MODE8_4 						(4U)
// 2. LCD CNTRL connections (RS,EN)
#define EN_PIN 							8
#define RS_PIN 							11
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
#define LCD_PORT_HIGH(data) 			LCD_PORT_RESET_4DATA();LCD_PORT_WRITE((data<<8) & 0xf000);LCD_PIN_LOW(RS_PIN); vid_lcdEnableRwData();LCD_PORT_RESET_4DATA();LCD_PORT_WRITE(((data)<<12));LCD_PIN_LOW(RS_PIN)
#define LCD_PORT_HIGH2(data) 			LCD_PORT_RESET_4DATA();LCD_PORT_WRITE((data<<8) & 0xf000);LCD_PIN_HIGH(RS_PIN);vid_lcdEnableRwData();LCD_PORT_RESET_4DATA();LCD_PORT_WRITE(((data)<<12));LCD_PIN_HIGH(RS_PIN)
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
#define LCD_4BIT_MODE											  (0x20U)
#define LCD_8BIT_MODE											  (0x30U)


//Macro used in vid_lcdStart4Bit
#define Start4Bit													(0x02U)

//Macros  of the 5 symbols we need to draw on the LCD in our project 
#define LCD_RIGHT_ARROW										(0b01111110)
#define LCD_LEFT_ARROW										(0b01111111)
#define LCD_AUTO_ARROW										(0b00111101)
#define LCD_COLON											(0b00111010)
#define LCD_DECIMAL_POINT									(0b10100101)

//Macros used for functional test
#define INITIALIZATION_ERROR 								(-1)
#define LCD_LIMIT1 											(0b00100001)
#define LCD_LIMIT2 											(0b01111111)
#define LCD_LIMIT3 												(0b10100001)
#define SPACE_CHAR 											(0b11111110)
//user defined dataTypes
typedef struct {
				s8_t s8Dots;
				s8_t s8Lines;
				s8_t s8Mode;
}lcdConfig_t;

typedef enum {
		LCD_API_RETURN_OK=1,
		LCD_API_RETURN_ERROR=-1
}lcdApiRet_e;
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




///@brief : This function initializes LCD HAL module
///@param strLcdConfigX : It is a user defined data type to determine dots, rows,
//Cursor on/off, Blinking on/off and Data on/off and so on
/// @return LCD_API_RETURN_OK "0" if the action is done proberly, 
//			else it returns LCD_API_RETURN_ERROR "-1" 
lcdApiRet_e enum_lcdInit(const lcdConfig_t* ptr_strLcdConfigX);

///@brief This function used to send a specific command to lcd to set many thing in LCD 
//such as adjust position of characters , turn cursor and blinking 
//on and off and so on.
//For more details please read HD44780 Hitachi specs.
/// @param enumlcdCommand This enumeration contains different lcd commands
/// @return LCD_API_RETURN_OK "0" if the action is done proberly, 
//			else it returns LCD_API_RETURN_ERROR "-1" 
lcdApiRet_e enum_lcdSendCommand(lcdCommand_e enumlcdCommand);


/// @brief This function sends a char to lcd.
/// @param s8CharToSend ascii characters the user may want to show on lcd
/// @return LCD_API_RETURN_OK "0" if the action is done proberly, 
//			else it returns LCD_API_RETURN_ERROR "-1" 
lcdApiRet_e enum_lcdWriteChar(u8_t s8CharToSend );


/// @brief This function sends a string to lcd.
/// @param s8StringToSend pointer  to string you want to show on LCD.
/// @return LCD_API_RETURN_OK "0" if the action is done proberly, 
//			else it returns LCD_API_RETURN_ERROR "-1" 
lcdApiRet_e enum_lcdWriteString(const s8_t *ptr_s8StringToSend);


/// @brief this function sets position of the cursor 
/// @param u8Line : LCD_1LINE or LCD_2LINE
//					else it returns LCD_API_RETURN_ERROR "-1" 
/// @param u8_cursorPosition : from 1 to 16
//							  else it returns LCD_API_RETURN_ERROR "-1" 
/// @return LCD_API_RETURN_OK "0" if the action is done proberly, 
//			else it returns LCD_API_RETURN_ERROR "-1" 
lcdApiRet_e enum_lcdSetCursorPosition(u8_t u8Line,u8_t u8_cursorPosition);

#endif /* SRC_LCD16_H_ */
