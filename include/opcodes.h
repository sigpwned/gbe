#ifndef __OPCODES_H_INCLUDED__
#define __OPCODES_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// DIRECT OPCODES //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// 0x0X ////////////////////////////////////////////////////////////////////////
#define NOP ((unsigned char) 0x00)
#define LD_BC_D16 ((unsigned char) 0x01)
#define LD_BC_IND_A ((unsigned char) 0x02)
#define INC_BC ((unsigned char) 0x03)
#define INC_B ((unsigned char) 0x04)
#define DEC_B ((unsigned char) 0x05)
#define LD_B_D8 ((unsigned char) 0x06)
#define RLCA ((unsigned char) 0x07)
#define LD_A16_IND_SP ((unsigned char) 0x08)
#define ADD_HL_BC ((unsigned char) 0x09)
#define LD_A_BC_IND ((unsigned char) 0x0A)
#define DEC_BC ((unsigned char) 0x0B)
#define INC_C ((unsigned char) 0x0C)
#define DEC_C ((unsigned char) 0x0D)
#define LD_C_D8 ((unsigned char) 0x0E)
#define RRCA ((unsigned char) 0x0F)

// 0x1X ////////////////////////////////////////////////////////////////////////
#define STOP ((unsigned char) 0x10)
#define LD_DE_D16 ((unsigned char) 0x11)
#define LD_DE_IND_A ((unsigned char) 0x12)
#define INC_DE ((unsigned char) 0x13)
#define INC_D ((unsigned char) 0x14)
#define DEC_D ((unsigned char) 0x15)
#define LD_D_D8 ((unsigned char) 0x16)
#define RLA ((unsigned char) 0x17)
#define JR_R8 ((unsigned char) 0x18)
#define ADD_HL_DE ((unsigned char) 0x19)
#define LD_A_DE_IND ((unsigned char) 0x1A)
#define DEC_DE ((unsigned char) 0x1B)
#define INC_E ((unsigned char) 0x1C)
#define DEC_E ((unsigned char) 0x1D)
#define LD_E_D8 ((unsigned char) 0x1E)
#define RRA ((unsigned char) 0x1F)

// 0x2X ////////////////////////////////////////////////////////////////////////
#define JR_NZ_R8 ((unsigned char) 0x20)
#define LD_HL_D16 ((unsigned char) 0x21)
#define LD_HL_IND_PLUS_A ((unsigned char) 0x22)
#define INC_HL ((unsigned char) 0x23)
#define INC_H ((unsigned char) 0x24)
#define DEC_H ((unsigned char) 0x25)
#define LD_H_D8 ((unsigned char) 0x26)
#define DAA ((unsigned char) 0x27)
#define JR_Z_R8 ((unsigned char) 0x28)
#define ADD_HL_HL ((unsigned char) 0x29)
#define LD_A_HL_IND_PLUS ((unsigned char) 0x2A)
#define DEC_HL ((unsigned char) 0x2B)
#define INC_L ((unsigned char) 0x2C)
#define DEC_L ((unsigned char) 0x2D)
#define LD_L_D8 ((unsigned char) 0x2E)
#define CPL ((unsigned char) 0x2F)

// 0x3X ////////////////////////////////////////////////////////////////////////
#define JR_NC_R8 ((unsigned char) 0x30)
#define LD_SP_D16 ((unsigned char) 0x31)
#define LD_HL_IND_MINUS_A ((unsigned char) 0x32)
#define INC_SP ((unsigned char) 0x33)
#define INC_HL_IND ((unsigned char) 0x34)
#define DEC_HL_IND ((unsigned char) 0x35)
#define LD_HL_IND_D8 ((unsigned char) 0x36)
#define SCF ((unsigned char) 0x37)
#define JR_C_R8 ((unsigned char) 0x38)
#define ADD_HL_SP ((unsigned char) 0x39)
#define LD_A_HL_IND_MINUS ((unsigned char) 0x3A)
#define DEC_SP ((unsigned char) 0x3B)
#define INC_A ((unsigned char) 0x3C)
#define DEC_A ((unsigned char) 0x3D)
#define LD_A_D8 ((unsigned char) 0x3E)
#define CCF ((unsigned char) 0x3F)

// 0x4X ////////////////////////////////////////////////////////////////////////
#define LD_B_B ((unsigned char) 0x40)
#define LD_B_C ((unsigned char) 0x41)
#define LD_B_D ((unsigned char) 0x42)
#define LD_B_E ((unsigned char) 0x43)
#define LD_B_H ((unsigned char) 0x44)
#define LD_B_L ((unsigned char) 0x45)
#define LD_B_HL_IND ((unsigned char) 0x46)
#define LD_B_A ((unsigned char) 0x47)
#define LD_C_B ((unsigned char) 0x48)
#define LD_C_C ((unsigned char) 0x49)
#define LD_C_D ((unsigned char) 0x4A)
#define LD_C_E ((unsigned char) 0x4B)
#define LD_C_H ((unsigned char) 0x4C)
#define LD_C_L ((unsigned char) 0x4D)
#define LD_C_HL_IND ((unsigned char) 0x4E)
#define LD_C_A ((unsigned char) 0x4F)

// 0x5X ////////////////////////////////////////////////////////////////////////
#define LD_D_B ((unsigned char) 0x50)
#define LD_D_C ((unsigned char) 0x51)
#define LD_D_D ((unsigned char) 0x52)
#define LD_D_E ((unsigned char) 0x53)
#define LD_D_H ((unsigned char) 0x54)
#define LD_D_L ((unsigned char) 0x55)
#define LD_D_HL_IND ((unsigned char) 0x56)
#define LD_D_A ((unsigned char) 0x57)
#define LD_E_B ((unsigned char) 0x58)
#define LD_E_C ((unsigned char) 0x59)
#define LD_E_D ((unsigned char) 0x5A)
#define LD_E_E ((unsigned char) 0x5B)
#define LD_E_H ((unsigned char) 0x5C)
#define LD_E_L ((unsigned char) 0x5D)
#define LD_E_HL_IND ((unsigned char) 0x5E)
#define LD_E_A ((unsigned char) 0x5F)

// 0x6X ////////////////////////////////////////////////////////////////////////
#define LD_H_B ((unsigned char) 0x60)
#define LD_H_C ((unsigned char) 0x61)
#define LD_H_D ((unsigned char) 0x62)
#define LD_H_E ((unsigned char) 0x63)
#define LD_H_H ((unsigned char) 0x64)
#define LD_H_L ((unsigned char) 0x65)
#define LD_H_HL_IND ((unsigned char) 0x66)
#define LD_H_A ((unsigned char) 0x67)
#define LD_L_B ((unsigned char) 0x68)
#define LD_L_C ((unsigned char) 0x69)
#define LD_L_D ((unsigned char) 0x6A)
#define LD_L_E ((unsigned char) 0x6B)
#define LD_L_H ((unsigned char) 0x6C)
#define LD_L_L ((unsigned char) 0x6D)
#define LD_L_HL_IND ((unsigned char) 0x6E)
#define LD_L_A ((unsigned char) 0x6F)

// 0x7X ////////////////////////////////////////////////////////////////////////
#define LD_HL_IND_B ((unsigned char) 0x70)
#define LD_HL_IND_C ((unsigned char) 0x71)
#define LD_HL_IND_D ((unsigned char) 0x72)
#define LD_HL_IND_E ((unsigned char) 0x73)
#define LD_HL_IND_H ((unsigned char) 0x74)
#define LD_HL_IND_L ((unsigned char) 0x75)
#define HALT ((unsigned char) 0x76)
#define LD_HL_IND_A ((unsigned char) 0x77)
#define LD_A_B ((unsigned char) 0x78)
#define LD_A_C ((unsigned char) 0x79)
#define LD_A_D ((unsigned char) 0x7A)
#define LD_A_E ((unsigned char) 0x7B)
#define LD_A_H ((unsigned char) 0x7C)
#define LD_A_L ((unsigned char) 0x7D)
#define LD_A_HL_IND ((unsigned char) 0x7E)
#define LD_A_A ((unsigned char) 0x7F)

// 0x8X ////////////////////////////////////////////////////////////////////////
#define ADD_A_B ((unsigned char) 0x80)
#define ADD_A_C ((unsigned char) 0x81)
#define ADD_A_D ((unsigned char) 0x82)
#define ADD_A_E ((unsigned char) 0x83)
#define ADD_A_H ((unsigned char) 0x84)
#define ADD_A_L ((unsigned char) 0x85)
#define ADD_A_HL_IND ((unsigned char) 0x86)
#define ADD_A_A ((unsigned char) 0x87)
#define ADC_A_B ((unsigned char) 0x88)
#define ADC_A_C ((unsigned char) 0x89)
#define ADC_A_D ((unsigned char) 0x8A)
#define ADC_A_E ((unsigned char) 0x8B)
#define ADC_A_H ((unsigned char) 0x8C)
#define ADC_A_L ((unsigned char) 0x8D)
#define ADC_A_HL_IND ((unsigned char) 0x8E)
#define ADC_A_A ((unsigned char) 0x8F)

// 0x9X ////////////////////////////////////////////////////////////////////////
#define SUB_B ((unsigned char) 0x90)
#define SUB_C ((unsigned char) 0x91)
#define SUB_D ((unsigned char) 0x92)
#define SUB_E ((unsigned char) 0x93)
#define SUB_H ((unsigned char) 0x94)
#define SUB_L ((unsigned char) 0x95)
#define SUB_HL_IND ((unsigned char) 0x96)
#define SUB_A ((unsigned char) 0x97)
#define SBC_A_B ((unsigned char) 0x98)
#define SBC_A_C ((unsigned char) 0x99)
#define SBC_A_D ((unsigned char) 0x9A)
#define SBC_A_E ((unsigned char) 0x9B)
#define SBC_A_H ((unsigned char) 0x9C)
#define SBC_A_L ((unsigned char) 0x9D)
#define SBC_A_HL_IND ((unsigned char) 0x9E)
#define SBC_A_A ((unsigned char) 0x9F)

// 0xAX ////////////////////////////////////////////////////////////////////////
#define AND_B ((unsigned char) 0xA0)
#define AND_C ((unsigned char) 0xA1)
#define AND_D ((unsigned char) 0xA2)
#define AND_E ((unsigned char) 0xA3)
#define AND_H ((unsigned char) 0xA4)
#define AND_L ((unsigned char) 0xA5)
#define AND_HL_IND ((unsigned char) 0xA6)
#define AND_A ((unsigned char) 0xA7)
#define XOR_A_B ((unsigned char) 0xA8)
#define XOR_A_C ((unsigned char) 0xA9)
#define XOR_A_D ((unsigned char) 0xAA)
#define XOR_A_E ((unsigned char) 0xAB)
#define XOR_A_H ((unsigned char) 0xAC)
#define XOR_A_L ((unsigned char) 0xAD)
#define XOR_A_HL_IND ((unsigned char) 0xAE)
#define XOR_A_A ((unsigned char) 0xAF)

// 0xBX ////////////////////////////////////////////////////////////////////////
#define OR_B ((unsigned char) 0xB0)
#define OR_C ((unsigned char) 0xB1)
#define OR_D ((unsigned char) 0xB2)
#define OR_E ((unsigned char) 0xB3)
#define OR_H ((unsigned char) 0xB4)
#define OR_L ((unsigned char) 0xB5)
#define OR_HL_IND ((unsigned char) 0xB6)
#define OR_A ((unsigned char) 0xB7)
#define CP_A_B ((unsigned char) 0xB8)
#define CP_A_C ((unsigned char) 0xB9)
#define CP_A_D ((unsigned char) 0xBA)
#define CP_A_E ((unsigned char) 0xBB)
#define CP_A_H ((unsigned char) 0xBC)
#define CP_A_L ((unsigned char) 0xBD)
#define CP_A_HL_IND ((unsigned char) 0xBE)
#define CP_A_A ((unsigned char) 0xBF)

// 0xCX ////////////////////////////////////////////////////////////////////////
#define RET_NZ ((unsigned char) 0xC0)
#define POP_BC ((unsigned char) 0xC1)
#define JP_NZ_A16 ((unsigned char) 0xC2)
#define JP_A16 ((unsigned char) 0xC3)
#define CALL_NZ_A16 ((unsigned char) 0xC4)
#define PUSH_BC ((unsigned char) 0xC5)
#define ADD_A_D8 ((unsigned char) 0xC6)
#define RST_00H ((unsigned char) 0xC7)
#define RET_Z ((unsigned char) 0xC8)
#define RET ((unsigned char) 0xC9)
#define JP_Z_A16 ((unsigned char) 0xCA)
#define PREFIX_CB ((unsigned char) 0xCB)
#define CALL_Z_A16 ((unsigned char) 0xCC)
#define CALL_A16 ((unsigned char) 0xCD)
#define ADC_A_D8 ((unsigned char) 0xCE)
#define RST_08H ((unsigned char) 0xCF)

// 0xDX ////////////////////////////////////////////////////////////////////////
#define RET_NC ((unsigned char) 0xD0)
#define POP_DE ((unsigned char) 0xD1)
#define JP_NC_A16 ((unsigned char) 0xD2)
#define CALL_NC_A16 ((unsigned char) 0xD4)
#define PUSH_DE ((unsigned char) 0xD5)
#define SUB_D8 ((unsigned char) 0xD6)
#define RST_10H ((unsigned char) 0xD7)
#define RET_C ((unsigned char) 0xD8)
#define RETI ((unsigned char) 0xD9)
#define JP_C_A16 ((unsigned char) 0xDA)
#define CALL_C_A16 ((unsigned char) 0xDC)
#define SBC_A_D8 ((unsigned char) 0xDE)
#define RST_18H ((unsigned char) 0xDF)

// 0xEX ////////////////////////////////////////////////////////////////////////
#define LDH_A8_IND_A ((unsigned char) 0xE0)
#define POP_HL ((unsigned char) 0xE1)
#define LD_C_IND_A ((unsigned char) 0xE2)
#define PUSH_HL ((unsigned char) 0xE5)
#define AND_D8 ((unsigned char) 0xE6)
#define RST_20H ((unsigned char) 0xE7)
#define ADD_SP_R8 ((unsigned char) 0xE8)
#define JP_HL_IND ((unsigned char) 0xE9)
#define LD_A16_IND_A ((unsigned char) 0xEA)
#define XOR_D8 ((unsigned char) 0xEE)
#define RST_28H ((unsigned char) 0xEF)

// 0xFX ////////////////////////////////////////////////////////////////////////
#define LDH_A_A8_IND ((unsigned char) 0xF0)
#define POP_AF ((unsigned char) 0xF1)
#define LD_A_C_IND ((unsigned char) 0xF2)
#define DI ((unsigned char) 0xF3)
#define PUSH_AF ((unsigned char) 0xF5)
#define OR_D8 ((unsigned char) 0xF6)
#define RST_30H ((unsigned char) 0xF7)
#define LD_HL_SP_PLUS_R8 ((unsigned char) 0xF8)
#define LD_SP_HL ((unsigned char) 0xF9)
#define LD_A_A16_IND ((unsigned char) 0xFA)
#define EI ((unsigned char) 0xFB)
#define CP_D8 ((unsigned char) 0xFE)
#define RST_38H ((unsigned char) 0xFF)

////////////////////////////////////////////////////////////////////////////////
// INDIRECT OPCODES ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// 0x0X ////////////////////////////////////////////////////////////////////////
#define RLC_B ((unsigned char) 0x00)
#define RLC_C ((unsigned char) 0x01)
#define RLC_D ((unsigned char) 0x02)
#define RLC_E ((unsigned char) 0x03)
#define RLC_H ((unsigned char) 0x04)
#define RLC_L ((unsigned char) 0x05)
#define RLC_HL_IND ((unsigned char) 0x06)
#define RLC_A ((unsigned char) 0x07)
#define RRC_B ((unsigned char) 0x08)
#define RRC_C ((unsigned char) 0x09)
#define RRC_D ((unsigned char) 0x0A)
#define RRC_E ((unsigned char) 0x0B)
#define RRC_H ((unsigned char) 0x0C)
#define RRC_L ((unsigned char) 0x0D)
#define RRC_HL_IND ((unsigned char) 0x0E)
#define RRC_A ((unsigned char) 0x0F)

// 0x1X ////////////////////////////////////////////////////////////////////////
#define RL_B ((unsigned char) 0x10)
#define RL_C ((unsigned char) 0x11)
#define RL_D ((unsigned char) 0x12)
#define RL_E ((unsigned char) 0x13)
#define RL_H ((unsigned char) 0x14)
#define RL_L ((unsigned char) 0x15)
#define RL_HL_IND ((unsigned char) 0x16)
#define RL_A ((unsigned char) 0x17)
#define RR_B ((unsigned char) 0x18)
#define RR_C ((unsigned char) 0x19)
#define RR_D ((unsigned char) 0x1A)
#define RR_E ((unsigned char) 0x1B)
#define RR_H ((unsigned char) 0x1C)
#define RR_L ((unsigned char) 0x1D)
#define RR_HL_IND ((unsigned char) 0x1E)
#define RR_A ((unsigned char) 0x1F)

// 0x2X ////////////////////////////////////////////////////////////////////////
#define SLA_B ((unsigned char) 0x20)
#define SLA_C ((unsigned char) 0x21)
#define SLA_D ((unsigned char) 0x22)
#define SLA_E ((unsigned char) 0x23)
#define SLA_H ((unsigned char) 0x24)
#define SLA_L ((unsigned char) 0x25)
#define SLA_HL_IND ((unsigned char) 0x26)
#define SLA_A ((unsigned char) 0x27)
#define SRA_B ((unsigned char) 0x28)
#define SRA_C ((unsigned char) 0x29)
#define SRA_D ((unsigned char) 0x2A)
#define SRA_E ((unsigned char) 0x2B)
#define SRA_H ((unsigned char) 0x2C)
#define SRA_L ((unsigned char) 0x2D)
#define SRA_HL_IND ((unsigned char) 0x2E)
#define SRA_A ((unsigned char) 0x2F)

// 0x3X ////////////////////////////////////////////////////////////////////////
#define SWAP_B ((unsigned char) 0x30)
#define SWAP_C ((unsigned char) 0x31)
#define SWAP_D ((unsigned char) 0x32)
#define SWAP_E ((unsigned char) 0x33)
#define SWAP_H ((unsigned char) 0x34)
#define SWAP_L ((unsigned char) 0x35)
#define SWAP_HL_IND ((unsigned char) 0x36)
#define SWAP_A ((unsigned char) 0x37)
#define SRL_B ((unsigned char) 0x38)
#define SRL_C ((unsigned char) 0x39)
#define SRL_D ((unsigned char) 0x3A)
#define SRL_E ((unsigned char) 0x3B)
#define SRL_H ((unsigned char) 0x3C)
#define SRL_L ((unsigned char) 0x3D)
#define SRL_HL_IND ((unsigned char) 0x3E)
#define SRL_A ((unsigned char) 0x3F)

// 0x4X ////////////////////////////////////////////////////////////////////////
#define BIT_0_B ((unsigned char) 0x40)
#define BIT_0_C ((unsigned char) 0x41)
#define BIT_0_D ((unsigned char) 0x42)
#define BIT_0_E ((unsigned char) 0x43)
#define BIT_0_H ((unsigned char) 0x44)
#define BIT_0_L ((unsigned char) 0x45)
#define BIT_0_HL_IND ((unsigned char) 0x46)
#define BIT_0_A ((unsigned char) 0x47)
#define BIT_1_B ((unsigned char) 0x48)
#define BIT_1_C ((unsigned char) 0x49)
#define BIT_1_D ((unsigned char) 0x4A)
#define BIT_1_E ((unsigned char) 0x4B)
#define BIT_1_H ((unsigned char) 0x4C)
#define BIT_1_L ((unsigned char) 0x4D)
#define BIT_1_HL_IND ((unsigned char) 0x4E)
#define BIT_1_A ((unsigned char) 0x4F)

// 0x5X ////////////////////////////////////////////////////////////////////////
#define BIT_2_B ((unsigned char) 0x50)
#define BIT_2_C ((unsigned char) 0x51)
#define BIT_2_D ((unsigned char) 0x52)
#define BIT_2_E ((unsigned char) 0x53)
#define BIT_2_H ((unsigned char) 0x54)
#define BIT_2_L ((unsigned char) 0x55)
#define BIT_2_HL_IND ((unsigned char) 0x56)
#define BIT_2_A ((unsigned char) 0x57)
#define BIT_3_B ((unsigned char) 0x58)
#define BIT_3_C ((unsigned char) 0x59)
#define BIT_3_D ((unsigned char) 0x5A)
#define BIT_3_E ((unsigned char) 0x5B)
#define BIT_3_H ((unsigned char) 0x5C)
#define BIT_3_L ((unsigned char) 0x5D)
#define BIT_3_HL_IND ((unsigned char) 0x5E)
#define BIT_3_A ((unsigned char) 0x5F)

// 0x6X ////////////////////////////////////////////////////////////////////////
#define BIT_4_B ((unsigned char) 0x60)
#define BIT_4_C ((unsigned char) 0x61)
#define BIT_4_D ((unsigned char) 0x62)
#define BIT_4_E ((unsigned char) 0x63)
#define BIT_4_H ((unsigned char) 0x64)
#define BIT_4_L ((unsigned char) 0x65)
#define BIT_4_HL_IND ((unsigned char) 0x66)
#define BIT_4_A ((unsigned char) 0x67)
#define BIT_5_B ((unsigned char) 0x68)
#define BIT_5_C ((unsigned char) 0x69)
#define BIT_5_D ((unsigned char) 0x6A)
#define BIT_5_E ((unsigned char) 0x6B)
#define BIT_5_H ((unsigned char) 0x6C)
#define BIT_5_L ((unsigned char) 0x6D)
#define BIT_5_HL_IND ((unsigned char) 0x6E)
#define BIT_5_A ((unsigned char) 0x6F)

// 0x7X ////////////////////////////////////////////////////////////////////////
#define BIT_6_B ((unsigned char) 0x70)
#define BIT_6_C ((unsigned char) 0x71)
#define BIT_6_D ((unsigned char) 0x72)
#define BIT_6_E ((unsigned char) 0x73)
#define BIT_6_H ((unsigned char) 0x74)
#define BIT_6_L ((unsigned char) 0x75)
#define BIT_6_HL_IND ((unsigned char) 0x76)
#define BIT_6_A ((unsigned char) 0x77)
#define BIT_7_B ((unsigned char) 0x78)
#define BIT_7_C ((unsigned char) 0x79)
#define BIT_7_D ((unsigned char) 0x7A)
#define BIT_7_E ((unsigned char) 0x7B)
#define BIT_7_H ((unsigned char) 0x7C)
#define BIT_7_L ((unsigned char) 0x7D)
#define BIT_7_HL_IND ((unsigned char) 0x7E)
#define BIT_7_A ((unsigned char) 0x7F)

// 0x8X ////////////////////////////////////////////////////////////////////////
#define RES_0_B ((unsigned char) 0x80)
#define RES_0_C ((unsigned char) 0x81)
#define RES_0_D ((unsigned char) 0x82)
#define RES_0_E ((unsigned char) 0x83)
#define RES_0_H ((unsigned char) 0x84)
#define RES_0_L ((unsigned char) 0x85)
#define RES_0_HL_IND ((unsigned char) 0x86)
#define RES_0_A ((unsigned char) 0x87)
#define RES_1_B ((unsigned char) 0x88)
#define RES_1_C ((unsigned char) 0x89)
#define RES_1_D ((unsigned char) 0x8A)
#define RES_1_E ((unsigned char) 0x8B)
#define RES_1_H ((unsigned char) 0x8C)
#define RES_1_L ((unsigned char) 0x8D)
#define RES_1_HL_IND ((unsigned char) 0x8E)
#define RES_1_A ((unsigned char) 0x8F)

// 0x9X ////////////////////////////////////////////////////////////////////////
#define RES_2_B ((unsigned char) 0x90)
#define RES_2_C ((unsigned char) 0x91)
#define RES_2_D ((unsigned char) 0x92)
#define RES_2_E ((unsigned char) 0x93)
#define RES_2_H ((unsigned char) 0x94)
#define RES_2_L ((unsigned char) 0x95)
#define RES_2_HL_IND ((unsigned char) 0x96)
#define RES_2_A ((unsigned char) 0x97)
#define RES_3_B ((unsigned char) 0x98)
#define RES_3_C ((unsigned char) 0x99)
#define RES_3_D ((unsigned char) 0x9A)
#define RES_3_E ((unsigned char) 0x9B)
#define RES_3_H ((unsigned char) 0x9C)
#define RES_3_L ((unsigned char) 0x9D)
#define RES_3_HL_IND ((unsigned char) 0x9E)
#define RES_3_A ((unsigned char) 0x9F)

// 0xAX ////////////////////////////////////////////////////////////////////////
#define RES_4_B ((unsigned char) 0xA0)
#define RES_4_C ((unsigned char) 0xA1)
#define RES_4_D ((unsigned char) 0xA2)
#define RES_4_E ((unsigned char) 0xA3)
#define RES_4_H ((unsigned char) 0xA4)
#define RES_4_L ((unsigned char) 0xA5)
#define RES_4_HL_IND ((unsigned char) 0xA6)
#define RES_4_A ((unsigned char) 0xA7)
#define RES_5_B ((unsigned char) 0xA8)
#define RES_5_C ((unsigned char) 0xA9)
#define RES_5_D ((unsigned char) 0xAA)
#define RES_5_E ((unsigned char) 0xAB)
#define RES_5_H ((unsigned char) 0xAC)
#define RES_5_L ((unsigned char) 0xAD)
#define RES_5_HL_IND ((unsigned char) 0xAE)
#define RES_5_A ((unsigned char) 0xAF)

// 0xBX ////////////////////////////////////////////////////////////////////////
#define RES_6_B ((unsigned char) 0xB0)
#define RES_6_C ((unsigned char) 0xB1)
#define RES_6_D ((unsigned char) 0xB2)
#define RES_6_E ((unsigned char) 0xB3)
#define RES_6_H ((unsigned char) 0xB4)
#define RES_6_L ((unsigned char) 0xB5)
#define RES_6_HL_IND ((unsigned char) 0xB6)
#define RES_6_A ((unsigned char) 0xB7)
#define RES_7_B ((unsigned char) 0xB8)
#define RES_7_C ((unsigned char) 0xB9)
#define RES_7_D ((unsigned char) 0xBA)
#define RES_7_E ((unsigned char) 0xBB)
#define RES_7_H ((unsigned char) 0xBC)
#define RES_7_L ((unsigned char) 0xBD)
#define RES_7_HL_IND ((unsigned char) 0xBE)
#define RES_7_A ((unsigned char) 0xBF)

// 0xCX ////////////////////////////////////////////////////////////////////////
#define SET_0_B ((unsigned char) 0xC0)
#define SET_0_C ((unsigned char) 0xC1)
#define SET_0_D ((unsigned char) 0xC2)
#define SET_0_E ((unsigned char) 0xC3)
#define SET_0_H ((unsigned char) 0xC4)
#define SET_0_L ((unsigned char) 0xC5)
#define SET_0_HL_IND ((unsigned char) 0xC6)
#define SET_0_A ((unsigned char) 0xC7)
#define SET_1_B ((unsigned char) 0xC8)
#define SET_1_C ((unsigned char) 0xC9)
#define SET_1_D ((unsigned char) 0xCA)
#define SET_1_E ((unsigned char) 0xCB)
#define SET_1_H ((unsigned char) 0xCC)
#define SET_1_L ((unsigned char) 0xCD)
#define SET_1_HL_IND ((unsigned char) 0xCE)
#define SET_1_A ((unsigned char) 0xCF)

// 0xDX ////////////////////////////////////////////////////////////////////////
#define SET_2_B ((unsigned char) 0xD0)
#define SET_2_C ((unsigned char) 0xD1)
#define SET_2_D ((unsigned char) 0xD2)
#define SET_2_E ((unsigned char) 0xD3)
#define SET_2_H ((unsigned char) 0xD4)
#define SET_2_L ((unsigned char) 0xD5)
#define SET_2_HL_IND ((unsigned char) 0xD6)
#define SET_2_A ((unsigned char) 0xD7)
#define SET_3_B ((unsigned char) 0xD8)
#define SET_3_C ((unsigned char) 0xD9)
#define SET_3_D ((unsigned char) 0xDA)
#define SET_3_E ((unsigned char) 0xDB)
#define SET_3_H ((unsigned char) 0xDC)
#define SET_3_L ((unsigned char) 0xDD)
#define SET_3_HL_IND ((unsigned char) 0xDE)
#define SET_3_A ((unsigned char) 0xDF)

// 0xEX ////////////////////////////////////////////////////////////////////////
#define SET_4_B ((unsigned char) 0xE0)
#define SET_4_C ((unsigned char) 0xE1)
#define SET_4_D ((unsigned char) 0xE2)
#define SET_4_E ((unsigned char) 0xE3)
#define SET_4_H ((unsigned char) 0xE4)
#define SET_4_L ((unsigned char) 0xE5)
#define SET_4_HL_IND ((unsigned char) 0xE6)
#define SET_4_A ((unsigned char) 0xE7)
#define SET_5_B ((unsigned char) 0xE8)
#define SET_5_C ((unsigned char) 0xE9)
#define SET_5_D ((unsigned char) 0xEA)
#define SET_5_E ((unsigned char) 0xEB)
#define SET_5_H ((unsigned char) 0xEC)
#define SET_5_L ((unsigned char) 0xED)
#define SET_5_HL_IND ((unsigned char) 0xEE)
#define SET_5_A ((unsigned char) 0xEF)

// 0xFX ////////////////////////////////////////////////////////////////////////
#define SET_6_B ((unsigned char) 0xF0)
#define SET_6_C ((unsigned char) 0xF1)
#define SET_6_D ((unsigned char) 0xF2)
#define SET_6_E ((unsigned char) 0xF3)
#define SET_6_H ((unsigned char) 0xF4)
#define SET_6_L ((unsigned char) 0xF5)
#define SET_6_HL_IND ((unsigned char) 0xF6)
#define SET_6_A ((unsigned char) 0xF7)
#define SET_7_B ((unsigned char) 0xF8)
#define SET_7_C ((unsigned char) 0xF9)
#define SET_7_D ((unsigned char) 0xFA)
#define SET_7_E ((unsigned char) 0xFB)
#define SET_7_H ((unsigned char) 0xFC)
#define SET_7_L ((unsigned char) 0xFD)
#define SET_7_HL_IND ((unsigned char) 0xFE)
#define SET_7_A ((unsigned char) 0xFF)

struct opcode {
  const char* name;
  unsigned char cb;
};

struct opcode* opcode_describe(unsigned char opcode);
struct opcode* opcode_cb_describe(unsigned char opcode);

#endif // __OPCODES_H_INCLUDED__
