CC = g++
CFLAGS = -O2 -Wall -std=c++11
TARGET = simple_taylor

all : $(TARGET)

simple_taylor: src/main.cpp src/simple_taylor.hpp src/jet.hpp src/vector_tools.hpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGET)