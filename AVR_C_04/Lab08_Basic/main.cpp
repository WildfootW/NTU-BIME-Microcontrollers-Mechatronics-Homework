/*
 * LAB8.cpp
 *
 * Created: 2019/4/28 上午 11:46:19
 * Author : MOMO TSAI
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
    CLKPR=(1<<CLKPCE);
    CLKPR=0b00000011; // set clk to 1Mhz
    DDRD=0xFF; // PORTD as output
	DDRB=0xFF;
	_delay_ms(1000);
    OCR0A=205;// 80% duty cycle
    OCR0B=0; // 20% duty cycle
	OCR2A=203;
	OCR2B=0;
    TCCR0A=0b10100001; // phase correct PWM
    TCCR0B=0b00000010; // timer prescaler
	TCCR2A=0b10100001;
	TCCR2B=0b00000010;
	_delay_ms(5500);
	OCR0A=203;
	OCR0B=0;
	OCR2A=0;
	OCR2B=203;
	_delay_ms(400);
	OCR0A=205;
	OCR0B=0;
	OCR2A=203;
	OCR2B=0;
	_delay_ms(3200);
	OCR0A=203;
	OCR0B=0;
	OCR2A=0;
	OCR2B=203;
	_delay_ms(400);
	OCR0A=205;
	OCR0B=0;
	OCR2A=203;
	OCR2B=0;
	_delay_ms(5500);
	OCR0A=203;
	OCR0B=0;
	OCR2A=0;
	OCR2B=203;
	_delay_ms(400);
	OCR0A=207;
	OCR0B=0;
	OCR2A=203;
	OCR2B=0;
	_delay_ms(3200);
	OCR0A=0;
	OCR0B=0;
	OCR2A=0;
	OCR2B=0;
	
	
    
}

