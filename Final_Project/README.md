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
* Serial
    * PD1 (TXD)
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
        * PC0 (ADC0)
    * RouteDetector
        * PC1 (ADC1) - llleft
        * PC2 (ADC2) - center
        * PC3 (ADC3) - rright

### Workflow

### Framework
#### Files
* main.cpp
* RouteDetector.h
* ObstacleDetector.h
* MySensor.h
* WheelControl.h

## Problemshooting
### Register Data Type
```c
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _SFR_MEM8(mem_addr) _MMIO_BYTE(mem_addr)
#define PINB _SFR_IO8(0x03)
```

## TODO
* how to read multiple ADC input

