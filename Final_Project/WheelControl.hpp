/*
 * WheelControl.hpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 */

#ifndef WHEELCONTROL_HPP
#define WHEELCONTROL_HPP
/*
 * class design for Atmega328p & L298 H-bridge controling two DC motor wheels.
 * Pin: PD2, PD3, PD4, PD5, PD6, PD7
 * Timer: Timer0
 */
#include "AVRUtils.hpp"

template<class pin_a, class pin_b, class pin_en, class output_compare_register> // digital, digital, pwm
class SingleWheelControl
{
    constexpr static volatile uint8_t *output_compare_register_ptr = output_compare_register::addr();
public:
    SingleWheelControl(){}
    void initial(double ratio = 1)
    {
        pin_a::configure_pin_mode(AVRIOPinMode::Output);
        pin_b::configure_pin_mode(AVRIOPinMode::Output);
        pin_en::configure_pin_mode(AVRIOPinMode::Output);
        output_ratio = ratio;
    }
    void set_speed(uint8_t speed, bool backward = false)
    {
        forward = !backward;
        current_speed = speed * output_ratio;
    }
    void execute() const
    {
#ifndef NDEBUG
        Serial.println(current_speed);
#endif // NDEBUG
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
private:
    bool forward;
    uint8_t current_speed;
    double output_ratio;
};

class WheelControl
{
public:
    WheelControl(){}
    void initial(double speed_ratio = 1)    // speed_ratio = llleft_speed / rright_speed;
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
    void set_speed(uint8_t llleft_speed, uint8_t rright_speed, bool llleft_backward = false, bool rright_backward = false)
    {
        llleft_wheel.set_speed(llleft_speed * global_ratio, llleft_backward);
        rright_wheel.set_speed(rright_speed * global_ratio, rright_backward);
    }
    WheelControl& set_global_ratio(double ratio) { global_ratio = ratio ; return (*this); }
    WheelControl& keep(unsigned int time)
    {
        //delay(time);
        return (*this);
    }

    WheelControl& go(uint8_t speed_amount, bool backward = false)
    {
        if(!backward) { set_speed(speed_amount, speed_amount); }
        else          { set_speed(speed_amount, speed_amount, true, true); }
        execute(); return (*this);
    }
    WheelControl& rotate(uint8_t speed_amount, bool clockwise = false)
    {
        if(clockwise) set_speed(speed_amount, speed_amount, false, true);
        else          set_speed(speed_amount, speed_amount, true, false);
        execute(); return (*this);
    }
    WheelControl& turn(int8_t steer_amount)
    {
        if(steer_amount == 0) set_speed(255, 255);
        if(steer_amount >  0) set_speed(255 - (steer_amount * 2), 255);
        if(steer_amount <  0) set_speed(255, 255 + (steer_amount * 2));
        execute(); return (*this);
    }

private:
    SingleWheelControl<pin_PD3, pin_PD4, pin_PD5, AVR_Register_OCR0B> llleft_wheel;
    SingleWheelControl<pin_PD2, pin_PD7, pin_PD6, AVR_Register_OCR0A> rright_wheel;
    double global_ratio;
    void execute() const
    {
#ifndef NDEBUG
        Serial.print("llleft: ");
#endif // NDEBUG
        llleft_wheel.execute();
#ifndef NDEBUG
        Serial.print("rright: ");
#endif // NDEBUG
        rright_wheel.execute();
    }
};
#endif //WHEELCONTROL_HPP

