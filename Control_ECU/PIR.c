/*
 * flame.c
 *
 *  Created on: Oct 31, 2024
 *      Author: SoO
 *
 * Module: PIR
 *
 *File Name: PIR.c
 *
 * Description: source file for the PIR Sensor driver
 */

#include"PIR.h"
#include"gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initializing the PIR.
 */
void PIR_init(){

	GPIO_setupPinDirection(PIR_SENSOR_PORT,PIR_SENSOR_PIN,PIN_INPUT);//set the PIR pin as an input

}

/*
 * Description :
 * Function responsible for getting the value of PIR.
 */
uint8 PIR_getState(){
	//return the reading of the PIR
	return GPIO_readPin(PIR_SENSOR_PORT,PIR_SENSOR_PIN);
}

