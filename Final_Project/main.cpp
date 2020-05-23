/*
 * main.cpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#include "AVRUtils.hpp"
#include "ADConverter.hpp"
#include "WheelControl.hpp"
#include <avr/interrupt.h>

WheelControl wheel_control; // PD3, 4, 5. PD2, 7, 6. Timer0
ADConverter ad_converter;

void initial()
{
    CLKPR = (1 << CLKPCE);
    CLKPR = 0b00000011; // set clk to 1 Mhz

    sei();

    wheel_control.initial();
    ad_converter.initial();

}

int main(void)
{
    initial();

}

ISR(ADC_vect)
{
    ADConverterMUX current_mux = ad_converter.get_mux();
    switch(current_mux)
    {
        case ADConverterMUX::ADC0:
            ad_converter.get_value();
            ad_converter.select_input_channel(ADConverterMUX::ADC1);
            break;
        case ADConverterMUX::ADC1:
            ad_converter.get_value();
            ad_converter.select_input_channel(ADConverterMUX::ADC2);
            break;
        case ADConverterMUX::ADC2:
            ad_converter.get_value();
            ad_converter.select_input_channel(ADConverterMUX::ADC3);
            break;
        case ADConverterMUX::ADC3:
            ad_converter.get_value();
            ad_converter.select_input_channel(ADConverterMUX::ADC0);
            break;
        default:
            break;
    }
    ad_converter.clear_interrupt_flag();
    ad_converter.start();
}
