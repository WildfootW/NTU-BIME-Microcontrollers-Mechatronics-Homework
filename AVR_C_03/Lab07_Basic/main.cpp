/*
 * GccApplication4.cpp
 *
 * Created: 2019/4/15 下午 06:05:09
 * Author : MOMO TSAI
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

uint16_t ADCRead(const int);
void USART_putstring(char* StringPtr);
int main(void){
	CLKPR=0b10000000;
	CLKPR=0b00000000;
	DDRC = 0;
	ADCSRA |= (1<<ADEN);
	unsigned int BaudR = 9600;
	unsigned int ubrr = (F_CPU / (BaudR*16UL))-1;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<TXEN0);
	DDRB=0b11111111;
	PORTB=0b11111111;
	DDRD=0b11111111;
	PORTD=0b11111111;
	while(1){
		float sumVal = 0;
		char Buffer[]=" ";
		int led = 0;
		int ledA = 0;
		int ledB = 0;
		for(int i = 0; i < 10; i++)
		sumVal += (float)ADCRead(0);
		sumVal /= 10; //mean of 10 readings
		if(sumVal>=628){
			sumVal = 6;
		}
		else if(sumVal>=593&&sumVal<=627){
			sumVal = 7;
		}
		else if(sumVal>=543&&sumVal<=592){
			sumVal = 8;
		}
		else if(sumVal>=496&&sumVal<=542){
			sumVal = 9;
		}
		else if(sumVal>=455&&sumVal<=495){
			sumVal = 10;
		}
		else if(sumVal>=417&&sumVal<=454){
			sumVal = 11;
		}
		else if(sumVal>=393&&sumVal<=416){
			sumVal = 12;
		}
		else if(sumVal>=371&&sumVal<=392){
			sumVal = 13;
		}
		else if(sumVal>=342&&sumVal<=370){
			sumVal = 14;
		}
		else if(sumVal>=322&&sumVal<=341){
			sumVal = 15;
		}
		else if(sumVal>=306&&sumVal<=321){
			sumVal = 16;
		}
		else if(sumVal>=292&&sumVal<=305){
			sumVal = 17;
		}
		else if(sumVal>=280&&sumVal<=291){
			sumVal = 18;
		}
		else if(sumVal>=264&&sumVal<=279){
			sumVal = 19;
		}
		else if(sumVal>=253&&sumVal<=263){
			sumVal = 20;
		}
		else if(sumVal>=246&&sumVal<=252){
			sumVal = 21;
		}
		else if(sumVal>=236&&sumVal<=245){
			sumVal = 22;
		}
		else if(sumVal>=227&&sumVal<=235){
			sumVal = 23;
		}
		else if(sumVal>=218&&sumVal<=226){
			sumVal = 24;
		}
		else if(sumVal>=207&&sumVal<=217){
			sumVal = 25;
		}
		else if(sumVal>=199&&sumVal<=206){
			sumVal = 26;
		}
		else if(sumVal>=193&&sumVal<=198){
			sumVal = 27;
		}
		else if(sumVal>=188&&sumVal<=192){
			sumVal = 28;
		}
		
		led = sumVal;
		ledA = led/10;
		ledB = led%10;
		if(ledB == 0) //0
		{
			PORTB=0b11000000;
		}
		else if (ledB == 9) //9
		{
			PORTB=0b10011000;
		}
		else if (ledB == 8) //8
		{
			PORTB=0b10000000;
		}
		else if (ledB == 7) //7
		{
			PORTB=0b11111000;
		}
		else if (ledB == 6) //6
		{
			PORTB=0b10000010;
		}
		else if (ledB == 5) //5
		{
			PORTB=0b10010010;
		}
		else if (ledB == 4) //4
		{
			PORTB=0b10011001;
		}
		else if (ledB == 3) //3
		{
			PORTB=0b10110000;
		}
		else if (ledB == 2) //2
		{
			PORTB=0b10100100;
		}
		else if (ledB == 1) //1
		{
			PORTB=0b11111001;
		}
		if(ledA == 0) //0
		{
			PORTD=0b10000000;
		}
		else if (ledA == 9) //9
		{
			PORTD=0b10110000;
		}
		else if (ledA == 8) //8
		{
			PORTD=0b00000000;
		}
		else if (ledA == 7) //7
		{
			PORTD=0b11110000;
		}
		else if (ledA == 6) //6
		{
			PORTD=0b00000100;
		}
		else if (ledA == 5) //5
		{
			PORTD=0b10010010;
		}
		else if (ledA == 4) //4
		{
			PORTD=0b00110001;
		}
		else if (ledA == 3) //3
		{
			PORTD=0b01100000;
		}
		else if (ledA == 2) //2
		{
			PORTD=0b01001000;
		}
		else if (ledA == 1) //1
		{
			PORTD=0b11110001;
		}
		char *intStr = itoa((int)sumVal, Buffer, 10);
		strcat(intStr, "\n");
		USART_putstring(intStr);
		_delay_ms(500);
	}
}uint16_t ADCRead(const int channel) {
	ADMUX = 0b01000000;
	ADMUX |= channel;
	ADCSRA |= (1<<ADSC) | (1<<ADIF);
	while ( (ADCSRA & (1<<ADIF)) == 0);
	ADCSRA &= ~(1<<ADSC);
	return ADC;
}
void USART_putstring(char* StringPtr){
	while(*StringPtr != 0x00){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *StringPtr;
		StringPtr++;
	}
}

