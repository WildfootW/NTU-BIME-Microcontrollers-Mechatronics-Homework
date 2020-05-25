/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#include "SevenSegment.hpp"
#include <avr/io.h>
#include <stdint.h>

void SevenSegment::initial()
{
    DDRB = 0xff;
}
void SevenSegment::print(SevenSegmentGraph graph)
{
    PORTB = ~static_cast<uint8_t>(graph);
}
