/*
 * app.c
 *
 *  Created on: Nov 6, 2024
 *      Author: SoO
 */

#include"keypad.h"
#include"lcd.h"
#include"UART.h"
#include<util/delay.h>
#include"timer.h"
#include<avr/io.h>
#include<avr/interrupt.h>

#define MC2_READY 0x10

UART_ConfigType UART_Configurations={UART_8,UART_PARITY_NONE,UART_Stop_1_BIT,UART_BAUD_9600};

uint8 pass[5];
uint8 key_num;
uint8 equal;// if two passwords are equal at setting the pass
uint8 option;//+ or - options fore changing the pass and for opening the door
uint8 match;//if the entered pass matches the right pass
uint8 people;//if there are people passing
uint8 counter=0;//the number of entered wrong passes
uint8 timerCounter=0;

void delay();
void delay_1sec();

int main(){
	UART_init(&UART_Configurations);
	UART_sendByte(MC2_READY);//Send MC2_READY byte to MC1

	LCD_init();/* initialize LCD driver */
	SREG|=(1<<7);//enable global interrupts


	LCD_displayString("Door Lock System");
	delay();
	while(timerCounter!=1);
	Timer_deInit(TIMER1);

	LCD_clearScreen();



	do{

		LCD_displayString("Plz enter pass:");

		for(int i=0;i<5;i++){

			/* Get the pressed button from keypad */
			key_num=KEYPAD_getPressedKey();
			_delay_ms(300);
			pass[i]=key_num;
			/* Send the Key number to the other micro-controller through the UART */
			UART_sendByte(pass[i]);
			LCD_moveCursor(1,i);
			LCD_displayCharacter('*');

		}

		key_num=KEYPAD_getPressedKey();
		while(key_num!='='){
			key_num=KEYPAD_getPressedKey();
		}
		_delay_ms(300);

		LCD_clearScreen();

		LCD_displayString("Plz re-enter the");
		LCD_displayStringRowColumn(1,0,"same pass:");

		for(int i=0;i<5;i++){

			/* Get the pressed button from keypad */
			key_num=KEYPAD_getPressedKey();
			_delay_ms(300);
			pass[i]=key_num;
			/* Send the Key number to the other micro-controller through the UART */
			UART_sendByte(pass[i]);
			LCD_moveCursor(1,10+i);
			LCD_displayCharacter('*');
		}

		key_num=KEYPAD_getPressedKey();
		while(key_num!='='){
			key_num=KEYPAD_getPressedKey();
		}
		_delay_ms(300);

		LCD_clearScreen();

		equal=UART_recieveByte();

	}while(!equal);



	while(1){

			counter=0;
			LCD_displayString("+ : Open Door");
			LCD_displayStringRowColumn(1,0,"- : Change Pass");

			option=KEYPAD_getPressedKey();
			_delay_ms(300);
			LCD_clearScreen();


			do{
				LCD_clearScreen();
				LCD_displayString("Plz enter old");
				LCD_displayStringRowColumn(1,0,"pass:");
				counter++;
				for(int i=0;i<5;i++){

						/* Get the pressed button from keypad*/
						key_num=KEYPAD_getPressedKey();
						_delay_ms(300);
						pass[i]=key_num;
						/* Send the Key number to the other micro-controller through the UART*/
						UART_sendByte(pass[i]);
						LCD_moveCursor(1,i+5);
						LCD_displayCharacter('*');

					}
				key_num=KEYPAD_getPressedKey();
				while(key_num!='='){
					key_num=KEYPAD_getPressedKey();
				}
				_delay_ms(300);


				match=UART_recieveByte();


				if(counter==3 && match==0){

					LCD_clearScreen();
					LCD_displayStringRowColumn(0,1,"System Locked");
					LCD_displayStringRowColumn(1,0,"Wait for 1 min");
					//delay 60 sec.
					delay();
					while(timerCounter!=60);
					Timer_deInit(TIMER1);
					LCD_clearScreen();

				}

			}while(!match && counter!=3);

			LCD_clearScreen();

			if(match){
				UART_sendByte(option);
				if(option=='+'){

					LCD_displayString("Door Unlocking");
					LCD_displayStringRowColumn(1,2,"Please wait");
					//delay 15seconds
					delay();
					while(timerCounter!=15);
					Timer_deInit(TIMER1);

					people=UART_recieveByte();
					LCD_clearScreen();

					while(people){

						LCD_displayStringRowColumn(0,0,"Wait for People");
						LCD_displayStringRowColumn(1,3,"To Enter");
						people=UART_recieveByte();
					}

					LCD_clearScreen();
					LCD_displayString("Door Locking");
					//delay 15 second
					delay();
					while(timerCounter!=15);
					Timer_deInit(TIMER1);

				}
				else if(option=='-'){




					do{
						LCD_displayString("Plz enter pass:");

						for(int i=0;i<5;i++){

							/* Get the pressed button from keypad */
							key_num=KEYPAD_getPressedKey();
							_delay_ms(300);
							pass[i]=key_num;
							/* Send the Key number to the other micro-controller through the UART */
							UART_sendByte(pass[i]);
							LCD_moveCursor(1,i);
							LCD_displayCharacter('*');

						}
						key_num=KEYPAD_getPressedKey();
						while(key_num!='='){
							key_num=KEYPAD_getPressedKey();
						}
						_delay_ms(300);

						LCD_clearScreen();

						LCD_displayString("Plz re-enter the");
						LCD_displayStringRowColumn(1,0,"same pass:");

						for(int i=0;i<5;i++){

							/* Get the pressed button from keypad */
							key_num=KEYPAD_getPressedKey();
							_delay_ms(300);
							pass[i]=key_num;
							/* Send the Key number to the other micro-controller through the UART */
							UART_sendByte(pass[i]);
							LCD_moveCursor(1,10+i);
							LCD_displayCharacter('*');
						}
						key_num=KEYPAD_getPressedKey();
						while(key_num!='='){
							key_num=KEYPAD_getPressedKey();
						}
						_delay_ms(300);

						LCD_clearScreen();

						equal=UART_recieveByte();

					}while(!equal);


				}

			}

				LCD_clearScreen();




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
