/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2020 WildfootW All rights reserved.
 *
 */

#include <avr/io.h>
#include <util/delay.h>

void init()
{
// 7 - segement
    DDRB = 0xff; // output
    DDRD = 0xff; // output
}

void print_seven_segement(uint8_t graph_a, uint8_t graph_b)
{
    PORTD = ~graph_a;
    PORTB = ~graph_b;
}

const uint8_t character_array[11] = {
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
    0b00000000  // turn off
};

int main(void)
{
    init();
    while(1)
    {
        for(int i = 0;i < 10;++i)
            for(int j = 0;j < 10;++j)
            {
                print_seven_segement(character_array[i], character_array[j]);
                _delay_ms(1000);
            }
    }
}
