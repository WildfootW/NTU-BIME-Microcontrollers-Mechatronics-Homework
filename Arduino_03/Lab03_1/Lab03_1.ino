/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2019 WildfootW All rights reserved.
 *
 */

#ifndef WHEEL_CONTROL_H
#define WHEEL_CONTROL_H
class wheel_control
{
public:
    wheel_control(byte pin_a, byte pin_b, byte pin_en): pin_a(pin_a), pin_b(pin_b), pin_en(pin_en) {}
    void initial() const { pinMode(pin_a, OUTPUT); pinMode(pin_b, OUTPUT); pinMode(pin_en, OUTPUT); }
    void set_speed(uint8_t speed, bool backward = false) const
    {
        if(speed == 0)    { digitalWrite(pin_a, HIGH); digitalWrite(pin_b, HIGH); }
        else if(backward) { digitalWrite(pin_a, LOW ); digitalWrite(pin_b, HIGH); }
        else              { digitalWrite(pin_a, HIGH); digitalWrite(pin_b, LOW ); }
        analogWrite(pin_en, speed);
    }
private:
    const byte pin_a, pin_b, pin_en;
};

class pair_wheel_control
{
public:
    pair_wheel_control(byte pin_a_left , byte pin_b_left,  byte pin_en_left,
                       byte pin_a_right, byte pin_b_right, byte pin_en_right):
                       left_wheel (pin_a_left,  pin_b_left,  pin_en_left),
                       right_wheel(pin_a_right, pin_b_right, pin_en_right) {}
    void initial() const { left_wheel.initial(); right_wheel.initial(); }
    void full_speed_ahead() const { left_wheel.set_speed(255);  right_wheel.set_speed(255); }
    void stop()             const { left_wheel.set_speed(0);    right_wheel.set_speed(0);   }
    void right_turn()       const { left_wheel.set_speed(255);  right_wheel.set_speed(127); }

private:
    wheel_control left_wheel, right_wheel;
};
#endif//WHEEL_CONTROL_H

pair_wheel_control pair_wheel(8, 9, 10, 13, 12, 11);

void setup()
{
    pair_wheel.initial();
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
