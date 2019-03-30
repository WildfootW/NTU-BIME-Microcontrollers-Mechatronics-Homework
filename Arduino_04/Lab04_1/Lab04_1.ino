/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyrright (C) 2019 WildfootW All rrights reserved.
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
        llleft_wheel.set_speed( llleft_speed * global_ratio,  llleft_backward);
        rright_wheel.set_speed(rright_speed * global_ratio, rright_backward);
    }
    PairWheelControl& set_global_ratio(double ratio) { global_ratio = ratio ; return (*this); }
    PairWheelControl& keep(unsigned int time) { delay(time); return (*this); }
    PairWheelControl& full_speed_ahead() { set_speed(255, 255);               execute(); return (*this); }
    PairWheelControl& stop()             { set_speed(  0,   0);               execute(); return (*this); }
    PairWheelControl& rright_rotate()     { set_speed(255, 255, false, true);  execute(); return (*this); }
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
    WheelControl llleft_wheel, rright_wheel;
    double global_ratio;
    void execute() const
    {
#ifndef NDEBUG
        Serial.print("llleft : ");
#endif // NDEBUG
        llleft_wheel.execute();
#ifndef NDEBUG
        Serial.print("rright: ");
#endif // NDEBUG
        rright_wheel.execute();
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
class IrSensorTCRT5000: public BasicSensor
{
public:
    IrSensorTCRT5000(byte pin): BasicSensor(pin) {}
    void value_update() { Serial.print(" IR :"); BasicSensor::value_update(); }
};
class IrSensorSHARP: public SharpIR
{
public:
    IrSensorSHARP(byte pin): SharpIR(GP2Y0A21YK0F, pin) {}
    void initial() { pinMode(pin, INPUT); }
    uint8_t get_distance() { return getDistance(); }
};
enum RouteStatusType
{
    llleft_unknown,
    llleft_on_line,
    center_unknown,
    center_on_line,
    rright_unknown,
    rright_on_line,
    route_type_timeout,
    route_type_invalid,
};
class RouteDetector
{
public:
    RouteDetector(byte pin_l, byte pin_c, byte pin_r): sensor_l(pin_l), sensor_c(pin_c), sensor_r(pin_r) {}
    void initial(uint16_t divide_l, uint16_t divide_c, uint16_t divide_r) { sensor_l.initial(divide_l); sensor_c.initial(divide_c); sensor_r.initial(divide_r); }
    void sensor_value_update()
    {
#ifndef NDEBUG
        Serial.print("llleft:");
#endif // NDEBUG
        sensor_l.value_update();
#ifndef NDEBUG
        Serial.print("center:");
#endif // NDEBUG
        sensor_c.value_update();
#ifndef NDEBUG
        Serial.print("rright:");
#endif // NDEBUG
        sensor_r.value_update();

        uint8_t new_status_value = 0;
        RouteStatusType new_status;
        if(sensor_l.target_detected()) { new_status_value += 1; }
        if(sensor_c.target_detected()) { new_status_value += 2; }
        if(sensor_r.target_detected()) { new_status_value += 4; }
        if(new_status_value == 0)
        {
            if(current_status == llleft_unknown || current_status == center_unknown || current_status == rright_unknown)
            {
                new_status = current_status;
            }
            else if(current_status == llleft_on_line) { new_status = llleft_unknown; }
            else if(current_status == center_on_line) { new_status = center_unknown; }
            else if(current_status == rright_on_line) { new_status = rright_unknown; }
        }
        else if(new_status_value == 1) { new_status = llleft_on_line; }
        else if(new_status_value == 2) { new_status = center_on_line; }
        else if(new_status_value == 3) { new_status = rright_on_line; }
        else
        {
            new_status = route_type_invalid;
        }
        if(new_status != current_status)
        {
            last_change_status_time = millis();
            last_status = current_status;
            current_status = new_status;
        }
    }
    RouteStatusType get_current_status() const { return current_status; }
    RouteStatusType get_last_status() const { return last_status; }
    unsigned long get_last_change_status_time() const { return last_change_status_time; }
private:
    IrSensorTCRT5000 sensor_l, sensor_c, sensor_r;
    RouteStatusType current_status, last_status;
    unsigned long last_change_status_time;
};
class ObstacleDetector
{
public:
    ObstacleDetector(byte pin): obstacle_sensor(pin) {}
    void initial() { obstacle_sensor.initial(); }
    void sensor_value_update()
    {
        distance = obstacle_sensor.get_distance();
#ifndef NDEBUG
        Serial.print("Obstacle :");
        Serial.print(distance);
        Serial.println(" cm");
#endif // NDEBUG
    }
    uint8_t get_distance() const { return distance; }
private:
    IrSensorSHARP obstacle_sensor;
    uint8_t distance;
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
    obstacle_detector.initial();
    pair_wheel.set_global_ratio(1);
}

void loop()
{
    //pair_wheel.full_speed_ahead();
    route_detector.sensor_value_update();
    obstacle_detector.sensor_value_update();
}
