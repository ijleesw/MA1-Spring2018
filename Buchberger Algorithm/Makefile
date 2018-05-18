CC = g++
CFLAGS = -O2 -Wall -std=c++11
LIBS = -lgmp -lgmpxx
TARGET = groebner
OBJECTS = src/main.cpp

all: groebner

groebner: src/main.cpp src/buchberger.hpp src/polynomial.hpp src/monomial.hpp
	$(CC) $(CFLAGS) -o groebner $(OBJECTS) $(LIBS)

reverse: src/main.cpp src/buchberger.hpp src/polynomial.hpp src/monomial.hpp
	$(CC) $(CFLAGS) -DREVERSE -o groebner $(OBJECTS) $(LIBS)

clean:
	$(RM) $(TARGET)