/*
 * dc_motor.c
 *
 *  Created on: Oct 6, 2024
 *      Author: SoO
 *
 * Module: Dc motor
 *
 *File Name: dc_motor.c
 *
 * Description: source file for the dc motor driver
 */
#include"dc_motor.h"
#include"pwm.h"
#include"gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the dc motor:
 * 1. Setup the dc motor direction by using the GPIO driver.
 * 2. write logic low on IN1 and IN2 to stop it the dc motor.
 */
void DCMotor_init(void){
	GPIO_setupPinDirection(IN1_PORT,IN1_PIN,PIN_OUTPUT);//set IN1 as output pin
	GPIO_setupPinDirection(IN2_PORT,IN2_PIN,PIN_OUTPUT);//set IN2 as output pin
	//motor stop at the beginning
	GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_LOW);
	GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_LOW);
}

/*
 * Description :
 * controlling the rotation of the motor and its speed.
 */
void DCMotor_rotate(DCMOTOR_State state,uint8 speed){
	switch(state){
	case 0:
		//rotate clock wise
		GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_HIGH);
		GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_LOW);
		break;
	case 1:
		//rotate anti clock wise
		GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_LOW);
		GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_HIGH);
		break;
	case 2:
		//stop the rotation
		GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_LOW);
		GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_LOW);
		break;

	}
	PWM_Timer0_start(speed);//the PWM controls the motor speed
}
