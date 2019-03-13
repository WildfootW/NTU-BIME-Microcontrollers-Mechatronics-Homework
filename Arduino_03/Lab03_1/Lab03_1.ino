/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2019 WildfootW All rights reserved.
 *
 */

/*
 * class design for L298 H-bridge controling two DC motor wheels.
 */
#ifndef WHEEL_CONTROL_H
#define WHEEL_CONTROL_H
#define with_enable_line 0
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
    PairWheelControl(byte pin_a_left , byte pin_b_left,  byte pin_en_left,      // digital, digital, pwm
                     byte pin_a_right, byte pin_b_right, byte pin_en_right):    // digital, digital, pwm
                     left_wheel (pin_a_left,  pin_b_left,  pin_en_left),
                     right_wheel(pin_a_right, pin_b_right, pin_en_right) {}
#else
    PairWheelControl(byte pin_a_left , byte pin_b_left,                         // pwm, pwm
                     byte pin_a_right, byte pin_b_right):                       // pwm, pwm
                     left_wheel (pin_a_left,  pin_b_left),
                     right_wheel(pin_a_right, pin_b_right) {}
#endif // with_enable_line
    void initial(double speed_ratio = 1)    // speed_ratio = left_speed / right_speed;
    {
        if(speed_ratio > 1) { left_wheel.initial(1 / speed_ratio); right_wheel.initial(1);           }
        else                { left_wheel.initial(1);               right_wheel.initial(speed_ratio); }
    }
    void full_speed_ahead() { right_wheel.set_speed(255); left_wheel.set_speed(255); execute(); }
    void stop()             { right_wheel.set_speed(0);   left_wheel.set_speed(0);   execute(); }
    void right_turn()       { right_wheel.set_speed(127); left_wheel.set_speed(255); execute(); }

private:
    void execute() const { left_wheel.execute(); right_wheel.execute(); }
    WheelControl left_wheel, right_wheel;
};
#endif//WHEEL_CONTROL_H

#if with_enable_line
PairWheelControl pair_wheel(7, 8, 9, 13, 12, 11);
#else
PairWheelControl pair_wheel(5, 6, 9, 10);
#endif // with_enable_line

void setup()
{
    Serial.begin(115200);
    pair_wheel.initial(2);
}

void loop()
{
    pair_wheel.stop();
    delay(5000);
    pair_wheel.full_speed_ahead();
    delay(5000);
    pair_wheel.right_turn();
    delay(5000);
}
