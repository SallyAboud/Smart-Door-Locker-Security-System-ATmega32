/*
 * buzzer.h
 *
 *  Created on: Oct 4, 2024
 *      Author: SoO
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: header file for the buzzer driver
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT PORTC_ID
#define BUZZER_PIN  PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initializing the buzzer.
 */
void BUZZER_init();

/*
 * Description :
 * Function responsible for turning on the buzzer.
 */
void BUZZER_on();

/*
 * Description :
 * Function responsible for turning off the buzzer.
 */
void BUZZER_off();


#endif /* BUZZER_H_ */
