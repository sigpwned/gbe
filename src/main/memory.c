#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gbe.h"
#include "memory.h"

void memory_init(struct memory* mem) {
  memset(mem, 0, sizeof(struct memory));
}

unsigned char memory_get_d8(struct memory* mem, unsigned short offset) {
  int result=0;
  if(offset >= 0x8000) {
    for(int i=0;i<mem->gethookstop;i++) {
      result = mem->gethooks[i](mem, offset);
      if(result != 0)
        break;
    }
  }
  if(result == 0)
    result = mem->mem[offset];
  return (unsigned char) result;
}

void memory_set_d8(struct memory* mem, unsigned short offset, unsigned char d8) {
  int result=0;
  if(offset >= 0x8000) {
    for(int i=0;i<mem->sethookstop;i++) {
      result = mem->sethooks[i](mem, offset, d8);
      if(result != 0)
        break;
    }
  }
  if(result == 0)
    mem->mem[offset] = d8;
}

void memory_register_get_hook(struct memory* mem, memory_get_hook hook) {
  if(mem->gethookstop == MAX_MEMORY_HOOKS)
    exit(ERR_MEMORY_HOOKS);
  mem->gethooks[mem->gethookstop++] = hook;
}

void memory_unregister_get_hook(struct memory* mem, memory_get_hook hook) {
  int index=0;
  while(index < mem->gethookstop) {
    if(mem->gethooks[index] == hook) {
      while(index+1 < mem->gethookstop) {
        mem->gethooks[index] = mem->gethooks[index+1];
        index = index+1;
      }
      mem->gethookstop = mem->gethookstop-1;
    }
    else {
      index = index+1;
    }
  }
}

void memory_register_set_hook(struct memory* mem, memory_set_hook hook) {
  if(mem->sethookstop == MAX_MEMORY_HOOKS)
    exit(ERR_MEMORY_HOOKS);
  mem->sethooks[mem->sethookstop++] = hook;
}

void memory_unregister_set_hook(struct memory* mem, memory_set_hook hook) {
  int index=0;
  while(index < mem->sethookstop) {
    if(mem->sethooks[index] == hook) {
      while(index+1 < mem->sethookstop) {
        mem->sethooks[index] = mem->sethooks[index+1];
        index = index+1;
      }
      mem->sethookstop = mem->sethookstop-1;
    }
    else {
      index = index+1;
    }
  }
}
