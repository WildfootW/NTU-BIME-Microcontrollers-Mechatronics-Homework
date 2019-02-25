# Lab01
Electronic Piano

## Contribution
B07611012: 50%
B07611040: 50%

## Basic points

```
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
```

## Advanced points

```
/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 0,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 0,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 48; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
```
