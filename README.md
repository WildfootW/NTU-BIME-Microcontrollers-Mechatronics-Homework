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
