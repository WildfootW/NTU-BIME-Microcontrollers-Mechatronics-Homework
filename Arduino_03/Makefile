SKETCH ?= Lab03_1

all: upload

upload: compile
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno $(SKETCH)

compile:
	arduino-cli compile --fqbn arduino:avr:uno $(SKETCH)

clean:
