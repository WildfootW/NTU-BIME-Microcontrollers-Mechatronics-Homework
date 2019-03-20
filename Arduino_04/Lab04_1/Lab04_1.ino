/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2019 WildfootW All rights reserved.
 *
 */

#include "SharpIR.h"

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
        global_ratio = 1;
        if(speed_ratio > 1) { left_wheel.initial(1 / speed_ratio); right_wheel.initial(1);           }
        else                { left_wheel.initial(1);               right_wheel.initial(speed_ratio); }
    }
    void set_speed(uint8_t left_speed, uint8_t right_speed, bool left_backward = false, bool right_backward = false) const
    {
         left_wheel.set_speed( left_speed * global_ratio,  left_backward);
        right_wheel.set_speed(right_speed * global_ratio, right_backward);
    }
    PairWheelControl& set_global_ratio(double ratio) { global_ratio = ratio ; return (*this); }
    PairWheelControl& keep(unsigned int time) { delay(time); return (*this); }
    PairWheelControl& full_speed_ahead() { set_speed(255, 255);               execute(); return (*this); }
    PairWheelControl& stop()             { set_speed(  0,   0);               execute(); return (*this); }
    PairWheelControl& right_rotate()     { set_speed(255, 255, false, true);  execute(); return (*this); }
    PairWheelControl& turn(int8_t steer_amount)
    {
        if(steer_amount == 0)
            set_speed(255, 255);
        else if(steer_amount > 0)
            set_speed(255 - (steer_amount * 2), 255);
        else
            set_speed(255, 255 + (steer_amount * 2));
        execute();
        return (*this);
    }

private:
    WheelControl left_wheel, right_wheel;
    double global_ratio;
    void execute() const
    {
#ifndef NDEBUG
        Serial.print("left : ");
#endif // NDEBUG
        left_wheel.execute();
#ifndef NDEBUG
        Serial.print("right: ");
#endif // NDEBUG
        right_wheel.execute();
    }
};
#endif//WHEEL_CONTROL_H

class BasicSensor
{
public:
    BasicSensor(byte pin): pin(pin) {}
    void initial(uint16_t divide, bool less_than = false) { pinMode(pin, INPUT); divide_value = divide; value_less_than = less_than; }
    void value_update()
    {
        unsigned int new_value = (mix_value * 9) + analogRead(pin);
        mix_value = new_value / 10;
#ifndef NDEBUG
        Serial.print(mix_value);
#endif // NDEBUG
        bool new_status = ( mix_value > divide_value );
        if(value_less_than) new_status = !new_status;
        if(new_status != current_status)
        {
            last_change_status_time = millis();
            current_status = new_status;
        }
#ifndef NDEBUG
        Serial.print(" ");
        Serial.println(current_status);
#endif // NDEBUG
    }
    bool target_detected() const { return current_status; }
    unsigned long get_last_change_status_time() const { return last_change_status_time; }
protected:
    bool current_status;
    bool value_less_than;
    const byte pin;
    uint16_t divide_value;
    uint16_t mix_value;
    unsigned long last_change_status_time;
};
class IrSensor: public BasicSensor
{
public:
    IrSensor(byte pin): BasicSensor(pin) {}
    void value_update() { Serial.print(" IR :"); BasicSensor::value_update(); }
};
class RouteDetector
{
public:
    RouteDetector(byte pin_l, byte pin_c, byte pin_r): sensor_l(pin_l), sensor_c(pin_c), sensor_r(pin_r) {}
    void initial(uint16_t divide_l, uint16_t divide_c, uint16_t divide_r) { sensor_l.initial(divide_l); sensor_c.initial(divide_c); sensor_r.initial(divide_r); }
    void sensor_value_update()
    {
#ifndef NDEBUG
        Serial.print("left  :");
#endif // NDEBUG
        sensor_l.value_update();
#ifndef NDEBUG
        Serial.print("center:");
#endif // NDEBUG
        sensor_c.value_update();
#ifndef NDEBUG
        Serial.print("right :");
#endif // NDEBUG
        sensor_r.value_update();
    }
    int8_t get_suggest_action() // return from -127(right) ~ 127(left) and 128 for invalid
    {
        bool l = sensor_l.target_detected();
        bool c = sensor_c.target_detected();
        bool r = sensor_r.target_detected();
        unsigned long l_t = sensor_l.get_last_change_status_time();
        unsigned long c_t = sensor_c.get_last_change_status_time();
        unsigned long r_t = sensor_r.get_last_change_status_time();
        unsigned long current_t = millis();
        int8_t ret = 0;
        if(c)
        {
            ret = 0;
            if(current_t - l_t < 2500)
                ret = -40;
            else if(current_t - r_t < 2500)
                ret = 40;
        }
        else if(l)
        {
            if(current_t - c_t < 300)
                ret = 60;
            else
                ret = 0;
        }
        else if(r)
        {
            if(current_t - c_t < 300)
                ret = -60;
            else
                ret = 0;
        }
        else
        {
            if(l_t > r_t)
                ret = 127;
            else if(l_t < r_t)
                ret = -127;
            if(current_t - l_t > 1000 && current_t - c_t > 1000 && current_t - r_t > 1000)
                ret = 128; // invalid
        }
        Serial.print("Suggest action: ");
        Serial.println(ret);
        return ret;
    }
private:
    IrSensor sensor_l, sensor_c, sensor_r;
};
class ObstacleDetector: public SharpIR
{
public:
    ObstacleDetector(byte pin): SharpIR(GP2Y0A21YK0F, pin) {}
    void sensor_value_update()
    {
        distance = getDistance();
#ifndef NDEBUG
        Serial.print("Obstacle :");
        Serial.print(distance);
        Serial.println(" cm");
#endif // NDEBUG
    }
    void initial(uint8_t distance) { pinMode(pin, INPUT); divide_distance = distance; }
    bool target_detected() const
    {
        return distance < divide_distance;
    }
private:
    uint8_t distance;
    uint8_t divide_distance;
};

#if with_enable_line
PairWheelControl pair_wheel(7, 8, 9, 13, 12, 11);
#else
PairWheelControl pair_wheel(5, 6, 9, 10);
#endif // with_enable_line

RouteDetector route_detector(A1, A2, A3);
ObstacleDetector obstacle_detector(A0);

void setup()
{
    Serial.begin(115200);
    pair_wheel.initial(1);
    route_detector.initial(500, 100, 500);
    obstacle_detector.initial(10);
    pair_wheel.set_global_ratio(1);
}

void loop()
{
    //pair_wheel.full_speed_ahead();
    route_detector.sensor_value_update();
    obstacle_detector.sensor_value_update();

    int8_t route_suggest_action = route_detector.get_suggest_action();
    if(obstacle_detector.target_detected())
        pair_wheel.stop();
    else
    {
        //pair_wheel.set_global_ratio(1 - (route_suggest_action / 255));
        pair_wheel.turn(route_suggest_action);
    }
}
