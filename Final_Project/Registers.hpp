/*
 * Registers.hpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <stdint.h>
#include <avr/io.h>

/*
 * AVR Register
 */
struct AVR_Register_PORTB
{
    constexpr static volatile uint8_t *const addr() { return &PORTB; }
};
struct AVR_Register_DDRB
{
    constexpr static volatile uint8_t *const addr() { return &DDRB; }
};
struct AVR_Register_PINB
{
    constexpr static volatile uint8_t *const addr() { return &PINB; }
};
struct AVR_Register_PORTC
{
    constexpr static volatile uint8_t *const addr() { return &PORTC; }
};
struct AVR_Register_DDRC
{
    constexpr static volatile uint8_t *const addr() { return &DDRC; }
};
struct AVR_Register_PINC
{
    constexpr static volatile uint8_t *const addr() { return &PINC; }
};
struct AVR_Register_PORTD
{
    constexpr static volatile uint8_t *const addr() { return &PORTD; }
};
struct AVR_Register_DDRD
{
    constexpr static volatile uint8_t *const addr() { return &DDRD; }
};
struct AVR_Register_PIND
{
    constexpr static volatile uint8_t *const addr() { return &PIND; }
};
struct AVR_Register_OCR0A
{
    constexpr static volatile uint8_t *const addr() { return &OCR0A; }
};
struct AVR_Register_OCR0B
{
    constexpr static volatile uint8_t *const addr() { return &OCR0B; }
};

template<class name, uint8_t bit>
class AVRRegisterBit
{
    constexpr static volatile uint8_t *addr = name::addr();
    constexpr static uint8_t mask = 1 << bit;
public:
    static void set(bool x)
    {
        if(x)
            *addr |= mask;
        else
            *addr &= ~mask;
    }
    static bool read()
    {
        return *addr & mask;
    }
};

#endif //REGISTERS_HPP
