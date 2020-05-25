/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#include "ObstacleDetector.hpp"

void ObstacleDetector::initial(){}
void ObstacleDetector::update_status()
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
ObstacleStatusType ObstacleDetector::get_current_status()
{
    return current_status;
}

