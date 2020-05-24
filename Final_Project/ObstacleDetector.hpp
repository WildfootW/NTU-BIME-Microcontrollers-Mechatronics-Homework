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
    void initial(){}
    void update_status()
    {
        if(sensor_c->get_distance() > 20 && sensor_r->get_distance() > 20)
            current_status = ObstacleStatusType::far;
        else if(sensor_c->get_distance() > 20)
            current_status = ObstacleStatusType::side_near;
        else if(sensor_r->get_distance() > 20)
            current_status = ObstacleStatusType::front_near;
        else
            current_status = ObstacleStatusType::front_side_near;
    }
    ObstacleStatusType get_current_status()
    {
        return current_status;
    }
private:
    IrSensor2Y0A21* sensor_c;
    IrSensor2Y0A21* sensor_r;
    ObstacleStatusType current_status;
};

#endif //OBSTACLEDETECTOR_HPP
