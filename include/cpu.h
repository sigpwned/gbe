#ifndef __CPU_H_INCLUDED__
#define __CPU_H_INCLUDED__

#include "memory.h"

#ifdef __cplusplus 
extern "C" {
#endif

struct registers {
  unsigned char  r8[8];
  unsigned short sp;
  unsigned short pc;
};

struct cpu {
  struct registers regs;
  struct memory* memory;
  unsigned char busy;
  unsigned char ime;
  unsigned char halted;
  unsigned char stopped;
};

// LIFECYLE ////////////////////////////////////////////////////////////////////
void cpu_init(struct cpu* p, struct memory* memory);

void cpu_tick(struct cpu* p);

// 8-BIT REGISTERS /////////////////////////////////////////////////////////////
unsigned char cpu_get_a(struct cpu* p);
void cpu_set_a(struct cpu* p, unsigned char a);

unsigned char cpu_get_f(struct cpu* p);
void cpu_set_f(struct cpu* p, unsigned char f);

unsigned char cpu_get_b(struct cpu* p);
void cpu_set_b(struct cpu* p, unsigned char b);

unsigned char cpu_get_c(struct cpu* p);
void cpu_set_c(struct cpu* p, unsigned char c);

unsigned char cpu_get_d(struct cpu* p);
void cpu_set_d(struct cpu* p, unsigned char d);

unsigned char cpu_get_e(struct cpu* p);
void cpu_set_e(struct cpu* p, unsigned char e);

unsigned char cpu_get_h(struct cpu* p);
void cpu_set_h(struct cpu* p, unsigned char h);

unsigned char cpu_get_l(struct cpu* p);
void cpu_set_l(struct cpu* p, unsigned char l);

// 16-BIT REGISTERS ////////////////////////////////////////////////////////////
unsigned short cpu_get_af(struct cpu* p);
void cpu_set_af(struct cpu* p, unsigned short af);

unsigned short cpu_get_bc(struct cpu* p);
void cpu_set_bc(struct cpu* p, unsigned short bc);

unsigned short cpu_get_de(struct cpu* p);
void cpu_set_de(struct cpu* p, unsigned short de);

unsigned short cpu_get_hl(struct cpu* p);
void cpu_set_hl(struct cpu* p, unsigned short hl);

// CONTROL REGISTERS ///////////////////////////////////////////////////////////
  
unsigned short cpu_get_sp(struct cpu* p);
void cpu_set_sp(struct cpu* p, unsigned short sp);

unsigned short cpu_get_pc(struct cpu* p);
void cpu_set_pc(struct cpu* p, unsigned short pc);

unsigned char cpu_get_ime(struct cpu* p);
void cpu_set_ime(struct cpu* p, unsigned char ime);

// SPECIAL OPERATIONS //////////////////////////////////////////////////////////

void cpu_push_pc(struct cpu* p);

#ifdef __cplusplus 
}
#endif

#endif // __CPU_H_INCLUDED__
