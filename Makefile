CC=gcc
CFLAGS=-c -Wall -Iinclude/
LDFLAGS=
HEADERS=include/*.h 
OBJECTS=main.o opcodes.o cpu.o
LIBRARIES=
TARGET=gbe

.PHONY: default all clean

all: default

default: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBRARIES) -o $(TARGET)

%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)


