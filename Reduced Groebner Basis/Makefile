CC = g++
CFLAGS = -O2 -std=c++11 -Wall
LIBS = -lgmp -lgmpxx
TARGET = groebner
OBJECTS = src/main.cpp

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) $(TARGET)