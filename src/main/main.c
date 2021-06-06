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

int gbe_write_buttons_rom(struct memory* mem, unsigned short offset, unsigned char d8);
int gbe_write_cartridge_rom(struct memory* mem, unsigned short offset, unsigned char d8);

struct buttons {
  int choose_buttons;
  int choose_directions;
  
  int up;
  int down;
  int left;
  int right;
  int b;
  int a;
  int select;
  int start;
};

struct memory memory;

struct screen screen;

struct cpu cpu;

struct ppu ppu;

struct cartridge cartridge;

struct buttons buttons;

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
  memory_register_set_hook(&memory, gbe_write_buttons_rom);

  memset(&buttons, 0, sizeof(buttons));
  buttons.choose_directions = 1;
  buttons.choose_buttons = 1;

  screen_init(&screen, SCREEN_WIDTH, SCREEN_HEIGHT);

  cpu_init(&cpu, &memory);

  ppu_init(&ppu, &screen, &memory);

  struct timespec then;
  gbe_gettime(&then);

  long vblanklen=1000000000/60;

  int working=1;
  while(working) {
    SDL_Event e;

    // Handle interrupts
    if(cpu_get_ime(&cpu)) {
      // Master interrupt is enabled
      unsigned char ienabled=memory_get_interrupt_enabled(&memory);
      unsigned char iflag=memory_get_interrupt_flag(&memory);
      if((ienabled  & INTERRUPT_MASK_VBLANK)!=0
          && (iflag & INTERRUPT_MASK_VBLANK)!=0) {
#ifdef GBE_DEBUG
        fprintf(stderr, "VBLANK\n");
#endif
        memory_clear_interrupt_flag(&memory, INTERRUPT_MASK_VBLANK);
        cpu_set_ime(&cpu, 0);
        cpu_push_pc(&cpu);
        cpu_set_pc(&cpu, INTERRUPT_VBLANK_ROUTINE_ADDR);
      }
      else {
        // No interrupts
      }
    }

    cpu_tick(&cpu);

    ppu_tick(&ppu);
    
    int vblank;
    // unsigned char stat=memory_get_d8(&memory, STAT);
    // if((stat&STAT_MODE)==STAT_MODE_01 && ppu.busy==1) {
    if(ppu.y==153 && ppu.busy==1) {
      // Worship at the SDL altar
      while(SDL_PollEvent(&e)) {
        switch(e.type) {
        case SDL_QUIT:
          working = 0;
          break;
        case SDL_KEYDOWN:
          switch(e.key.keysym.sym) {
          case SDLK_w:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYDOWN UP\n");
#endif            
            buttons.up = 1;
            break;
          case SDLK_a:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYDOWN LEFT\n");
#endif            
            buttons.left = 1;
            break;
          case SDLK_s:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYDOWN DOWN\n");
#endif            
            buttons.down = 1;
            break;
          case SDLK_d:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYDOWN RIGHT\n");
#endif            
            buttons.right = 1;
            break;
          case SDLK_j:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYDOWN A\n");
#endif            
            buttons.a = 1;
            break;
          case SDLK_k:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYDOWN B\n");
#endif            
            buttons.b = 1;
            break;
          case SDLK_g:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYDOWN SELECT\n");
#endif            
            buttons.select = 1;
            break;
          case SDLK_h:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYDOWN START\n");
#endif            
            buttons.start = 1;
            break;
          default:
            break;
          }
          break;
        case SDL_KEYUP:
          switch(e.key.keysym.sym) {
          case SDLK_w:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYUP   UP\n");
#endif            
            buttons.up = 0;
            break;
          case SDLK_a:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYUP   LEFT\n");
#endif            
            buttons.left = 0;
            break;
          case SDLK_s:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYUP   DOWN\n");
#endif            
            buttons.down = 0;
            break;
          case SDLK_d:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYUP   RIGHT\n");
#endif            
            buttons.right = 0;
            break;
          case SDLK_j:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYUP   A\n");
#endif            
            buttons.a = 0;
            break;
          case SDLK_k:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYUP   B\n");
#endif            
            buttons.b = 0;
            break;
          case SDLK_g:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYUP   SELECT\n");
#endif            
            buttons.select = 0;
            break;
          case SDLK_h:
#ifdef GBE_DEBUG
            fprintf(stderr, "KEYUP   START\n");
#endif            
            buttons.start = 0;
            break;
          default:
            break;
          }
          break;
        default:
          // Ignore this for now
          break;
        }
      }

      // Set our interrupt flag
      memory_set_interrupt_flag(&memory, INTERRUPT_MASK_VBLANK);

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

// @see https://gbdev.gg8.se/wiki/articles/Joypad_Input
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

#define BUTTONS_MEMORY_REGISTER 0xFF00
#define BUTTONS_CHOOSE_DIRECTIONS 0x10
#define BUTTONS_CHOOSE_BUTTONS 0x20
#define BUTTONS_NONE 0x0F

#define BUTTONS_DOWN 0x08
#define BUTTONS_UP 0x04
#define BUTTONS_LEFT 0x02
#define BUTTONS_RIGHT 0x01

#define BUTTONS_START 0x08
#define BUTTONS_SELECT 0x04
#define BUTTONS_B 0x02
#define BUTTONS_A 0x01

int gbe_read_buttons_rom(struct memory* mem, unsigned short offset) {
  int result;

  if(offset == BUTTONS_MEMORY_REGISTER) {
    int dirs=BUTTONS_NONE;
    if(buttons.choose_directions) {
#ifdef GBE_DEBUG
      fprintf(stderr, "KEYSTATE DIRECTIONS\n");
#endif            
      dirs = 
          (buttons.right ? 0 : BUTTONS_RIGHT)
        | (buttons.left ? 0 : BUTTONS_LEFT)
        | (buttons.up ? 0 : BUTTONS_UP)
        | (buttons.down ? 0 : BUTTONS_DOWN);
    }

    int buts=BUTTONS_NONE;
    if(buttons.choose_buttons) {
#ifdef GBE_DEBUG
      fprintf(stderr, "KEYSTATE BUTTONS\n");
#endif            
      buts = 
          (buttons.a ? 0 : BUTTONS_A)
        | (buttons.b ? 0 : BUTTONS_B)
        | (buttons.select ? 0 : BUTTONS_SELECT)
        | (buttons.start ? 0 : BUTTONS_START);
    }
    
    result = MEMORY_HOOK_RESULT | (dirs & buts);
    if(!buttons.choose_directions)
      result = result | BUTTONS_CHOOSE_DIRECTIONS;
    if(!buttons.choose_buttons)
      result = result | BUTTONS_CHOOSE_BUTTONS;

#ifdef GBE_DEBUG
    fprintf(stderr, "KEYSTATE %04x\n", result);
#endif

  }
  else {
    result = 0;
  }

  return result;
}

int gbe_write_buttons_rom(struct memory* mem, unsigned short offset, unsigned char d8) {
  int result;

  if(offset == BUTTONS_MEMORY_REGISTER) {
    buttons.choose_directions = (d8 & BUTTONS_CHOOSE_DIRECTIONS) ? 0 : 1;
    buttons.choose_buttons    = (d8 & BUTTONS_CHOOSE_BUTTONS) ? 0 : 1;
#ifdef GBE_DEBUG
    fprintf(stderr, "KEYSETUP %04x %d %d\n", d8, buttons.choose_directions, buttons.choose_buttons);
#endif            
    result = MEMORY_HOOK_RESULT;
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
