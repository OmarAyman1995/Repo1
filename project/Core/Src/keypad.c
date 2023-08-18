#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "standards.h"
#include "keypad.h"


PRIVATE u8_t u8_keyPadScan(void);
PRIVATE void vid_keypadreset(void);


/* brief: this function sets intial values for the keypad row pins to be released
this function should be called before keypad scan API in any application when using this module

 param: void
 return:  void*/ 
PRIVATE void vid_keypadreset(void)
{
    HAL_GPIO_WritePin(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID,KEYPAD_BUTTON_RELEASED);
    HAL_GPIO_WritePin(KEYPAD_ROW_PORT_ID,KEYPAD_SECOND_ROW_PIN_ID,KEYPAD_BUTTON_RELEASED);
    HAL_GPIO_WritePin(KEYPAD_ROW_PORT_ID,KEYPAD_THIRD_ROW_PIN_ID,KEYPAD_BUTTON_RELEASED);


}

PRIVATE u8_t u8_keyPadScan(void)
{
    u8_t LOC_u8buttonNum=0; /* pressed button number*/

    /*iterate on rows*/
    for(u8_t LOC_u8row=0;LOC_u8row<KEYPAD_ROWS_NUM;LOC_u8row++)
    {
  /*initalize all row pins to be released*/
    vid_keypadreset();

   switch (LOC_u8row)
   {
    case 0:
    HAL_GPIO_WritePin(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID,KEYPAD_BUTTON_PRESSED);
    break;
    case 1:
    HAL_GPIO_WritePin(KEYPAD_ROW_PORT_ID,KEYPAD_SECOND_ROW_PIN_ID,KEYPAD_BUTTON_PRESSED);
    break;
    case 2:
    HAL_GPIO_WritePin(KEYPAD_ROW_PORT_ID,KEYPAD_THIRD_ROW_PIN_ID,KEYPAD_BUTTON_PRESSED);
    break;
    case 3:
    HAL_GPIO_WritePin(KEYPAD_ROW_PORT_ID,KEYPAD_FOURTH_ROW_PIN_ID,KEYPAD_BUTTON_PRESSED);
    break;

    default:
   }

 /* check all columns */

 if( HAL_GPIO_ReadPin(KEYPAD_COL_PORT_ID,KEYPAD_COL_1_ID)==KEYPAD_BUTTON_PRESSED)
 {
HAL_Delay(DEBOUNCING_DELAY);
  if(HAL_GPIO_ReadPin(KEYPAD_COL_PORT_ID,KEYPAD_COL_1_ID)==KEYPAD_BUTTON_PRESSED)
  {
  /* assign corresponding number*/
  /*  row 1----->col 1----> (1)
      row 2----->col 1----> (4)
      row 3----->col 1----> (8)
      */
  LOC_u8buttonNum= (LOC_u8row * KEYPAD_COL_NUM )+1;
  return LOC_u8buttonNum; /*return keypad number*/

  }
 }

 else if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT_ID,KEYPAD_COL_2_ID)==KEYPAD_BUTTON_PRESSED)
 {
  HAL_Delay(DEBOUNCING_DELAY);
  if(HAL_GPIO_ReadPin(KEYPAD_COL_PORT_ID,KEYPAD_COL_2_ID)==KEYPAD_BUTTON_PRESSED)
  {
   /* assign corresponding number*/
  /*  row 1----->col 2----> (2)
      row 2----->col 2----> (5)
      row 3----->col 2----> (9)
     */
  LOC_u8buttonNum= (LOC_u8row * KEYPAD_COL_NUM)+2;
   return LOC_u8buttonNum; /*return keypad number*/
  }
 }

 else if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT_ID,KEYPAD_COL_3_ID)==KEYPAD_BUTTON_PRESSED)
 {
  HAL_Delay(DEBOUNCING_DELAY);
  if(HAL_GPIO_ReadPin(KEYPAD_COL_PORT_ID,KEYPAD_COL_3_ID)==KEYPAD_BUTTON_PRESSED)
  {
   /* assign corresponding number*/
  /*  row 1----->col 3----> (3)
      row 2----->col 3----> (7)
      row 3----->col 3----> (11)
      */
  LOC_u8buttonNum= (LOC_u8row * KEYPAD_COL_NUM )+3;
  return LOC_u8buttonNum; /*return keypad number*/
  }
 }

  }
 return LOC_u8buttonNum; /*return keypad number*/
}


keypad_buttons_e enum_getUserRequest(void)
{
  u8_t LOC_u8buttonNum;
  keypad_buttons_e LOC_enumUserRequest=0; /*user request to be returned*/
  
  LOC_u8buttonNum=u8_keyPadScan();

  switch (LOC_u8buttonNum)
    {
      /* row 1----->col 1---->1*/
      case COL_1_ROW_1:
      LOC_enumUserRequest=AIR_UP;
      break;
      /*row 2----->col 1----> (5)*/
      case COL_1_ROW_2:
      LOC_enumUserRequest=AIR_DOWN;
      break;
      /*row 3----->col 1----> (9)*/
      case COL_1_ROW_3:
      LOC_enumUserRequest=AIR_FRONT;
      break;
      /*row 2----->col 2----> (2)*/
      case COL_2_ROW_1:
      LOC_enumUserRequest= FAN_SPEED_INCREASE;
      break;
      /*row 2----->col 2----> (6)*/
      case COL_2_ROW_2:
      LOC_enumUserRequest= FAN_SPEED_DECREASE;
      break;
     /*row 2----->col 3----> (10)*/
     case COL_2_ROW_3:
     LOC_enumUserRequest= TEMPERATURE_INCREASE;
     break;
     /*row 3----->col 1----> (3)*/
     case COL_3_ROW_1:
     LOC_enumUserRequest= TEMPERATURE_DECREASE;
     break;
     /*row 3----->col 2----> (7)*/
     case COL_3_ROW_2:
     LOC_enumUserRequest= RECIRCULATION_MODE;
     break;
     /*row 3----->col 3----> (11)*/
     case COL_3_ROW_3:
     LOC_enumUserRequest= AUTO_CONTROL_MODE;
     break;

    default:
    LOC_enumUserRequest=NO_PRESS;
    }

 return LOC_enumUserRequest;
}