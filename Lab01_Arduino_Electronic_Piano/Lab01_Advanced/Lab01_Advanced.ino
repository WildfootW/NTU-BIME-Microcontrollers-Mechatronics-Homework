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


class note
{
public:
    note(int frequency, int duration): frequency(frequency), duration(duration) {}
    int frequency, duration;
};

const int buzzer_pin = 8;

// note durations: 4 = quarter note, 8 = eighth note, etc.:
note melody[] = {
    {NOTE_C4, 4},
    {NOTE_C4, 4},
    {NOTE_G4, 4},
    {NOTE_G4, 4},
    {NOTE_A4, 4},
    {NOTE_A4, 4},
    {NOTE_G4, 4},
    {      0, 4},
    {NOTE_F4, 4},
    {NOTE_F4, 4},
    {NOTE_E4, 4},
    {NOTE_E4, 4},
    {NOTE_D4, 4},
    {NOTE_D4, 4},
    {NOTE_C4, 4},
    {      0, 4},
    {NOTE_G4, 4},
    {NOTE_G4, 4},
    {NOTE_F4, 4},
    {NOTE_F4, 4},
    {NOTE_E4, 4},
    {NOTE_E4, 4},
    {NOTE_D4, 4},
    {      0, 4},
    {NOTE_G4, 4},
    {NOTE_G4, 4},
    {NOTE_F4, 4},
    {NOTE_F4, 4},
    {NOTE_E4, 4},
    {NOTE_E4, 4},
    {NOTE_D4, 4},
    {      0, 4},
    {NOTE_C4, 4},
    {NOTE_C4, 4},
    {NOTE_G4, 4},
    {NOTE_G4, 4},
    {NOTE_A4, 4},
    {NOTE_A4, 4},
    {NOTE_G4, 4},
    {      0, 4},
    {NOTE_F4, 4},
    {NOTE_F4, 4},
    {NOTE_E4, 4},
    {NOTE_E4, 4},
    {NOTE_D4, 4},
    {NOTE_D4, 4},
    {NOTE_C4, 4},
    {      0, 4},
};

void setup()
{
    // iterate over the notes of the melody:
    for(int i = 0;i < 48;++i)
    {
        // to calculate the note duration, take one second divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int length = 1000 / melody[i].duration;
        tone(buzzer_pin, melody[i].frequency, length);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        delay(length * 1.30);

        // stop the tone playing:
        noTone(8);
    }
}

void loop()
{
    // no need to repeat the melody.
}
