/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2018 WildfootW All rights reserved.
 *
 */

//#include "emg_value_1.hpp"
//#include "emg_value_2.hpp"
#include "emg_value_3.hpp"
//#include "emg_value_4.hpp"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    static size_t count = 0;

    // PROGMEM https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
    int raw_muscle_sensor_value = pgm_read_word_near(raw_value + count);

    // voltage = sensor_value * 5.0 / 1023.0;
    Serial.print("\"raw_muscle_sensor_value\": ");
    Serial.print("\"");
    Serial.print(raw_muscle_sensor_value);
    Serial.print("\"\r\n");

    ++count;
    if(count == ARR_MAX_SIZE)
        count = 0;
}

