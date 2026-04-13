/*
 * Timer.h
 *
 *  Created on: Nov 6, 2024
 *      Author: SoO
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	TIMER0,TIMER1,TIMER2
}Timer_ID_Type;

typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_CLOCK_ON_FALLING_EDGE,EXTERNAL_CLOCK_ON_RISING_EDGE
}Timer_ClockType;

typedef enum{
	NORMAL_MODE,COMPARE_MODE
}Timer_ModeType;

typedef struct{

	uint16 timer_initialValue;
	uint16 timer_compare_MatchValue; /*it will be used in compare mode only*/
	Timer_ID_Type timer_ID;
	Timer_ClockType timer_clock;
	Timer_ModeType timer_mode;

}Timer_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the TIMER
 */
void Timer_init(const Timer_ConfigType* Config_ptr);

/*
 * Description :
 * Functional responsible for Disabling the TIMER via Timer_ID
 */
void Timer_deinit(Timer_ID_Type timer_type);

/*
 * Description :
 * Functional responsible for set the call back function address to the required Timer.
 */
void Timer_setCallBack(void(*a_ptr)(void),Timer_ID_Type a_timer_ID);

#endif /* TIMER_H_ */
