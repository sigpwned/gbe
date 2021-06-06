#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "SDL/SDL.h"

#include "gbe.h"
#include "cpu.h"
#include "ppu.h"
#include "screen.h"
#include "cartridge.h"

// From GameBoy-Online emulator
const unsigned char BOOT_ROM[] = {
  0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
  0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
  0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
  0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
  0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
  0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
  0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
  0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
  0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
  0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
  0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
  0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
  0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
  0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
  0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x00, 0x00, 0x23, 0x7D, 0xFE, 0x34, 0x20,
  0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x00, 0x00, 0x3E, 0x01, 0xE0, 0x50
};

void timespec_subtract(struct timespec *result, struct timespec *x, struct timespec *y);

int gbe_read_fully(FILE* fp, unsigned char* offset, size_t length);

int gbe_read_buttons_rom(struct memory* mem, unsigned short offset);
int gbe_read_cartridge_rom(struct memory* mem, unsigned short offset);

int gbe_map_cartridge_rom(struct memory* mem, unsigned short offset, unsigned char d8);
int gbe_write_cartridge_rom(struct memory* mem, unsigned short offset, unsigned char d8);

struct memory memory;

struct screen screen;

struct cpu cpu;

struct ppu ppu;

struct cartridge cartridge;

int main(int argc, char* argv[]) {
  if(argc != 2) {
    fprintf(stderr, "usage: gbe <cartridge>\n");
    exit(0);
  }

  const char* filename=argv[1];

  FILE* file=fopen(filename, "rb");
  if(file == NULL)
    exit(ERR_BAD_CARTRIDGE);
  cartridge_init(&cartridge, file);
  fclose(file);

  if(SDL_Init(SDL_INIT_VIDEO) != 0)
    exit(ERR_SDL);

  memory_init(&memory);
  memcpy(&memory.mem[  0],              BOOT_ROM,        256);
  memcpy(&memory.mem[256], &cartridge.data[256], 0x4000-256);
  memory_register_get_hook(&memory, gbe_read_buttons_rom);
  memory_register_get_hook(&memory, gbe_read_cartridge_rom);
  memory_register_set_hook(&memory, gbe_map_cartridge_rom);
  memory_register_set_hook(&memory, gbe_write_cartridge_rom);

  screen_init(&screen, SCREEN_WIDTH, SCREEN_HEIGHT);

  cpu_init(&cpu, &memory);

  ppu_init(&ppu, &screen, &memory);

  struct timespec then;
  gbe_gettime(&then);

  long vblanklen=1000000000/60;

  int working=1;
  while(working) {
    SDL_Event e;

    cpu_tick(&cpu);

    ppu_tick(&ppu);

    
    // unsigned char stat=memory_get_d8(&memory, STAT);
    // if((stat&STAT_MODE)==STAT_MODE_01 && ppu.busy==1) {
    if(ppu.y==153 && ppu.busy==1) {
      // We're at the tail end of a vblank.

      // Worship at the SDL altar
      while(SDL_PollEvent(&e)) {
        switch(e.type) {
        case SDL_QUIT:
          working = 0;
          break;
        default:
          // Ignore this for now
          break;
        }
      }

      // Manage our refresh time
      struct timespec now;
      gbe_gettime(&now);

      struct timespec elapsed;
      timespec_subtract(&elapsed, &now, &then);
      
      if(elapsed.tv_sec==0 && elapsed.tv_nsec<vblanklen) {
        struct timespec sleep;
        sleep.tv_sec = 0;
        sleep.tv_nsec = vblanklen-elapsed.tv_nsec;
        nanosleep(&sleep, NULL);
      }

      gbe_gettime(&then);
    }
  }

  screen_destroy(&screen);

  SDL_Quit();

  return 0;
}

int gbe_read_buttons_rom(struct memory* mem, unsigned short offset) {
  int result;

  if(offset == 0xFF00) {
    // SEE: https://gbdev.gg8.se/wiki/articles/Joypad_Input
    // FF00 - P1/JOYP - Joypad (R/W)
    // The eight gameboy buttons/direction keys are arranged in form of a 2x4 matrix. Select either button or direction keys by writing to this register, then read-out bit 0-3.
    // Bit 7 - Not used
    // Bit 6 - Not used
    // Bit 5 - P15 Select Button Keys      (0=Select)
    // Bit 4 - P14 Select Direction Keys   (0=Select)
    // Bit 3 - P13 Input Down  or Start    (0=Pressed) (Read Only)
    // Bit 2 - P12 Input Up    or Select   (0=Pressed) (Read Only)
    // Bit 1 - P11 Input Left  or Button B (0=Pressed) (Read Only)
    // Bit 0 - P10 Input Right or Button A (0=Pressed) (Read Only)
    result = MEMORY_HOOK_RESULT | 0xFF;
  }
  else {
    result = 0;
  }

  return result;
}

int gbe_read_cartridge_rom(struct memory* mem, unsigned short offset) {
  int result;

  if(offset>=0x4000 && offset<0x8000) {
    result = MEMORY_HOOK_RESULT | cartridge_get_d8(&cartridge, offset);
  }
  else {
    result = 0;
  }

  return result;
}

int gbe_map_cartridge_rom(struct memory* mem, unsigned short offset, unsigned char d8) {
  int result;

  if(offset == MAP_CARTRIDGE) {
    // This write means to swap out the cartridge ROM!
    memcpy(&mem->mem[0], &cartridge.data[0], 256);
    memory_unregister_set_hook(mem, gbe_map_cartridge_rom);
    result = MEMORY_HOOK_RESULT;
  }
  else {
    result = 0;
  }

  return result;
}

int gbe_write_cartridge_rom(struct memory* mem, unsigned short offset, unsigned char d8) {
  int result;

  if(offset>=0x2000 && offset<0x4000) {
    // This write goes to the cartridge
    cartridge_set_d8(&cartridge, offset, d8);
    result = MEMORY_HOOK_RESULT;
  }
  else {
    result = 0;
  }

  return result;
}

/**
 * @see https://gist.github.com/diabloneo/9619917
 */
void timespec_subtract(struct timespec *result, struct timespec *stop, struct timespec *start) {
  if ((stop->tv_nsec - start->tv_nsec) < 0) {
    result->tv_sec = stop->tv_sec - start->tv_sec - 1;
    result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
  } else {
    result->tv_sec = stop->tv_sec - start->tv_sec;
    result->tv_nsec = stop->tv_nsec - start->tv_nsec;
  }
}

int gbe_read_fully(FILE* fp, unsigned char* offset, size_t length) {
  size_t total=0;
  while(total < length) {
    size_t nread=fread(&offset[total], 1, length-total, fp);
    total = total+nread;
  }
  return total == length;
}
