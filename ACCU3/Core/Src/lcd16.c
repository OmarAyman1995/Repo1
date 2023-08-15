/*
 * lcd16.c
 *
 *  Created on: AUG 14th, 2023.
 *      Author: OMAR AYMAN @ crewTeq comp.
 */


#include "lcd16.h"
const s8_t symbolsArray[5][8] =
{
		{0b00100,0b01110,0b10101,0b00100,0b00100,0b00100,0b00100,0b00100},//UP Arrow
		{0b00100,0b00100,0b00100,0b00100,0b00100,0b10101,0b01110,0b00100},//DOWN Arrow
		{0b00000,0b01010,0b00100,0b01110,0b00100,0b00100,0b00100,0b00000},//Auto Arrow
		{0b00000,0b00100,0b00000,0b00000,0b00000,0b00000,0b00100,0b00000},//: COLON
		{0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00100},// . DECIMAL POINT
};
PRIVATE  void lcd_ENABLE_R_W_DATA(void)
{
	LCD_PIN_HIGH(EN_PIN);
	LCD_PIN_LOW(EN_PIN);
	s16_t LOC_s16Counter=0;
	for(;LOC_s16Counter<=1000;LOC_s16Counter++);
}

PRIVATE  void lcd_start4Bit(void)
{
	LCD_PORT_HIGH(0x02);
	LCD_PIN_LOW(RS_PIN);
	lcd_ENABLE_R_W_DATA();
}

void lcdInit(const lcdConfig_t* strLcdConfigX)
{
	s8_t LOC_s8DOTS=0;
	s8_t LOC_s8LINES=0;
	s8_t LOC_s8MODE=0;
	if(strLcdConfigX->s8Dots==8)
	{
		LOC_s8DOTS= LCD_5X8_DOTS_COMMAND;
	}
	else if(strLcdConfigX->s8Dots==10)
	{
		LOC_s8DOTS= LCD_5X10_DOTS_COMMAND;
	}
	else 
	{
		/*MISRA*/
	}
		
	if(strLcdConfigX->s8Lines == 1)
	{
		LOC_s8LINES=LCD_1_LINE_COMMAND;
	}
		
	else if(strLcdConfigX->s8Lines == 2)
	{
		LOC_s8LINES=LCD_2_LINES_COMMAND;
	}
	else 
	{
		/*MISRA*/
	}
		
	if(strLcdConfigX->s8Mode == 4)
	{
		LOC_s8MODE=LCD_4BIT_MODE;
	}
		
	else if(strLcdConfigX->s8Mode == 8)
	{
		LOC_s8MODE=LCD_8BIT_MODE;
	}
		
	else 
	{
		/*MISRA*/
	}

	if(strLcdConfigX->s8Mode==4)
	{
		lcd_start4Bit();
	}
	else 
	{
		/*MISRA*/
	}

	LCD_PORT_HIGH((LOC_s8DOTS)|(LOC_s8LINES)|(LOC_s8MODE));
	lcd_ENABLE_R_W_DATA();
}

void lcdSendCommand(lcdCommand_e enumlcdCommand)
{
	LCD_PORT_HIGH(enumlcdCommand);
	lcd_ENABLE_R_W_DATA();
}

void lcdWriteChar(s8_t s8CharToSend)
{
	LCD_PORT_HIGH2(s8CharToSend);
	lcd_ENABLE_R_W_DATA();
}

void lcdWriteSpecialChar(const s8_t *s8SpecialCharToSend)
{
	if( 
		(s8SpecialCharToSend == symbolsArray[0]) || 
	    (s8SpecialCharToSend == symbolsArray[1]) || 
		(s8SpecialCharToSend == symbolsArray[2]) ||
		(s8SpecialCharToSend == symbolsArray[3]) || 
		(s8SpecialCharToSend == symbolsArray[4])
		)

	{
		for(u8_t LOC_u8counter =0;LOC_u8counter<5;LOC_u8counter++)
		{
			lcdWriteChar(s8SpecialCharToSend[LOC_u8counter]);
		}
	}

	else 
	{
		/*MISRA*/
	}
	
}

void lcdWriteString(const s8_t *s8StringToSend)
{
	s16_t LOC_s16Counter =0;
	for(;s8StringToSend[LOC_s16Counter]!='\0';LOC_s16Counter++)
	{
		LCD_PORT_HIGH2(s8StringToSend[LOC_s16Counter]);
		lcd_ENABLE_R_W_DATA();
	}
}

