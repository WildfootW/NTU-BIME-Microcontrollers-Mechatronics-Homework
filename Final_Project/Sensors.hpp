/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef SENSORS_H
#define SENSORS_H

#include "Millis.hpp"

class BasicSensor
{
public:
    BasicSensor(){}

    void value_update(uint8_t input_value)
    {
        unsigned int new_value = (mix_value * 9) + input_value;
        mix_value = new_value / 10;
#ifndef NDEBUG
        Serial.print(mix_value);
#endif // NDEBUG
    }
protected:
    uint16_t mix_value;
};

class IrSensorTCRT5000: public BasicSensor
{
public:
    IrSensorTCRT5000(){}
    void initial(uint16_t divide, bool less_than = false)
    {
        divide_value = divide;
        value_less_than = less_than;
    }
    void value_update(uint8_t input_value)
    {
        BasicSensor::value_update(input_value);
        bool new_status = ( mix_value > divide_value );
        if(value_less_than) new_status = !new_status;
        if(new_status != current_status)
        {
            last_change_status_time = millis.get();
            current_status = new_status;
        }
#ifndef NDEBUG
        Serial.print(" ");
        Serial.println(current_status);
#endif // NDEBUG
    }
    bool target_detected() const { return current_status; }
    unsigned long get_last_change_status_time() const { return last_change_status_time; }
private:
    bool current_status;
    bool value_less_than;
    uint16_t divide_value;
    unsigned long last_change_status_time;
};

class IrSensor2Y0A21: public BasicSensor
{
public:
    IrSensor2Y0A21(){}
    uint8_t get_distance()
    {
        return distance;
    }
    void value_update(uint8_t input_value)
    {
        BasicSensor::value_update(input_value);
        uint8_t distance = 4800 / (mix_value - 20);
        if(distance > 80) distance = 81;
        if(distance < 10) distance = 9;
    }
private:
    unsigned long last_read_time;
    uint8_t distance;
};

#endif //SENSORS_H
