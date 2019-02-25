/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2019 WildfootW All rights reserved.
 *
 */
#include "pitches.h"

const int buzzer_pin = 8;
const unsigned int buttom_num = 7;
unsigned int pressed_buttom_index;
const int buttom_pin[buttom_num] = {A0, A1, A2, A3, A4, A5, 2};
int melody[buttom_num] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4 };

void setup()
{
    for(unsigned int i = 0;i < buttom_num;++i)
    {
        pinMode(buttom_pin[i], INPUT);
    }
    //Serial.begin(115200);
    Serial.begin(9600);
}

void loop()
{
    
    for(unsigned int i = 0;i < buttom_num + 1;++i)
    {
        if(i == buttom_num)
            pressed_buttom_index = buttom_num;

        if(digitalRead(buttom_pin[i]))
        {
            pressed_buttom_index = i;
            break;
        }
    }
    //String log = String(pressed_buttom_index);
    //Serial.write(log);
    Serial.print(pressed_buttom_index);
    //Serial.print(buttom_num);
    if(pressed_buttom_index == buttom_num)
    {
        Serial.write(" No Tone\n");
        noTone(buzzer_pin);
    }
    else
    {
        Serial.write(" Bee\n");
        tone(buzzer_pin, melody[pressed_buttom_index]);
    }
}
