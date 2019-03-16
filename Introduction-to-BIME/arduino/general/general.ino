/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2018 WildfootW All rights reserved.
 *
 */

void setup()
{
    Serial.begin(115200);
}
void loop()
{
    int muscle_sensor_value = analogRead(A0);

    // voltage = sensor_value * 5.0 / 1023.0;
    Serial.print("\"muscle_sensor_value\": ");
    Serial.print("\"");
    Serial.print(muscle_sensor_value);
    Serial.print("\"\r\n");

    int raw_muscle_sensor_value = analogRead(A1);
    Serial.print("\"raw_muscle_sensor_value\": ");
    Serial.print("\"");
    Serial.print(raw_muscle_sensor_value);
    Serial.print("\"\r\n");
}

