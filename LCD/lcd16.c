/*
 * lcd16.c
 *
 *  Created on: Nov 21, 2022
 *      Author: OMAR
 */


#include "lcd16.h"

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
	LCD_PIN_LOW(RS_PIN); LCD_PIN_LOW(RW_PIN);
	lcd_ENABLE_R_W_DATA();
}

void lcd_INIT(char dots, char lines, char mode)
{
	char _DOTS=0,_LINES=0,_MODE=0;
	if(dots==8)
		_DOTS= LCD_5X8_DOTS_COMMAND;
	else if(dots==10)
		_DOTS= LCD_5X10_DOTS_COMMAND;
	if(lines == 1)
		_LINES=LCD_1_LINE_COMMAND;
	else if(lines == 2)
		_LINES=LCD_2_LINES_COMMAND;
	if(mode == 4)
		_MODE=LCD_4BIT_MODE;
	else if(mode == 8)
		_MODE=LCD_8BIT_MODE;
	if(mode==4)lcd_start4Bit();
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

void lcd_WRITE_CHAR(char ch)
{
	LCD_PORT_HIGH2(ch);
	lcd_ENABLE_R_W_DATA();
}

void lcd_WRITE_TEXT(char *ch)
{
	int i =0;
	for(;ch[i]!='\0';i++)
	{
	LCD_PORT_HIGH2(ch[i]);
	lcd_ENABLE_R_W_DATA();
	}
}

