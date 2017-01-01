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

unsigned char cpu_get_r8(struct cpu* cpu, int ri);
void cpu_set_r8(struct cpu* cpu, int ri, unsigned char v);

unsigned short cpu_get_r16(struct cpu* cpu, int ri);
void cpu_set_r16(struct cpu* cpu, int ri, unsigned short v);

unsigned char cpu_get_m8(struct cpu* cpu, int mi);
void cpu_set_m8(struct cpu* cpu, int mi, unsigned char v);

unsigned short cpu_get_m16(struct cpu* cpu, int mi);
void cpu_set_m16(struct cpu* cpu, int mi, unsigned short v);

void cpu_adc_r8(struct cpu* cpu, int rb);
void cpu_adc_d8(struct cpu* cpu, unsigned char d8);
void cpu_adc_ind8(struct cpu* cpu, unsigned short p);

void cpu_add8_r8(struct cpu* cpu, int rb);
void cpu_add8_d8(struct cpu* cpu, unsigned char d8);
void cpu_add8_ind8(struct cpu* cpu, unsigned short p);

void cpu_add16_r16(struct cpu* cpu, int rb);
void cpu_add16_d16(struct cpu* cpu, unsigned short d16);
void cpu_add16_sp(struct cpu* cpu, signed char d8);

void cpu_and_r8(struct cpu* cpu, int rb);
void cpu_and_d8(struct cpu* cpu, unsigned char d8);
void cpu_and_ind8(struct cpu* cpu, unsigned short p);

void cpu_cp_r8(struct cpu* cpu, int rb);
void cpu_cp_d8(struct cpu* cpu, unsigned char d8);
void cpu_cp_ind8(struct cpu* cpu, unsigned short p);

void cpu_dec8_r8(struct cpu* cpu, int rb);
void cpu_dec8_ind8(struct cpu* cpu);
void cpu_dec16_r16(struct cpu* cpu, int rb);
void cpu_dec16_sp(struct cpu* cpu);

void cpu_inc8_r8(struct cpu* cpu, int rb);
void cpu_inc8_ind8(struct cpu* cpu);
void cpu_inc16_r16(struct cpu* cpu, int rb);
void cpu_inc16_sp(struct cpu* cpu);

// LIFECYCLE ///////////////////////////////////////////////////////////////////
void cpu_init(struct cpu* cpu, unsigned char* memory) {
  memset(cpu, 0, sizeof(struct cpu));
  cpu->memory = memory;
}

void cpu_tick(struct cpu* cpu) {
  unsigned char opcode=cpu->memory[cpu->regs.pc++];
  switch(opcode) {
  // ADC ///////////////////////////////////////////////////////////////////////
  case ADC_A_A:
    cpu_adc_r8(cpu, RA);
    break;
  case ADC_A_B:
    cpu_adc_r8(cpu, RB);
    break;
  case ADC_A_C:
    cpu_adc_r8(cpu, RC);
    break;
  case ADC_A_D:
    cpu_adc_r8(cpu, RD);
    break;
  case ADC_A_E:
    cpu_adc_r8(cpu, RE);
    break;
  case ADC_A_H:
    cpu_adc_r8(cpu, RH);
    break;
  case ADC_A_L:
    cpu_adc_r8(cpu, RL);
    break;

  case ADC_A_D8:
    {
      unsigned char d8=cpu->memory[cpu->regs.pc++];
      cpu_adc_d8(cpu, d8);
    } break;
  case ADC_A_HL_IND:
    {
      unsigned char l=cpu->memory[cpu->regs.pc++];
      unsigned char h=cpu->memory[cpu->regs.pc++];
      unsigned short p=UCS_TO_US(h, l);
      cpu_adc_ind8(cpu, p);
    } break;

  // ADD ///////////////////////////////////////////////////////////////////////
  case ADD_A_A:
    cpu_add8_r8(cpu, RA);
    break;
  case ADD_A_B:
    cpu_add8_r8(cpu, RB);
    break;
  case ADD_A_C:
    cpu_add8_r8(cpu, RC);
    break;
  case ADD_A_D:
    cpu_add8_r8(cpu, RD);
    break;
  case ADD_A_E:
    cpu_add8_r8(cpu, RE);
    break;
  case ADD_A_H:
    cpu_add8_r8(cpu, RH);
    break;
  case ADD_A_L:
    cpu_add8_r8(cpu, RL);
    break;

  case ADD_A_D8:
    {
      unsigned char d8=cpu->memory[cpu->regs.pc++];
      cpu_add8_d8(cpu, d8);
    } break;
  case ADD_A_HL_IND:
    {
      unsigned char l=cpu->memory[cpu->regs.pc++];
      unsigned char h=cpu->memory[cpu->regs.pc++];
      unsigned short p=UCS_TO_US(h, l);
      cpu_add8_ind8(cpu, p);
    } break;

  case ADD_HL_BC:
    cpu_add16_r16(cpu, RBC);
    break;
  case ADD_HL_DE:
    cpu_add16_r16(cpu, RDE);
    break;
  case ADD_HL_HL:
    cpu_add16_r16(cpu, RHL);
    break;
  case ADD_HL_SP:
    {
      unsigned short sp=cpu->regs.sp;
      cpu_add16_d16(cpu, sp);
    } break;

  case ADD_SP_R8:
    {
      signed char d8=(signed char) cpu->memory[cpu->regs.pc++];
      cpu_add16_sp(cpu, d8);
    } break;

  
  // AND ///////////////////////////////////////////////////////////////////////
  case AND_A:
    cpu_and_r8(cpu, RA);
    break;
  case AND_B:
    cpu_and_r8(cpu, RB);
    break;
  case AND_C:
    cpu_and_r8(cpu, RC);
    break;
  case AND_D:
    cpu_and_r8(cpu, RD);
    break;
  case AND_E:
    cpu_and_r8(cpu, RE);
    break;
  case AND_H:
    cpu_and_r8(cpu, RH);
    break;
  case AND_L:
    cpu_and_r8(cpu, RL);
    break;

  case AND_D8:
    {
      unsigned char d8=cpu->memory[cpu->regs.pc++];
      cpu_and_d8(cpu, d8);
    } break;
  case AND_HL_IND:
    {
      unsigned char l=cpu->memory[cpu->regs.pc++];
      unsigned char h=cpu->memory[cpu->regs.pc++];
      unsigned short p=UCS_TO_US(h, l);
      cpu_and_ind8(cpu, p);
    } break;

  // CALL //////////////////////////////////////////////////////////////////////
  case CALL_A16:
  case CALL_C_A16:
  case CALL_NC_A16:
  case CALL_NZ_A16:
  case CALL_Z_A16:

  // CF ////////////////////////////////////////////////////////////////////////
  case CCF:
    {
      unsigned char f=cpu_get_r8(cpu, RF);
      f = (f & ~NF & ~HF) ^ CF;
      cpu_set_r8(cpu, RF, f);
    } break;
  case SCF:
    {
      unsigned char f=cpu_get_r8(cpu, RF);
      f = (f & ~NF & ~HF) | CF;
      cpu_set_r8(cpu, RF, f);
    } break;

  // CPL ///////////////////////////////////////////////////////////////////////
  case CPL:
    {
      unsigned char a=cpu_get_r8(cpu, RA);
      a = ~a;
      cpu_set_r8(cpu, RA, a);

      unsigned char f=cpu_get_r8(cpu, RF);
      f = f | NF | HF;
      cpu_set_r8(cpu, RF, f);
    } break;

  // CP ////////////////////////////////////////////////////////////////////////
  case CP_A_A:
    cpu_cp_r8(cpu, RA);
    break;
  case CP_A_B:
    cpu_cp_r8(cpu, RB);
    break;
  case CP_A_C:
    cpu_cp_r8(cpu, RC);
    break;
  case CP_A_D:
    cpu_cp_r8(cpu, RD);
    break;
  case CP_A_E:
    cpu_cp_r8(cpu, RE);
    break;
  case CP_A_H:
    cpu_cp_r8(cpu, RH);
    break;
  case CP_A_L:
    cpu_cp_r8(cpu, RL);
    break;
  case CP_D8:
    {
      unsigned char d8=cpu->memory[cpu->regs.pc++];
      cpu_cp_d8(cpu, d8);
    } break;
  case CP_A_HL_IND:
    {
      unsigned char l=cpu->memory[cpu->regs.pc++];
      unsigned char h=cpu->memory[cpu->regs.pc++];
      unsigned short p=UCS_TO_US(h, l);
      cpu_cp_ind8(cpu, p);
    } break;

  case DAA:
    // wat
    break;

  case DEC_A:
    cpu_dec8_r8(cpu, RA);
    break;
  case DEC_B:
    cpu_dec8_r8(cpu, RB);
    break;
  case DEC_C:
    cpu_dec8_r8(cpu, RC);
    break;
  case DEC_D:
    cpu_dec8_r8(cpu, RD);
    break;
  case DEC_E:
    cpu_dec8_r8(cpu, RE);
    break;
  case DEC_H:
    cpu_dec8_r8(cpu, RH);
    break;
  case DEC_L:
    cpu_dec8_r8(cpu, RL);
    break;
  case DEC_HL_IND:
    cpu_dec8_ind8(cpu);
    break;

  case DEC_BC:
    cpu_dec16_r16(cpu, RBC);
    break;
  case DEC_DE:
    cpu_dec16_r16(cpu, RDE);
    break;
  case DEC_HL:
    cpu_dec16_r16(cpu, RHL);
    break;
  case DEC_SP:
    cpu_dec16_sp(cpu);
    break;

  // INTERRUPTS ////////////////////////////////////////////////////////////////
  case DI:
  case EI:

  // INC ///////////////////////////////////////////////////////////////////////
  case INC_A:
    cpu_inc8_r8(cpu, RA);
    break;
  case INC_B:
    cpu_inc8_r8(cpu, RB);
    break;
  case INC_C:
    cpu_inc8_r8(cpu, RC);
    break;
  case INC_D:
    cpu_inc8_r8(cpu, RD);
    break;
  case INC_E:
    cpu_inc8_r8(cpu, RE);
    break;
  case INC_H:
    cpu_inc8_r8(cpu, RH);
    break;
  case INC_L:
    cpu_inc8_r8(cpu, RL);
    break;
  case INC_HL_IND:
    cpu_inc8_ind8(cpu);
    break;

  case INC_BC:
    cpu_inc16_r16(cpu, RBC);
    break;
  case INC_DE:
    cpu_inc16_r16(cpu, RDE);
    break;
  case INC_HL:
    cpu_inc16_r16(cpu, RHL);
    break;
  case INC_SP:
    cpu_inc16_sp(cpu);
    break;

  // JUMP //////////////////////////////////////////////////////////////////////
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
  case LD_A_D:
  case LD_A_E:
  case LD_A_H:
  case LD_A_L:
  case LD_A_D8:
  case LD_A_HL_IND:

  case LD_A_BC_IND:
  case LD_A_DE_IND:
  case LD_A_HL_IND_MINUS:
  case LD_A_HL_IND_PLUS:

  case LD_B_A:
  case LD_B_B:
  case LD_B_C:
  case LD_B_D:
  case LD_B_E:
  case LD_B_H:
  case LD_B_L:
  case LD_B_D8:
  case LD_B_HL_IND:

  case LD_C_A:
  case LD_C_B:
  case LD_C_C:
  case LD_C_D:
  case LD_C_E:
  case LD_C_H:
  case LD_C_L:
  case LD_C_D8:
  case LD_C_HL_IND:

  case LD_D_A:
  case LD_D_B:
  case LD_D_C:
  case LD_D_D:
  case LD_D_E:
  case LD_D_H:
  case LD_D_L:
  case LD_D_D8:
  case LD_D_HL_IND:

  case LD_E_A:
  case LD_E_B:
  case LD_E_C:
  case LD_E_D:
  case LD_E_E:
  case LD_E_H:
  case LD_E_L:
  case LD_E_D8:
  case LD_E_HL_IND:

  case LD_H_A:
  case LD_H_B:
  case LD_H_C:
  case LD_H_D:
  case LD_H_E:
  case LD_H_H:
  case LD_H_L:
  case LD_H_D8:
  case LD_H_HL_IND:

  case LD_L_A:
  case LD_L_B:
  case LD_L_C:
  case LD_L_D:
  case LD_L_E:
  case LD_L_H:
  case LD_L_L:
  case LD_L_D8:
  case LD_L_HL_IND:

  case LD_C_IND_A:
  case LD_A_C_IND:

  case LD_BC_D16:
  case LD_DE_D16:
  case LD_HL_D16:
  case LD_HL_IND_A:
  case LD_HL_IND_B:
  case LD_HL_IND_C:
  case LD_HL_IND_D:
  case LD_HL_IND_E:
  case LD_HL_IND_H:
  case LD_HL_IND_L:
  case LD_HL_IND_D8:
  case LD_HL_SP_PLUS_R8:

  case LD_A16_IND_SP:
  case LD_BC_IND_A:
  case LD_DE_IND_A:
  case LD_HL_IND_MINUS_A:
  case LD_HL_IND_PLUS_A:

  case LD_SP_D16:
  case LD_SP_HL:

  // NOP ///////////////////////////////////////////////////////////////////////
  case NOP:
    // Well that was easy! :)
    break;

  case OR_A:
  case OR_B:
  case OR_C:
  case OR_D:
  case OR_E:
  case OR_H:
  case OR_L:
  case OR_D8:
  case OR_HL_IND:

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
  case SBC_A_D:
  case SBC_A_E:
  case SBC_A_H:
  case SBC_A_L:
  case SBC_A_D8:
  case SBC_A_HL_IND:

  // STOP //////////////////////////////////////////////////////////////////////
  case HALT:
  case STOP:

  case SUB_A:
  case SUB_B:
  case SUB_C:
  case SUB_D:
  case SUB_E:
  case SUB_H:
  case SUB_L:
  case SUB_D8:
  case SUB_HL_IND:

  case XOR_A_A:
  case XOR_A_B:
  case XOR_A_C:
  case XOR_A_D:
  case XOR_A_E:
  case XOR_A_H:
  case XOR_A_L:
  case XOR_A_HL_IND:
  case XOR_D8:

  default:
    break;
  }
}

// 8-BIT REGISTERS /////////////////////////////////////////////////////////////
unsigned char cpu_get_a(struct cpu* cpu) {
  return cpu_get_r8(cpu, RA);
}

void cpu_set_a(struct cpu* cpu, unsigned char a) {
  cpu_set_r8(cpu, RA, a);
}

unsigned char cpu_get_f(struct cpu* cpu) {
  return cpu_get_r8(cpu, RF);
}

void cpu_set_f(struct cpu* cpu, unsigned char f) {
  cpu_set_r8(cpu, RF, f);
}

unsigned char cpu_get_b(struct cpu* cpu) {
  return cpu_get_r8(cpu, RB);
}

void cpu_set_b(struct cpu* cpu, unsigned char b) {
  cpu_set_r8(cpu, RB, b);
}

unsigned char cpu_get_c(struct cpu* cpu) {
  return cpu_get_r8(cpu, RC);
}

void cpu_set_c(struct cpu* cpu, unsigned char c) {
  cpu_set_r8(cpu, RC, c);
}

unsigned char cpu_get_d(struct cpu* cpu) {
  return cpu_get_r8(cpu, RD);
}

void cpu_set_d(struct cpu* cpu, unsigned char d) {
  cpu_set_r8(cpu, RD, d);
}

unsigned char cpu_get_e(struct cpu* cpu) {
  return cpu_get_r8(cpu, RE);
}

void cpu_set_e(struct cpu* cpu, unsigned char e) {
  cpu_set_r8(cpu, RE, e);
}

unsigned char cpu_get_h(struct cpu* cpu) {
  return cpu_get_r8(cpu, RH);
}

void cpu_set_h(struct cpu* cpu, unsigned char h) {
  cpu_set_r8(cpu, RH, h);
}

unsigned char cpu_get_l(struct cpu* cpu) {
  return cpu_get_r8(cpu, RL);
}

void cpu_set_l(struct cpu* cpu, unsigned char l) {
  cpu_set_r8(cpu, RL, l);
}

// 16-BIT REGISTERS ////////////////////////////////////////////////////////////
unsigned short cpu_get_af(struct cpu* cpu) {
  unsigned char a=cpu_get_a(cpu);
  unsigned char f=cpu_get_f(cpu);
  return UCS_TO_US(a, f);
}

void cpu_set_af(struct cpu* cpu, unsigned short af) {
  unsigned char a=US_TO_HUC(af);
  unsigned char f=US_TO_LUC(af);
  cpu_set_a(cpu, a);
  cpu_set_f(cpu, f);
}

unsigned short cpu_get_bc(struct cpu* cpu) {
  unsigned char b=cpu_get_b(cpu);
  unsigned char c=cpu_get_c(cpu);
  return UCS_TO_US(b, c);
}

void cpu_set_bc(struct cpu* cpu, unsigned short bc) {
  unsigned char b=US_TO_HUC(bc);
  unsigned char c=US_TO_LUC(bc);
  cpu_set_b(cpu, b);
  cpu_set_c(cpu, c);
}

unsigned short cpu_get_de(struct cpu* cpu) {
  unsigned char d=cpu_get_d(cpu);
  unsigned char e=cpu_get_e(cpu);
  return UCS_TO_US(d, e);
}

void cpu_set_de(struct cpu* cpu, unsigned short de) {
  unsigned char d=US_TO_HUC(de);
  unsigned char e=US_TO_LUC(de);
  cpu_set_d(cpu, d);
  cpu_set_e(cpu, e);
}

unsigned short cpu_get_hl(struct cpu* cpu) {
  unsigned char h=cpu_get_h(cpu);
  unsigned char l=cpu_get_l(cpu);
  return UCS_TO_US(h, l);
}

void cpu_set_hl(struct cpu* cpu, unsigned short hl) {
  unsigned char h=US_TO_HUC(hl);
  unsigned char l=US_TO_LUC(hl);
  cpu_set_h(cpu, h);
  cpu_set_l(cpu, l);
}

unsigned short cpu_get_sp(struct cpu* cpu) {
  return cpu->regs.sp;
}

void cpu_set_sp(struct cpu* cpu, unsigned short sp) {
  cpu->regs.sp = sp;
}

unsigned short cpu_get_pc(struct cpu* cpu) {
  return cpu->regs.pc;
}

void cpu_set_pc(struct cpu* cpu, unsigned short pc) {
  cpu->regs.pc = pc;
}

// REGISTERS ///////////////////////////////////////////////////////////////////
unsigned char cpu_get_r8(struct cpu* cpu, int ri) {
  return cpu->regs.r8[ri];
}

void cpu_set_r8(struct cpu* cpu, int ri, unsigned char v) {
  cpu->regs.r8[ri] = v;
}

unsigned short cpu_get_r16(struct cpu* cpu, int ri) {
  unsigned char l=cpu_get_r8(cpu, ri+0);
  unsigned char h=cpu_get_r8(cpu, ri+1);
  return UCS_TO_US(h, l);
}

void cpu_set_r16(struct cpu* cpu, int ri, unsigned short v) {
  unsigned char h=US_TO_HUC(v);
  unsigned char l=US_TO_LUC(v);
  cpu_set_r8(cpu, ri+0, l);
  cpu_set_r8(cpu, ri+1, h);
}

// MEMORY //////////////////////////////////////////////////////////////////////
unsigned char cpu_get_m8(struct cpu* cpu, int mi) {
  return cpu->memory[mi];
}

void cpu_set_m8(struct cpu* cpu, int mi, unsigned char v) {
  cpu->memory[mi] = v;
}

unsigned short cpu_get_m16(struct cpu* cpu, int mi) {
  // The GameBoy CPU architecture is Little-Endian!
  unsigned char l=cpu_get_m8(cpu, mi+0);
  unsigned char h=cpu_get_m8(cpu, mi+1);
  return UCS_TO_US(h, l);
}

void cpu_set_m16(struct cpu* cpu, int mi, unsigned short v) {
  unsigned char l=US_TO_LUC(v);
  unsigned char h=US_TO_HUC(v);
  cpu_set_m8(cpu, mi+0, l);
  cpu_set_m8(cpu, mi+1, h);
}

// INSTRUCTIONS ////////////////////////////////////////////////////////////////
//// ADC ///////////////////////////////////////////////////////////////////////
void cpu_adc_flags(struct cpu* cpu, unsigned char a, unsigned char b, unsigned int t) {
  unsigned int  carries=t ^ a ^ b;
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=carries & 0x10  ? HF : 0;
  unsigned char c=carries & 0x100 ? CF : 0;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_adc_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu_get_r8(cpu, rb);
  unsigned int t=a+b;
  if(cpu_get_r8(cpu, RF) & CF)
    t = t+1;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_adc_flags(cpu, a, b, t);
}

void cpu_adc_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  unsigned int t=a+b;
  if(cpu_get_r8(cpu, RF) & CF)
    t = t+1;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_adc_flags(cpu, a, b, t);
}

void cpu_adc_ind8(struct cpu* cpu, unsigned short p) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu->memory[p];
  unsigned int t=a+b;
  if(cpu_get_r8(cpu, RF) & CF)
    t = t+1;
  cpu_set_r8(cpu, RA, t);
  cpu_adc_flags(cpu, a, b, t);
}

//// ADD ///////////////////////////////////////////////////////////////////////
void cpu_add8_flags(struct cpu* cpu, unsigned char a, unsigned char b, unsigned int t) {
  unsigned int  carries=t ^ a ^ b;
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=carries & 0x10  ? HF : 0;
  unsigned char c=carries & 0x100 ? CF : 0;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_add8_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu_get_r8(cpu, rb);
  unsigned int t=a+b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_add8_flags(cpu, a, b, t);
}

void cpu_add8_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  unsigned int t=a+b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_add8_flags(cpu, a, b, t);
}

void cpu_add8_ind8(struct cpu* cpu, unsigned short p) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu->memory[p];
  unsigned int t=a+b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_add8_flags(cpu, a, b, t);
}

void cpu_add16_flags(struct cpu* cpu, unsigned short a, unsigned short b, unsigned int t) {
  unsigned int  carries=t ^ a ^ b;
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=carries & 0x1000  ? HF : 0;
  unsigned char c=carries & 0x10000 ? CF : 0;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_add16_r16(struct cpu* cpu, int rb) {
  unsigned short a=cpu_get_r16(cpu, RHL);
  unsigned short b=cpu_get_r16(cpu, rb);
  unsigned int t=a+b;
  cpu_set_r16(cpu, RHL, (unsigned short) t);
  cpu_add16_flags(cpu, a, b, t);
}

void cpu_add16_d16(struct cpu* cpu, unsigned short d16) {
  unsigned short a=cpu_get_r16(cpu, RHL);
  unsigned short b=d16;
  unsigned int t=a+b;
  cpu_set_r16(cpu, RHL, (unsigned short) t);
  cpu_add16_flags(cpu, a, b, t);
}

void cpu_add16_sp(struct cpu* cpu, signed char d8) {
  cpu->regs.sp += d8;

  unsigned short a=cpu->regs.sp;
  signed char b=d8;
  int t=a+b;
  
  unsigned int carries=(t & 0x1FFFF) ^ a ^ b;
  unsigned char z=0;
  unsigned char n=0;
  unsigned char h=carries & 0x10 ? HF : 0;
  unsigned char c=carries ^ 0x100 ? CF : 0;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

//// AND ///////////////////////////////////////////////////////////////////////
void cpu_and_flags(struct cpu* cpu, unsigned char a, unsigned char b, unsigned int t) {
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=HF;
  unsigned char c=0;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_and_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu_get_r8(cpu, rb);
  unsigned int t=a & b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_and_flags(cpu, a, b, t);
}

void cpu_and_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  unsigned int t=a & b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_and_flags(cpu, a, b, t);
}

void cpu_and_ind8(struct cpu* cpu, unsigned short p) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu->memory[p];
  unsigned int t=a & b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_and_flags(cpu, a, b, t);
}

//// CP ////////////////////////////////////////////////////////////////////////
void cpu_cp_flags(struct cpu* cpu, unsigned char a, unsigned char b) {
  unsigned char z=a==b ? ZF : 0;
  unsigned char n=NF;
  unsigned char h=(a&0x0F) < (b&0x0F) ? HF : 0;
  unsigned char c=(a&0xFF) < (b&0xFF) ? CF : 0 ;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_cp_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu_get_r8(cpu, rb);
  cpu_cp_flags(cpu, a, b);
}

void cpu_cp_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  cpu_cp_flags(cpu, a, b);
}

void cpu_cp_ind8(struct cpu* cpu, unsigned short p) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu->memory[p];
  cpu_cp_flags(cpu, a, b);
}

// DEC /////////////////////////////////////////////////////////////////////////
void cpu_dec8_flags(struct cpu* cpu, unsigned char a, signed int t) {
  unsigned int carries=(t ^ 0x1FF) ^ a ^ ((signed char) -1);
  unsigned char f=cpu_get_r8(cpu, RF);
  unsigned char z=a==0 ? ZF : 0;
  unsigned char n=NF;
  unsigned char h=carries & 0x10 ? HF : 0;
  unsigned char c=f & CF;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_dec8_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, rb);
  signed int t=a-1;
  cpu_set_r8(cpu, rb, (unsigned char) t);
  cpu_dec8_flags(cpu, a, t);
}

void cpu_dec8_ind8(struct cpu* cpu) {
  unsigned short hl=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu->memory[hl];
  signed int t=a-1;
  cpu->memory[hl] = (unsigned char) t;
  cpu_dec8_flags(cpu, a, t);
}

void cpu_dec16_flags(struct cpu* cpu, unsigned short a, signed int t) {
  // Flags not affected
}

void cpu_dec16_r16(struct cpu* cpu, int rb) {
  unsigned short a=cpu_get_r16(cpu, rb);
  signed int t=a-1;
  cpu_set_r16(cpu, rb, (unsigned short) t);
  cpu_dec16_flags(cpu, a, t);
}

void cpu_dec16_sp(struct cpu* cpu) {
  unsigned short a=cpu->regs.sp;
  signed int t=a-1;
  cpu->regs.sp = (unsigned short) t;
  cpu_dec16_flags(cpu, a, t);
}

// INC /////////////////////////////////////////////////////////////////////////
void cpu_inc8_flags(struct cpu* cpu, unsigned char a, unsigned int t) {
  unsigned int carries=t ^ a ^ ((unsigned char) +1);
  unsigned char f=cpu_get_r8(cpu, RF);
  unsigned char z=a==0 ? ZF : 0;
  unsigned char n=0;
  unsigned char h=carries & 0x10 ? HF : 0;
  unsigned char c=f & CF;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_inc8_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, rb);
  unsigned int t=a+1;
  cpu_set_r8(cpu, rb, (unsigned char) t);
  cpu_inc8_flags(cpu, a, t);
}

void cpu_inc8_ind8(struct cpu* cpu) {
  unsigned short hl=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu->memory[hl];
  unsigned int t=a+1;
  cpu->memory[hl] = (unsigned char) t;
  cpu_inc8_flags(cpu, a, t);
}

void cpu_inc16_flags(struct cpu* cpu, unsigned short a, signed int t) {
  // Flags not affected
}

void cpu_inc16_r16(struct cpu* cpu, int rb) {
  unsigned short a=cpu_get_r16(cpu, rb);
  unsigned int t=a+1;
  cpu_set_r16(cpu, rb, (unsigned short) t);
  cpu_inc16_flags(cpu, a, t);
}

void cpu_inc16_sp(struct cpu* cpu) {
  unsigned short a=cpu->regs.sp;
  unsigned int t=a+1;
  cpu->regs.sp = (unsigned short) t;
  cpu_inc16_flags(cpu, a, t);
}
