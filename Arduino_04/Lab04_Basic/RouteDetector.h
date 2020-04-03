/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef ROUTEDETECTOR_H
#define ROUTEDETECTOR_H

#include "Setting.h"
#include "My_Sensor.h"

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

#endif //ROUTEDETECTOR_H
