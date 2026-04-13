/*
 * dc_motor.h
 *
 *  Created on: Oct 6, 2024
 *      Author: SoO
 *
 * Module: Dc motor
 *
 * File Name: dc_motor.h
 *
 * Description: header file for the dc motor driver
 *
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define IN1_PORT  PORTD_ID
#define IN2_PORT  PORTD_ID
#define IN1_PIN   PIN6_ID
#define IN2_PIN   PIN7_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	CW,ACW,Stop
}DCMOTOR_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initializing the dc_motor.
 */
void DCMotor_init(void);
/*
 * Description :
 * Function responsible for rotation of the motor and its speed.
 */
void DCMotor_rotate(DCMOTOR_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */
