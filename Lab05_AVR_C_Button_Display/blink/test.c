/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2019 WildfootW All rights reserved.
 *
 */

#ifndef F_CPU
#define F_CPU 8000000L // or whatever may be your frequency
#endif

#include <avr/io.h>                    // adding header files
#include <util/delay.h>            // for _delay_ms()

int main(void)
{
    DDRD=0b11111111;

    while(1)
    {
        PORTD=0b00000001;
        _delay_ms(1000);
        PORTD=0b00000000;
        _delay_ms(1000);
    }
}
