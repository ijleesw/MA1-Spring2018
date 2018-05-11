CC = g++
CFLAGS = -O2 -std=c++11 -Wall
LIBS = -lgmp -lgmpxx
TARGET = groebner
OBJECTS = src/main.cpp

all: groebner

groebner: src/main.cpp src/groebner.hpp src/polynomial.hpp src/monomial.hpp
	$(CC) $(CFLAGS) -o groebner $(OBJECTS) $(LIBS)

reverse: src/main.cpp src/groebner.hpp src/polynomial.hpp src/monomial.hpp
	$(CC) $(CFLAGS) -o groebner $(OBJECTS) $(LIBS) -DREVERSE

clean:
	$(RM) $(TARGET)