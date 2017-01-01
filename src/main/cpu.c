#include <string.h>
#include "cpu.h"
#include "opcodes.h"

#define ZF ((unsigned char)(0x80))
#define NF ((unsigned char)(0x40))
#define HF ((unsigned char)(0x20))
#define CF ((unsigned char)(0x10))

#define RA (1)
#define RF (0)
#define RB (3)
#define RC (2)
#define RD (5)
#define RE (4)
#define RH (7)
#define RL (6)

#define RAF RF
#define RBC RC
#define RDE RE
#define RHL RL

#define UCS_TO_US(h, l) ( ((unsigned short)((unsigned char)(l))) | (((unsigned short)((unsigned char)(h))) << 8) )
#define US_TO_LUC(s) ((unsigned char)(((unsigned short)(s)) >> 0))
#define US_TO_HUC(s) ((unsigned char)(((unsigned short)(s)) >> 8))

unsigned char cpu_get_r8(struct cpu* p, int ri);
void cpu_set_r8(struct cpu* p, int ri, unsigned char v);

unsigned short cpu_get_r16(struct cpu* p, int ri);
void cpu_set_r16(struct cpu* p, int ri, unsigned short v);

unsigned char cpu_get_m8(struct cpu* p, int mi);
void cpu_set_m8(struct cpu* p, int mi, unsigned char v);

unsigned short cpu_get_m16(struct cpu* p, int mi);
void cpu_set_m16(struct cpu* p, int mi, unsigned short v);

// LIFECYCLE ///////////////////////////////////////////////////////////////////
void cpu_init(struct cpu* p, unsigned char* memory) {
  memset(p, 0, sizeof(struct cpu));
  p->memory = memory;
}

void cpu_tick(struct cpu* p) {
  unsigned char opcode=p->memory[p->regs.pc];
  switch(opcode) {
  case ADC_A_A:
  case ADC_A_B:
  case ADC_A_C:
  case ADC_A_D8:
  case ADC_A_D:
  case ADC_A_E:
  case ADC_A_H:
  case ADC_A_HL_IND:
  case ADC_A_L:
  case ADD_A_A:
  case ADD_A_B:
  case ADD_A_C:
  case ADD_A_D8:
  case ADD_A_D:
  case ADD_A_E:
  case ADD_A_H:
  case ADD_A_HL_IND:
  case ADD_A_L:
  case ADD_HL_BC:
  case ADD_HL_DE:
  case ADD_HL_HL:
  case ADD_HL_SP:
  case ADD_SP_R8:
  case AND_A:
  case AND_B:
  case AND_C:
  case AND_D8:
  case AND_D:
  case AND_E:
  case AND_H:
  case AND_HL_IND:
  case AND_L:
  case CALL_A16:
  case CALL_C_A16:
  case CALL_NC_A16:
  case CALL_NZ_A16:
  case CALL_Z_A16:
  case CCF:
  case CPL:
  case CP_A_A:
  case CP_A_B:
  case CP_A_C:
  case CP_A_D:
  case CP_A_E:
  case CP_A_H:
  case CP_A_HL_IND:
  case CP_A_L:
  case CP_D8:
  case DAA:
  case DEC_A:
  case DEC_B:
  case DEC_BC:
  case DEC_C:
  case DEC_D:
  case DEC_DE:
  case DEC_E:
  case DEC_H:
  case DEC_HL:
  case DEC_HL_IND:
  case DEC_L:
  case DEC_SP:
  case DI:
  case EI:
  case HALT:
  case INC_A:
  case INC_B:
  case INC_BC:
  case INC_C:
  case INC_D:
  case INC_DE:
  case INC_E:
  case INC_H:
  case INC_HL:
  case INC_HL_IND:
  case INC_L:
  case INC_SP:
  case JP_A16:
  case JP_C_A16:
  case JP_HL_IND:
  case JP_NC_A16:
  case JP_NZ_A16:
  case JP_Z_A16:
  case JR_C_R8:
  case JR_NC_R8:
  case JR_NZ_R8:
  case JR_R8:
  case JR_Z_R8:
  case LDH_A8_IND_A:
  case LDH_A_A8_IND:
  case LD_A16_IND_A:
  case LD_A_A16_IND:
  case LD_A_A:
  case LD_A_B:
  case LD_A_C:
  case LD_A_C_IND:
  case LD_A_D8:
  case LD_A_D:
  case LD_A_E:
  case LD_A_H:
  case LD_A_HL_IND:
  case LD_A_IND_BC:
  case LD_A_IND_DE:
  case LD_A_IND_HL_MINUS:
  case LD_A_IND_HL_PLUS:
  case LD_A_L:
  case LD_BC_D16:
  case LD_B_A:
  case LD_B_B:
  case LD_B_C:
  case LD_B_D8:
  case LD_B_D:
  case LD_B_E:
  case LD_B_H:
  case LD_B_HL_IND:
  case LD_B_L:
  case LD_C_A:
  case LD_C_B:
  case LD_C_C:
  case LD_C_D8:
  case LD_C_D:
  case LD_C_E:
  case LD_C_H:
  case LD_C_HL_IND:
  case LD_C_IND_A:
  case LD_C_L:
  case LD_DE_D16:
  case LD_D_A:
  case LD_D_B:
  case LD_D_C:
  case LD_D_D8:
  case LD_D_D:
  case LD_D_E:
  case LD_D_H:
  case LD_D_HL_IND:
  case LD_D_L:
  case LD_E_A:
  case LD_E_B:
  case LD_E_C:
  case LD_E_D8:
  case LD_E_D:
  case LD_E_E:
  case LD_E_H:
  case LD_E_HL_IND:
  case LD_E_L:
  case LD_HL_D16:
  case LD_HL_IND_A:
  case LD_HL_IND_B:
  case LD_HL_IND_C:
  case LD_HL_IND_D8:
  case LD_HL_IND_D:
  case LD_HL_IND_E:
  case LD_HL_IND_H:
  case LD_HL_IND_L:
  case LD_HL_SP_PLUS_R8:
  case LD_H_A:
  case LD_H_B:
  case LD_H_C:
  case LD_H_D8:
  case LD_H_D:
  case LD_H_E:
  case LD_H_H:
  case LD_H_HL_IND:
  case LD_H_L:
  case LD_IND_A16_SP:
  case LD_IND_BC_A:
  case LD_IND_DE_A:
  case LD_IND_HL_MINUS_A:
  case LD_IND_HL_PLUS_A:
  case LD_L_A:
  case LD_L_B:
  case LD_L_C:
  case LD_L_D8:
  case LD_L_D:
  case LD_L_E:
  case LD_L_H:
  case LD_L_HL_IND:
  case LD_L_L:
  case LD_SP_D16:
  case LD_SP_HL:
  case NOP:
  case OR_A:
  case OR_B:
  case OR_C:
  case OR_D8:
  case OR_D:
  case OR_E:
  case OR_H:
  case OR_HL_IND:
  case OR_L:
  case POP_AF:
  case POP_BC:
  case POP_DE:
  case POP_HL:
  case PREFIX_CB:
  case PUSH_AF:
  case PUSH_BC:
  case PUSH_DE:
  case PUSH_HL:
  case RET:
  case RETI:
  case RET_C:
  case RET_NC:
  case RET_NZ:
  case RET_Z:
  case RLA:
  case RLCA:
  case RRA:
  case RRCA:
  case RST_00H:
  case RST_08H:
  case RST_10H:
  case RST_18H:
  case RST_20H:
  case RST_28H:
  case RST_30H:
  case RST_38H:
  case SBC_A_A:
  case SBC_A_B:
  case SBC_A_C:
  case SBC_A_D8:
  case SBC_A_D:
  case SBC_A_E:
  case SBC_A_H:
  case SBC_A_HL_IND:
  case SBC_A_L:
  case SCF:
  case STOP:
  case SUB_A:
  case SUB_B:
  case SUB_C:
  case SUB_D8:
  case SUB_D:
  case SUB_E:
  case SUB_H:
  case SUB_HL_IND:
  case SUB_L:
  case XOR_A_A:
  case XOR_A_B:
  case XOR_A_C:
  case XOR_A_D:
  case XOR_A_E:
  case XOR_A_H:
  case XOR_A_HL_IND:
  case XOR_A_L:
  case XOR_D8:
  default:
    break;
  }
}

// 8-BIT REGISTERS /////////////////////////////////////////////////////////////
unsigned char cpu_get_a(struct cpu* p) {
  return cpu_get_r8(p, RA);
}

void cpu_set_a(struct cpu* p, unsigned char a) {
  cpu_set_r8(p, RA, a);
}

unsigned char cpu_get_f(struct cpu* p) {
  return cpu_get_r8(p, RF);
}

void cpu_set_f(struct cpu* p, unsigned char f) {
  cpu_set_r8(p, RF, f);
}

unsigned char cpu_get_b(struct cpu* p) {
  return cpu_get_r8(p, RB);
}

void cpu_set_b(struct cpu* p, unsigned char b) {
  cpu_set_r8(p, RB, b);
}

unsigned char cpu_get_c(struct cpu* p) {
  return cpu_get_r8(p, RC);
}

void cpu_set_c(struct cpu* p, unsigned char c) {
  cpu_set_r8(p, RC, c);
}

unsigned char cpu_get_d(struct cpu* p) {
  return cpu_get_r8(p, RD);
}

void cpu_set_d(struct cpu* p, unsigned char d) {
  cpu_set_r8(p, RD, d);
}

unsigned char cpu_get_e(struct cpu* p) {
  return cpu_get_r8(p, RE);
}

void cpu_set_e(struct cpu* p, unsigned char e) {
  cpu_set_r8(p, RE, e);
}

unsigned char cpu_get_h(struct cpu* p) {
  return cpu_get_r8(p, RH);
}

void cpu_set_h(struct cpu* p, unsigned char h) {
  cpu_set_r8(p, RH, h);
}

unsigned char cpu_get_l(struct cpu* p) {
  return cpu_get_r8(p, RL);
}

void cpu_set_l(struct cpu* p, unsigned char l) {
  cpu_set_r8(p, RL, l);
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
  return p->regs.sp;
}

void cpu_set_sp(struct cpu* p, unsigned short sp) {
  p->regs.sp = sp;
}

unsigned short cpu_get_pc(struct cpu* p) {
  return p->regs.pc;
}

void cpu_set_pc(struct cpu* p, unsigned short pc) {
  p->regs.pc = pc;
}

// REGISTERS ///////////////////////////////////////////////////////////////////
unsigned char cpu_get_r8(struct cpu* p, int ri) {
  return p->regs.r8[ri];
}

void cpu_set_r8(struct cpu* p, int ri, unsigned char v) {
  p->regs.r8[ri] = v;
}

unsigned short cpu_get_r16(struct cpu* p, int ri) {
  unsigned char l=cpu_get_r8(p, ri+0);
  unsigned char h=cpu_get_r8(p, ri+1);
  return UCS_TO_US(h, l);
}

void cpu_set_r16(struct cpu* p, int ri, unsigned short v) {
  unsigned char h=US_TO_HUC(v);
  unsigned char l=US_TO_LUC(v);
  cpu_set_r8(p, ri+0, l);
  cpu_set_r8(p, ri+1, h);
}

// MEMORY //////////////////////////////////////////////////////////////////////
unsigned char cpu_get_m8(struct cpu* p, int mi) {
  return p->memory[mi];
}

void cpu_set_m8(struct cpu* p, int mi, unsigned char v) {
  p->memory[mi] = v;
}

unsigned short cpu_get_m16(struct cpu* p, int mi) {
  // The GameBoy CPU architecture is Little-Endian!
  unsigned char l=cpu_get_m8(p, mi+0);
  unsigned char h=cpu_get_m8(p, mi+1);
  return UCS_TO_US(h, l);
}

void cpu_set_m16(struct cpu* p, int mi, unsigned short v) {
  unsigned char l=US_TO_LUC(v);
  unsigned char h=US_TO_HUC(v);
  cpu_set_m8(p, mi+0, l);
  cpu_set_m8(p, mi+1, h);
}
