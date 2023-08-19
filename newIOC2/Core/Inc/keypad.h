
/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Source file for the Keypad driver
 * 
 * Author: Ahmed Bahaa
 *
 *******************************************************************************/



#ifndef KEYPAD_H_
#define KEYPAD_H_


#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "commonMacros.h"
#include "standards.h"

/* @brief Keypad static configuration
this part should be configure keypad driver based on your hardware configuration of you keypad with you MCU
*/ 

/*Keypad size*/
#define KEYPAD_ROWS_NUM 4
#define KEYPAD_COL_NUM  4

/*Rows Ports and start pin */
#define KEYPAD_ROW_PORT_ID     GPIOA           
#define KEYPAD_FIRST_ROW_PIN_ID   GPIO_PIN_4 
#define KEYPAD_SECOND_ROW_PIN_ID   GPIO_PIN_5 
#define KEYPAD_THIRD_ROW_PIN_ID   GPIO_PIN_6  
#define KEYPAD_FOURTH_ROW_PIN_ID   GPIO_PIN_7
    
/*Columns PORT and PINS*/
#define KEYPAD_COL_PORT_ID GPIOB        
#define KEYPAD_COL_1_ID    GPIO_PIN_11 
#define KEYPAD_COL_2_ID    GPIO_PIN_10  
#define KEYPAD_COL_3_ID    GPIO_PIN_1
#define KEYPAD_COL_4_ID    GPIO_PIN_0

/*Buttons matrix number*/
#define COL_1_ROW_1 1    /* Air UP Button*/
#define COL_1_ROW_2 5    /*Air Down Button*/
#define COL_1_ROW_3 9    /*Air Front*/

#define COL_2_ROW_1 2    /*Fan speed increase button*/
#define COL_2_ROW_2 6    /*Fan speed decrease button*/
#define COL_2_ROW_3 10   /*Temperature Increase button*/

#define COL_3_ROW_1 3     /*Temperature decrease button*/
#define COL_3_ROW_2 7     /*Recirculation button*/
#define COL_3_ROW_3 11    /*Auto Control Button*/



/* Keypad button wiring configurations
 if configured using pull up resistor
 Key pressed---> LOW
 Key released---> High */

#define KEYPAD_BUTTON_PRESSED            GPIO_PIN_RESET
#define KEYPAD_BUTTON_RELEASED           GPIO_PIN_SET 

#define STEP_BETWEEN_ROW_PINS             0x0010

#define DEBOUNCING_DELAY                  5


/* @brief User Keypad options*/ 

typedef enum keypad_buttons_e {
RECIRCULATION_MODE,
FAN_SPEED_INCREASE, FAN_SPEED_DECREASE,
AIR_UP,AIR_DOWN,AIR_FRONT,
TEMPERATURE_INCREASE,TEMPERATURE_DECREASE,
AUTO_CONTROL_MODE,NO_PRESS
}keypad_buttons_e;



 /*brief: this function takes a button matrix number and returns the corrsponding user request

 param: button's matrix number
 return:   an enum that represents user desired request based on the pushed key*/
 PUBLIC keypad_buttons_e enum_getUserRequest(void);





 



#endif