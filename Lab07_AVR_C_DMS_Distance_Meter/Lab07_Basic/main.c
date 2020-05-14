/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include "Usart.h"
#include "ADConverter.h"

void initial()
{
    // set prescaler
    CLKPR = (1 << CLKPCE);
    CLKPR = 0b00000011;

    // input
    DDRC = 0x00;
    // output
    DDRB = 0xFF;
    DDRD = 0xFF;
}

uint8_t distance_raw_to_cm(uint16_t raw) // GP2Y0A21YK0F
{
    uint8_t distance = 4800 / (raw - 20);
    if(distance > 80) return 81;
    if(distance < 10) return 9;
    return distance;
}

const uint8_t seven_segement_graph[12] = {
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
    0b00000000, // turn off all
    0b11111111  // turn on all
};

int main(void)
{
    initial();
    ADConverter adc;
    ADConverter__init(&adc);
    Usart usart;
    Usart__init(&usart, 9600);
    uint16_t distance_raw = 0;
    while(1)
    {
        ADConverter__start(&adc);
        distance_raw = (distance_raw * 9 + ADConverter__read(&adc)) / 10;
        uint8_t distance_cm = distance_raw_to_cm(distance_raw);

        // usart
        char buffer[10];
        itoa(distance_raw, buffer, 10);
        Usart__put_string(&usart, buffer);

        // print centimeter to 7 segement LED
        PORTB = ~seven_segement_graph[distance_cm / 10];
        PORTD = ~(((seven_segement_graph[distance_cm % 10] << 1) & 0b11111100) | ((seven_segement_graph[distance_cm % 10]) & 0b00000001));
    }
    return 0;
}

