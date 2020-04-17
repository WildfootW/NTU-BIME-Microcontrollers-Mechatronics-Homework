/*
 * LAB8_BONUS.cpp
 *
 * Created: 2019/4/28 下午 04:15:41
 * Author : MOMO TSAI
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	int i;
    CLKPR=(1<<CLKPCE);
	CLKPR=0b00000011;
	DDRD=0xFF;
	DDRB=0XFF;
	TCCR0A=0b10100001; 
	TCCR0B=0b00000010; 
	TCCR2A=0b10100001;
	TCCR2B=0b00000010;
	OCR0A=0;
	OCR0B=0;
	OCR2A=0;
	OCR2B=0;
	_delay_ms(1000);
	for(i=0;i<3;i++){
		OCR0A=205;
		OCR0B=0; 
		OCR2A=203;
		OCR2B=0;
		_delay_ms(3200);
		OCR0A=203;
		OCR0B=0;
		OCR2A=0;
		OCR2B=203;
		_delay_ms(520);
	}
	OCR0A=0;
	OCR0B=0;
	OCR2A=0;
	OCR2B=0;
	
	
}

