#ifndef __GBE_H_INCLUDED__
#define __GBE_H_INCLUDED__

#include <stdio.h>
#include <time.h>

#define VMEM_WIDTH 256
#define VMEM_HEIGHT 256

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

#define ERR_BAD_OPCODE 1
#define ERR_SDL 2
#define ERR_MEMORY_HOOKS 3
#define ERR_BAD_CARTRIDGE 4


#ifdef __cplusplus
extern "C" {
#endif

void gbe_setup();

void gbe_cleanup();

void gbe_gettime(struct timespec *tp);

int gbe_read_fully(FILE* fp, unsigned char* offset, size_t length);


#ifdef __cplusplus
}
#endif

#endif // __GBE_H_INCLUDED__
