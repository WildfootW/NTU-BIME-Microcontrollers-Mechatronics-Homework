/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef WHEEL_CONTROL_H
#define WHEEL_CONTROL_H
/*
 * class design for Arduino uno & L298 H-bridge controling two DC motor wheels.
 */
#include "Setting.h"

class WheelControl
{
public:
#if with_enable_line
    WheelControl(byte pin_a, byte pin_b, byte pin_en): pin_a(pin_a), pin_b(pin_b), pin_en(pin_en) {} // digital, digital, pwm
    void initial(double ratio = 1) { pinMode(pin_a, OUTPUT); pinMode(pin_b, OUTPUT); pinMode(pin_en, OUTPUT); output_ratio = ratio; }
#else
    WheelControl(byte pin_a, byte pin_b): pin_a(pin_a), pin_b(pin_b) {} // pwm, pwm
    void initial(double ratio = 1) { pinMode(pin_a, OUTPUT); pinMode(pin_b, OUTPUT); output_ratio = ratio; }
#endif // with_enable_line
    void set_speed(uint8_t speed, bool backward = false) { forward = !backward; current_speed = speed * output_ratio; }
    void execute() const
    {
#ifndef NDEBUG
        Serial.println(current_speed);
#endif // NDEBUG
#if with_enable_line
        analogWrite(pin_en, current_speed);
        if(forward) { digitalWrite(pin_a, HIGH); digitalWrite(pin_b, LOW ); }
        else        { digitalWrite(pin_a, LOW ); digitalWrite(pin_b, HIGH); }
#else
        if(forward) { analogWrite(pin_a, current_speed); digitalWrite(pin_b, LOW ); }
        else        { digitalWrite(pin_a, LOW ); analogWrite(pin_b, current_speed); }
#endif // with_enable_line
    }
private:
    const byte pin_a, pin_b;
#if with_enable_line
    const byte pin_en;
#endif // with_enable_line
    bool forward;
    uint8_t current_speed;
    double output_ratio;
};

class PairWheelControl
{
public:
#if with_enable_line
    PairWheelControl(byte pin_a_llleft, byte pin_b_llleft, byte pin_en_llleft,      // digital, digital, pwm
                     byte pin_a_rright, byte pin_b_rright, byte pin_en_rright):    // digital, digital, pwm
                     llleft_wheel(pin_a_llleft, pin_b_llleft, pin_en_llleft),
                     rright_wheel(pin_a_rright, pin_b_rright, pin_en_rright) {}
#else
    PairWheelControl(byte pin_a_llleft, byte pin_b_llleft,                         // pwm, pwm
                     byte pin_a_rright, byte pin_b_rright):                       // pwm, pwm
                     llleft_wheel(pin_a_llleft, pin_b_llleft),
                     rright_wheel(pin_a_rright, pin_b_rright) {}
#endif // with_enable_line
    void initial(double speed_ratio = 1)    // speed_ratio = llleft_speed / rright_speed;
    {
        global_ratio = 1;
        if(speed_ratio > 1) { llleft_wheel.initial(1 / speed_ratio); rright_wheel.initial(1);           }
        else                { llleft_wheel.initial(1);               rright_wheel.initial(speed_ratio); }
    }
    void set_speed(uint8_t llleft_speed, uint8_t rright_speed, bool llleft_backward = false, bool rright_backward = false) const
    {
        llleft_wheel.set_speed(llleft_speed * global_ratio, llleft_backward);
        rright_wheel.set_speed(rright_speed * global_ratio, rright_backward);
    }
    PairWheelControl& set_global_ratio(double ratio) { global_ratio = ratio ; return (*this); }
    PairWheelControl& keep(unsigned int time) { delay(time); return (*this); }

    PairWheelControl& go(uint8_t speed_amount, bool backward = false)
    {
        if(!backward) { set_speed(speed_amount, speed_amount); }
        else          { set_speed(speed_amount, speed_amount, true, true); }
        execute(); return (*this);
    }
    PairWheelControl& rotate(uint8_t speed_amount, bool clockwise = false)
    {
        if(clockwise) set_speed(speed_amount, speed_amount, false, true);
        else          set_speed(speed_amount, speed_amount, true, false);
        execute(); return (*this);
    }
    PairWheelControl& turn(int8_t steer_amount)
    {
        if(steer_amount == 0) set_speed(255, 255);
        if(steer_amount >  0) set_speed(255 - (steer_amount * 2), 255);
        if(steer_amount <  0) set_speed(255, 255 + (steer_amount * 2));
        execute(); return (*this);
    }

private:
    WheelControl llleft_wheel, rright_wheel;
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
#endif //WHEEL_CONTROL_H

