/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#include <avr/io.h>
#include "ADConverter.h"

void ADConverter__init(ADConverter* self)
{
    // ADC enabled
    ADCSRA |= (1 << ADEN);
    // select reference voltage
    ADMUX |= (1 << REFS0); // Avcc
    ADMUX |= (1 << REFS1);
    // select left/right adjusted
    //ADMUX |= (1 << ADLAR); // left
    ADMUX &= ~(1 << ADLAR); // right
    // set which pin to use
    ADMUX &= ~(1 << MUX3); // ADC 0
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX0);
    // auto trigger
    ADCSRA &= ~(1 << ADATE);
    // interrupt enable
    ADCSRA &= ~(1 << ADIE);
    // set ADC prescaler
    ADCSRA |= (1 << ADPS2); // 128
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS0);
}
void ADConverter__start(ADConverter* self)
{
    // clear Interrupt Flag
    ADCSRA &= ~(1 << ADIF);
    // start ADC
    ADCSRA |= (1 << ADSC);
}
uint16_t ADConverter__read(ADConverter* self)
{
    //if(!(ADCSRA & (1 << ADIF))) // not done yet
    //    return (1 << 15);
    while((ADCSRA & (1 << ADIF)) == 0);
    return ADC; //_SFR_MEM16(0x78)
}
