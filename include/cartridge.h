#ifndef __CARTRIDGE_H_INCLUDED__
#define __CARTRIDGE_H_INCLUDED__

#include "SDL/SDL.h"

struct cartridge {
  unsigned char  type;
  unsigned char  rom_size;
  unsigned char  ram_size;
  unsigned char  mode;
  unsigned char  rom_bank;
  unsigned char  ram_bank;
  unsigned char* data;
  size_t         datalen;
};

void cartridge_init(struct cartridge* cartridge, FILE* f);
void cartridge_destroy(struct cartridge* cartridge);

unsigned char cartridge_get_d8(struct cartridge* cartridge, unsigned short offset);

void cartridge_set_d8(struct cartridge* cartridge, unsigned short offset, unsigned char value);

#endif // __CARTRIDGE_H_INCLUDED__
