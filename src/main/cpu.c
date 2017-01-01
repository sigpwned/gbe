#include <string.h>
#include "cpu.h"

#define UCS_TO_US(h, l) ( ((unsigned short)((unsigned char)(l))) | (((unsigned short)((unsigned char)(h))) << 8) )
#define US_TO_LUC(s) ((unsigned char)(((unsigned short)(s)) >> 0))
#define US_TO_HUC(s) ((unsigned char)(((unsigned short)(s)) >> 8))

// LIFECYCLE ///////////////////////////////////////////////////////////////////
void cpu_init(struct cpu* p) {
  memset(p, 0, sizeof(struct cpu));
}

// 8-BIT REGISTERS /////////////////////////////////////////////////////////////
unsigned char cpu_get_a(struct cpu* p) {
  return p->a;
}

void cpu_set_a(struct cpu* p, unsigned char a) {
  p->a = a;
}

unsigned char cpu_get_f(struct cpu* p) {
  return p->f;
}

void cpu_set_f(struct cpu* p, unsigned char f) {
  p->f = f;
}

unsigned char cpu_get_b(struct cpu* p) {
  return p->b;
}

void cpu_set_b(struct cpu* p, unsigned char b) {
  p->b = b;
}

unsigned char cpu_get_c(struct cpu* p) {
  return p->c;
}

void cpu_set_c(struct cpu* p, unsigned char c) {
  p->c = c;
}

unsigned char cpu_get_d(struct cpu* p) {
  return p->d;
}

void cpu_set_d(struct cpu* p, unsigned char d) {
  p->d = d;
}

unsigned char cpu_get_e(struct cpu* p) {
  return p->e;
}

void cpu_set_e(struct cpu* p, unsigned char e) {
  p->e = e;
}

unsigned char cpu_get_h(struct cpu* p) {
  return p->h;
}

void cpu_set_h(struct cpu* p, unsigned char h) {
  p->h = h;
}

unsigned char cpu_get_l(struct cpu* p) {
  return p->l;
}

void cpu_set_l(struct cpu* p, unsigned char l) {
  p->l = l;
}

// 16-BIT REGISTERS ////////////////////////////////////////////////////////////
unsigned short cpu_get_af(struct cpu* p) {
  unsigned char a=cpu_get_a(p);
  unsigned char f=cpu_get_f(p);
  return UCS_TO_US(a, f);
}

void cpu_set_af(struct cpu* p, unsigned short af) {
  unsigned char a=US_TO_HUC(af);
  unsigned char f=US_TO_LUC(af);
  cpu_set_a(p, a);
  cpu_set_f(p, f);
}

unsigned short cpu_get_bc(struct cpu* p) {
  unsigned char b=cpu_get_b(p);
  unsigned char c=cpu_get_c(p);
  return UCS_TO_US(b, c);
}

void cpu_set_bc(struct cpu* p, unsigned short bc) {
  unsigned char b=US_TO_HUC(bc);
  unsigned char c=US_TO_LUC(bc);
  cpu_set_b(p, b);
  cpu_set_c(p, c);
}

unsigned short cpu_get_de(struct cpu* p) {
  unsigned char d=cpu_get_d(p);
  unsigned char e=cpu_get_e(p);
  return UCS_TO_US(d, e);
}

void cpu_set_de(struct cpu* p, unsigned short de) {
  unsigned char d=US_TO_HUC(de);
  unsigned char e=US_TO_LUC(de);
  cpu_set_d(p, d);
  cpu_set_e(p, e);
}

unsigned short cpu_get_hl(struct cpu* p) {
  unsigned char h=cpu_get_h(p);
  unsigned char l=cpu_get_l(p);
  return UCS_TO_US(h, l);
}

void cpu_set_hl(struct cpu* p, unsigned short hl) {
  unsigned char h=US_TO_HUC(hl);
  unsigned char l=US_TO_LUC(hl);
  cpu_set_h(p, h);
  cpu_set_l(p, l);
}

unsigned short cpu_get_sp(struct cpu* p) {
  return p->sp;
}

void cpu_set_sp(struct cpu* p, unsigned short sp) {
  p->sp = sp;
}

unsigned short cpu_get_pc(struct cpu* p) {
  return p->pc;
}

void cpu_set_pc(struct cpu* p, unsigned short pc) {
  p->pc = pc;
}
