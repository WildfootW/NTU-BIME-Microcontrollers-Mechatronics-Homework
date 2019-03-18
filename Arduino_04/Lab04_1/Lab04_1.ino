/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2019 WildfootW All rights reserved.
 *
 */

void setup()
{
    Serial.begin(115200); // initialize serial communication at 9600 bits per second
    pinMode(A0, INPUT);
}

void loop()
{
    uint16_t sensorValue = analogRead(A0);  // read the input on analog pin 0
    Serial.println(sensorValue);            // print out the value you read
    delay(100);                             // wait for 1000 milliseconds
}
