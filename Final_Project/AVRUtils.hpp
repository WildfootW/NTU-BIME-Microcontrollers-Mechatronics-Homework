/*
 * AVRUtils.hpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#ifndef AVRUTILS_HPP
#define AVRUTILS_HPP

extern "C"
{
    #include <stdint.h>
    #include <avr/io.h>
}

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
enum class AVRIOPinMode
{
    Output,
    Input,
    InputPullup
};
template<class data, class data_direction, class input_pin> // PORT, DDR, PIN
class AVRIOPin
{
public:
    static void configure_pin_mode(AVRIOPinMode x)
    {
        if(x == AVRIOPinMode::Output)
        {
            data_direction::set(true);
        }
        if(x == AVRIOPinMode::Input)
        {
            data_direction::set(false);
            data::set(false);
        }
        if(x == AVRIOPinMode::InputPullup)
        {
            data_direction::set(false);
            data::set(true);
        }
    }
    static void set_output(bool x)
    {
        data::set(x);
    }
    static bool read_input()
    {
        return input_pin::read();
    }
};
using pin_PB0 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTB, 0>, AVRRegisterBit<AVR_Register_DDRB, 0>, AVRRegisterBit<AVR_Register_PINB, 0>>;
using pin_PB1 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTB, 1>, AVRRegisterBit<AVR_Register_DDRB, 1>, AVRRegisterBit<AVR_Register_PINB, 1>>;
using pin_PB2 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTB, 2>, AVRRegisterBit<AVR_Register_DDRB, 2>, AVRRegisterBit<AVR_Register_PINB, 2>>;
using pin_PB3 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTB, 3>, AVRRegisterBit<AVR_Register_DDRB, 3>, AVRRegisterBit<AVR_Register_PINB, 3>>;
using pin_PB4 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTB, 4>, AVRRegisterBit<AVR_Register_DDRB, 4>, AVRRegisterBit<AVR_Register_PINB, 4>>;
using pin_PB5 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTB, 5>, AVRRegisterBit<AVR_Register_DDRB, 5>, AVRRegisterBit<AVR_Register_PINB, 5>>;
using pin_PB6 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTB, 6>, AVRRegisterBit<AVR_Register_DDRB, 6>, AVRRegisterBit<AVR_Register_PINB, 6>>;
using pin_PB7 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTB, 7>, AVRRegisterBit<AVR_Register_DDRB, 7>, AVRRegisterBit<AVR_Register_PINB, 7>>;
using pin_PC0 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTC, 0>, AVRRegisterBit<AVR_Register_DDRC, 0>, AVRRegisterBit<AVR_Register_PINC, 0>>;
using pin_PC1 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTC, 1>, AVRRegisterBit<AVR_Register_DDRC, 1>, AVRRegisterBit<AVR_Register_PINC, 1>>;
using pin_PC2 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTC, 2>, AVRRegisterBit<AVR_Register_DDRC, 2>, AVRRegisterBit<AVR_Register_PINC, 2>>;
using pin_PC3 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTC, 3>, AVRRegisterBit<AVR_Register_DDRC, 3>, AVRRegisterBit<AVR_Register_PINC, 3>>;
using pin_PC4 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTC, 4>, AVRRegisterBit<AVR_Register_DDRC, 4>, AVRRegisterBit<AVR_Register_PINC, 4>>;
using pin_PC5 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTC, 5>, AVRRegisterBit<AVR_Register_DDRC, 5>, AVRRegisterBit<AVR_Register_PINC, 5>>;
using pin_PC6 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTC, 6>, AVRRegisterBit<AVR_Register_DDRC, 6>, AVRRegisterBit<AVR_Register_PINC, 6>>;
using pin_PD0 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTD, 0>, AVRRegisterBit<AVR_Register_DDRD, 0>, AVRRegisterBit<AVR_Register_PIND, 0>>;
using pin_PD1 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTD, 1>, AVRRegisterBit<AVR_Register_DDRD, 1>, AVRRegisterBit<AVR_Register_PIND, 1>>;
using pin_PD2 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTD, 2>, AVRRegisterBit<AVR_Register_DDRD, 2>, AVRRegisterBit<AVR_Register_PIND, 2>>;
using pin_PD3 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTD, 3>, AVRRegisterBit<AVR_Register_DDRD, 3>, AVRRegisterBit<AVR_Register_PIND, 3>>;
using pin_PD4 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTD, 4>, AVRRegisterBit<AVR_Register_DDRD, 4>, AVRRegisterBit<AVR_Register_PIND, 4>>;
using pin_PD5 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTD, 5>, AVRRegisterBit<AVR_Register_DDRD, 5>, AVRRegisterBit<AVR_Register_PIND, 5>>;
using pin_PD6 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTD, 6>, AVRRegisterBit<AVR_Register_DDRD, 6>, AVRRegisterBit<AVR_Register_PIND, 6>>;
using pin_PD7 = AVRIOPin<AVRRegisterBit<AVR_Register_PORTD, 7>, AVRRegisterBit<AVR_Register_DDRD, 7>, AVRRegisterBit<AVR_Register_PIND, 7>>;

#endif //AVRUTILS_HPP
