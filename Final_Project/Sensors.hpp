/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

class BasicSensor
{
public:
    BasicSensor(){}
    void value_update(uint8_t input_value);
protected:
    uint16_t mix_value;
};

class IrSensorTCRT5000: public BasicSensor
{
public:
    IrSensorTCRT5000(){}
    void initial(uint16_t divide, bool less_than = false);
    void value_update(uint8_t input_value);
    bool target_detected() const;
    unsigned long get_last_change_status_time() const;
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
    uint8_t get_distance();
    void value_update(uint8_t input_value);
private:
    unsigned long last_read_time;
    uint8_t distance;
};

#endif //SENSORS_H
