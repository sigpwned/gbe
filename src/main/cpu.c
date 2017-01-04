#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "opcodes.h"
#include "gbe.h"

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

void cpu_adc_r8(struct cpu* cpu, int rb);
void cpu_adc_d8(struct cpu* cpu, unsigned char d8);
void cpu_adc_ind8(struct cpu* cpu);

void cpu_add8_r8(struct cpu* cpu, int rb);
void cpu_add8_d8(struct cpu* cpu, unsigned char d8);
void cpu_add8_ind8(struct cpu* cpu);
void cpu_add16_r16(struct cpu* cpu, int rb);
void cpu_add16_d16(struct cpu* cpu, unsigned short d16);
void cpu_add16_sp(struct cpu* cpu, signed char d8);

void cpu_and_r8(struct cpu* cpu, int rb);
void cpu_and_d8(struct cpu* cpu, unsigned char d8);
void cpu_and_ind8(struct cpu* cpu);

void cpu_call_cond(struct cpu* cpu, unsigned short p, unsigned char mask, unsigned char test);

void cpu_cp_r8(struct cpu* cpu, int rb);
void cpu_cp_d8(struct cpu* cpu, unsigned char d8);
void cpu_cp_ind8(struct cpu* cpu);

void cpu_dec8_r8(struct cpu* cpu, int rb);
void cpu_dec8_ind8(struct cpu* cpu);
void cpu_dec16_r16(struct cpu* cpu, int rb);
void cpu_dec16_sp(struct cpu* cpu);

void cpu_inc8_r8(struct cpu* cpu, int rb);
void cpu_inc8_ind8(struct cpu* cpu);
void cpu_inc16_r16(struct cpu* cpu, int rb);
void cpu_inc16_sp(struct cpu* cpu);

void cpu_ld_r8_r8(struct cpu* cpu, int ra, int rb);
void cpu_ld_r8_d8(struct cpu* cpu, int ri, unsigned char d8);
void cpu_ld_r8_ind8(struct cpu* cpu, int ra, int rb);
void cpu_ld_ind8_r8(struct cpu* cpu, int ra, int rb);
void cpu_ld_hl_spd8(struct cpu* cpu, signed char d8);

void cpu_or_r8(struct cpu* cpu, int rb);
void cpu_or_d8(struct cpu* cpu, unsigned char d8);
void cpu_or_ind8(struct cpu* cpu);

void cpu_push_r16(struct cpu* cpu, int rb);
void cpu_pop_r16(struct cpu* cpu, int rb);

void cpu_sbc_r8(struct cpu* cpu, int rb);
void cpu_sbc_d8(struct cpu* cpu, unsigned char d8);
void cpu_sbc_ind8(struct cpu* cpu);

void cpu_sub_r8(struct cpu* cpu, int rb);
void cpu_sub_d8(struct cpu* cpu, unsigned char d8);
void cpu_sub_ind8(struct cpu* cpu);

void cpu_xor_r8(struct cpu* cpu, int rb);
void cpu_xor_d8(struct cpu* cpu, unsigned char d8);
void cpu_xor_ind8(struct cpu* cpu);

void cpu_rr_r8(struct cpu* cpu, int ri);
void cpu_rr_ind8(struct cpu* cpu);
void cpu_rrc_r8(struct cpu* cpu, int ri);
void cpu_rrc_ind8(struct cpu* cpu);
void cpu_rl_r8(struct cpu* cpu, int ri);
void cpu_rl_ind8(struct cpu* cpu);
void cpu_rlc_r8(struct cpu* cpu, int ri);
void cpu_rlc_ind8(struct cpu* cpu);

void cpu_bit_r8_n(struct cpu* cpu, int ri, int n);
void cpu_bit_ind8_n(struct cpu* cpu, int n);

void cpu_set_r8_n(struct cpu* cpu, int ri, int n);
void cpu_set_ind8_n(struct cpu* cpu, int n);

void cpu_res_r8_n(struct cpu* cpu, int ri, int n);
void cpu_res_ind8_n(struct cpu* cpu, int n);

void cpu_swap_r8(struct cpu* cpu, int ri);
void cpu_swap_ind8(struct cpu* cpu);

void cpu_sla_r8(struct cpu* cpu, int ri);
void cpu_sla_ind8(struct cpu* cpu);

void cpu_sra_r8(struct cpu* cpu, int ri);
void cpu_sra_ind8(struct cpu* cpu);

void cpu_srl_r8(struct cpu* cpu, int ri);
void cpu_srl_ind8(struct cpu* cpu);

void cpu_rst_addr(struct cpu* cpu, unsigned short addr);

// LIFECYCLE ///////////////////////////////////////////////////////////////////
void cpu_init(struct cpu* cpu, struct memory* memory) {
  memset(cpu, 0, sizeof(struct cpu));
  cpu->memory = memory;
}

void cpu_tick_cb(struct cpu* cpu);

void cpu_tick(struct cpu* cpu) {
  if(cpu->busy <= 1) {
    unsigned char opcode=memory_get_d8(cpu->memory, cpu->regs.pc++);

#ifdef GBE_DEBUG
  struct opcode* d=opcode_describe(opcode);
  fprintf(stderr, "PC %04x %s\n", cpu->regs.pc-1, d->name);
#endif

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
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_adc_d8(cpu, d8);
      } break;
    case ADC_A_HL_IND:
      cpu_adc_ind8(cpu);
      break;
  
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
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_add8_d8(cpu, d8);
      } break;
    case ADD_A_HL_IND:
      cpu_add8_ind8(cpu);
      break;
  
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
        signed char d8=(signed char) memory_get_d8(cpu->memory, cpu->regs.pc++);
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
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_and_d8(cpu, d8);
      } break;
    case AND_HL_IND:
      cpu_and_ind8(cpu);
      break;
  
    // CALL //////////////////////////////////////////////////////////////////////
    case CALL_A16:
      {
        unsigned char fl=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char fh=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short fp=UCS_TO_US(fh, fl);

        unsigned char pcl=US_TO_LUC(cpu->regs.pc);
        unsigned char pch=US_TO_HUC(cpu->regs.pc);
        memory_set_d8(cpu->memory, --cpu->regs.sp, pch);
        memory_set_d8(cpu->memory, --cpu->regs.sp, pcl);

        cpu->regs.pc = fp;

        cpu->busy = 24;
      } break;
    case CALL_C_A16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        cpu_call_cond(cpu, p, CF, CF);
      } break;
    case CALL_NC_A16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        cpu_call_cond(cpu, p, CF, 0);
      } break;
    case CALL_Z_A16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        cpu_call_cond(cpu, p, ZF, ZF);
      } break;
    case CALL_NZ_A16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        cpu_call_cond(cpu, p, ZF, 0);
      } break;
  
    // CF ////////////////////////////////////////////////////////////////////////
    case CCF:
      {
        unsigned char f=cpu_get_r8(cpu, RF);
        f = (f & ~NF & ~HF) ^ CF;
        cpu_set_r8(cpu, RF, f);
        cpu->busy = 4;
      } break;
    case SCF:
      {
        unsigned char f=cpu_get_r8(cpu, RF);
        f = (f & ~NF & ~HF) | CF;
        cpu_set_r8(cpu, RF, f);
        cpu->busy = 4;
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

        cpu->busy = 4;
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
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_cp_d8(cpu, d8);
      } break;
    case CP_A_HL_IND:
      cpu_cp_ind8(cpu);
      break;
  
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
      cpu->ime = 0;
      cpu->busy = 4;
      break;
  
    case EI:
      cpu->ime = 1;
      cpu->busy = 4;
      break;
  
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
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        cpu->regs.pc = p;
        cpu->busy = 16;
      } break;
    case JP_HL_IND:
      {
        unsigned short p=cpu_get_r16(cpu, RHL);
        cpu->regs.pc = p;
        cpu->busy = 4;
      } break;
    case JP_C_A16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        if((cpu_get_r8(cpu, RF)&CF) != 0) {
          cpu->regs.pc = p;
          cpu->busy = 16;
        }
        else {
          cpu->busy = 12;
        }
      } break;
    case JP_NC_A16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        if((cpu_get_r8(cpu, RF)&CF) == 0) {
          cpu->regs.pc = p;
          cpu->busy = 16;
        }
        else {
          cpu->busy = 12;
        }
      } break;
    case JP_Z_A16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        if((cpu_get_r8(cpu, RF)&ZF) != 0) {
          cpu->regs.pc = p;
          cpu->busy = 16;
        }
        else {
          cpu->busy = 12;
        }
      } break;
    case JP_NZ_A16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        if((cpu_get_r8(cpu, RF)&ZF) == 0) {
          cpu->regs.pc = p;
          cpu->busy = 16;
        }
        else {
          cpu->busy = 12;
        }
      } break;
    case JR_R8:
      {
        signed char d=(signed char) memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu->regs.pc += d;
        cpu->busy = 12;
      } break;
    case JR_C_R8:
      {
        signed char d=(signed char) memory_get_d8(cpu->memory, cpu->regs.pc++);
        if((cpu_get_r8(cpu, RF)&CF) != 0) {
          cpu->regs.pc += d;
          cpu->busy = 12;
        }
        else {
          cpu->busy = 8;
        }
      } break;
    case JR_NC_R8:
      {
        signed char d=(signed char) memory_get_d8(cpu->memory, cpu->regs.pc++);
        if((cpu_get_r8(cpu, RF)&CF) == 0) {
          cpu->regs.pc += d;
          cpu->busy = 12;
        }
        else {
          cpu->busy = 8;
        }
      } break;
    case JR_Z_R8:
      {
        signed char d=(signed char) memory_get_d8(cpu->memory, cpu->regs.pc++);
        if((cpu_get_r8(cpu, RF)&ZF) != 0) {
          cpu->regs.pc += d;
          cpu->busy = 12;
        }
        else {
          cpu->busy = 8;
        }
      } break;
    case JR_NZ_R8:
      {
        signed char d=(signed char) memory_get_d8(cpu->memory, cpu->regs.pc++);
        if((cpu_get_r8(cpu, RF)&ZF) == 0) {
          cpu->regs.pc += d;
          cpu->busy = 12;
        }
        else {
          cpu->busy = 8;
        }
      } break;
  
    // LOAD //////////////////////////////////////////////////////////////////////
    case LDH_A8_IND_A:
      {
        unsigned char a=cpu_get_r8(cpu, RA);
        unsigned char n=memory_get_d8(cpu->memory, cpu->regs.pc++);
        memory_set_d8(cpu->memory, 0xFF00+n, a);
        cpu->busy = 12;
      } break;
    case LDH_A_A8_IND:
      {
        unsigned char n=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char t=memory_get_d8(cpu->memory, 0xFF00+n);
        cpu_set_r8(cpu, RA, t);
        cpu->busy = 12;
      } break;
    case LD_A16_IND_A:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        unsigned char a=cpu_get_r8(cpu, RA);
        memory_set_d8(cpu->memory, p, a);
        cpu->busy = 16;
      } break;
    case LD_A_A16_IND:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=UCS_TO_US(h, l);
        unsigned char t=memory_get_d8(cpu->memory, p);
        cpu_set_r8(cpu, RA, t);
        cpu->busy = 16;
      } break;
  
    case LD_A_A:
      cpu_ld_r8_r8(cpu, RA, RA);
      break;
    case LD_A_B:
      cpu_ld_r8_r8(cpu, RA, RB);
      break;
    case LD_A_C:
      cpu_ld_r8_r8(cpu, RA, RC);
      break;
    case LD_A_D:
      cpu_ld_r8_r8(cpu, RA, RD);
      break;
    case LD_A_E:
      cpu_ld_r8_r8(cpu, RA, RE);
      break;
    case LD_A_H:
      cpu_ld_r8_r8(cpu, RA, RH);
      break;
    case LD_A_L:
      cpu_ld_r8_r8(cpu, RA, RL);
      break;
    case LD_A_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_ld_r8_d8(cpu, RA, d8);
      } break;
    case LD_A_HL_IND:
      cpu_ld_r8_ind8(cpu, RA, RHL);
      break;
  
    case LD_A_BC_IND:
      cpu_ld_r8_ind8(cpu, RA, RBC);
      break;
    case LD_A_DE_IND:
      cpu_ld_r8_ind8(cpu, RA, RDE);
      break;
    case LD_A_HL_IND_MINUS:
      {
        unsigned short hl=cpu_get_r16(cpu, RHL);
        unsigned char a=memory_get_d8(cpu->memory, hl);
        cpu_set_r8(cpu, RA, a);
        cpu_set_r16(cpu, RHL, hl-1);
        cpu->busy = 8;
      } break;
    case LD_A_HL_IND_PLUS:
      {
        unsigned short hl=cpu_get_r16(cpu, RHL);
        unsigned char a=memory_get_d8(cpu->memory, hl);
        cpu_set_r8(cpu, RA, a);
        hl = hl+1;
        cpu_set_r16(cpu, RHL, hl);
        cpu->busy = 8;
      } break;
  
    case LD_B_A:
      cpu_ld_r8_r8(cpu, RB, RA);
      break;
    case LD_B_B:
      cpu_ld_r8_r8(cpu, RB, RB);
      break;
    case LD_B_C:
      cpu_ld_r8_r8(cpu, RB, RC);
      break;
    case LD_B_D:
      cpu_ld_r8_r8(cpu, RB, RD);
      break;
    case LD_B_E:
      cpu_ld_r8_r8(cpu, RB, RE);
      break;
    case LD_B_H:
      cpu_ld_r8_r8(cpu, RB, RH);
      break;
    case LD_B_L:
      cpu_ld_r8_r8(cpu, RB, RL);
      break;
    case LD_B_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_ld_r8_d8(cpu, RB, d8);
      } break;
    case LD_B_HL_IND:
      cpu_ld_r8_ind8(cpu, RB, RHL);
      break;
  
    case LD_C_A:
      cpu_ld_r8_r8(cpu, RC, RA);
      break;
    case LD_C_B:
      cpu_ld_r8_r8(cpu, RC, RB);
      break;
    case LD_C_C:
      cpu_ld_r8_r8(cpu, RC, RC);
      break;
    case LD_C_D:
      cpu_ld_r8_r8(cpu, RC, RD);
      break;
    case LD_C_E:
      cpu_ld_r8_r8(cpu, RC, RE);
      break;
    case LD_C_H:
      cpu_ld_r8_r8(cpu, RC, RH);
      break;
    case LD_C_L:
      cpu_ld_r8_r8(cpu, RC, RL);
      break;
    case LD_C_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_ld_r8_d8(cpu, RC, d8);
      } break;
    case LD_C_HL_IND:
      cpu_ld_r8_ind8(cpu, RC, RHL);
      break;
  
    case LD_D_A:
      cpu_ld_r8_r8(cpu, RD, RA);
      break;
    case LD_D_B:
      cpu_ld_r8_r8(cpu, RD, RB);
      break;
    case LD_D_C:
      cpu_ld_r8_r8(cpu, RD, RC);
      break;
    case LD_D_D:
      cpu_ld_r8_r8(cpu, RD, RD);
      break;
    case LD_D_E:
      cpu_ld_r8_r8(cpu, RD, RE);
      break;
    case LD_D_H:
      cpu_ld_r8_r8(cpu, RD, RH);
      break;
    case LD_D_L:
      cpu_ld_r8_r8(cpu, RD, RL);
      break;
    case LD_D_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_ld_r8_d8(cpu, RD, d8);
      } break;
    case LD_D_HL_IND:
      cpu_ld_r8_ind8(cpu, RD, RHL);
      break;
  
    case LD_E_A:
      cpu_ld_r8_r8(cpu, RE, RA);
      break;
    case LD_E_B:
      cpu_ld_r8_r8(cpu, RE, RB);
      break;
    case LD_E_C:
      cpu_ld_r8_r8(cpu, RE, RC);
      break;
    case LD_E_D:
      cpu_ld_r8_r8(cpu, RE, RD);
      break;
    case LD_E_E:
      cpu_ld_r8_r8(cpu, RE, RE);
      break;
    case LD_E_H:
      cpu_ld_r8_r8(cpu, RE, RH);
      break;
    case LD_E_L:
      cpu_ld_r8_r8(cpu, RE, RL);
      break;
    case LD_E_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_ld_r8_d8(cpu, RE, d8);
      } break;
    case LD_E_HL_IND:
      cpu_ld_r8_ind8(cpu, RE, RHL);
      break;
  
    case LD_H_A:
      cpu_ld_r8_r8(cpu, RH, RA);
      break;
    case LD_H_B:
      cpu_ld_r8_r8(cpu, RH, RB);
      break;
    case LD_H_C:
      cpu_ld_r8_r8(cpu, RH, RC);
      break;
    case LD_H_D:
      cpu_ld_r8_r8(cpu, RH, RD);
      break;
    case LD_H_E:
      cpu_ld_r8_r8(cpu, RH, RE);
      break;
    case LD_H_H:
      cpu_ld_r8_r8(cpu, RH, RH);
      break;
    case LD_H_L:
      cpu_ld_r8_r8(cpu, RH, RL);
      break;
    case LD_H_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_ld_r8_d8(cpu, RH, d8);
      } break;
    case LD_H_HL_IND:
      cpu_ld_r8_ind8(cpu, RH, RHL);
      break;
  
    case LD_L_A:
      cpu_ld_r8_r8(cpu, RL, RA);
      break;
    case LD_L_B:
      cpu_ld_r8_r8(cpu, RL, RB);
      break;
    case LD_L_C:
      cpu_ld_r8_r8(cpu, RL, RC);
      break;
    case LD_L_D:
      cpu_ld_r8_r8(cpu, RL, RD);
      break;
    case LD_L_E:
      cpu_ld_r8_r8(cpu, RL, RE);
      break;
    case LD_L_H:
      cpu_ld_r8_r8(cpu, RL, RH);
      break;
    case LD_L_L:
      cpu_ld_r8_r8(cpu, RL, RL);
      break;
    case LD_L_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_ld_r8_d8(cpu, RL, d8);
      } break;
    case LD_L_HL_IND:
      cpu_ld_r8_ind8(cpu, RL, RHL);
      break;
  
    case LD_C_IND_A:
      {
        unsigned char a=cpu_get_r8(cpu, RA);
        unsigned char c=cpu_get_r8(cpu, RC);
        memory_set_d8(cpu->memory, 0xFF00+c, a);
        cpu->busy = 8;
      } break;
    case LD_A_C_IND:
      {
        unsigned char c=cpu_get_r8(cpu, RC);
        unsigned char t=memory_get_d8(cpu->memory, 0xFF00+c);
        cpu_set_r8(cpu, RA, t);
        cpu->busy = 8;
      } break;
  
    case LD_BC_D16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short d16=UCS_TO_US(h, l);
        cpu_set_r16(cpu, RBC, d16);
        cpu->busy = 12;
      } break;
    case LD_DE_D16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short d16=UCS_TO_US(h, l);
        cpu_set_r16(cpu, RDE, d16);
        cpu->busy = 12;
      } break;
    case LD_HL_D16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short d16=UCS_TO_US(h, l);
        cpu_set_r16(cpu, RHL, d16);
        cpu->busy = 12;
      } break;
    case LD_HL_IND_A:
      cpu_ld_ind8_r8(cpu, RHL, RA);
      break;
    case LD_HL_IND_B:
      cpu_ld_ind8_r8(cpu, RHL, RB);
      break;
    case LD_HL_IND_C:
      cpu_ld_ind8_r8(cpu, RHL, RC);
      break;
    case LD_HL_IND_D:
      cpu_ld_ind8_r8(cpu, RHL, RD);
      break;
    case LD_HL_IND_E:
      cpu_ld_ind8_r8(cpu, RHL, RE);
      break;
    case LD_HL_IND_H:
      cpu_ld_ind8_r8(cpu, RHL, RH);
      break;
    case LD_HL_IND_L:
      cpu_ld_ind8_r8(cpu, RHL, RL);
      break;
    case LD_HL_IND_D8:
      {
        unsigned char a=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short p=cpu_get_r16(cpu, RHL);
        memory_set_d8(cpu->memory, p, a);
        cpu->busy = 12;
      } break;
    case LD_HL_SP_PLUS_R8:
      {
        signed char d8=(signed char) memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_ld_hl_spd8(cpu, d8);
        cpu->busy = 12;
      } break;
  
    case LD_BC_IND_A:
      cpu_ld_ind8_r8(cpu, RBC, RA);
      break;
    case LD_DE_IND_A:
      cpu_ld_ind8_r8(cpu, RDE, RA);
      break;
  
    case LD_A16_IND_SP:
    case LD_HL_IND_MINUS_A:
      {
        unsigned short hl=cpu_get_r16(cpu, RHL);
        unsigned char a=cpu_get_r8(cpu, RA);
        memory_set_d8(cpu->memory, hl, a);
        cpu_set_r16(cpu, RHL, hl-1);
        cpu->busy = 8;
      } break;
    case LD_HL_IND_PLUS_A:
      {
        unsigned short hl=cpu_get_r16(cpu, RHL);
        unsigned char a=cpu_get_r8(cpu, RA);
        memory_set_d8(cpu->memory, hl, a);
        hl = hl+1;
        cpu_set_r16(cpu, RHL, hl);
        cpu->busy = 8;
      } break;
  
    case LD_SP_D16:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.pc++);
        unsigned short d16=UCS_TO_US(h, l);
        cpu->regs.sp = d16;
        cpu->busy = 12;
      } break;
    case LD_SP_HL:
      {
        unsigned short hl=cpu_get_r16(cpu, RHL);
        cpu->regs.sp = hl;
        cpu->busy = 8;
      } break;
  
    // NOP ///////////////////////////////////////////////////////////////////////
    case NOP:
      // Well that was easy! :)
      cpu->busy = 4;
      break;
  
    // OR ////////////////////////////////////////////////////////////////////////
    case OR_A:
      cpu_or_r8(cpu, RA);
      break;
    case OR_B:
      cpu_or_r8(cpu, RB);
      break;
    case OR_C:
      cpu_or_r8(cpu, RC);
      break;
    case OR_D:
      cpu_or_r8(cpu, RD);
      break;
    case OR_E:
      cpu_or_r8(cpu, RE);
      break;
    case OR_H:
      cpu_or_r8(cpu, RH);
      break;
    case OR_L:
      cpu_or_r8(cpu, RL);
      break;
    case OR_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_or_d8(cpu, d8);
      } break;
    case OR_HL_IND:
      cpu_or_ind8(cpu);
      break;
  
    // POP ///////////////////////////////////////////////////////////////////////
    case POP_AF:
      cpu_pop_r16(cpu, RAF);
      break;
    case POP_BC:
      cpu_pop_r16(cpu, RBC);
      break;
    case POP_DE:
      cpu_pop_r16(cpu, RDE);
      break;
    case POP_HL:
      cpu_pop_r16(cpu, RHL);
      break;
  
    // PUSH //////////////////////////////////////////////////////////////////////
    case PUSH_AF:
      cpu_push_r16(cpu, RAF);
      break;
    case PUSH_BC:
      cpu_push_r16(cpu, RBC);
      break;
    case PUSH_DE:
      cpu_push_r16(cpu, RDE);
      break;
    case PUSH_HL:
      cpu_push_r16(cpu, RHL);
      break;
  
    // OTHER INSTRUCTIONS ////////////////////////////////////////////////////////
    case PREFIX_CB:
      cpu_tick_cb(cpu);
      break;
  
    // RETURN ////////////////////////////////////////////////////////////////////
    case RET:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned short p=UCS_TO_US(h, l);
        cpu->regs.pc = p;
        cpu->busy = 16;
      } break;
    case RET_C:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned short p=UCS_TO_US(h, l);
        if((cpu_get_r8(cpu, RF)&CF) != 0) {
          cpu->regs.pc = p;
          cpu->busy = 20;
        }
        else {
          cpu->busy = 8;
        }
      } break;
    case RET_NC:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned short p=UCS_TO_US(h, l);
        if((cpu_get_r8(cpu, RF)&CF) == 0) {
          cpu->regs.pc = p;
          cpu->busy = 20;
        }
        else {
          cpu->busy = 8;
        }
      } break;
    case RET_Z:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned short p=UCS_TO_US(h, l);
        if((cpu_get_r8(cpu, RF)&ZF) != 0) {
          cpu->regs.pc = p;
          cpu->busy = 20;
        }
        else {
          cpu->busy = 8;
        }
      } break;
    case RET_NZ:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned short p=UCS_TO_US(h, l);
        if((cpu_get_r8(cpu, RF)&ZF) == 0) {
          cpu->regs.pc = p;
          cpu->busy = 20;
        }
        else {
          cpu->busy = 8;
        }
      } break;
    case RETI:
      {
        unsigned char l=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned char h=memory_get_d8(cpu->memory, cpu->regs.sp++);
        unsigned short p=UCS_TO_US(h, l);
        cpu->regs.pc = p;
        cpu->ime = 1;
        cpu->busy = 16;
      } break;
  
      // ROTATIONS
    case RLA:
      cpu_rl_r8(cpu, RA);
      break;
    case RLCA:
      cpu_rlc_r8(cpu, RA);
      break;
    case RRA:
      cpu_rr_r8(cpu, RA);
      break;
    case RRCA:
      cpu_rrc_r8(cpu, RA);
      break;
  
    // RESET /////////////////////////////////////////////////////////////////////
    case RST_00H:
      cpu_rst_addr(cpu, 0x00);
      break;
    case RST_08H:
      cpu_rst_addr(cpu, 0x08);
      break;
    case RST_10H:
      cpu_rst_addr(cpu, 0x10);
      break;
    case RST_18H:
      cpu_rst_addr(cpu, 0x18);
      break;
    case RST_20H:
      cpu_rst_addr(cpu, 0x20);
      break;
    case RST_28H:
      cpu_rst_addr(cpu, 0x28);
      break;
    case RST_30H:
      cpu_rst_addr(cpu, 0x30);
      break;
    case RST_38H:
      cpu_rst_addr(cpu, 0x38);
      break;
  
    // SBC ///////////////////////////////////////////////////////////////////////
    case SBC_A_A:
      cpu_sbc_r8(cpu, RA);
      break;
    case SBC_A_B:
      cpu_sbc_r8(cpu, RB);
      break;
    case SBC_A_C:
      cpu_sbc_r8(cpu, RC);
      break;
    case SBC_A_D:
      cpu_sbc_r8(cpu, RD);
      break;
    case SBC_A_E:
      cpu_sbc_r8(cpu, RE);
      break;
    case SBC_A_H:
      cpu_sbc_r8(cpu, RH);
      break;
    case SBC_A_L:
      cpu_sbc_r8(cpu, RL);
      break;
    case SBC_A_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_sbc_d8(cpu, d8);
      } break;
    case SBC_A_HL_IND:
      cpu_sbc_ind8(cpu);
      break;
  
    // STOP //////////////////////////////////////////////////////////////////////
    case HALT:
      cpu->halted = 1;
      cpu->busy = 4;
      break;
    case STOP:
      cpu->stopped = 1;
      cpu->busy = 4;
      break;
  
    // SUB ///////////////////////////////////////////////////////////////////////
    case SUB_A:
      cpu_sub_r8(cpu, RA);
      break;
    case SUB_B:
      cpu_sub_r8(cpu, RB);
      break;
    case SUB_C:
      cpu_sub_r8(cpu, RC);
      break;
    case SUB_D:
      cpu_sub_r8(cpu, RD);
      break;
    case SUB_E:
      cpu_sub_r8(cpu, RE);
      break;
    case SUB_H:
      cpu_sub_r8(cpu, RH);
      break;
    case SUB_L:
      cpu_sub_r8(cpu, RL);
      break;
    case SUB_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_sub_d8(cpu, d8);
      } break;
    case SUB_HL_IND:
      cpu_sub_ind8(cpu);
      break;
  
    // XOR ///////////////////////////////////////////////////////////////////////
    case XOR_A_A:
      cpu_xor_r8(cpu, RA);
      break;
    case XOR_A_B:
      cpu_xor_r8(cpu, RB);
      break;
    case XOR_A_C:
      cpu_xor_r8(cpu, RC);
      break;
    case XOR_A_D:
      cpu_xor_r8(cpu, RD);
      break;
    case XOR_A_E:
      cpu_xor_r8(cpu, RE);
      break;
    case XOR_A_H:
      cpu_xor_r8(cpu, RH);
      break;
    case XOR_A_L:
      cpu_xor_r8(cpu, RL);
      break;
    case XOR_D8:
      {
        unsigned char d8=memory_get_d8(cpu->memory, cpu->regs.pc++);
        cpu_xor_d8(cpu, d8);
      } break;
    case XOR_A_HL_IND:
      cpu_xor_ind8(cpu);
      break;
  
    default:
      exit(ERR_BAD_OPCODE);
      break;
    }
  }
  else {
    cpu->busy = cpu->busy-1;
  }
}

void cpu_tick_cb(struct cpu* cpu) {
  unsigned char opcode=memory_get_d8(cpu->memory, cpu->regs.pc++);

#ifdef GBE_DEBUG
  struct opcode* d=opcode_cb_describe(opcode);
  fprintf(stderr, "         %s\n", d->name);
#endif

  switch(opcode) {
  case BIT_0_A:
    cpu_bit_r8_n(cpu, RA, 0);
    break;
  case BIT_0_B:
    cpu_bit_r8_n(cpu, RB, 0);
    break;
  case BIT_0_C:
    cpu_bit_r8_n(cpu, RC, 0);
    break;
  case BIT_0_D:
    cpu_bit_r8_n(cpu, RD, 0);
    break;
  case BIT_0_E:
    cpu_bit_r8_n(cpu, RE, 0);
    break;
  case BIT_0_H:
    cpu_bit_r8_n(cpu, RH, 0);
    break;
  case BIT_0_L:
    cpu_bit_r8_n(cpu, RL, 0);
    break;
  case BIT_0_HL_IND:
    cpu_bit_ind8_n(cpu, 0);
    break;

  case BIT_1_A:
    cpu_bit_r8_n(cpu, RA, 1);
    break;
  case BIT_1_B:
    cpu_bit_r8_n(cpu, RB, 1);
    break;
  case BIT_1_C:
    cpu_bit_r8_n(cpu, RC, 1);
    break;
  case BIT_1_D:
    cpu_bit_r8_n(cpu, RD, 1);
    break;
  case BIT_1_E:
    cpu_bit_r8_n(cpu, RE, 1);
    break;
  case BIT_1_H:
    cpu_bit_r8_n(cpu, RH, 1);
    break;
  case BIT_1_L:
    cpu_bit_r8_n(cpu, RL, 1);
    break;
  case BIT_1_HL_IND:
    cpu_bit_ind8_n(cpu, 1);
    break;

  case BIT_2_A:
    cpu_bit_r8_n(cpu, RA, 2);
    break;
  case BIT_2_B:
    cpu_bit_r8_n(cpu, RB, 2);
    break;
  case BIT_2_C:
    cpu_bit_r8_n(cpu, RC, 2);
    break;
  case BIT_2_D:
    cpu_bit_r8_n(cpu, RD, 2);
    break;
  case BIT_2_E:
    cpu_bit_r8_n(cpu, RE, 2);
    break;
  case BIT_2_H:
    cpu_bit_r8_n(cpu, RH, 2);
    break;
  case BIT_2_L:
    cpu_bit_r8_n(cpu, RL, 2);
    break;
  case BIT_2_HL_IND:
    cpu_bit_ind8_n(cpu, 2);
    break;

  case BIT_3_A:
    cpu_bit_r8_n(cpu, RA, 3);
    break;
  case BIT_3_B:
    cpu_bit_r8_n(cpu, RB, 3);
    break;
  case BIT_3_C:
    cpu_bit_r8_n(cpu, RC, 3);
    break;
  case BIT_3_D:
    cpu_bit_r8_n(cpu, RD, 3);
    break;
  case BIT_3_E:
    cpu_bit_r8_n(cpu, RE, 3);
    break;
  case BIT_3_H:
    cpu_bit_r8_n(cpu, RH, 3);
    break;
  case BIT_3_L:
    cpu_bit_r8_n(cpu, RL, 3);
    break;
  case BIT_3_HL_IND:
    cpu_bit_ind8_n(cpu, 3);
    break;

  case BIT_4_A:
    cpu_bit_r8_n(cpu, RA, 4);
    break;
  case BIT_4_B:
    cpu_bit_r8_n(cpu, RB, 4);
    break;
  case BIT_4_C:
    cpu_bit_r8_n(cpu, RC, 4);
    break;
  case BIT_4_D:
    cpu_bit_r8_n(cpu, RD, 4);
    break;
  case BIT_4_E:
    cpu_bit_r8_n(cpu, RE, 4);
    break;
  case BIT_4_H:
    cpu_bit_r8_n(cpu, RH, 4);
    break;
  case BIT_4_L:
    cpu_bit_r8_n(cpu, RL, 4);
    break;
  case BIT_4_HL_IND:
    cpu_bit_ind8_n(cpu, 4);
    break;

  case BIT_5_A:
    cpu_bit_r8_n(cpu, RA, 5);
    break;
  case BIT_5_B:
    cpu_bit_r8_n(cpu, RB, 5);
    break;
  case BIT_5_C:
    cpu_bit_r8_n(cpu, RC, 5);
    break;
  case BIT_5_D:
    cpu_bit_r8_n(cpu, RD, 5);
    break;
  case BIT_5_E:
    cpu_bit_r8_n(cpu, RE, 5);
    break;
  case BIT_5_H:
    cpu_bit_r8_n(cpu, RH, 5);
    break;
  case BIT_5_L:
    cpu_bit_r8_n(cpu, RL, 5);
    break;
  case BIT_5_HL_IND:
    cpu_bit_ind8_n(cpu, 5);
    break;

  case BIT_6_A:
    cpu_bit_r8_n(cpu, RA, 6);
    break;
  case BIT_6_B:
    cpu_bit_r8_n(cpu, RB, 6);
    break;
  case BIT_6_C:
    cpu_bit_r8_n(cpu, RC, 6);
    break;
  case BIT_6_D:
    cpu_bit_r8_n(cpu, RD, 6);
    break;
  case BIT_6_E:
    cpu_bit_r8_n(cpu, RE, 6);
    break;
  case BIT_6_H:
    cpu_bit_r8_n(cpu, RH, 6);
    break;
  case BIT_6_L:
    cpu_bit_r8_n(cpu, RL, 6);
    break;
  case BIT_6_HL_IND:
    cpu_bit_ind8_n(cpu, 6);
    break;

  case BIT_7_A:
    cpu_bit_r8_n(cpu, RA, 7);
    break;
  case BIT_7_B:
    cpu_bit_r8_n(cpu, RB, 7);
    break;
  case BIT_7_C:
    cpu_bit_r8_n(cpu, RC, 7);
    break;
  case BIT_7_D:
    cpu_bit_r8_n(cpu, RD, 7);
    break;
  case BIT_7_E:
    cpu_bit_r8_n(cpu, RE, 7);
    break;
  case BIT_7_H:
    cpu_bit_r8_n(cpu, RH, 7);
    break;
  case BIT_7_L:
    cpu_bit_r8_n(cpu, RL, 7);
    break;
  case BIT_7_HL_IND:
    cpu_bit_ind8_n(cpu, 7);
    break;

  case RES_0_A:
    cpu_res_r8_n(cpu, RA, 0);
    break;
  case RES_0_B:
    cpu_res_r8_n(cpu, RB, 0);
    break;
  case RES_0_C:
    cpu_res_r8_n(cpu, RC, 0);
    break;
  case RES_0_D:
    cpu_res_r8_n(cpu, RD, 0);
    break;
  case RES_0_E:
    cpu_res_r8_n(cpu, RE, 0);
    break;
  case RES_0_H:
    cpu_res_r8_n(cpu, RH, 0);
    break;
  case RES_0_L:
    cpu_res_r8_n(cpu, RL, 0);
    break;
  case RES_0_HL_IND:
    cpu_res_ind8_n(cpu, 0);
    break;

  case RES_1_A:
    cpu_res_r8_n(cpu, RA, 1);
    break;
  case RES_1_B:
    cpu_res_r8_n(cpu, RB, 1);
    break;
  case RES_1_C:
    cpu_res_r8_n(cpu, RC, 1);
    break;
  case RES_1_D:
    cpu_res_r8_n(cpu, RD, 1);
    break;
  case RES_1_E:
    cpu_res_r8_n(cpu, RE, 1);
    break;
  case RES_1_H:
    cpu_res_r8_n(cpu, RH, 1);
    break;
  case RES_1_L:
    cpu_res_r8_n(cpu, RL, 1);
    break;
  case RES_1_HL_IND:
    cpu_res_ind8_n(cpu, 1);
    break;

  case RES_2_A:
    cpu_res_r8_n(cpu, RA, 2);
    break;
  case RES_2_B:
    cpu_res_r8_n(cpu, RB, 2);
    break;
  case RES_2_C:
    cpu_res_r8_n(cpu, RC, 2);
    break;
  case RES_2_D:
    cpu_res_r8_n(cpu, RD, 2);
    break;
  case RES_2_E:
    cpu_res_r8_n(cpu, RE, 2);
    break;
  case RES_2_H:
    cpu_res_r8_n(cpu, RH, 2);
    break;
  case RES_2_L:
    cpu_res_r8_n(cpu, RL, 2);
    break;
  case RES_2_HL_IND:
    cpu_res_ind8_n(cpu, 2);
    break;

  case RES_3_A:
    cpu_res_r8_n(cpu, RA, 3);
    break;
  case RES_3_B:
    cpu_res_r8_n(cpu, RB, 3);
    break;
  case RES_3_C:
    cpu_res_r8_n(cpu, RC, 3);
    break;
  case RES_3_D:
    cpu_res_r8_n(cpu, RD, 3);
    break;
  case RES_3_E:
    cpu_res_r8_n(cpu, RE, 3);
    break;
  case RES_3_H:
    cpu_res_r8_n(cpu, RH, 3);
    break;
  case RES_3_L:
    cpu_res_r8_n(cpu, RL, 3);
    break;
  case RES_3_HL_IND:
    cpu_res_ind8_n(cpu, 3);
    break;

  case RES_4_A:
    cpu_res_r8_n(cpu, RA, 4);
    break;
  case RES_4_B:
    cpu_res_r8_n(cpu, RB, 4);
    break;
  case RES_4_C:
    cpu_res_r8_n(cpu, RC, 4);
    break;
  case RES_4_D:
    cpu_res_r8_n(cpu, RD, 4);
    break;
  case RES_4_E:
    cpu_res_r8_n(cpu, RE, 4);
    break;
  case RES_4_H:
    cpu_res_r8_n(cpu, RH, 4);
    break;
  case RES_4_L:
    cpu_res_r8_n(cpu, RL, 4);
    break;
  case RES_4_HL_IND:
    cpu_res_ind8_n(cpu, 4);
    break;

  case RES_5_A:
    cpu_res_r8_n(cpu, RA, 5);
    break;
  case RES_5_B:
    cpu_res_r8_n(cpu, RB, 5);
    break;
  case RES_5_C:
    cpu_res_r8_n(cpu, RC, 5);
    break;
  case RES_5_D:
    cpu_res_r8_n(cpu, RD, 5);
    break;
  case RES_5_E:
    cpu_res_r8_n(cpu, RE, 5);
    break;
  case RES_5_H:
    cpu_res_r8_n(cpu, RH, 5);
    break;
  case RES_5_L:
    cpu_res_r8_n(cpu, RL, 5);
    break;
  case RES_5_HL_IND:
    cpu_res_ind8_n(cpu, 5);
    break;

  case RES_6_A:
    cpu_res_r8_n(cpu, RA, 6);
    break;
  case RES_6_B:
    cpu_res_r8_n(cpu, RB, 6);
    break;
  case RES_6_C:
    cpu_res_r8_n(cpu, RC, 6);
    break;
  case RES_6_D:
    cpu_res_r8_n(cpu, RD, 6);
    break;
  case RES_6_E:
    cpu_res_r8_n(cpu, RE, 6);
    break;
  case RES_6_H:
    cpu_res_r8_n(cpu, RH, 6);
    break;
  case RES_6_L:
    cpu_res_r8_n(cpu, RL, 6);
    break;
  case RES_6_HL_IND:
    cpu_res_ind8_n(cpu, 6);
    break;

  case RES_7_A:
    cpu_res_r8_n(cpu, RA, 7);
    break;
  case RES_7_B:
    cpu_res_r8_n(cpu, RB, 7);
    break;
  case RES_7_C:
    cpu_res_r8_n(cpu, RC, 7);
    break;
  case RES_7_D:
    cpu_res_r8_n(cpu, RD, 7);
    break;
  case RES_7_E:
    cpu_res_r8_n(cpu, RE, 7);
    break;
  case RES_7_H:
    cpu_res_r8_n(cpu, RH, 7);
    break;
  case RES_7_L:
    cpu_res_r8_n(cpu, RL, 7);
    break;
  case RES_7_HL_IND:
    cpu_res_ind8_n(cpu, 7);
    break;

  case SET_0_A:
    cpu_set_r8_n(cpu, RA, 0);
    break;
  case SET_0_B:
    cpu_set_r8_n(cpu, RB, 0);
    break;
  case SET_0_C:
    cpu_set_r8_n(cpu, RC, 0);
    break;
  case SET_0_D:
    cpu_set_r8_n(cpu, RD, 0);
    break;
  case SET_0_E:
    cpu_set_r8_n(cpu, RE, 0);
    break;
  case SET_0_H:
    cpu_set_r8_n(cpu, RH, 0);
    break;
  case SET_0_L:
    cpu_set_r8_n(cpu, RL, 0);
    break;
  case SET_0_HL_IND:
    cpu_set_ind8_n(cpu, 0);
    break;

  case SET_1_A:
    cpu_set_r8_n(cpu, RA, 1);
    break;
  case SET_1_B:
    cpu_set_r8_n(cpu, RB, 1);
    break;
  case SET_1_C:
    cpu_set_r8_n(cpu, RC, 1);
    break;
  case SET_1_D:
    cpu_set_r8_n(cpu, RD, 1);
    break;
  case SET_1_E:
    cpu_set_r8_n(cpu, RE, 1);
    break;
  case SET_1_H:
    cpu_set_r8_n(cpu, RH, 1);
    break;
  case SET_1_L:
    cpu_set_r8_n(cpu, RL, 1);
    break;
  case SET_1_HL_IND:
    cpu_set_ind8_n(cpu, 1);
    break;

  case SET_2_A:
    cpu_set_r8_n(cpu, RA, 2);
    break;
  case SET_2_B:
    cpu_set_r8_n(cpu, RB, 2);
    break;
  case SET_2_C:
    cpu_set_r8_n(cpu, RC, 2);
    break;
  case SET_2_D:
    cpu_set_r8_n(cpu, RD, 2);
    break;
  case SET_2_E:
    cpu_set_r8_n(cpu, RE, 2);
    break;
  case SET_2_H:
    cpu_set_r8_n(cpu, RH, 2);
    break;
  case SET_2_L:
    cpu_set_r8_n(cpu, RL, 2);
    break;
  case SET_2_HL_IND:
    cpu_set_ind8_n(cpu, 2);
    break;

  case SET_3_A:
    cpu_set_r8_n(cpu, RA, 3);
    break;
  case SET_3_B:
    cpu_set_r8_n(cpu, RB, 3);
    break;
  case SET_3_C:
    cpu_set_r8_n(cpu, RC, 3);
    break;
  case SET_3_D:
    cpu_set_r8_n(cpu, RD, 3);
    break;
  case SET_3_E:
    cpu_set_r8_n(cpu, RE, 3);
    break;
  case SET_3_H:
    cpu_set_r8_n(cpu, RH, 3);
    break;
  case SET_3_L:
    cpu_set_r8_n(cpu, RL, 3);
    break;
  case SET_3_HL_IND:
    cpu_set_ind8_n(cpu, 3);
    break;

  case SET_4_A:
    cpu_set_r8_n(cpu, RA, 4);
    break;
  case SET_4_B:
    cpu_set_r8_n(cpu, RB, 4);
    break;
  case SET_4_C:
    cpu_set_r8_n(cpu, RC, 4);
    break;
  case SET_4_D:
    cpu_set_r8_n(cpu, RD, 4);
    break;
  case SET_4_E:
    cpu_set_r8_n(cpu, RE, 4);
    break;
  case SET_4_H:
    cpu_set_r8_n(cpu, RH, 4);
    break;
  case SET_4_L:
    cpu_set_r8_n(cpu, RL, 4);
    break;
  case SET_4_HL_IND:
    cpu_set_ind8_n(cpu, 4);
    break;

  case SET_5_A:
    cpu_set_r8_n(cpu, RA, 5);
    break;
  case SET_5_B:
    cpu_set_r8_n(cpu, RB, 5);
    break;
  case SET_5_C:
    cpu_set_r8_n(cpu, RC, 5);
    break;
  case SET_5_D:
    cpu_set_r8_n(cpu, RD, 5);
    break;
  case SET_5_E:
    cpu_set_r8_n(cpu, RE, 5);
    break;
  case SET_5_H:
    cpu_set_r8_n(cpu, RH, 5);
    break;
  case SET_5_L:
    cpu_set_r8_n(cpu, RL, 5);
    break;
  case SET_5_HL_IND:
    cpu_set_ind8_n(cpu, 5);
    break;

  case SET_6_A:
    cpu_set_r8_n(cpu, RA, 6);
    break;
  case SET_6_B:
    cpu_set_r8_n(cpu, RB, 6);
    break;
  case SET_6_C:
    cpu_set_r8_n(cpu, RC, 6);
    break;
  case SET_6_D:
    cpu_set_r8_n(cpu, RD, 6);
    break;
  case SET_6_E:
    cpu_set_r8_n(cpu, RE, 6);
    break;
  case SET_6_H:
    cpu_set_r8_n(cpu, RH, 6);
    break;
  case SET_6_L:
    cpu_set_r8_n(cpu, RL, 6);
    break;
  case SET_6_HL_IND:
    cpu_set_ind8_n(cpu, 6);
    break;

  case SET_7_A:
    cpu_set_r8_n(cpu, RA, 7);
    break;
  case SET_7_B:
    cpu_set_r8_n(cpu, RB, 7);
    break;
  case SET_7_C:
    cpu_set_r8_n(cpu, RC, 7);
    break;
  case SET_7_D:
    cpu_set_r8_n(cpu, RD, 7);
    break;
  case SET_7_E:
    cpu_set_r8_n(cpu, RE, 7);
    break;
  case SET_7_H:
    cpu_set_r8_n(cpu, RH, 7);
    break;
  case SET_7_L:
    cpu_set_r8_n(cpu, RL, 7);
    break;
  case SET_7_HL_IND:
    cpu_set_ind8_n(cpu, 7);
    break;

  case RLC_A:
    cpu_rlc_r8(cpu, RA);
    break;
  case RLC_B:
    cpu_rlc_r8(cpu, RB);
    break;
  case RLC_C:
    cpu_rlc_r8(cpu, RC);
    break;
  case RLC_D:
    cpu_rlc_r8(cpu, RD);
    break;
  case RLC_E:
    cpu_rlc_r8(cpu, RE);
    break;
  case RLC_H:
    cpu_rlc_r8(cpu, RH);
    break;
  case RLC_L:
    cpu_rlc_r8(cpu, RH);
    break;
  case RLC_HL_IND:
    cpu_rlc_ind8(cpu);
    break;

  case RL_A:
    cpu_rl_r8(cpu, RA);
    break;
  case RL_B:
    cpu_rl_r8(cpu, RB);
    break;
  case RL_C:
    cpu_rl_r8(cpu, RC);
    break;
  case RL_D:
    cpu_rl_r8(cpu, RD);
    break;
  case RL_E:
    cpu_rl_r8(cpu, RE);
    break;
  case RL_H:
    cpu_rl_r8(cpu, RH);
    break;
  case RL_L:
    cpu_rl_r8(cpu, RL);
    break;
  case RL_HL_IND:
    cpu_rl_ind8(cpu);
    break;

  case RRC_A:
    cpu_rrc_r8(cpu, RA);
    break;
  case RRC_B:
    cpu_rrc_r8(cpu, RB);
    break;
  case RRC_C:
    cpu_rrc_r8(cpu, RC);
    break;
  case RRC_D:
    cpu_rrc_r8(cpu, RD);
    break;
  case RRC_E:
    cpu_rrc_r8(cpu, RE);
    break;
  case RRC_H:
    cpu_rrc_r8(cpu, RH);
    break;
  case RRC_L:
    cpu_rrc_r8(cpu, RL);
    break;
  case RRC_HL_IND:
    cpu_rrc_ind8(cpu);
    break;

  case RR_A:
    cpu_rr_r8(cpu, RA);
    break;
  case RR_B:
    cpu_rr_r8(cpu, RB);
    break;
  case RR_C:
    cpu_rr_r8(cpu, RC);
    break;
  case RR_D:
    cpu_rr_r8(cpu, RD);
    break;
  case RR_E:
    cpu_rr_r8(cpu, RE);
    break;
  case RR_H:
    cpu_rr_r8(cpu, RH);
    break;
  case RR_L:
    cpu_rr_r8(cpu, RL);
    break;
  case RR_HL_IND:
    cpu_rr_ind8(cpu);
    break;

  case SLA_A:
    cpu_sla_r8(cpu, RA);
    break;
  case SLA_B:
    cpu_sla_r8(cpu, RB);
    break;
  case SLA_C:
    cpu_sla_r8(cpu, RC);
    break;
  case SLA_D:
    cpu_sla_r8(cpu, RD);
    break;
  case SLA_E:
    cpu_sla_r8(cpu, RE);
    break;
  case SLA_H:
    cpu_sla_r8(cpu, RH);
    break;
  case SLA_L:
    cpu_sla_r8(cpu, RL);
    break;
  case SLA_HL_IND:
    cpu_sla_ind8(cpu);
    break;

  case SRA_A:
    cpu_sra_r8(cpu, RA);
    break;
  case SRA_B:
    cpu_sra_r8(cpu, RB);
    break;
  case SRA_C:
    cpu_sra_r8(cpu, RC);
    break;
  case SRA_D:
    cpu_sra_r8(cpu, RD);
    break;
  case SRA_E:
    cpu_sra_r8(cpu, RE);
    break;
  case SRA_H:
    cpu_sra_r8(cpu, RH);
    break;
  case SRA_L:
    cpu_sra_r8(cpu, RL);
    break;
  case SRA_HL_IND:
    cpu_sra_ind8(cpu);
    break;

  case SRL_A:
    cpu_srl_r8(cpu, RA);
    break;
  case SRL_B:
    cpu_srl_r8(cpu, RB);
    break;
  case SRL_C:
    cpu_srl_r8(cpu, RC);
    break;
  case SRL_D:
    cpu_srl_r8(cpu, RD);
    break;
  case SRL_E:
    cpu_srl_r8(cpu, RE);
    break;
  case SRL_H:
    cpu_srl_r8(cpu, RH);
    break;
  case SRL_L:
    cpu_srl_r8(cpu, RL);
    break;
  case SRL_HL_IND:
    cpu_srl_ind8(cpu);
    break;

  case SWAP_A:
    cpu_swap_r8(cpu, RA);
    break;
  case SWAP_B:
    cpu_swap_r8(cpu, RB);
    break;
  case SWAP_C:
    cpu_swap_r8(cpu, RC);
    break;
  case SWAP_D:
    cpu_swap_r8(cpu, RD);
    break;
  case SWAP_E:
    cpu_swap_r8(cpu, RE);
    break;
  case SWAP_H:
    cpu_swap_r8(cpu, RH);
    break;
  case SWAP_L:
    cpu_swap_r8(cpu, RL);
    break;
  case SWAP_HL_IND:
    cpu_swap_ind8(cpu);
    break;

  default:
    exit(ERR_BAD_OPCODE);
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

// INSTRUCTIONS ////////////////////////////////////////////////////////////////
//// ADC ///////////////////////////////////////////////////////////////////////
void cpu_adc_flags(struct cpu* cpu, unsigned char a, unsigned char b, unsigned int t) {
  unsigned int  carries=t ^ a ^ b;
  unsigned char z=t&0xFF ? 0 : ZF;
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
  cpu->busy = 4;
}

void cpu_adc_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  unsigned int t=a+b;
  if(cpu_get_r8(cpu, RF) & CF)
    t = t+1;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_adc_flags(cpu, a, b, t);
  cpu->busy = 8;
}

void cpu_adc_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=memory_get_d8(cpu->memory, p);
  unsigned int t=a+b;
  if(cpu_get_r8(cpu, RF) & CF)
    t = t+1;
  cpu_set_r8(cpu, RA, t);
  cpu_adc_flags(cpu, a, b, t);
  cpu->busy = 8;
}

//// ADD ///////////////////////////////////////////////////////////////////////
void cpu_add8_flags(struct cpu* cpu, unsigned char a, unsigned char b, unsigned int t) {
  unsigned int  carries=t ^ a ^ b;
  unsigned char z=t&0xFF ? 0 : ZF;
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
  cpu->busy = 4;
}

void cpu_add8_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  unsigned int t=a+b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_add8_flags(cpu, a, b, t);
  cpu->busy = 8;
}

void cpu_add8_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=memory_get_d8(cpu->memory, p);
  unsigned int t=a+b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_add8_flags(cpu, a, b, t);
  cpu->busy = 8;
}

void cpu_add16_flags(struct cpu* cpu, unsigned short a, unsigned short b, unsigned int t) {
  unsigned int  carries=t ^ a ^ b;
  unsigned char z=t&0xFFFF ? 0 : ZF;
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
  cpu->busy = 8;
}

void cpu_add16_d16(struct cpu* cpu, unsigned short d16) {
  unsigned short a=cpu_get_r16(cpu, RHL);
  unsigned short b=d16;
  unsigned int t=a+b;
  cpu_set_r16(cpu, RHL, (unsigned short) t);
  cpu_add16_flags(cpu, a, b, t);
  cpu->busy = 8;
}

void cpu_add16_sp(struct cpu* cpu, signed char d8) {
  cpu->regs.sp += d8;

  unsigned short a=cpu->regs.sp;
  signed char b=d8;
  signed int t=a+b;
  
  unsigned int carries=(t & 0x1FFFF) ^ a ^ b;
  unsigned char z=0;
  unsigned char n=0;
  unsigned char h=carries & 0x10 ? HF : 0;
  unsigned char c=carries ^ 0x100 ? CF : 0;
  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 16;
}

//// AND ///////////////////////////////////////////////////////////////////////
void cpu_and_flags(struct cpu* cpu, unsigned char a, unsigned char b, unsigned char t) {
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=HF;
  unsigned char c=0;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_and_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu_get_r8(cpu, rb);
  unsigned char t=a & b;
  cpu_set_r8(cpu, RA, t);
  cpu_and_flags(cpu, a, b, t);
  cpu->busy = 4;
}

void cpu_and_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  unsigned char t=a & b;
  cpu_set_r8(cpu, RA, t);
  cpu_and_flags(cpu, a, b, t);
  cpu->busy = 8;
}

void cpu_and_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=memory_get_d8(cpu->memory, p);
  unsigned char t=a & b;
  cpu_set_r8(cpu, RA, t);
  cpu_and_flags(cpu, a, b, t);
  cpu->busy = 8;
}

//// CALL //////////////////////////////////////////////////////////////////////
void cpu_call_cond(struct cpu* cpu, unsigned short p, unsigned char mask, unsigned char test) {
  unsigned char f=cpu_get_r8(cpu, RF);
  if((f & mask) == test) {
    unsigned char pcl=US_TO_LUC(cpu->regs.pc);
    unsigned char pch=US_TO_HUC(cpu->regs.pc);

    memory_set_d8(cpu->memory, --cpu->regs.sp, pch);
    memory_set_d8(cpu->memory, --cpu->regs.sp, pcl);

    cpu->regs.pc = p;

    cpu->busy = 24;
  }
  else {
    cpu->busy = 12;
  }
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
  cpu->busy = 4;
}

void cpu_cp_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  cpu_cp_flags(cpu, a, b);
  cpu->busy = 8;
}

void cpu_cp_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=memory_get_d8(cpu->memory, p);
  cpu_cp_flags(cpu, a, b);
  cpu->busy = 8;
}

// DEC /////////////////////////////////////////////////////////////////////////
void cpu_dec8_flags(struct cpu* cpu, unsigned char a, signed int t) {
  unsigned int carries=(t ^ 0x1FF) ^ a ^ ((signed char) -1);
  unsigned char f=cpu_get_r8(cpu, RF);
  unsigned char z=(t&0xFF)==0 ? ZF : 0;
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
  cpu->busy = 4;
}

void cpu_dec8_ind8(struct cpu* cpu) {
  unsigned short hl=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, hl);
  signed int t=a-1;
  memory_set_d8(cpu->memory, hl, (unsigned char) t);
  cpu_dec8_flags(cpu, a, t);
  cpu->busy = 12;
}

void cpu_dec16_flags(struct cpu* cpu, unsigned short a, signed int t) {
  // Flags not affected
}

void cpu_dec16_r16(struct cpu* cpu, int rb) {
  unsigned short a=cpu_get_r16(cpu, rb);
  signed int t=a-1;
  cpu_set_r16(cpu, rb, (unsigned short) t);
  cpu_dec16_flags(cpu, a, t);
  cpu->busy = 8;
}

void cpu_dec16_sp(struct cpu* cpu) {
  unsigned short a=cpu->regs.sp;
  signed int t=a-1;
  cpu->regs.sp = (unsigned short) t;
  cpu_dec16_flags(cpu, a, t);
  cpu->busy = 8;
}

// INC /////////////////////////////////////////////////////////////////////////
void cpu_inc8_flags(struct cpu* cpu, unsigned char a, unsigned int t) {
  unsigned int carries=t ^ a ^ ((unsigned char) +1);
  unsigned char f=cpu_get_r8(cpu, RF);
  unsigned char z=(t&0xFF)==0 ? ZF : 0;
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
  fprintf(stderr, "INC %d : %d -> %d (%02x)\n", rb, a, t, cpu_get_r8(cpu, RF));
  cpu->busy = 4;
}

void cpu_inc8_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);
  unsigned int t=a+1;
  memory_set_d8(cpu->memory, p, (unsigned char) t);
  cpu_inc8_flags(cpu, a, t);
  cpu->busy = 12;
}

void cpu_inc16_flags(struct cpu* cpu, unsigned short a, signed int t) {
  // Flags not affected
}

void cpu_inc16_r16(struct cpu* cpu, int rb) {
  unsigned short a=cpu_get_r16(cpu, rb);
  unsigned int t=a+1;
  cpu_set_r16(cpu, rb, (unsigned short) t);
  cpu_inc16_flags(cpu, a, t);
  cpu->busy = 8;
}

void cpu_inc16_sp(struct cpu* cpu) {
  unsigned short a=cpu->regs.sp;
  unsigned int t=a+1;
  cpu->regs.sp = (unsigned short) t;
  cpu_inc16_flags(cpu, a, t);
  cpu->busy = 8;
}

// LD //////////////////////////////////////////////////////////////////////////
void cpu_ld_r8_r8(struct cpu* cpu, int ra, int rb) {
  unsigned char b=cpu_get_r8(cpu, rb);
  cpu_set_r8(cpu, ra, b);
  cpu->busy = 4;
}

void cpu_ld_r8_d8(struct cpu* cpu, int ri, unsigned char d8) {
  unsigned char b=d8;
  cpu_set_r8(cpu, ri, b);
  cpu->busy = 8;
}

void cpu_ld_r8_ind8(struct cpu* cpu, int ra, int rb) {
  unsigned short p=cpu_get_r16(cpu, rb);
  unsigned char t=memory_get_d8(cpu->memory, p);
  cpu_set_r8(cpu, ra, t);
  cpu->busy = 8;
}

void cpu_ld_ind8_r8(struct cpu* cpu, int ra, int rb) {
  unsigned char a=cpu_get_r8(cpu, rb);
  unsigned short p=cpu_get_r16(cpu, ra);
  memory_set_d8(cpu->memory, p, a);
  cpu->busy = 8;
}

void cpu_ld_hl_spd8(struct cpu* cpu, signed char d8) {
  unsigned short a=cpu->regs.sp;
  signed char b=d8;
  signed int t=a+b;

  unsigned int  carries=(t & 0x1FF) ^ a ^ b;
  unsigned char z=0;
  unsigned char n=0;
  unsigned char h=carries&0x10 ? HF : 0;
  unsigned char c=carries&0x100 ? CF : 0;

  cpu_set_r16(cpu, RHL, (unsigned short) t);
  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 12;
}

//// OR ////////////////////////////////////////////////////////////////////////
void cpu_or_flags(struct cpu* cpu, unsigned char a, unsigned char b, unsigned char t) {
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=0;
  unsigned char c=0;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_or_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu_get_r8(cpu, rb);
  unsigned char t=a | b;
  cpu_set_r8(cpu, RA, t);
  cpu_or_flags(cpu, a, b, t);
  cpu->busy = 4;
}

void cpu_or_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  unsigned char t=a | b;
  cpu_set_r8(cpu, RA, t);
  cpu_or_flags(cpu, a, b, t);
  cpu->busy = 8;
}

void cpu_or_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=memory_get_d8(cpu->memory, p);
  unsigned char t=a | b;
  cpu_set_r8(cpu, RA, t);
  cpu_or_flags(cpu, a, b, t);
  cpu->busy = 8;
}

//// PUSH //////////////////////////////////////////////////////////////////////
void cpu_push_r16(struct cpu* cpu, int ri) {
  unsigned char l=cpu_get_r8(cpu, ri+0);
  unsigned char h=cpu_get_r8(cpu, ri+1);

  memory_set_d8(cpu->memory, --cpu->regs.sp, h);
  memory_set_d8(cpu->memory, --cpu->regs.sp, l);

  cpu->busy = 16;
}

//// POP ///////////////////////////////////////////////////////////////////////
void cpu_pop_r16(struct cpu* cpu, int ri) {
  unsigned char l=memory_get_d8(cpu->memory, cpu->regs.sp++);
  unsigned char h=memory_get_d8(cpu->memory, cpu->regs.sp++);

  cpu_set_r8(cpu, ri+0, l);
  cpu_set_r8(cpu, ri+1, h);

  cpu->busy = 12;
}

//// SBC ///////////////////////////////////////////////////////////////////////
void cpu_sbc_flags(struct cpu* cpu, unsigned char a, unsigned char b, signed int t) {
  unsigned int  carries=(t & 0x1FFFF) ^ a ^ b;
  unsigned char z=(t&0xFF) ? 0 : ZF;
  unsigned char n=NF;
  unsigned char h=carries & 0x10  ? 0 : HF;
  unsigned char c=carries & 0x100 ? 0 : CF;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_sbc_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu_get_r8(cpu, rb);
  signed int t=a-b;
  if(cpu_get_r8(cpu, RF) & CF)
    t = t-1;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_sbc_flags(cpu, a, b, t);
  cpu->busy = 4;
}

void cpu_sbc_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  signed int t=a-b;
  if(cpu_get_r8(cpu, RF) & CF)
    t = t-1;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_sbc_flags(cpu, a, b, t);
  cpu->busy = 8;
}

void cpu_sbc_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=memory_get_d8(cpu->memory, p);
  signed int t=a-b;
  if(cpu_get_r8(cpu, RF) & CF)
    t = t-1;
  cpu_set_r8(cpu, RA, t);
  cpu_sbc_flags(cpu, a, b, t);
  cpu->busy = 8;
}

//// SUB ///////////////////////////////////////////////////////////////////////
void cpu_sub_flags(struct cpu* cpu, unsigned char a, unsigned char b, signed int t) {
  unsigned int  carries=(t & 0x1FF) ^ a ^ b;
  unsigned char z=t&0xFF ? 0 : ZF;
  unsigned char n=1;
  unsigned char h=carries & 0x10  ? 0 : HF;
  unsigned char c=carries & 0x100 ? 0 : CF;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_sub_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu_get_r8(cpu, rb);
  signed int t=a-b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_sub_flags(cpu, a, b, t);
  cpu->busy = 4;
}

void cpu_sub_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  signed int t=a-b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_sub_flags(cpu, a, b, t);
  cpu->busy = 8;
}

void cpu_sub_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=memory_get_d8(cpu->memory, p);
  signed int t=a-b;
  cpu_set_r8(cpu, RA, (unsigned char) t);
  cpu_sub_flags(cpu, a, b, t);
  cpu->busy = 8;
}

//// XOR ///////////////////////////////////////////////////////////////////////
void cpu_xor_flags(struct cpu* cpu, unsigned char a, unsigned char b, unsigned char t) {
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=0;
  unsigned char c=0;
  cpu_set_r8(cpu, RF, z | n | h | c);
}

void cpu_xor_r8(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=cpu_get_r8(cpu, rb);
  unsigned char t=a ^ b;
  cpu_set_r8(cpu, RA, t);
  cpu_xor_flags(cpu, a, b, t);
  cpu->busy = 4;
}

void cpu_xor_d8(struct cpu* cpu, unsigned char d8) {
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=d8;
  unsigned char t=a ^ b;
  cpu_set_r8(cpu, RA, t);
  cpu_xor_flags(cpu, a, b, t);
  cpu->busy = 8;
}

void cpu_xor_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=cpu_get_r8(cpu, RA);
  unsigned char b=memory_get_d8(cpu->memory, p);
  unsigned char t=a ^ b;
  cpu_set_r8(cpu, RA, t);
  cpu_xor_flags(cpu, a, b, t);
  cpu->busy = 8;
}

//// RST ///////////////////////////////////////////////////////////////////////
void cpu_rst_addr(struct cpu* cpu, unsigned short addr) {
  unsigned char l=US_TO_LUC(cpu->regs.pc);
  unsigned char h=US_TO_HUC(cpu->regs.pc);

  memory_set_d8(cpu->memory, --cpu->regs.sp, h);
  memory_set_d8(cpu->memory, --cpu->regs.sp, l);
  
  cpu->regs.pc = addr;

  cpu->busy = 16;
}

//// ROTATION //////////////////////////////////////////////////////////////////
void cpu_rr_r8(struct cpu* cpu, int ri) {
  unsigned char f=cpu_get_r8(cpu, RF);
  unsigned char a=cpu_get_r8(cpu, ri);

  unsigned char t=a >> 1;
  if(f & CF)
    t = t | 0x80;
  
  unsigned char z=t ? 0 : ZF;
  unsigned char h=0;
  unsigned char n=0;
  unsigned char c=a&0x01 ? CF : 0;

  cpu_set_r8(cpu, ri, t);
  cpu_set_r8(cpu, RF, z | h | n | c);

  cpu->busy = 8;
}

void cpu_rr_ind8(struct cpu* cpu) {
  unsigned char f=cpu_get_r8(cpu, RF);
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);

  unsigned char t=a >> 1;
  if(f & CF)
    t = t | 0x80;

  unsigned char z=t ? 0 : ZF;
  unsigned char h=0;
  unsigned char n=0;
  unsigned char c=a&0x01 ? CF : 0;

  memory_set_d8(cpu->memory, p, t);
  cpu_set_r8(cpu, RF, z | h | n | c);

  cpu->busy = 16;
}

void cpu_rrc_r8(struct cpu* cpu, int ri) {
  unsigned char a=cpu_get_r8(cpu, ri);

  unsigned char c;
  unsigned char t=a >> 1;
  if(a & 0x01) {
    t = t | 0x80;
    c = CF;
  }
  else
    c = 0;

  unsigned char z=t ? 0 : ZF;
  unsigned char h=0;
  unsigned char n=0;

  cpu_set_r8(cpu, ri, t);
  cpu_set_r8(cpu, RF, z | h | n | c);

  cpu->busy = 8;
}

void cpu_rrc_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);

  unsigned char c;
  unsigned char t=a >> 1;
  if(a & 0x01) {
    t = t | 0x80;
    c = CF;
  }
  else
    c = 0;

  unsigned char z=t ? 0 : ZF;
  unsigned char h=0;
  unsigned char n=0;

  memory_set_d8(cpu->memory, p, t);
  cpu_set_r8(cpu, RF, z | h | n | c);

  cpu->busy = 16;
}

void cpu_rl_r8(struct cpu* cpu, int ri) {
  unsigned char f=cpu_get_r8(cpu, RF);
  unsigned char a=cpu_get_r8(cpu, ri);

  unsigned char t=a << 1;
  if(f & CF)
    t = t | 0x01;

  
  unsigned char z=t ? 0 : ZF;
  unsigned char h=0;
  unsigned char n=0;
  unsigned char c=a&0x80 ? CF : 0;

  cpu_set_r8(cpu, ri, t);
  cpu_set_r8(cpu, RF, z | h | n | c);

  cpu->busy = 8;
}

void cpu_rl_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);
  unsigned char f=cpu_get_r8(cpu, RF);

  unsigned char t=a << 1;
  if(f & CF)
    t = t | 0x01;
  
  unsigned char z=t ? 0 : ZF;
  unsigned char h=0;
  unsigned char n=0;
  unsigned char c=a&0x80 ? CF : 0;

  memory_set_d8(cpu->memory, p, t);
  cpu_set_r8(cpu, RF, z | h | n | c);

  cpu->busy = 16;
}

void cpu_rlc_r8(struct cpu* cpu, int ri) {
  unsigned char a=cpu_get_r8(cpu, ri);

  unsigned char c;
  unsigned char t=a << 1;
  if(a & 0x80) {
    t = t | 0x01;
    c = CF;
  }
  else
    c = 0;

  unsigned char z=t ? 0 : ZF;
  unsigned char h=0;
  unsigned char n=0;

  cpu_set_r8(cpu, ri, t);
  cpu_set_r8(cpu, RF, z | h | n | c);

  cpu->busy = 8;
}

void cpu_rlc_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);

  unsigned char c;
  unsigned char t=a << 1;
  if(a & 0x80) {
    t = t | 0x01;
    c = CF;
  }
  else
    c = 0;

  unsigned char z=t ? 0 : ZF;
  unsigned char h=0;
  unsigned char n=0;

  memory_set_d8(cpu->memory, p, t);
  cpu_set_r8(cpu, RF, z | h | n | c);

  cpu->busy = 16;
}

//// BIT ///////////////////////////////////////////////////////////////////////
void cpu_bit_r8_n(struct cpu* cpu, int ri, int bi) {
  unsigned char a=cpu_get_r8(cpu, ri);
  unsigned char m=1 << bi;
  unsigned char f=cpu_get_r8(cpu, RF);

  unsigned char z=a & m ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=HF;
  unsigned char c=f & CF;

  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 8;
}

void cpu_bit_ind8_n(struct cpu* cpu, int bi) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);
  unsigned char m=1 << bi;
  unsigned char f=cpu_get_r8(cpu, RF);

  unsigned char z=a & m ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=HF;
  unsigned char c=f & CF;

  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 16;
}

void cpu_set_r8_n(struct cpu* cpu, int ri, int bi) {
  unsigned char a=cpu_get_r8(cpu, ri);
  unsigned char m=1 << bi;
  cpu_set_r8(cpu, ri, a | m);
  cpu->busy = 8;
}

void cpu_set_ind8_n(struct cpu* cpu, int bi) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);
  unsigned char m=1 << bi;
  memory_set_d8(cpu->memory, p, a | m);
  cpu->busy = 16;
}

void cpu_res_r8_n(struct cpu* cpu, int ri, int bi) {
  unsigned char a=cpu_get_r8(cpu, ri);
  unsigned char m=1 << bi;
  cpu_set_r8(cpu, ri, a & ~m);
  cpu->busy = 8;
}

void cpu_res_ind8_n(struct cpu* cpu, int bi) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);
  unsigned char m=1 << bi;
  memory_set_d8(cpu->memory, p, a & ~m);
  cpu->busy = 16;
}

void cpu_swap_r8(struct cpu* cpu, int ri) {
  unsigned char a=cpu_get_r8(cpu, ri);
  unsigned char al=a & 0x0F;
  unsigned char ah=a & 0xF0;
  unsigned char t=(al << 4) | (ah >> 4);

  unsigned char z=t ? 0 : ZF;

  cpu_set_r8(cpu, ri, t);  
  cpu_set_r8(cpu, RF, z);

  cpu->busy = 8;
}

void cpu_swap_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);
  unsigned char al=a & 0x0F;
  unsigned char ah=a & 0xF0;
  unsigned char t=(al << 4) | (ah >> 4);

  unsigned char z=t ? 0 : ZF;
  
  memory_set_d8(cpu->memory, p, t);
  cpu_set_r8(cpu, RF, z);

  cpu->busy = 16;
}

void cpu_sla_r8(struct cpu* cpu, int ri) {
  unsigned char a=cpu_get_r8(cpu, ri);
  unsigned char t=a << 1;
  
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=0;
  unsigned char c=a & 0x80 ? CF : 0;

  cpu_set_r8(cpu, ri, t);
  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 8;
}

void cpu_sla_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);
  unsigned char t=a << 1;
  
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=0;
  unsigned char c=a & 0x80 ? CF : 0;

  memory_set_d8(cpu->memory, p, t);
  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 16;
}

void cpu_sra_r8(struct cpu* cpu, int ri) {
  unsigned char a=cpu_get_r8(cpu, ri);
  unsigned char t=a >> 1;
  if(a & 0x80)
    t |= 0x80;
  
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=0;
  unsigned char c=a & 0x01 ? CF : 0;

  cpu_set_r8(cpu, ri, t);
  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 8;
}

void cpu_sra_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);
  unsigned char t=a >> 1;
  if(a & 0x80)
    t |= 0x80;
  
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=0;
  unsigned char c=a & 0x01 ? CF : 0;

  memory_set_d8(cpu->memory, p, t);
  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 16;
}

void cpu_srl_r8(struct cpu* cpu, int ri) {
  unsigned char a=cpu_get_r8(cpu, ri);
  unsigned char t=a >> 1;
  
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=0;
  unsigned char c=a & 0x01 ? CF : 0;

  cpu_set_r8(cpu, ri, t);
  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 8;
}

void cpu_srl_ind8(struct cpu* cpu) {
  unsigned short p=cpu_get_r16(cpu, RHL);
  unsigned char a=memory_get_d8(cpu->memory, p);
  unsigned char t=a >> 1;
  
  unsigned char z=t ? 0 : ZF;
  unsigned char n=0;
  unsigned char h=0;
  unsigned char c=a & 0x01 ? CF : 0;

  memory_set_d8(cpu->memory, p, t);
  cpu_set_r8(cpu, RF, z | n | h | c);

  cpu->busy = 16;
}
