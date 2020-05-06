/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#ifndef TIMER_H
#define TIMER_H
typedef struct Timer0 { } Timer0;
void Timer0__timer_mode(Timer0* self);
void Timer0__compare_output_mode(Timer0* self, char output);
void Timer0__clock_selector(Timer0* self);
#endif // TIMER_H

