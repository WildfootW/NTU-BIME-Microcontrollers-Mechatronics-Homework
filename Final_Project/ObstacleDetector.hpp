/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef OBSTACLEDETECTOR_HPP
#define OBSTACLEDETECTOR_HPP

#include "Sensors.hpp"

enum class ObstacleStatusType
{
    far,
    front_near,
    side_near,
    front_side_near
};

class ObstacleDetector
{
public:
    ObstacleDetector(IrSensor2Y0A21* sensor_c, IrSensor2Y0A21* sensor_r): sensor_c(sensor_c), sensor_r(sensor_r){}
    void initial();
    void update_status();
    ObstacleStatusType get_current_status();
private:
    IrSensor2Y0A21* sensor_c;
    IrSensor2Y0A21* sensor_r;
    ObstacleStatusType current_status;
};

#endif //OBSTACLEDETECTOR_HPP
