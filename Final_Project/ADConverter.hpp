/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#ifndef ADCONVERTER_HPP
#define ADCONVERTER_HPP

#include <avr/io.h>

enum class ADConverterMUX: uint8_t
{
    ADC0 = 0,
    ADC1 = 1,
    ADC2 = 2,
    ADC3 = 3,
    ADC4 = 4,
    ADC5 = 5
};
class ADConverter
{
public:
    ADConverter(){}
    void initial();

    // set which pin to use
    void select_input_channel(ADConverterMUX mux);
    void clear_interrupt_flag();
    void start();
    uint16_t get_value();
    ADConverterMUX get_mux();
};
/*
in main:
sei();
adconverter.start()
ISR(ADC_vect)
{
    adconverter.get_value();
    adconverter.clear_interrupt_flag();
    adconverter.select_input_channel(0b00000101);
    adconverter.start();
}
*/
#endif //ADCONVERTER_HPP
