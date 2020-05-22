/*
 * AVRUtils.hpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#ifndef AVRUTILS_HPP
#define AVRUTILS_HPP
template<uint8_t name, int8_t bit>
class AVRRegisterBit
{
public:
    static void set(bool x) const
    {
        if(x)
            name |= (1 << bit);
        else
            name &= ~(1 << bit);
    }
    static bool read() const
    {
        return name & (1 << bit);
    }
};
template<class data, class data_direction, class input_pin> // PORT, DDR, PIN
class AVRIOPin
{
public:
    enum PinMode
    {
        Output,
        Input,
        InputPullup
    };
    static void configure_pin_mode(PinMode x) const
    {
        if(x == Output)
        {
            data_direction::set(true);
        }
        if(x == Input)
        {
            data_direction::set(false);
            data::set(false);
        }
        if(x == InputPullup)
        {
            data_direction::set(false);
            data::set(true);
        }
    }
    static void set_output(bool x) const
    {
        data::set(x);
    }
    static bool read_input() const
    {
        return input_pin::read();
    }
};
template<class data, class data_direction, class input_pin> // PORT, DDR, PIN
using pin_PD2 = AVRIOPin<AVRRegisterBit<PORTD, 2>, AVRRegisterBit<DDRD, 2>, AVRRegisterBit<PIND, 2>>;
using pin_PD3 = AVRIOPin<AVRRegisterBit<PORTD, 3>, AVRRegisterBit<DDRD, 3>, AVRRegisterBit<PIND, 3>>;
using pin_PD3 = AVRIOPin<AVRRegisterBit<PORTD, 3>, AVRRegisterBit<DDRD, 3>, AVRRegisterBit<PIND, 3>>;
using pin_PD3 = AVRIOPin<AVRRegisterBit<PORTD, 3>, AVRRegisterBit<DDRD, 3>, AVRRegisterBit<PIND, 3>>;
using pin_PD3 = AVRIOPin<AVRRegisterBit<PORTD, 3>, AVRRegisterBit<DDRD, 3>, AVRRegisterBit<PIND, 3>>;
using pin_PD3 = AVRIOPin<AVRRegisterBit<PORTD, 3>, AVRRegisterBit<DDRD, 3>, AVRRegisterBit<PIND, 3>>;
#endif //AVRUTILS_HPP

