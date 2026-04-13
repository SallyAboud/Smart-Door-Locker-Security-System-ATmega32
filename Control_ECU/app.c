/*
 * app.c
 *
 *  Created on: Nov 6, 2024
 *      Author: SoO
 */

#include"PIR.h"
#include"dc_motor.h"
#include"external_eeprom.h"
#include"buzzer.h"
#include"UART.h"
#include"timer.h"
#include"twi.h"
#include<util/delay.h>
#include<avr/io.h>
#include<avr/interrupt.h>


#define MC2_READY 0x10
UART_ConfigType UART_Configurations = {UART_8,UART_PARITY_NONE,UART_Stop_1_BIT,UART_BAUD_9600};
TWI_ConfigType TWI_Configurations = {0x01,TWI_BIT_RATE_PRESCALAR_400K};

/* 1.send that mc is ready//done
 * 2.then recieve the pass and put it in pass1[5] and give it to the eeprom //done
 * 3.then recieve the pass again and put it in pass2[5] and compare it to the one in the eeprom//done
 * 3.either they are equal or not send to the other mc//done
 * 4.1.if they are not equal then back to step 2//done
 * 4.2.if they are equal then the pass will be checked if it is correct//done
 * 5.either they are matched or not send to the other mc//done
 * 6.1.if they are not matched go to step 4.2//done
 * 6.2.if they are matched if the option is +//done
 * 6.2.1turn on motor and after 15 sec. check pir and send the reading of the pir to the other mc//done
 * 6.3.if they are matched if the option is -//done
 * 6.3.1 go back to step 2 and change the pass
 * 7.ask about the options again//done
 * */

uint8 pass1[5];
uint8 pass2[5];
uint8 checkPass[5];
uint8 equal=0;
uint8 match=0;
uint8 counter=0;
uint8 option;
uint8 timerCounter=0;

void delay();
void delay_1sec();

int main(){

	UART_init(&UART_Configurations);/* initialize UART driver */
	/* Wait until MC2 is ready to receive the string */
	while(UART_recieveByte() != MC2_READY){}

	TWI_init(&TWI_Configurations);	/* Initialize the TWI/I2C Driver */
	BUZZER_init();/*initialize the buzzer*/
	DCMotor_init();/* initialize dc motor driver */
	PIR_init();/* initialize PIR driver */

	do{
		for(int i=0;i<5;i++){

			pass1[i]=UART_recieveByte();
			EEPROM_writeByte(0x0311, pass1[i]); /* Write 0x0F in the external EEPROM */
			_delay_ms(10);
			EEPROM_readByte(0x0311, checkPass+i);  /* Read 0x0F from the external EEPROM */

		}

		equal=1;

		for(int i=0;i<5;i++){

			pass2[i]=UART_recieveByte();
			if(pass2[i]!=checkPass[i]){

				equal=0;

			}


		}

		UART_sendByte(equal);

	}while(!equal);


	while(1){
		counter=0;
		do{

			match=1;
			for(int i=0;i<5;i++){

				pass2[i]=UART_recieveByte();
				if(pass2[i]!=checkPass[i]){

					match=0;

				}

			}
			UART_sendByte(match);
			counter++;
			if(counter==3 && match==0){
				BUZZER_on();
				//delay 1 minute
				delay();
				while(timerCounter!=60);
				Timer_deInit(TIMER1);
				BUZZER_off();
			}

		}while(!match && counter!=3);

		if(match){

			option=UART_recieveByte();

					if(option=='+'){

						DCMotor_rotate(CW,100);
						//delay(15sec.
						delay();
						while(timerCounter!=15);
						Timer_deInit(TIMER1);
						DCMotor_rotate(Stop,0);
						while(PIR_getState()){

							UART_sendByte(PIR_getState());

						}
						UART_sendByte(PIR_getState());
						DCMotor_rotate(ACW,100);
						//delay(15sec.
						delay();
						while(timerCounter!=15);
						Timer_deInit(TIMER1);
						DCMotor_rotate(Stop,0);
					}
					else if(option=='-'){
						do{
							for(int i=0;i<5;i++){

								pass1[i]=UART_recieveByte();
								EEPROM_writeByte(0x0311, pass1[i]); /* Write 0x0F in the external EEPROM */
								_delay_ms(10);
								EEPROM_readByte(0x0311, checkPass+i);  /* Read 0x0F from the external EEPROM */

							}

							equal=1;

							for(int i=0;i<5;i++){

								pass2[i]=UART_recieveByte();
								if(pass2[i]!=checkPass[i]){

									equal=0;

								}


							}

							UART_sendByte(equal);

						}while(!equal);

					}

		}

	}


}


/*
 * Description :
 * Function responsible for:
 * the callback function called by the Timer driver.
 */
void delay(void){

	timerCounter=0;
	/* Create configuration structure for timer driver */
	Timer_ConfigType Timer_Configurations={0,7811,TIMER1,F_CPU_1024,COMPARE_MODE};


	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Set the Call back function pointer in the timer driver */
	Timer_setCallBack(delay_1sec,TIMER1);

	Timer_init(&Timer_Configurations);/* initialize TIMER driver */



}

void delay_1sec(){

	timerCounter++;
}
