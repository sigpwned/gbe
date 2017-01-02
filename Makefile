CC=gcc
CXX=g++
CFLAGS=-Iinclude/ -Wall -O0 `sdl-config --cflags`
LDFLAGS=
HEADERS=include/*.h 
OBJECTS=cpu.o opcodes.o screen.o
TESTS=$(OBJECTS:.o=.to)
LIBRARIES=`sdl-config --libs`
TARGET=gbe

.PHONY: default all clean test

all: default

default: $(TARGET)

$(TARGET): $(OBJECTS) main.o
	$(CC) $(OBJECTS) main.o $(LIBRARIES) -o $(TARGET)

%.o: src/main/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.to: src/test/%-test.cpp $(HEADERS) $(OBJECTS)
	$(CXX) $(CFLAGS) $(LIBRARIES) -lboost_unit_test_framework $(OBJECTS) $< -o $@
	./$@ --log_level=test_suite

test: $(TESTS)

clean:
	rm -f *.o
	rm -f *.to
	rm -f $(TARGET)


