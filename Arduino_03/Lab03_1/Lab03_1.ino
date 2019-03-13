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
    void initial(double ratio = 1) { pinMode(pin_a, OUTPUT); pinMode(pin_b, OUTPUT); pinMode(pin_en, OUTPUT); output_ratio = ratio; }
    void set_speed(uint8_t speed, bool backward = false) const
    {
        analogWrite(pin_en, speed * output_ratio);
        Serial.println(speed * output_ratio);
        if(speed == 0)    { digitalWrite(pin_a, HIGH); digitalWrite(pin_b, HIGH); }
        else if(backward) { digitalWrite(pin_a, LOW ); digitalWrite(pin_b, HIGH); }
        else              { digitalWrite(pin_a, HIGH); digitalWrite(pin_b, LOW ); }
    }
private:
    const byte pin_a, pin_b, pin_en;
    double output_ratio;
};

class pair_wheel_control
{
public:
    pair_wheel_control(byte pin_a_left , byte pin_b_left,  byte pin_en_left,
                       byte pin_a_right, byte pin_b_right, byte pin_en_right):
                       left_wheel (pin_a_left,  pin_b_left,  pin_en_left),
                       right_wheel(pin_a_right, pin_b_right, pin_en_right) {}
    void initial(double speed_ratio = 1)    // speed_ratio = left_speed / right_speed;
    {
        if(speed_ratio > 1)
        {
             left_wheel.initial(1 / speed_ratio);
            right_wheel.initial(1);
        }
        else
        {
             left_wheel.initial(1);
            right_wheel.initial(speed_ratio);
        }
    }
    void full_speed_ahead() const { right_wheel.set_speed(255); left_wheel.set_speed(255); }
    void stop()             const { right_wheel.set_speed(0);   left_wheel.set_speed(0);   }
    void right_turn()       const { right_wheel.set_speed(127); left_wheel.set_speed(255); }

private:
    wheel_control left_wheel, right_wheel;
};
#endif//WHEEL_CONTROL_H

pair_wheel_control pair_wheel(8, 9, 10, 13, 12, 11);

void setup()
{
    Serial.begin(115200);
    //pair_wheel.initial(0.19215686274); // 49/255
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
