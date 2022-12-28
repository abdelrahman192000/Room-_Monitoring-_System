/*
 * main.c
 *
 *  Created on: Dec 21, 2022
 *
 *      Author: Abdelrahman Adel Mahmoud
 *      ID : 20180131
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int number=0;
// /////////////////////////////////////////////////////
// interupt 0 config

ISR(INT0_vect)
{
	_delay_ms(30);
	if (number >=0 && number <7)
	{
		number++;
	}
	PORTC = (PORTC & 0Xf0) | (number);
}

void INT0_Inti (void)
{
	DDRD &=~(1<<2);
	MCUCR |= (1<<0);
	MCUCR |= (1<<1);
	GICR |=(1<<6);
	SREG |=(1<<7);
}
// //////////////////////////////////////////////////////
// interupt 1 config

ISR(INT1_vect)
{
	_delay_ms(30);
	if (number==0)
	{
		// no thing
	}
	else
	{
		number--;
	}

	PORTC = (PORTC & 0Xf0) | (number);
}

void INT1_Inti (void)
{
	DDRD &=~(1<<3);

	MCUCR |= (1<<2);
	MCUCR |= (1<<3);

	GICR |=(1<<7);

	SREG |=(1<<7);
}
// /////////////////////////////////////////////////////
// interupt 2 config
int main ()
{

	INT1_Inti();
	INT0_Inti();

	DDRC |= (1<<0) | (1<<1) | (1<<2) | (1<<3);
	//set 4 pin of 7447  as output
	PORTC = (PORTC & 0Xf0) | (0x0f);//make use use only first 4pins from port c
	PORTC = 0 ;
	DDRD |= (1<<5) | (1<<6) | (1<<7) ;
	// three pins : 5 for red led , 6 for green led and 7 blue led
	PORTC &=~ (1<<5) & (1<<6) & (1<<7);
	// set the three led as initial value low
	while (1)
	{
		// check room empty

		if (number == 0)
		{
			PORTD|= (1<<6);
		}
		else
		{
			PORTD&=~ (1<<6);

		}
		// /////////////////////
		//check room full
		if (number == 7)
		{
			PORTD |=(1<<5);
			;
		}
		else
		{
			PORTD &=~(1<<5);

		}
		// ///////////////////
		// check room not full and not empty
		if (number !=0 && number!=7)
		{
			PORTD |= (1<<7);
		}
		else
		{
			PORTD &=~(1<<7);
		}
	}
}
