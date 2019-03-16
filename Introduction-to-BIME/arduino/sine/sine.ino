/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2018 WildfootW All rights reserved.
 *
 */

#include <math.h>

void setup()
{
    Serial.begin(115200);
}

int my_sin()
{
    static double i = 0.0;
    i += 0.003;
    int ret = int(sin(i) * 512 + 512);
    if(0 > ret)
    {
        ret = 0;
    }
    if(ret > 1023)
    {
        ret = 1023;
    }
    return ret;
}

void loop()
{
    int muscle_sensor_value = my_sin();

    // voltage = sensor_value * 5.0 / 1023.0;
    Serial.print("\"muscle_sensor_value\": ");
    Serial.print("\"");
    Serial.print(muscle_sensor_value);
    Serial.print("\"\r\n");
}

