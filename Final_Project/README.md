# Final Project

## Makefile
* link
    * compile & link
* flash
    * copy elf to ihex
    * write ihex file to flash via avrdude
* size
    * list section sizes and total size
* clean

## Plan
### Architecture
#### I/O Port
* Wheel
    * llleft
        * PD3
        * PD4
        * PD5 (OC0B)
    * rright
        * PD2
        * PD7
        * PD6 (OC0A)
* Sensor
    * ObstacleDetector
        * PC0 (ADC0) - center
        * PC4 (ADC4) - right
    * RouteDetector
        * PC1 (ADC1) - llleft
        * PC2 (ADC2) - center
        * PC3 (ADC3) - rright
* SevenSegment
    * PB0 - PB7
* Serial
    * PD1 (TXD)

### Workflow
* main
    * initial
    * loop
        * update detector status ( according to current sensor value )
        * let the wheels respond to the state
* input
    * trigger interrupt while complete reading from ADC
    * pass value to sensor
    * change input channel to next channel
    * start next ADC

### Framework
#### Files
* Makefile
* main.cpp
* ADConverter.hpp
* AVRUtils.hpp
* Millis.hpp
* ObstacleDetector.hpp
* RouteDetector.hpp
* Sensors.hpp
* SevenSegment.hpp
* Usart.hpp
* WheelControl.hpp

## Reference
* [avr/iom328p.h](https://github.com/vancegroup-mirrors/avr-libc/blob/master/avr-libc/include/avr/iom328p.h)
* [AvrLib/inc/HAL/Atmel/Pin.hpp](https://github.com/jypma/AvrLib/blob/master/inc/HAL/Atmel/Pin.hpp)
* [TTU Robotiklubi - ATmega88 avr/cpp/IO.h](http://avr-cpp-lib.sourceforge.net/ATmega88/_i_o_8h-source.html)
* [libpololu-avr](https://github.com/pololu/libpololu-avr)

## Note / Problemshooting
### Object Oriented
* [Electronics - C++ classes for I/O pin abstraction](https://electronics.stackexchange.com/questions/19057/c-classes-for-i-o-pin-abstraction)
* [Objects? No, thanks! (Using C++ effectively on small systems)](https://www.embedded.com/objects-no-thanks-using-c-effectively-on-small-systems/)

### Register Data Type
```c
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _SFR_MEM8(mem_addr) _MMIO_BYTE(mem_addr)
#define PINB _SFR_IO8(0x03)
```

### constexpr reference to avr port address
```
In file included from /usr/lib/avr/include/avr/io.h:99:0,
                 from AVRUtils.hpp:14,
                 from main.cpp:8:
AVRUtils.hpp:70:41: error: expression ‘*37u’ has side-effects
 using pin_PB0 = AVRIOPin<AVRRegisterBit<PORTB, PORTB0>, AVRRegisterBit<DDRB, DDB0>, AVRRegisterBit<PINB, PINB0>>;
                                         ^
In file included from main.cpp:8:0:
AVRUtils.hpp:70:54: error: ‘*37u’ is not a constant expression
 using pin_PB0 = AVRIOPin<AVRRegisterBit<PORTB, PORTB0>, AVRRegisterBit<DDRB, DDB0>, AVRRegisterBit<PINB, PINB0>>;
                                                      ^
```
I need to use struct `AVR_REGISTER_DDRD` packing `DDRD` while as template argument.
* [stackoverflow - constexpr reference to avr port address](https://stackoverflow.com/questions/41077173/constexpr-reference-to-avr-port-address)
* [What exactly is a 'side-effect' in C++?](https://stackoverflow.com/questions/9563600/what-exactly-is-a-side-effect-in-c)

### Member functions of class templates
```
template<class T> class X {
   public:
      T operator+(T);
};

template<class T> T X<T>::operator+(T arg1) {
   return arg1;
};
```
* [Member functions of class templates (C++ only)](https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/member_function_templates.htm)

### enum class
* [Why is enum class preferred over plain enum?](https://stackoverflow.com/questions/18335861/why-is-enum-class-preferred-over-plain-enum)
* [Declaring an enum within a class](https://stackoverflow.com/questions/2503807/declaring-an-enum-within-a-class)

## TODO
* fix Usart

