/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef ROUTEDETECTOR_HPP
#define ROUTEDETECTOR_HPP

#include "Sensors.hpp"

enum class RouteStatusType
{
    llleft_unknown,
    llleft_on_line,
    center_unknown,
    center_on_line,
    rright_unknown,
    rright_on_line,
    timeout,
    invalid
};
#ifndef NDEBUG
String route_status_to_str(const RouteStatusType type)
{
    switch(type)
    {
        case RouteStatusType::llleft_unknown: return "llleft_unknown";
        case RouteStatusType::llleft_on_line: return "llleft_on_line";
        case RouteStatusType::center_unknown: return "center_unknown";
        case RouteStatusType::center_on_line: return "center_on_line";
        case RouteStatusType::rright_unknown: return "rright_unkonwn";
        case RouteStatusType::rright_on_line: return "rright_on_line";
        case RouteStatusType::timeout:        return "timeout";
        case RouteStatusType::invalid:        return "invalid";
    }
}
#endif // NDEBUG
class RouteDetector
{
public:
    RouteDetector(IrSensorTCRT5000* sensor_l, IrSensorTCRT5000* sensor_c, IrSensorTCRT5000* sensor_r): sensor_l(sensor_l), sensor_c(sensor_c), sensor_r(sensor_r) {}
    void initial() {}
    void update_status()
    {
        uint8_t new_status_value = 0;
        RouteStatusType new_status = RouteStatusType::invalid;
        if(sensor_l->target_detected()) { new_status_value += 1; }
        if(sensor_c->target_detected()) { new_status_value += 2; }
        if(sensor_r->target_detected()) { new_status_value += 4; }

        if(new_status_value == 0)
        {
            if(current_status == RouteStatusType::llleft_unknown || current_status == RouteStatusType::center_unknown || current_status == RouteStatusType::rright_unknown)
            {
                new_status = current_status;
            }
            else if(current_status == RouteStatusType::llleft_on_line) { new_status = RouteStatusType::llleft_unknown; }
            else if(current_status == RouteStatusType::center_on_line) { new_status = RouteStatusType::center_unknown; }
            else if(current_status == RouteStatusType::rright_on_line) { new_status = RouteStatusType::rright_unknown; }
        }
        else if(new_status_value == 1) { new_status = RouteStatusType::llleft_on_line; }
        else if(new_status_value == 2) { new_status = RouteStatusType::center_on_line; }
        else if(new_status_value == 4) { new_status = RouteStatusType::rright_on_line; }
        else
        {
            new_status = RouteStatusType::invalid;
        }
        if(new_status != current_status)
        {
            last_change_status_time = millis.get();
            last_status = current_status;
            current_status = new_status;
        }
#ifndef NDEBUG
        Serial.print(route_status_to_str(current_status) + " ");
        Serial.println(last_change_status_time);
#endif // NDEBUG
    }
    RouteStatusType get_current_status() const { return current_status; }
    RouteStatusType get_last_status() const { return last_status; }
    unsigned long get_last_change_status_time() const { return last_change_status_time; }
private:
    IrSensorTCRT5000* sensor_l;
    IrSensorTCRT5000* sensor_c;
    IrSensorTCRT5000* sensor_r;
    RouteStatusType current_status, last_status;
    unsigned long last_change_status_time;
};

#endif //ROUTEDETECTOR_HPP
