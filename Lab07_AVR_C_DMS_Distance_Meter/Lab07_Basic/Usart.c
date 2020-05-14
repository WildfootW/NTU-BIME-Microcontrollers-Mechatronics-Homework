/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#include <avr/io.h>
#include "Usart.h"

void Usart__init(Usart* self, uint16_t baud_rate)
{
    self->baud_rate = baud_rate;
    // setup baud rate
    // Fosc / (UBRR0 + 1) / 16 = baud rate
    UBRR0 = (F_CPU / (self->baud_rate * 16UL)) - 1;
    // usart mode
    UCSR0C &= ~(1 << UMSEL00); // Asynchronous USART
    UCSR0C &= ~(1 << UMSEL01);
    // number of data bits
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // normal mode, int clk
    // transmit
    UCSR0B |= (1 << TXEN0); // enable
}
void Usart__put_string(Usart* self, char* str_ptr)
{
    while(*str_ptr != 0x00)
    {
        while(!(UCSR0A & (1 << UDRE0))); // Usart Data Register Empty
        UDR0 = *str_ptr; // shift register
        ++str_ptr;
    }
}

