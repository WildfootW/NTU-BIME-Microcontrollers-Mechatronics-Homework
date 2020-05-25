/*
 * WheelControl.hpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 */

#include "WheelControl.hpp"

template<class pin_a, class pin_b, class pin_en, class output_compare_register>
void SingleWheelControl<pin_a, pin_b, pin_en, output_compare_register>::initial(double ratio)
{
    pin_a::configure_pin_mode(AVRIOPinMode::Output);
    pin_b::configure_pin_mode(AVRIOPinMode::Output);
    pin_en::configure_pin_mode(AVRIOPinMode::Output);
    output_ratio = ratio;
}

template<class pin_a, class pin_b, class pin_en, class output_compare_register>
void SingleWheelControl<pin_a, pin_b, pin_en, output_compare_register>::set_speed(uint8_t speed, bool backward)
{
    forward = !backward;
    current_speed = speed * output_ratio;
}

template<class pin_a, class pin_b, class pin_en, class output_compare_register>
void SingleWheelControl<pin_a, pin_b, pin_en, output_compare_register>::execute() const
{
    *output_compare_register_ptr = current_speed;
    if(forward)
    {
        pin_a::set_output(true);
        pin_b::set_output(false);
    }
    else
    {
        pin_a::set_output(false);
        pin_b::set_output(true);
    }
}

void WheelControl::initial(double speed_ratio)
{
    TCCR0A = 0b10100011; // fast PWM, non-inverted
    TCCR0B = 0b00000011; // timer prescaler ( clk / 64 )
    global_ratio = 1;
    if(speed_ratio > 1)
    {
        llleft_wheel.initial(1 / speed_ratio);
        rright_wheel.initial(1);
    }
    else
    {
        llleft_wheel.initial(1);
        rright_wheel.initial(speed_ratio);
    }
}

void WheelControl::set_speed(uint8_t llleft_speed, uint8_t rright_speed, bool llleft_backward, bool rright_backward)
{
    llleft_wheel.set_speed(llleft_speed * global_ratio, llleft_backward);
    rright_wheel.set_speed(rright_speed * global_ratio, rright_backward);
}

WheelControl& WheelControl::set_global_ratio(double ratio)
{
    global_ratio = ratio;
    return (*this);
}

WheelControl& WheelControl::keep(unsigned int time)
{
    //delay(time);
    return (*this);
}

WheelControl& WheelControl::go(uint8_t speed_amount, bool backward)
{
    if(!backward) { set_speed(speed_amount, speed_amount); }
    else          { set_speed(speed_amount, speed_amount, true, true); }
    execute(); return (*this);
}

WheelControl& WheelControl::rotate(uint8_t speed_amount, bool clockwise)
{
    if(clockwise) set_speed(speed_amount, speed_amount, false, true);
    else          set_speed(speed_amount, speed_amount, true, false);
    execute(); return (*this);
}

WheelControl& WheelControl::turn(int8_t steer_amount)
{
    if(steer_amount == 0) set_speed(255, 255);
    if(steer_amount >  0) set_speed(255 - (steer_amount * 2), 255);
    if(steer_amount <  0) set_speed(255, 255 + (steer_amount * 2));
    execute(); return (*this);
}

void WheelControl::execute() const
{
    llleft_wheel.execute();
    rright_wheel.execute();
}

