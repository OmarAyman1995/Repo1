#include "temperature_control.h"

PRIVATE s64_t s64TemperatureOnLcd = 20.0;
PRIVATE autoButtonState_e enumAutoButtonState = TEMP_AUTO_BUTTON_UNPRESSED;
PRIVATE s64_t s64_GetTemperatureFromLcd(void)
{
        return s64TemperatureOnLcd;
}

PRIVATE tempControlApiRet_e enum_SetTemperatureOnLcd(setTemperatureAction_e enumTempUpdateAction)
{
        tempControlApiRet_e retVal = TEMP_CONTROL_API_RETURN_ERROR;

        if((s64_GetTemperatureFromLcd() <40.0) && (enumTempUpdateAction == TEMP_INCREASE_WHEN_BUTTON_PRESSED))
        {
                s64TemperatureOnLcd = s64TemperatureOnLcd + 0.5;
                retVal = TEMP_CONTROL_API_RETURN_OK;
        }
        else if((s64_GetTemperatureFromLcd() >16.0) && (enumTempUpdateAction == TEMP_DECREASE_WHEN_BUTTON_PRESSED))
        {
                s64TemperatureOnLcd = s64TemperatureOnLcd - 0.5;
                retVal = TEMP_CONTROL_API_RETURN_OK;
        }
        else
        {
               
               retVal = TEMP_CONTROL_API_RETURN_ERROR;
        }
         return retVal;
}

PRIVATE void vid_UpdateLcdAfterTempControl(void)
{

        //L.................C...................D
        enum_lcdSetCursorPosition(LCD_1LINE,0);
        enum_lcdWriteString((const s8_t *)"TEMP:");

        enum_lcdSetCursorPosition(LCD_1LINE,5);
        enum_lcdWriteString(ptr_s8FloatToString(s64_GetTemperatureFromLcd(),6));

        enum_lcdSetCursorPosition(LCD_1LINE,10);
        if(enumAutoButtonState == TEMP_AUTO_BUTTON_UNPRESSED)
                enum_lcdWriteString((const s8_t *)"AUTO  ");
        else if(enumAutoButtonState == TEMP_AUTO_BUTTON_PRESSED)
                enum_lcdWriteString((const s8_t *)"MANUAL");

}

tempControlApiRet_e temperatureHandle(void)
{
        tempControlApiRet_e retVal = TEMP_CONTROL_API_RETURN_ERROR;
        keypad_buttons_e LOC_enumKeyPressed = enum_getUserRequest();
        if((LOC_enumKeyPressed == TEMPERATURE_INCREASE) ||(LOC_enumKeyPressed == TEMPERATURE_DECREASE) ||(LOC_enumKeyPressed == AUTO_CONTROL_MODE))
        {
                retVal =  TEMP_CONTROL_API_RETURN_OK;
                //check manual Or Auto
                if(enumAutoButtonState == TEMP_AUTO_BUTTON_PRESSED)
                {
                        /*Manual Mode*/
                        if(LOC_enumKeyPressed== TEMPERATURE_INCREASE) // +temp
                        {       
                                retVal = enum_SetTemperatureOnLcd(TEMP_INCREASE_WHEN_BUTTON_PRESSED);
                        }
                        else  if(LOC_enumKeyPressed == TEMPERATURE_DECREASE) // -temp
                        {
                                retVal = enum_SetTemperatureOnLcd(TEMP_DECREASE_WHEN_BUTTON_PRESSED);
                        }
                }
                else if(enumAutoButtonState == TEMP_AUTO_BUTTON_UNPRESSED)
                {
                        /*Auto Mode*/
                }
                else 
                {
                        /*do NOTHING!*/
                }

                if(LOC_enumKeyPressed == AUTO_CONTROL_MODE)
                {
                        retVal = TEMP_CONTROL_API_RETURN_OK;
                        /*switch from/To Auto Mode*/
                        if(enumAutoButtonState == TEMP_AUTO_BUTTON_UNPRESSED)
                        {
                        enumAutoButtonState = TEMP_AUTO_BUTTON_PRESSED;    
                        }
                        else if(enumAutoButtonState == TEMP_AUTO_BUTTON_PRESSED)
                        {
                        enumAutoButtonState = TEMP_AUTO_BUTTON_UNPRESSED;       
                        }
                        else 
                        {
                                /*do nothing */
                        }
                }
                else 
                {
                        /*do NOTHING!*/
                }
        }
        else 
        {
              retVal =  TEMP_CONTROL_API_RETURN_ERROR;   
        }
        vid_UpdateLcdAfterTempControl();
        return retVal;
}