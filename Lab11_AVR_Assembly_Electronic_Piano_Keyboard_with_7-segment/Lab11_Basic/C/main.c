/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2020 WildfootW All rights reserved.
 *
 */

#include <avr/io.h>

void initial()
{
// Buttom
    DDRB = 0x00;    // input
    PORTB = 0xff;   // pull-up
// 7 - segement
    DDRD = 0xff;    // output
}

void print_seven_segement(uint8_t graph)
{
    PORTD = ~graph;
}

const uint8_t character_array[18] = {
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
    0b01111100, // b
    0b00111001, // C
    0b01011110, // d
    0b01111001, // E
    0b01110001, // F
    0b00111101, // G
    0b00000000  // turn off
};

int8_t check_status()
{
    for(uint8_t i = 0;i < 8;++i)
    {
        if((~PINB) & (0x1 << i))
        {
            return i;
        }
    }
    return -1;
}

int main(void)
{
    initial();
    while(1)
    {
        int8_t key = check_status();
        switch(key)
        {
            case -1: // off
                print_seven_segement(character_array[17]);
                break;
            case 0: // C
                print_seven_segement(character_array[12]);
                break;
            case 1: // D
                print_seven_segement(character_array[13]);
                break;
            case 2: // E
                print_seven_segement(character_array[14]);
                break;
            case 3: // F
                print_seven_segement(character_array[15]);
                break;
            case 4: // G
                print_seven_segement(character_array[16]);
                break;
            case 5: // A
                print_seven_segement(character_array[10]);
                break;
            case 6: // B
                print_seven_segement(character_array[11]);
                break;
        }
    }
    return 0;
}
