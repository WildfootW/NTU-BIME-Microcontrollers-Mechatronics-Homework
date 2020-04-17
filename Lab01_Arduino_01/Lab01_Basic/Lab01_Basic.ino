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
class piano_key
{
public:
    piano_key(int pin, int melody): pin(pin), melody(melody) {}
    int pin, melody;
};
const piano_key piano_keys[buttom_num] = {
    {A0, NOTE_C4},
    {A1, NOTE_D4},
    {A2, NOTE_E4},
    {A3, NOTE_F4},
    {A4, NOTE_G4},
    {A5, NOTE_A4},
    { 2, NOTE_B4},
};

//unsigned int pressed_buttom_index; // [TODO] find out why declare this variable in loop() will make "if statement" failed

void setup()
{
    for(unsigned int i = 0;i < buttom_num;++i)
    {
        pinMode(piano_keys[i].pin, INPUT);
    }
    Serial.begin(115200);
}

void loop()
{
    int pressed_buttom_index = -1;
    //unsigned int pressed_buttom_index;
    for(unsigned int i = 0;i < buttom_num;++i)
    {
        if(digitalRead(piano_keys[i].pin))
        {
            pressed_buttom_index = i;
            break;
        }
    }

    Serial.print(pressed_buttom_index);
    if(pressed_buttom_index == -1)
    {
        Serial.write(" No Tone\n");
        noTone(buzzer_pin);
    }
    else
    {
        Serial.write(" Bee\n");
        tone(buzzer_pin, piano_keys[pressed_buttom_index].melody);
    }
}
