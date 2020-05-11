/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2020 WildfootW All rights reserved.
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

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

volatile unsigned long timer1_millis;

void init()
{
// 7 - segement
    DDRB = 0xff; // output
// 7 - segement control
    DDRD = 0xff; // output

// timer
    unsigned long ctc_match_overflow;

    ctc_match_overflow = ((F_CPU / 1000) / 8); //when timer1 is this value, 1ms has passed

    // (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor to 8)
    TCCR1B |= (1 << WGM12) | (1 << CS11);

    OCR1A = ctc_match_overflow;

    // Enable the compare match interrupt
    TIMSK1 |= (1 << OCIE1A);

// interrupt
    sei(); // enable global interrupt
}

void print_seven_segement(uint8_t graph)
{
    PORTB = ~graph;
}

void print_multiplexed_seven_segement(uint16_t number)
{

    for(int i = 0;i < 4;++i)
    {
        int divisor = 1;
        for(int j = 0;j < i;++j) divisor *= 10;

        if(number < divisor)
            continue;

        PORTD = (1 << i);
        print_seven_segement(character_array[(number / divisor) % 10]);
        _delay_ms(1);

        print_seven_segement(character_array[10]); // clear
    }
}


int main(void)
{
    init();
    while(1)
    {
        for(uint16_t i = 0;i < 100;++i)
        {
            timer1_millis = 0;
            while(timer1_millis < 1000)
            {
                print_multiplexed_seven_segement(i);
            }
        }
    }
}

ISR(TIMER1_COMPA_vect)
{
    ++timer1_millis;
}
