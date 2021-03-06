#include <stdio.h>
#include "gbe.h"
#include "ppu.h"
#include "memory.h"

#define STATE_OAM 0 // 20 clocks
#define STATE_TRANSFER 1 // 40-ish
#define STATE_HBLANK 2 // Finish out 114 clocks per line
#define STATE_VBLANK 3 // 114 * 10 = 1140

#define VMEM 0x8000

void ppu_init(struct ppu* ppu, struct screen* screen, struct memory* memory) {
  memset(ppu, 0, sizeof(struct ppu));

  ppu->screen = screen;

  ppu->memory = memory;

  ppu->state = STATE_OAM;
  ppu->y = ppu->x = ppu->c = 0;
  ppu->busy = 80;

  memory_set_d8(ppu->memory, LY, ppu->y);
}

void ppu_tick(struct ppu* ppu) {
  if(ppu->busy <= 1) {
    switch(ppu->state) {
    case STATE_OAM:
      {
        unsigned char stat=memory_get_d8(ppu->memory, STAT);
        stat = (stat & ~STAT_MODE) | STAT_MODE_11;
        memory_set_d8(ppu->memory, STAT, stat);

        ppu->state = STATE_TRANSFER;
        ppu->x = 0;
        ppu->busy = 1;
      } break;
    case STATE_TRANSFER:
      {
        unsigned char lcdc=memory_get_d8(ppu->memory, LCDC);
        unsigned char sx=memory_get_d8(ppu->memory, SCX), sy=memory_get_d8(ppu->memory, SCY);
        unsigned char palette=memory_get_d8(ppu->memory, BG_PALETTE);

        unsigned char color;
        if(lcdc & LCDC_ON) {
          if(lcdc & LCDC_BG_WINDOW_DISPLAY) {
            unsigned char x=sx+ppu->x, y=sy+ppu->y;
      
            unsigned short bgmapoff=lcdc & LCDC_BG_TILE_MAP_DISPLAY_SELECT ? 0x9c00 : 0x9800;
            unsigned char tx=x/8, ty=y/8;
            unsigned char ti=memory_get_d8(ppu->memory, bgmapoff+32*ty+tx);
        
            unsigned short bgtsoff=lcdc & LCDC_BG_WINDOW_TILE_DATA_SELECT ? 0x8000 : 0x8800;
        
            unsigned short tpoff;
            if(lcdc & LCDC_BG_WINDOW_TILE_DATA_SELECT) {
              tpoff = bgtsoff+ti*16;
            }
            else {
              // Here, our indexes are actually signed chars offset from 9000.
              signed char ti2=(signed char) ti;
              tpoff = bgtsoff+0x200+ti2*16;
            }
     
            unsigned char px=x%8, py=y%8;
      
            // This is just a bizarre encoding. I don't understand this choice.
            unsigned char b1=memory_get_d8(ppu->memory, tpoff+2*py+0);
            unsigned char b2=memory_get_d8(ppu->memory, tpoff+2*py+1);
            unsigned char mx=1 << (7 - px);
            
            unsigned char c1=(b1 & mx ? 1 : 0) | (b2 & mx ? 2 : 0);
             unsigned char c2=(palette & (3 << (2*c1))) >> (2*c1);
    
            color = 255-85*c2;
          }
          else {
            color = 255;
          }
        }
        else {
          color = 255;
        }

        screen_put_pixel(ppu->screen, ppu->x, ppu->y, color, color, color);
    
        ppu->x = ppu->x+1;
  
        if(ppu->x == SCREEN_WIDTH) {
          unsigned char stat=memory_get_d8(ppu->memory, STAT);
          stat = (stat & ~STAT_MODE) | STAT_MODE_00;
          memory_set_d8(ppu->memory, STAT, stat);

          ppu->state = STATE_HBLANK;
          ppu->busy  = 204;
        }
      } break;
    case STATE_HBLANK:
      {
        ppu->y = ppu->y+1;

        unsigned char mode;
        if(ppu->y == SCREEN_HEIGHT) {
          ppu->state = STATE_VBLANK;
          ppu->busy  = 456;
          mode       = STAT_MODE_01;
        }
        else {
          ppu->state = STATE_OAM;
          ppu->busy  = 80;
          mode       = STAT_MODE_10;
        }

        unsigned char stat=memory_get_d8(ppu->memory, STAT);
        unsigned char lyc=memory_get_d8(ppu->memory, LYC);
        if(ppu->y == lyc) {
          stat = stat | STAT_LYC;
        }
        else {
          stat = stat & ~STAT_LYC;
        }
        stat = (stat & ~STAT_MODE) | mode;
        memory_set_d8(ppu->memory, STAT, stat);

        memory_set_d8(ppu->memory, LY, ppu->y);
      } break;
    case STATE_VBLANK:
      {
        ppu->y = ppu->y+1;        

        unsigned char mode;

        if(ppu->y == SCREEN_HEIGHT+10) {
          ppu->y = 0;
          ppu->state = STATE_OAM;
          ppu->busy = 80;
          mode = STAT_MODE_10;
          screen_flip(ppu->screen);
        }
        else {
          ppu->state = STATE_VBLANK;
          ppu->busy = 456;
          mode = STAT_MODE_01;
        }

        unsigned char stat=memory_get_d8(ppu->memory, STAT);
        unsigned char lyc=memory_get_d8(ppu->memory, LYC);
        if(ppu->y == lyc) {
          stat = stat | STAT_LYC;
        }
        else {
          stat = stat & ~STAT_LYC;
        }
        stat = (stat & ~STAT_MODE) | mode;
        memory_set_d8(ppu->memory, STAT, stat);

        memory_set_d8(ppu->memory, LY, ppu->y);
      } break;
    }
  }
  else {
    ppu->busy = ppu->busy-1;
  }
}
