/*
 * main.cpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#include <avr/interrupt.h>
#include "IOPin.hpp"

/*
#include "Usart.hpp"
Usart usart(9600);
*/

#include "Millis.hpp"
Millis millis; // Timer1

#include "SevenSegment.hpp"
SevenSegment sevensegment;

#include "ADConverter.hpp"
ADConverter ad_converter; // PC0, 1, 2, 3

#include "WheelControl.hpp"
WheelControl wheel_control; // PD3, 4, 5. PD2, 7, 6. Timer0

#include "Sensors.hpp"
IrSensor2Y0A21 sensor_o_c; // PC0
IrSensorTCRT5000 sensor_l; // PC1
IrSensorTCRT5000 sensor_c; // PC2
IrSensorTCRT5000 sensor_r; // PC3
IrSensor2Y0A21 sensor_o_r; // PC4

#include "RouteDetector.hpp"
RouteDetector routedetector(&sensor_l, &sensor_c, &sensor_r);

#include "ObstacleDetector.hpp"
ObstacleDetector obstacledetector(&sensor_o_c, &sensor_o_r);

void initial()
{
    CLKPR = (1 << CLKPCE);
    CLKPR = 0b00000011; // set clk to 1 Mhz
    //CLKPR = 0b00000000; // set clk to 8 Mhz

    sei();
    ad_converter.initial();
    pin_PC1::configure_pin_mode(AVRIOPinMode::Input);
    pin_PC2::configure_pin_mode(AVRIOPinMode::Input);
    pin_PC3::configure_pin_mode(AVRIOPinMode::Input);
    pin_PC4::configure_pin_mode(AVRIOPinMode::Input);

    millis.initial();
    /*
    usart.initial();
    */
    sevensegment.print(SevenSegmentGraph::off);

    wheel_control.initial(0.8);

    sensor_l.initial(225);
    sensor_c.initial(170);
    sensor_r.initial(255);

    obstacledetector.initial();
    routedetector.initial();

    sevensegment.initial();
}

int main(void)
{
    initial();

    /* Usart */
    /*
    while(true)
    {
        char hello[] = "Hello World!\n";
        usart.put_str(hello);
    }
    */

    //wheel_control.set_global_ratio(0.5);
    while(true)
    {
        routedetector.update_status();
        RouteStatusType current_status = routedetector.get_current_status();
        switch(current_status)
        {
            /* only two sensor */
            /*
            case RouteStatusType::center_on_line:
            {
                wheel_control.go(255);
                break;
            }
            case RouteStatusType::llleft_on_line:
            {
                wheel_control.rotate(100); // left turn
                break;
            }
            case RouteStatusType::rright_on_line:
            {
                wheel_control.rotate(-100);
                break;
            }
            */

            /* simple version */
            /*
            case RouteStatusType::center_on_line:
            {
                wheel_control.go(255);
                break;
            }
            case RouteStatusType::llleft_on_line:
            {
                wheel_control.turn(100); // left turn
                break;
            }
            case RouteStatusType::rright_unknown:
            {
                wheel_control.turn(-70);
                break;
            }
            case RouteStatusType::llleft_unknown:
            {
                wheel_control.turn(70);
                break;
            }
            case RouteStatusType::rright_on_line:
            {
                wheel_control.turn(-100);
                break;
            }
            case RouteStatusType::invalid:
            {
                wheel_control.go(150);
                break;
            }
            */

            /* Version 1 */
            case RouteStatusType::center_on_line:
            {
                wheel_control.go(255);
                break;
            }
            case RouteStatusType::llleft_on_line:
            {
                wheel_control.turn(70);
                break;
            }
            case RouteStatusType::center_unknown:
            {
                wheel_control.go(50);
                break;
            }
            case RouteStatusType::rright_unknown:
            {
                wheel_control.turn(-100);
                break;
            }
            case RouteStatusType::llleft_unknown:
            {
                wheel_control.turn(100);
                break;
            }
            case RouteStatusType::rright_on_line:
            {
                wheel_control.turn(-70);
                break;
            }
            case RouteStatusType::invalid:
            {
                wheel_control.go(150);
                break;
            }

            default:
            {
                break;
            }
        }
    }
    /*
    wheel_control.rotate(50);
    while(sensor_o_c.get_distance() > 20)
        wheel_control.go(100);
    wheel_control.rotate(-50);
    while(true)
    {
        obstacledetector.update_status();
        ObstacleStatusType current_status = obstacledetector.get_current_status();
        switch(current_status)
        {
            case ObstacleStatusType::far:
                wheel_control.turn(50);
                sevensegment.print(SevenSegmentGraph::number_0);
                break;
            case ObstacleStatusType::front_near:
                wheel_control.turn(-50);
                sevensegment.print(SevenSegmentGraph::number_1);
                break;
            case ObstacleStatusType::side_near:
                wheel_control.turn(-50);
                sevensegment.print(SevenSegmentGraph::number_2);
                break;
            case ObstacleStatusType::front_side_near:
                wheel_control.rotate(-50);
                sevensegment.print(SevenSegmentGraph::number_3);
                break;
        }
    }
    */
}

ISR(ADC_vect)
{
    ADConverterMUX current_mux = ad_converter.get_mux();
    switch(current_mux)
    {
        case ADConverterMUX::ADC0:
            sensor_o_c.value_update(ad_converter.get_value());
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
            ad_converter.select_input_channel(ADConverterMUX::ADC4);
            break;
        case ADConverterMUX::ADC4:
            sensor_o_r.value_update(ad_converter.get_value());
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
