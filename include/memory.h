#ifndef __MEMORY_H_INCLUDED__
#define __MEMORY_H_INCLUDED__

struct memory;

typedef int (*memory_get_hook)(struct memory*, unsigned short);

typedef int (*memory_set_hook)(struct memory*, unsigned short, unsigned char);

#define MAX_MEMORY_HOOKS 16

#define MEMORY_HOOK_RESULT ((int) 0x8000)

struct memory {
  memory_get_hook gethooks[MAX_MEMORY_HOOKS];
  int gethookstop;
  memory_set_hook sethooks[MAX_MEMORY_HOOKS];
  int sethookstop;
  unsigned char mem[64*1024];
};

void memory_init(struct memory* mem);

unsigned char memory_get_d8(struct memory* mem, unsigned short offset);
void memory_set_d8(struct memory* mem, unsigned short offset, unsigned char value);

void memory_register_get_hook(struct memory* mem, memory_get_hook hook);
void memory_unregister_get_hook(struct memory* mem, memory_get_hook hook);

void memory_register_set_hook(struct memory* mem, memory_set_hook hook);
void memory_unregister_set_hook(struct memory* mem, memory_set_hook hook);

unsigned char memory_get_interrupt_flag(struct memory* mem);
void memory_set_interrupt_flag(struct memory* mem, unsigned char mask);
void memory_clear_interrupt_flag(struct memory* mem, unsigned char mask);

unsigned char memory_get_interrupt_enabled(struct memory* mem);

// CARTRIDGE ///////////////////////////////////////////////////////////////////
#define CARTRIDGE_TITLE ((unsigned short) 0x134)
#define CARTRIDGE_TITLE_LEN ((unsigned short) 15

#define CARTRIDGE_TYPE                   ((unsigned short) 0x147)
#define CARTRIDGE_TYPE_ROM               ((unsigned char) 0)
#define CARTRIDGE_TYPE_ROM_MBC1          ((unsigned char) 1)
#define CARTRIDGE_TYPE_ROM_MBC1_RAM      ((unsigned char) 2)
#define CARTRIDGE_TYPE_ROM_MBC1_RAM_BATT ((unsigned char) 3)
// TODO Add remaining constants

#define CARTRIDGE_ROM_SIZE               ((unsigned short) 0x148)
#define CARTRIDGE_ROM_SIZE_32KB          ((unsigned char) 0x00)
#define CARTRIDGE_ROM_SIZE_64KB          ((unsigned char) 0x01)
#define CARTRIDGE_ROM_SIZE_128KB         ((unsigned char) 0x02)
#define CARTRIDGE_ROM_SIZE_256KB         ((unsigned char) 0x03)
#define CARTRIDGE_ROM_SIZE_512KB         ((unsigned char) 0x04)
// TODO Add remaining constants

#define CARTRIDGE_RAM_SIZE               ((unsigned short) 0x149)
#define CARTRIDGE_RAM_SIZE_2KB           ((unsigned char) 0x01)
#define CARTRIDGE_RAM_SIZE_8KB           ((unsigned char) 0x02)
#define CARTRIDGE_RAM_SIZE_32KB          ((unsigned char) 0x03)
#define CARTRIDGE_RAM_SIZE_128KB         ((unsigned char) 0x04)

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

// OTHER CONTROL REGS //////////////////////////////////////////////////////////

#define INTERRUPT_MASK_VBLANK ((unsigned char) 0x01)
#define INTERRUPT_MASK_LCDC ((unsigned char) 0x02)
#define INTERRUPT_MASK_TIMER ((unsigned char) 0x04)
#define INTERRUPT_MASK_SERIAL ((unsigned char) 0x08)
#define INTERRUPT_MASK_JOYPAD ((unsigned char) 0x10)

#define IF ((unsigned short) 0xFF0F)
#define IE ((unsigned short) 0xFFFF)

// INTERRUPTS //////////////////////////////////////////////////////////////////

#define INTERRUPT_VBLANK_ROUTINE_ADDR ((unsigned short) 0x0040)

// PALETTE /////////////////////////////////////////////////////////////////////
#define BG_PALETTE ((unsigned short) 0xFF47)
#define BG_PALETTE_00 ((unsigned char) 0x03)
#define BG_PALETTE_01 ((unsigned char) 0x0C)
#define BG_PALETTE_10 ((unsigned char) 0x30)
#define BG_PALETTE_11 ((unsigned char) 0xC0)

// MISCELLANEOUS ///////////////////////////////////////////////////////////////
#define MAP_CARTRIDGE ((unsigned short) 0xFF50)

#endif // __MEMORY_H_INCLUDED__
