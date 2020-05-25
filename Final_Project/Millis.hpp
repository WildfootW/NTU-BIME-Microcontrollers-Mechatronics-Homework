/*
 * The millis() function known from Arduino
 * Calling millis() will return the milliseconds since the program started
 *
 * Tested on atmega328p
 *
 * Using content from http://www.adnbr.co.uk/articles/counting-milliseconds
 * Author: Monoclecat, https://github.com/monoclecat/avr-millis-function
 * Author: WildfootW, https://github.com/WildfootW
 *
 * REMEMBER: Add sei(); after init_millis() to enable global interrupts!
 */

#ifndef MILLIS_HPP
#define MILLIS_HPP

//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/atomic.h>

/*
main: sei()
ISR(TIMER1_COMPA_vect)
{
    timer1_millis++;
}
*/

class Millis
{
public:
    Millis(){}
    void initial();
    void increase_millis();
    unsigned long get();

private:
    volatile unsigned long timer1_millis;
    //NOTE: A unsigned long holds values from 0 to 4,294,967,295 (2^32 - 1). It will roll over to 0 after reaching its maximum value.
};

/* [TODO]
class Delay
{
public:
    Delay()
    {
        start_time = millis.get();
    }

private:
    unsigned long start_time;
}
*/

#endif //MILLIS_HPP
