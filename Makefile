CC=gcc
CXX=g++
CFLAGS=-Iinclude/ -Wall -O2 `sdl-config --cflags` -g
LDFLAGS=
HEADERS=include/*.h 
OBJECTS=cpu.o opcodes.o screen.o ppu.o mach.o memory.o cartridge.o
TESTS=$(OBJECTS:.o=-test.o)
LIBRARIES=`sdl-config --libs`
TARGET=gbe

.PHONY: default all clean test

all: default

default: $(TARGET)

$(TARGET): $(OBJECTS) main.o
	$(CC) $(CFLAGS) $(OBJECTS) main.o $(LIBRARIES) -o $(TARGET)

%.o: src/main/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: src/main/platform/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%-test.o: src/test/%-test.cpp $(HEADERS) $(OBJECTS)
	$(CXX) $(CFLAGS) $(LIBRARIES) -lboost_unit_test_framework $(OBJECTS) $< -o $@
	./$@ --log_level=test_suite

test: $(TESTS)

clean:
	rm -f *.o
	rm -f $(TARGET)


