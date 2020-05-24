/*
 * main.cpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#include <avr/interrupt.h>
#include "AVRUtils.hpp"

/*
#include "Usart.hpp"
Usart usart(9600);
*/

#include "Millis.hpp"
Millis millis; // Timer1

#include "ADConverter.hpp"
ADConverter ad_converter; // PC0, 1, 2, 3

#include "Sensors.hpp"
#include "RouteDetector.hpp"
#include "ObstacleDetector.hpp"
#include "WheelControl.hpp"

WheelControl wheel_control; // PD3, 4, 5. PD2, 7, 6. Timer0
IrSensor2Y0A21 sensor_o_c; // PC0
IrSensorTCRT5000 sensor_l; // PC1
IrSensorTCRT5000 sensor_c; // PC2
IrSensorTCRT5000 sensor_r; // PC3
IrSensor2Y0A21 sensor_o_r; // PC4
RouteDetector routedetector(&sensor_l, &sensor_c, &sensor_r);
ObstacleDetector obstacledetector(&sensor_o_c, &sensor_o_r);
#include "SevenSegment.hpp"
SevenSegment sevensegment;

void initial()
{
    sevensegment.print(SevenSegmentGraph::off);
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

    wheel_control.initial();

    sensor_l.initial(200);
    sensor_c.initial(150);
    sensor_r.initial(230);

    obstacledetector.initial();
    routedetector.initial();

    sevensegment.initial();
}

int main(void)
{
    initial();

    ad_converter.start();

    /*
    while(true)
    {
        char hello[] = "Hello World!\n";
        usart.put_str(hello);
    }
    */

    //wheel_control.set_global_ratio(0.5);
    /*
    while(true)
    {
        routedetector.update_status();
        RouteStatusType current_status = routedetector.get_current_status();
        switch(current_status)
        {
            case RouteStatusType::center_on_line:
                wheel_control.go(255);
                sevensegment.print(SevenSegmentGraph::number_2);
                break;
            case RouteStatusType::llleft_on_line:
                wheel_control.turn(70);
                sevensegment.print(SevenSegmentGraph::number_1);
                break;
            case RouteStatusType::center_unknown:
                wheel_control.go(50);
                sevensegment.print(SevenSegmentGraph::number_5);
                break;
            case RouteStatusType::rright_unknown:
                wheel_control.turn(-100);
                sevensegment.print(SevenSegmentGraph::number_6);
                break;
            case RouteStatusType::llleft_unknown:
                wheel_control.turn(100);
                sevensegment.print(SevenSegmentGraph::number_4);
                break;
            case RouteStatusType::rright_on_line:
                wheel_control.turn(-70);
                sevensegment.print(SevenSegmentGraph::number_3);
                break;
            case RouteStatusType::invalid:
                wheel_control.go(150);
                sevensegment.print(SevenSegmentGraph::number_7);
                break;
        }
    }
    */
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
