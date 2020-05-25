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
#include <stdint.h>

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

/*
#ifndef NDEBUG
String route_status_to_str(const RouteStatusType type)
{
    switch(type)
    {
        case RouteStatusType::llleft_unknown: return "llleft_unknown";
        case RouteStatusType::llleft_on_line: return "llleft_on_line";
        case RouteStatusType::center_unknown: return "center_unknown";
        case RouteStatusType::center_on_line: return "center_on_line";
        case RouteStatusType::rright_unknown: return "rright_unknown";
        case RouteStatusType::rright_on_line: return "rright_on_line";
        case RouteStatusType::timeout:        return "timeout";
        case RouteStatusType::invalid:        return "invalid";
    }
}
#endif // NDEBUG
*/

class RouteDetector
{
public:
    RouteDetector(IrSensorTCRT5000* sensor_l, IrSensorTCRT5000* sensor_c, IrSensorTCRT5000* sensor_r): sensor_l(sensor_l), sensor_c(sensor_c), sensor_r(sensor_r) {}
    void initial();
    void update_status();
    RouteStatusType get_current_status() const;
    RouteStatusType get_last_status() const;
    unsigned long get_last_change_status_time() const;
private:
    IrSensorTCRT5000* sensor_l;
    IrSensorTCRT5000* sensor_c;
    IrSensorTCRT5000* sensor_r;
    RouteStatusType current_status, last_status;
    unsigned long last_change_status_time;
};

#endif //ROUTEDETECTOR_HPP
