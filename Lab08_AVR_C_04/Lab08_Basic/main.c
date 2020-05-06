/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include "ClockPrescale.h"
#include "Timer.h"

void initial()
{
    DDRD = 0xff;
    DDRB = 0xff;
    ClockPrescale clk;
    ClockPrescale__change_enable(&clk);
    ClockPrescale__select(&clk, 8);
}

int main()
{

    return 0;
}

