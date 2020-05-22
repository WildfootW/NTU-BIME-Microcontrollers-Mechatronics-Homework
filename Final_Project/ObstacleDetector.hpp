/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef OBSTACLEDETECTOR_H
#define OBSTACLEDETECTOR_H

class ObstacleDetector
{
public:
    ObstacleDetector(byte pin): obstacle_sensor(pin) {}
    void initial() { obstacle_sensor.initial(); }
    void sensor_value_update()
    {
        distance = obstacle_sensor.get_distance();
#ifndef NDEBUG
        Serial.print("Obstacle :");
        Serial.print(distance);
        Serial.println(" cm");
#endif // NDEBUG
    }
    uint8_t get_distance() const { return distance; }
private:
    IrSensorSHARP obstacle_sensor;
    uint8_t distance;
};

#endif //OBSTACLEDETECTOR_H
