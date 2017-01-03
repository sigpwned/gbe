#ifndef __PPU_H_INCLUDED__
#define __PPU_H_INCLUDED__

#include "screen.h"
#include "memory.h"

#ifdef __cplusplus 
extern "C" {
#endif

struct ppu {
  struct screen* screen;
  struct memory* memory;
  unsigned int y;
  unsigned int x;
  unsigned int c;
  unsigned int state;
  unsigned int busy;
};

// LIFECYLE ////////////////////////////////////////////////////////////////////
void ppu_init(struct ppu* p, struct screen* screen, struct memory* memory);

void ppu_tick(struct ppu* p);

#ifdef __cplusplus 
}
#endif

#endif // __PPU_H_INCLUDED__
