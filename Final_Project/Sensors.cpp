/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#include "Sensors.hpp"
#include "Millis.hpp"

extern Millis millis;

/* BasicSensor */
void BasicSensor::value_update(uint8_t input_value)
{
    unsigned int new_value = (mix_value * 9) + input_value;
    mix_value = new_value / 10;
}

/* IrSensorTCRT5000 */
void IrSensorTCRT5000::initial(uint16_t divide, bool less_than)
{
    divide_value = divide;
    value_less_than = less_than;
}
void IrSensorTCRT5000::value_update(uint8_t input_value)
{
    BasicSensor::value_update(input_value);
    bool new_status = ( mix_value > divide_value );
    if(value_less_than) new_status = !new_status;
    if(new_status != current_status)
    {
        last_change_status_time = millis.get();
        current_status = new_status;
    }
}
bool IrSensorTCRT5000::target_detected() const
{
    return current_status;
}
unsigned long IrSensorTCRT5000::get_last_change_status_time() const
{
    return last_change_status_time;
}

/* IrSensor2Y0A21 */
uint8_t IrSensor2Y0A21::get_distance()
{
    return distance;
}
void IrSensor2Y0A21::value_update(uint8_t input_value)
{
    BasicSensor::value_update(input_value);
    uint8_t distance = 4800 / (mix_value - 20);
    if(distance > 80) distance = 81;
    if(distance < 10) distance = 9;
}

