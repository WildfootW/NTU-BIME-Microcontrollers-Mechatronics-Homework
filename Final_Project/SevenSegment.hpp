/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#ifndef SEVENSEGMENT_HPP
#define SEVENSEGMENT_HPP

enum class SevenSegmentGraph
{
    //PGFEDCBA
    number_0 = 0b00111111, // 0
    number_1 = 0b00000110, // 1
    number_2 = 0b01011011, // 2
    number_3 = 0b01001111, // 3
    number_4 = 0b01100110, // 4
    number_5 = 0b01101101, // 5
    number_6 = 0b01111101, // 6
    number_7 = 0b00000111, // 7
    number_8 = 0b01111111, // 8
    number_9 = 0b01101111, // 9
    off = 0b00000000  // turn off
};
class SevenSegment
{
public:
    SevenSegment(){}
    void initial();
    void print(SevenSegmentGraph graph);
};

#endif //SEVENSEGMENT_HPP
