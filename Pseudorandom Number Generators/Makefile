CC = g++
CFLAGS = -Og
TARGET = lcg msm lfg

all: $(TARGET)

lcg: src/linear_congruence_generator.cpp src/stats.cpp
	$(CC) $(CFLAGS) -o $@ $^

msm: src/middle_square_method.cpp src/stats.cpp
	$(CC) $(CFLAGS) -o $@ $^

lfg: src/lagged_fibonacci_generator.cpp src/stats.cpp
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(TARGET)