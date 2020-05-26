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
#include "IOPin.hpp"

template<class pin_a, class pin_b, class pin_en, class output_compare_register> // digital, digital, pwm
class SingleWheelControl
{
public:
    SingleWheelControl(){}
    void initial(double ratio = 1);
    void set_speed(uint8_t speed, bool backward = false);
    void execute() const;
private:
    bool forward;
    uint8_t current_speed;
    double output_ratio;
    constexpr static volatile uint8_t *output_compare_register_ptr = output_compare_register::addr();
};

class WheelControl
{
public:
    WheelControl(){}
    void initial(double speed_ratio = 1);    // speed_ratio = llleft_speed / rright_speed;
    void set_speed(uint8_t llleft_speed, uint8_t rright_speed, bool llleft_backward = false, bool rright_backward = false);
    WheelControl& set_global_ratio(double ratio);
    WheelControl& keep(unsigned int time);
    WheelControl& go(uint8_t speed_amount, bool backward = false);
    WheelControl& rotate(uint8_t speed_amount, bool clockwise = false);
    WheelControl& turn(int8_t steer_amount);
private:
    SingleWheelControl<pin_PD3, pin_PD4, pin_PD5, AVR_Register_OCR0B> llleft_wheel;
    SingleWheelControl<pin_PD2, pin_PD7, pin_PD6, AVR_Register_OCR0A> rright_wheel;
    double global_ratio;
    void execute() const;
};
#endif //WHEELCONTROL_HPP

