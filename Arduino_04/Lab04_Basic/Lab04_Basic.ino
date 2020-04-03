/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#include "Setting.h"
#include "Wheel_Control.h"
#include "RouteDetector.h"
#include "ObstacleDetector.h"

// with enable line
//PairWheelControl pair_wheel(7, 8, 9, 13, 12, 11);
// without enable line
PairWheelControl pair_wheel(5, 6, 10, 11);

RouteDetector route_detector(A1, A2, A3);
ObstacleDetector obstacle_detector(A0);

void setup()
{
    Serial.begin(115200);
    pair_wheel.initial(1);
    route_detector.initial(350, 150, 500);
    obstacle_detector.initial();
    pair_wheel.set_global_ratio(1);
}

void loop()
{

    //pair_wheel.full_speed_ahead();
    route_detector.sensor_value_update();
    obstacle_detector.sensor_value_update();
}
