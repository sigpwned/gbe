#include <stdlib.h>
#include <string.h>
#include "memory.h"

void memory_init(struct memory* mem) {
  memset(mem, 0, sizeof(struct memory));
}

unsigned char memory_get_d8(struct memory* mem, unsigned short offset) {
  return mem->mem[offset];
}

void memory_set_d8(struct memory* mem, unsigned short offset, unsigned char d8) {
  mem->mem[offset] = d8;
}
