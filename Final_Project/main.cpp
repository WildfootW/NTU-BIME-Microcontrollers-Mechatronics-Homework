/*
 * main.cpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#include <avr/interrupt.h>
#include "AVRUtils.hpp"
#include "ADConverter.hpp"
#include "Millis.hpp"

ADConverter ad_converter; // PC0, 1, 2, 3
Millis millis; // Timer1

#include "Sensors.hpp"
#include "RouteDetector.hpp"
#include "ObstacleDetector.hpp"
#include "WheelControl.hpp"

WheelControl wheel_control; // PD3, 4, 5. PD2, 7, 6. Timer0
IrSensor2Y0A21 sensor_o; // PC0
IrSensorTCRT5000 sensor_l; // PC1
IrSensorTCRT5000 sensor_c; // PC2
IrSensorTCRT5000 sensor_r; // PC3
RouteDetector routedetector(&sensor_l, &sensor_c, &sensor_r);
ObstacleDetector obstacledetector(&sensor_o);

void initial()
{
    CLKPR = (1 << CLKPCE);
    CLKPR = 0b00000011; // set clk to 1 Mhz

    sei();
    ad_converter.initial();
    pin_PC1::configure_pin_mode(AVRIOPinMode::Input);
    pin_PC2::configure_pin_mode(AVRIOPinMode::Input);
    pin_PC3::configure_pin_mode(AVRIOPinMode::Input);
    pin_PC4::configure_pin_mode(AVRIOPinMode::Input);

    millis.initial();

    wheel_control.initial();

    sensor_l.initial(350);
    sensor_c.initial(150);
    sensor_r.initial(500);

    obstacledetector.initial();
    routedetector.initial();
}

int main(void)
{
    initial();

    while(true)
    {
        RouteStatusType current_status = routedetector.get_current_status();
        if(current_status == RouteStatusType::center_on_line)
        {
            wheel_control.go(255);
        }
    }
}

ISR(ADC_vect)
{
    ADConverterMUX current_mux = ad_converter.get_mux();
    switch(current_mux)
    {
        case ADConverterMUX::ADC0:
            sensor_o.value_update(ad_converter.get_value());
            ad_converter.select_input_channel(ADConverterMUX::ADC1);
            break;
        case ADConverterMUX::ADC1:
            sensor_l.value_update(ad_converter.get_value());
            ad_converter.select_input_channel(ADConverterMUX::ADC2);
            break;
        case ADConverterMUX::ADC2:
            sensor_c.value_update(ad_converter.get_value());
            ad_converter.select_input_channel(ADConverterMUX::ADC3);
            break;
        case ADConverterMUX::ADC3:
            sensor_r.value_update(ad_converter.get_value());
            ad_converter.select_input_channel(ADConverterMUX::ADC0);
            break;
        default:
            break;
    }
    ad_converter.clear_interrupt_flag();
    ad_converter.start();
}
ISR(TIMER1_COMPA_vect)
{
    millis.increase_millis();
}
