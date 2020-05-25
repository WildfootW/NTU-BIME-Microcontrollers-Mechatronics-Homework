/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#include <avr/io.h>
#include "ADConverter.hpp"

void ADConverter::initial()
{
    // ADC enabled
    ADCSRA |= (1 << ADEN);
    // interrupt enable
    ADCSRA |= (1 << ADIE); // enable
    //ADCSRA &= ~(1 << ADIE); // disable
    // set ADC prescaler
    ADCSRA |= (1 << ADPS2); // 128
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS0);
    // auto trigger
    //ADCSRA &= ~(1 << ADATE); // Auto trigger off

    // select reference voltage
    ADMUX |= (1 << REFS0); // Avcc
    ADMUX |= (1 << REFS1);
    // select left/right adjusted
    //ADMUX |= (1 << ADLAR); // left
    ADMUX &= ~(1 << ADLAR); // right
}
// set which pin to use
void ADConverter::select_input_channel(ADConverterMUX mux)
{
    // 0000 ADC0
    // 0001 ADC1
    // 0010 ADC2
    // 0011 ADC3
    // 0100 ADC4
    // 0101 ADC5
    ADMUX &= 0b11110000;
    ADMUX |= static_cast<uint8_t>(mux);
}
void ADConverter::clear_interrupt_flag()
{
    ADCSRA |= (1 << ADIF);
}
void ADConverter::start()
{
    ADCSRA |= (1 << ADSC);
}
uint16_t ADConverter::get_value()
{
    return ADCW;
}
ADConverterMUX ADConverter::get_mux()
{
    return static_cast<ADConverterMUX>(ADMUX & 0b00001111);
}

