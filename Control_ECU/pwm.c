/*
 * pwm.c
 *
 *  Created on: Oct 6, 2024
 *      Author: SoO
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: source file for the pwm driver
 */

#include"pwm.h"
#include<avr/io.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for controlling a motor speed.
 */
void PWM_Timer0_start(uint8 duty_cycle){

	TCNT0=0; //Set Timer Initial value

	duty_cycle=(duty_cycle*255)/100;// to convert it from 0 to 255 as it is sent in percentage

	OCR0=duty_cycle; // Set Compare Value

	DDRB=DDRB|(1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/64 CS00=1 CS01=1 CS02=0
	 */
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01)|(1<<CS00);
}

