/*
 * lcd16.h
 *
 *  Created on: Nov 21, 2022
 *      Author: OMAR AYMAN
 *
 *      #####################Instructions##################
 *		0. do NOT forget to include your MCAL GPIO Driver!
 *		1. this driver supports the 8bit mode and 4bit Mode
 *			according to this MACRO definition :
 *				#define MODE8_4 (8U)      8Bit_Mode
 *				#define MODE8_4 (4U)      4Bit_Mode
 *
 *      2. you should connect pins to any port as follow:
 *      (10,9,8)  >>> (RS,RW,E)
 *      (7~0)     >>> (D7~D0)
 *      	IF you want to edit this connection, you should
 *      	edit the MACROs below (LCD connections)
 *      3. data and control pins of LCD should be initialized in
 *      	push pull output mode MCU pins .
 *      	(do NOT connect them to open drain output mode MCU pins)
 *      4. change (MCAL MACROs) as your MCAL GPIO Driver!
 *
 *
 */

#ifndef SRC_LCD16_H_
#define SRC_LCD16_H_


/****************you can edit those(0,1,2,3,4) as required ***************************************/
/* 0. do NOT forget to include your MCAL GPIO Driver!*/
#include "GPIOSTM32.h"
// 1. MODE :  4 bit or 8 bit mode
#define MODE8_4 						(8U)
// 2. LCD CNTRL connections (RS,RW,E)
#define EN_PIN 13
#define RW_PIN 14
#define RS_PIN 15
/* 3. (in Application layer) data and control pins of LCD should be
       initialized in push pull output mode,
       don NOT connect them to (OPEN DRAIN pins).*/
// 4. MACAL MACROs
#define LCD_PIN_HIGH(pin)   			GPIO_Set_Pin(GPIOC,pin)
#define LCD_PIN_LOW(pin)   				GPIO_Reset_Pin(GPIOC,pin)
#define LCD_PORT_WRITE(data)			GPIO_Set_pins(GPIOB,(data))
#define LCD_PORT_RESET_8DATA()			GPIO_Reset_pins(GPIOB,0xff)
#define LCD_PORT_RESET_4DATA()			GPIO_Reset_pins(GPIOB,0xf0)


/************************!! DO NOT EDIT ALL BELLOW !!*************************/


#if MODE8_4 == 8
#define LCD_PORT_HIGH(data) 			 LCD_PORT_RESET_8DATA();LCD_PORT_WRITE(data);LCD_PIN_LOW(RS_PIN); LCD_PIN_LOW(RW_PIN);
#define LCD_PORT_HIGH2(data) 			 LCD_PORT_RESET_8DATA();LCD_PORT_WRITE(data);LCD_PIN_HIGH(RS_PIN); LCD_PIN_LOW(RW_PIN)
#endif

#if MODE8_4 == 4
#define LCD_PORT_HIGH(data) 			LCD_PORT_RESET_4DATA();LCD_PORT_WRITE((data) & 0xf0);LCD_PIN_LOW(RS_PIN); LCD_PIN_LOW(RW_PIN);lcd_ENABLE_R_W_DATA();LCD_PORT_RESET_4DATA();LCD_PORT_WRITE((char)((data)<<4));LCD_PIN_LOW(RS_PIN); LCD_PIN_LOW(RW_PIN);
#define LCD_PORT_HIGH2(data) 			LCD_PORT_RESET_4DATA();LCD_PORT_WRITE((data) & 0xf0);LCD_PIN_HIGH(RS_PIN); LCD_PIN_LOW(RW_PIN);lcd_ENABLE_R_W_DATA();LCD_PORT_RESET_4DATA();LCD_PORT_WRITE((char)((data)<<4));LCD_PIN_HIGH(RS_PIN); LCD_PIN_LOW(RW_PIN);
#endif






//Useful MACROs
#define _40DOTS  8U
#define _50DOTS 10U
#define _4BIT    4U
#define _8BIT    8U
#define _1LINE   1U
#define _2LINE   2U

//commands
#define LCD_5X8_DOTS_COMMAND			(0x20U)
#define LCD_5X10_DOTS_COMMAND			(0x24U)
#define LCD_1_LINE_COMMAND				(0x20U)
#define LCD_2_LINES_COMMAND				(0x28U)
#define LCD_4BIT_MODE					(0x20U)
#define LCD_8BIT_MODE					(0x30U)

#define LCD_DCB_ON_COMMAND				(0x0fU)
#define LCD_CURS_ON_COMMAND				(0x0aU)
#define LCD_CURS_OFF_COMMAND			(0x08U)
#define LCD_BLINK_ON_COMMAND			(0x09U)
#define LCD_BLINK_OFF_COMMAND			(0x08U)
#define LCD_DATA_ON_COMMAND				(0x0cU)
#define LCD_DATA_OFF_COMMAND			(0x08U)

#define LCD_CLR_COMMAND					(0x01U)
#define LCD_RET_HOME_COMMAND			(0x02U)
#define LCD_SHIFT_CURS_R_COMMAND		(0x14U)
#define LCD_SHIFT_CURS_L_COMMAND		(0x10U)
#define LCD_SHIFT_DATA_R_COMMAND		(0x1cU)
#define LCD_SHIFT_DATA_L_COMMAND		(0x18U)
#define LCD_CURSOR_POS_1ST_LINE_COMMAND	(0x80U)
#define LCD_CURSOR_POS_2ND_LINE_COMMAND	(0xc0U)


//prototypes
void lcd_INIT(char dots,char lines,char mode);
void lcd_Send_Command(unsigned command);
void lcd_SET_CURSOR_POSITION(char line ,char pos);
void lcd_WRITE_CHAR(char ch);
void lcd_WRITE_TEXT(char *ch);


#endif /* SRC_LCD16_H_ */
