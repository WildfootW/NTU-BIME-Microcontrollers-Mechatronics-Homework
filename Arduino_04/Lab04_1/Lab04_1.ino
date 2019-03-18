/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2019 WildfootW All rights reserved.
 *
 */

#ifndef WHEEL_CONTROL_H
#define WHEEL_CONTROL_H
/*
 * class design for Arduino uno & L298 H-bridge controling two DC motor wheels.
 */
#define with_enable_line 1
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
    PairWheelControl& keep(unsigned int time) { delay(time); return (*this); }
    PairWheelControl& full_speed_ahead() { right_wheel.set_speed(255);       left_wheel.set_speed(255); execute(); return (*this); }
    PairWheelControl& stop()             { right_wheel.set_speed(  0);       left_wheel.set_speed(  0); execute(); return (*this); }
    PairWheelControl& right_turn()       { right_wheel.set_speed( 63);       left_wheel.set_speed(255); execute(); return (*this); }
    PairWheelControl& right_rotate()     { right_wheel.set_speed(255, true); left_wheel.set_speed(255); execute(); return (*this); }

private:
    void execute() const { left_wheel.execute(); right_wheel.execute(); }
    WheelControl left_wheel, right_wheel;
};
#endif//WHEEL_CONTROL_H

#ifndef ROUTE_DETECTOR
#define ROUTE_DETECTOR
class IrSensor
{
public:
    IrSensor(byte pin): pin(pin) {}
    void initial(uint16_t divide) { pinMode(pin, INPUT); divide_value = divide; }
    bool target_detected() const
    {
        uint16_t sensor_value = analogRead(pin);
        Serial.println(sensor_value);
        return sensor_value > divide_value;
    }
private:
    const byte pin;
    uint16_t divide_value;
};
class RouteDetector
{
public:
    RouteDetector(byte pin_l, byte pin_c, byte pin_r): sensor_l(pin_l), sensor_c(pin_c), sensor_r(pin_r) {}
    void initial(uint16_t divide) { sensor_l.initial(divide); sensor_c.initial(divide); sensor_r.initial(divide); }
    int8_t get_suggest_action()
    {
        sensor_l.target_detected();
        sensor_c.target_detected();
        sensor_r.target_detected();
        return 0;
    }
private:
    IrSensor sensor_l, sensor_c, sensor_r;
};
#endif//ROUTE_DETECTOR

#if with_enable_line
PairWheelControl pair_wheel(7, 8, 9, 13, 12, 11);
#else
PairWheelControl pair_wheel(5, 6, 9, 10);
#endif // with_enable_line

RouteDetector route_detector(A1, A2, A3);

void setup()
{
    Serial.begin(115200);
    pair_wheel.initial(1.15);
    route_detector.initial(500);
}

void loop()
{
    //pair_wheel.stop().keep(5000);
    //pair_wheel.full_speed_ahead().keep(1000).right_rotate().keep(150);
    //pair_wheel.full_speed_ahead().keep( 500).right_rotate().keep(150);
    //pair_wheel.full_speed_ahead().keep(1000).right_rotate().keep(150);
    //pair_wheel.full_speed_ahead().keep( 500).right_rotate().keep(150);
    //pair_wheel.full_speed_ahead().keep( 500);
    route_detector.get_suggest_action();
}
