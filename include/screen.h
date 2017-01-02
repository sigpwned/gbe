#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include "SDL/SDL.h"

struct screen {
  unsigned int w;
  unsigned int h;
  SDL_Surface* surf;
  Uint8* buf;
};

void screen_init(struct screen* screen, unsigned int w, unsigned int h);
void screen_destroy(struct screen* screen);

void screen_put_pixel(struct screen* screen, unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
void screen_flip(struct screen* screen);

#endif // __SCREEN_H_INCLUDED__
