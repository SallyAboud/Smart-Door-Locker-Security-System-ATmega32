/*
 * buzzer.c
 *
 *  Created on: Oct 4, 2024
 *      Author: SoO
 *
 * Module: Buzzer
 *
 *File Name: buzzer.c
 *
 * Description: source file for the buzzer driver
 */

#include"buzzer.h"
#include"gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the buzzer:
 * 1. Setup the buzzer pin direction by using the GPIO driver.
 * 2. write logic low on the buzzer to turn it off.
 */
void BUZZER_init(){

	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);//set buzzer as output
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);//turn buzzer off
}

/*
 * Description :
 * Function responsible for turning on the buzzer.
 */
void BUZZER_on(){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);//turn buzzer on
}

/*
 * Description :
 * Function responsible for turning off the buzzer.
 */
void BUZZER_off(){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);//turn buzzer off
}

