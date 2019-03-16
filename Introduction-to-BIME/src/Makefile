CXX       = g++
CCC       = gcc
AR        = ar cr
ECHO      = echo

CCCFLAGS = -O3 -Wall -std=c11
CXXFLAGS = -O3 -Wall -std=c++11
CXXFLAGS = -g -Wall -std=c++11 -D NDEBUG

all: libs main

libs: emg.o moving_average.o peak_to_peak.o queue.o

main: main.o
	$(ECHO) "> linking..."
	$(CXX) -o main.out emg.o moving_average.o peak_to_peak.o queue.o main.o

%.o : %.cpp
	$(ECHO) "> compiling: $<"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o : %.c
	$(ECHO) "> compiling: $<"
	$(CCC) $(CCCFLAGS) -c -o $@ $<

clean:
	rm *.o
