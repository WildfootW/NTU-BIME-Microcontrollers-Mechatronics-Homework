/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2019 WildfootW All rights reserved.
 *
 */

#ifndef F_CPU
#define F_CPU 1000000UL // Announce that we will use this frequency (determine by FUSE and CLKPR)
#endif

#include <avr/io.h>

/*
 * we want blink at 10Hz, so we need switch the output every (1/10)/2 second = 50 ms
 * 49 * 1024 / 1000000 = 0.050176 second
 */

int main(void)
{
    CLKPR = (1 << CLKPCE); // enable a change to CLKPR
    CLKPR = 0b00000011; // set clk to 1Mhz ( 8Mhz(Calibrated internal RC specific by FUSE) / 8(Clock Division Factor) )

    DDRD  = 0b00000001; // PD0 as output
    PORTD = 0b00000000; // initial output 0
    while(1)
    {
        TCNT0 = 206; // 255 - 49 = 206

        TCCR0A = 0b00000000; // normal mode
        TCCR0B = 0b00000101; // prescaling = 1024, start Timer

        while((TIFR0 & (1 << TOV0)) == 0); // wait for flag TOV0 == 1
        TCCR0B = 0b00000000; // stop Timer

        TIFR0 = (1 << TOV0); // clear TOV0 (important: write 1 to TOV0 bit to clear)

        PORTD = PORTD ^ 0b00000001; // switch PD0
    }
    return 0;
}
