/*
 * lcd16.c
 *
 *  Created on: Nov 21, 2022
 *      Author: OMAR
 */


#include "lcd16.h"
static const char symbolsArray[8][8] =
{
		{0b00100,0b01110,0b10101,0b00100,0b00100,0b00100,0b00100,0b00100},
		{0b00100,0b00100,0b00100,0b00100,0b00100,0b10101,0b01110,0b00100},
		{0b00000,0b01010,0b00100,0b01110,0b00100,0b00100,0b00100,0b00000},
		{5,1,2,3,3,4},
		{6},
		{7},
		{8},
		{9}
};
static void lcd_ENABLE_R_W_DATA(void)
{
	LCD_PIN_HIGH(EN_PIN);
	LCD_PIN_LOW(EN_PIN);
	int i=0;
	for(;i<=1000;i++);
}

static void lcd_start4Bit(void)
{
	LCD_PORT_HIGH(0x02);
	LCD_PIN_LOW(RS_PIN);
	lcd_ENABLE_R_W_DATA();
}

void lcdInit(lcdConfig_t* lcdConfigX)
{
	char _DOTS=0,_LINES=0,_MODE=0;
	if(lcdConfigX->dots==8)
		_DOTS= LCD_5X8_DOTS_COMMAND;
	else if(lcdConfigX->dots==10)
		_DOTS= LCD_5X10_DOTS_COMMAND;
	if(lcdConfigX->lines == 1)
		_LINES=LCD_1_LINE_COMMAND;
	else if(lcdConfigX->lines == 2)
		_LINES=LCD_2_LINES_COMMAND;
	if(lcdConfigX->mode == 4)
		_MODE=LCD_4BIT_MODE;
	else if(lcdConfigX->mode == 8)
		_MODE=LCD_8BIT_MODE;
	if(lcdConfigX->mode==4)lcd_start4Bit();
	LCD_PORT_HIGH((_DOTS)|(_LINES)|(_MODE));
	lcd_ENABLE_R_W_DATA();
}

void lcd_Send_Command(unsigned command)
{
	LCD_PORT_HIGH(command);
	lcd_ENABLE_R_W_DATA();
}

void lcd_SET_CURSOR_POSITION(char line ,char pos)
{
	if(line == 1)
	{
		LCD_PORT_HIGH((LCD_CURSOR_POS_1ST_LINE_COMMAND) | (pos));
		lcd_ENABLE_R_W_DATA();
	}
	else if (line ==2)
	{
		LCD_PORT_HIGH((LCD_CURSOR_POS_2ND_LINE_COMMAND) | (pos));
		lcd_ENABLE_R_W_DATA();}
	else {}
}

void lcdWriteChar(char ch)
{
	LCD_PORT_HIGH2(ch);
	lcd_ENABLE_R_W_DATA();
}

void lcdWriteString(char *ch)
{
	int i =0;
	for(;ch[i]!='\0';i++)
	{
	LCD_PORT_HIGH2(ch[i]);
	lcd_ENABLE_R_W_DATA();
	}
}

