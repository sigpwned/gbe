#ifndef __MEMORY_H_INCLUDED__
#define __MEMORY_H_INCLUDED__

struct memory {
  unsigned char mem[64*1024];
};

void memory_init(struct memory* mem);

unsigned char memory_get_d8(struct memory* mem, unsigned short offset);
void memory_set_d8(struct memory* mem, unsigned short offset, unsigned char value);

// LCDC ////////////////////////////////////////////////////////////////////////
#define LCDC ((unsigned short) 0xFF40)

#define LCDC_STATE ((unsigned char) 0x80)
#define LCDC_ON ((unsigned char) 0x80)
#define LCDC_OFF ((unsigned char) 0x00)

#define LCDC_WINDOW_TILE_MAP_DISPLAY_SELECT ((unsigned char) 0x40)
#define LCDC_WINDOW_TILE_MAP_DISPLAY_SELECT_9800 ((unsigned char) 0x00) // If this bit is set, then window tile map spans 9800-9BFF
#define LCDC_WINDOW_TILE_MAP_DISPLAY_SELECT_9C00 ((unsigned char) 0x40) // If this bit is clear, then window tile map spans 9C00-9FFF

#define LCDC_WINDOW_DISPLAY ((unsigned char) 0x20)
#define LCDC_WINDOW_DISPLAY_ON ((unsigned char) 0x20)
#define LCDC_WINDOW_DISPLAY_OFF ((unsigned char) 0x00)

#define LCDC_BG_WINDOW_TILE_DATA_SELECT ((unsigned char) 0x10)
#define LCDC_BG_WINDOW_TILE_DATA_SELECT_8000 ((unsigned char) 0x10) // If this bit is set, then bg and window tiles span 8000-8FFF, same as sprites
#define LCDC_BG_WINDOW_TILE_DATA_SELECT_8800 ((unsigned char) 0x00) // If this bit is clear, then bg and window tiles span 8800-97FF

#define LCDC_BG_TILE_MAP_DISPLAY_SELECT ((unsigned char) 0x08)
#define LCDC_BG_TILE_MAP_DISPLAY_SELECT_9C00 ((unsigned char) 0x08) // If this bit is set, then bg tile map spans 9C00-9FFF
#define LCDC_BG_TILE_MAP_DISPLAY_SELECT_9800 ((unsigned char) 0x00) // If this bit is clear, then bg tile map spans 9800-9BFF

#define LCDC_OBJ_SIZE ((unsigned char) 0x04)
#define LCDC_OBJ_SIZE_16 ((unsigned char) 0x04) // If this bit is set, then all sprites are 8x16
#define LCDC_OBJ_SIZE_8 ((unsigned char) 0x00) // If this bit is clear, then all sprites are 8x8

#define LCDC_OBJ_DISPLAY ((unsigned char) 0x02)
#define LCDC_OBJ_DISPLAY_ON ((unsigned char) 0x02)
#define LCDC_OBJ_DISPLAY_OFF ((unsigned char) 0x00)

#define LCDC_BG_WINDOW_DISPLAY ((unsigned char) 0x01)
#define LCDC_BG_WINDOW_DISPLAY_ON ((unsigned char) 0x10)
#define LCDC_BG_WINDOW_DISPLAY_OFF ((unsigned char) 0x00)

// LCDC STATUS /////////////////////////////////////////////////////////////////
#define STAT ((unsigned short) 0xFF41)

#define STAT_INTERRUPT_LYC ((unsigned char) 0x40)
#define STAT_INTERRUPT_MODE_10 ((unsigned char) 0x20)
#define STAT_INTERRUPT_MODE_01 ((unsigned char) 0x10)
#define STAT_INTERRUPT_MODE_00 ((unsigned char) 0x08)
#define STAT_LYC ((unsigned char) 0x04)
#define STAT_MODE ((unsigned char) 0x03)
#define STAT_MODE_00 ((unsigned char) 0x00) // HBLANK
#define STAT_MODE_01 ((unsigned char) 0x01) // VBLANK
#define STAT_MODE_10 ((unsigned char) 0x02) // Searching OAM RAM
#define STAT_MODE_11 ((unsigned char) 0x03) // Transfer to LCD

// OTHER VIDEO REGS ////////////////////////////////////////////////////////////

#define SCY ((unsigned short) 0xFF42)
#define SCX ((unsigned short) 0xFF43)
#define LY ((unsigned short) 0xFF44)
#define LYC ((unsigned short) 0xFF45)

#endif // __MEMORY_H_INCLUDED__
