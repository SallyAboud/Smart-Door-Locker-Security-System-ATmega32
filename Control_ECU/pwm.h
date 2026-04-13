/*
 * pwm.h
 *
 *  Created on: Oct 6, 2024
 *      Author: SoO
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for the pwm driver
 */

#ifndef PWM_H_
#define PWM_H_

#include"std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for controlling a motor speed.
 */
void PWM_Timer0_start(uint8 duty_cycle);


#endif /* PWM_H_ */
