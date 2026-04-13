/*
 * flame.h
 *
 *  Created on: Oct 31, 2024
 *      Author: SoO
 *
 * Module: PIR
 *
 * File Name: PIR.h
 *
 * Description: header file for the PIR sensor driver
 */

#ifndef PIR_H_
#define PIR_H_
#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PIR_SENSOR_PORT  PORTC_ID
#define PIR_SENSOR_PIN   PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initializing the PIR.
 */
void PIR_init();

/*
 * Description :
 * Function responsible for getting the value of the PIR.
 */
uint8 PIR_getState();

#endif /* PIR_H_ */
