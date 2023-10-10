/*
 * lcd16.c
 *
 *  Created on: AUG 14th, 2023.
 *      Author: OMAR AYMAN @ crewTeq comp.
 */


#include "lcd.h"
PRIVATE void vid_lcdEnableRwData(void)
{
	LCD_PIN_HIGH(EN_PIN);
	LCD_PIN_LOW(EN_PIN);
	s16_t LOC_s16Counter=0;
	for(;LOC_s16Counter<=1000;LOC_s16Counter++);
}

PRIVATE void vid_lcdStart4Bit(void)
{
	LCD_PORT_HIGH(Start4Bit);
	LCD_PIN_LOW(RS_PIN);
	vid_lcdEnableRwData();
}

lcdApiRet_e enum_lcdInit(const lcdConfig_t* ptr_strLcdConfigX)
{
	lcdApiRet_e LOC_enumLcdApiRet = LCD_API_RETURN_OK;
	s8_t LOC_s8Dots=0;
	s8_t LOC_s8Line=0;
	s8_t LOC_s8Mode=0;
	if(ptr_strLcdConfigX!=NULL)
	{
		if(ptr_strLcdConfigX->s8Dots==LCD_40DOTS)
		{
			LOC_s8Dots= LCD_5X8_DOTS_COMMAND;
		}
		else if(ptr_strLcdConfigX->s8Dots==LCD_50DOTS)
		{
			LOC_s8Dots= LCD_5X10_DOTS_COMMAND;
		}
		else 
		{
			LOC_enumLcdApiRet = LCD_API_RETURN_ERROR;
		}
			
		if(ptr_strLcdConfigX->s8Lines == LCD_1LINE)
		{
			LOC_s8Line=LCD_1_LINE_COMMAND;
		}
			
		else if(ptr_strLcdConfigX->s8Lines == LCD_2LINE)
		{
			LOC_s8Line=LCD_2_LINES_COMMAND;
		}
		else 
		{
			LOC_enumLcdApiRet = LCD_API_RETURN_ERROR;
		}
			
		if(ptr_strLcdConfigX->s8Mode == LCD_4BIT)
		{
			LOC_s8Mode=LCD_4BIT_MODE;
			vid_lcdStart4Bit();
		}
			
		else if(ptr_strLcdConfigX->s8Mode == LCD_8BIT)
		{
			LOC_s8Mode=LCD_8BIT_MODE;
		}
			
		else 
		{
			LOC_enumLcdApiRet = LCD_API_RETURN_ERROR;
		}

		if(LOC_enumLcdApiRet == LCD_API_RETURN_OK)
		{
			LCD_PORT_HIGH((LOC_s8Dots)|(LOC_s8Line)|(LOC_s8Mode));
			vid_lcdEnableRwData();
		}
		else
		{
			/*do nothing!*/
		}
	}
	else 
	{
		LOC_enumLcdApiRet = LCD_API_RETURN_ERROR;
	}

	return LOC_enumLcdApiRet;
}

lcdApiRet_e enum_lcdSendCommand(lcdCommand_e enumlcdCommand)
{
	lcdApiRet_e LOC_enumLcdApiRet = LCD_API_RETURN_OK;
	if(
		(enumlcdCommand == LCD_CLR_COMMAND) ||
		(enumlcdCommand == LCD_RET_HOME_COMMAND) ||
		(enumlcdCommand == LCD_DATA_OFF_COMMAND) ||
		(enumlcdCommand == LCD_CURS_OFF_COMMAND) ||
		(enumlcdCommand == LCD_BLINK_OFF_COMMAND) ||
		(enumlcdCommand == LCD_BLINK_ON_COMMAND) ||
		(enumlcdCommand == LCD_CURS_ON_DATA_OFF_COMMAND) ||
		(enumlcdCommand == LCD_DATA_ON_COMMAND) ||
		(enumlcdCommand == LCD_DATA_CURSOR_BLINKING_ALL_ON_COMMAND) ||
		(enumlcdCommand == LCD_SHIFT_CURS_L_COMMAND) ||
		(enumlcdCommand == LCD_SHIFT_DATA_R_COMMAND) ||
		(enumlcdCommand == LCD_SHIFT_CURS_R_COMMAND) ||
		(enumlcdCommand == LCD_CURSOR_POS_1ST_LINE_COMMAND) ||
		(enumlcdCommand == LCD_CURSOR_POS_2ND_LINE_COMMAND) ||
		(enumlcdCommand == LCD_SHIFT_DATA_L_COMMAND)
	)
	{
		LCD_PORT_HIGH(enumlcdCommand);
		vid_lcdEnableRwData();
	}
	else 
	{
		LOC_enumLcdApiRet = LCD_API_RETURN_ERROR;
	}
	return LOC_enumLcdApiRet;
}

lcdApiRet_e enum_lcdWriteChar(u8_t s8CharToSend)
{
	lcdApiRet_e LOC_enumLcdApiRet = LCD_API_RETURN_OK;
	if( ((s8CharToSend>=LCD_LIMIT1 ) && ( s8CharToSend <= LCD_LIMIT2))
									 ||
		((s8CharToSend>=LCD_LIMIT3) && (s8CharToSend != SPACE_CHAR))
	)
	{
		LCD_PORT_HIGH2(s8CharToSend);
		vid_lcdEnableRwData();
	}
	else 
	{
		LOC_enumLcdApiRet = LCD_API_RETURN_ERROR;
	}
	return LOC_enumLcdApiRet;
}

lcdApiRet_e enum_lcdWriteString(const s8_t *ptr_s8StringToSend)
{
	lcdApiRet_e LOC_enumLcdApiRet = LCD_API_RETURN_OK;
	if(ptr_s8StringToSend != NULL)
	{
		s16_t LOC_s16Counter =0;
		for(;ptr_s8StringToSend[LOC_s16Counter]!='\0';LOC_s16Counter++)
		{
			LCD_PORT_HIGH2(ptr_s8StringToSend[LOC_s16Counter]);
			vid_lcdEnableRwData();
		}
	}
	else 
	{
		LOC_enumLcdApiRet = LCD_API_RETURN_ERROR;
	}
	return LOC_enumLcdApiRet;
}


lcdApiRet_e enum_lcdSetCursorPosition(u8_t u8Line,u8_t u8_cursorPosition)
{
   lcdApiRet_e LOC_enumLcdApiRet = LCD_API_RETURN_OK;
   if((u8Line == LCD_1LINE) && ((u8_cursorPosition>=1) && (u8_cursorPosition<=16)) )
   {
        enum_lcdSendCommand(LCD_CURSOR_POS_1ST_LINE_COMMAND);
		for(u8_t LOC_u8Counter = 0;LOC_u8Counter<u8_cursorPosition;LOC_u8Counter++)
   		{
        	enum_lcdSendCommand(LCD_SHIFT_CURS_R_COMMAND);
   		}
   }
   else if((u8Line == LCD_2LINE) && ((u8_cursorPosition>=1) && (u8_cursorPosition<=16)) )
   {
        enum_lcdSendCommand(LCD_CURSOR_POS_2ND_LINE_COMMAND);
		for(u8_t LOC_u8Counter = 0;LOC_u8Counter<u8_cursorPosition;LOC_u8Counter++)
   		{
        	enum_lcdSendCommand(LCD_SHIFT_CURS_R_COMMAND);
   		}
   }
   else 
   {
         LOC_enumLcdApiRet = LCD_API_RETURN_ERROR;
   }


   return LOC_enumLcdApiRet;

}
