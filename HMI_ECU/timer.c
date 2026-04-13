/*
 * Timer1.c
 *
 *  Created on: Nov 6, 2024
 *      Author: SoO
 */

#include"timer.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include "common_macros.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_timer0Callback)(void)=NULL_PTR;
static volatile void (*g_timer1Callback)(void)=NULL_PTR;
static volatile void (*g_timer2Callback)(void)=NULL_PTR;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect){
    if (g_timer0Callback!=NULL_PTR){
        g_timer0Callback();
    }
}

ISR(TIMER0_COMP_vect){
    if (g_timer0Callback!=NULL_PTR){
        g_timer0Callback();
    }
}

ISR(TIMER1_OVF_vect){
    if (g_timer1Callback!=NULL_PTR){
        g_timer1Callback();
    }
}

ISR(TIMER1_COMPA_vect){
    if (g_timer1Callback!=NULL_PTR){
        g_timer1Callback();
    }
}

ISR(TIMER2_OVF_vect){
    if (g_timer2Callback!=NULL_PTR){
        g_timer2Callback();
    }
}

ISR(TIMER2_COMP_vect){
    if (g_timer2Callback!=NULL_PTR) {
        g_timer2Callback();
    }
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the TIMER
 */
void Timer_init(const Timer_ConfigType* Config_ptr){

	switch(Config_ptr->timer_ID){
	case TIMER0:
		TCCR0=(1<<FOC0);//non pwm mode
		TCNT0=Config_ptr->timer_initialValue;//Set Timer initial value

		//timer prescalar
		if(Config_ptr->timer_clock==NO_CLOCK){

			//do nothing as CS02:01:00 is already 000

		}

		else if(Config_ptr->timer_clock==F_CPU_CLOCK){

			TCCR0|=(1<<CS00);//CS02:01:00 is 001

		}

		else if(Config_ptr->timer_clock==F_CPU_8){

			TCCR0|=(1<<CS01);//CS02:01:00 is 010

		}

		else if(Config_ptr->timer_clock==F_CPU_64){

			TCCR0|=(1<<CS00)|(1<<CS01);//CS02:01:00 is 011

		}

		else if(Config_ptr->timer_clock==F_CPU_256){

			TCCR0|=(1<<CS02);//CS02:01:00 is 100

		}

		else if(Config_ptr->timer_clock==F_CPU_1024){

			TCCR0|=(1<<CS00)|(1<<CS02);//CS02:01:00 is 101

		}

		else if(Config_ptr->timer_clock==EXTERNAL_CLOCK_ON_FALLING_EDGE){

			TCCR0|=(1<<CS01)|(1<<CS02);//CS02:01:00 is 110

		}

		else if(Config_ptr->timer_clock==EXTERNAL_CLOCK_ON_RISING_EDGE){

			TCCR0|=(1<<CS00)|(1<<CS01)|(1<<CS02);//CS02:01:00 is 111

		}

		//timer mode
		if(Config_ptr->timer_mode==NORMAL_MODE){

			// Normal ModeWGM01=0 & WGM00=0 and they are already 00
			TIMSK|=(1<<TOIE0); // Enable Timer0 Overflow Interrupt


		}
		else if(Config_ptr->timer_mode==COMPARE_MODE){

			TIMSK|=(1<<OCIE0); // Enable Timer0 Compare Interrupt
			TCCR0|=(1<<WGM01);//CTC Mode WGM01=1 & WGM00=0
			OCR0=Config_ptr->timer_compare_MatchValue;// Set Compare Value

		}

		break;
	case TIMER1:

		TCCR1A=(1<<FOC1A);//not PWM mode
		TCNT1=Config_ptr->timer_initialValue;//Set Timer initial value

		//timer prescalar
		if(Config_ptr->timer_clock==NO_CLOCK){

			//do nothing as CS12:11:10 is already 000

		}

		else if(Config_ptr->timer_clock==F_CPU_CLOCK){

			TCCR1B|=(1<<CS10);//CS12:11:10 is 001

		}

		else if(Config_ptr->timer_clock==F_CPU_8){

			TCCR1B|=(1<<CS11);//CS12:11:10 is 010

		}

		else if(Config_ptr->timer_clock==F_CPU_64){

			TCCR1B|=(1<<CS10)|(1<<CS11);//CS12:11:10 is 011

		}

		else if(Config_ptr->timer_clock==F_CPU_256){

			TCCR1B|=(1<<CS12);//CS12:11:10 is 100

		}

		else if(Config_ptr->timer_clock==F_CPU_1024){

			TCCR1B|=(1<<CS10)|(1<<CS12);//CS12:11:10 is 101

		}

		else if(Config_ptr->timer_clock==EXTERNAL_CLOCK_ON_FALLING_EDGE){

			TCCR1B|=(1<<CS11)|(1<<CS12);//CS12:11:10 is 110

		}

		else if(Config_ptr->timer_clock==EXTERNAL_CLOCK_ON_RISING_EDGE){

			TCCR1B|=(1<<CS10)|(1<<CS11)|(1<<CS12);//CS12:11:10 is 111

		}

		//timer mode
		if(Config_ptr->timer_mode==NORMAL_MODE){

			// Normal Mode WGM13=0 & WGM12=0 &WGM11=0 & WGM10=0 and they are already 0000
			TIMSK|=(1<<TOIE1); // Enable Timer0 Overflow Interrupt

		}
		else if(Config_ptr->timer_mode==COMPARE_MODE){

			TIMSK|=(1<<OCIE1A);//timer1A output compare match interrupt enable
			TCCR1B|=(1<<WGM12);//CTC Mode
			OCR1A=Config_ptr->timer_compare_MatchValue;// Set Compare Value

		}

		break;

	case TIMER2:

		TCCR2=(1<<FOC2);//non pwm mode
		TCNT2=Config_ptr->timer_initialValue;//Set Timer initial value

		//timer prescalar
		if(Config_ptr->timer_clock==NO_CLOCK){

			//do nothing as CS22:21:20 is already 000

		}

		else if(Config_ptr->timer_clock==F_CPU_CLOCK){

			TCCR2|=(1<<CS20);//CS22:21:20 is 001

		}

		else if(Config_ptr->timer_clock==F_CPU_8){

			TCCR2|=(1<<CS21);//CS22:21:20 is 010

		}

		else if(Config_ptr->timer_clock==F_CPU_64){

			TCCR2|=(1<<CS20)|(1<<CS21);//CS22:21:20 is 011

		}

		else if(Config_ptr->timer_clock==F_CPU_256){

			TCCR2|=(1<<CS22);//CS22:21:20 is 100

		}

		else if(Config_ptr->timer_clock==F_CPU_1024){

			TCCR2|=(1<<CS20)|(1<<CS22);//CS22:21:20 is 101

		}

		else if(Config_ptr->timer_clock==EXTERNAL_CLOCK_ON_FALLING_EDGE){

			TCCR2|=(1<<CS21)|(1<<CS22);//CS22:21:20 is 110

		}

		else if(Config_ptr->timer_clock==EXTERNAL_CLOCK_ON_RISING_EDGE){

			TCCR2|=(1<<CS20)|(1<<CS21)|(1<<CS22);//CS22:21:20 is 111

		}

		//timer mode
		if(Config_ptr->timer_mode==NORMAL_MODE){

			// Normal ModeWGM21=0 & WGM20=0 and they are already 00
			TIMSK|=(1<<TOIE2); // Enable Timer2 Overflow Interrupt


		}
		else if(Config_ptr->timer_mode==COMPARE_MODE){

			TIMSK|=(1<<OCIE2); // Enable Timer2 Compare Interrupt
			TCCR2|=(1<<WGM21);//CTC Mode WGM21=1 & WGM20=0
			OCR0=Config_ptr->timer_compare_MatchValue;// Set Compare Value

		}

		break;
	}

}


/*
 * Description :
 * Functional responsible for Disabling the TIMER via Timer_ID
 */
void Timer_deInit(Timer_ID_Type timer_type) {

	switch (timer_type) {
        case TIMER0:

            TCCR0=0;// disable TIMER0 by clearing the control register
            //disable TIMER0 interrupts
            TIMSK&=~(1<<TOIE0);//disable overflow interrupt
            TIMSK&=~(1<<OCIE0);//disable compare match Interrupt
            break;

        case TIMER1:
            // disable TIMER1 by clearing the control registers
            TCCR1A=0x00;
            TCCR1B=0;
            // Disable TIMER1 interrupts
            TIMSK&=~(1<<TOIE1);//disable overflow interrupt
            TIMSK&=~(1<<OCIE1A);//disable compare match Interrupt
            break;

        case TIMER2:
            TCCR2=0;//disable TIMER2 by clearing the control register
            //disable TIMER2 interrupts
            TIMSK&=~(1<<TOIE2);//disable overflow interrupt
            TIMSK&=~(1<<OCIE2);//disable compare match Interrupt
            break;
    }
}

/*
 * Description :
 * Functional responsible for set the call back function address to the required Timer.
 */
void Timer_setCallBack(void(*a_ptr)(void),Timer_ID_Type a_timer_ID){

	 switch(a_timer_ID) {
	        case TIMER0:
	        	/* Save the address of the Call back function of timer0 in a global variable */
	        	g_timer0Callback = a_ptr;
	            break;

	        case TIMER1:
	        	/* Save the address of the Call back function of timer1 in a global variable */
	        	g_timer1Callback = a_ptr;
	            break;

	        case TIMER2:
	        	/* Save the address of the Call back function of timer2 in a global variable */
	        	g_timer2Callback = a_ptr;
	            break;

	 }

}


