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

class ObstacleDetector
{
public:
    ObstacleDetector(IrSensor2Y0A21* sensor_o): sensor_o(sensor_o){}
    void initial(){}
    uint8_t get_distance() const { return sensor_o->get_distance(); }
private:
    IrSensor2Y0A21* sensor_o;
};

#endif //OBSTACLEDETECTOR_HPP
