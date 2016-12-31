#include "opcodes.h"

////////////////////////////////////////////////////////////////////////////////
// DIRECT OPCODES //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// 0x0X ////////////////////////////////////////////////////////////////////////
const unsigned char NOP=0x00;
const unsigned char LD_BC_D16=0x01;
const unsigned char LD_IND_BC_A=0x02;
const unsigned char INC_BC=0x03;
const unsigned char INC_B=0x04;
const unsigned char DEC_B=0x05;
const unsigned char LD_B_D8=0x06;
const unsigned char RLCA=0x07;
const unsigned char LD_IND_A16_SP=0x08;
const unsigned char ADD_HL_BC=0x09;
const unsigned char LD_A_IND_BC=0x0A;
const unsigned char DEC_BC=0x0B;
const unsigned char INC_C=0x0C;
const unsigned char DEC_C=0x0D;
const unsigned char LD_C_D8=0x0E;
const unsigned char RRCA=0x0F;

// 0x1X ////////////////////////////////////////////////////////////////////////
const unsigned char STOP=0x10;
const unsigned char LD_DE_D16=0x11;
const unsigned char LD_IND_DE_A=0x12;
const unsigned char INC_DE=0x13;
const unsigned char INC_D=0x14;
const unsigned char DEC_D=0x15;
const unsigned char LD_D_D8=0x16;
const unsigned char RLA=0x17;
const unsigned char JR_R8=0x18;
const unsigned char ADD_HL_DE=0x19;
const unsigned char LD_A_IND_DE=0x1A;
const unsigned char DEC_DE=0x1B;
const unsigned char INC_E=0x1C;
const unsigned char DEC_E=0x1D;
const unsigned char LD_E_D8=0x1E;
const unsigned char RRA=0x1F;

// 0x2X ////////////////////////////////////////////////////////////////////////
const unsigned char JR_NZ_R8=0x20;
const unsigned char LD_HL_D16=0x21;
const unsigned char LD_IND_HL_PLUS_A=0x22;
const unsigned char INC_HL=0x23;
const unsigned char INC_H=0x24;
const unsigned char DEC_H=0x25;
const unsigned char LD_H_D8=0x26;
const unsigned char DAA=0x27;
const unsigned char JR_Z_R8=0x28;
const unsigned char ADD_HL_HL=0x29;
const unsigned char LD_A_IND_HL_PLUS=0x2A;
const unsigned char DEC_HL=0x2B;
const unsigned char INC_L=0x2C;
const unsigned char DEC_L=0x2D;
const unsigned char LD_L_D8=0x2E;
const unsigned char CPL=0x2F;

// 0x3X ////////////////////////////////////////////////////////////////////////
const unsigned char JR_NC_R8=0x30;
const unsigned char LD_SP_D16=0x31;
const unsigned char LD_IND_HL_MINUS_A=0x32;
const unsigned char INC_SP=0x33;
const unsigned char INC_HL_IND=0x34;
const unsigned char DEC_HL_IND=0x35;
const unsigned char LD_HL_IND_D8=0x36;
const unsigned char SCF=0x37;
const unsigned char JR_C_R8=0x38;
const unsigned char ADD_HL_SP=0x39;
const unsigned char LD_A_IND_HL_MINUS=0x3A;
const unsigned char DEC_SP=0x3B;
const unsigned char INC_A=0x3C;
const unsigned char DEC_A=0x3D;
const unsigned char LD_A_D8=0x3E;
const unsigned char CCF=0x3F;

// 0x4X ////////////////////////////////////////////////////////////////////////
const unsigned char LD_B_B=0x40;
const unsigned char LD_B_C=0x41;
const unsigned char LD_B_D=0x42;
const unsigned char LD_B_E=0x43;
const unsigned char LD_B_H=0x44;
const unsigned char LD_B_L=0x45;
const unsigned char LD_B_HL_IND=0x46;
const unsigned char LD_B_A=0x47;
const unsigned char LD_C_B=0x48;
const unsigned char LD_C_C=0x49;
const unsigned char LD_C_D=0x4A;
const unsigned char LD_C_E=0x4B;
const unsigned char LD_C_H=0x4C;
const unsigned char LD_C_L=0x4D;
const unsigned char LD_C_HL_IND=0x4E;
const unsigned char LD_C_A=0x4F;

// 0x5X ////////////////////////////////////////////////////////////////////////
const unsigned char LD_D_B=0x50;
const unsigned char LD_D_C=0x51;
const unsigned char LD_D_D=0x52;
const unsigned char LD_D_E=0x53;
const unsigned char LD_D_H=0x54;
const unsigned char LD_D_L=0x55;
const unsigned char LD_D_HL_IND=0x56;
const unsigned char LD_D_A=0x57;
const unsigned char LD_E_B=0x58;
const unsigned char LD_E_C=0x59;
const unsigned char LD_E_D=0x5A;
const unsigned char LD_E_E=0x5B;
const unsigned char LD_E_H=0x5C;
const unsigned char LD_E_L=0x5D;
const unsigned char LD_E_HL_IND=0x5E;
const unsigned char LD_E_A=0x5F;

// 0x6X ////////////////////////////////////////////////////////////////////////
const unsigned char LD_H_B=0x60;
const unsigned char LD_H_C=0x61;
const unsigned char LD_H_D=0x62;
const unsigned char LD_H_E=0x63;
const unsigned char LD_H_H=0x64;
const unsigned char LD_H_L=0x65;
const unsigned char LD_H_HL_IND=0x66;
const unsigned char LD_H_A=0x67;
const unsigned char LD_L_B=0x68;
const unsigned char LD_L_C=0x69;
const unsigned char LD_L_D=0x6A;
const unsigned char LD_L_E=0x6B;
const unsigned char LD_L_H=0x6C;
const unsigned char LD_L_L=0x6D;
const unsigned char LD_L_HL_IND=0x6E;
const unsigned char LD_L_A=0x6F;

// 0x7X ////////////////////////////////////////////////////////////////////////
const unsigned char LD_HL_IND_B=0x70;
const unsigned char LD_HL_IND_C=0x71;
const unsigned char LD_HL_IND_D=0x72;
const unsigned char LD_HL_IND_E=0x73;
const unsigned char LD_HL_IND_H=0x74;
const unsigned char LD_HL_IND_L=0x75;
const unsigned char HALT=0x76;
const unsigned char LD_HL_IND_A=0x77;
const unsigned char LD_A_B=0x78;
const unsigned char LD_A_C=0x79;
const unsigned char LD_A_D=0x7A;
const unsigned char LD_A_E=0x7B;
const unsigned char LD_A_H=0x7C;
const unsigned char LD_A_L=0x7D;
const unsigned char LD_A_HL_IND=0x7E;
const unsigned char LD_A_A=0x7F;

// 0x8X ////////////////////////////////////////////////////////////////////////
const unsigned char ADD_A_B=0x80;
const unsigned char ADD_A_C=0x81;
const unsigned char ADD_A_D=0x82;
const unsigned char ADD_A_E=0x83;
const unsigned char ADD_A_H=0x84;
const unsigned char ADD_A_L=0x85;
const unsigned char ADD_A_HL_IND=0x86;
const unsigned char ADD_A_A=0x87;
const unsigned char ADC_A_B=0x88;
const unsigned char ADC_A_C=0x89;
const unsigned char ADC_A_D=0x8A;
const unsigned char ADC_A_E=0x8B;
const unsigned char ADC_A_H=0x8C;
const unsigned char ADC_A_L=0x8D;
const unsigned char ADC_A_HL_IND=0x8E;
const unsigned char ADC_A_A=0x8F;

// 0x9X ////////////////////////////////////////////////////////////////////////
const unsigned char SUB_B=0x90;
const unsigned char SUB_C=0x91;
const unsigned char SUB_D=0x92;
const unsigned char SUB_E=0x93;
const unsigned char SUB_H=0x94;
const unsigned char SUB_L=0x95;
const unsigned char SUB_HL_IND=0x96;
const unsigned char SUB_A=0x97;
const unsigned char SBC_A_B=0x98;
const unsigned char SBC_A_C=0x99;
const unsigned char SBC_A_D=0x9A;
const unsigned char SBC_A_E=0x9B;
const unsigned char SBC_A_H=0x9C;
const unsigned char SBC_A_L=0x9D;
const unsigned char SBC_A_HL_IND=0x9E;
const unsigned char SBC_A_A=0x9F;

// 0xAX ////////////////////////////////////////////////////////////////////////
const unsigned char AND_B=0xA0;
const unsigned char AND_C=0xA1;
const unsigned char AND_D=0xA2;
const unsigned char AND_E=0xA3;
const unsigned char AND_H=0xA4;
const unsigned char AND_L=0xA5;
const unsigned char AND_HL_IND=0xA6;
const unsigned char AND_A=0xA7;
const unsigned char XOR_A_B=0xA8;
const unsigned char XOR_A_C=0xA9;
const unsigned char XOR_A_D=0xAA;
const unsigned char XOR_A_E=0xAB;
const unsigned char XOR_A_H=0xAC;
const unsigned char XOR_A_L=0xAD;
const unsigned char XOR_A_HL_IND=0xAE;
const unsigned char XOR_A_A=0xAF;

// 0xBX ////////////////////////////////////////////////////////////////////////
const unsigned char OR_B=0xB0;
const unsigned char OR_C=0xB1;
const unsigned char OR_D=0xB2;
const unsigned char OR_E=0xB3;
const unsigned char OR_H=0xB4;
const unsigned char OR_L=0xB5;
const unsigned char OR_HL_IND=0xB6;
const unsigned char OR_A=0xB7;
const unsigned char CP_A_B=0xB8;
const unsigned char CP_A_C=0xB9;
const unsigned char CP_A_D=0xBA;
const unsigned char CP_A_E=0xBB;
const unsigned char CP_A_H=0xBC;
const unsigned char CP_A_L=0xBD;
const unsigned char CP_A_HL_IND=0xBE;
const unsigned char CP_A_A=0xBF;

// 0xCX ////////////////////////////////////////////////////////////////////////
const unsigned char RET_NZ=0xC0;
const unsigned char POP_BC=0xC1;
const unsigned char JP_NZ_A16=0xC2;
const unsigned char JP_A16=0xC3;
const unsigned char CALL_NZ_A16=0xC4;
const unsigned char PUSH_BC=0xC5;
const unsigned char ADD_A_D8=0xC6;
const unsigned char RST_00H=0xC7;
const unsigned char RET_Z=0xC8;
const unsigned char RET=0xC9;
const unsigned char JP_Z_A16=0xCA;
const unsigned char PREFIX_CB=0xCB;
const unsigned char CALL_Z_A16=0xCC;
const unsigned char CALL_A16=0xCD;
const unsigned char ADC_A_D8=0xCE;
const unsigned char RST_08H=0xCF;

// 0xDX ////////////////////////////////////////////////////////////////////////
const unsigned char RET_NC=0xD0;
const unsigned char POP_DE=0xD1;
const unsigned char JP_NC_A16=0xD2;
const unsigned char CALL_NC_A16=0xD4;
const unsigned char PUSH_DE=0xD5;
const unsigned char SUB_D8=0xD6;
const unsigned char RST_10H=0xD7;
const unsigned char RET_C=0xD8;
const unsigned char RETI=0xD9;
const unsigned char JP_C_A16=0xDA;
const unsigned char CALL_C_A16=0xDC;
const unsigned char SBC_A_D8=0xDE;
const unsigned char RST_18H=0xDF;

// 0xEX ////////////////////////////////////////////////////////////////////////
const unsigned char LDH_A8_IND_A=0xE0;
const unsigned char POP_HL=0xE1;
const unsigned char LD_C_IND_A=0xE2;
const unsigned char PUSH_HL=0xE5;
const unsigned char AND_D8=0xE6;
const unsigned char RST_20H=0xE7;
const unsigned char ADD_SP_R8=0xE8;
const unsigned char JP_HL_IND=0xE9;
const unsigned char LD_A16_IND_A=0xEA;
const unsigned char XOR_D8=0xEE;
const unsigned char RST_28H=0xEF;

// 0xFX ////////////////////////////////////////////////////////////////////////
const unsigned char LDH_A_A8_IND=0xF0;
const unsigned char POP_AF=0xF1;
const unsigned char LD_A_C_IND=0xF2;
const unsigned char DI=0xF3;
const unsigned char PUSH_AF=0xF5;
const unsigned char OR_D8=0xF6;
const unsigned char RST_30H=0xF7;
const unsigned char LD_HL_SP_PLUS_R8=0xF8;
const unsigned char LD_SP_HL=0xF9;
const unsigned char LD_A_A16_IND=0xFA;
const unsigned char EI=0xFB;
const unsigned char CP_D8=0xFE;
const unsigned char RST_38H=0xFF;

////////////////////////////////////////////////////////////////////////////////
// INDIRECT OPCODES ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// 0x0X ////////////////////////////////////////////////////////////////////////
const unsigned char RLC_B=0x00;
const unsigned char RLC_C=0x01;
const unsigned char RLC_D=0x02;
const unsigned char RLC_E=0x03;
const unsigned char RLC_H=0x04;
const unsigned char RLC_L=0x05;
const unsigned char RLC_HL_IND=0x06;
const unsigned char RLC_A=0x07;
const unsigned char RRC_B=0x08;
const unsigned char RRC_C=0x09;
const unsigned char RRC_D=0x0A;
const unsigned char RRC_E=0x0B;
const unsigned char RRC_H=0x0C;
const unsigned char RRC_L=0x0D;
const unsigned char RRC_HL_IND=0x0E;
const unsigned char RRC_A=0x0F;

// 0x1X ////////////////////////////////////////////////////////////////////////
const unsigned char RL_B=0x10;
const unsigned char RL_C=0x11;
const unsigned char RL_D=0x12;
const unsigned char RL_E=0x13;
const unsigned char RL_H=0x14;
const unsigned char RL_L=0x15;
const unsigned char RL_HL_IND=0x16;
const unsigned char RL_A=0x17;
const unsigned char RR_B=0x18;
const unsigned char RR_C=0x19;
const unsigned char RR_D=0x1A;
const unsigned char RR_E=0x1B;
const unsigned char RR_H=0x1C;
const unsigned char RR_L=0x1D;
const unsigned char RR_HL_IND=0x1E;
const unsigned char RR_A=0x1F;

// 0x2X ////////////////////////////////////////////////////////////////////////
const unsigned char SLA_B=0x20;
const unsigned char SLA_C=0x21;
const unsigned char SLA_D=0x22;
const unsigned char SLA_E=0x23;
const unsigned char SLA_H=0x24;
const unsigned char SLA_L=0x25;
const unsigned char SLA_HL_IND=0x26;
const unsigned char SLA_A=0x27;
const unsigned char SRA_B=0x28;
const unsigned char SRA_C=0x29;
const unsigned char SRA_D=0x2A;
const unsigned char SRA_E=0x2B;
const unsigned char SRA_H=0x2C;
const unsigned char SRA_L=0x2D;
const unsigned char SRA_HL_IND=0x2E;
const unsigned char SRA_A=0x2F;

// 0x3X ////////////////////////////////////////////////////////////////////////
const unsigned char SWAP_B=0x30;
const unsigned char SWAP_C=0x31;
const unsigned char SWAP_D=0x32;
const unsigned char SWAP_E=0x33;
const unsigned char SWAP_H=0x34;
const unsigned char SWAP_L=0x35;
const unsigned char SWAP_HL_IND=0x36;
const unsigned char SWAP_A=0x37;
const unsigned char SRL_B=0x38;
const unsigned char SRL_C=0x39;
const unsigned char SRL_D=0x3A;
const unsigned char SRL_E=0x3B;
const unsigned char SRL_H=0x3C;
const unsigned char SRL_L=0x3D;
const unsigned char SRL_HL_IND=0x3E;
const unsigned char SRL_A=0x3F;

// 0x4X ////////////////////////////////////////////////////////////////////////
const unsigned char BIT_0_B=0x40;
const unsigned char BIT_0_C=0x41;
const unsigned char BIT_0_D=0x42;
const unsigned char BIT_0_E=0x43;
const unsigned char BIT_0_H=0x44;
const unsigned char BIT_0_L=0x45;
const unsigned char BIT_0_HL_IND=0x46;
const unsigned char BIT_0_A=0x47;
const unsigned char BIT_1_B=0x48;
const unsigned char BIT_1_C=0x49;
const unsigned char BIT_1_D=0x4A;
const unsigned char BIT_1_E=0x4B;
const unsigned char BIT_1_H=0x4C;
const unsigned char BIT_1_L=0x4D;
const unsigned char BIT_1_HL_IND=0x4E;
const unsigned char BIT_1_A=0x4F;

// 0x5X ////////////////////////////////////////////////////////////////////////
const unsigned char BIT_2_B=0x50;
const unsigned char BIT_2_C=0x51;
const unsigned char BIT_2_D=0x52;
const unsigned char BIT_2_E=0x53;
const unsigned char BIT_2_H=0x54;
const unsigned char BIT_2_L=0x55;
const unsigned char BIT_2_HL_IND=0x56;
const unsigned char BIT_2_A=0x57;
const unsigned char BIT_3_B=0x58;
const unsigned char BIT_3_C=0x59;
const unsigned char BIT_3_D=0x5A;
const unsigned char BIT_3_E=0x5B;
const unsigned char BIT_3_H=0x5C;
const unsigned char BIT_3_L=0x5D;
const unsigned char BIT_3_HL_IND=0x5E;
const unsigned char BIT_3_A=0x5F;

// 0x6X ////////////////////////////////////////////////////////////////////////
const unsigned char BIT_4_B=0x60;
const unsigned char BIT_4_C=0x61;
const unsigned char BIT_4_D=0x62;
const unsigned char BIT_4_E=0x63;
const unsigned char BIT_4_H=0x64;
const unsigned char BIT_4_L=0x65;
const unsigned char BIT_4_HL_IND=0x66;
const unsigned char BIT_4_A=0x67;
const unsigned char BIT_5_B=0x68;
const unsigned char BIT_5_C=0x69;
const unsigned char BIT_5_D=0x6A;
const unsigned char BIT_5_E=0x6B;
const unsigned char BIT_5_H=0x6C;
const unsigned char BIT_5_L=0x6D;
const unsigned char BIT_5_HL_IND=0x6E;
const unsigned char BIT_5_A=0x6F;

// 0x7X ////////////////////////////////////////////////////////////////////////
const unsigned char BIT_6_B=0x70;
const unsigned char BIT_6_C=0x71;
const unsigned char BIT_6_D=0x72;
const unsigned char BIT_6_E=0x73;
const unsigned char BIT_6_H=0x74;
const unsigned char BIT_6_L=0x75;
const unsigned char BIT_6_HL_IND=0x76;
const unsigned char BIT_6_A=0x77;
const unsigned char BIT_7_B=0x78;
const unsigned char BIT_7_C=0x79;
const unsigned char BIT_7_D=0x7A;
const unsigned char BIT_7_E=0x7B;
const unsigned char BIT_7_H=0x7C;
const unsigned char BIT_7_L=0x7D;
const unsigned char BIT_7_HL_IND=0x7E;
const unsigned char BIT_7_A=0x7F;

// 0x8X ////////////////////////////////////////////////////////////////////////
const unsigned char RES_0_B=0x80;
const unsigned char RES_0_C=0x81;
const unsigned char RES_0_D=0x82;
const unsigned char RES_0_E=0x83;
const unsigned char RES_0_H=0x84;
const unsigned char RES_0_L=0x85;
const unsigned char RES_0_HL_IND=0x86;
const unsigned char RES_0_A=0x87;
const unsigned char RES_1_B=0x88;
const unsigned char RES_1_C=0x89;
const unsigned char RES_1_D=0x8A;
const unsigned char RES_1_E=0x8B;
const unsigned char RES_1_H=0x8C;
const unsigned char RES_1_L=0x8D;
const unsigned char RES_1_HL_IND=0x8E;
const unsigned char RES_1_A=0x8F;

// 0x9X ////////////////////////////////////////////////////////////////////////
const unsigned char RES_2_B=0x90;
const unsigned char RES_2_C=0x91;
const unsigned char RES_2_D=0x92;
const unsigned char RES_2_E=0x93;
const unsigned char RES_2_H=0x94;
const unsigned char RES_2_L=0x95;
const unsigned char RES_2_HL_IND=0x96;
const unsigned char RES_2_A=0x97;
const unsigned char RES_3_B=0x98;
const unsigned char RES_3_C=0x99;
const unsigned char RES_3_D=0x9A;
const unsigned char RES_3_E=0x9B;
const unsigned char RES_3_H=0x9C;
const unsigned char RES_3_L=0x9D;
const unsigned char RES_3_HL_IND=0x9E;
const unsigned char RES_3_A=0x9F;

// 0xAX ////////////////////////////////////////////////////////////////////////
const unsigned char RES_4_B=0xA0;
const unsigned char RES_4_C=0xA1;
const unsigned char RES_4_D=0xA2;
const unsigned char RES_4_E=0xA3;
const unsigned char RES_4_H=0xA4;
const unsigned char RES_4_L=0xA5;
const unsigned char RES_4_HL_IND=0xA6;
const unsigned char RES_4_A=0xA7;
const unsigned char RES_5_B=0xA8;
const unsigned char RES_5_C=0xA9;
const unsigned char RES_5_D=0xAA;
const unsigned char RES_5_E=0xAB;
const unsigned char RES_5_H=0xAC;
const unsigned char RES_5_L=0xAD;
const unsigned char RES_5_HL_IND=0xAE;
const unsigned char RES_5_A=0xAF;

// 0xBX ////////////////////////////////////////////////////////////////////////
const unsigned char RES_6_B=0xB0;
const unsigned char RES_6_C=0xB1;
const unsigned char RES_6_D=0xB2;
const unsigned char RES_6_E=0xB3;
const unsigned char RES_6_H=0xB4;
const unsigned char RES_6_L=0xB5;
const unsigned char RES_6_HL_IND=0xB6;
const unsigned char RES_6_A=0xB7;
const unsigned char RES_7_B=0xB8;
const unsigned char RES_7_C=0xB9;
const unsigned char RES_7_D=0xBA;
const unsigned char RES_7_E=0xBB;
const unsigned char RES_7_H=0xBC;
const unsigned char RES_7_L=0xBD;
const unsigned char RES_7_HL_IND=0xBE;
const unsigned char RES_7_A=0xBF;

// 0xCX ////////////////////////////////////////////////////////////////////////
const unsigned char SET_0_B=0xC0;
const unsigned char SET_0_C=0xC1;
const unsigned char SET_0_D=0xC2;
const unsigned char SET_0_E=0xC3;
const unsigned char SET_0_H=0xC4;
const unsigned char SET_0_L=0xC5;
const unsigned char SET_0_HL_IND=0xC6;
const unsigned char SET_0_A=0xC7;
const unsigned char SET_1_B=0xC8;
const unsigned char SET_1_C=0xC9;
const unsigned char SET_1_D=0xCA;
const unsigned char SET_1_E=0xCB;
const unsigned char SET_1_H=0xCC;
const unsigned char SET_1_L=0xCD;
const unsigned char SET_1_HL_IND=0xCE;
const unsigned char SET_1_A=0xCF;

// 0xDX ////////////////////////////////////////////////////////////////////////
const unsigned char SET_2_B=0xD0;
const unsigned char SET_2_C=0xD1;
const unsigned char SET_2_D=0xD2;
const unsigned char SET_2_E=0xD3;
const unsigned char SET_2_H=0xD4;
const unsigned char SET_2_L=0xD5;
const unsigned char SET_2_HL_IND=0xD6;
const unsigned char SET_2_A=0xD7;
const unsigned char SET_3_B=0xD8;
const unsigned char SET_3_C=0xD9;
const unsigned char SET_3_D=0xDA;
const unsigned char SET_3_E=0xDB;
const unsigned char SET_3_H=0xDC;
const unsigned char SET_3_L=0xDD;
const unsigned char SET_3_HL_IND=0xDE;
const unsigned char SET_3_A=0xDF;

// 0xEX ////////////////////////////////////////////////////////////////////////
const unsigned char SET_4_B=0xE0;
const unsigned char SET_4_C=0xE1;
const unsigned char SET_4_D=0xE2;
const unsigned char SET_4_E=0xE3;
const unsigned char SET_4_H=0xE4;
const unsigned char SET_4_L=0xE5;
const unsigned char SET_4_HL_IND=0xE6;
const unsigned char SET_4_A=0xE7;
const unsigned char SET_5_B=0xE8;
const unsigned char SET_5_C=0xE9;
const unsigned char SET_5_D=0xEA;
const unsigned char SET_5_E=0xEB;
const unsigned char SET_5_H=0xEC;
const unsigned char SET_5_L=0xED;
const unsigned char SET_5_HL_IND=0xEE;
const unsigned char SET_5_A=0xEF;

// 0xFX ////////////////////////////////////////////////////////////////////////
const unsigned char SET_6_B=0xF0;
const unsigned char SET_6_C=0xF1;
const unsigned char SET_6_D=0xF2;
const unsigned char SET_6_E=0xF3;
const unsigned char SET_6_H=0xF4;
const unsigned char SET_6_L=0xF5;
const unsigned char SET_6_HL_IND=0xF6;
const unsigned char SET_6_A=0xF7;
const unsigned char SET_7_B=0xF8;
const unsigned char SET_7_C=0xF9;
const unsigned char SET_7_D=0xFA;
const unsigned char SET_7_E=0xFB;
const unsigned char SET_7_H=0xFC;
const unsigned char SET_7_L=0xFD;
const unsigned char SET_7_HL_IND=0xFE;
const unsigned char SET_7_A=0xFF;
