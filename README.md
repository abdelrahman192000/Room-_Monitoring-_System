# Room-Monitoring-System

#### Description

1-A counter is required to count people entering and leaving a room. The room has a separate entrance and exit. Sensor detects people entering and leaving. Up to sevenpeople are allowed in the room at one time

2-The number of peoplein the room is shown on a seven segmentdisplay

3-Using threeLED lights, oneindicates that the room is empty, and one indicates room isfulland one to indicatethatthe room have people but not full

4-For input buttons, entering and leaving, choose push buttons.
### first use library

```
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

```

### second we define the interrupt configuration
#### configuration of interrupt 0 : 
```
void INT0_Inti (void)
{
	DDRD &=~(1<<2);
	MCUCR |= (1<<0);
	MCUCR |= (1<<1);
	GICR |=(1<<6);
	SREG |=(1<<7);
}
```

we use reg call `DDRD` to set the direction of the pin
, `MCUCR`	 (MCU CONTROL REGISTER) to define a level trigger or edge trigger on external INT0 and INT1
![the reg image ](https://www.google.com/url?sa=i&url=http%3A%2F%2Farchive.fabacademy.org%2Ffabacademy2017%2Ffablabtrivandrum%2Fstudents%2F280%2Fweek8.html&psig=AOvVaw2lewNrCJrM1cy8l-hSX5t-&ust=1672352738985000&source=images&cd=vfe&ved=0CBAQjRxqFwoTCJCR9MytnfwCFQAAAAAdAAAAABAE)

we put in bit num 0 and 1 one to define INT0 as rising edge 
#### configuration of interrupt 1 : 
```
void INT1_Inti (void)
{
	DDRD &=~(1<<3);
	MCUCR |= (1<<2);
	MCUCR |= (1<<3);
	GICR |=(1<<7);
	SREG |=(1<<7);
}
```

the same with INT1 but here we put one in bir num 2 and 3 

next we use `GICR` (GENERAL INTERRUPT CONTROL REG) that contains the interrupt enable bits for all the external interrupts of the atmega 32 

put one on bit num 6 to active INT0 and one in bit 7 to active INT1

and finaly `SREG` put one in bit 7 to active general interrupt to use ISR

####  USE ISR :
```
use isr 
ISR(INT0_vect)
{
	_delay_ms(30);
	if (number >=0 && number <7)
	{
		number++;
	}
	PORTC = (PORTC & 0Xf0) | (number);
}
```
in the condetion we see if the push button is active or not , if it active we increment number till the max 7 every time it work or active button

```
DDRC |= (1<<0) | (1<<1) | (1<<2) | (1<<3);
PORTC = (PORTC & 0Xf0) | (0x0f);
PORTC = 0 ;
DDRD |= (1<<5) | (1<<6) | (1<<7) ;
PORTC &=~ (1<<5) & (1<<6) & (1<<7);
	
```
`DDRC |= (1<< bit_num )` to set bit and
`DDRC & = ~ (1<< bit_num )` to clear bit

#### check leds

```
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
```
ARed LED that willbe on when the number of peopleinside the room is at the maximum

AGreenLED that willbe on when the room is empty

A Blue LED that will be one when the number of peopleinside the room is greaterthan zero and less than the maximum

