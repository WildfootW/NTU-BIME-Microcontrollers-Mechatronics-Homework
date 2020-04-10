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

// buttom: PB0-7 PC0-1
// segement: PB0-6

void init()
{
// input & output
    DDRD = ((0x1 << 0) | (0x1 << 1) | (0x1 << 2) | (0x1 << 3)); // 0-3 output, 4-7 input
    PORTD = 0x00; // non pull-up
// output
    DDRB = 0xff;
}

int8_t check_status()
{
    for(int8_t i = 0;i < 4;++i)
    {
        PORTD = 0x1 << i;
        //_delay_ms(50);
        for(int8_t j = 0;j < 4;++j)
        {
            if((PIND) & (0x1 << (j + 4)))
                return i * 4 + j;
        }
    }
    return -1;
}
void print_seven_segement(uint8_t graph)
{
    PORTB = ~graph;
}

/*
const uint8_t characterArray[17] = {
    //PGFEDCBA
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0b01110111, // A
    0b01111100, // B
    0b00111001, // C
    0b01011110, // D
    0b01111001, // E
    0b01110001, // F
    0b00000000  // turn off
};
*/
const uint8_t characterArray[17] = {
    //PGFEDCBA
    0b01110001, // F
    0b01111100, // B
    0b01110111, // A
    0b00111111, // 0
    0b01111001, // E
    0b01001111, // 3
    0b01011011, // 2
    0b00000110, // 1
    0b01011110, // D
    0b01111101, // 6
    0b01101101, // 5
    0b01100110, // 4
    0b00111001, // C
    0b01101111, // 9
    0b01111111, // 8
    0b00000111, // 7
    0b00000000  // turn off
};

int main(void)
{
    init();
    int8_t old_result = 16;
    print_seven_segement((characterArray[old_result]));
    while(1)
    {
        int8_t result = check_status();
        if(result == -1)
        {
            //print_seven_segement((characterArray[old_result]));
        }
        else
        {
            print_seven_segement((characterArray[result]));
            //old_result = result;
        }
    }
    _delay_ms(50);
}
