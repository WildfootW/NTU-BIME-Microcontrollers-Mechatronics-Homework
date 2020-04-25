# NTU BIME Microcontrollers Mechatronics Homework
BIME Microcontrollers Mechatronics 2018/2019-2 semester Homework

# arduino-cli cheat sheet
```
arduino-cli core update-index
arduino-cli board list
arduino-cli core search uno
arduino-cli core install arduino:avr
arduino-cli core list
arduino-cli board list
```

## Makefile
```
all: upload

upload: compile
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno $(SKETCH)

compile:
	arduino-cli compile --fqbn arduino:avr:uno $(SKETCH)

clean:
```

# AVR-C
## Tools
```
sudo apt install gcc-avr binutils-avr avr-libc
sudo apt install gdb-avr
sudo apt install avrdude
```

## Makefile

## Library
* References
    * jypma
        * [AvrLib](https://github.com/jypma/AvrLib)
        * [AvrLibDemo](https://github.com/jypma/AvrLibDemo)
    * [Electronics - C++ classes for I/O pin abstraction](https://electronics.stackexchange.com/questions/19057/c-classes-for-i-o-pin-abstraction)
    * [Objects? No, thanks! (Using C++ effectively on small systems)](https://www.embedded.com/objects-no-thanks-using-c-effectively-on-small-systems/)
