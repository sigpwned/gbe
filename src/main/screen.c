#include "gbe.h"
#include "screen.h"

void screen_init(struct screen* screen, unsigned int w, unsigned int h) {
  memset(screen, 0, sizeof(struct screen));

  screen->surf = SDL_SetVideoMode(w, h, 32, SDL_SWSURFACE);
  if(screen->surf == NULL)
    exit(ERR_SDL);

  screen->w = w;
  screen->h = h;

  screen->buf = (Uint8*) malloc(SCREEN_HEIGHT * screen->surf->pitch);
}

void screen_destroy(struct screen* screen) {
  SDL_FreeSurface(screen->surf);

  free(screen->buf);
}

void screen_put_pixel(struct screen* screen, unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
  Uint8* p8=screen->buf + y*screen->surf->pitch + 4*x;
  Uint32* p32=(Uint32*) p8;
  *p32 = SDL_MapRGB(screen->surf->format, r, g, b);
}

void screen_flip(struct screen* screen) {
  if(SDL_MUSTLOCK(screen->surf))
    if(SDL_LockSurface(screen->surf) < 0)
      exit(ERR_SDL);

  memcpy(screen->surf->pixels, screen->buf, screen->h*screen->surf->pitch);

  if(SDL_MUSTLOCK(screen->surf))
    SDL_UnlockSurface(screen->surf);

  SDL_UpdateRect(screen->surf, 0, 0, screen->w, screen->h);
}

