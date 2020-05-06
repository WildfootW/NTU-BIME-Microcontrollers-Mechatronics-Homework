/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#include "Timer.h"
void Timer0__init(Timer0* self)
{
    TCCR0A = 0b10100001;
    TCCR0B = 0b00000010;
}
void Timer0__compare_output_mode(Timer0* self, char output)
void Timer0__clock_selector(Timer0* self);

