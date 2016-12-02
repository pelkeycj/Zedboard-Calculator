CXXFLAGS: -Wall -Werror

all: Calculator

Calculator: Zedboard.o Calculator.o
	g++ Zedboard.o Calculator.o -o Calculator

Zedboard.o: Zedboard.cpp Zedboard.h
	g++ $(CXXFLAGS) -c Zedboard.cpp

Calculator.o: Calculator.cpp Zedboard.h
	g++ $(CXXFLAGS) -c Calculator.cpp

clean:
	rm *.o Calculator
