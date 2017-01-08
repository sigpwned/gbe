#include <stdio.h>
#include "gbe.h"
#include "cartridge.h"
#include "memory.h"

void cartridge_init(struct cartridge* cartridge, FILE* f) {
  memset(cartridge, 0, sizeof(struct cartridge));

  // This is not guaranteed to work by the standard. However, it seems pretty
  // reasonable to me. We can replace with platform-specific code if needed.
  // http://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
  fseek(f, 0L, SEEK_END);
  size_t datalen=ftell(f);
  rewind(f);

  unsigned char* data=malloc(datalen);
  gbe_read_fully(f, data, datalen);

  cartridge->type = data[CARTRIDGE_TYPE];
  cartridge->rom_size = data[CARTRIDGE_ROM_SIZE];
  cartridge->ram_size = data[CARTRIDGE_RAM_SIZE];

  cartridge->data = data;
  cartridge->datalen = datalen;
}

void cartridge_destroy(struct cartridge* cartridge) {
  free(cartridge->data);
}

unsigned char cartridge_get_d8(struct cartridge* cartridge, unsigned short offset) {
  unsigned char result;
    
  switch(cartridge->type) {
  case CARTRIDGE_TYPE_ROM:
    result = cartridge->data[offset];
    break;
  case CARTRIDGE_TYPE_ROM_MBC1:
  case CARTRIDGE_TYPE_ROM_MBC1_RAM:
  case CARTRIDGE_TYPE_ROM_MBC1_RAM_BATT:
    {
      if(offset < 0x4000) {
        // Always "ram bank 0," which is just the beginning of the cart.
        result = cartridge->data[offset];
      } else
      if(offset>=0x4000 && offset<0x8000) {
        // This uses the proper ROM bank
        unsigned char bank=cartridge->rom_bank & 0x1F;
        if(bank == 0)
          bank = 1;
        unsigned short offsetp=0x4000*bank+(offset-0x4000);
        result = cartridge->data[offsetp];
      } else
      if(offset>=0xA000 && offset<0xC000) {
        // TODO Implement RAM bank switching
        result = 0;
      }
      else {
        // Uh... this should not come to the cartridge.
        result = 0;
      }
    } break;
  default:
    // TODO Implement other banking
    result = 0;
    break;
  }

  return result;
}

void cartridge_set_d8(struct cartridge* cartridge, unsigned short offset, unsigned char value) {
  switch(cartridge->type) {
  case CARTRIDGE_TYPE_ROM:
    // Ignore this
    break;
  case CARTRIDGE_TYPE_ROM_MBC1:
  case CARTRIDGE_TYPE_ROM_MBC1_RAM:
  case CARTRIDGE_TYPE_ROM_MBC1_RAM_BATT:
    {
      if(offset>=0x2000 && offset<0x4000) {
        cartridge->rom_bank = value & 0x1F;
      }
      else {
        // Ignore
      }
    } break;
  }
}
