/*
 * main.cpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#include "AVRUtils.hpp"
#include "WheelControl.hpp"

WheelControl wheel_control; // PD3, 4, 5. PD2, 7, 6. Timer0

void initial()
{
    CLKPR = (1 << CLKPCE);
    CLKPR = 0b00000011; // set clk to 1 Mhz
    wheel_control.initial();

}

int main(void)
{
    initial();

}

