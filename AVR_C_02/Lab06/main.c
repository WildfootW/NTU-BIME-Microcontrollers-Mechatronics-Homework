/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2019 WildfootW All rights reserved.
 *
 */

#ifndef F_CPU
#define F_CPU 1000000uL // 1 MHz unsinged long
#endif
 
#include <avr/io.h>                    // adding header files

// buttom: PB0-7 PC0-1
// segement: PD0-6

// don't use fucking PC6

void init()
{
// input
    DDRB = 0x0;
    PORTB = 0xff;
    DDRC = 0x0;
    PORTC = 0xff; // pull-up
// output
    DDRD = 0xff;
}

int8_t check_status()
{
    for(int8_t i = 0;i < 10;++i)
    {
        if(0 <= i && i <= 7)
        {
            if((~PINB) & (0x1 << i))
                return i;
        }
        else if(8 <= i && i <= 9)
        {
            if((~PINC) & (0x1 << (i - 8)))
                return i;
        }
    }
    return -1;
}
void print_seven_segement(uint8_t graph)
{
    PORTD = graph;
}

// common anode
const uint8_t characterArray[10] = {
    //PGFEDCBA
    0b11000000,
    0b11111001,
    0b10100100,
    0b10110000,
    0b10011001,
    0b10010010,
    0b10000010,
    0b11111000,
    0b10000000,
    0b10010000
};

int main(void)
{
    init();
    while(1)
    {
        int8_t result = check_status();
        if(result == -1)
            print_seven_segement((0xff)); // turn off
        else
            print_seven_segement((characterArray[result]));
    }
    _delay_ms(50);
}
