/*
 * LAB6_1.cpp
 *
 * Created: 2019/4/14 上午 10:45:01
 * Author : MOMO TSAI
 */ 

#include <avr/io.h>
int BUZZER(int countdown){
	TCNT0 = countdown;
	TCCR0A = 0;
	TCCR0B = 0b00000010;
	while((TIFR0&(1<<TOV0))==0);
	TCCR0B = 0;
	TIFR0 = (1<<TOV0);
	PORTC = PORTC^0b00100000;
	return  1;
}

int main(void)
{
    CLKPR=(1<<CLKPCE);
    CLKPR=0b00000011;
    DDRB=0b11111111;
    PORTB=0b11111111;
    DDRC=0b11111111;
    DDRD=0b00000000;
    PORTD=0b11111111;
    PORTC=0b11011111;
    while (1)
    {
	    if ((PIND & 0b10000000)==0) //G.
	    {
		    PORTB=0b01000010;
			while(1){
				BUZZER(176);
				if((PIND & 0b10000000)!=0){
					PORTC = 0b00000000;
					break;
				}
			}
	    }
	    else if ((PIND & 0b01000000)==0) //F.
	    {
		    PORTB=0b00001110;
			while(1){
				BUZZER(166);
				if((PIND & 0b01000000)!=0){
					PORTC = 0b00000000;
					break;
				}
			}
	    }
	    else if ((PIND & 0b00100000)==0) //E.
	    {
		    PORTB=0b000000110;
			while(1){
				BUZZER(161);
				if((PIND & 0b00100000)!=0){
					PORTC = 0b00000000;
					break;
				}
			}
	    }
	    else if ((PIND & 0b00010000)==0) //D.
	    {
		    PORTB=0b01000000;
			while(1){
				BUZZER(149);
				if((PIND & 0b00010000)!=0){
					PORTC = 0b00000000;
					break;
				}
			}
	    }
	    else if ((PIND & 0b00001000)==0) //C.
	    {
		    PORTB=0b01000110;
			while(1){
				BUZZER(137);
				if((PIND & 0b00001000)!=0){
					PORTC = 0b00000000;
					break;
				}
			}
	    }
	    else if ((PIND & 0b00000100)==0) //B
	    {
		    PORTB=0b00000000;
			while(1){
				BUZZER(129);
				if((PIND & 0b00000100)!=0){
					PORTC = 0b00000000;
					break;
				}
			}
	    }
	    else if ((PIND & 0b00000010)==0) //A
	    {
		    PORTB=0b00001000;
			while(1){
				BUZZER(114);
				if((PIND & 0b00000010)!=0){
					PORTC = 0b00000000;
					break;
				}
			}
	    }
	    else if ((PIND & 0b00000001)==0) //G
	    {
		    PORTB=0b11000010;
			while(1){
				BUZZER(96);
				if((PIND & 0b00000001)!=0){
					PORTC = 0b00000000;
					break;
				}
			}
	    }
	    PORTB=0b11111111;
    }
}


