/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#include <avr/io.h>
#include "ClockPrescale.h"
#include "assert.h"

void ClockPrescale__change_enable(ClockPrescale* self)
{
    CLKPR |= CLKPCE << 1;
}
void ClockPrescale__select(ClockPrescale* self, uint16_t prescale)
{
    if(prescale == 8)
    {
        CLKPR |= CLKPS0 << 1;
        CLKPR |= CLKPS1 << 1;
    }
    assert(1);
}
