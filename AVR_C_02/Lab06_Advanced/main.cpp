/*
 * LAB6_2.cpp
 *
 * Created: 2019/4/14 下午 10:14:15
 * Author : MOMO TSAI
 */ 

#include <avr/io.h>

int time1(int melody,int last_time){
	int i;
	for(i=0;i<last_time;i++){
		TCNT0 = melody;
		TCCR0A = 0;
		TCCR0B = 0b00000010;
		while((TIFR0&(1<<TOV0))==0);
		TCCR0B = 0;
		TIFR0 = (1<<TOV0);
		PORTC = PORTC^0b00100000;
		
	}
	PORTC = 0b00000000;
	return 0;
}
int main(void)
{
	CLKPR=(1<<CLKPCE);
	CLKPR=0b00000011;
	DDRC=0b11111111;
	PORTC=0b11011111;
	int sound[25][2] = {
		{96,196},{96,196},{114,440},{96,392},{137,522},{129,494},
		{96,196},{96,196},{114,440},{96,392},{149,588},{137,522},
		{96,196},{96,196},{176,784},{161,660},{137,522},{129,494},{114,440},
		{166,349},{166,349},{161,660},{137,522},{149,588},{137,522}
		};
	int j;
	for(j=0;j<25;j++){
		time1(sound[j][0],sound[j][1]);
	}
	
}

  


