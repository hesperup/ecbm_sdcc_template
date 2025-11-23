#ifndef _ECBM_REG_H_
#define _ECBM_REG_H_


/* #ifdef __SDCC
#include "keil_compat.h"
#endif */



#if defined(SDCC) || defined(__SDCC)
#define SBIT(name, addr, bit) __sbit __at(addr + bit) name
#define SFR(name, addr) __sfr __at(addr) name
#define SFRX(name, addr) __xdata volatile unsigned char __at(addr) name
#define SFR16(name, addr) __sfr16 __at(((addr + 1U) << 8) | addr) name
#define SFR16E(name, fulladdr) __sfr16 __at(fulladdr) name
#define SFR16LEX(name, addr) __xdata volatile unsigned short __at(addr) name
#define SFR32(name, addr) __sfr32 __at(((addr + 3UL) << 24) | ((addr + 2UL) << 16) | ((addr + 1UL) << 8) | addr) name
#define SFR32E(name, fulladdr) __sfr32 __at(fulladdr) name

#define INTERRUPT(name, vector) void name(void) __interrupt(vector)
#define INTERRUPT_USING(name, vector, regnum) void name(void) __interrupt(vector) __using(regnum)

#ifndef bit
typedef unsigned char bit;
#endif

#define reentrant __reentrant
#define compact
#define small __near
#define large __far
#define data __data
#define bdata
#define idata __idata
#define pdata __pdata
#define xdata __xdata
#define code __code
// NOP () macro support
#define NOP() __asm NOP __endasm
#define interrupt __interrupt
#define using __using
#define _at_ __at
#define _priority_
#define _task_
/** Keil C51
  * http://www.keil.com
 */
#else
#define SBIT(name, addr, bit) sbit name = addr ^ bit
#define SFR(name, addr) sfr name = addr
#define SFRX(name, addr) volatile unsigned char xdata name _at_ addr
#define SFR16(name, addr) sfr16 name = addr
#define SFR16E(name, fulladdr) /* not supported */
#define SFR16LEX(name, addr)   /* not supported */
#define SFR32(name, fulladdr)  /* not supported */
#define SFR32E(name, fulladdr) /* not supported */

#define INTERRUPT(name, vector) void name(void) interrupt vector
#define INTERRUPT_USING(name, vector, regnum) void name(void) interrupt vector using regnum


// NOP () macro support
extern void _nop_(void);
#define NOP() _nop_()

#endif

//<o>STC8系列型号选择
//<i>列表提供的芯片类型都是在数据手册中出现的，仅根据理论进行设置，若有兼容性问题请入群告知我。
//<i>ROM容量留空，在下一个选项中选择。
//<0x110301=>STC8F1Kxx_8PIN
//<0x110302=>STC8F1KxxS2_16PIN_20PIN
//<0x120502=>STC8F2KxxS2_ALL
//<0x120504=>STC8F2KxxS4_ALL
//<0x2405C2=>STC8A4KxxS2A12_ALL
//<0x2805C4=>STC8A8KxxS4A12_ALL
//<0x2815C4=>STC8A8KxxD4_ALL
//<0x310201=>STC8G1Kxx_8PIN
//<0x3102A1=>STC8G1KxxA_8PIN
//<0x3103A2=>STC8G1Kxx_16PIN_20PIN
//<0x3103A1=>STC8G1KxxT_20PIN
//<0x3205A2=>STC8G2KxxS2_ALL
//<0x3205A4=>STC8G2KxxS4_ALL
//<0x4103A2=>STC8H1Kxx_20PIN
//<0x4105A2=>STC8H1Kxx_32PIN
//<0x4305C2=>STC8H3KxxS2_ALL
//<0x4305C4=>STC8H3KxxS4_ALL
//<0x4805C4=>STC8H8KxxU_ALL
//<0x520502=>STC8C2K64S2_ALL
//<0x520504=>STC8C2K64S4_ALL
#define ECBM_MCU (0x4805C4)

//<o>ROM选择
//<i>选择单片机的flash容量大小，主要影响唯一ID的读取。
//<8=>08 
//<12=>12 
//<16=>16 
//<17=>17 
//<28=>28 
//<32=>32 
//<60=>60 
//<64=>64
#define ECBM_MCU_ROM_SIZE (8)

#define __IO     volatile
typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;
typedef   signed char s8;
typedef   signed int  s16;
typedef   signed long s32;

#define REG_IN_MASK(reg,mask,value) do{reg=((reg&(~mask))|((u8)(value)&mask));}while(0)
#define REG_SET_BIT(reg,bit_mask)   do{reg|= (bit_mask);}while(0)
#define REG_RESET_BIT(reg,bit_mask) do{reg&=~(bit_mask);}while(0)
#define read_idata_u8(x)    (*((u8  volatile idata *)x))
#define read_idata_u16(x)   (*((u16 volatile idata *)x))
#define read_idata_u32(x)   (*((u32 volatile idata *)x))
#define read_xdata_u8(x)    (*((u8  volatile xdata *)x))
#define read_xdata_u16(x)   (*((u16 volatile xdata *)x))
#define read_xdata_u32(x)   (*((u32 volatile xdata *)x))
#define read_idata_s8(x)    (*((s8  volatile idata *)x))
#define read_idata_s16(x)   (*((s16 volatile idata *)x))
#define read_idata_s32(x)   (*((s32 volatile idata *)x))
#define read_xdata_s8(x)    (*((s8  volatile xdata *)x))
#define read_xdata_s16(x)   (*((s16 volatile xdata *)x))
#define read_xdata_s32(x)   (*((s32 volatile xdata *)x))

#if     (ECBM_MCU_ROM_SIZE==8)
#   define MCUID    (  (u8  code *)(0x1FF9))
#   define BGV      (*((u16 code *)(0x1FF7)))
#elif   (ECBM_MCU_ROM_SIZE==12)
#   define MCUID    (  (u8  code *)(0x2FF9))
#   define BGV      (*((u16 code *)(0x2FF7)))
#elif   (ECBM_MCU_ROM_SIZE==16)
#   define MCUID    (  (u8  code *)(0x3FF9))
#   define BGV      (*((u16 code *)(0x3FF7)))
#elif   (ECBM_MCU_ROM_SIZE==17)
#   define MCUID    (  (u8  code *)(0x43F9))
#   define BGV      (*((u16 code *)(0x43F7)))
#elif   (ECBM_MCU_ROM_SIZE==28)
#   define  MCUID   (  (u8  code *)(0x6FF9))
#   define  BGV     (*((u16 code *)(0x6FF7)))
#elif   (ECBM_MCU_ROM_SIZE==32)
#   define MCUID    (  (u8  code *)(0x7FF9))
#   define BGV      (*((u16 code *)(0x7FF7)))
#elif   (ECBM_MCU_ROM_SIZE==60)
#   define MCUID    (  (u8  code *)(0xEFF9))
#   define BGV      (*((u16 code *)(0xEFF7)))
#elif   (ECBM_MCU_ROM_SIZE==64)
#   define MCUID    (  (u8  code *)(0xFDF9))
#   define BGV      (*((u16 code *)(0xFDF7)))
#endif
#if 1

SFR(P0, 0x80);
SFR(SP, 0x81);
SFR(DPL, 0x82);
SFR(DPH, 0x83);
SFR(S4CON, 0x84);
SFR(S4BUF, 0x85);
SFR(PCON, 0x87);
SFR(TCON, 0x88);
SFR(TMOD, 0x89);
SFR(TL0, 0x8A);
SFR(TL1, 0x8B);
SFR(TH0, 0x8C);
SFR(TH1, 0x8D);
SFR(AUXR, 0x8E);
SFR(INTCLKO, 0x8F);
SFR(P1, 0x90);
SFR(P1M1, 0x91);
SFR(P1M0, 0x92);
SFR(P0M1, 0x93);
SFR(P0M0, 0x94);
SFR(P2M1, 0x95);
SFR(P2M0, 0x96);
SFR(SCON, 0x98);
SFR(SBUF, 0x99);
SFR(S2CON, 0x9A);
SFR(S2BUF, 0x9B);
SFR(IRCBAND, 0x9D);
SFR(LIRTRIM, 0x9E);
SFR(IRTRIM, 0x9F);
SFR(P2, 0xA0);
SFR(BUS_SPEED, 0xA1);
SFR(P_SW1, 0xA2);
SFR(IE, 0xA8);
SFR(SADDR, 0xA9);
SFR(WKTCL, 0xAA);
SFR(WKTCH, 0xAB);
/* Note: some SDCC versions warn about __sfr16 absolute addresses.
	Use separate byte registers (WKTCL/WKTCH) and access via macros
	to avoid "absolute address for __sfr ... probably out of range" warnings. */
// 原始地址范围: 0xAC - 0xAF
SFR(S3CON, 0xAC);
SFR(S3BUF, 0xAD);
SFR(TA, 0xAE);
SFR(IE2, 0xAF);

// 原始地址范围: 0xB0 - 0xBF
SFR(P3, 0xB0);
SFR(P3M1, 0xB1);
SFR(P3M0, 0xB2);
SFR(P4M1, 0xB3);
SFR(P4M0, 0xB4);
SFR(IP2, 0xB5);
SFR(IP2H, 0xB6);
SFR(IPH, 0xB7);
SFR(IP, 0xB8);
SFR(SADEN, 0xB9);
SFR(P_SW2, 0xBA);
SFR(VOCTRL, 0xBB);
SFR(ADC_CONTR, 0xBC);
SFR(ADC_RES, 0xBD);
SFR(ADC_RESL, 0xBE);

// 原始地址范围: 0xC0 - 0xCF
SFR(P4, 0xC0);
SFR(WDT_CONTR, 0xC1);
SFR(IAP_DATA, 0xC2);
SFR(IAP_ADDRH, 0xC3);
SFR(IAP_ADDRL, 0xC4);
SFR(IAP_CMD, 0xC5);
SFR(IAP_TRIG, 0xC6);
SFR(IAP_CONTR, 0xC7);
SFR(P5, 0xC8);
SFR(P5M1, 0xC9);
SFR(P5M0, 0xCA);
SFR(P6M1, 0xCB);
SFR(P6M0, 0xCC);
SFR(SPSTAT, 0xCD);
SFR(SPCTL, 0xCE);
SFR(SPDAT, 0xCF);

// 原始地址范围: 0xD0 - 0xDB
SFR(PSW, 0xD0);
SFR(T4T3M, 0xD1);
SFR(T4H, 0xD2);
SFR(T4L, 0xD3);
SFR(T3H, 0xD4);
SFR(T3L, 0xD5);
SFR(T2H, 0xD6);
SFR(T2L, 0xD7);
SFR(CCON, 0xD8);
SFR(CMOD, 0xD9);
SFR(CCAPM0, 0xDA);
SFR(CCAPM1, 0xDB);


// 地址范围: 0xDC - 0xDF
#if (ECBM_MCU==0x4805C4)
SFR(USBCLK, 0xDC);
#else
SFR(CCAPM2, 0xDC);
#endif

#if (ECBM_MCU==0x2815C4)
// CCAPM3 为 xdata 寄存器，保持原定义
#define CCAPM3  read_xdata_u8(0xFD54)
#else
SFR(CCAPM3, 0xDD);
#endif

SFR(ADC_CFG, 0xDE);
SFR(IP3, 0xDF);

// 地址范围: 0xE0 - 0xEF
SFR(ACC, 0xE0);
SFR(P7M1, 0xE1);
SFR(P7M0, 0xE2);
SFR(DPS, 0xE3);
SFR(DPL1, 0xE4);
SFR(DPH1, 0xE5);
SFR(CMPCR1, 0xE6);
SFR(CMPCR2, 0xE7);

SFR(P6, 0xE8);
SFR(CL, 0xE9);
SFR(CCAP0L, 0xEA);
SFR(CCAP1L, 0xEB);

#if (ECBM_MCU==0x4805C4)
SFR(USBDAT, 0xEC);
#else
SFR(CCAP2L, 0xEC);
#endif

#if (ECBM_MCU==0x2815C4)
// CCAP3L 为 xdata 寄存器，保持原定义
#define CCAP3L  read_xdata_u8(0xFD55)
#else
SFR(CCAP3L, 0xED);
#endif

SFR(IP3H, 0xEE);
SFR(AUXINTIF, 0xEF);

// 地址范围: 0xF0 - 0xFF
SFR(B, 0xF0);

#if (ECBM_MCU==0x3205A4)||(ECBM_MCU==0x2815C4)
SFR(PWMSET, 0xF1);
#endif

#if (ECBM_MCU==0x2405C2)||(ECBM_MCU==0x2805C4)
SFR(PWMCFG, 0xF1);
#endif

SFR(PCA_PWM0, 0xF2);
SFR(PCA_PWM1, 0xF3);

#if (ECBM_MCU==0x4805C4)
SFR(USBCON, 0xF4);
#else
SFR(PCA_PWM2, 0xF4);
#endif

#if (ECBM_MCU==0x2405C2)||(ECBM_MCU==0x2805C4)
SFR(PCA_PWM3, 0xF5);
#else
SFR(IAP_TPS, 0xF5);
#endif

#if (ECBM_MCU==0x2815C4)
// PCA_PWM3 为 xdata 寄存器，保持原定义
#define PCA_PWM3    read_xdata_u8(0xFD57)
SFR(PWMCFG, 0xF6);
#endif

#if (ECBM_MCU==0x2405C2)||(ECBM_MCU==0x2805C4)
SFR(PWMIF, 0xF6);
SFR(PWMFDCR, 0xF7);
#endif

#if (ECBM_MCU==0x3205A2)||(ECBM_MCU==0x3205A4)
SFR(PWMCFG01, 0xF6);
SFR(PWMCFG23, 0xF7);
#endif

SFR(P7, 0xF8);
SFR(CH, 0xF9);
SFR(CCAP0H, 0xFA);
SFR(CCAP1H, 0xFB);

#if (ECBM_MCU==0x4805C4)
SFR(USBADR, 0xFC);
#else
SFR(CCAP2H, 0xFC);
#endif

#if (ECBM_MCU==0x2815C4)
// CCAP3H 为 xdata 寄存器，保持原定义
#define CCAP3H  read_xdata_u8(0xFD56)
#else
SFR(CCAP3H, 0xFD);
#endif

#if (ECBM_MCU==0x2405C2)||(ECBM_MCU==0x2805C4)
SFR(PWMCR, 0xFE);
#endif

#if (ECBM_MCU==0x3205A4)
SFR(PWMCFG45, 0xFE);
#endif

SFR(RSTCFG, 0xFF);

#endif
#if 1
/* Restored bit-addressable sbits for SDCC */
/* TCON (0x88) bits */
 SBIT(IT0, 0x88, 0);
 SBIT(IE0, 0x88, 1);
 SBIT(IT1, 0x88, 2);
 SBIT(IE1, 0x88, 3);
 SBIT(TR0, 0x88, 4);
 SBIT(TF0, 0x88, 5);
 SBIT(TR1, 0x88, 6);
 SBIT(TF1, 0x88, 7);

/*need to fix IE (0xA8) bits */
 SBIT(EX0, 0xA8, 0);
 SBIT(ET0, 0xA8, 1);
 SBIT(EX1, 0xA8, 2);
 SBIT(ET1, 0xA8, 3);
 SBIT(ES, 0xA8, 4);
 SBIT(EADC, 0xA8, 5);
 SBIT(ELVD, 0xA8, 6);
 SBIT(EA, 0xA8, 7);

/* need to fix IP (0xB8) bits (priority low bits) */
 SBIT(PX0, 0xB8, 0);
 SBIT(PT0, 0xB8, 1);
 SBIT(PX1, 0xB8, 2);
 SBIT(PT1, 0xB8, 3);
 SBIT(PS, 0xB8, 4);
 SBIT(PADC, 0xB8, 5);
 SBIT(PLVD, 0xB8, 6);


/* need to fix SCON(0x98)bits*/
 SBIT(SM0, 0x98, 7);
 SBIT(SM1, 0x98, 6);
 SBIT(SM2, 0x98, 5);
 SBIT(REN, 0x98, 4);
 SBIT(TB8, 0x98, 3);
 SBIT(RB8, 0x98, 2);
 SBIT(TI, 0x98, 1);
 SBIT(RI, 0x98, 0);


#endif
#if 1

#define DMA_M2M_CFG                 read_xdata_u8(0xFA00)
#define DMA_M2M_CR                  read_xdata_u8(0xFA01)
#define DMA_M2M_STA                 read_xdata_u8(0xFA02)
#define DMA_M2M_AMT                 read_xdata_u8(0xFA03)
#define DMA_M2M_DONE                read_xdata_u8(0xFA04)
#define DMA_M2M_TXA                 read_xdata_u16(0xFA05)
#define DMA_M2M_TXAH                read_xdata_u8(0xFA05)
#define DMA_M2M_TXAL                read_xdata_u8(0xFA06)
#define DMA_M2M_RXA                 read_xdata_u16(0xFA07)
#define DMA_M2M_RXAH                read_xdata_u8(0xFA07)
#define DMA_M2M_RXAL                read_xdata_u8(0xFA08)

#define DMA_ADC_CFG                 read_xdata_u8(0xFA10)
#define DMA_ADC_CR                  read_xdata_u8(0xFA11)
#define DMA_ADC_STA                 read_xdata_u8(0xFA12)
#define DMA_ADC_RXA                 read_xdata_u16(0xFA17)
#define DMA_ADC_RXAH                read_xdata_u8(0xFA17)
#define DMA_ADC_RXAL                read_xdata_u8(0xFA18)
#define DMA_ADC_CFG2                read_xdata_u8(0xFA19)
#define DMA_ADC_CHSW0               read_xdata_u8(0xFA1A)
#define DMA_ADC_CHSW1               read_xdata_u8(0xFA1B)

#define DMA_SPI_CFG                 read_xdata_u8(0xFA20)
#define DMA_SPI_CR                  read_xdata_u8(0xFA21)
#define DMA_SPI_STA                 read_xdata_u8(0xFA22)
#define DMA_SPI_AMT                 read_xdata_u8(0xFA23)
#define DMA_SPI_DONE                read_xdata_u8(0xFA24)
#define DMA_SPI_TXA                 read_xdata_u16(0xFA25)
#define DMA_SPI_TXAH                read_xdata_u8(0xFA25)
#define DMA_SPI_TXAL                read_xdata_u8(0xFA26)
#define DMA_SPI_RXA                 read_xdata_u16(0xFA27)
#define DMA_SPI_RXAH                read_xdata_u8(0xFA27)
#define DMA_SPI_RXAL                read_xdata_u8(0xFA28)
#define DMA_SPI_CFG2                read_xdata_u8(0xFA29)

#define DMA_UR1T_CFG                read_xdata_u8(0xFA30)
#define DMA_UR1T_CR                 read_xdata_u8(0xFA31)
#define DMA_UR1T_STA                read_xdata_u8(0xFA32)
#define DMA_UR1T_AMT                read_xdata_u8(0xFA33)
#define DMA_UR1T_DONE               read_xdata_u8(0xFA34)
#define DMA_UR1T_TXA                read_xdata_u16(0xFA35)
#define DMA_UR1T_TXAH               read_xdata_u8(0xFA35)
#define DMA_UR1T_TXAL               read_xdata_u8(0xFA36)
#define DMA_UR1R_CFG                read_xdata_u8(0xFA38)
#define DMA_UR1R_CR                 read_xdata_u8(0xFA39)
#define DMA_UR1R_STA                read_xdata_u8(0xFA3A)
#define DMA_UR1R_AMT                read_xdata_u8(0xFA3B)
#define DMA_UR1R_DONE               read_xdata_u8(0xFA3C)
#define DMA_UR1R_RXA                read_xdata_u16(0xFA3D)
#define DMA_UR1R_RXAH               read_xdata_u8(0xFA3D)
#define DMA_UR1R_RXAL               read_xdata_u8(0xFA3E)

#define DMA_UR2T_CFG                read_xdata_u8(0xFA40)
#define DMA_UR2T_CR                 read_xdata_u8(0xFA41)
#define DMA_UR2T_STA                read_xdata_u8(0xFA42)
#define DMA_UR2T_AMT                read_xdata_u8(0xFA43)
#define DMA_UR2T_DONE               read_xdata_u8(0xFA44)
#define DMA_UR2T_TXA                read_xdata_u16(0xFA45)
#define DMA_UR2T_TXAH               read_xdata_u8(0xFA45)
#define DMA_UR2T_TXAL               read_xdata_u8(0xFA46)
#define DMA_UR2R_CFG                read_xdata_u8(0xFA48)
#define DMA_UR2R_CR                 read_xdata_u8(0xFA49)
#define DMA_UR2R_STA                read_xdata_u8(0xFA4A)
#define DMA_UR2R_AMT                read_xdata_u8(0xFA4B)
#define DMA_UR2R_DONE               read_xdata_u8(0xFA4C)
#define DMA_UR2R_RXA                read_xdata_u16(0xFA4D)
#define DMA_UR2R_RXAH               read_xdata_u8(0xFA4D)
#define DMA_UR2R_RXAL               read_xdata_u8(0xFA4E)

#define DMA_UR3T_CFG                read_xdata_u8(0xFA50)
#define DMA_UR3T_CR                 read_xdata_u8(0xFA51)
#define DMA_UR3T_STA                read_xdata_u8(0xFA52)
#define DMA_UR3T_AMT                read_xdata_u8(0xFA53)
#define DMA_UR3T_DONE               read_xdata_u8(0xFA54)
#define DMA_UR3T_TXA                read_xdata_u16(0xFA55)
#define DMA_UR3T_TXAH               read_xdata_u8(0xFA55)
#define DMA_UR3T_TXAL               read_xdata_u8(0xFA56)
#define DMA_UR3R_CFG                read_xdata_u8(0xFA58)
#define DMA_UR3R_CR                 read_xdata_u8(0xFA59)
#define DMA_UR3R_STA                read_xdata_u8(0xFA5A)
#define DMA_UR3R_AMT                read_xdata_u8(0xFA5B)
#define DMA_UR3R_DONE               read_xdata_u8(0xFA5C)
#define DMA_UR3R_RXA                read_xdata_u16(0xFA5D)
#define DMA_UR3R_RXAH               read_xdata_u8(0xFA5D)
#define DMA_UR3R_RXAL               read_xdata_u8(0xFA5E)

#define DMA_UR4T_CFG                read_xdata_u8(0xFA60)
#define DMA_UR4T_CR                 read_xdata_u8(0xFA61)
#define DMA_UR4T_STA                read_xdata_u8(0xFA62)
#define DMA_UR4T_AMT                read_xdata_u8(0xFA63)
#define DMA_UR4T_DONE               read_xdata_u8(0xFA64)
#define DMA_UR4T_TXA                read_xdata_u16(0xFA65)
#define DMA_UR4T_TXAH               read_xdata_u8(0xFA65)
#define DMA_UR4T_TXAL               read_xdata_u8(0xFA66)
#define DMA_UR4R_CFG                read_xdata_u8(0xFA68)
#define DMA_UR4R_CR                 read_xdata_u8(0xFA69)
#define DMA_UR4R_STA                read_xdata_u8(0xFA6A)
#define DMA_UR4R_AMT                read_xdata_u8(0xFA6B)
#define DMA_UR4R_DONE               read_xdata_u8(0xFA6C)
#define DMA_UR4R_RXA                read_xdata_u16(0xFA6D)
#define DMA_UR4R_RXAH               read_xdata_u8(0xFA6D)
#define DMA_UR4R_RXAL               read_xdata_u8(0xFA6E)

#define DMA_LCM_CFG                 read_xdata_u8(0xFA70)
#define DMA_LCM_CR                  read_xdata_u8(0xFA71)
#define DMA_LCM_STA                 read_xdata_u8(0xFA72)
#define DMA_LCM_AMT                 read_xdata_u8(0xFA73)
#define DMA_LCM_DONE                read_xdata_u8(0xFA74)
#define DMA_LCM_TXA                 read_xdata_u16(0xFA75)
#define DMA_LCM_TXAH                read_xdata_u8(0xFA75)
#define DMA_LCM_TXAL                read_xdata_u8(0xFA76)
#define DMA_LCM_RXA                 read_xdata_u16(0xFA77)
#define DMA_LCM_RXAH                read_xdata_u8(0xFA77)
#define DMA_LCM_RXAL                read_xdata_u8(0xFA78)

#define COMEN                       read_xdata_u8(0xFB00)
#define SEGENL                      read_xdata_u8(0xFB01)
#define SEGENH                      read_xdata_u8(0xFB02)
#define LEDCTRL                     read_xdata_u8(0xFB03)
#define LEDCKS                      read_xdata_u8(0xFB04)
#define COM0_DA_L                   read_xdata_u8(0xFB10)
#define COM1_DA_L                   read_xdata_u8(0xFB11)
#define COM2_DA_L                   read_xdata_u8(0xFB12)
#define COM3_DA_L                   read_xdata_u8(0xFB13)
#define COM4_DA_L                   read_xdata_u8(0xFB14)
#define COM5_DA_L                   read_xdata_u8(0xFB15)
#define COM6_DA_L                   read_xdata_u8(0xFB16)
#define COM7_DA_L                   read_xdata_u8(0xFB17)
#define COM0_DA_H                   read_xdata_u8(0xFB18)
#define COM1_DA_H                   read_xdata_u8(0xFB19)
#define COM2_DA_H                   read_xdata_u8(0xFB1A)
#define COM3_DA_H                   read_xdata_u8(0xFB1B)
#define COM4_DA_H                   read_xdata_u8(0xFB1C)
#define COM5_DA_H                   read_xdata_u8(0xFB1D)
#define COM6_DA_H                   read_xdata_u8(0xFB1E)
#define COM7_DA_H                   read_xdata_u8(0xFB1F)
#define COM0_DC_L                   read_xdata_u8(0xFB20)
#define COM1_DC_L                   read_xdata_u8(0xFB21)
#define COM2_DC_L                   read_xdata_u8(0xFB22)
#define COM3_DC_L                   read_xdata_u8(0xFB23)
#define COM4_DC_L                   read_xdata_u8(0xFB24)
#define COM5_DC_L                   read_xdata_u8(0xFB25)
#define COM6_DC_L                   read_xdata_u8(0xFB26)
#define COM7_DC_L                   read_xdata_u8(0xFB27)
#define COM0_DC_H                   read_xdata_u8(0xFB28)
#define COM1_DC_H                   read_xdata_u8(0xFB29)
#define COM2_DC_H                   read_xdata_u8(0xFB2A)
#define COM3_DC_H                   read_xdata_u8(0xFB2B)
#define COM4_DC_H                   read_xdata_u8(0xFB2C)
#define COM5_DC_H                   read_xdata_u8(0xFB2D)
#define COM6_DC_H                   read_xdata_u8(0xFB2E)
#define COM7_DC_H                   read_xdata_u8(0xFB2F)

#define TSCHEN1                     read_xdata_u8(0xFB40)
#define TSCHEN2                     read_xdata_u8(0xFB41)
#define TSCFG1                      read_xdata_u8(0xFB42)
#define TSCFG2                      read_xdata_u8(0xFB43)
#define TSWUTC                      read_xdata_u8(0xFB44)
#define TSCTRL                      read_xdata_u8(0xFB45)
#define TSSTA1                      read_xdata_u8(0xFB46)
#define TSSTA2                      read_xdata_u8(0xFB47)
#define TSRT                        read_xdata_u8(0xFB48)
#define TSDATH                      read_xdata_u8(0xFB49)
#define TSDATL                      read_xdata_u8(0xFB4A)
#define TSTH00H                     read_xdata_u8(0xFB50)
#define TSTH00L                     read_xdata_u8(0xFB51)
#define TSTH01H                     read_xdata_u8(0xFB52)
#define TSTH01L                     read_xdata_u8(0xFB53)
#define TSTH02H                     read_xdata_u8(0xFB54)
#define TSTH02L                     read_xdata_u8(0xFB55)
#define TSTH03H                     read_xdata_u8(0xFB56)
#define TSTH03L                     read_xdata_u8(0xFB57)
#define TSTH04H                     read_xdata_u8(0xFB58)
#define TSTH04L                     read_xdata_u8(0xFB59)
#define TSTH05H                     read_xdata_u8(0xFB5A)
#define TSTH05L                     read_xdata_u8(0xFB5B)
#define TSTH06H                     read_xdata_u8(0xFB5C)
#define TSTH06L                     read_xdata_u8(0xFB5D)
#define TSTH07H                     read_xdata_u8(0xFB5E)
#define TSTH07L                     read_xdata_u8(0xFB5F)
#define TSTH08H                     read_xdata_u8(0xFB60)
#define TSTH08L                     read_xdata_u8(0xFB61)
#define TSTH09H                     read_xdata_u8(0xFB62)
#define TSTH09L                     read_xdata_u8(0xFB63)
#define TSTH10H                     read_xdata_u8(0xFB64)
#define TSTH10L                     read_xdata_u8(0xFB65)
#define TSTH11H                     read_xdata_u8(0xFB66)
#define TSTH11L                     read_xdata_u8(0xFB67)
#define TSTH12H                     read_xdata_u8(0xFB68)
#define TSTH12L                     read_xdata_u8(0xFB69)
#define TSTH13H                     read_xdata_u8(0xFB6A)
#define TSTH13L                     read_xdata_u8(0xFB6B)
#define TSTH14H                     read_xdata_u8(0xFB6C)
#define TSTH14L                     read_xdata_u8(0xFB6D)
#define TSTH15H                     read_xdata_u8(0xFB6E)
#define TSTH15L                     read_xdata_u8(0xFB6F)

#define LCDCFG                      read_xdata_u8(0xFB80)
#define LCDCFG2                     read_xdata_u8(0xFB81)
#define DBLEN                       read_xdata_u8(0xFB82)
#define COMLENL                     read_xdata_u8(0xFB83)
#define COMLENM                     read_xdata_u8(0xFB84)
#define COMLENH                     read_xdata_u8(0xFB85)
#define BLINKRATE                   read_xdata_u8(0xFB86)
#define LCDCR                       read_xdata_u8(0xFB87)
#define COMON                       read_xdata_u8(0xFB88)
#define SEGON1                      read_xdata_u8(0xFB8A)
#define SEGON2                      read_xdata_u8(0xFB8B)
#define SEGON3                      read_xdata_u8(0xFB8C)
#define SEGON4                      read_xdata_u8(0xFB8D)
#define SEGON5                      read_xdata_u8(0xFB8E)
#define C0SEGV0                     read_xdata_u8(0xFB90)
#define C0SEGV1                     read_xdata_u8(0xFB91)
#define C0SEGV2                     read_xdata_u8(0xFB92)
#define C0SEGV3                     read_xdata_u8(0xFB93)
#define C0SEGV4                     read_xdata_u8(0xFB94)
#define C1SEGV0                     read_xdata_u8(0xFB98)
#define C1SEGV1                     read_xdata_u8(0xFB99)
#define C1SEGV2                     read_xdata_u8(0xFB9A)
#define C1SEGV3                     read_xdata_u8(0xFB9B)
#define C1SEGV4                     read_xdata_u8(0xFB9C)
#define C2SEGV0                     read_xdata_u8(0xFBA0)
#define C2SEGV1                     read_xdata_u8(0xFBA1)
#define C2SEGV2                     read_xdata_u8(0xFBA2)
#define C2SEGV3                     read_xdata_u8(0xFBA3)
#define C2SEGV4                     read_xdata_u8(0xFBA4)
#define C3SEGV0                     read_xdata_u8(0xFBA8)
#define C3SEGV1                     read_xdata_u8(0xFBA9)
#define C3SEGV2                     read_xdata_u8(0xFBAA)
#define C3SEGV3                     read_xdata_u8(0xFBAB)
#define C3SEGV4                     read_xdata_u8(0xFBAC)

#define PWM_P3_C                    read_xdata_u16(0xFC00)
#define PWM_P3_CH                   read_xdata_u8(0xFC00)
#define PWM_P3_CL                   read_xdata_u8(0xFC01)
#define PWM_P3_CKS                  read_xdata_u8(0xFC02)
#define PWM_P3_IF                   read_xdata_u8(0xFC05)
#define PWM_P3_FDCR                 read_xdata_u8(0xFC06)
#define PWM_P30_T1                  read_xdata_u16(0xFC10)
#define PWM_P30_T1H                 read_xdata_u8(0xFC10)
#define PWM_P30_T1L                 read_xdata_u8(0xFC11)
#define PWM_P30_T2                  read_xdata_u16(0xFC12)
#define PWM_P30_T2H                 read_xdata_u8(0xFC12)
#define PWM_P30_T2L                 read_xdata_u8(0xFC13)
#define PWM_P30_CR                  read_xdata_u8(0xFC14)
#define PWM_P30_HLD                 read_xdata_u8(0xFC15)
#define PWM_P31_T1                  read_xdata_u16(0xFC18)
#define PWM_P31_T1H                 read_xdata_u8(0xFC18)
#define PWM_P31_T1L                 read_xdata_u8(0xFC19)
#define PWM_P31_T2                  read_xdata_u16(0xFC1A)
#define PWM_P31_T2H                 read_xdata_u8(0xFC1A)
#define PWM_P31_T2L                 read_xdata_u8(0xFC1B)
#define PWM_P31_CR                  read_xdata_u8(0xFC1C)
#define PWM_P31_HLD                 read_xdata_u8(0xFC1D)
#define PWM_P32_T1                  read_xdata_u16(0xFC20)
#define PWM_P32_T1H                 read_xdata_u8(0xFC20)
#define PWM_P32_T1L                 read_xdata_u8(0xFC21)
#define PWM_P32_T2                  read_xdata_u16(0xFC22)
#define PWM_P32_T2H                 read_xdata_u8(0xFC22)
#define PWM_P32_T2L                 read_xdata_u8(0xFC23)
#define PWM_P32_CR                  read_xdata_u8(0xFC24)
#define PWM_P32_HLD                 read_xdata_u8(0xFC25)
#define PWM_P33_T1                  read_xdata_u16(0xFC28)
#define PWM_P33_T1H                 read_xdata_u8(0xFC28)
#define PWM_P33_T1L                 read_xdata_u8(0xFC29)
#define PWM_P33_T2                  read_xdata_u16(0xFC2A)
#define PWM_P33_T2H                 read_xdata_u8(0xFC2A)
#define PWM_P33_T2L                 read_xdata_u8(0xFC2B)
#define PWM_P33_CR                  read_xdata_u8(0xFC2C)
#define PWM_P33_HLD                 read_xdata_u8(0xFC2D)
#define PWM_P34_T1                  read_xdata_u16(0xFC30)
#define PWM_P34_T1H                 read_xdata_u8(0xFC30)
#define PWM_P34_T1L                 read_xdata_u8(0xFC31)
#define PWM_P34_T2                  read_xdata_u16(0xFC32)
#define PWM_P34_T2H                 read_xdata_u8(0xFC32)
#define PWM_P34_T2L                 read_xdata_u8(0xFC33)
#define PWM_P34_CR                  read_xdata_u8(0xFC34)
#define PWM_P34_HLD                 read_xdata_u8(0xFC35)
#define PWM_P35_T1                  read_xdata_u16(0xFC38)
#define PWM_P35_T1H                 read_xdata_u8(0xFC38)
#define PWM_P35_T1L                 read_xdata_u8(0xFC39)
#define PWM_P35_T2                  read_xdata_u16(0xFC3A)
#define PWM_P35_T2H                 read_xdata_u8(0xFC3A)
#define PWM_P35_T2L                 read_xdata_u8(0xFC3B)
#define PWM_P35_CR                  read_xdata_u8(0xFC3C)
#define PWM_P35_HLD                 read_xdata_u8(0xFC3D)
#define PWM_P36_T1                  read_xdata_u16(0xFC40)
#define PWM_P36_T1H                 read_xdata_u8(0xFC40)
#define PWM_P36_T1L                 read_xdata_u8(0xFC41)
#define PWM_P36_T2                  read_xdata_u16(0xFC42)
#define PWM_P36_T2H                 read_xdata_u8(0xFC42)
#define PWM_P36_T2L                 read_xdata_u8(0xFC43)
#define PWM_P36_CR                  read_xdata_u8(0xFC44)
#define PWM_P36_HLD                 read_xdata_u8(0xFC45)
#define PWM_P37_T1                  read_xdata_u16(0xFC48)
#define PWM_P37_T1H                 read_xdata_u8(0xFC48)
#define PWM_P37_T1L                 read_xdata_u8(0xFC49)
#define PWM_P37_T2                  read_xdata_u16(0xFC4A)
#define PWM_P37_T2H                 read_xdata_u8(0xFC4A)
#define PWM_P37_T2L                 read_xdata_u8(0xFC4B)
#define PWM_P37_CR                  read_xdata_u8(0xFC4C)
#define PWM_P37_HLD                 read_xdata_u8(0xFC4D)
#define PWM_P4_C                    read_xdata_u16(0xFC50)
#define PWM_P4_CH                   read_xdata_u8(0xFC50)
#define PWM_P4_CL                   read_xdata_u8(0xFC51)
#define PWM_P4_CKS                  read_xdata_u8(0xFC52)
#define PWM_P4_TADC                 read_xdata_u16(0xFC53)
#define PWM_P4_TADCH                read_xdata_u8(0xFC53)
#define PWM_P4_TADCL                read_xdata_u8(0xFC54)
#define PWM_P4_IF                   read_xdata_u8(0xFC55)
#define PWM_P4_FDCR                 read_xdata_u8(0xFC56)
#define PWM_P40_T1                  read_xdata_u16(0xFC60)
#define PWM_P40_T1H                 read_xdata_u8(0xFC60)
#define PWM_P40_T1L                 read_xdata_u8(0xFC61)
#define PWM_P40_T2                  read_xdata_u16(0xFC62)
#define PWM_P40_T2H                 read_xdata_u8(0xFC62)
#define PWM_P40_T2L                 read_xdata_u8(0xFC63)
#define PWM_P40_CR                  read_xdata_u8(0xFC64)
#define PWM_P40_HLD                 read_xdata_u8(0xFC65)
#define PWM_P41_T1                  read_xdata_u16(0xFC68)
#define PWM_P41_T1H                 read_xdata_u8(0xFC68)
#define PWM_P41_T1L                 read_xdata_u8(0xFC69)
#define PWM_P41_T2                  read_xdata_u16(0xFC6A)
#define PWM_P41_T2H                 read_xdata_u8(0xFC6A)
#define PWM_P41_T2L                 read_xdata_u8(0xFC6B)
#define PWM_P41_CR                  read_xdata_u8(0xFC6C)
#define PWM_P41_HLD                 read_xdata_u8(0xFC6D)
#define PWM_P42_T1                  read_xdata_u16(0xFC70)
#define PWM_P42_T1H                 read_xdata_u8(0xFC70)
#define PWM_P42_T1L                 read_xdata_u8(0xFC71)
#define PWM_P42_T2                  read_xdata_u16(0xFC72)
#define PWM_P42_T2H                 read_xdata_u8(0xFC72)
#define PWM_P42_T2L                 read_xdata_u8(0xFC73)
#define PWM_P42_CR                  read_xdata_u8(0xFC74)
#define PWM_P42_HLD                 read_xdata_u8(0xFC75)
#define PWM_P43_T1                  read_xdata_u16(0xFC78)
#define PWM_P43_T1H                 read_xdata_u8(0xFC78)
#define PWM_P43_T1L                 read_xdata_u8(0xFC79)
#define PWM_P43_T2                  read_xdata_u16(0xFC7A)
#define PWM_P43_T2H                 read_xdata_u8(0xFC7A)
#define PWM_P43_T2L                 read_xdata_u8(0xFC7B)
#define PWM_P43_CR                  read_xdata_u8(0xFC7C)
#define PWM_P43_HLD                 read_xdata_u8(0xFC7D)
#define PWM_P44_T1                  read_xdata_u16(0xFC80)
#define PWM_P44_T1H                 read_xdata_u8(0xFC80)
#define PWM_P44_T1L                 read_xdata_u8(0xFC81)
#define PWM_P44_T2                  read_xdata_u16(0xFC82)
#define PWM_P44_T2H                 read_xdata_u8(0xFC82)
#define PWM_P44_T2L                 read_xdata_u8(0xFC83)
#define PWM_P44_CR                  read_xdata_u8(0xFC84)
#define PWM_P44_HLD                 read_xdata_u8(0xFC85)
#define PWM_P45_T1                  read_xdata_u16(0xFC88)
#define PWM_P45_T1H                 read_xdata_u8(0xFC88)
#define PWM_P45_T1L                 read_xdata_u8(0xFC89)
#define PWM_P45_T2                  read_xdata_u16(0xFC8A)
#define PWM_P45_T2H                 read_xdata_u8(0xFC8A)
#define PWM_P45_T2L                 read_xdata_u8(0xFC8B)
#define PWM_P45_CR                  read_xdata_u8(0xFC8C)
#define PWM_P45_HLD                 read_xdata_u8(0xFC8D)
#define PWM_P46_T1                  read_xdata_u16(0xFC90)
#define PWM_P46_T1H                 read_xdata_u8(0xFC90)
#define PWM_P46_T1L                 read_xdata_u8(0xFC91)
#define PWM_P46_T2                  read_xdata_u16(0xFC92)
#define PWM_P46_T2H                 read_xdata_u8(0xFC92)
#define PWM_P46_T2L                 read_xdata_u8(0xFC93)
#define PWM_P46_CR                  read_xdata_u8(0xFC94)
#define PWM_P46_HLD                 read_xdata_u8(0xFC95)
#define PWM_P47_T1                  read_xdata_u16(0xFC98)
#define PWM_P47_T1H                 read_xdata_u8(0xFC98)
#define PWM_P47_T1L                 read_xdata_u8(0xFC99)
#define PWM_P47_T2                  read_xdata_u16(0xFC9A)
#define PWM_P47_T2H                 read_xdata_u8(0xFC9A)
#define PWM_P47_T2L                 read_xdata_u8(0xFC9B)
#define PWM_P47_CR                  read_xdata_u8(0xFC9C)
#define PWM_P47_HLD                 read_xdata_u8(0xFC9D)
#define PWM_P5_C                    read_xdata_u16(0xFCA0)
#define PWM_P5_CH                   read_xdata_u8(0xFCA0)
#define PWM_P5_CL                   read_xdata_u8(0xFCA1)
#define PWM_P5_CKS                  read_xdata_u8(0xFCA2)
#define PWM_P5_IF                   read_xdata_u8(0xFCA5)
#define PWM_P5_FDCR                 read_xdata_u8(0xFCA6)
#define PWM_P50_T1                  read_xdata_u16(0xFCB0)
#define PWM_P50_T1H                 read_xdata_u8(0xFCB0)
#define PWM_P50_T1L                 read_xdata_u8(0xFCB1)
#define PWM_P50_T2                  read_xdata_u16(0xFCB2)
#define PWM_P50_T2H                 read_xdata_u8(0xFCB2)
#define PWM_P50_T2L                 read_xdata_u8(0xFCB3)
#define PWM_P50_CR                  read_xdata_u8(0xFCB4)
#define PWM_P50_HLD                 read_xdata_u8(0xFCB5)
#define PWM_P51_T1                  read_xdata_u16(0xFCB8)
#define PWM_P51_T1H                 read_xdata_u8(0xFCB8)
#define PWM_P51_T1L                 read_xdata_u8(0xFCB9)
#define PWM_P51_T2                  read_xdata_u16(0xFCBA)
#define PWM_P51_T2H                 read_xdata_u8(0xFCBA)
#define PWM_P51_T2L                 read_xdata_u8(0xFCBB)
#define PWM_P51_CR                  read_xdata_u8(0xFCBC)
#define PWM_P51_HLD                 read_xdata_u8(0xFCBD)
#define PWM_P52_T1                  read_xdata_u16(0xFCC0)
#define PWM_P52_T1H                 read_xdata_u8(0xFCC0)
#define PWM_P52_T1L                 read_xdata_u8(0xFCC1)
#define PWM_P52_T2                  read_xdata_u16(0xFCC2)
#define PWM_P52_T2H                 read_xdata_u8(0xFCC2)
#define PWM_P52_T2L                 read_xdata_u8(0xFCC3)
#define PWM_P52_CR                  read_xdata_u8(0xFCC4)
#define PWM_P52_HLD                 read_xdata_u8(0xFCC5)
#define PWM_P53_T1                  read_xdata_u16(0xFCC8)
#define PWM_P53_T1H                 read_xdata_u8(0xFCC8)
#define PWM_P53_T1L                 read_xdata_u8(0xFCC9)
#define PWM_P53_T2                  read_xdata_u16(0xFCCA)
#define PWM_P53_T2H                 read_xdata_u8(0xFCCA)
#define PWM_P53_T2L                 read_xdata_u8(0xFCCB)
#define PWM_P53_CR                  read_xdata_u8(0xFCCC)
#define PWM_P53_HLD                 read_xdata_u8(0xFCCD)
#define PWM_P54_T1                  read_xdata_u16(0xFCD0)
#define PWM_P54_T1H                 read_xdata_u8(0xFCD0)
#define PWM_P54_T1L                 read_xdata_u8(0xFCD1)
#define PWM_P54_T2                  read_xdata_u16(0xFCD2)
#define PWM_P54_T2H                 read_xdata_u8(0xFCD2)
#define PWM_P54_T2L                 read_xdata_u8(0xFCD3)
#define PWM_P54_CR                  read_xdata_u8(0xFCD4)
#define PWM_P54_HLD                 read_xdata_u8(0xFCD5)
#define PWM_P55_T1                  read_xdata_u16(0xFCD8)
#define PWM_P55_T1H                 read_xdata_u8(0xFCD8)
#define PWM_P55_T1L                 read_xdata_u8(0xFCD9)
#define PWM_P55_T2                  read_xdata_u16(0xFCDA)
#define PWM_P55_T2H                 read_xdata_u8(0xFCDA)
#define PWM_P55_T2L                 read_xdata_u8(0xFCDB)
#define PWM_P55_CR                  read_xdata_u8(0xFCDC)
#define PWM_P55_HLD                 read_xdata_u8(0xFCDD)
#define PWM_P56_T1                  read_xdata_u16(0xFCE0)
#define PWM_P56_T1H                 read_xdata_u8(0xFCE0)
#define PWM_P56_T1L                 read_xdata_u8(0xFCE1)
#define PWM_P56_T2                  read_xdata_u16(0xFCE2)
#define PWM_P56_T2H                 read_xdata_u8(0xFCE2)
#define PWM_P56_T2L                 read_xdata_u8(0xFCE3)
#define PWM_P56_CR                  read_xdata_u8(0xFCE4)
#define PWM_P56_HLD                 read_xdata_u8(0xFCE5)
#define PWM_P57_T1                  read_xdata_u16(0xFCE8)
#define PWM_P57_T1H                 read_xdata_u8(0xFCE8)
#define PWM_P57_T1L                 read_xdata_u8(0xFCE9)
#define PWM_P57_T2                  read_xdata_u16(0xFCEA)
#define PWM_P57_T2H                 read_xdata_u8(0xFCEA)
#define PWM_P57_T2L                 read_xdata_u8(0xFCEB)
#define PWM_P57_CR                  read_xdata_u8(0xFCEC)
#define PWM_P57_HLD                 read_xdata_u8(0xFCED)

#define MD3MD2MD1MD0                read_xdata_u32(0xFCF0)
#define MD1MD0                      read_xdata_u16(0xFCF2)
#define MD5MD4                      read_xdata_u16(0xFCF4)
#define ARCON                       read_xdata_u8(0xFCF6)
#define OPCON                       read_xdata_u8(0xFCF7)

#define P0INTE                      read_xdata_u8(0xFD00)
#define P1INTE                      read_xdata_u8(0xFD01)
#define P2INTE                      read_xdata_u8(0xFD02)
#define P3INTE                      read_xdata_u8(0xFD03)
#define P4INTE                      read_xdata_u8(0xFD04)
#define P5INTE                      read_xdata_u8(0xFD05)
#define P6INTE                      read_xdata_u8(0xFD06)
#define P7INTE                      read_xdata_u8(0xFD07)
#define P0INTF                      read_xdata_u8(0xFD10)
#define P1INTF                      read_xdata_u8(0xFD11)
#define P2INTF                      read_xdata_u8(0xFD12)
#define P3INTF                      read_xdata_u8(0xFD13)
#define P4INTF                      read_xdata_u8(0xFD14)
#define P5INTF                      read_xdata_u8(0xFD15)
#define P6INTF                      read_xdata_u8(0xFD16)
#define P7INTF                      read_xdata_u8(0xFD17)
#define P0IM0                       read_xdata_u8(0xFD20)
#define P1IM0                       read_xdata_u8(0xFD21)
#define P2IM0                       read_xdata_u8(0xFD22)
#define P3IM0                       read_xdata_u8(0xFD23)
#define P4IM0                       read_xdata_u8(0xFD24)
#define P5IM0                       read_xdata_u8(0xFD25)
#define P6IM0                       read_xdata_u8(0xFD26)
#define P7IM0                       read_xdata_u8(0xFD27)
#define P0IM1                       read_xdata_u8(0xFD30)
#define P1IM1                       read_xdata_u8(0xFD31)
#define P2IM1                       read_xdata_u8(0xFD32)
#define P3IM1                       read_xdata_u8(0xFD33)
#define P4IM1                       read_xdata_u8(0xFD34)
#define P5IM1                       read_xdata_u8(0xFD35)
#define P6IM1                       read_xdata_u8(0xFD36)
#define P7IM1                       read_xdata_u8(0xFD37)

#define P0WKUE                      read_xdata_u8(0xFD40)
#define P1WKUE                      read_xdata_u8(0xFD41)
#define P2WKUE                      read_xdata_u8(0xFD42)
#define P3WKUE                      read_xdata_u8(0xFD43)
#define P4WKUE                      read_xdata_u8(0xFD44)
#define P5WKUE                      read_xdata_u8(0xFD45)
#define P6WKUE                      read_xdata_u8(0xFD46)
#define P7WKUE                      read_xdata_u8(0xFD47)

#define PINIPL                      read_xdata_u8(0xFD60)
#define PINIPH                      read_xdata_u8(0xFD61)

#define CKSEL                       read_xdata_u8(0xFE00)
#define CLKDIV                      read_xdata_u8(0xFE01)
#define HIRCCR                      read_xdata_u8(0xFE02)
#define XOSCCR                      read_xdata_u8(0xFE03)
#define IRC32KCR                    read_xdata_u8(0xFE04)
#define MCLKOCR                     read_xdata_u8(0xFE05)
#define IRCDB                       read_xdata_u8(0xFE06)
#define IRC48MCR                    read_xdata_u8(0xFE07)

#define X32KCR                      read_xdata_u8(0xFE08)
#define SPFUNC                      read_xdata_u8(0xFE08)
#define RSTFLAG                     read_xdata_u8(0xFE09)

/* Pull-up registers: keep using the read/write macros which expand
   to lvalues (via pointer dereference). The SDCC __xdata + __at
   declaration variant caused syntax issues on some toolchains, so
   prefer the portable macro form to preserve assignability. */
#if 0
/* Disabled: volatile __xdata u8 declarations caused syntax errors */
#else
#define P0PU                        read_xdata_u8(0xFE10)
#define P1PU                        read_xdata_u8(0xFE11)
#define P2PU                        read_xdata_u8(0xFE12)
#define P3PU                        read_xdata_u8(0xFE13)
#define P4PU                        read_xdata_u8(0xFE14)
#define P5PU                        read_xdata_u8(0xFE15)
#define P6PU                        read_xdata_u8(0xFE16)
#define P7PU                        read_xdata_u8(0xFE17)
#endif

#define P0NCS                       read_xdata_u8(0xFE18)
#define P1NCS                       read_xdata_u8(0xFE19)
#define P2NCS                       read_xdata_u8(0xFE1A)
#define P3NCS                       read_xdata_u8(0xFE1B)
#define P4NCS                       read_xdata_u8(0xFE1C)
#define P5NCS                       read_xdata_u8(0xFE1D)
#define P6NCS                       read_xdata_u8(0xFE1E)
#define P7NCS                       read_xdata_u8(0xFE1F)

/* Drive/slew-rate registers: use macro form for portability */
#if 0
/* Disabled: volatile __xdata u8 declarations caused syntax errors */
#else
#define P0SR                        read_xdata_u8(0xFE20)
#define P1SR                        read_xdata_u8(0xFE21)
#define P2SR                        read_xdata_u8(0xFE22)
#define P3SR                        read_xdata_u8(0xFE23)
#define P4SR                        read_xdata_u8(0xFE24)
#define P5SR                        read_xdata_u8(0xFE25)
#define P6SR                        read_xdata_u8(0xFE26)
#define P7SR                        read_xdata_u8(0xFE27)
#endif

/* Drive strength/current registers: use macro form for portability */
#if 0
/* Disabled: volatile __xdata u8 declarations caused syntax errors */
#else
#define P0DR                        read_xdata_u8(0xFE28)
#define P1DR                        read_xdata_u8(0xFE29)
#define P2DR                        read_xdata_u8(0xFE2A)
#define P3DR                        read_xdata_u8(0xFE2B)
#define P4DR                        read_xdata_u8(0xFE2C)
#define P5DR                        read_xdata_u8(0xFE2D)
#define P6DR                        read_xdata_u8(0xFE2E)
#define P7DR                        read_xdata_u8(0xFE2F)
#endif

#define P0IE                        read_xdata_u8(0xFE30)
#define P1IE                        read_xdata_u8(0xFE31)
#define P2IE                        read_xdata_u8(0xFE32)
#define P3IE                        read_xdata_u8(0xFE33)
#define P4IE                        read_xdata_u8(0xFE34)
#define P5IE                        read_xdata_u8(0xFE35)
#define P6IE                        read_xdata_u8(0xFE36)
#define P7IE                        read_xdata_u8(0xFE37)

#define LCMIFCFG                    read_xdata_u8(0xFE50)
#define LCMIFCFG2                   read_xdata_u8(0xFE51)
#define LCMIFCR                     read_xdata_u8(0xFE52)
#define LCMIFSTA                    read_xdata_u8(0xFE53)
#define LCMIFDATL                   read_xdata_u8(0xFE54)
#define LCMIFDATH                   read_xdata_u8(0xFE55)


#define RTCCR                       read_xdata_u8(0xFE60)
#define RTCCFG                      read_xdata_u8(0xFE61)
#define RTCIEN                      read_xdata_u8(0xFE62)
#define RTCIF                       read_xdata_u8(0xFE63)
#define ALAHOUR                     read_xdata_u8(0xFE64)
#define ALAMIN                      read_xdata_u8(0xFE65)
#define ALASEC                      read_xdata_u8(0xFE66)
#define ALASSEC                     read_xdata_u8(0xFE67)
#define INIYEAR                     read_xdata_u8(0xFE68)
#define INIMONTH                    read_xdata_u8(0xFE69)
#define INIDAY                      read_xdata_u8(0xFE6A)
#define INIHOUR                     read_xdata_u8(0xFE6B)
#define INIMIN                      read_xdata_u8(0xFE6C)
#define INISEC                      read_xdata_u8(0xFE6D)
#define INISSEC                     read_xdata_u8(0xFE6E)
#define YEAR                        read_xdata_u8(0xFE70)
#define MONTH                       read_xdata_u8(0xFE71)
#define DAY                         read_xdata_u8(0xFE72)
#define HOUR                        read_xdata_u8(0xFE73)
#define MIN                         read_xdata_u8(0xFE74)
#define SEC                         read_xdata_u8(0xFE75)
#define SSEC                        read_xdata_u8(0xFE76)


#define I2CCFG                      read_xdata_u8(0xFE80)
#define I2CMSCR                     read_xdata_u8(0xFE81)
#define I2CMSST                     read_xdata_u8(0xFE82)
#define I2CSLCR                     read_xdata_u8(0xFE83)
#define I2CSLST                     read_xdata_u8(0xFE84)
#define I2CSLADR                    read_xdata_u8(0xFE85)
#define I2CTXD                      read_xdata_u8(0xFE86)
#define I2CRXD                      read_xdata_u8(0xFE87)
#define I2CMSAUX                    read_xdata_u8(0xFE88)

#define TM2PS                       read_xdata_u8(0xFEA2)
#define TM3PS                       read_xdata_u8(0xFEA3)
#define TM4PS                       read_xdata_u8(0xFEA4)

#define ADC_TIM                     read_xdata_u8(0xFEA8)
#define T3T4PIN                     read_xdata_u8(0xFEAC)
#define ADCEXCFG                    read_xdata_u8(0xFEAD)
#define CMPEXCFG                    read_xdata_u8(0xFEAE)

#define PWMA_ETRPS                  read_xdata_u8(0xFEB0)
#define PWMA_ENO                    read_xdata_u8(0xFEB1)
#define PWMA_PS                     read_xdata_u8(0xFEB2)
#define PWMA_IOAUX                  read_xdata_u8(0xFEB3)
#define PWMB_ETRPS                  read_xdata_u8(0xFEB4)
#define PWMB_ENO                    read_xdata_u8(0xFEB5)
#define PWMB_PS                     read_xdata_u8(0xFEB6)
#define PWMB_IOAUX                  read_xdata_u8(0xFEB7)
#define PWMA_CR1                    read_xdata_u8(0xFEC0)
#define PWMA_CR2                    read_xdata_u8(0xFEC1)
#define PWMA_SMCR                   read_xdata_u8(0xFEC2)
#define PWMA_ETR                    read_xdata_u8(0xFEC3)
#define PWMA_IER                    read_xdata_u8(0xFEC4)
#define PWMA_SR1                    read_xdata_u8(0xFEC5)
#define PWMA_SR2                    read_xdata_u8(0xFEC6)
#define PWMA_EGR                    read_xdata_u8(0xFEC7)
#define PWMA_CCMR1                  read_xdata_u8(0xFEC8)
#define PWMA_CCMR2                  read_xdata_u8(0xFEC9)
#define PWMA_CCMR3                  read_xdata_u8(0xFECA)
#define PWMA_CCMR4                  read_xdata_u8(0xFECB)
#define PWMA_CCER1                  read_xdata_u8(0xFECC)
#define PWMA_CCER2                  read_xdata_u8(0xFECD)
#define PWMA_CNTR                   read_xdata_u16(0xFECE)
#define PWMA_CNTRH                  read_xdata_u8(0xFECE)
#define PWMA_CNTRL                  read_xdata_u8(0xFECF)
#define PWMA_PSCR                   read_xdata_u16(0xFED0)
#define PWMA_PSCRH                  read_xdata_u8(0xFED0)
#define PWMA_PSCRL                  read_xdata_u8(0xFED1)
#define PWMA_ARR                    read_xdata_u16(0xFED2)
#define PWMA_ARRH                   read_xdata_u8(0xFED2)
#define PWMA_ARRL                   read_xdata_u8(0xFED3)
#define PWMA_RCR                    read_xdata_u8(0xFED4)
#define PWMA_CCR1                   read_xdata_u16(0xFED5)
#define PWMA_CCR1H                  read_xdata_u8(0xFED5)
#define PWMA_CCR1L                  read_xdata_u8(0xFED6)
#define PWMA_CCR2                   read_xdata_u16(0xFED7)
#define PWMA_CCR2H                  read_xdata_u8(0xFED7)
#define PWMA_CCR2L                  read_xdata_u8(0xFED8)
#define PWMA_CCR3                   read_xdata_u16(0xFED9)
#define PWMA_CCR3H                  read_xdata_u8(0xFED9)
#define PWMA_CCR3L                  read_xdata_u8(0xFEDA)
#define PWMA_CCR4                   read_xdata_u16(0xFEDB)
#define PWMA_CCR4H                  read_xdata_u8(0xFEDB)
#define PWMA_CCR4L                  read_xdata_u8(0xFEDC)
#define PWMA_BKR                    read_xdata_u8(0xFEDD)
#define PWMA_DTR                    read_xdata_u8(0xFEDE)
#define PWMA_OISR                   read_xdata_u8(0xFEDF)
#define PWMB_CR1                    read_xdata_u8(0xFEE0)
#define PWMB_CR2                    read_xdata_u8(0xFEE1)
#define PWMB_SMCR                   read_xdata_u8(0xFEE2)
#define PWMB_ETR                    read_xdata_u8(0xFEE3)
#define PWMB_IER                    read_xdata_u8(0xFEE4)
#define PWMB_SR1                    read_xdata_u8(0xFEE5)
#define PWMB_SR2                    read_xdata_u8(0xFEE6)
#define PWMB_EGR                    read_xdata_u8(0xFEE7)
#define PWMB_CCMR1                  read_xdata_u8(0xFEE8)
#define PWMB_CCMR2                  read_xdata_u8(0xFEE9)
#define PWMB_CCMR3                  read_xdata_u8(0xFEEA)
#define PWMB_CCMR4                  read_xdata_u8(0xFEEB)
#define PWMB_CCER1                  read_xdata_u8(0xFEEC)
#define PWMB_CCER2                  read_xdata_u8(0xFEED)
#define PWMB_CNTR                   read_xdata_u16(0xFEEE)
#define PWMB_CNTRH                  read_xdata_u8(0xFEEE)
#define PWMB_CNTRL                  read_xdata_u8(0xFEEF)
#define PWMB_PSCR                   read_xdata_u16(0xFEF0)
#define PWMB_PSCRH                  read_xdata_u8(0xFEF0)
#define PWMB_PSCRL                  read_xdata_u8(0xFEF1)
#define PWMB_ARR                    read_xdata_u16(0xFEF2)
#define PWMB_ARRH                   read_xdata_u8(0xFEF2)
#define PWMB_ARRL                   read_xdata_u8(0xFEF3)
#define PWMB_RCR                    read_xdata_u8(0xFEF4)
#define PWMB_CCR5                   read_xdata_u16(0xFEF5)
#define PWMB_CCR5H                  read_xdata_u8(0xFEF5)
#define PWMB_CCR5L                  read_xdata_u8(0xFEF6)
#define PWMB_CCR6                   read_xdata_u16(0xFEF7)
#define PWMB_CCR6H                  read_xdata_u8(0xFEF7)
#define PWMB_CCR6L                  read_xdata_u8(0xFEF8)
#define PWMB_CCR7                   read_xdata_u16(0xFEF9)
#define PWMB_CCR7H                  read_xdata_u8(0xFEF9)
#define PWMB_CCR7L                  read_xdata_u8(0xFEFA)
#define PWMB_CCR8                   read_xdata_u16(0xFEFB)
#define PWMB_CCR8H                  read_xdata_u8(0xFEFB)
#define PWMB_CCR8L                  read_xdata_u8(0xFEFC)
#define PWMB_BKR                    read_xdata_u8(0xFEFD)
#define PWMB_DTR                    read_xdata_u8(0xFEFE)
#define PWMB_OISR                   read_xdata_u8(0xFEFF)

#define PWM_P0_C                    read_xdata_u16(0xFF00)
#define PWM_P0_CH                   read_xdata_u8(0xFF00)
#define PWM_P0_CL                   read_xdata_u8(0xFF01)
#define PWM_P0_CKS                  read_xdata_u8(0xFF02)
#define PWM_P0_TADC                 read_xdata_u16(0xFF03)
#define PWM_P0_TADCH                read_xdata_u8(0xFF03)
#define PWM_P0_TADCL                read_xdata_u8(0xFF04)
#define PWM_P0_IF                   read_xdata_u8(0xFF05)
#define PWM_P0_FDCR                 read_xdata_u8(0xFF06)
#define PWM_P00_T1                  read_xdata_u16(0xFF10)
#define PWM_P00_T1H                 read_xdata_u8(0xFF10)
#define PWM_P00_T1L                 read_xdata_u8(0xFF11)
#define PWM_P00_T2                  read_xdata_u16(0xFF12)
#define PWM_P00_T2H                 read_xdata_u8(0xFF12)
#define PWM_P00_T2L                 read_xdata_u8(0xFF13)
#define PWM_P00_CR                  read_xdata_u8(0xFF14)
#define PWM_P00_HLD                 read_xdata_u8(0xFF15)
#define PWM_P01_T1                  read_xdata_u16(0xFF18)
#define PWM_P01_T1H                 read_xdata_u8(0xFF18)
#define PWM_P01_T1L                 read_xdata_u8(0xFF19)
#define PWM_P01_T2                  read_xdata_u16(0xFF1A)
#define PWM_P01_T2H                 read_xdata_u8(0xFF1A)
#define PWM_P01_T2L                 read_xdata_u8(0xFF1B)
#define PWM_P01_CR                  read_xdata_u8(0xFF1C)
#define PWM_P01_HLD                 read_xdata_u8(0xFF1D)
#define PWM_P02_T1                  read_xdata_u16(0xFF20)
#define PWM_P02_T1H                 read_xdata_u8(0xFF20)
#define PWM_P02_T1L                 read_xdata_u8(0xFF21)
#define PWM_P02_T2                  read_xdata_u16(0xFF22)
#define PWM_P02_T2H                 read_xdata_u8(0xFF22)
#define PWM_P02_T2L                 read_xdata_u8(0xFF23)
#define PWM_P02_CR                  read_xdata_u8(0xFF24)
#define PWM_P02_HLD                 read_xdata_u8(0xFF25)
#define PWM_P03_T1                  read_xdata_u16(0xFF28)
#define PWM_P03_T1H                 read_xdata_u8(0xFF28)
#define PWM_P03_T1L                 read_xdata_u8(0xFF29)
#define PWM_P03_T2                  read_xdata_u16(0xFF2A)
#define PWM_P03_T2H                 read_xdata_u8(0xFF2A)
#define PWM_P03_T2L                 read_xdata_u8(0xFF2B)
#define PWM_P03_CR                  read_xdata_u8(0xFF2C)
#define PWM_P03_HLD                 read_xdata_u8(0xFF2D)
#define PWM_P04_T1                  read_xdata_u16(0xFF30)
#define PWM_P04_T1H                 read_xdata_u8(0xFF30)
#define PWM_P04_T1L                 read_xdata_u8(0xFF31)
#define PWM_P04_T2                  read_xdata_u16(0xFF32)
#define PWM_P04_T2H                 read_xdata_u8(0xFF32)
#define PWM_P04_T2L                 read_xdata_u8(0xFF33)
#define PWM_P04_CR                  read_xdata_u8(0xFF34)
#define PWM_P04_HLD                 read_xdata_u8(0xFF35)
#define PWM_P05_T1                  read_xdata_u16(0xFF38)
#define PWM_P05_T1H                 read_xdata_u8(0xFF38)
#define PWM_P05_T1L                 read_xdata_u8(0xFF39)
#define PWM_P05_T2                  read_xdata_u16(0xFF3A)
#define PWM_P05_T2H                 read_xdata_u8(0xFF3A)
#define PWM_P05_T2L                 read_xdata_u8(0xFF3B)
#define PWM_P05_CR                  read_xdata_u8(0xFF3C)
#define PWM_P05_HLD                 read_xdata_u8(0xFF3D)
#define PWM_P06_T1                  read_xdata_u16(0xFF40)
#define PWM_P06_T1H                 read_xdata_u8(0xFF40)
#define PWM_P06_T1L                 read_xdata_u8(0xFF41)
#define PWM_P06_T2                  read_xdata_u16(0xFF42)
#define PWM_P06_T2H                 read_xdata_u8(0xFF42)
#define PWM_P06_T2L                 read_xdata_u8(0xFF43)
#define PWM_P06_CR                  read_xdata_u8(0xFF44)
#define PWM_P06_HLD                 read_xdata_u8(0xFF45)
#define PWM_P07_T1                  read_xdata_u16(0xFF48)
#define PWM_P07_T1H                 read_xdata_u8(0xFF48)
#define PWM_P07_T1L                 read_xdata_u8(0xFF49)
#define PWM_P07_T2                  read_xdata_u16(0xFF4A)
#define PWM_P07_T2H                 read_xdata_u8(0xFF4A)
#define PWM_P07_T2L                 read_xdata_u8(0xFF4B)
#define PWM_P07_CR                  read_xdata_u8(0xFF4C)
#define PWM_P07_HLD                 read_xdata_u8(0xFF4D)
#define PWM_P1_C                    read_xdata_u16(0xFF50)
#define PWM_P1_CH                   read_xdata_u8(0xFF50)
#define PWM_P1_CL                   read_xdata_u8(0xFF51)
#define PWM_P1_CKS                  read_xdata_u8(0xFF52)
#define PWM_P1_IF                   read_xdata_u8(0xFF55)
#define PWM_P1_FDCR                 read_xdata_u8(0xFF56)
#define PWM_P10_T1                  read_xdata_u16(0xFF60)
#define PWM_P10_T1H                 read_xdata_u8(0xFF60)
#define PWM_P10_T1L                 read_xdata_u8(0xFF61)
#define PWM_P10_T2                  read_xdata_u16(0xFF62)
#define PWM_P10_T2H                 read_xdata_u8(0xFF62)
#define PWM_P10_T2L                 read_xdata_u8(0xFF63)
#define PWM_P10_CR                  read_xdata_u8(0xFF64)
#define PWM_P10_HLD                 read_xdata_u8(0xFF65)
#define PWM_P11_T1                  read_xdata_u16(0xFF68)
#define PWM_P11_T1H                 read_xdata_u8(0xFF68)
#define PWM_P11_T1L                 read_xdata_u8(0xFF69)
#define PWM_P11_T2                  read_xdata_u16(0xFF6A)
#define PWM_P11_T2H                 read_xdata_u8(0xFF6A)
#define PWM_P11_T2L                 read_xdata_u8(0xFF6B)
#define PWM_P11_CR                  read_xdata_u8(0xFF6C)
#define PWM_P11_HLD                 read_xdata_u8(0xFF6D)
#define PWM_P12_T1                  read_xdata_u16(0xFF70)
#define PWM_P12_T1H                 read_xdata_u8(0xFF70)
#define PWM_P12_T1L                 read_xdata_u8(0xFF71)
#define PWM_P12_T2                  read_xdata_u16(0xFF72)
#define PWM_P12_T2H                 read_xdata_u8(0xFF72)
#define PWM_P12_T2L                 read_xdata_u8(0xFF73)
#define PWM_P12_CR                  read_xdata_u8(0xFF74)
#define PWM_P12_HLD                 read_xdata_u8(0xFF75)
#define PWM_P13_T1                  read_xdata_u16(0xFF78)
#define PWM_P13_T1H                 read_xdata_u8(0xFF78)
#define PWM_P13_T1L                 read_xdata_u8(0xFF79)
#define PWM_P13_T2                  read_xdata_u16(0xFF7A)
#define PWM_P13_T2H                 read_xdata_u8(0xFF7A)
#define PWM_P13_T2L                 read_xdata_u8(0xFF7B)
#define PWM_P13_CR                  read_xdata_u8(0xFF7C)
#define PWM_P13_HLD                 read_xdata_u8(0xFF7D)
#define PWM_P14_T1                  read_xdata_u16(0xFF80)
#define PWM_P14_T1H                 read_xdata_u8(0xFF80)
#define PWM_P14_T1L                 read_xdata_u8(0xFF81)
#define PWM_P14_T2                  read_xdata_u16(0xFF82)
#define PWM_P14_T2H                 read_xdata_u8(0xFF82)
#define PWM_P14_T2L                 read_xdata_u8(0xFF83)
#define PWM_P14_CR                  read_xdata_u8(0xFF84)
#define PWM_P14_HLD                 read_xdata_u8(0xFF85)
#define PWM_P15_T1                  read_xdata_u16(0xFF88)
#define PWM_P15_T1H                 read_xdata_u8(0xFF88)
#define PWM_P15_T1L                 read_xdata_u8(0xFF89)
#define PWM_P15_T2                  read_xdata_u16(0xFF8A)
#define PWM_P15_T2H                 read_xdata_u8(0xFF8A)
#define PWM_P15_T2L                 read_xdata_u8(0xFF8B)
#define PWM_P15_CR                  read_xdata_u8(0xFF8C)
#define PWM_P15_HLD                 read_xdata_u8(0xFF8D)
#define PWM_P16_T1                  read_xdata_u16(0xFF90)
#define PWM_P16_T1H                 read_xdata_u8(0xFF90)
#define PWM_P16_T1L                 read_xdata_u8(0xFF91)
#define PWM_P16_T2                  read_xdata_u16(0xFF92)
#define PWM_P16_T2H                 read_xdata_u8(0xFF92)
#define PWM_P16_T2L                 read_xdata_u8(0xFF93)
#define PWM_P16_CR                  read_xdata_u8(0xFF94)
#define PWM_P16_HLD                 read_xdata_u8(0xFF95)
#define PWM_P17_T1                  read_xdata_u16(0xFF98)
#define PWM_P17_T1H                 read_xdata_u8(0xFF98)
#define PWM_P17_T1L                 read_xdata_u8(0xFF99)
#define PWM_P17_T2                  read_xdata_u16(0xFF9A)
#define PWM_P17_T2H                 read_xdata_u8(0xFF9A)
#define PWM_P17_T2L                 read_xdata_u8(0xFF9B)
#define PWM_P17_CR                  read_xdata_u8(0xFF9C)
#define PWM_P17_HLD                 read_xdata_u8(0xFF9D)
#define PWM_P2_C                    read_xdata_u16(0xFFA0)
#define PWM_P2_CH                   read_xdata_u8(0xFFA0)
#define PWM_P2_CL                   read_xdata_u8(0xFFA1)
#define PWM_P2_CKS                  read_xdata_u8(0xFFA2)
#define PWM_P2_TADC                 read_xdata_u16(0xFFA3)
#define PWM_P2_TADCH                read_xdata_u8(0xFFA3)
#define PWM_P2_TADCL                read_xdata_u8(0xFFA4)
#define PWM_P2_IF                   read_xdata_u8(0xFFA5)
#define PWM_P2_FDCR                 read_xdata_u8(0xFFA6)
#define PWM_P20_T1                  read_xdata_u16(0xFFB0)
#define PWM_P20_T1H                 read_xdata_u8(0xFFB0)
#define PWM_P20_T1L                 read_xdata_u8(0xFFB1)
#define PWM_P20_T2                  read_xdata_u16(0xFFB2)
#define PWM_P20_T2H                 read_xdata_u8(0xFFB2)
#define PWM_P20_T2L                 read_xdata_u8(0xFFB3)
#define PWM_P20_CR                  read_xdata_u8(0xFFB4)
#define PWM_P20_HLD                 read_xdata_u8(0xFFB5)
#define PWM_P21_T1                  read_xdata_u16(0xFFB8)
#define PWM_P21_T1H                 read_xdata_u8(0xFFB8)
#define PWM_P21_T1L                 read_xdata_u8(0xFFB9)
#define PWM_P21_T2                  read_xdata_u16(0xFFBA)
#define PWM_P21_T2H                 read_xdata_u8(0xFFBA)
#define PWM_P21_T2L                 read_xdata_u8(0xFFBB)
#define PWM_P21_CR                  read_xdata_u8(0xFFBC)
#define PWM_P21_HLD                 read_xdata_u8(0xFFBD)
#define PWM_P22_T1                  read_xdata_u16(0xFFC0)
#define PWM_P22_T1H                 read_xdata_u8(0xFFC0)
#define PWM_P22_T1L                 read_xdata_u8(0xFFC1)
#define PWM_P22_T2                  read_xdata_u16(0xFFC2)
#define PWM_P22_T2H                 read_xdata_u8(0xFFC2)
#define PWM_P22_T2L                 read_xdata_u8(0xFFC3)
#define PWM_P22_CR                  read_xdata_u8(0xFFC4)
#define PWM_P22_HLD                 read_xdata_u8(0xFFC5)
#define PWM_P23_T1                  read_xdata_u16(0xFFC8)
#define PWM_P23_T1H                 read_xdata_u8(0xFFC8)
#define PWM_P23_T1L                 read_xdata_u8(0xFFC9)
#define PWM_P23_T2                  read_xdata_u16(0xFFCA)
#define PWM_P23_T2H                 read_xdata_u8(0xFFCA)
#define PWM_P23_T2L                 read_xdata_u8(0xFFCB)
#define PWM_P23_CR                  read_xdata_u8(0xFFCC)
#define PWM_P23_HLD                 read_xdata_u8(0xFFCD)
#define PWM_P24_T1                  read_xdata_u16(0xFFD0)
#define PWM_P24_T1H                 read_xdata_u8(0xFFD0)
#define PWM_P24_T1L                 read_xdata_u8(0xFFD1)
#define PWM_P24_T2                  read_xdata_u16(0xFFD2)
#define PWM_P24_T2H                 read_xdata_u8(0xFFD2)
#define PWM_P24_T2L                 read_xdata_u8(0xFFD3)
#define PWM_P24_CR                  read_xdata_u8(0xFFD4)
#define PWM_P24_HLD                 read_xdata_u8(0xFFD5)
#define PWM_P25_T1                  read_xdata_u16(0xFFD8)
#define PWM_P25_T1H                 read_xdata_u8(0xFFD8)
#define PWM_P25_T1L                 read_xdata_u8(0xFFD9)
#define PWM_P25_T2                  read_xdata_u16(0xFFDA)
#define PWM_P25_T2H                 read_xdata_u8(0xFFDA)
#define PWM_P25_T2L                 read_xdata_u8(0xFFDB)
#define PWM_P25_CR                  read_xdata_u8(0xFFDC)
#define PWM_P25_HLD                 read_xdata_u8(0xFFDD)
#define PWM_P26_T1                  read_xdata_u16(0xFFE0)
#define PWM_P26_T1H                 read_xdata_u8(0xFFE0)
#define PWM_P26_T1L                 read_xdata_u8(0xFFE1)
#define PWM_P26_T2                  read_xdata_u16(0xFFE2)
#define PWM_P26_T2H                 read_xdata_u8(0xFFE2)
#define PWM_P26_T2L                 read_xdata_u8(0xFFE3)
#define PWM_P26_CR                  read_xdata_u8(0xFFE4)
#define PWM_P26_HLD                 read_xdata_u8(0xFFE5)
#define PWM_P27_T1                  read_xdata_u16(0xFFE8)
#define PWM_P27_T1H                 read_xdata_u8(0xFFE8)
#define PWM_P27_T1L                 read_xdata_u8(0xFFE9)
#define PWM_P27_T2                  read_xdata_u16(0xFFEA)
#define PWM_P27_T2H                 read_xdata_u8(0xFFEA)
#define PWM_P27_T2L                 read_xdata_u8(0xFFEB)
#define PWM_P27_CR                  read_xdata_u8(0xFFEC)
#define PWM_P27_HLD                 read_xdata_u8(0xFFED)
#if     (ECBM_MCU==0x2815C4)
#define PWM_C                       read_xdata_u16(0xFF00)
#define PWM_CH                      read_xdata_u8(0xFF00)
#define PWM_CL                      read_xdata_u8(0xFF01)
#define PWM_CKS                     read_xdata_u8(0xFF02)
#define PWM_TADC                    read_xdata_u16(0xFF03)
#define PWM_TADCH                   read_xdata_u8(0xFF03)
#define PWM_TADCL                   read_xdata_u8(0xFF04)
#define PWM_IF                      read_xdata_u8(0xFF05)
#define PWM_FDCR                    read_xdata_u8(0xFF06)
#define PWM_DELSEL                  read_xdata_u8(0xFF07)
#define PWM_CH0_T1                  read_xdata_u16(0xFF10)
#define PWM_CH0_T1H                 read_xdata_u8(0xFF10)
#define PWM_CH0_T1L                 read_xdata_u8(0xFF11)
#define PWM_CH0_T2                  read_xdata_u16(0xFF12)
#define PWM_CH0_T2H                 read_xdata_u8(0xFF12)
#define PWM_CH0_T2L                 read_xdata_u8(0xFF13)
#define PWM_CH0_CR                  read_xdata_u8(0xFF14)
#define PWM_CH0_HLD                 read_xdata_u8(0xFF15)
#define PWM_CH1_T1                  read_xdata_u16(0xFF18)
#define PWM_CH1_T1H                 read_xdata_u8(0xFF18)
#define PWM_CH1_T1L                 read_xdata_u8(0xFF19)
#define PWM_CH1_T2                  read_xdata_u16(0xFF1A)
#define PWM_CH1_T2H                 read_xdata_u8(0xFF1A)
#define PWM_CH1_T2L                 read_xdata_u8(0xFF1B)
#define PWM_CH1_CR                  read_xdata_u8(0xFF1C)
#define PWM_CH1_HLD                 read_xdata_u8(0xFF1D)
#define PWM_CH2_T1                  read_xdata_u16(0xFF20)
#define PWM_CH2_T1H                 read_xdata_u8(0xFF20)
#define PWM_CH2_T1L                 read_xdata_u8(0xFF21)
#define PWM_CH2_T2                  read_xdata_u16(0xFF22)
#define PWM_CH2_T2H                 read_xdata_u8(0xFF22)
#define PWM_CH2_T2L                 read_xdata_u8(0xFF23)
#define PWM_CH2_CR                  read_xdata_u8(0xFF24)
#define PWM_CH2_HLD                 read_xdata_u8(0xFF25)
#define PWM_CH3_T1                  read_xdata_u16(0xFF28)
#define PWM_CH3_T1H                 read_xdata_u8(0xFF28)
#define PWM_CH3_T1L                 read_xdata_u8(0xFF29)
#define PWM_CH3_T2                  read_xdata_u16(0xFF2A)
#define PWM_CH3_T2H                 read_xdata_u8(0xFF2A)
#define PWM_CH3_T2L                 read_xdata_u8(0xFF2B)
#define PWM_CH3_CR                  read_xdata_u8(0xFF2C)
#define PWM_CH3_HLD                 read_xdata_u8(0xFF2D)
#define PWM_CH4_T1                  read_xdata_u16(0xFF30)
#define PWM_CH4_T1H                 read_xdata_u8(0xFF30)
#define PWM_CH4_T1L                 read_xdata_u8(0xFF31)
#define PWM_CH4_T2                  read_xdata_u16(0xFF32)
#define PWM_CH4_T2H                 read_xdata_u8(0xFF32)
#define PWM_CH4_T2L                 read_xdata_u8(0xFF33)
#define PWM_CH4_CR                  read_xdata_u8(0xFF34)
#define PWM_CH4_HLD                 read_xdata_u8(0xFF35)
#define PWM_CH5_T1                  read_xdata_u16(0xFF38)
#define PWM_CH5_T1H                 read_xdata_u8(0xFF38)
#define PWM_CH5_T1L                 read_xdata_u8(0xFF39)
#define PWM_CH5_T2                  read_xdata_u16(0xFF3A)
#define PWM_CH5_T2H                 read_xdata_u8(0xFF3A)
#define PWM_CH5_T2L                 read_xdata_u8(0xFF3B)
#define PWM_CH5_CR                  read_xdata_u8(0xFF3C)
#define PWM_CH5_HLD                 read_xdata_u8(0xFF3D)
#define PWM_CH6_T1                  read_xdata_u16(0xFF40)
#define PWM_CH6_T1H                 read_xdata_u8(0xFF40)
#define PWM_CH6_T1L                 read_xdata_u8(0xFF41)
#define PWM_CH6_T2                  read_xdata_u16(0xFF42)
#define PWM_CH6_T2H                 read_xdata_u8(0xFF42)
#define PWM_CH6_T2L                 read_xdata_u8(0xFF43)
#define PWM_CH6_CR                  read_xdata_u8(0xFF44)
#define PWM_CH6_HLD                 read_xdata_u8(0xFF45)
#define PWM_CH7_T1                  read_xdata_u16(0xFF48)
#define PWM_CH7_T1H                 read_xdata_u8(0xFF48)
#define PWM_CH7_T1L                 read_xdata_u8(0xFF49)
#define PWM_CH7_T2                  read_xdata_u16(0xFF4A)
#define PWM_CH7_T2H                 read_xdata_u8(0xFF4A)
#define PWM_CH7_T2L                 read_xdata_u8(0xFF4B)
#define PWM_CH7_CR                  read_xdata_u8(0xFF4C)
#define PWM_CH7_HLD                 read_xdata_u8(0xFF4D)
#endif
#if     ((ECBM_MCU&0xF0F000)==0x200000)
#define PWM_C                       read_xdata_u16(0xFFF0)
#define PWM_CH                      read_xdata_u8(0xFFF0)
#define PWM_CL                      read_xdata_u8(0xFFF1)
#define PWM_CKS                     read_xdata_u8(0xFFF2)
#define PWM_TADCP                   read_xdata_u8(0xFFF3)
#define PWM_TADCPH                  read_xdata_u8(0xFFF3)
#define PWM_TADCPL                  read_xdata_u8(0xFFF4)
#define PWM_CH0_T1                  read_xdata_u16(0xFF00)
#define PWM_CH0_T1H                 read_xdata_u8(0xFF00)
#define PWM_CH0_T1L                 read_xdata_u8(0xFF01)
#define PWM_CH0_T2                  read_xdata_u16(0xFF02)
#define PWM_CH0_T2H                 read_xdata_u8(0xFF02)
#define PWM_CH0_T2L                 read_xdata_u8(0xFF03)
#define PWM_CH0_CR                  read_xdata_u8(0xFF04)
#define PWM_CH0_HLD                 read_xdata_u8(0xFF05)
#define PWM_CH1_T1                  read_xdata_u16(0xFF10)
#define PWM_CH1_T1H                 read_xdata_u8(0xFF10)
#define PWM_CH1_T1L                 read_xdata_u8(0xFF11)
#define PWM_CH1_T2                  read_xdata_u16(0xFF12)
#define PWM_CH1_T2H                 read_xdata_u8(0xFF12)
#define PWM_CH1_T2L                 read_xdata_u8(0xFF13)
#define PWM_CH1_CR                  read_xdata_u8(0xFF14)
#define PWM_CH1_HLD                 read_xdata_u8(0xFF15)
#define PWM_CH2_T1                  read_xdata_u16(0xFF20)
#define PWM_CH2_T1H                 read_xdata_u8(0xFF20)
#define PWM_CH2_T1L                 read_xdata_u8(0xFF21)
#define PWM_CH2_T2                  read_xdata_u16(0xFF22)
#define PWM_CH2_T2H                 read_xdata_u8(0xFF22)
#define PWM_CH2_T2L                 read_xdata_u8(0xFF23)
#define PWM_CH2_CR                  read_xdata_u8(0xFF24)
#define PWM_CH2_HLD                 read_xdata_u8(0xFF25)
#define PWM_CH3_T1                  read_xdata_u16(0xFF30)
#define PWM_CH3_T1H                 read_xdata_u8(0xFF30)
#define PWM_CH3_T1L                 read_xdata_u8(0xFF31)
#define PWM_CH3_T2                  read_xdata_u16(0xFF32)
#define PWM_CH3_T2H                 read_xdata_u8(0xFF32)
#define PWM_CH3_T2L                 read_xdata_u8(0xFF33)
#define PWM_CH3_CR                  read_xdata_u8(0xFF34)
#define PWM_CH3_HLD                 read_xdata_u8(0xFF35)
#define PWM_CH4_T1                  read_xdata_u16(0xFF40)
#define PWM_CH4_T1H                 read_xdata_u8(0xFF40)
#define PWM_CH4_T1L                 read_xdata_u8(0xFF41)
#define PWM_CH4_T2                  read_xdata_u16(0xFF42)
#define PWM_CH4_T2H                 read_xdata_u8(0xFF42)
#define PWM_CH4_T2L                 read_xdata_u8(0xFF43)
#define PWM_CH4_CR                  read_xdata_u8(0xFF44)
#define PWM_CH4_HLD                 read_xdata_u8(0xFF45)
#define PWM_CH5_T1                  read_xdata_u16(0xFF50)
#define PWM_CH5_T1H                 read_xdata_u8(0xFF50)
#define PWM_CH5_T1L                 read_xdata_u8(0xFF51)
#define PWM_CH5_T2                  read_xdata_u16(0xFF52)
#define PWM_CH5_T2H                 read_xdata_u8(0xFF52)
#define PWM_CH5_T2L                 read_xdata_u8(0xFF53)
#define PWM_CH5_CR                  read_xdata_u8(0xFF54)
#define PWM_CH5_HLD                 read_xdata_u8(0xFF55)
#define PWM_CH6_T1                  read_xdata_u16(0xFF60)
#define PWM_CH6_T1H                 read_xdata_u8(0xFF60)
#define PWM_CH6_T1L                 read_xdata_u8(0xFF61)
#define PWM_CH6_T2                  read_xdata_u16(0xFF62)
#define PWM_CH6_T2H                 read_xdata_u8(0xFF62)
#define PWM_CH6_T2L                 read_xdata_u8(0xFF63)
#define PWM_CH6_CR                  read_xdata_u8(0xFF64)
#define PWM_CH6_HLD                 read_xdata_u8(0xFF65)
#define PWM_CH7_T1                  read_xdata_u16(0xFF70)
#define PWM_CH7_T1H                 read_xdata_u8(0xFF70)
#define PWM_CH7_T1L                 read_xdata_u8(0xFF71)
#define PWM_CH7_T2                  read_xdata_u16(0xFF72)
#define PWM_CH7_T2H                 read_xdata_u8(0xFF72)
#define PWM_CH7_T2L                 read_xdata_u8(0xFF73)
#define PWM_CH7_CR                  read_xdata_u8(0xFF74)
#define PWM_CH7_HLD                 read_xdata_u8(0xFF75)
#endif
#endif


#define WDT_FLAG                    0x80
#define EN_WDT                      0x20
#define CLR_WDT                     0x10
#define IDL_WDT                     0x08

#define WDT_POWER_ON                REG_SET_BIT(WDT_CONTR,EN_WDT)
#define WDT_CLR                     REG_SET_BIT(WDT_CONTR,CLR_WDT)
#define WDT_SET_IDLE_ENABLE         REG_SET_BIT(WDT_CONTR,IDL_WDT)
#define WDT_SET_IDLE_DISABLE        REG_RESET_BIT(WDT_CONTR,IDL_WDT)
#define WDT_SET_SCALE(value)        REG_IN_MASK(WDT_CONTR,0x07,value)
#define WDT_GET_FLAG                (WDT_CONTR & WDT_FLAG)

#define WDT_SET_REG_CONTR(value)    do{WDT_CONTR=(u8)(value);}while(0)
#define WDT_GET_REG_CONTR           (WDT_CONTR)





#define PX0H                        0x01

#define EXTI0_ENABLE                do{EX0=1;}while(0)
#define EXTI0_DISABLE               do{EX0=0;}while(0)
#define EXTI0_SET_MODE_UP_DOWN      do{IT0=0;}while(0)
#define EXTI0_SET_MODE_DOWN         do{IT0=1;}while(0)
#define EXTI0_SET_IT_FLAG           do{IE0=1;}while(0)
#define EXTI0_CLS_IT_FLAG           do{IE0=0;}while(0)
#define EXTI0_GET_IT_FLAG           (IE0)
#define EXTI0_SET_IO_HIGH           do{P32=1;}while(0)
#define EXTI0_GET_IO                (P32)
#define EXTI0_SET_IT_PRIORITY_0     do{IPH&=~PX0H;IP&=~PX0H;}while(0)
#define EXTI0_SET_IT_PRIORITY_1     do{IPH&=~PX0H;IP|= PX0H;}while(0)
#define EXTI0_SET_IT_PRIORITY_2     do{IPH|= PX0H;IP&=~PX0H;}while(0)
#define EXTI0_SET_IT_PRIORITY_3     do{IPH|= PX0H;IP|= PX0H;}while(0)

#define EXTI0_IT_NUM                interrupt 0





#define PX1H                        0x04

#define EXTI1_ENABLE                do{EX1=1;}while(0)
#define EXTI1_DISABLE               do{EX1=0;}while(0)
#define EXTI1_SET_MODE_UP_DOWN      do{IT1=0;}while(0)
#define EXTI1_SET_MODE_DOWN         do{IT1=1;}while(0)
#define EXTI1_SET_IT_FLAG           do{IE1=1;}while(0)
#define EXTI1_CLS_IT_FLAG           do{IE1=0;}while(0)
#define EXTI1_GET_IT_FLAG           (IE1)
#define EXTI1_SET_IO_HIGH           do{P33=1;}while(0)
#define EXTI1_GET_IO                (P33)
#define EXTI1_SET_IT_PRIORITY_0     do{IPH&=~PX1H;IP&=~PX1H;}while(0)
#define EXTI1_SET_IT_PRIORITY_1     do{IPH&=~PX1H;IP|= PX1H;}while(0)
#define EXTI1_SET_IT_PRIORITY_2     do{IPH|= PX1H;IP&=~PX1H;}while(0)
#define EXTI1_SET_IT_PRIORITY_3     do{IPH|= PX1H;IP|= PX1H;}while(0)

#define EXTI1_IT_NUM                interrupt 2

#define EX2                         0x10
#define INT2IF                      0x10

#define EXTI2_ENABLE                REG_SET_BIT(INTCLKO,EX2)
#define EXTI2_DISABLE               REG_RESET_BIT(INTCLKO,EX2)
#define EXTI2_SET_IT_FLAG           REG_SET_BIT(AUXINTIF,INT2IF)
#define EXTI2_CLS_IT_FLAG           REG_RESET_BIT(AUXINTIF,INT2IF)
#define EXTI2_GET_IT_FLAG           (AUXINTIF & INT2IF)
#define EXTI2_SET_IO_HIGH           do{P36=1;}while(0)
#define EXTI2_GET_IO                (P36)

#define EXTI2_IT_NUM                interrupt 10

#define EX3                         0x20
#define INT3IF                      0x20

#define EXTI3_ENABLE                REG_SET_BIT(INTCLKO,EX3)
#define EXTI3_DISABLE               REG_RESET_BIT(INTCLKO,EX3)
#define EXTI3_SET_IT_FLAG           REG_SET_BIT(AUXINTIF,INT3IF)
#define EXTI3_CLS_IT_FLAG           REG_RESET_BIT(AUXINTIF,INT3IF)
#define EXTI3_GET_IT_FLAG           (AUXINTIF & INT3IF)
#define EXTI3_SET_IO_HIGH           do{P37=1;}while(0)
#define EXTI3_GET_IO                (P37)

#define EXTI3_IT_NUM                interrupt 11

#define EX4                         0x40
#define INT4IF                      0x40
#define PX4                         0x10
#define PX4H                        0x10

#define EXTI4_ENABLE                REG_SET_BIT(INTCLKO,EX4)
#define EXTI4_DISABLE               REG_RESET_BIT(INTCLKO,EX4)
#define EXTI4_SET_IT_FLAG           REG_SET_BIT(AUXINTIF,INT4IF)
#define EXTI4_CLS_IT_FLAG           REG_RESET_BIT(AUXINTIF,INT4IF)
#define EXTI4_GET_IT_FLAG           (AUXINTIF & INT4IF)
#define EXTI4_SET_IO_HIGH           do{P30=1;}while(0)
#define EXTI4_GET_IO                P30
#define EXTI4_SET_IT_PRIORITY_0     do{IP2H&=~PX4H;IP2&=~PX4;}while(0)
#define EXTI4_SET_IT_PRIORITY_1     do{IP2H&=~PX4H;IP2|= PX4;}while(0)
#define EXTI4_SET_IT_PRIORITY_2     do{IP2H|= PX4H;IP2&=~PX4;}while(0)
#define EXTI4_SET_IT_PRIORITY_3     do{IP2H|= PX4H;IP2|= PX4;}while(0)

#define EXTI4_IT_NUM                interrupt 16

#define IAP_IDL                     0x00
#define IAP_READ                    0x01
#define IAP_WRITE                   0x02
#define IAP_ERASE                   0x03
#define IAP_EN                      0x80
#define IAP_FAIL                    0x10

#define IAP_POWER_ON                REG_SET_BIT(IAP_CONTR,IAP_EN)
#define IAP_POWER_OFF               REG_RESET_BIT(IAP_CONTR,IAP_EN)
#define IAP_CMD_NOP                 do{IAP_CMD=IAP_IDL;   }while(0)
#define IAP_CMD_READ                do{IAP_CMD=IAP_READ;  }while(0)
#define IAP_CMD_WRITE               do{IAP_CMD=IAP_WRITE; }while(0)
#define IAP_CMD_ERASE               do{IAP_CMD=IAP_ERASE; }while(0)
#define IAP_TRIG_ON                 do{IAP_TRIG=0x5A;IAP_TRIG=0xA5;}while(0)
#define IAP_TRIG_CLS                do{IAP_TRIG=0;}while(0)
#define IAP_GET_FAIL                (IAP_CONTR & IAP_FAIL)

#define IAP_SET_REG_DATA(value)     do{IAP_DATA=(u8)(value);}while(0)
#define IAP_GET_REG_DATA            (IAP_DATA)
#define IAP_SET_REG_ADDR_HL(value)  do{IAP_ADDRL=(u8)(value);IAP_ADDRH=(u8)(value>>8);}while(0)
#define IAP_GET_REG_ADDR_HL         ((((u16)IAP_ADDRH)<<8)|(u16)IAP_ADDRL)
#define IAP_SET_REG_ADDR_H8(value)  do{IAP_ADDRH=(u8)(value);}while(0)
#define IAP_GET_REG_ADDR_H8         (IAP_ADDRH)
#define IAP_SET_REG_ADDR_L8(value)  do{IAP_ADDRL=(u8)(value);}while(0)
#define IAP_GET_REG_ADDR_L8         (IAP_ADDRL)
#define IAP_SET_REG_CONTR(value)    do{IAP_CONTR=(u8)(value);}while(0)
#define IAP_GET_REG_CONTR           (IAP_CONTR)
#define IAP_SET_REG_TPS(value)      do{IAP_TPS=(u8)(value);}while(0)
#define IAP_GET_REG_TPS             (IAP_TPS)

#define SPIF                        0x80
#define WCOL                        0x40
#define SSIG                        0x80
#define SPEN                        0x40
#define DORD                        0x20
#define MSTR                        0x10
#define CPOL                        0x08
#define CPHA                        0x04
#define ESPI                        0x02
#define PSPIH                       0x02
#define PSPI                        0x02

#define SPI_POWER_ON                REG_SET_BIT(SPCTL,SPEN)
#define SPI_POWER_OFF               REG_RESET_BIT(SPCTL,SPEN)
#define SPI_SET_CS_ENABLE           REG_RESET_BIT(SPCTL,SSIG)
#define SPI_SET_CS_DISABLE          REG_SET_BIT(SPCTL,SSIG)
#define SPI_SET_DATA_MSB            REG_RESET_BIT(SPCTL,DORD)
#define SPI_SET_DATA_LSB            REG_SET_BIT(SPCTL,DORD)
#define SPI_SET_MODE_MASTER         REG_SET_BIT(SPCTL,MSTR)
#define SPI_SET_MODE_SLAVE          REG_RESET_BIT(SPCTL,MSTR)
#define SPI_SET_CPOL_1              REG_SET_BIT(SPCTL,CPOL)
#define SPI_SET_CPOL_0              REG_RESET_BIT(SPCTL,CPOL)
#define SPI_SET_CPHA_1              REG_SET_BIT(SPCTL,CPHA)
#define SPI_SET_CPHA_0              REG_RESET_BIT(SPCTL,CPHA)
#define SPI_SET_PIN(value)          REG_IN_MASK(P_SW1,0x0C,value)
#define SPI_CLS_IT_FLAG             REG_SET_BIT(SPSTAT,(SPIF|WCOL))
#define SPI_GET_IT_FLAG             (SPSTAT & SPIF)
#define SPI_CLS_WCOL_FLAG           REG_SET_BIT(SPSTAT,WCOL)
#define SPI_GET_WCOL_FLAG           (SPSTAT & WCOL)
#define SPI_IT_ENABLE               REG_SET_BIT(IE2,ESPI)
#define SPI_IT_DISABLE              REG_RESET_BIT(IE2,ESPI)
#define SPI_SET_SPR(value)          REG_IN_MASK(SPCTL,0x03,value)
#define SPI_GET_SPR                 (SPCTL & 0x03)
#define SPI_SET_IT_PRIORITY_0       do{IP2H&=~PSPIH;IP2&=~PSPI;}while(0)
#define SPI_SET_IT_PRIORITY_1       do{IP2H&=~PSPIH;IP2|= PSPI;}while(0)
#define SPI_SET_IT_PRIORITY_2       do{IP2H|= PSPIH;IP2&=~PSPI;}while(0)
#define SPI_SET_IT_PRIORITY_3       do{IP2H|= PSPIH;IP2|= PSPI;}while(0)

#define SPI_SET_REG_SPSTAT(value)   do{SPSTAT=(u8)(value);}while(0)
#define SPI_GET_REG_SPSTAT          (SPSTAT)
#define SPI_SET_REG_SPCTL(value)    do{SPCTL=(u8)(value);}while(0)
#define SPI_GET_REG_SPCTL           (SPCTL)
#define SPI_SET_REG_SPDAT(value)    do{SPDAT=(u8)(value);}while(0)
#define SPI_GET_REG_SPDAT           (SPDAT)

#define SPI_IT_NUM                  interrupt 9

#define CMPEN                       0x80
#define CMPIF                       0x40
#define PIE                         0x20
#define NIE                         0x10
#define PIS                         0x08
#define NIS                         0x04
#define CMPOE                       0x02
#define CMPRES                      0x01
#define INVCMPO                     0x80
#define DISFLT                      0x40
#define PCMP                        0x20
#define PCMPH                       0x20

#define CMP_POWER_ON                do{CMPCR1|= CMPEN;}while(0)
#define CMP_POWER_OFF               do{CMPCR1&=~CMPEN;}while(0)
#define CMP_IT_CLS                  do{CMPCR1&=~CMPIF;}while(0)
#define CMP_IT_POSITIVE_ENABLE      do{CMPCR1|= PIE;  }while(0)
#define CMP_IT_POSITIVE_DISABLE     do{CMPCR1&=~PIE;  }while(0)
#define CMP_IT_NEGATIVE_ENABLE      do{CMPCR1|= NIE;  }while(0)
#define CMP_IT_NEGATIVE_DISABLE     do{CMPCR1&=~NIE;  }while(0)
#if     ECBM_MCU == 0x2815C4
#define CMP_SET_POSITIVE_ADC        REG_IN_MASK(CMPEXCFG,0x03,0x03)
#define CMP_SET_POSITIVE_P51        REG_IN_MASK(CMPEXCFG,0x03,0x02)
#define CMP_SET_POSITIVE_A50        REG_IN_MASK(CMPEXCFG,0x03,0x01)
#define CMP_SET_POSITIVE_P37        REG_IN_MASK(CMPEXCFG,0x03,0x00)
#else
#define CMP_SET_POSITIVE_ADC        do{CMPCR1|= PIS;  }while(0)
#define CMP_SET_POSITIVE_P37        do{CMPCR1&=~PIS;  }while(0)
#endif
#if     ECBM_MCU == 0x2815C4
#define CMP_SET_NEGATIVE_P36        do{CMPEXCFG&=~NIS;}while(0)
#define CMP_SET_NEGATIVE_BGV        do{CMPEXCFG|= NIS;}while(0)
#else
#define CMP_SET_NEGATIVE_P36        do{CMPCR1|= NIS;  }while(0)
#define CMP_SET_NEGATIVE_BGV        do{CMPCR1&=~NIS;  }while(0)
#endif
#define CMP_SET_OUT_ENABLE          do{CMPCR1|= CMPOE;}while(0)
#define CMP_SET_OUT_DISABLE         do{CMPCR1&=~CMPOE;}while(0)
#define CMP_GET_RESULT              (CMPCR1 & CMPRES)
#define CMP_SET_OUT_NEGATIVE        do{CMPCR2|= INVCMPO;}while(0)
#define CMP_SET_OUT_POSITIVE        do{CMPCR2&=~INVCMPO;}while(0)
#define CMP_SET_ANALOG_FILTER_ENABLE    do{CMPCR2&=~DISFLT;}while(0)
#define CMP_SET_ANALOG_FILTER_DISABLE   do{CMPCR2|= DISFLT;}while(0)
#define CMP_SET_DIGITAL_FILTER(value)   REG_IN_MASK(CMPCR2,0x3F,value)
#define CMP_SET_OUT_PIN(value)      REG_IN_MASK(P_SW2,0x08,value)
#define CMP_SET_IT_PRIORITY_0       do{IP2H&=~PCMPH;IP2&=~PCMP;}while(0)
#define CMP_SET_IT_PRIORITY_1       do{IP2H&=~PCMPH;IP2|= PCMP;}while(0)
#define CMP_SET_IT_PRIORITY_2       do{IP2H|= PCMPH;IP2&=~PCMP;}while(0)
#define CMP_SET_IT_PRIORITY_3       do{IP2H|= PCMPH;IP2|= PCMP;}while(0)

#define CMP_SET_REG_CMPCR1(value)   do{CMPCR1=(u8)(value);}while(0)
#define CMP_GET_REG_CMPCR1          (CMPCR1)
#define CMP_SET_REG_CMPCR2(value)   do{CMPCR2=(u8)(value);}while(0)
#define CMP_GET_REG_CMPCR2          (CMPCR2)
#define CMP_SET_REG_CMPEXCFG(value) do{CMPEXCFG=(u8)(value);}while(0)
#define CMP_GET_REG_CMPEXCFG        (CMPEXCFG)

#define CMP_IT_NUM                  interrupt 21

#define SWBS                        0x40
#define SWRST                       0x20
#define PD                          0x02
#define IDL                         0x01
#define EAXFR                       0x80

#define POWER_RESET                 do{IAP_CONTR=(SWRST|SWBS);}while(0)
#define MCU_RESET                   do{IAP_CONTR=(SWRST);     }while(0)
#define POWER_DOWN                  REG_SET_BIT(PCON,PD)
#define POWER_IDLE                  REG_SET_BIT(PCON,IDL)
#define EX_SFR_ENABLE               REG_SET_BIT(P_SW2,EAXFR)
#define EX_SFR_DISABLE              REG_RESET_BIT(P_SW2,EAXFR)

#define SYS_SET_REG_RSTCFG(value)   do{RSTCFG=(u8)(value);}while(0)
#define SYS_GET_REG_RSTCFG          (RSTCFG)

#define WKTEN                       0x80

#define WKT_ON                      REG_SET_BIT(WKTCH,WKTEN)
#define WKT_OFF                     REG_RESET_BIT(WKTCH,WKTEN)

#define WKT_SET_REG_COUNT(value)    do{WKTCL=(u8)(value); WKTCH=(u8)((value)>>8);}while(0)
#define WKT_GET_REG_COUNT           ((((u16)WKTCH)<<8)|(u16)WKTCL)




#define T0_GATE                     0x08
#define T0CLKO                      0x01
#define T0_CT                       0x04
#define T0_M1                       0x02
#define T0_M0                       0x01
#define T0x12                       0x80

#define PT0H                        0x02

#define TIMER0_POWER_ON             do{REG_RESET_BIT(TCON,0x20);REG_SET_BIT(TCON,0x10);}while(0)
#define TIMER0_POWER_OFF            do{REG_RESET_BIT(TCON,0x10);}while(0)
#define TIMER0_IT_ENABLE            REG_SET_BIT(IE,0x02)
#define TIMER0_IT_DISABLE           REG_RESET_BIT(IE,0x02)
#define TIMER0_GATE_ENABLE          REG_SET_BIT(TMOD,T0_GATE)
#define TIMER0_GATE_DISABLE         REG_RESET_BIT(TMOD,T0_GATE)
#define TIMER0_OUT_ON               REG_SET_BIT(INTCLKO,T0CLKO)
#define TIMER0_OUT_OFF              REG_RESET_BIT(INTCLKO,T0CLKO)
#define TIMER0_SET_MODE_COUNT       REG_SET_BIT(TMOD,T0_CT)
#define TIMER0_SET_MODE_TIMER       REG_RESET_BIT(TMOD,T0_CT)
#define TIMER0_SET_MODE_AUTO16      do{TMOD=(TMOD&(~0x03));}while(0)
#define TIMER0_SET_MODE_16BIT       do{TMOD=(TMOD&(~0x03))|T0_M0;}while(0)
#define TIMER0_SET_MODE_8BIT        do{TMOD=(TMOD&(~0x03))|T0_M1;}while(0)
#define TIMER0_SET_MODE_1T          REG_SET_BIT(AUXR,T0x12)
#define TIMER0_SET_MODE_12T         REG_RESET_BIT(AUXR,T0x12)
#define TIMER0_GET_FLAG             (TF0)
#define TIMER0_CLS_FLAG             do{TF0=0;}while(0)
#define TIMER0_SET_IT_PRIORITY_0    do{IPH&=~PT0H;IP&=~PT0H;}while(0)
#define TIMER0_SET_IT_PRIORITY_1    do{IPH&=~PT0H;IP|= PT0H;}while(0)
#define TIMER0_SET_IT_PRIORITY_2    do{IPH|= PT0H;IP&=~PT0H;}while(0)
#define TIMER0_SET_IT_PRIORITY_3    do{IPH|= PT0H;IP|= PT0H;}while(0)

#define TIMER0_SET_REG_AUXR(value)  REG_IN_MASK(AUXR,0x80,value)
#define TIMER0_GET_REG_AUXR         (AUXR & 0x80)
#define TIMER0_SET_REG_TMOD(value)  REG_IN_MASK(TMOD,0x0F,value)
#define TIMER0_GET_REG_TMOD         (TMOD & 0x0F)
#define TIMER0_SET_REG_HL(value)    do{TL0=(u8)(value);TH0=(u8)(value>>8);}while(0)
#define TIMER0_GET_REG_HL           ((((u16)TH0)<<8)|(u16)TL0)
#define TIMER0_SET_REG_H8(value)    do{TH0=(u8)(value);}while(0)
#define TIMER0_GET_REG_H8           (TH0)
#define TIMER0_SET_REG_L8(value)    do{TL0=(u8)(value);}while(0)
#define TIMER0_GET_REG_L8           (TL0)

#define TIMER0_IT_NUM               interrupt 1




#define T1_GATE                     0x80
#define T1CLKO                      0x02
#define T1_CT                       0x40
#define T1_M1                       0x20
#define T1_M0                       0x10
#define T1x12                       0x40

#define PT1H                        0x08

#define TIMER1_POWER_ON             do{TF1=0;TR1=1;}while(0)
#define TIMER1_POWER_OFF            do{TR1=0;}while(0)
#define TIMER1_IT_ENABLE            REG_SET_BIT(IE,0x08)
#define TIMER1_IT_DISABLE           REG_RESET_BIT(IE,0x08)
#define TIMER1_GATE_ENABLE          REG_SET_BIT(TMOD,T1_GATE)
#define TIMER1_GATE_DISABLE         REG_RESET_BIT(TMOD,T1_GATE)
#define TIMER1_OUT_ON               REG_SET_BIT(INTCLKO,T1CLKO)
#define TIMER1_OUT_OFF              REG_RESET_BIT(INTCLKO,T1CLKO)
#define TIMER1_SET_MODE_COUNT       REG_SET_BIT(TMOD,T1_CT)
#define TIMER1_SET_MODE_TIMER       REG_RESET_BIT(TMOD,T1_CT)
#define TIMER1_SET_MODE_AUTO16      do{TMOD=(TMOD&(~0x30));}while(0)
#define TIMER1_SET_MODE_16BIT       do{TMOD=(TMOD&(~0x30))|T1_M0;}while(0)
#define TIMER1_SET_MODE_8BIT        do{TMOD=(TMOD&(~0x30))|T1_M1;}while(0)
#define TIMER1_SET_MODE_1T          REG_SET_BIT(AUXR,T1x12)
#define TIMER1_SET_MODE_12T         REG_RESET_BIT(AUXR,T1x12)
#define TIMER1_GET_FLAG             (TF1)
#define TIMER1_CLS_FLAG             do{TF1=0;}while(0)
#define TIMER1_SET_IT_PRIORITY_0    do{IPH&=~PT1H;IP&=~PT1H;}while(0)
#define TIMER1_SET_IT_PRIORITY_1    do{IPH&=~PT1H;IP|= PT1H;}while(0)
#define TIMER1_SET_IT_PRIORITY_2    do{IPH|= PT1H;IP&=~PT1H;}while(0)
#define TIMER1_SET_IT_PRIORITY_3    do{IPH|= PT1H;IP|= PT1H;}while(0)

#define TIMER1_SET_REG_AUXR(value)  REG_IN_MASK(AUXR,0x40,value)
#define TIMER1_GET_REG_AUXR         (AUXR & 0x40)
#define TIMER1_SET_REG_TMOD(value)  REG_IN_MASK(TMOD,0xF0,value)
#define TIMER1_GET_REG_TMOD         (TMOD & 0xF0)
#define TIMER1_SET_REG_HL(value)    do{TL1=(u8)(value);TH1=(u8)(value>>8);}while(0)
#define TIMER1_GET_REG_HL           ((((u16)TH1)<<8)|(u16)TL1)
#define TIMER1_SET_REG_H8(value)    do{TH1=(u8)(value);}while(0)
#define TIMER1_GET_REG_H8           (TH1)
#define TIMER1_SET_REG_L8(value)    do{TL1=(u8)(value);}while(0)
#define TIMER1_GET_REG_L8           (TL1)

#define TIMER1_IT_NUM               interrupt 3

#define T2R                         0x10
#define ET2                         0x04
#define T2CLKO                      0x04
#define T2_CT                       0x08
#define T2x12                       0x04
#define T2IF                        0x01

#define TIMER2_POWER_ON             REG_SET_BIT(AUXR,T2R)
#define TIMER2_POWER_OFF            REG_RESET_BIT(AUXR,T2R)
#define TIMER2_IT_ENABLE            REG_SET_BIT(IE2,ET2)
#define TIMER2_IT_DISABLE           REG_RESET_BIT(IE2,ET2)
#define TIMER2_OUT_ON               REG_SET_BIT(INTCLKO,T2CLKO)
#define TIMER2_OUT_OFF              REG_RESET_BIT(INTCLKO,T2CLKO)
#define TIMER2_SET_MODE_COUNT       REG_SET_BIT(AUXR,T2_CT)
#define TIMER2_SET_MODE_TIMER       REG_RESET_BIT(AUXR,T2_CT)
#define TIMER2_SET_MODE_1T          REG_SET_BIT(AUXR,T2x12)
#define TIMER2_SET_MODE_12T         REG_RESET_BIT(AUXR,T2x12)
#define TIMER2_CLS_FLAG             REG_RESET_BIT(AUXINTIF,T2IF)

#define TIMER2_SET_REG_AUXR(value)  REG_IN_MASK(AUXR,0x0C,value)
#define TIMER2_GET_REG_AUXR         (AUXR&0x0C)
#define TIMER2_SET_REG_HL(value)    do{T2L=(u8)(value);T2H=(u8)(value>>8);}while(0)
#define TIMER2_GET_REG_HL           ((((u16)T2H)<<8)|(u16)T2L)
#define TIMER2_SET_REG_H8(value)    do{T2H=(u8)(value);}while(0)
#define TIMER2_GET_REG_H8           (T2H)
#define TIMER2_SET_REG_L8(value)    do{T2L=(u8)(value);}while(0)
#define TIMER2_GET_REG_L8           (T2L)

#define TIMER2_IT_NUM               interrupt 12

#define T3R                         0x08
#define ET3                         0x20
#define T3CLKO                      0x01
#define T3_CT                       0x04
#define T3x12                       0x02
#define T3IF                        0x02

#define TIMER3_POWER_ON             REG_SET_BIT(T4T3M,T3R)
#define TIMER3_POWER_OFF            REG_RESET_BIT(T4T3M,T3R)
#define TIMER3_IT_ENABLE            REG_SET_BIT(IE2,ET3)
#define TIMER3_IT_DISABLE           REG_RESET_BIT(IE2,ET3)
#define TIMER3_OUT_ON               REG_SET_BIT(T4T3M,T3CLKO)
#define TIMER3_OUT_OFF              REG_RESET_BIT(T4T3M,T3CLKO)
#define TIMER3_SET_MODE_COUNT       REG_SET_BIT(T4T3M,T3_CT)
#define TIMER3_SET_MODE_TIMER       REG_RESET_BIT(T4T3M,T3_CT)
#define TIMER3_SET_MODE_1T          REG_SET_BIT(T4T3M,T3x12)
#define TIMER3_SET_MODE_12T         REG_RESET_BIT(T4T3M,T3x12)
#define TIMER3_CLS_FLAG             REG_RESET_BIT(AUXINTIF,T3IF)

#define TIMER3_SET_REG_T4T3M(value) REG_IN_MASK(T4T3M,0x0F,value)
#define TIMER3_GET_REG_T4T3M        (T4T3M & 0x0F)
#define TIMER3_SET_REG_HL(value)    do{T3L=(u8)(value);T3H=(u8)(value>>8);}while(0)
#define TIMER3_GET_REG_HL           ((((u16)T3H)<<8)|(u16)T3L)
#define TIMER3_SET_REG_H8(value)    do{T3H=(u8)(value);}while(0)
#define TIMER3_GET_REG_H8           (T3H)
#define TIMER3_SET_REG_L8(value)    do{T3L=(u8)(value);}while(0)
#define TIMER3_GET_REG_L8           (T3L)

#define TIMER3_IT_NUM               interrupt 19

#define T4R                         0x80
#define ET4                         0x40
#define T4CLKO                      0x10
#define T4_CT                       0x40
#define T4x12                       0x20
#define T4IF                        0x04

#define TIMER4_POWER_ON             REG_SET_BIT(T4T3M,T4R)
#define TIMER4_POWER_OFF            REG_RESET_BIT(T4T3M,T4R)
#define TIMER4_IT_ENABLE            REG_SET_BIT(IE2,ET4)
#define TIMER4_IT_DISABLE           REG_RESET_BIT(IE2,ET4)
#define TIMER4_OUT_ON               REG_SET_BIT(T4T3M,T4CLKO)
#define TIMER4_OUT_OFF              REG_RESET_BIT(T4T3M,T4CLKO)
#define TIMER4_SET_MODE_COUNT       REG_SET_BIT(T4T3M,T4_CT)
#define TIMER4_SET_MODE_TIMER       REG_RESET_BIT(T4T3M,T4_CT)
#define TIMER4_SET_MODE_1T          REG_SET_BIT(T4T3M,T4x12)
#define TIMER4_SET_MODE_12T         REG_RESET_BIT(T4T3M,T4x12)
#define TIMER4_CLS_FLAG              REG_RESET_BIT(AUXINTIF,T4IF)

#define TIMER4_SET_REG_T4T3M(value) REG_IN_MASK(T4T3M,0xF0,value)
#define TIMER4_GET_REG_T4T3M        (T4T3M & 0xF0)
#define TIMER4_SET_REG_HL(value)    do{T4L=(u8)(value);T4H=(u8)(value>>8);}while(0)
#define TIMER4_GET_REG_HL           ((((u16)T4H)<<8)|(u16)T4L)
#define TIMER4_SET_REG_H8(value)    do{T4H=(u8)(value);}while(0)
#define TIMER4_GET_REG_H8           (T4H)
#define TIMER4_SET_REG_L8(value)    do{T4L=(u8)(value);}while(0)
#define TIMER4_GET_REG_L8           (T4L)

#define TIMER4_IT_NUM               interrupt 20










#define SMOD                        0x80
#define SMOD0                       0x40
#define UART_M0x6                   0x20
#define S1ST2                       0x01

#define PSH                         0x10

#define UART1_IT_ENABLE             do{ES=1;}while(0)
#define UART1_IT_DISABLE            do{ES=0;}while(0)
#define UART1_CLR_TI_FLAG           do{TI=0;}while(0)
#define UART1_GET_TI_FLAG           (TI)
#define UART1_CLR_RI_FLAG           do{RI=0;}while(0)
#define UART1_GET_RI_FLAG           (RI)
#define UART1_SET_TXD_BYTE9_0       do{TB8=0;TB8=0;}while(0)
#define UART1_SET_TXD_BYTE9_1       do{TB8=1;TB8=1;}while(0)
#define UART1_GET_RXD_BYTE9         (RB8)
#define UART1_SET_PIN(value)        REG_IN_MASK(P_SW1,0xC0,value)
#define UART1_SET_BAUD_1            REG_RESET_BIT(PCON,SMOD)
#define UART1_SET_BAUD_2            REG_SET_BIT(PCON,SMOD)
#define UART1_SET_CLK_TIMER1        REG_RESET_BIT(AUXR,S1ST2)
#define UART1_SET_CLK_TIMER2        REG_SET_BIT(AUXR,S1ST2)
#define UART1_SET_RXD_ENABLE        do{REN=1;}while(0)
#define UART1_SET_RXD_DISABLE       do{REN=0;}while(0)
#define UART1_SET_MUX_ENABLE        do{SM2=1;}while(0)
#define UART1_SET_MUX_DISABLE       do{SM2=0;}while(0)
#define UART1_SET_MODE_S_8          do{SCON=(SCON&(~0xC0))|0x00;}while(0)
#define UART1_SET_MODE_A_8_BAUD     do{SCON=(SCON&(~0xC0))|0x40;}while(0)
#define UART1_SET_MODE_A_9          do{SCON=(SCON&(~0xC0))|0x80;}while(0)
#define UART1_SET_MODE_A_9_BAUD     do{SCON=(SCON&(~0xC0))|0xC0;}while(0)
#define UART1_SET_IT_PRIORITY_0     do{IPH&=~PSH;PS=0;}while(0)
#define UART1_SET_IT_PRIORITY_1     do{IPH&=~PSH;PS=1;}while(0)
#define UART1_SET_IT_PRIORITY_2     do{IPH|= PSH;PS=0;}while(0)
#define UART1_SET_IT_PRIORITY_3     do{IPH|= PSH;PS=1;}while(0)

#define UART1_SET_REG_SADDR(value)  do{SADDR=(u8)(value);}while(0)
#define UART1_GET_REG_SADDR         (SADDR)
#define UART1_SET_REG_SADEN(value)  do{SADEN=(u8)(value);}while(0)
#define UART1_GET_REG_SADEN         (SADEN)
#define UART1_SET_REG_SBUF(value)   do{SBUF =(u8)(value);}while(0)
#define UART1_GET_REG_SBUF          (SBUF)
#define UART1_SET_REG_SCON(value)   do{SCON =(u8)(value);}while(0)
#define UART1_GET_REG_SCON          (SCON)
#define UART1_SET_REG_PCON(value)   REG_IN_MASK(PCON,0xC0,value)
#define UART1_GET_REG_PCON          (PCON & 0xC0)
#define UART1_SET_REG_AUXR(value)   REG_IN_MASK(AUXR,0x21,value)
#define UART1_GET_REG_AUXR          (AUXR & 0x21)

#define UART1_IT_NUM                interrupt 4

#define ES2                         0x01
#define S2SM0                       0x80
#define S2SM2                       0x20
#define S2REN                       0x10
#define S2TB8                       0x08
#define S2RB8                       0x04
#define S2TI                        0x02
#define S2RI                        0x01
#define PS2                         0x01
#define PS2H                        0x01

#define UART2_IT_ENABLE             REG_SET_BIT(IE2,ES2)
#define UART2_IT_DISABLE            REG_RESET_BIT(IE2,ES2)
#define UART2_CLR_TI_FLAG           REG_RESET_BIT(S2CON,S2TI)
#define UART2_GET_TI_FLAG           (S2CON & S2TI)
#define UART2_CLR_RI_FLAG           REG_RESET_BIT(S2CON,S2RI)
#define UART2_GET_RI_FLAG           (S2CON & S2RI)
#define UART2_SET_TXD_BYTE9_0       do{S2CON&=~S2TB8;S2CON&=~S2TB8;}while(0)
#define UART2_SET_TXD_BYTE9_1       do{S2CON|= S2TB8;S2CON|= S2TB8;}while(0)
#define UART2_GET_RXD_BYTE9         (S2CON & S2RB8)
#define UART2_SET_PIN(value)        REG_IN_MASK(P_SW2,0x01,value)
#define UART2_SET_RXD_ENABLE        REG_SET_BIT(S2CON,S2REN)
#define UART2_SET_RXD_DISABLE       REG_RESET_BIT(S2CON,S2REN)
#define UART2_SET_MUX_ENABLE        REG_SET_BIT(S2CON,S2SM2)
#define UART2_SET_MUX_DISABLE       REG_RESET_BIT(S2CON,S2SM2)
#define UART2_SET_MODE_A_8_BAUD     REG_RESET_BIT(S2CON,S2SM0)
#define UART2_SET_MODE_A_9_BAUD     REG_SET_BIT(S2CON,S2SM0)
#define UART2_SET_IT_PRIORITY_0     do{IP2H&=~PS2H;IP2&=~PS2;}while(0)
#define UART2_SET_IT_PRIORITY_1     do{IP2H&=~PS2H;IP2|= PS2;}while(0)
#define UART2_SET_IT_PRIORITY_2     do{IP2H|= PS2H;IP2&=~PS2;}while(0)
#define UART2_SET_IT_PRIORITY_3     do{IP2H|= PS2H;IP2|= PS2;}while(0)

#define UART2_SET_REG_S2BUF(value)  do{S2BUF =(u8)(value);}while(0)
#define UART2_GET_REG_S2BUF         (S2BUF)
#define UART2_SET_REG_S2CON(value)  do{S2CON =(u8)(value);}while(0)
#define UART2_GET_REG_S2CON         (S2CON)

#define UART2_IT_NUM                interrupt 8

#define ES3                         0x08
#define S3SM0                       0x80
#define S3ST3                       0x40
#define S3SM2                       0x20
#define S3REN                       0x10
#define S3TB8                       0x08
#define S3RB8                       0x04
#define S3TI                        0x02
#define S3RI                        0x01
#define PS3                         0x01
#define PS3H                        0x01

#define UART3_IT_ENABLE             REG_SET_BIT(IE2,ES3)
#define UART3_IT_DISABLE            REG_RESET_BIT(IE2,ES3)
#define UART3_CLR_TI_FLAG           REG_RESET_BIT(S3CON,S3TI)
#define UART3_GET_TI_FLAG           (S3CON & S3TI)
#define UART3_CLR_RI_FLAG           REG_RESET_BIT(S3CON,S3RI)
#define UART3_GET_RI_FLAG           (S3CON & S3RI)
#define UART3_SET_TXD_BYTE9_0       do{S3CON&=~S3TB8;S3CON&=~S3TB8;}while(0)
#define UART3_SET_TXD_BYTE9_1       do{S3CON|= S3TB8;S3CON|= S3TB8;}while(0)
#define UART3_GET_RXD_BYTE9         (S3CON & S3RB8)
#define UART3_SET_PIN(value)        REG_IN_MASK(P_SW2,0x02,value)
#define UART3_SET_CLK_TIMER2        REG_RESET_BIT(S3CON,S3ST3)
#define UART3_SET_CLK_TIMER3        REG_SET_BIT(S3CON,S3ST3)
#define UART3_SET_RXD_ENABLE        REG_SET_BIT(S3CON,S3REN)
#define UART3_SET_RXD_DISABLE       REG_RESET_BIT(S3CON,S3REN)
#define UART3_SET_MUX_ENABLE        REG_SET_BIT(S3CON,S3SM2)
#define UART3_SET_MUX_DISABLE       REG_RESET_BIT(S3CON,S3SM2)
#define UART3_SET_MODE_A_8_BAUD     REG_RESET_BIT(S3CON,S3SM0)
#define UART3_SET_MODE_A_9_BAUD     REG_SET_BIT(S3CON,S3SM0)
#define UART3_SET_IT_PRIORITY_0     do{IP3H&=~PS3H;IP3&=~PS3;}while(0)
#define UART3_SET_IT_PRIORITY_1     do{IP3H&=~PS3H;IP3|= PS3;}while(0)
#define UART3_SET_IT_PRIORITY_2     do{IP3H|= PS3H;IP3&=~PS3;}while(0)
#define UART3_SET_IT_PRIORITY_3     do{IP3H|= PS3H;IP3|= PS3;}while(0)

#define UART3_SET_REG_S3BUF(value)  do{S3BUF =((u8)(value));}while(0)
#define UART3_GET_REG_S3BUF         (S3BUF)
#define UART3_SET_REG_S3CON(value)  do{S3CON =((u8)(value));}while(0)
#define UART3_GET_REG_S3CON         (S3CON)

#define UART3_IT_NUM                interrupt 17

#define ES4                         0x10
#define S4SM0                       0x80
#define S4ST4                       0x40
#define S4SM2                       0x20
#define S4REN                       0x10
#define S4TB8                       0x08
#define S4RB8                       0x04
#define S4TI                        0x02
#define S4RI                        0x01
#define PS4                         0x02
#define PS4H                        0x02

#define UART4_IT_ENABLE             REG_SET_BIT(IE2,ES4)
#define UART4_IT_DISABLE            REG_RESET_BIT(IE2,ES4)
#define UART4_CLR_TI_FLAG           REG_RESET_BIT(S4CON,S4TI)
#define UART4_GET_TI_FLAG           (S4CON & S4TI)
#define UART4_CLR_RI_FLAG           REG_RESET_BIT(S4CON,S4RI)
#define UART4_GET_RI_FLAG           (S4CON & S4RI)
#define UART4_SET_TXD_BYTE9_0       do{S4CON&=~S4TB8;S4CON&=~S4TB8;}while(0)
#define UART4_SET_TXD_BYTE9_1       do{S4CON|= S4TB8;S4CON|= S4TB8;}while(0)
#define UART4_GET_RXD_BYTE9         (S4CON & S4RB8)
#define UART4_SET_PIN(value)        REG_IN_MASK(P_SW2,0x04,value)
#define UART4_SET_CLK_TIMER2        REG_RESET_BIT(S4CON,S4ST4)
#define UART4_SET_CLK_TIMER4        REG_SET_BIT(S4CON,S4ST4)
#define UART4_SET_RXD_ENABLE        REG_SET_BIT(S4CON,S4REN)
#define UART4_SET_RXD_DISABLE       REG_RESET_BIT(S4CON,S4REN)
#define UART4_SET_MUX_ENABLE        REG_SET_BIT(S4CON,S4SM2)
#define UART4_SET_MUX_DISABLE       REG_RESET_BIT(S4CON,S4SM2)
#define UART4_SET_MODE_A_8_BAUD     REG_RESET_BIT(S4CON,S4SM0)
#define UART4_SET_MODE_A_9_BAUD     REG_SET_BIT(S4CON,S4SM0)
#define UART4_SET_IT_PRIORITY_0     do{IP3H&=~PS4H;IP3&=~PS4;}while(0)
#define UART4_SET_IT_PRIORITY_1     do{IP3H&=~PS4H;IP3|= PS4;}while(0)
#define UART4_SET_IT_PRIORITY_2     do{IP3H|= PS4H;IP3&=~PS4;}while(0)
#define UART4_SET_IT_PRIORITY_3     do{IP3H|= PS4H;IP3|= PS4;}while(0)

#define UART4_SET_REG_S4BUF(value)  do{S4BUF =(u8)(value);}while(0)
#define UART4_GET_REG_S4BUF         (S4BUF)
#define UART4_SET_REG_S4CON(value)  do{S4CON =(u8)(value);}while(0)
#define UART4_GET_REG_S4CON         (S4CON)

#define UART4_IT_NUM                interrupt 18

#define MDOV                        0x40
#define MDRST                       0x02
#define ENOP                        0x01

#define MDU16_RESET                 do{OPCON=MDRST;}while(0)
#define MDU16_START                 do{OPCON=ENOP; }while(0)
#define MDU16_GET_END_FLAG          (OPCON & ENOP)
#define MDU16_GET_MDOV_FLAG         (OPCON & MDOV)
#define MDU16_SET_16MUL             do{ARCON=0x80; }while(0)
#define MDU16_SET_16DIV             do{ARCON=0xa0; }while(0)
#define MDU16_SET_32DIV             do{ARCON=0xc0; }while(0)

#define MDU16_SET_REG_ARCON(value)  do{ARCON=(u8)(value);}while(0)
#define MDU16_GET_REG_ARCON         (ARCON)
#define MDU16_SET_REG_OPCON(value)  do{OPCON=(u8)(value);}while(0)
#define MDU16_GET_REG_OPCON         (OPCON)

#define ENI2C                       0x80
#define MSSL                        0x40
#define EMSI                        0x80
#define MSBUSY                      0x80
#define MSIF                        0x40
#define MSACKI                      0x02
#define MSACKO                      0x01
#define WDTA                        0x01
#define ESTAI                       0x40
#define ERXI                        0x20
#define ETXI                        0x10
#define ESTOI                       0x08
#define SLRST                       0x01
#define SLBUSY                      0x80
#define STAIF                       0x40
#define RXIF                        0x20
#define TXIF                        0x10
#define STOIF                       0x08
#define SLACKI                      0x02
#define SLACKO                      0x01
#define PI2C                        0x40
#define PI2CH                       0x40

#define IIC_POWER_ON                REG_SET_BIT(I2CCFG,ENI2C)
#define IIC_POWER_OFF               REG_RESET_BIT(I2CCFG,ENI2C)
#define IIC_SET_MODE_MASTER         REG_SET_BIT(I2CCFG,MSSL)
#define IIC_SET_MODE_SLAVE          REG_RESET_BIT(I2CCFG,MSSL)
#define IIC_SET_AUTOACK_ENABLE      REG_SET_BIT(I2CMSAUX,WDTA)
#define IIC_SET_AUTOACK_DISABLE     REG_RESET_BIT(I2CMSAUX,WDTA)
#define IIC_SET_SPEED(value)        REG_IN_MASK(I2CCFG,0x3F,value)
#define IIC_GET_M_IT_FLAG           (I2CMSST & MSIF)
#define IIC_CLS_M_IT_FLAG           REG_RESET_BIT(I2CMSST,MSIF)
#define IIC_GET_S_STA_FLAG          (I2CSLST & STAIF)
#define IIC_CLS_S_STA_FLAG          REG_RESET_BIT(I2CSLST,STAIF)
#define IIC_GET_S_STO_FLAG          (I2CSLST & STOIF)
#define IIC_CLS_S_STO_FLAG          REG_RESET_BIT(I2CSLST,STOIF)
#define IIC_GET_S_RX_FLAG           (I2CSLST & RXIF)
#define IIC_CLS_S_RX_FLAG           REG_RESET_BIT(I2CSLST,RXIF)
#define IIC_GET_ACK                 (I2CMSST & MSACKI)
#define IIC_SET_PIN(value)          REG_IN_MASK(P_SW2,0x30,value)
#define IIC_SET_IT_PRIORITY_0       do{IP2H&=~PI2CH;IP2&=~PI2C;}while(0)
#define IIC_SET_IT_PRIORITY_1       do{IP2H&=~PI2CH;IP2|= PI2C;}while(0)
#define IIC_SET_IT_PRIORITY_2       do{IP2H|= PI2CH;IP2&=~PI2C;}while(0)
#define IIC_SET_IT_PRIORITY_3       do{IP2H|= PI2CH;IP2|= PI2C;}while(0)
#define IIC_CMD_START               do{I2CMSCR=(EMSI|0x01);}while(0)
#define IIC_CMD_TX_DATA             do{I2CMSCR=(EMSI|0x02);}while(0)
#define IIC_CMD_RX_ACK              do{I2CMSCR=(EMSI|0x03);}while(0)
#define IIC_CMD_RX_DATA             do{I2CMSCR=(EMSI|0x04);}while(0)
#define IIC_CMD_TX_ACK              do{I2CMSST=0x00;I2CMSCR=(EMSI|0x05);}while(0)
#define IIC_CMD_TX_NACK             do{I2CMSST=0x01;I2CMSCR=(EMSI|0x05);}while(0)
#define IIC_CMD_STOP                do{I2CMSCR=(EMSI|0x06);}while(0)
#define IIC_CMD_START_TXDATA_RXACK  do{I2CMSCR=(EMSI|0x09);}while(0)
#define IIC_CMD_TXDATA_RXACK        do{I2CMSCR=(EMSI|0x0A);}while(0)
#define IIC_CMD_RXDATA_ACK          do{I2CMSCR=(EMSI|0x0B);}while(0)
#define IIC_CMD_RXDATA_NACK         do{I2CMSCR=(EMSI|0x0C);}while(0)

#define IIC_SET_REG_CFG(value)      do{I2CCFG=(u8)(value);}while(0)
#define IIC_GET_REG_CFG             (I2CCFG)
#define IIC_SET_REG_MSCR(value)     do{I2CMSCR=(u8)(value);}while(0)
#define IIC_GET_REG_MSCR            (I2CMSCR)
#define IIC_SET_REG_MSST(value)     do{I2CMSST=(u8)(value);}while(0)
#define IIC_GET_REG_MSST            (I2CMSST)
#define IIC_SET_REG_MSAUX(value)    do{I2CMSAUX=(u8)(value);}while(0)
#define IIC_GET_REG_MSAUX           (I2CMSAUX)
#define IIC_SET_REG_DATA(value)     do{I2CTXD=(u8)(value);}while(0)
#define IIC_GET_REG_DATA            (I2CRXD)

#define IIC_SET_REG_SLCR(value)     do{I2CSLCR=(u8)(value);}while(0)
#define IIC_GET_REG_SLCR            (I2CSLCR)
#define IIC_SET_REG_SLST(value)     do{I2CSLST=(u8)(value);}while(0)
#define IIC_GET_REG_SLST            (I2CSLST)
#define IIC_SET_REG_SLADR(value)    do{I2CSLADR=(u8)(value);}while(0)
#define IIC_GET_REG_SLADR           (I2CSLADR)

#define IIC_IT_NUM                  interrupt 24


#define ADC_POWER                   0x80
#define ADC_START                   0x40
#define ADC_FLAG                    0x20
#define ADC_EPWMT                   0x10
#define ADC_RESFMT                  0x20

#define PADCH                       0x20

#define ADC_POWER_ON                REG_SET_BIT(ADC_CONTR,ADC_POWER)
#define ADC_POWER_OFF               REG_RESET_BIT(ADC_CONTR,ADC_POWER)
#define ADC_IT_ENABLE               do{EADC=1;}while(0)
#define ADC_IT_DISABLE              do{EADC=0;}while(0)
#define ADC_PWM_ENABLE              REG_SET_BIT(ADC_CONTR,ADC_EPWMT)
#define ADC_PWM_DISABLE             REG_RESET_BIT(ADC_CONTR,ADC_EPWMT)
#define ADC_GET_IT_FLAG             (ADC_CONTR & ADC_FLAG)
#define ADC_CLS_IT_FLAG             REG_RESET_BIT(ADC_CONTR,(ADC_START|ADC_FLAG))
#define ADC_MEASURE_ON              REG_SET_BIT(ADC_CONTR,ADC_START)
#define ADC_SET_CHANNELS(value)     REG_IN_MASK(ADC_CONTR,0x0F,value)
#define ADC_SET_ALIGN_LEFT          REG_RESET_BIT(ADC_CFG,ADC_RESFMT)
#define ADC_SET_ALIGN_RIGHT         REG_SET_BIT(ADC_CFG,ADC_RESFMT)
#define ADC_SET_SPEED(value)        REG_IN_MASK(ADC_CFG,0x0F,value)
#define ADC_SET_IT_PRIORITY_0       do{IPH&=~PADCH;PADC=0;}while(0)
#define ADC_SET_IT_PRIORITY_1       do{IPH&=~PADCH;PADC=1;}while(0)
#define ADC_SET_IT_PRIORITY_2       do{IPH|= PADCH;PADC=0;}while(0)
#define ADC_SET_IT_PRIORITY_3       do{IPH|= PADCH;PADC=1;}while(0)

#define ADC_SET_REG_CONTR(value)    do{ADC_CONTR=(u8)(value);}while(0)
#define ADC_GET_REG_CONTR           (ADC_CONTR)
#define ADC_SET_REG_CFG(value)      do{ADC_CFG=(u8)(value);}while(0)
#define ADC_GET_REG_CFG             (ADC_CFG)
#define ADC_SET_REG_EXCFG(value)    do{ADCEXCFG=(u8)(value);}while(0)
#define ADC_GET_REG_EXCFG           (ADCEXCFG)
#define ADC_SET_REG_TIM(value)      do{ADC_TIM=(u8)(value);}while(0)
#define ADC_GET_REG_TIM             (ADC_TIM)
#define ADC_GET_REG_RES_HL          ((((u16)ADC_RES)<<8)|(u16)ADC_RESL)
#define ADC_GET_REG_RES_H8          (ADC_RES )
#define ADC_GET_REG_RES_L8          (ADC_RESL)

#define ADC_IT_NUM                  interrupt 5


/*-------------------------------I/O口特殊功能寄存器-----------------------------*/
/* sbit    P00                         =P0^0;  //P0.0�?
sbit    P01                         =P0^1;  //P0.1�?
sbit    P02                         =P0^2;  //P0.2�?
sbit    P03                         =P0^3;  //P0.3�?
sbit    P04                         =P0^4;  //P0.4�?
sbit    P05                         =P0^5;  //P0.5�?
sbit    P06                         =P0^6;  //P0.6�?
sbit    P07                         =P0^7;  //P0.7�?
sbit    P10                         =P1^0;  //P1.0�?
sbit    P11                         =P1^1;  //P1.1�?
sbit    P12                         =P1^2;  //P1.2�?
sbit    P13                         =P1^3;  //P1.3�?
sbit    P14                         =P1^4;  //P1.4�?
sbit    P15                         =P1^5;  //P1.5�?
sbit    P16                         =P1^6;  //P1.6�?
sbit    P17                         =P1^7;  //P1.7�?
sbit    P20                         =P2^0;  //P2.0�?
sbit    P21                         =P2^1;  //P2.1�?
sbit    P22                         =P2^2;  //P2.2�?
sbit    P23                         =P2^3;  //P2.3�?
sbit    P24                         =P2^4;  //P2.4�?
sbit    P25                         =P2^5;  //P2.5�?
sbit    P26                         =P2^6;  //P2.6�?
sbit    P27                         =P2^7;  //P2.7�?
sbit    P30                         =P3^0;  //P3.0�?
sbit    P31                         =P3^1;  //P3.1�?
sbit    P32                         =P3^2;  //P3.2�?
sbit    P33                         =P3^3;  //P3.3�?
sbit    P34                         =P3^4;  //P3.4�?
sbit    P35                         =P3^5;  //P3.5�?
sbit    P36                         =P3^6;  //P3.6�?
sbit    P37                         =P3^7;  //P3.7�?
sbit    P40                         =P4^0;  //P4.0�?
sbit    P41                         =P4^1;  //P4.1�?
sbit    P42                         =P4^2;  //P4.2�?
sbit    P43                         =P4^3;  //P4.3�?
sbit    P44                         =P4^4;  //P4.4�?
sbit    P45                         =P4^5;  //P4.5�?
sbit    P46                         =P4^6;  //P4.6�?
sbit    P47                         =P4^7;  //P4.7�?
sbit    P50                         =P5^0;  //P5.0�?
sbit    P51                         =P5^1;  //P5.1�?
sbit    P52                         =P5^2;  //P5.2�?
sbit    P53                         =P5^3;  //P5.3�?
sbit    P54                         =P5^4;  //P5.4�?
sbit    P55                         =P5^5;  //P5.5�?
sbit    P56                         =P5^6;  //P5.6�?
sbit    P57                         =P5^7;  //P5.7�?
sbit    P60                         =P6^0;  //P6.0�?
sbit    P61                         =P6^1;  //P6.1�?
sbit    P62                         =P6^2;  //P6.2�?
sbit    P63                         =P6^3;  //P6.3�?
sbit    P64                         =P6^4;  //P6.4�?
sbit    P65                         =P6^5;  //P6.5�?
sbit    P66                         =P6^6;  //P6.6�?
sbit    P67                         =P6^7;  //P6.7�?
sbit    P70                         =P7^0;  //P7.0�?
sbit    P71                         =P7^1;  //P7.1�?
sbit    P72                         =P7^2;  //P7.2�?
sbit    P73                         =P7^3;  //P7.3�?
sbit    P74                         =P7^4;  //P7.4�?
sbit    P75                         =P7^5;  //P7.5�?
sbit    P76                         =P7^6;  //P7.6�?
sbit    P77                         =P7^7;  //P7.7�?*/


 SBIT(P00, 0x80, 0);
 SBIT(P01, 0x80, 1);
 SBIT(P02, 0x80, 2);
 SBIT(P03, 0x80, 3);
 SBIT(P04, 0x80, 4);
 SBIT(P05, 0x80, 5);
 SBIT(P06, 0x80, 6);
 SBIT(P07, 0x80, 7);

 SBIT(P10, 0x90, 0);
 SBIT(P11, 0x90, 1);
 SBIT(P12, 0x90, 2);
 SBIT(P13, 0x90, 3);
 SBIT(P14, 0x90, 4);
 SBIT(P15, 0x90, 5);
 SBIT(P16, 0x90, 6);
 SBIT(P17, 0x90, 7);

 SBIT(P20, 0xA0, 0);
 SBIT(P21, 0xA0, 1);
 SBIT(P22, 0xA0, 2);
 SBIT(P23, 0xA0, 3);
 SBIT(P24, 0xA0, 4);
 SBIT(P25, 0xA0, 5);
 SBIT(P26, 0xA0, 6);
 SBIT(P27, 0xA0, 7);

 SBIT(P30, 0xB0, 0);
 SBIT(P31, 0xB0, 1);
 SBIT(P32, 0xB0, 2);
 SBIT(P33, 0xB0, 3);
 SBIT(P34, 0xB0, 4);
 SBIT(P35, 0xB0, 5);
 SBIT(P36, 0xB0, 6);
 SBIT(P37, 0xB0, 7);

 SBIT(P40, 0xC0, 0);
 SBIT(P41, 0xC0, 1);
 SBIT(P42, 0xC0, 2);
 SBIT(P43, 0xC0, 3);
 SBIT(P44, 0xC0, 4);
 SBIT(P45, 0xC0, 5);
 SBIT(P46, 0xC0, 6);
 SBIT(P47, 0xC0, 7);

 SBIT(P50, 0xC8, 0);
 SBIT(P51, 0xC8, 1);
 SBIT(P52, 0xC8, 2);
 SBIT(P53, 0xC8, 3);
 SBIT(P54, 0xC8, 4);
 SBIT(P55, 0xC8, 5);
 SBIT(P56, 0xC8, 6);
 SBIT(P57, 0xC8, 7);

 SBIT(P60, 0xE8, 0);
 SBIT(P61, 0xE8, 1);
 SBIT(P62, 0xE8, 2);
 SBIT(P63, 0xE8, 3);
 SBIT(P64, 0xE8, 4);
 SBIT(P65, 0xE8, 5);
 SBIT(P66, 0xE8, 6);
 SBIT(P67, 0xE8, 7);

 SBIT(P70, 0xF8, 0);
 SBIT(P71, 0xF8, 1);
 SBIT(P72, 0xF8, 2);
 SBIT(P73, 0xF8, 3);
 SBIT(P74, 0xF8, 4);
 SBIT(P75, 0xF8, 5);
 SBIT(P76, 0xF8, 6);
 SBIT(P77, 0xF8, 7);

/*--------------------------------内核特殊功能寄存�?-----------------------------*/
/* sbit    CY                          =PSW^7;
sbit    AC                          =PSW^6;
sbit    F0                          =PSW^5; 
sbit    RS1                         =PSW^4; 
sbit    RS0                         =PSW^3;
sbit    OV                          =PSW^2; 
sbit    P                           =PSW^0;  */
 SBIT(CY, 0xD0, 7);
 SBIT(AC, 0xD0, 6);
 SBIT(F0, 0xD0, 5);
 SBIT(RS1, 0xD0, 4);
 SBIT(RS0, 0xD0, 3);
 SBIT(OV, 0xD0, 2);
/*  SBIT(xx, 0xD0, 1); */
 SBIT(P, 0xD0, 0);
#define IF_ODD(_OE_)                ACC=_OE_;if(P)


#define CLK_SET_SOURCE_HSI          do{CKSEL=((CKSEL&(~0x03))|0x00);}while(0)
#define CLK_SET_SOURCE_HSE          do{CKSEL=((CKSEL&(~0x03))|0x01);}while(0)
#define CLK_SET_SOURCE_LSE          do{CKSEL=((CKSEL&(~0x03))|0x02);}while(0)
#define CLK_SET_SOURCE_LSI          do{CKSEL=((CKSEL&(~0x03))|0x03);}while(0)
#define CLK_HSI_POWER_ON            do{HIRCCR=((HIRCCR&(~0x81))|0x80);}while(!(HIRCCR&0x01))
#define CLK_HSI_POWER_OFF           do{HIRCCR=0x00;}while(0)
#define CLK_HSE_A_POWER_ON          do{XOSCCR=((XOSCCR&(~0xC1))|0x80);}while(!(XOSCCR&0x01))
#define CLK_HSE_P_POWER_ON          do{XOSCCR=((XOSCCR&(~0xC1))|0xC0);}while(!(XOSCCR&0x01))
#define CLK_HSE_POWER_OFF           do{XOSCCR=0x00;}while(0)
#define CLK_HSE_GAIN_ENABLE         do{XOSCCR|= 0x20;}while(0)
#define CLK_HSE_GAIN_DISABLE        do{XOSCCR&=~0x20;}while(0)
#define CLK_LSE_POWER_ON            do{X32KCR=((X32KCR&(~0x81))|0x80);}while(!(X32KCR&0x01))
#define CLK_LSE_POWER_OFF           do{X32KCR  = 0x00;}while(0)
#define CLK_LSE_GAIN_ENABLE         do{X32KCR |= 0x40;}while(0)
#define CLK_LSE_GAIN_DISABLE        do{X32KCR &=~0x40;}while(0)
#define CLK_LSI_POWER_ON            do{IRC32KCR=((IRC32KCR&(~0x81))|0x80);}while(!(IRC32KCR&0x01))
#define CLK_LSI_POWER_OFF           do{IRC32KCR= 0x00;}while(0)
#define CLK_SET_OUT_TO_P54_FA       do{CKSEL  &=~0x08;}while(0)
#define CLK_SET_OUT_TO_P16_FA       do{CKSEL  |= 0x08;}while(0)
#define CLK_OUT_SET_DIV_FA(value)   REG_IN_MASK(CKSEL,0xF0,value)
#define CLK_SET_OUT_TO_P54_GH       do{MCLKOCR&=~0x80;}while(0)
#define CLK_SET_OUT_TO_P16_GH       do{MCLKOCR|= 0x80;}while(0)
#define CLK_OUT_SET_DIV_GH(value)   REG_IN_MASK(MCLKOCR,0x7F,value)

#define CLK_SET_REG_CLKDIV(value)   do{CLKDIV=(u8)value;}while(0)
#define CLK_GET_REG_CLKDIV          (CLKDIV)



#define LVDF                        0x20
#define PLVDH                       0x40


#define EA_ENABLE                   REG_SET_BIT(IE,0x80)
#define EA_DISABLE                  REG_RESET_BIT(IE,0x80)
#define EA_GET                      (IE & 0x80)
#define LVD_IT_ENABLE               do{ELVD=1;}while(0)
#define LVD_IT_DISABLE              do{ELVD=0;}while(0)
#define LVD_GET_IT_FLAG             (PCON & LVDF)
#define LVD_CLS_IT_FLAG             REG_RESET_BIT(PCON,LVDF)
#define LVD_SET_IT_PRIORITY_0       do{IPH&=~PLVDH;PLVD=0;}while(0)
#define LVD_SET_IT_PRIORITY_1       do{IPH&=~PLVDH;PLVD=1;}while(0)
#define LVD_SET_IT_PRIORITY_2       do{IPH|= PLVDH;PLVD=0;}while(0)
#define LVD_SET_IT_PRIORITY_3       do{IPH|= PLVDH;PLVD=1;}while(0)

#define LCMIFIE                     0x80
#define D16_D8                      0x02
#define M68_I80                     0x01
#define ELCMIF                      0x80
#define LCMIFIF                     0x01

#define LCM_IT_ENABLE               do{LCMIFCFG|= LCMIFIE;}while(0)
#define LCM_IT_DISABLE              do{LCMIFCFG&=~LCMIFIE;}while(0)
#define LCM_SET_IT_PRIORITY_0       do{LCMIFCFG=(LCMIFCFG&(~0x30))|0x00;}while(0)
#define LCM_SET_IT_PRIORITY_1       do{LCMIFCFG=(LCMIFCFG&(~0x30))|0x10;}while(0)
#define LCM_SET_IT_PRIORITY_2       do{LCMIFCFG=(LCMIFCFG&(~0x30))|0x20;}while(0)
#define LCM_SET_IT_PRIORITY_3       do{LCMIFCFG=(LCMIFCFG&(~0x30))|0x30;}while(0)
#define LCM_SET_DATABUS_NA_P2       do{LCMIFCFG=(LCMIFCFG&(~0x0E))|0x00;}while(0)
#define LCM_SET_DATABUS_NA_P6       do{LCMIFCFG=(LCMIFCFG&(~0x0E))|0x04;}while(0)
#define LCM_SET_DATABUS_P2_P0       do{LCMIFCFG=(LCMIFCFG&(~0x0E))|0x02;}while(0)
#define LCM_SET_DATABUS_P6_P2       do{LCMIFCFG=(LCMIFCFG&(~0x0E))|0x06;}while(0)
#define LCM_SET_DATABUS_P2_P7       do{LCMIFCFG=(LCMIFCFG&(~0x0E))|0x0A;}while(0)
#define LCM_SET_DATABUS_P6_P7       do{LCMIFCFG=(LCMIFCFG&(~0x0E))|0x0E;}while(0)
#define LCM_SET_MODE_I8080          do{LCMIFCFG&=~M68_I80;}while(0)
#define LCM_SET_MODE_M6800          do{LCMIFCFG|= M68_I80;}while(0)
#define LCM_SET_P41_P44_P43         do{LCMIFCFG2=(LCMIFCFG2&(~0x60))|0x00;}while(0)
#define LCM_SET_P41_P37_P46         do{LCMIFCFG2=(LCMIFCFG2&(~0x60))|0x20;}while(0)
#define LCM_SET_P41_P42_P40         do{LCMIFCFG2=(LCMIFCFG2&(~0x60))|0x40;}while(0)
#define LCM_SET_P40_P37_P36         do{LCMIFCFG2=(LCMIFCFG2&(~0x60))|0x60;}while(0)
#define LCM_WRITE_CMD               do{LCMIFCR=(ELCMIF|0x04);}while(0)
#define LCM_WRITE_DATA              do{LCMIFCR=(ELCMIF|0x05);}while(0)
#define LCM_READ_CMD                do{LCMIFCR=(ELCMIF|0x06);}while(0)
#define LCM_READ_DATA               do{LCMIFCR=(ELCMIF|0x07);}while(0)
#define LCM_GET_FLAG                (LCMIFSTA & LCMIFIF)
#define LCM_CLS_FLAG                do{LCMIFSTA&=~LCMIFIF;}while(0)







#define CIDL                        0x80
#define ECF                         0x01
#define ECOM0_3                     0x40
#define CCAPP0_3                    0x20
#define CCAPN0_3                    0x10
#define MAT0_3                      0x08
#define TOG0_3                      0x04
#define PWM0_3                      0x02
#define ECCF0_3                     0x01

#define PCA_POWER_ON                do{CR=1;}while(0)
#define PCA_POWER_OFF               do{CR=0;}while(0)
#define PCA_IT_ENABLE               do{CMOD|= ECF;}while(0)
#define PCA_IT_DISABLE              do{CMOD&=~ECF;}while(0)
#define PCA_GET_IT_FLAG             (CF)
#define PCA_CLS_IT_FLAG             do{CF=0;}while(0)
#define PCA_SET_IDLE_ENABLE         do{CMOD&=~CIDL;}while(0)
#define PCA_SET_IDLE_DISABLE        do{CMOD|= CIDL;}while(0)
#define PCA_SET_CPS(value)          REG_IN_MASK(CMOD,0x0E,value)
#define PCA_SET_PIN(value)          REG_IN_MASK(P_SW1,0x30,value)
#define PCA0_GET_IT_FLAG            (CCF0)
#define PCA0_CLS_IT_FLAG            do{CCF0=0;}while(0)
#define PCA0_SET_ECOM_ENABLE        do{CCAPM0|= ECOM0_3; }while(0)
#define PCA0_SET_ECOM_DISABLE       do{CCAPM0&=~ECOM0_3; }while(0)
#define PCA0_SET_CCAPP_ENABLE       do{CCAPM0|= CCAPP0_3;}while(0)
#define PCA0_SET_CCAPP_DISABLE      do{CCAPM0&=~CCAPP0_3;}while(0)
#define PCA0_SET_CCAPN_ENABLE       do{CCAPM0|= CCAPN0_3;}while(0)
#define PCA0_SET_CCAPN_DISABLE      do{CCAPM0&=~CCAPN0_3;}while(0)
#define PCA0_SET_MAT_ENABLE         do{CCAPM0|= MAT0_3;  }while(0)
#define PCA0_SET_MAT_DISABLE        do{CCAPM0&=~MAT0_3;  }while(0)
#define PCA0_SET_TOG_ENABLE         do{CCAPM0|= TOG0_3;  }while(0)
#define PCA0_SET_TOG_DISABLE        do{CCAPM0&=~TOG0_3;  }while(0)
#define PCA0_SET_PWM_ENABLE         do{CCAPM0|= PWM0_3;  }while(0)
#define PCA0_SET_PWM_DISABLE        do{CCAPM0&=~PWM0_3;  }while(0)
#define PCA0_SET_ECCF_ENABLE        do{CCAPM0|= ECCF0_3; }while(0)
#define PCA0_SET_ECCF_DISABLE       do{CCAPM0&=~ECCF0_3; }while(0)
#define PCA1_GET_IT_FLAG            (CCF1)
#define PCA1_CLS_IT_FLAG            do{CCF1=0;}while(0)
#define PCA1_SET_ECOM_ENABLE        do{CCAPM1|= ECOM0_3; }while(0)
#define PCA1_SET_ECOM_DISABLE       do{CCAPM1&=~ECOM0_3; }while(0)
#define PCA1_SET_CCAPP_ENABLE       do{CCAPM1|= CCAPP0_3;}while(0)
#define PCA1_SET_CCAPP_DISABLE      do{CCAPM1&=~CCAPP0_3;}while(0)
#define PCA1_SET_CCAPN_ENABLE       do{CCAPM1|= CCAPN0_3;}while(0)
#define PCA1_SET_CCAPN_DISABLE      do{CCAPM1&=~CCAPN0_3;}while(0)
#define PCA1_SET_MAT_ENABLE         do{CCAPM1|= MAT0_3;  }while(0)
#define PCA1_SET_MAT_DISABLE        do{CCAPM1&=~MAT0_3;  }while(0)
#define PCA1_SET_TOG_ENABLE         do{CCAPM1|= TOG0_3;  }while(0)
#define PCA1_SET_TOG_DISABLE        do{CCAPM1&=~TOG0_3;  }while(0)
#define PCA1_SET_PWM_ENABLE         do{CCAPM1|= PWM0_3;  }while(0)
#define PCA1_SET_PWM_DISABLE        do{CCAPM1&=~PWM0_3;  }while(0)
#define PCA1_SET_ECCF_ENABLE        do{CCAPM1|= ECCF0_3; }while(0)
#define PCA1_SET_ECCF_DISABLE       do{CCAPM1&=~ECCF0_3; }while(0)
#define PCA2_GET_IT_FLAG            (CCF2)
#define PCA2_CLS_IT_FLAG            do{CCF2=0;}while(0)
#define PCA2_SET_ECOM_ENABLE        do{CCAPM2|= ECOM0_3; }while(0)
#define PCA2_SET_ECOM_DISABLE       do{CCAPM2&=~ECOM0_3; }while(0)
#define PCA2_SET_CCAPP_ENABLE       do{CCAPM2|= CCAPP0_3;}while(0)
#define PCA2_SET_CCAPP_DISABLE      do{CCAPM2&=~CCAPP0_3;}while(0)
#define PCA2_SET_CCAPN_ENABLE       do{CCAPM2|= CCAPN0_3;}while(0)
#define PCA2_SET_CCAPN_DISABLE      do{CCAPM2&=~CCAPN0_3;}while(0)
#define PCA2_SET_MAT_ENABLE         do{CCAPM2|= MAT0_3;  }while(0)
#define PCA2_SET_MAT_DISABLE        do{CCAPM2&=~MAT0_3;  }while(0)
#define PCA2_SET_TOG_ENABLE         do{CCAPM2|= TOG0_3;  }while(0)
#define PCA2_SET_TOG_DISABLE        do{CCAPM2&=~TOG0_3;  }while(0)
#define PCA2_SET_PWM_ENABLE         do{CCAPM2|= PWM0_3;  }while(0)
#define PCA2_SET_PWM_DISABLE        do{CCAPM2&=~PWM0_3;  }while(0)
#define PCA2_SET_ECCF_ENABLE        do{CCAPM2|= ECCF0_3; }while(0)
#define PCA2_SET_ECCF_DISABLE       do{CCAPM2&=~ECCF0_3; }while(0)
#define PCA3_GET_IT_FLAG            (CCF3)
#define PCA3_CLS_IT_FLAG            do{CCF3=0;}while(0)
#define PCA3_SET_ECOM_ENABLE        do{CCAPM3|= ECOM0_3;  }while(0)
#define PCA3_SET_ECOM_DISABLE       do{CCAPM3&=~ECOM0_3;  }while(0)
#define PCA3_SET_CCAPP_ENABLE       do{CCAPM3|= CCAPP0_3; }while(0)
#define PCA3_SET_CCAPP_DISABLE      do{CCAPM3&=~CCAPP0_3; }while(0)
#define PCA3_SET_CCAPN_ENABLE       do{CCAPM3|= CCAPN0_3; }while(0)
#define PCA3_SET_CCAPN_DISABLE      do{CCAPM3&=~CCAPN0_3; }while(0)
#define PCA3_SET_MAT_ENABLE         do{CCAPM3|= MAT0_3;   }while(0)
#define PCA3_SET_MAT_DISABLE        do{CCAPM3&=~MAT0_3;   }while(0)
#define PCA3_SET_TOG_ENABLE         do{CCAPM3|= TOG0_3;   }while(0)
#define PCA3_SET_TOG_DISABLE        do{CCAPM3&=~TOG0_3;   }while(0)
#define PCA3_SET_PWM_ENABLE         do{CCAPM3|= PWM0_3;   }while(0)
#define PCA3_SET_PWM_DISABLE        do{CCAPM3&=~PWM0_3;   }while(0)
#define PCA3_SET_ECCF_ENABLE        do{CCAPM3|= ECCF0_3;  }while(0)
#define PCA3_SET_ECCF_DISABLE       do{CCAPM3&=~ECCF0_3;  }while(0)

#define PCA_SET_REG_CCON(value)     do{CCON=(u8)(value);}while(0)
#define PCA_GET_REG_CCON            (CCON)
#define PCA_SET_REG_CMOD(value)     do{CMOD=(u8)(value);}while(0)
#define PCA_GET_REG_CMOD            (CMOD)
#define PCA_SET_REG_CL(value)       do{CL=(u8)(value);}while(0)
#define PCA_GET_REG_CL              (CL)
#define PCA_SET_REG_CH(value)       do{CH=(u8)(value);}while(0)
#define PCA_GET_REG_CH              (CH)
#define PCA_SET_REG_CHL(value)      do{CL=(u8)(value);CH=(u8)(value>>8);}while(0)
#define PCA_GET_REG_CHL             ((((u16)CH)<<8)|(u16)CL)
#define PCA_SET_REG_CCAPM0(value)   do{CCAPM0=(u8)value;}while(0)
#define PCA_GET_REG_CCAPM0          (CCAPM0)
#define PCA_SET_REG_CCAP0L(value)   do{CCAP0L=(u8)(value);}while(0)
#define PCA_GET_REG_CCAP0L          (CCAP0L)
#define PCA_SET_REG_CCAP0H(value)   do{CCAP0H=(u8)(value);}while(0)
#define PCA_GET_REG_CCAP0H          (CCAP0H)
#define PCA_SET_REG_CCAP0HL(value)  do{CCAP0L=(u8)(value);CCAP0H=(u8)(value>>8);}while(0)
#define PCA_GET_REG_CCAP0HL         ((((u16)CCAP0H)<<8)|(u16)CCAP0L)
#define PCA_SET_REG_PWM0(value)     do{PCA_PWM0=(u8)(value);}while(0)
#define PCA_GET_REG_PWM0            (PCA_PWM0)
#define PCA_SET_REG_CCAPM1(value)   do{CCAPM1=(u8)value;}while(0)
#define PCA_GET_REG_CCAPM1          (CCAPM1)
#define PCA_SET_REG_CCAP1L(value)   do{CCAP1L=(u8)(value);}while(0)
#define PCA_GET_REG_CCAP1L          (CCAP1L)
#define PCA_SET_REG_CCAP1H(value)   do{CCAP1H=(u8)(value);}while(0)
#define PCA_GET_REG_CCAP1H          (CCAP1H)
#define PCA_SET_REG_CCAP1HL(value)  do{CCAP1L=(u8)(value);CCAP1H=(u8)(value>>8);}while(0)
#define PCA_GET_REG_CCAP1HL         ((((u16)CCAP1H)<<8)|(u16)CCAP1L)
#define PCA_SET_REG_PWM1(value)     do{PCA_PWM1=(u8)(value);}while(0)
#define PCA_GET_REG_PWM1            (PCA_PWM1)
#define PCA_SET_REG_CCAPM2(value)   do{CCAPM2=(u8)value;}while(0)
#define PCA_GET_REG_CCAPM2          (CCAPM2)
#define PCA_SET_REG_CCAP2L(value)   do{CCAP2L=(u8)(value);}while(0)
#define PCA_GET_REG_CCAP2L          (CCAP2L)
#define PCA_SET_REG_CCAP2H(value)   do{CCAP2H=(u8)(value);}while(0)
#define PCA_GET_REG_CCAP2H          (CCAP2H)
#define PCA_SET_REG_CCAP2HL(value)  do{CCAP2L=(u8)(value);CCAP2H=(u8)(value>>8);}while(0)
#define PCA_GET_REG_CCAP2HL         ((((u16)CCAP2H)<<8)|(u16)CCAP2L)
#define PCA_SET_REG_PWM2(value)     do{PCA_PWM2=(u8)(value);}while(0)
#define PCA_GET_REG_PWM2            (PCA_PWM2)
#define PCA_SET_REG_CCAPM3(value)   do{CCAPM3=(u8)value;}while(0)
#define PCA_GET_REG_CCAPM3          (CCAPM3)
#define PCA_SET_REG_CCAP3L(value)   do{CCAP3L=(u8)value;}while(0)
#define PCA_GET_REG_CCAP3L          (CCAP3L)
#define PCA_SET_REG_CCAP3H(value)   do{CCAP3H=(u8)value;}while(0)
#define PCA_GET_REG_CCAP3H          (CCAP3H)
#define PCA_SET_REG_CCAP3HL(value)  do{CCAP3L=(u8)(value);CCAP3H=(u8)(value>>8);}while(0)
#define PCA_GET_REG_CCAP3HL         ((((u16)CCAP3H)<<8)|(u16)CCAP3L)
#define PCA_SET_REG_PWM3(value)     do{PCA_PWM3=(u8)value;}while(0)
#define PCA_GET_REG_PWM3            (PCA_PWM3)

#define PCA_IT_NUM                  interrupt 7

#define M2MIE                       0x80
#define TXACO                       0x40
#define RXACO                       0x20
#define ENM2M                       0x80
#define M2MTRIG                     0x40
#define ADCIE                       0x80
#define ENADC                       0x80
#define A2MTRIG                     0x40
#define SPIIE                       0x80
#define ACT_TX                      0x40
#define ACT_RX                      0x20
#define ENSPI                       0x80
#define S2MTRIG_M                   0x40
#define S2MTRIG_S                   0x20
#define CLRFIFO                     0x01
#define SPIIF                       0x01
#define SPIRXLOSS                   0x02
#define SPITXOVW                    0x04
#define WRPSS                       0x04
#define URTIE                       0x80
#define ENURT                       0x80
#define URTTRIG                     0x40
#define URTIF                       0x01
#define URTXOVW                     0x04
#define URRIE                       0x80
#define ENURR                       0x80
#define URRTRIG                     0x40
#define URRIF                       0x01
#define URRXOVW                     0x04
#define LCMIE                       0x80
#define ENLCM                       0x80
#define TRIGWC                      0x40
#define TRIGWD                      0x20
#define TRIGRC                      0x10
#define TRIGRD                      0x08
#define LCMIF                       0x01
#define LCMTXOVW                    0x02

#define MEM_MEM_IT_ENABLE               do{DMA_M2M_CFG|= M2MIE;}while(0)
#define MEM_MEM_IT_DISABLE              do{DMA_M2M_CFG&=~M2MIE;}while(0)
#define MEM_MEM_SET_TX_ADD              do{DMA_M2M_CFG&=~TXACO;}while(0)
#define MEM_MEM_SET_TX_DEC              do{DMA_M2M_CFG|= TXACO;}while(0)
#define MEM_MEM_SET_RX_ADD              do{DMA_M2M_CFG&=~RXACO;}while(0)
#define MEM_MEM_SET_RX_DEC              do{DMA_M2M_CFG|= RXACO;}while(0)
#define MEM_MEM_SET_IT_PRIORITY_0       do{DMA_M2M_CFG=((DMA_M2M_CFG&(~0x0C))|0x00);}while(0)
#define MEM_MEM_SET_IT_PRIORITY_1       do{DMA_M2M_CFG=((DMA_M2M_CFG&(~0x0C))|0x04);}while(0)
#define MEM_MEM_SET_IT_PRIORITY_2       do{DMA_M2M_CFG=((DMA_M2M_CFG&(~0x0C))|0x08);}while(0)
#define MEM_MEM_SET_IT_PRIORITY_3       do{DMA_M2M_CFG=((DMA_M2M_CFG&(~0x0C))|0x0C);}while(0)
#define MEM_MEM_SET_BUS_PRIORITY_0      do{DMA_M2M_CFG=((DMA_M2M_CFG&(~0x03))|0x00);}while(0)
#define MEM_MEM_SET_BUS_PRIORITY_1      do{DMA_M2M_CFG=((DMA_M2M_CFG&(~0x03))|0x01);}while(0)
#define MEM_MEM_SET_BUS_PRIORITY_2      do{DMA_M2M_CFG=((DMA_M2M_CFG&(~0x03))|0x02);}while(0)
#define MEM_MEM_SET_BUS_PRIORITY_3      do{DMA_M2M_CFG=((DMA_M2M_CFG&(~0x03))|0x03);}while(0)
#define MEM_MEM_ENABLE                  do{DMA_M2M_CR|= ENM2M;}while(0)
#define MEM_MEM_DISABLE                 do{DMA_M2M_CR&=~ENM2M;}while(0)
#define MEM_MEM_START                   do{DMA_M2M_CR|= M2MTRIG;}while(0)
#define MEM_MEM_GET_FLAG                (DMA_M2M_STA)
#define MEM_MEM_CLS_FLAG                do{DMA_M2M_STA=0;}while(0)
#define MEM_MEM_SET_COUNT_MAX(value)    do{DMA_M2M_AMT=(u8)(value);}while(0)
#define MEM_MEM_GET_COUNT_DONE          (DMA_M2M_DONE)
#define MEM_MEM_SET_TX_ADDR(value)      do{DMA_M2M_TXA=(u16)(value);}while(0)
#define MEM_MEM_SET_RX_ADDR(value)      do{DMA_M2M_RXA=(u16)(value);}while(0)
#define ADC_MEM_IT_ENABLE               do{DMA_ADC_CFG|= ADCIE;}while(0)
#define ADC_MEM_IT_DISABLE              do{DMA_ADC_CFG&=~ADCIE;}while(0)
#define ADC_MEM_SET_IT_PRIORITY_0       do{DMA_ADC_CFG=((DMA_ADC_CFG&(~0x0C))|0x00);}while(0)
#define ADC_MEM_SET_IT_PRIORITY_1       do{DMA_ADC_CFG=((DMA_ADC_CFG&(~0x0C))|0x04);}while(0)
#define ADC_MEM_SET_IT_PRIORITY_2       do{DMA_ADC_CFG=((DMA_ADC_CFG&(~0x0C))|0x08);}while(0)
#define ADC_MEM_SET_IT_PRIORITY_3       do{DMA_ADC_CFG=((DMA_ADC_CFG&(~0x0C))|0x0C);}while(0)
#define ADC_MEM_SET_BUS_PRIORITY_0      do{DMA_ADC_CFG=((DMA_ADC_CFG&(~0x03))|0x00);}while(0)
#define ADC_MEM_SET_BUS_PRIORITY_1      do{DMA_ADC_CFG=((DMA_ADC_CFG&(~0x03))|0x01);}while(0)
#define ADC_MEM_SET_BUS_PRIORITY_2      do{DMA_ADC_CFG=((DMA_ADC_CFG&(~0x03))|0x02);}while(0)
#define ADC_MEM_SET_BUS_PRIORITY_3      do{DMA_ADC_CFG=((DMA_ADC_CFG&(~0x03))|0x03);}while(0)
#define ADC_MEM_ENABLE                  do{DMA_ADC_CR|= ENADC;}while(0)
#define ADC_MEM_DISABLE                 do{DMA_ADC_CR&=~ENADC;}while(0)
#define ADC_MEM_START                   do{DMA_ADC_CR|= A2MTRIG;}while(0)
#define ADC_MEM_GET_FLAG                (DMA_ADC_STA)
#define ADC_MEM_CLS_FLAG                do{DMA_ADC_STA=0;}while(0)
#define ADC_MEM_SET_RX_ADDR(value)      do{DMA_ADC_RXA=(u16)(value);}while(0)
#define ADC_MEM_SET_CH_COUNT(value)     do{DMA_ADC_CFG2=((u8)(value)&0x0F);}while(0)
#define ADC_MEM_SET_CH_0_7_EN(value)    do{DMA_ADC_CHSW1=(u8)(value);}while(0)
#define ADC_MEM_SET_CH_8_15_EN(value)   do{DMA_ADC_CHSW0=(u8)(value);}while(0)
#define SPI_MEM_IT_ENABLE               do{DMA_SPI_CFG|= SPIIE;}while(0)
#define SPI_MEM_IT_DISABLE              do{DMA_SPI_CFG&=~SPIIE;}while(0)
#define SPI_MEM_SET_TX_ENABLE           do{DMA_SPI_CFG|= ACT_TX;}while(0)
#define SPI_MEM_SET_TX_DISABLE          do{DMA_SPI_CFG&=~ACT_TX;}while(0)
#define SPI_MEM_SET_RX_ENABLE           do{DMA_SPI_CFG|= ACT_RX;}while(0)
#define SPI_MEM_SET_RX_DISABLE          do{DMA_SPI_CFG&=~ACT_RX;}while(0)
#define SPI_MEM_SET_IT_PRIORITY_0       do{DMA_SPI_CFG=((DMA_SPI_CFG&(~0x0C))|0x00);}while(0)
#define SPI_MEM_SET_IT_PRIORITY_1       do{DMA_SPI_CFG=((DMA_SPI_CFG&(~0x0C))|0x04);}while(0)
#define SPI_MEM_SET_IT_PRIORITY_2       do{DMA_SPI_CFG=((DMA_SPI_CFG&(~0x0C))|0x08);}while(0)
#define SPI_MEM_SET_IT_PRIORITY_3       do{DMA_SPI_CFG=((DMA_SPI_CFG&(~0x0C))|0x0C);}while(0)
#define SPI_MEM_SET_BUS_PRIORITY_0      do{DMA_SPI_CFG=((DMA_SPI_CFG&(~0x03))|0x00);}while(0)
#define SPI_MEM_SET_BUS_PRIORITY_1      do{DMA_SPI_CFG=((DMA_SPI_CFG&(~0x03))|0x01);}while(0)
#define SPI_MEM_SET_BUS_PRIORITY_2      do{DMA_SPI_CFG=((DMA_SPI_CFG&(~0x03))|0x02);}while(0)
#define SPI_MEM_SET_BUS_PRIORITY_3      do{DMA_SPI_CFG=((DMA_SPI_CFG&(~0x03))|0x03);}while(0)
#define SPI_MEM_ENABLE                  do{DMA_SPI_CR|= ENSPI;}while(0)
#define SPI_MEM_DISABLE                 do{DMA_SPI_CR&=~ENSPI;}while(0)
#define SPI_MEM_MODE_M_START            do{DMA_SPI_CR|= S2MTRIG_M;}while(0)
#define SPI_MEM_MODE_S_START            do{DMA_SPI_CR|= S2MTRIG_S;}while(0)
#define SPI_MEM_CLS_FIFO                do{DMA_SPI_CR|= CLRFIFO;}while(0)
#define SPI_MEM_GET_FLAG                (DMA_SPI_STA & SPIIF)
#define SPI_MEM_GET_FLAG_RXLOSS         (DMA_SPI_STA & SPIRXLOSS)
#define SPI_MEM_GET_FLAG_TXOVW          (DMA_SPI_STA & SPITXOVW)
#define SPI_MEM_CLS_FLAG                do{DMA_SPI_STA&=~SPIIF;}while(0)
#define SPI_MEM_CLS_FLAG_RXLOSS         do{DMA_SPI_STA&=~SPIRXLOSS;}while(0)
#define SPI_MEM_CLS_FLAG_TXOVW          do{DMA_SPI_STA&=~SPITXOVW;}while(0)
#define SPI_MEM_SET_COUNT_MAX(value)    do{DMA_SPI_AMT=(u8)(value);}while(0)
#define SPI_MEM_GET_COUNT_DONE          (DMA_SPI_DONE)
#define SPI_MEM_SET_TX_ADDR(value)      do{DMA_SPI_TXA=(u16)(value);}while(0)
#define SPI_MEM_SET_RX_ADDR(value)      do{DMA_SPI_RXA=(u16)(value);}while(0)
#define SPI_MEM_SET_SS_AUTO_ENABLE      do{DMA_SPI_CFG2|= WRPSS;}while(0)
#define SPI_MEM_SET_SS_AUTO_DISABLE     do{DMA_SPI_CFG2&=~WRPSS;}while(0)
#define SPI_MEM_SET_SS_P12              do{DMA_SPI_CFG2=(DMA_SPI_CFG2&(~0x03))|0x00;}while(0)
#define SPI_MEM_SET_SS_P22              do{DMA_SPI_CFG2=(DMA_SPI_CFG2&(~0x03))|0x01;}while(0)
#define SPI_MEM_SET_SS_P74              do{DMA_SPI_CFG2=(DMA_SPI_CFG2&(~0x03))|0x02;}while(0)
#define SPI_MEM_SET_SS_P35              do{DMA_SPI_CFG2=(DMA_SPI_CFG2&(~0x03))|0x03;}while(0)
#define UR1_MEM_TX_IT_ENABLE            do{DMA_UR1T_CFG|= URTIE;}while(0)
#define UR1_MEM_TX_IT_DISABLE           do{DMA_UR1T_CFG|= URTIE;}while(0)
#define UR1_MEM_RX_IT_ENABLE            do{DMA_UR1R_CFG|= URRIE;}while(0)
#define UR1_MEM_RX_IT_DISABLE           do{DMA_UR1R_CFG|= URRIE;}while(0)
#define UR1_MEM_SET_TX_IT_PRIORITY_0    do{DMA_UR1T_CFG=((DMA_UR1T_CFG&(~0x0C))|0x00);}while(0)
#define UR1_MEM_SET_TX_IT_PRIORITY_1    do{DMA_UR1T_CFG=((DMA_UR1T_CFG&(~0x0C))|0x04);}while(0)
#define UR1_MEM_SET_TX_IT_PRIORITY_2    do{DMA_UR1T_CFG=((DMA_UR1T_CFG&(~0x0C))|0x08);}while(0)
#define UR1_MEM_SET_TX_IT_PRIORITY_3    do{DMA_UR1T_CFG=((DMA_UR1T_CFG&(~0x0C))|0x0C);}while(0)
#define UR1_MEM_SET_RX_IT_PRIORITY_0    do{DMA_UR1R_CFG=((DMA_UR1R_CFG&(~0x0C))|0x00);}while(0)
#define UR1_MEM_SET_RX_IT_PRIORITY_1    do{DMA_UR1R_CFG=((DMA_UR1R_CFG&(~0x0C))|0x04);}while(0)
#define UR1_MEM_SET_RX_IT_PRIORITY_2    do{DMA_UR1R_CFG=((DMA_UR1R_CFG&(~0x0C))|0x08);}while(0)
#define UR1_MEM_SET_RX_IT_PRIORITY_3    do{DMA_UR1R_CFG=((DMA_UR1R_CFG&(~0x0C))|0x0C);}while(0)
#define UR1_MEM_SET_TX_BUS_PRIORITY_0   do{DMA_UR1T_CFG=((DMA_UR1T_CFG&(~0x03))|0x00);}while(0)
#define UR1_MEM_SET_TX_BUS_PRIORITY_1   do{DMA_UR1T_CFG=((DMA_UR1T_CFG&(~0x03))|0x01);}while(0)
#define UR1_MEM_SET_TX_BUS_PRIORITY_2   do{DMA_UR1T_CFG=((DMA_UR1T_CFG&(~0x03))|0x02);}while(0)
#define UR1_MEM_SET_TX_BUS_PRIORITY_3   do{DMA_UR1T_CFG=((DMA_UR1T_CFG&(~0x03))|0x03);}while(0)
#define UR1_MEM_SET_RX_BUS_PRIORITY_0   do{DMA_UR1R_CFG=((DMA_UR1R_CFG&(~0x03))|0x00);}while(0)
#define UR1_MEM_SET_RX_BUS_PRIORITY_1   do{DMA_UR1R_CFG=((DMA_UR1R_CFG&(~0x03))|0x01);}while(0)
#define UR1_MEM_SET_RX_BUS_PRIORITY_2   do{DMA_UR1R_CFG=((DMA_UR1R_CFG&(~0x03))|0x02);}while(0)
#define UR1_MEM_SET_RX_BUS_PRIORITY_3   do{DMA_UR1R_CFG=((DMA_UR1R_CFG&(~0x03))|0x03);}while(0)
#define UR1_MEM_TX_ENABLE               do{DMA_UR1T_CR|= ENURT;}while(0)
#define UR1_MEM_TX_DISABLE              do{DMA_UR1T_CR&=~ENURT;}while(0)
#define UR1_MEM_RX_ENABLE               do{DMA_UR1R_CR|= ENURR;}while(0)
#define UR1_MEM_RX_DISABLE              do{DMA_UR1R_CR&=~ENURR;}while(0)
#define UR1_MEM_TX_START                do{DMA_UR1T_CR|= URTTRIG;}while(0)
#define UR1_MEM_RX_START                do{DMA_UR1R_CR|= URRTRIG;}while(0)
#define UR1_MEM_GET_TX_FLAG             (DMA_UR1T_STA & URTIF)
#define UR1_MEM_GET_TX_FLAG_TXOVW       (DMA_UR1T_STA & URTXOVW)
#define UR1_MEM_GET_RX_FLAG             (DMA_UR1R_STA & URRIF)
#define UR1_MEM_GET_RX_FLAG_RXOVW       (DMA_UR1R_STA & URRXOVW)
#define UR1_MEM_CLS_TX_FLAG             do{DMA_UR1T_STA&=~URTIF;}while(0)
#define UR1_MEM_CLS_TX_FLAG_TXOVW       do{DMA_UR1T_STA&=~URTXOVW;}while(0)
#define UR1_MEM_CLS_RX_FLAG             do{DMA_UR1R_STA&=~URRIF;}while(0)
#define UR1_MEM_CLS_RX_FLAG_RXOVW       do{DMA_UR1R_STA&=~URRXOVW;}while(0)
#define UR1_MEM_SET_TX_COUNT_MAX(value) do{DMA_UR1T_AMT=(u8)(value);}while(0)
#define UR1_MEM_GET_TX_COUNT_DONE       (DMA_UR1T_DONE)
#define UR1_MEM_SET_RX_COUNT_MAX(value) do{DMA_UR1R_AMT=(u8)(value);}while(0)
#define UR1_MEM_GET_RX_COUNT_DONE       (DMA_UR1R_DONE)
#define UR1_MEM_SET_TX_ADDR(value)      do{DMA_UR1T_TXA=(u16)(value);}while(0)
#define UR1_MEM_SET_RX_ADDR(value)      do{DMA_UR1R_RXA=(u16)(value);}while(0)
#define UR2_MEM_TX_IT_ENABLE            do{DMA_UR2T_CFG|= URTIE;}while(0)
#define UR2_MEM_TX_IT_DISABLE           do{DMA_UR2T_CFG|= URTIE;}while(0)
#define UR2_MEM_RX_IT_ENABLE            do{DMA_UR2R_CFG|= URRIE;}while(0)
#define UR2_MEM_RX_IT_DISABLE           do{DMA_UR2R_CFG|= URRIE;}while(0)
#define UR2_MEM_SET_TX_IT_PRIORITY_0    do{DMA_UR2T_CFG=((DMA_UR2T_CFG&(~0x0C))|0x00);}while(0)
#define UR2_MEM_SET_TX_IT_PRIORITY_1    do{DMA_UR2T_CFG=((DMA_UR2T_CFG&(~0x0C))|0x04);}while(0)
#define UR2_MEM_SET_TX_IT_PRIORITY_2    do{DMA_UR2T_CFG=((DMA_UR2T_CFG&(~0x0C))|0x08);}while(0)
#define UR2_MEM_SET_TX_IT_PRIORITY_3    do{DMA_UR2T_CFG=((DMA_UR2T_CFG&(~0x0C))|0x0C);}while(0)
#define UR2_MEM_SET_RX_IT_PRIORITY_0    do{DMA_UR2R_CFG=((DMA_UR2R_CFG&(~0x0C))|0x00);}while(0)
#define UR2_MEM_SET_RX_IT_PRIORITY_1    do{DMA_UR2R_CFG=((DMA_UR2R_CFG&(~0x0C))|0x04);}while(0)
#define UR2_MEM_SET_RX_IT_PRIORITY_2    do{DMA_UR2R_CFG=((DMA_UR2R_CFG&(~0x0C))|0x08);}while(0)
#define UR2_MEM_SET_RX_IT_PRIORITY_3    do{DMA_UR2R_CFG=((DMA_UR2R_CFG&(~0x0C))|0x0C);}while(0)
#define UR2_MEM_SET_TX_BUS_PRIORITY_0   do{DMA_UR2T_CFG=((DMA_UR2T_CFG&(~0x03))|0x00);}while(0)
#define UR2_MEM_SET_TX_BUS_PRIORITY_1   do{DMA_UR2T_CFG=((DMA_UR2T_CFG&(~0x03))|0x01);}while(0)
#define UR2_MEM_SET_TX_BUS_PRIORITY_2   do{DMA_UR2T_CFG=((DMA_UR2T_CFG&(~0x03))|0x02);}while(0)
#define UR2_MEM_SET_TX_BUS_PRIORITY_3   do{DMA_UR2T_CFG=((DMA_UR2T_CFG&(~0x03))|0x03);}while(0)
#define UR2_MEM_SET_RX_BUS_PRIORITY_0   do{DMA_UR2R_CFG=((DMA_UR2R_CFG&(~0x03))|0x00);}while(0)
#define UR2_MEM_SET_RX_BUS_PRIORITY_1   do{DMA_UR2R_CFG=((DMA_UR2R_CFG&(~0x03))|0x01);}while(0)
#define UR2_MEM_SET_RX_BUS_PRIORITY_2   do{DMA_UR2R_CFG=((DMA_UR2R_CFG&(~0x03))|0x02);}while(0)
#define UR2_MEM_SET_RX_BUS_PRIORITY_3   do{DMA_UR2R_CFG=((DMA_UR2R_CFG&(~0x03))|0x03);}while(0)
#define UR2_MEM_TX_ENABLE               do{DMA_UR2T_CR|= ENURT;}while(0)
#define UR2_MEM_TX_DISABLE              do{DMA_UR2T_CR&=~ENURT;}while(0)
#define UR2_MEM_RX_ENABLE               do{DMA_UR2R_CR|= ENURR;}while(0)
#define UR2_MEM_RX_DISABLE              do{DMA_UR2R_CR&=~ENURR;}while(0)
#define UR2_MEM_TX_START                do{DMA_UR2T_CR|= URTTRIG;}while(0)
#define UR2_MEM_RX_START                do{DMA_UR2R_CR|= URRTRIG;}while(0)
#define UR2_MEM_GET_TX_FLAG             (DMA_UR2T_STA & URTIF)
#define UR2_MEM_GET_TX_FLAG_TXOVW       (DMA_UR2T_STA & URTXOVW)
#define UR2_MEM_GET_RX_FLAG             (DMA_UR2R_STA & URRIF)
#define UR2_MEM_GET_RX_FLAG_RXOVW       (DMA_UR2R_STA & URRXOVW)
#define UR2_MEM_CLS_TX_FLAG             do{DMA_UR2T_STA&=~URTIF;}while(0)
#define UR2_MEM_CLS_TX_FLAG_TXOVW       do{DMA_UR2T_STA&=~URTXOVW;}while(0)
#define UR2_MEM_CLS_RX_FLAG             do{DMA_UR2R_STA&=~URRIF;}while(0)
#define UR2_MEM_CLS_RX_FLAG_RXOVW       do{DMA_UR2R_STA&=~URRXOVW;}while(0)
#define UR2_MEM_SET_TX_COUNT_MAX(value) do{DMA_UR2T_AMT=(u8)(value);}while(0)
#define UR2_MEM_GET_TX_COUNT_DONE       (DMA_UR2T_DONE)
#define UR2_MEM_SET_RX_COUNT_MAX(value) do{DMA_UR2R_AMT=(u8)(value);}while(0)
#define UR2_MEM_GET_RX_COUNT_DONE       (DMA_UR2R_DONE)
#define UR2_MEM_SET_TX_ADDR(value)      do{DMA_UR2T_TXA=(u16)(value);}while(0)
#define UR2_MEM_SET_RX_ADDR(value)      do{DMA_UR2R_RXA=(u16)(value);}while(0)
#define UR3_MEM_TX_IT_ENABLE            do{DMA_UR3T_CFG|= URTIE;}while(0)
#define UR3_MEM_TX_IT_DISABLE           do{DMA_UR3T_CFG|= URTIE;}while(0)
#define UR3_MEM_RX_IT_ENABLE            do{DMA_UR3R_CFG|= URRIE;}while(0)
#define UR3_MEM_RX_IT_DISABLE           do{DMA_UR3R_CFG|= URRIE;}while(0)
#define UR3_MEM_SET_TX_IT_PRIORITY_0    do{DMA_UR3T_CFG=((DMA_UR3T_CFG&(~0x0C))|0x00);}while(0)
#define UR3_MEM_SET_TX_IT_PRIORITY_1    do{DMA_UR3T_CFG=((DMA_UR3T_CFG&(~0x0C))|0x04);}while(0)
#define UR3_MEM_SET_TX_IT_PRIORITY_2    do{DMA_UR3T_CFG=((DMA_UR3T_CFG&(~0x0C))|0x08);}while(0)
#define UR3_MEM_SET_TX_IT_PRIORITY_3    do{DMA_UR3T_CFG=((DMA_UR3T_CFG&(~0x0C))|0x0C);}while(0)
#define UR3_MEM_SET_RX_IT_PRIORITY_0    do{DMA_UR3R_CFG=((DMA_UR3R_CFG&(~0x0C))|0x00);}while(0)
#define UR3_MEM_SET_RX_IT_PRIORITY_1    do{DMA_UR3R_CFG=((DMA_UR3R_CFG&(~0x0C))|0x04);}while(0)
#define UR3_MEM_SET_RX_IT_PRIORITY_2    do{DMA_UR3R_CFG=((DMA_UR3R_CFG&(~0x0C))|0x08);}while(0)
#define UR3_MEM_SET_RX_IT_PRIORITY_3    do{DMA_UR3R_CFG=((DMA_UR3R_CFG&(~0x0C))|0x0C);}while(0)
#define UR3_MEM_SET_TX_BUS_PRIORITY_0   do{DMA_UR3T_CFG=((DMA_UR3T_CFG&(~0x03))|0x00);}while(0)
#define UR3_MEM_SET_TX_BUS_PRIORITY_1   do{DMA_UR3T_CFG=((DMA_UR3T_CFG&(~0x03))|0x01);}while(0)
#define UR3_MEM_SET_TX_BUS_PRIORITY_2   do{DMA_UR3T_CFG=((DMA_UR3T_CFG&(~0x03))|0x02);}while(0)
#define UR3_MEM_SET_TX_BUS_PRIORITY_3   do{DMA_UR3T_CFG=((DMA_UR3T_CFG&(~0x03))|0x03);}while(0)
#define UR3_MEM_SET_RX_BUS_PRIORITY_0   do{DMA_UR3R_CFG=((DMA_UR3R_CFG&(~0x03))|0x00);}while(0)
#define UR3_MEM_SET_RX_BUS_PRIORITY_1   do{DMA_UR3R_CFG=((DMA_UR3R_CFG&(~0x03))|0x01);}while(0)
#define UR3_MEM_SET_RX_BUS_PRIORITY_2   do{DMA_UR3R_CFG=((DMA_UR3R_CFG&(~0x03))|0x02);}while(0)
#define UR3_MEM_SET_RX_BUS_PRIORITY_3   do{DMA_UR3R_CFG=((DMA_UR3R_CFG&(~0x03))|0x03);}while(0)
#define UR3_MEM_TX_ENABLE               do{DMA_UR3T_CR|= ENURT;}while(0)
#define UR3_MEM_TX_DISABLE              do{DMA_UR3T_CR&=~ENURT;}while(0)
#define UR3_MEM_RX_ENABLE               do{DMA_UR3R_CR|= ENURR;}while(0)
#define UR3_MEM_RX_DISABLE              do{DMA_UR3R_CR&=~ENURR;}while(0)
#define UR3_MEM_TX_START                do{DMA_UR3T_CR|= URTTRIG;}while(0)
#define UR3_MEM_RX_START                do{DMA_UR3R_CR|= URRTRIG;}while(0)
#define UR3_MEM_GET_TX_FLAG             (DMA_UR3T_STA & URTIF)
#define UR3_MEM_GET_TX_FLAG_TXOVW       (DMA_UR3T_STA & URTXOVW)
#define UR3_MEM_GET_RX_FLAG             (DMA_UR3R_STA & URRIF)
#define UR3_MEM_GET_RX_FLAG_RXOVW       (DMA_UR3R_STA & URRXOVW)
#define UR3_MEM_CLS_TX_FLAG             do{DMA_UR3T_STA&=~URTIF;}while(0)
#define UR3_MEM_CLS_TX_FLAG_TXOVW       do{DMA_UR3T_STA&=~URTXOVW;}while(0)
#define UR3_MEM_CLS_RX_FLAG             do{DMA_UR3R_STA&=~URRIF;}while(0)
#define UR3_MEM_CLS_RX_FLAG_RXOVW       do{DMA_UR3R_STA&=~URRXOVW;}while(0)
#define UR3_MEM_SET_TX_COUNT_MAX(value) do{DMA_UR3T_AMT=(u8)(value);}while(0)
#define UR3_MEM_GET_TX_COUNT_DONE       (DMA_UR3T_DONE)
#define UR3_MEM_SET_RX_COUNT_MAX(value) do{DMA_UR3R_AMT=(u8)(value);}while(0)
#define UR3_MEM_GET_RX_COUNT_DONE       (DMA_UR3R_DONE)
#define UR3_MEM_SET_TX_ADDR(value)      do{DMA_UR3T_TXA=(u16)(value);}while(0)
#define UR3_MEM_SET_RX_ADDR(value)      do{DMA_UR3R_RXA=(u16)(value);}while(0)
#define UR4_MEM_TX_IT_ENABLE            do{DMA_UR4T_CFG|= URTIE;}while(0)
#define UR4_MEM_TX_IT_DISABLE           do{DMA_UR4T_CFG|= URTIE;}while(0)
#define UR4_MEM_RX_IT_ENABLE            do{DMA_UR4R_CFG|= URRIE;}while(0)
#define UR4_MEM_RX_IT_DISABLE           do{DMA_UR4R_CFG|= URRIE;}while(0)
#define UR4_MEM_SET_TX_IT_PRIORITY_0    do{DMA_UR4T_CFG=((DMA_UR4T_CFG&(~0x0C))|0x00);}while(0)
#define UR4_MEM_SET_TX_IT_PRIORITY_1    do{DMA_UR4T_CFG=((DMA_UR4T_CFG&(~0x0C))|0x04);}while(0)
#define UR4_MEM_SET_TX_IT_PRIORITY_2    do{DMA_UR4T_CFG=((DMA_UR4T_CFG&(~0x0C))|0x08);}while(0)
#define UR4_MEM_SET_TX_IT_PRIORITY_3    do{DMA_UR4T_CFG=((DMA_UR4T_CFG&(~0x0C))|0x0C);}while(0)
#define UR4_MEM_SET_RX_IT_PRIORITY_0    do{DMA_UR4R_CFG=((DMA_UR4R_CFG&(~0x0C))|0x00);}while(0)
#define UR4_MEM_SET_RX_IT_PRIORITY_1    do{DMA_UR4R_CFG=((DMA_UR4R_CFG&(~0x0C))|0x04);}while(0)
#define UR4_MEM_SET_RX_IT_PRIORITY_2    do{DMA_UR4R_CFG=((DMA_UR4R_CFG&(~0x0C))|0x08);}while(0)
#define UR4_MEM_SET_RX_IT_PRIORITY_3    do{DMA_UR4R_CFG=((DMA_UR4R_CFG&(~0x0C))|0x0C);}while(0)
#define UR4_MEM_SET_TX_BUS_PRIORITY_0   do{DMA_UR4T_CFG=((DMA_UR4T_CFG&(~0x03))|0x00);}while(0)
#define UR4_MEM_SET_TX_BUS_PRIORITY_1   do{DMA_UR4T_CFG=((DMA_UR4T_CFG&(~0x03))|0x01);}while(0)
#define UR4_MEM_SET_TX_BUS_PRIORITY_2   do{DMA_UR4T_CFG=((DMA_UR4T_CFG&(~0x03))|0x02);}while(0)
#define UR4_MEM_SET_TX_BUS_PRIORITY_3   do{DMA_UR4T_CFG=((DMA_UR4T_CFG&(~0x03))|0x03);}while(0)
#define UR4_MEM_SET_RX_BUS_PRIORITY_0   do{DMA_UR4R_CFG=((DMA_UR4R_CFG&(~0x03))|0x00);}while(0)
#define UR4_MEM_SET_RX_BUS_PRIORITY_1   do{DMA_UR4R_CFG=((DMA_UR4R_CFG&(~0x03))|0x01);}while(0)
#define UR4_MEM_SET_RX_BUS_PRIORITY_2   do{DMA_UR4R_CFG=((DMA_UR4R_CFG&(~0x03))|0x02);}while(0)
#define UR4_MEM_SET_RX_BUS_PRIORITY_3   do{DMA_UR4R_CFG=((DMA_UR4R_CFG&(~0x03))|0x03);}while(0)
#define UR4_MEM_TX_ENABLE               do{DMA_UR4T_CR|= ENURT;}while(0)
#define UR4_MEM_TX_DISABLE              do{DMA_UR4T_CR&=~ENURT;}while(0)
#define UR4_MEM_RX_ENABLE               do{DMA_UR4R_CR|= ENURR;}while(0)
#define UR4_MEM_RX_DISABLE              do{DMA_UR4R_CR&=~ENURR;}while(0)
#define UR4_MEM_TX_START                do{DMA_UR4T_CR|= URTTRIG;}while(0)
#define UR4_MEM_RX_START                do{DMA_UR4R_CR|= URRTRIG;}while(0)
#define UR4_MEM_GET_TX_FLAG             (DMA_UR4T_STA & URTIF)
#define UR4_MEM_GET_TX_FLAG_TXOVW       (DMA_UR4T_STA & URTXOVW)
#define UR4_MEM_GET_RX_FLAG             (DMA_UR4R_STA & URRIF)
#define UR4_MEM_GET_RX_FLAG_RXOVW       (DMA_UR4R_STA & URRXOVW)
#define UR4_MEM_CLS_TX_FLAG             do{DMA_UR4T_STA&=~URTIF;}while(0)
#define UR4_MEM_CLS_TX_FLAG_TXOVW       do{DMA_UR4T_STA&=~URTXOVW;}while(0)
#define UR4_MEM_CLS_RX_FLAG             do{DMA_UR4R_STA&=~URRIF;}while(0)
#define UR4_MEM_CLS_RX_FLAG_RXOVW       do{DMA_UR4R_STA&=~URRXOVW;}while(0)
#define UR4_MEM_SET_TX_COUNT_MAX(value) do{DMA_UR4T_AMT=(u8)(value);}while(0)
#define UR4_MEM_GET_TX_COUNT_DONE       (DMA_UR4T_DONE)
#define UR4_MEM_SET_RX_COUNT_MAX(value) do{DMA_UR4R_AMT=(u8)(value);}while(0)
#define UR4_MEM_GET_RX_COUNT_DONE       (DMA_UR4R_DONE)
#define UR4_MEM_SET_TX_ADDR(value)      do{DMA_UR4T_TXA=(u16)(value);}while(0)
#define UR4_MEM_SET_RX_ADDR(value)      do{DMA_UR4R_RXA=(u16)(value);}while(0)
#define LCM_MEM_IT_ENABLE               do{DMA_LCM_CFG|= LCMIE;}while(0)
#define LCM_MEM_IT_DISABLE              do{DMA_LCM_CFG&=~LCMIE;}while(0)
#define LCM_MEM_SET_IT_PRIORITY_0       do{DMA_LCM_CFG=((DMA_LCM_CFG&(~0x0C))|0x00);}while(0)
#define LCM_MEM_SET_IT_PRIORITY_1       do{DMA_LCM_CFG=((DMA_LCM_CFG&(~0x0C))|0x04);}while(0)
#define LCM_MEM_SET_IT_PRIORITY_2       do{DMA_LCM_CFG=((DMA_LCM_CFG&(~0x0C))|0x08);}while(0)
#define LCM_MEM_SET_IT_PRIORITY_3       do{DMA_LCM_CFG=((DMA_LCM_CFG&(~0x0C))|0x0C);}while(0)
#define LCM_MEM_SET_BUS_PRIORITY_0      do{DMA_LCM_CFG=((DMA_LCM_CFG&(~0x03))|0x00);}while(0)
#define LCM_MEM_SET_BUS_PRIORITY_1      do{DMA_LCM_CFG=((DMA_LCM_CFG&(~0x03))|0x01);}while(0)
#define LCM_MEM_SET_BUS_PRIORITY_2      do{DMA_LCM_CFG=((DMA_LCM_CFG&(~0x03))|0x02);}while(0)
#define LCM_MEM_SET_BUS_PRIORITY_3      do{DMA_LCM_CFG=((DMA_LCM_CFG&(~0x03))|0x03);}while(0)
#define LCM_MEM_ENABLE                  do{DMA_LCM_CR|= ENLCM;}while(0)
#define LCM_MEM_DISABLE                 do{DMA_LCM_CR&=~ENLCM;}while(0)
#define LCM_MEM_START_TX_CMD            do{DMA_LCM_CR|= TRIGWC;}while(0)
#define LCM_MEM_START_TX_DAT            do{DMA_LCM_CR|= TRIGWD;}while(0)
#define LCM_MEM_START_RX_CMD            do{DMA_LCM_CR|= TRIGRC;}while(0)
#define LCM_MEM_START_RX_DAT            do{DMA_LCM_CR|= TRIGRD;}while(0)
#define LCM_MEM_GET_FLAG                (DMA_LCM_STA & LCMIF)
#define LCM_MEM_GET_FLAG_TXOVW          (DMA_LCM_STA & LCMTXOVW)
#define LCM_MEM_CLS_FLAG                (DMA_LCM_STA&=~LCMIF)
#define LCM_MEM_CLS_FLAG_TXOVW          (DMA_LCM_STA&=~LCMTXOVW)
#define LCM_MEM_SET_COUNT_MAX(value)    do{DMA_LCM_AMT=(u8)(value);}while(0)
#define LCM_MEM_GET_COUNT_DONE          (DMA_LCM_DONE)
#define LCM_MEM_SET_TX_ADDR(value)      do{DMA_LCM_TXA=(u16)(value);}while(0)
#define LCM_MEM_SET_RX_ADDR(value)      do{DMA_LCM_RXA=(u16)(value);}while(0)

#define PWMRST                      0x40
#define ENPWM                       0x01
#define PWMCBIF                     0x08
#define EPWMCBI                     0x04
#define EPWMTA                      0x02
#define PWMCEN                      0x01
#define INVCMP                      0x80
#define INVIO                       0x40
#define ENFD                        0x20
#define FLTFLIO                     0x10
#define EFDI                        0x08
#define FDCMP                       0x04
#define FDIO                        0x02
#define FDIF                        0x01
#define SELT2                       0x10
#define ENO                         0x80
#define INI                         0x40
#define ENI                         0x04
#define ENT2I                       0x02
#define ENT1I                       0x01
#define PWM_EN                      0x80

#if     ((ECBM_MCU&0xF00000)==0x200000)
#define PWM15_SET_CLK_TIMER2        do{PWMCKS=SELT2;}while(0)
#define PWM15_SET_CLK_SYS(value)    do{PWMCKS=((u8)(value)&0x0F);}while(0)

#define PWM15_SET_CH0_IO_P20        do{PWM_CH0_CR=((PWM_CH0_CR&(~0x18))|0x00);}while(0)
#define PWM15_SET_CH0_IO_P10        do{PWM_CH0_CR=((PWM_CH0_CR&(~0x18))|0x08);}while(0)
#define PWM15_SET_CH0_IO_P60        do{PWM_CH0_CR=((PWM_CH0_CR&(~0x18))|0x10);}while(0)
#define PWM15_SET_CH1_IO_P21        do{PWM_CH1_CR=((PWM_CH1_CR&(~0x18))|0x00);}while(0)
#define PWM15_SET_CH1_IO_P11        do{PWM_CH1_CR=((PWM_CH1_CR&(~0x18))|0x08);}while(0)
#define PWM15_SET_CH1_IO_P61        do{PWM_CH1_CR=((PWM_CH1_CR&(~0x18))|0x10);}while(0)
#define PWM15_SET_CH2_IO_P22        do{PWM_CH2_CR=((PWM_CH2_CR&(~0x18))|0x00);}while(0)
#define PWM15_SET_CH2_IO_P12        do{PWM_CH2_CR=((PWM_CH2_CR&(~0x18))|0x08);}while(0)
#define PWM15_SET_CH2_IO_P62        do{PWM_CH2_CR=((PWM_CH2_CR&(~0x18))|0x10);}while(0)
#define PWM15_SET_CH3_IO_P23        do{PWM_CH3_CR=((PWM_CH3_CR&(~0x18))|0x00);}while(0)
#define PWM15_SET_CH3_IO_P13        do{PWM_CH3_CR=((PWM_CH3_CR&(~0x18))|0x08);}while(0)
#define PWM15_SET_CH3_IO_P63        do{PWM_CH3_CR=((PWM_CH3_CR&(~0x18))|0x10);}while(0)
#define PWM15_SET_CH4_IO_P24        do{PWM_CH4_CR=((PWM_CH4_CR&(~0x18))|0x00);}while(0)
#define PWM15_SET_CH4_IO_P14        do{PWM_CH4_CR=((PWM_CH4_CR&(~0x18))|0x08);}while(0)
#define PWM15_SET_CH4_IO_P64        do{PWM_CH4_CR=((PWM_CH4_CR&(~0x18))|0x10);}while(0)
#define PWM15_SET_CH5_IO_P25        do{PWM_CH5_CR=((PWM_CH5_CR&(~0x18))|0x00);}while(0)
#define PWM15_SET_CH5_IO_P15        do{PWM_CH5_CR=((PWM_CH5_CR&(~0x18))|0x08);}while(0)
#define PWM15_SET_CH5_IO_P65        do{PWM_CH5_CR=((PWM_CH5_CR&(~0x18))|0x10);}while(0)
#define PWM15_SET_CH6_IO_P26        do{PWM_CH6_CR=((PWM_CH6_CR&(~0x18))|0x00);}while(0)
#define PWM15_SET_CH6_IO_P16        do{PWM_CH6_CR=((PWM_CH6_CR&(~0x18))|0x08);}while(0)
#define PWM15_SET_CH6_IO_P66        do{PWM_CH6_CR=((PWM_CH6_CR&(~0x18))|0x10);}while(0)
#define PWM15_SET_CH7_IO_P27        do{PWM_CH7_CR=((PWM_CH7_CR&(~0x18))|0x00);}while(0)
#define PWM15_SET_CH7_IO_P17        do{PWM_CH7_CR=((PWM_CH7_CR&(~0x18))|0x08);}while(0)
#define PWM15_SET_CH7_IO_P67        do{PWM_CH7_CR=((PWM_CH7_CR&(~0x18))|0x10);}while(0)

#define PWM15_GET_CH0_IT_FLAG       (PWMIF & 0x01)
#define PWM15_GET_CH1_IT_FLAG       (PWMIF & 0x02)
#define PWM15_GET_CH2_IT_FLAG       (PWMIF & 0x04)
#define PWM15_GET_CH3_IT_FLAG       (PWMIF & 0x08)
#define PWM15_GET_CH4_IT_FLAG       (PWMIF & 0x10)
#define PWM15_GET_CH5_IT_FLAG       (PWMIF & 0x20)
#define PWM15_GET_CH6_IT_FLAG       (PWMIF & 0x40)
#define PWM15_GET_CH7_IT_FLAG       (PWMIF & 0x80)

#define PWM15_CLS_CH0_IT_FLAG       do{PWMIF&=~0x01}while(0)
#define PWM15_CLS_CH1_IT_FLAG       do{PWMIF&=~0x02}while(0)
#define PWM15_CLS_CH2_IT_FLAG       do{PWMIF&=~0x04}while(0)
#define PWM15_CLS_CH3_IT_FLAG       do{PWMIF&=~0x08}while(0)
#define PWM15_CLS_CH4_IT_FLAG       do{PWMIF&=~0x10}while(0)
#define PWM15_CLS_CH5_IT_FLAG       do{PWMIF&=~0x20}while(0)
#define PWM15_CLS_CH6_IT_FLAG       do{PWMIF&=~0x40}while(0)
#define PWM15_CLS_CH7_IT_FLAG       do{PWMIF&=~0x80}while(0)

#define PWM15_SET_CH0_OUT_ENABLE    do{PWM_CH0_CR|= ENO;}while(0)
#define PWM15_SET_CH0_OUT_DISABLE   do{PWM_CH0_CR&=~ENO;}while(0)
#define PWM15_SET_CH0_INIT_H        do{PWM_CH0_CR|= INI;}while(0)
#define PWM15_SET_CH0_INIT_L        do{PWM_CH0_CR&=~INI;}while(0)
#define PWM15_SET_CH0_IT_ENABLE     do{PWM_CH0_CR|= ENI;}while(0)
#define PWM15_SET_CH0_IT_DISABLE    do{PWM_CH0_CR&=~ENI;}while(0)
#define PWM15_SET_CH0_T1_IT_ENABLE  do{PWM_CH0_CR|= ENT1I;}while(0)
#define PWM15_SET_CH0_T1_IT_DISABLE do{PWM_CH0_CR&=~ENT1I;}while(0)
#define PWM15_SET_CH0_T2_IT_ENABLE  do{PWM_CH0_CR|= ENT2I;}while(0)
#define PWM15_SET_CH0_T2_IT_DISABLE do{PWM_CH0_CR&=~ENT2I;}while(0)
#define PWM15_SET_CH0_HOLD_H        do{PWM_CH0_HLD=0x02;}while(0)
#define PWM15_SET_CH0_HOLD_L        do{PWM_CH0_HLD=0x01;}while(0)
#define PWM15_SET_CH0_HOLD_OFF      do{PWM_CH0_HLD=0x00;}while(0)
#define PWM15_SET_CH1_OUT_ENABLE    do{PWM_CH1_CR|= ENO;}while(0)
#define PWM15_SET_CH1_OUT_DISABLE   do{PWM_CH1_CR&=~ENO;}while(0)
#define PWM15_SET_CH1_INIT_H        do{PWM_CH1_CR|= INI;}while(0)
#define PWM15_SET_CH1_INIT_L        do{PWM_CH1_CR&=~INI;}while(0)
#define PWM15_SET_CH1_IT_ENABLE     do{PWM_CH1_CR|= ENI;}while(0)
#define PWM15_SET_CH1_IT_DISABLE    do{PWM_CH1_CR&=~ENI;}while(0)
#define PWM15_SET_CH1_T1_IT_ENABLE  do{PWM_CH1_CR|= ENT1I;}while(0)
#define PWM15_SET_CH1_T1_IT_DISABLE do{PWM_CH1_CR&=~ENT1I;}while(0)
#define PWM15_SET_CH1_T2_IT_ENABLE  do{PWM_CH1_CR|= ENT2I;}while(0)
#define PWM15_SET_CH1_T2_IT_DISABLE do{PWM_CH1_CR&=~ENT2I;}while(0)
#define PWM15_SET_CH1_HOLD_H        do{PWM_CH1_HLD=0x02;}while(0)
#define PWM15_SET_CH1_HOLD_L        do{PWM_CH1_HLD=0x01;}while(0)
#define PWM15_SET_CH1_HOLD_OFF      do{PWM_CH1_HLD=0x00;}while(0)
#define PWM15_SET_CH2_OUT_ENABLE    do{PWM_CH2_CR|= ENO;}while(0)
#define PWM15_SET_CH2_OUT_DISABLE   do{PWM_CH2_CR&=~ENO;}while(0)
#define PWM15_SET_CH2_INIT_H        do{PWM_CH2_CR|= INI;}while(0)
#define PWM15_SET_CH2_INIT_L        do{PWM_CH2_CR&=~INI;}while(0)
#define PWM15_SET_CH2_IT_ENABLE     do{PWM_CH2_CR|= ENI;}while(0)
#define PWM15_SET_CH2_IT_DISABLE    do{PWM_CH2_CR&=~ENI;}while(0)
#define PWM15_SET_CH2_T1_IT_ENABLE  do{PWM_CH2_CR|= ENT1I;}while(0)
#define PWM15_SET_CH2_T1_IT_DISABLE do{PWM_CH2_CR&=~ENT1I;}while(0)
#define PWM15_SET_CH2_T2_IT_ENABLE  do{PWM_CH2_CR|= ENT2I;}while(0)
#define PWM15_SET_CH2_T2_IT_DISABLE do{PWM_CH2_CR&=~ENT2I;}while(0)
#define PWM15_SET_CH2_HOLD_H        do{PWM_CH2_HLD=0x02;}while(0)
#define PWM15_SET_CH2_HOLD_L        do{PWM_CH2_HLD=0x01;}while(0)
#define PWM15_SET_CH2_HOLD_OFF      do{PWM_CH2_HLD=0x00;}while(0)
#define PWM15_SET_CH3_OUT_ENABLE    do{PWM_CH3_CR|= ENO;}while(0)
#define PWM15_SET_CH3_OUT_DISABLE   do{PWM_CH3_CR&=~ENO;}while(0)
#define PWM15_SET_CH3_INIT_H        do{PWM_CH3_CR|= INI;}while(0)
#define PWM15_SET_CH3_INIT_L        do{PWM_CH3_CR&=~INI;}while(0)
#define PWM15_SET_CH3_IT_ENABLE     do{PWM_CH3_CR|= ENI;}while(0)
#define PWM15_SET_CH3_IT_DISABLE    do{PWM_CH3_CR&=~ENI;}while(0)
#define PWM15_SET_CH3_T1_IT_ENABLE  do{PWM_CH3_CR|= ENT1I;}while(0)
#define PWM15_SET_CH3_T1_IT_DISABLE do{PWM_CH3_CR&=~ENT1I;}while(0)
#define PWM15_SET_CH3_T2_IT_ENABLE  do{PWM_CH3_CR|= ENT2I;}while(0)
#define PWM15_SET_CH3_T2_IT_DISABLE do{PWM_CH3_CR&=~ENT2I;}while(0)
#define PWM15_SET_CH3_HOLD_H        do{PWM_CH3_HLD=0x02;}while(0)
#define PWM15_SET_CH3_HOLD_L        do{PWM_CH3_HLD=0x01;}while(0)
#define PWM15_SET_CH3_HOLD_OFF      do{PWM_CH3_HLD=0x00;}while(0)
#define PWM15_SET_CH4_OUT_ENABLE    do{PWM_CH4_CR|= ENO;}while(0)
#define PWM15_SET_CH4_OUT_DISABLE   do{PWM_CH4_CR&=~ENO;}while(0)
#define PWM15_SET_CH4_INIT_H        do{PWM_CH4_CR|= INI;}while(0)
#define PWM15_SET_CH4_INIT_L        do{PWM_CH4_CR&=~INI;}while(0)
#define PWM15_SET_CH4_IT_ENABLE     do{PWM_CH4_CR|= ENI;}while(0)
#define PWM15_SET_CH4_IT_DISABLE    do{PWM_CH4_CR&=~ENI;}while(0)
#define PWM15_SET_CH4_T1_IT_ENABLE  do{PWM_CH4_CR|= ENT1I;}while(0)
#define PWM15_SET_CH4_T1_IT_DISABLE do{PWM_CH4_CR&=~ENT1I;}while(0)
#define PWM15_SET_CH4_T2_IT_ENABLE  do{PWM_CH4_CR|= ENT2I;}while(0)
#define PWM15_SET_CH4_T2_IT_DISABLE do{PWM_CH4_CR&=~ENT2I;}while(0)
#define PWM15_SET_CH4_HOLD_H        do{PWM_CH4_HLD=0x02;}while(0)
#define PWM15_SET_CH4_HOLD_L        do{PWM_CH4_HLD=0x01;}while(0)
#define PWM15_SET_CH4_HOLD_OFF      do{PWM_CH4_HLD=0x00;}while(0)
#define PWM15_SET_CH5_OUT_ENABLE    do{PWM_CH5_CR|= ENO;}while(0)
#define PWM15_SET_CH5_OUT_DISABLE   do{PWM_CH5_CR&=~ENO;}while(0)
#define PWM15_SET_CH5_INIT_H        do{PWM_CH5_CR|= INI;}while(0)
#define PWM15_SET_CH5_INIT_L        do{PWM_CH5_CR&=~INI;}while(0)
#define PWM15_SET_CH5_IT_ENABLE     do{PWM_CH5_CR|= ENI;}while(0)
#define PWM15_SET_CH5_IT_DISABLE    do{PWM_CH5_CR&=~ENI;}while(0)
#define PWM15_SET_CH5_T1_IT_ENABLE  do{PWM_CH5_CR|= ENT1I;}while(0)
#define PWM15_SET_CH5_T1_IT_DISABLE do{PWM_CH5_CR&=~ENT1I;}while(0)
#define PWM15_SET_CH5_T2_IT_ENABLE  do{PWM_CH5_CR|= ENT2I;}while(0)
#define PWM15_SET_CH5_T2_IT_DISABLE do{PWM_CH5_CR&=~ENT2I;}while(0)
#define PWM15_SET_CH5_HOLD_H        do{PWM_CH5_HLD=0x02;}while(0)
#define PWM15_SET_CH5_HOLD_L        do{PWM_CH5_HLD=0x01;}while(0)
#define PWM15_SET_CH5_HOLD_OFF      do{PWM_CH5_HLD=0x00;}while(0)
#define PWM15_SET_CH6_OUT_ENABLE    do{PWM_CH6_CR|= ENO;}while(0)
#define PWM15_SET_CH6_OUT_DISABLE   do{PWM_CH6_CR&=~ENO;}while(0)
#define PWM15_SET_CH6_INIT_H        do{PWM_CH6_CR|= INI;}while(0)
#define PWM15_SET_CH6_INIT_L        do{PWM_CH6_CR&=~INI;}while(0)
#define PWM15_SET_CH6_IT_ENABLE     do{PWM_CH6_CR|= ENI;}while(0)
#define PWM15_SET_CH6_IT_DISABLE    do{PWM_CH6_CR&=~ENI;}while(0)
#define PWM15_SET_CH6_T1_IT_ENABLE  do{PWM_CH6_CR|= ENT1I;}while(0)
#define PWM15_SET_CH6_T1_IT_DISABLE do{PWM_CH6_CR&=~ENT1I;}while(0)
#define PWM15_SET_CH6_T2_IT_ENABLE  do{PWM_CH6_CR|= ENT2I;}while(0)
#define PWM15_SET_CH6_T2_IT_DISABLE do{PWM_CH6_CR&=~ENT2I;}while(0)
#define PWM15_SET_CH6_HOLD_H        do{PWM_CH6_HLD=0x02;}while(0)
#define PWM15_SET_CH6_HOLD_L        do{PWM_CH6_HLD=0x01;}while(0)
#define PWM15_SET_CH6_HOLD_OFF      do{PWM_CH6_HLD=0x00;}while(0)
#define PWM15_SET_CH7_OUT_ENABLE    do{PWM_CH7_CR|= ENO;}while(0)
#define PWM15_SET_CH7_OUT_DISABLE   do{PWM_CH7_CR&=~ENO;}while(0)
#define PWM15_SET_CH7_INIT_H        do{PWM_CH7_CR|= INI;}while(0)
#define PWM15_SET_CH7_INIT_L        do{PWM_CH7_CR&=~INI;}while(0)
#define PWM15_SET_CH7_IT_ENABLE     do{PWM_CH7_CR|= ENI;}while(0)
#define PWM15_SET_CH7_IT_DISABLE    do{PWM_CH7_CR&=~ENI;}while(0)
#define PWM15_SET_CH7_T1_IT_ENABLE  do{PWM_CH7_CR|= ENT1I;}while(0)
#define PWM15_SET_CH7_T1_IT_DISABLE do{PWM_CH7_CR&=~ENT1I;}while(0)
#define PWM15_SET_CH7_T2_IT_ENABLE  do{PWM_CH7_CR|= ENT2I;}while(0)
#define PWM15_SET_CH7_T2_IT_DISABLE do{PWM_CH7_CR&=~ENT2I;}while(0)
#define PWM15_SET_CH7_HOLD_H        do{PWM_CH7_HLD=0x02;}while(0)
#define PWM15_SET_CH7_HOLD_L        do{PWM_CH7_HLD=0x01;}while(0)
#define PWM15_SET_CH7_HOLD_OFF      do{PWM_CH7_HLD=0x00;}while(0)
#elif   ((ECBM_MCU&0xFF0000)==0x320000)
#define PWM15_SET_G0_CLK_TIMER2     do{PWM_P0_CKS=SELT2;}while(0)
#define PWM15_SET_G1_CLK_TIMER2     do{PWM_P1_CKS=SELT2;}while(0)
#define PWM15_SET_G2_CLK_TIMER2     do{PWM_P2_CKS=SELT2;}while(0)
#define PWM15_SET_G3_CLK_TIMER2     do{PWM_P3_CKS=SELT2;}while(0)
#define PWM15_SET_G4_CLK_TIMER2     do{PWM_P4_CKS=SELT2;}while(0)
#define PWM15_SET_G5_CLK_TIMER2     do{PWM_P5_CKS=SELT2;}while(0)

#define PWM15_SET_G0_CLK_SYS(value) do{PWM_P0_CKS=((u8)(value)&0x0F);}while(0)
#define PWM15_SET_G1_CLK_SYS(value) do{PWM_P1_CKS=((u8)(value)&0x0F);}while(0)
#define PWM15_SET_G2_CLK_SYS(value) do{PWM_P2_CKS=((u8)(value)&0x0F);}while(0)
#define PWM15_SET_G3_CLK_SYS(value) do{PWM_P3_CKS=((u8)(value)&0x0F);}while(0)
#define PWM15_SET_G4_CLK_SYS(value) do{PWM_P4_CKS=((u8)(value)&0x0F);}while(0)
#define PWM15_SET_G5_CLK_SYS(value) do{PWM_P5_CKS=((u8)(value)&0x0F);}while(0)

#define PWM15_GET_G0_CH0_IT_FLAG    (PWM_P0_IF & 0x01)
#define PWM15_GET_G0_CH1_IT_FLAG    (PWM_P0_IF & 0x02)
#define PWM15_GET_G0_CH2_IT_FLAG    (PWM_P0_IF & 0x04)
#define PWM15_GET_G0_CH3_IT_FLAG    (PWM_P0_IF & 0x08)
#define PWM15_GET_G0_CH4_IT_FLAG    (PWM_P0_IF & 0x10)
#define PWM15_GET_G0_CH5_IT_FLAG    (PWM_P0_IF & 0x20)
#define PWM15_GET_G0_CH6_IT_FLAG    (PWM_P0_IF & 0x40)
#define PWM15_GET_G0_CH7_IT_FLAG    (PWM_P0_IF & 0x80)
#define PWM15_GET_G1_CH0_IT_FLAG    (PWM_P1_IF & 0x01)
#define PWM15_GET_G1_CH1_IT_FLAG    (PWM_P1_IF & 0x02)
#define PWM15_GET_G1_CH2_IT_FLAG    (PWM_P1_IF & 0x04)
#define PWM15_GET_G1_CH3_IT_FLAG    (PWM_P1_IF & 0x08)
#define PWM15_GET_G1_CH4_IT_FLAG    (PWM_P1_IF & 0x10)
#define PWM15_GET_G1_CH5_IT_FLAG    (PWM_P1_IF & 0x20)
#define PWM15_GET_G1_CH6_IT_FLAG    (PWM_P1_IF & 0x40)
#define PWM15_GET_G1_CH7_IT_FLAG    (PWM_P1_IF & 0x80)
#define PWM15_GET_G2_CH0_IT_FLAG    (PWM_P2_IF & 0x01)
#define PWM15_GET_G2_CH1_IT_FLAG    (PWM_P2_IF & 0x02)
#define PWM15_GET_G2_CH2_IT_FLAG    (PWM_P2_IF & 0x04)
#define PWM15_GET_G2_CH3_IT_FLAG    (PWM_P2_IF & 0x08)
#define PWM15_GET_G2_CH4_IT_FLAG    (PWM_P2_IF & 0x10)
#define PWM15_GET_G2_CH5_IT_FLAG    (PWM_P2_IF & 0x20)
#define PWM15_GET_G2_CH6_IT_FLAG    (PWM_P2_IF & 0x40)
#define PWM15_GET_G2_CH7_IT_FLAG    (PWM_P2_IF & 0x80)
#define PWM15_GET_G3_CH0_IT_FLAG    (PWM_P3_IF & 0x01)
#define PWM15_GET_G3_CH1_IT_FLAG    (PWM_P3_IF & 0x02)
#define PWM15_GET_G3_CH2_IT_FLAG    (PWM_P3_IF & 0x04)
#define PWM15_GET_G3_CH3_IT_FLAG    (PWM_P3_IF & 0x08)
#define PWM15_GET_G3_CH4_IT_FLAG    (PWM_P3_IF & 0x10)
#define PWM15_GET_G3_CH5_IT_FLAG    (PWM_P3_IF & 0x20)
#define PWM15_GET_G3_CH6_IT_FLAG    (PWM_P3_IF & 0x40)
#define PWM15_GET_G3_CH7_IT_FLAG    (PWM_P3_IF & 0x80)
#define PWM15_GET_G4_CH0_IT_FLAG    (PWM_P4_IF & 0x01)
#define PWM15_GET_G4_CH1_IT_FLAG    (PWM_P4_IF & 0x02)
#define PWM15_GET_G4_CH2_IT_FLAG    (PWM_P4_IF & 0x04)
#define PWM15_GET_G4_CH3_IT_FLAG    (PWM_P4_IF & 0x08)
#define PWM15_GET_G4_CH4_IT_FLAG    (PWM_P4_IF & 0x10)
#define PWM15_GET_G4_CH5_IT_FLAG    (PWM_P4_IF & 0x20)
#define PWM15_GET_G4_CH6_IT_FLAG    (PWM_P4_IF & 0x40)
#define PWM15_GET_G4_CH7_IT_FLAG    (PWM_P4_IF & 0x80)
#define PWM15_GET_G5_CH0_IT_FLAG    (PWM_P5_IF & 0x01)
#define PWM15_GET_G5_CH1_IT_FLAG    (PWM_P5_IF & 0x02)
#define PWM15_GET_G5_CH2_IT_FLAG    (PWM_P5_IF & 0x04)
#define PWM15_GET_G5_CH3_IT_FLAG    (PWM_P5_IF & 0x08)
#define PWM15_GET_G5_CH4_IT_FLAG    (PWM_P5_IF & 0x10)
#define PWM15_GET_G5_CH5_IT_FLAG    (PWM_P5_IF & 0x20)
#define PWM15_GET_G5_CH6_IT_FLAG    (PWM_P5_IF & 0x40)
#define PWM15_GET_G5_CH7_IT_FLAG    (PWM_P5_IF & 0x80)

#define PWM15_CLS_G0_CH0_IT_FLAG    do{PWM_P0_IF&=~0x01}while(0)
#define PWM15_CLS_G0_CH1_IT_FLAG    do{PWM_P0_IF&=~0x02}while(0)
#define PWM15_CLS_G0_CH2_IT_FLAG    do{PWM_P0_IF&=~0x04}while(0)
#define PWM15_CLS_G0_CH3_IT_FLAG    do{PWM_P0_IF&=~0x08}while(0)
#define PWM15_CLS_G0_CH4_IT_FLAG    do{PWM_P0_IF&=~0x10}while(0)
#define PWM15_CLS_G0_CH5_IT_FLAG    do{PWM_P0_IF&=~0x20}while(0)
#define PWM15_CLS_G0_CH6_IT_FLAG    do{PWM_P0_IF&=~0x40}while(0)
#define PWM15_CLS_G0_CH7_IT_FLAG    do{PWM_P0_IF&=~0x80}while(0)
#define PWM15_CLS_G1_CH0_IT_FLAG    do{PWM_P1_IF&=~0x01}while(0)
#define PWM15_CLS_G1_CH1_IT_FLAG    do{PWM_P1_IF&=~0x02}while(0)
#define PWM15_CLS_G1_CH2_IT_FLAG    do{PWM_P1_IF&=~0x04}while(0)
#define PWM15_CLS_G1_CH3_IT_FLAG    do{PWM_P1_IF&=~0x08}while(0)
#define PWM15_CLS_G1_CH4_IT_FLAG    do{PWM_P1_IF&=~0x10}while(0)
#define PWM15_CLS_G1_CH5_IT_FLAG    do{PWM_P1_IF&=~0x20}while(0)
#define PWM15_CLS_G1_CH6_IT_FLAG    do{PWM_P1_IF&=~0x40}while(0)
#define PWM15_CLS_G1_CH7_IT_FLAG    do{PWM_P1_IF&=~0x80}while(0)
#define PWM15_CLS_G2_CH0_IT_FLAG    do{PWM_P2_IF&=~0x01}while(0)
#define PWM15_CLS_G2_CH1_IT_FLAG    do{PWM_P2_IF&=~0x02}while(0)
#define PWM15_CLS_G2_CH2_IT_FLAG    do{PWM_P2_IF&=~0x04}while(0)
#define PWM15_CLS_G2_CH3_IT_FLAG    do{PWM_P2_IF&=~0x08}while(0)
#define PWM15_CLS_G2_CH4_IT_FLAG    do{PWM_P2_IF&=~0x10}while(0)
#define PWM15_CLS_G2_CH5_IT_FLAG    do{PWM_P2_IF&=~0x20}while(0)
#define PWM15_CLS_G2_CH6_IT_FLAG    do{PWM_P2_IF&=~0x40}while(0)
#define PWM15_CLS_G2_CH7_IT_FLAG    do{PWM_P2_IF&=~0x80}while(0)
#define PWM15_CLS_G3_CH0_IT_FLAG    do{PWM_P3_IF&=~0x01}while(0)
#define PWM15_CLS_G3_CH1_IT_FLAG    do{PWM_P3_IF&=~0x02}while(0)
#define PWM15_CLS_G3_CH2_IT_FLAG    do{PWM_P3_IF&=~0x04}while(0)
#define PWM15_CLS_G3_CH3_IT_FLAG    do{PWM_P3_IF&=~0x08}while(0)
#define PWM15_CLS_G3_CH4_IT_FLAG    do{PWM_P3_IF&=~0x10}while(0)
#define PWM15_CLS_G3_CH5_IT_FLAG    do{PWM_P3_IF&=~0x20}while(0)
#define PWM15_CLS_G3_CH6_IT_FLAG    do{PWM_P3_IF&=~0x40}while(0)
#define PWM15_CLS_G3_CH7_IT_FLAG    do{PWM_P3_IF&=~0x80}while(0)
#define PWM15_CLS_G4_CH0_IT_FLAG    do{PWM_P4_IF&=~0x01}while(0)
#define PWM15_CLS_G4_CH1_IT_FLAG    do{PWM_P4_IF&=~0x02}while(0)
#define PWM15_CLS_G4_CH2_IT_FLAG    do{PWM_P4_IF&=~0x04}while(0)
#define PWM15_CLS_G4_CH3_IT_FLAG    do{PWM_P4_IF&=~0x08}while(0)
#define PWM15_CLS_G4_CH4_IT_FLAG    do{PWM_P4_IF&=~0x10}while(0)
#define PWM15_CLS_G4_CH5_IT_FLAG    do{PWM_P4_IF&=~0x20}while(0)
#define PWM15_CLS_G4_CH6_IT_FLAG    do{PWM_P4_IF&=~0x40}while(0)
#define PWM15_CLS_G4_CH7_IT_FLAG    do{PWM_P4_IF&=~0x80}while(0)
#define PWM15_CLS_G5_CH0_IT_FLAG    do{PWM_P5_IF&=~0x01}while(0)
#define PWM15_CLS_G5_CH1_IT_FLAG    do{PWM_P5_IF&=~0x02}while(0)
#define PWM15_CLS_G5_CH2_IT_FLAG    do{PWM_P5_IF&=~0x04}while(0)
#define PWM15_CLS_G5_CH3_IT_FLAG    do{PWM_P5_IF&=~0x08}while(0)
#define PWM15_CLS_G5_CH4_IT_FLAG    do{PWM_P5_IF&=~0x10}while(0)
#define PWM15_CLS_G5_CH5_IT_FLAG    do{PWM_P5_IF&=~0x20}while(0)
#define PWM15_CLS_G5_CH6_IT_FLAG    do{PWM_P5_IF&=~0x40}while(0)
#define PWM15_CLS_G5_CH7_IT_FLAG    do{PWM_P5_IF&=~0x80}while(0)

#define PWM15_SET_G0_CH0_OUT_ENABLE    do{PWM_P00_CR|= ENO;}while(0)
#define PWM15_SET_G0_CH0_OUT_DISABLE   do{PWM_P00_CR&=~ENO;}while(0)
#define PWM15_SET_G0_CH0_INIT_H        do{PWM_P00_CR|= INI;}while(0)
#define PWM15_SET_G0_CH0_INIT_L        do{PWM_P00_CR&=~INI;}while(0)
#define PWM15_SET_G0_CH0_IT_ENABLE     do{PWM_P00_CR|= ENI;}while(0)
#define PWM15_SET_G0_CH0_IT_DISABLE    do{PWM_P00_CR&=~ENI;}while(0)
#define PWM15_SET_G0_CH0_T1_IT_ENABLE  do{PWM_P00_CR|= ENT1I;}while(0)
#define PWM15_SET_G0_CH0_T1_IT_DISABLE do{PWM_P00_CR&=~ENT1I;}while(0)
#define PWM15_SET_G0_CH0_T2_IT_ENABLE  do{PWM_P00_CR|= ENT2I;}while(0)
#define PWM15_SET_G0_CH0_T2_IT_DISABLE do{PWM_P00_CR&=~ENT2I;}while(0)
#define PWM15_SET_G0_CH0_HOLD_H        do{PWM_P00_HLD=0x02;}while(0)
#define PWM15_SET_G0_CH0_HOLD_L        do{PWM_P00_HLD=0x01;}while(0)
#define PWM15_SET_G0_CH0_HOLD_OFF      do{PWM_P00_HLD=0x00;}while(0)
#define PWM15_SET_G0_CH1_OUT_ENABLE    do{PWM_P01_CR|= ENO;}while(0)
#define PWM15_SET_G0_CH1_OUT_DISABLE   do{PWM_P01_CR&=~ENO;}while(0)
#define PWM15_SET_G0_CH1_INIT_H        do{PWM_P01_CR|= INI;}while(0)
#define PWM15_SET_G0_CH1_INIT_L        do{PWM_P01_CR&=~INI;}while(0)
#define PWM15_SET_G0_CH1_IT_ENABLE     do{PWM_P01_CR|= ENI;}while(0)
#define PWM15_SET_G0_CH1_IT_DISABLE    do{PWM_P01_CR&=~ENI;}while(0)
#define PWM15_SET_G0_CH1_T1_IT_ENABLE  do{PWM_P01_CR|= ENT1I;}while(0)
#define PWM15_SET_G0_CH1_T1_IT_DISABLE do{PWM_P01_CR&=~ENT1I;}while(0)
#define PWM15_SET_G0_CH1_T2_IT_ENABLE  do{PWM_P01_CR|= ENT2I;}while(0)
#define PWM15_SET_G0_CH1_T2_IT_DISABLE do{PWM_P01_CR&=~ENT2I;}while(0)
#define PWM15_SET_G0_CH1_HOLD_H        do{PWM_P01_HLD=0x02;}while(0)
#define PWM15_SET_G0_CH1_HOLD_L        do{PWM_P01_HLD=0x01;}while(0)
#define PWM15_SET_G0_CH1_HOLD_OFF      do{PWM_P01_HLD=0x00;}while(0)
#define PWM15_SET_G0_CH2_OUT_ENABLE    do{PWM_P02_CR|= ENO;}while(0)
#define PWM15_SET_G0_CH2_OUT_DISABLE   do{PWM_P02_CR&=~ENO;}while(0)
#define PWM15_SET_G0_CH2_INIT_H        do{PWM_P02_CR|= INI;}while(0)
#define PWM15_SET_G0_CH2_INIT_L        do{PWM_P02_CR&=~INI;}while(0)
#define PWM15_SET_G0_CH2_IT_ENABLE     do{PWM_P02_CR|= ENI;}while(0)
#define PWM15_SET_G0_CH2_IT_DISABLE    do{PWM_P02_CR&=~ENI;}while(0)
#define PWM15_SET_G0_CH2_T1_IT_ENABLE  do{PWM_P02_CR|= ENT1I;}while(0)
#define PWM15_SET_G0_CH2_T1_IT_DISABLE do{PWM_P02_CR&=~ENT1I;}while(0)
#define PWM15_SET_G0_CH2_T2_IT_ENABLE  do{PWM_P02_CR|= ENT2I;}while(0)
#define PWM15_SET_G0_CH2_T2_IT_DISABLE do{PWM_P02_CR&=~ENT2I;}while(0)
#define PWM15_SET_G0_CH2_HOLD_H        do{PWM_P02_HLD=0x02;}while(0)
#define PWM15_SET_G0_CH2_HOLD_L        do{PWM_P02_HLD=0x01;}while(0)
#define PWM15_SET_G0_CH2_HOLD_OFF      do{PWM_P02_HLD=0x00;}while(0)
#define PWM15_SET_G0_CH3_OUT_ENABLE    do{PWM_P03_CR|= ENO;}while(0)
#define PWM15_SET_G0_CH3_OUT_DISABLE   do{PWM_P03_CR&=~ENO;}while(0)
#define PWM15_SET_G0_CH3_INIT_H        do{PWM_P03_CR|= INI;}while(0)
#define PWM15_SET_G0_CH3_INIT_L        do{PWM_P03_CR&=~INI;}while(0)
#define PWM15_SET_G0_CH3_IT_ENABLE     do{PWM_P03_CR|= ENI;}while(0)
#define PWM15_SET_G0_CH3_IT_DISABLE    do{PWM_P03_CR&=~ENI;}while(0)
#define PWM15_SET_G0_CH3_T1_IT_ENABLE  do{PWM_P03_CR|= ENT1I;}while(0)
#define PWM15_SET_G0_CH3_T1_IT_DISABLE do{PWM_P03_CR&=~ENT1I;}while(0)
#define PWM15_SET_G0_CH3_T2_IT_ENABLE  do{PWM_P03_CR|= ENT2I;}while(0)
#define PWM15_SET_G0_CH3_T2_IT_DISABLE do{PWM_P03_CR&=~ENT2I;}while(0)
#define PWM15_SET_G0_CH3_HOLD_H        do{PWM_P03_HLD=0x02;}while(0)
#define PWM15_SET_G0_CH3_HOLD_L        do{PWM_P03_HLD=0x01;}while(0)
#define PWM15_SET_G0_CH3_HOLD_OFF      do{PWM_P03_HLD=0x00;}while(0)
#define PWM15_SET_G0_CH4_OUT_ENABLE    do{PWM_P04_CR|= ENO;}while(0)
#define PWM15_SET_G0_CH4_OUT_DISABLE   do{PWM_P04_CR&=~ENO;}while(0)
#define PWM15_SET_G0_CH4_INIT_H        do{PWM_P04_CR|= INI;}while(0)
#define PWM15_SET_G0_CH4_INIT_L        do{PWM_P04_CR&=~INI;}while(0)
#define PWM15_SET_G0_CH4_IT_ENABLE     do{PWM_P04_CR|= ENI;}while(0)
#define PWM15_SET_G0_CH4_IT_DISABLE    do{PWM_P04_CR&=~ENI;}while(0)
#define PWM15_SET_G0_CH4_T1_IT_ENABLE  do{PWM_P04_CR|= ENT1I;}while(0)
#define PWM15_SET_G0_CH4_T1_IT_DISABLE do{PWM_P04_CR&=~ENT1I;}while(0)
#define PWM15_SET_G0_CH4_T2_IT_ENABLE  do{PWM_P04_CR|= ENT2I;}while(0)
#define PWM15_SET_G0_CH4_T2_IT_DISABLE do{PWM_P04_CR&=~ENT2I;}while(0)
#define PWM15_SET_G0_CH4_HOLD_H        do{PWM_P04_HLD=0x02;}while(0)
#define PWM15_SET_G0_CH4_HOLD_L        do{PWM_P04_HLD=0x01;}while(0)
#define PWM15_SET_G0_CH4_HOLD_OFF      do{PWM_P04_HLD=0x00;}while(0)
#define PWM15_SET_G0_CH5_OUT_ENABLE    do{PWM_P05_CR|= ENO;}while(0)
#define PWM15_SET_G0_CH5_OUT_DISABLE   do{PWM_P05_CR&=~ENO;}while(0)
#define PWM15_SET_G0_CH5_INIT_H        do{PWM_P05_CR|= INI;}while(0)
#define PWM15_SET_G0_CH5_INIT_L        do{PWM_P05_CR&=~INI;}while(0)
#define PWM15_SET_G0_CH5_IT_ENABLE     do{PWM_P05_CR|= ENI;}while(0)
#define PWM15_SET_G0_CH5_IT_DISABLE    do{PWM_P05_CR&=~ENI;}while(0)
#define PWM15_SET_G0_CH5_T1_IT_ENABLE  do{PWM_P05_CR|= ENT1I;}while(0)
#define PWM15_SET_G0_CH5_T1_IT_DISABLE do{PWM_P05_CR&=~ENT1I;}while(0)
#define PWM15_SET_G0_CH5_T2_IT_ENABLE  do{PWM_P05_CR|= ENT2I;}while(0)
#define PWM15_SET_G0_CH5_T2_IT_DISABLE do{PWM_P05_CR&=~ENT2I;}while(0)
#define PWM15_SET_G0_CH5_HOLD_H        do{PWM_P05_HLD=0x02;}while(0)
#define PWM15_SET_G0_CH5_HOLD_L        do{PWM_P05_HLD=0x01;}while(0)
#define PWM15_SET_G0_CH5_HOLD_OFF      do{PWM_P05_HLD=0x00;}while(0)
#define PWM15_SET_G0_CH6_OUT_ENABLE    do{PWM_P06_CR|= ENO;}while(0)
#define PWM15_SET_G0_CH6_OUT_DISABLE   do{PWM_P06_CR&=~ENO;}while(0)
#define PWM15_SET_G0_CH6_INIT_H        do{PWM_P06_CR|= INI;}while(0)
#define PWM15_SET_G0_CH6_INIT_L        do{PWM_P06_CR&=~INI;}while(0)
#define PWM15_SET_G0_CH6_IT_ENABLE     do{PWM_P06_CR|= ENI;}while(0)
#define PWM15_SET_G0_CH6_IT_DISABLE    do{PWM_P06_CR&=~ENI;}while(0)
#define PWM15_SET_G0_CH6_T1_IT_ENABLE  do{PWM_P06_CR|= ENT1I;}while(0)
#define PWM15_SET_G0_CH6_T1_IT_DISABLE do{PWM_P06_CR&=~ENT1I;}while(0)
#define PWM15_SET_G0_CH6_T2_IT_ENABLE  do{PWM_P06_CR|= ENT2I;}while(0)
#define PWM15_SET_G0_CH6_T2_IT_DISABLE do{PWM_P06_CR&=~ENT2I;}while(0)
#define PWM15_SET_G0_CH6_HOLD_H        do{PWM_P06_HLD=0x02;}while(0)
#define PWM15_SET_G0_CH6_HOLD_L        do{PWM_P06_HLD=0x01;}while(0)
#define PWM15_SET_G0_CH6_HOLD_OFF      do{PWM_P06_HLD=0x00;}while(0)
#define PWM15_SET_G0_CH7_OUT_ENABLE    do{PWM_P07_CR|= ENO;}while(0)
#define PWM15_SET_G0_CH7_OUT_DISABLE   do{PWM_P07_CR&=~ENO;}while(0)
#define PWM15_SET_G0_CH7_INIT_H        do{PWM_P07_CR|= INI;}while(0)
#define PWM15_SET_G0_CH7_INIT_L        do{PWM_P07_CR&=~INI;}while(0)
#define PWM15_SET_G0_CH7_IT_ENABLE     do{PWM_P07_CR|= ENI;}while(0)
#define PWM15_SET_G0_CH7_IT_DISABLE    do{PWM_P07_CR&=~ENI;}while(0)
#define PWM15_SET_G0_CH7_T1_IT_ENABLE  do{PWM_P07_CR|= ENT1I;}while(0)
#define PWM15_SET_G0_CH7_T1_IT_DISABLE do{PWM_P07_CR&=~ENT1I;}while(0)
#define PWM15_SET_G0_CH7_T2_IT_ENABLE  do{PWM_P07_CR|= ENT2I;}while(0)
#define PWM15_SET_G0_CH7_T2_IT_DISABLE do{PWM_P07_CR&=~ENT2I;}while(0)
#define PWM15_SET_G0_CH7_HOLD_H        do{PWM_P07_HLD=0x02;}while(0)
#define PWM15_SET_G0_CH7_HOLD_L        do{PWM_P07_HLD=0x01;}while(0)
#define PWM15_SET_G0_CH7_HOLD_OFF      do{PWM_P07_HLD=0x00;}while(0)

#define PWM15_SET_G1_CH0_OUT_ENABLE    do{PWM_P10_CR|= ENO;}while(0)
#define PWM15_SET_G1_CH0_OUT_DISABLE   do{PWM_P10_CR&=~ENO;}while(0)
#define PWM15_SET_G1_CH0_INIT_H        do{PWM_P10_CR|= INI;}while(0)
#define PWM15_SET_G1_CH0_INIT_L        do{PWM_P10_CR&=~INI;}while(0)
#define PWM15_SET_G1_CH0_IT_ENABLE     do{PWM_P10_CR|= ENI;}while(0)
#define PWM15_SET_G1_CH0_IT_DISABLE    do{PWM_P10_CR&=~ENI;}while(0)
#define PWM15_SET_G1_CH0_T1_IT_ENABLE  do{PWM_P10_CR|= ENT1I;}while(0)
#define PWM15_SET_G1_CH0_T1_IT_DISABLE do{PWM_P10_CR&=~ENT1I;}while(0)
#define PWM15_SET_G1_CH0_T2_IT_ENABLE  do{PWM_P10_CR|= ENT2I;}while(0)
#define PWM15_SET_G1_CH0_T2_IT_DISABLE do{PWM_P10_CR&=~ENT2I;}while(0)
#define PWM15_SET_G1_CH0_HOLD_H        do{PWM_P10_HLD=0x02;}while(0)
#define PWM15_SET_G1_CH0_HOLD_L        do{PWM_P10_HLD=0x01;}while(0)
#define PWM15_SET_G1_CH0_HOLD_OFF      do{PWM_P10_HLD=0x00;}while(0)
#define PWM15_SET_G1_CH1_OUT_ENABLE    do{PWM_P11_CR|= ENO;}while(0)
#define PWM15_SET_G1_CH1_OUT_DISABLE   do{PWM_P11_CR&=~ENO;}while(0)
#define PWM15_SET_G1_CH1_INIT_H        do{PWM_P11_CR|= INI;}while(0)
#define PWM15_SET_G1_CH1_INIT_L        do{PWM_P11_CR&=~INI;}while(0)
#define PWM15_SET_G1_CH1_IT_ENABLE     do{PWM_P11_CR|= ENI;}while(0)
#define PWM15_SET_G1_CH1_IT_DISABLE    do{PWM_P11_CR&=~ENI;}while(0)
#define PWM15_SET_G1_CH1_T1_IT_ENABLE  do{PWM_P11_CR|= ENT1I;}while(0)
#define PWM15_SET_G1_CH1_T1_IT_DISABLE do{PWM_P11_CR&=~ENT1I;}while(0)
#define PWM15_SET_G1_CH1_T2_IT_ENABLE  do{PWM_P11_CR|= ENT2I;}while(0)
#define PWM15_SET_G1_CH1_T2_IT_DISABLE do{PWM_P11_CR&=~ENT2I;}while(0)
#define PWM15_SET_G1_CH1_HOLD_H        do{PWM_P11_HLD=0x02;}while(0)
#define PWM15_SET_G1_CH1_HOLD_L        do{PWM_P11_HLD=0x01;}while(0)
#define PWM15_SET_G1_CH1_HOLD_OFF      do{PWM_P11_HLD=0x00;}while(0)
#define PWM15_SET_G1_CH2_OUT_ENABLE    do{PWM_P12_CR|= ENO;}while(0)
#define PWM15_SET_G1_CH2_OUT_DISABLE   do{PWM_P12_CR&=~ENO;}while(0)
#define PWM15_SET_G1_CH2_INIT_H        do{PWM_P12_CR|= INI;}while(0)
#define PWM15_SET_G1_CH2_INIT_L        do{PWM_P12_CR&=~INI;}while(0)
#define PWM15_SET_G1_CH2_IT_ENABLE     do{PWM_P12_CR|= ENI;}while(0)
#define PWM15_SET_G1_CH2_IT_DISABLE    do{PWM_P12_CR&=~ENI;}while(0)
#define PWM15_SET_G1_CH2_T1_IT_ENABLE  do{PWM_P12_CR|= ENT1I;}while(0)
#define PWM15_SET_G1_CH2_T1_IT_DISABLE do{PWM_P12_CR&=~ENT1I;}while(0)
#define PWM15_SET_G1_CH2_T2_IT_ENABLE  do{PWM_P12_CR|= ENT2I;}while(0)
#define PWM15_SET_G1_CH2_T2_IT_DISABLE do{PWM_P12_CR&=~ENT2I;}while(0)
#define PWM15_SET_G1_CH2_HOLD_H        do{PWM_P12_HLD=0x02;}while(0)
#define PWM15_SET_G1_CH2_HOLD_L        do{PWM_P12_HLD=0x01;}while(0)
#define PWM15_SET_G1_CH2_HOLD_OFF      do{PWM_P12_HLD=0x00;}while(0)
#define PWM15_SET_G1_CH3_OUT_ENABLE    do{PWM_P13_CR|= ENO;}while(0)
#define PWM15_SET_G1_CH3_OUT_DISABLE   do{PWM_P13_CR&=~ENO;}while(0)
#define PWM15_SET_G1_CH3_INIT_H        do{PWM_P13_CR|= INI;}while(0)
#define PWM15_SET_G1_CH3_INIT_L        do{PWM_P13_CR&=~INI;}while(0)
#define PWM15_SET_G1_CH3_IT_ENABLE     do{PWM_P13_CR|= ENI;}while(0)
#define PWM15_SET_G1_CH3_IT_DISABLE    do{PWM_P13_CR&=~ENI;}while(0)
#define PWM15_SET_G1_CH3_T1_IT_ENABLE  do{PWM_P13_CR|= ENT1I;}while(0)
#define PWM15_SET_G1_CH3_T1_IT_DISABLE do{PWM_P13_CR&=~ENT1I;}while(0)
#define PWM15_SET_G1_CH3_T2_IT_ENABLE  do{PWM_P13_CR|= ENT2I;}while(0)
#define PWM15_SET_G1_CH3_T2_IT_DISABLE do{PWM_P13_CR&=~ENT2I;}while(0)
#define PWM15_SET_G1_CH3_HOLD_H        do{PWM_P13_HLD=0x02;}while(0)
#define PWM15_SET_G1_CH3_HOLD_L        do{PWM_P13_HLD=0x01;}while(0)
#define PWM15_SET_G1_CH3_HOLD_OFF      do{PWM_P13_HLD=0x00;}while(0)
#define PWM15_SET_G1_CH4_OUT_ENABLE    do{PWM_P14_CR|= ENO;}while(0)
#define PWM15_SET_G1_CH4_OUT_DISABLE   do{PWM_P14_CR&=~ENO;}while(0)
#define PWM15_SET_G1_CH4_INIT_H        do{PWM_P14_CR|= INI;}while(0)
#define PWM15_SET_G1_CH4_INIT_L        do{PWM_P14_CR&=~INI;}while(0)
#define PWM15_SET_G1_CH4_IT_ENABLE     do{PWM_P14_CR|= ENI;}while(0)
#define PWM15_SET_G1_CH4_IT_DISABLE    do{PWM_P14_CR&=~ENI;}while(0)
#define PWM15_SET_G1_CH4_T1_IT_ENABLE  do{PWM_P14_CR|= ENT1I;}while(0)
#define PWM15_SET_G1_CH4_T1_IT_DISABLE do{PWM_P14_CR&=~ENT1I;}while(0)
#define PWM15_SET_G1_CH4_T2_IT_ENABLE  do{PWM_P14_CR|= ENT2I;}while(0)
#define PWM15_SET_G1_CH4_T2_IT_DISABLE do{PWM_P14_CR&=~ENT2I;}while(0)
#define PWM15_SET_G1_CH4_HOLD_H        do{PWM_P14_HLD=0x02;}while(0)
#define PWM15_SET_G1_CH4_HOLD_L        do{PWM_P14_HLD=0x01;}while(0)
#define PWM15_SET_G1_CH4_HOLD_OFF      do{PWM_P14_HLD=0x00;}while(0)
#define PWM15_SET_G1_CH5_OUT_ENABLE    do{PWM_P15_CR|= ENO;}while(0)
#define PWM15_SET_G1_CH5_OUT_DISABLE   do{PWM_P15_CR&=~ENO;}while(0)
#define PWM15_SET_G1_CH5_INIT_H        do{PWM_P15_CR|= INI;}while(0)
#define PWM15_SET_G1_CH5_INIT_L        do{PWM_P15_CR&=~INI;}while(0)
#define PWM15_SET_G1_CH5_IT_ENABLE     do{PWM_P15_CR|= ENI;}while(0)
#define PWM15_SET_G1_CH5_IT_DISABLE    do{PWM_P15_CR&=~ENI;}while(0)
#define PWM15_SET_G1_CH5_T1_IT_ENABLE  do{PWM_P15_CR|= ENT1I;}while(0)
#define PWM15_SET_G1_CH5_T1_IT_DISABLE do{PWM_P15_CR&=~ENT1I;}while(0)
#define PWM15_SET_G1_CH5_T2_IT_ENABLE  do{PWM_P15_CR|= ENT2I;}while(0)
#define PWM15_SET_G1_CH5_T2_IT_DISABLE do{PWM_P15_CR&=~ENT2I;}while(0)
#define PWM15_SET_G1_CH5_HOLD_H        do{PWM_P15_HLD=0x02;}while(0)
#define PWM15_SET_G1_CH5_HOLD_L        do{PWM_P15_HLD=0x01;}while(0)
#define PWM15_SET_G1_CH5_HOLD_OFF      do{PWM_P15_HLD=0x00;}while(0)
#define PWM15_SET_G1_CH6_OUT_ENABLE    do{PWM_P16_CR|= ENO;}while(0)
#define PWM15_SET_G1_CH6_OUT_DISABLE   do{PWM_P16_CR&=~ENO;}while(0)
#define PWM15_SET_G1_CH6_INIT_H        do{PWM_P16_CR|= INI;}while(0)
#define PWM15_SET_G1_CH6_INIT_L        do{PWM_P16_CR&=~INI;}while(0)
#define PWM15_SET_G1_CH6_IT_ENABLE     do{PWM_P16_CR|= ENI;}while(0)
#define PWM15_SET_G1_CH6_IT_DISABLE    do{PWM_P16_CR&=~ENI;}while(0)
#define PWM15_SET_G1_CH6_T1_IT_ENABLE  do{PWM_P16_CR|= ENT1I;}while(0)
#define PWM15_SET_G1_CH6_T1_IT_DISABLE do{PWM_P16_CR&=~ENT1I;}while(0)
#define PWM15_SET_G1_CH6_T2_IT_ENABLE  do{PWM_P16_CR|= ENT2I;}while(0)
#define PWM15_SET_G1_CH6_T2_IT_DISABLE do{PWM_P16_CR&=~ENT2I;}while(0)
#define PWM15_SET_G1_CH6_HOLD_H        do{PWM_P16_HLD=0x02;}while(0)
#define PWM15_SET_G1_CH6_HOLD_L        do{PWM_P16_HLD=0x01;}while(0)
#define PWM15_SET_G1_CH6_HOLD_OFF      do{PWM_P16_HLD=0x00;}while(0)
#define PWM15_SET_G1_CH7_OUT_ENABLE    do{PWM_P17_CR|= ENO;}while(0)
#define PWM15_SET_G1_CH7_OUT_DISABLE   do{PWM_P17_CR&=~ENO;}while(0)
#define PWM15_SET_G1_CH7_INIT_H        do{PWM_P17_CR|= INI;}while(0)
#define PWM15_SET_G1_CH7_INIT_L        do{PWM_P17_CR&=~INI;}while(0)
#define PWM15_SET_G1_CH7_IT_ENABLE     do{PWM_P17_CR|= ENI;}while(0)
#define PWM15_SET_G1_CH7_IT_DISABLE    do{PWM_P17_CR&=~ENI;}while(0)
#define PWM15_SET_G1_CH7_T1_IT_ENABLE  do{PWM_P17_CR|= ENT1I;}while(0)
#define PWM15_SET_G1_CH7_T1_IT_DISABLE do{PWM_P17_CR&=~ENT1I;}while(0)
#define PWM15_SET_G1_CH7_T2_IT_ENABLE  do{PWM_P17_CR|= ENT2I;}while(0)
#define PWM15_SET_G1_CH7_T2_IT_DISABLE do{PWM_P17_CR&=~ENT2I;}while(0)
#define PWM15_SET_G1_CH7_HOLD_H        do{PWM_P17_HLD=0x02;}while(0)
#define PWM15_SET_G1_CH7_HOLD_L        do{PWM_P17_HLD=0x01;}while(0)
#define PWM15_SET_G1_CH7_HOLD_OFF      do{PWM_P17_HLD=0x00;}while(0)

#define PWM15_SET_G2_CH0_OUT_ENABLE    do{PWM_P20_CR|= ENO;}while(0)
#define PWM15_SET_G2_CH0_OUT_DISABLE   do{PWM_P20_CR&=~ENO;}while(0)
#define PWM15_SET_G2_CH0_INIT_H        do{PWM_P20_CR|= INI;}while(0)
#define PWM15_SET_G2_CH0_INIT_L        do{PWM_P20_CR&=~INI;}while(0)
#define PWM15_SET_G2_CH0_IT_ENABLE     do{PWM_P20_CR|= ENI;}while(0)
#define PWM15_SET_G2_CH0_IT_DISABLE    do{PWM_P20_CR&=~ENI;}while(0)
#define PWM15_SET_G2_CH0_T1_IT_ENABLE  do{PWM_P20_CR|= ENT1I;}while(0)
#define PWM15_SET_G2_CH0_T1_IT_DISABLE do{PWM_P20_CR&=~ENT1I;}while(0)
#define PWM15_SET_G2_CH0_T2_IT_ENABLE  do{PWM_P20_CR|= ENT2I;}while(0)
#define PWM15_SET_G2_CH0_T2_IT_DISABLE do{PWM_P20_CR&=~ENT2I;}while(0)
#define PWM15_SET_G2_CH0_HOLD_H        do{PWM_P20_HLD=0x02;}while(0)
#define PWM15_SET_G2_CH0_HOLD_L        do{PWM_P20_HLD=0x01;}while(0)
#define PWM15_SET_G2_CH0_HOLD_OFF      do{PWM_P20_HLD=0x00;}while(0)
#define PWM15_SET_G2_CH1_OUT_ENABLE    do{PWM_P21_CR|= ENO;}while(0)
#define PWM15_SET_G2_CH1_OUT_DISABLE   do{PWM_P21_CR&=~ENO;}while(0)
#define PWM15_SET_G2_CH1_INIT_H        do{PWM_P21_CR|= INI;}while(0)
#define PWM15_SET_G2_CH1_INIT_L        do{PWM_P21_CR&=~INI;}while(0)
#define PWM15_SET_G2_CH1_IT_ENABLE     do{PWM_P21_CR|= ENI;}while(0)
#define PWM15_SET_G2_CH1_IT_DISABLE    do{PWM_P21_CR&=~ENI;}while(0)
#define PWM15_SET_G2_CH1_T1_IT_ENABLE  do{PWM_P21_CR|= ENT1I;}while(0)
#define PWM15_SET_G2_CH1_T1_IT_DISABLE do{PWM_P21_CR&=~ENT1I;}while(0)
#define PWM15_SET_G2_CH1_T2_IT_ENABLE  do{PWM_P21_CR|= ENT2I;}while(0)
#define PWM15_SET_G2_CH1_T2_IT_DISABLE do{PWM_P21_CR&=~ENT2I;}while(0)
#define PWM15_SET_G2_CH1_HOLD_H        do{PWM_P21_HLD=0x02;}while(0)
#define PWM15_SET_G2_CH1_HOLD_L        do{PWM_P21_HLD=0x01;}while(0)
#define PWM15_SET_G2_CH1_HOLD_OFF      do{PWM_P21_HLD=0x00;}while(0)
#define PWM15_SET_G2_CH2_OUT_ENABLE    do{PWM_P22_CR|= ENO;}while(0)
#define PWM15_SET_G2_CH2_OUT_DISABLE   do{PWM_P22_CR&=~ENO;}while(0)
#define PWM15_SET_G2_CH2_INIT_H        do{PWM_P22_CR|= INI;}while(0)
#define PWM15_SET_G2_CH2_INIT_L        do{PWM_P22_CR&=~INI;}while(0)
#define PWM15_SET_G2_CH2_IT_ENABLE     do{PWM_P22_CR|= ENI;}while(0)
#define PWM15_SET_G2_CH2_IT_DISABLE    do{PWM_P22_CR&=~ENI;}while(0)
#define PWM15_SET_G2_CH2_T1_IT_ENABLE  do{PWM_P22_CR|= ENT1I;}while(0)
#define PWM15_SET_G2_CH2_T1_IT_DISABLE do{PWM_P22_CR&=~ENT1I;}while(0)
#define PWM15_SET_G2_CH2_T2_IT_ENABLE  do{PWM_P22_CR|= ENT2I;}while(0)
#define PWM15_SET_G2_CH2_T2_IT_DISABLE do{PWM_P22_CR&=~ENT2I;}while(0)
#define PWM15_SET_G2_CH2_HOLD_H        do{PWM_P22_HLD=0x02;}while(0)
#define PWM15_SET_G2_CH2_HOLD_L        do{PWM_P22_HLD=0x01;}while(0)
#define PWM15_SET_G2_CH2_HOLD_OFF      do{PWM_P22_HLD=0x00;}while(0)
#define PWM15_SET_G2_CH3_OUT_ENABLE    do{PWM_P23_CR|= ENO;}while(0)
#define PWM15_SET_G2_CH3_OUT_DISABLE   do{PWM_P23_CR&=~ENO;}while(0)
#define PWM15_SET_G2_CH3_INIT_H        do{PWM_P23_CR|= INI;}while(0)
#define PWM15_SET_G2_CH3_INIT_L        do{PWM_P23_CR&=~INI;}while(0)
#define PWM15_SET_G2_CH3_IT_ENABLE     do{PWM_P23_CR|= ENI;}while(0)
#define PWM15_SET_G2_CH3_IT_DISABLE    do{PWM_P23_CR&=~ENI;}while(0)
#define PWM15_SET_G2_CH3_T1_IT_ENABLE  do{PWM_P23_CR|= ENT1I;}while(0)
#define PWM15_SET_G2_CH3_T1_IT_DISABLE do{PWM_P23_CR&=~ENT1I;}while(0)
#define PWM15_SET_G2_CH3_T2_IT_ENABLE  do{PWM_P23_CR|= ENT2I;}while(0)
#define PWM15_SET_G2_CH3_T2_IT_DISABLE do{PWM_P23_CR&=~ENT2I;}while(0)
#define PWM15_SET_G2_CH3_HOLD_H        do{PWM_P23_HLD=0x02;}while(0)
#define PWM15_SET_G2_CH3_HOLD_L        do{PWM_P23_HLD=0x01;}while(0)
#define PWM15_SET_G2_CH3_HOLD_OFF      do{PWM_P23_HLD=0x00;}while(0)
#define PWM15_SET_G2_CH4_OUT_ENABLE    do{PWM_P24_CR|= ENO;}while(0)
#define PWM15_SET_G2_CH4_OUT_DISABLE   do{PWM_P24_CR&=~ENO;}while(0)
#define PWM15_SET_G2_CH4_INIT_H        do{PWM_P24_CR|= INI;}while(0)
#define PWM15_SET_G2_CH4_INIT_L        do{PWM_P24_CR&=~INI;}while(0)
#define PWM15_SET_G2_CH4_IT_ENABLE     do{PWM_P24_CR|= ENI;}while(0)
#define PWM15_SET_G2_CH4_IT_DISABLE    do{PWM_P24_CR&=~ENI;}while(0)
#define PWM15_SET_G2_CH4_T1_IT_ENABLE  do{PWM_P24_CR|= ENT1I;}while(0)
#define PWM15_SET_G2_CH4_T1_IT_DISABLE do{PWM_P24_CR&=~ENT1I;}while(0)
#define PWM15_SET_G2_CH4_T2_IT_ENABLE  do{PWM_P24_CR|= ENT2I;}while(0)
#define PWM15_SET_G2_CH4_T2_IT_DISABLE do{PWM_P24_CR&=~ENT2I;}while(0)
#define PWM15_SET_G2_CH4_HOLD_H        do{PWM_P24_HLD=0x02;}while(0)
#define PWM15_SET_G2_CH4_HOLD_L        do{PWM_P24_HLD=0x01;}while(0)
#define PWM15_SET_G2_CH4_HOLD_OFF      do{PWM_P24_HLD=0x00;}while(0)
#define PWM15_SET_G2_CH5_OUT_ENABLE    do{PWM_P25_CR|= ENO;}while(0)
#define PWM15_SET_G2_CH5_OUT_DISABLE   do{PWM_P25_CR&=~ENO;}while(0)
#define PWM15_SET_G2_CH5_INIT_H        do{PWM_P25_CR|= INI;}while(0)
#define PWM15_SET_G2_CH5_INIT_L        do{PWM_P25_CR&=~INI;}while(0)
#define PWM15_SET_G2_CH5_IT_ENABLE     do{PWM_P25_CR|= ENI;}while(0)
#define PWM15_SET_G2_CH5_IT_DISABLE    do{PWM_P25_CR&=~ENI;}while(0)
#define PWM15_SET_G2_CH5_T1_IT_ENABLE  do{PWM_P25_CR|= ENT1I;}while(0)
#define PWM15_SET_G2_CH5_T1_IT_DISABLE do{PWM_P25_CR&=~ENT1I;}while(0)
#define PWM15_SET_G2_CH5_T2_IT_ENABLE  do{PWM_P25_CR|= ENT2I;}while(0)
#define PWM15_SET_G2_CH5_T2_IT_DISABLE do{PWM_P25_CR&=~ENT2I;}while(0)
#define PWM15_SET_G2_CH5_HOLD_H        do{PWM_P25_HLD=0x02;}while(0)
#define PWM15_SET_G2_CH5_HOLD_L        do{PWM_P25_HLD=0x01;}while(0)
#define PWM15_SET_G2_CH5_HOLD_OFF      do{PWM_P25_HLD=0x00;}while(0)
#define PWM15_SET_G2_CH6_OUT_ENABLE    do{PWM_P26_CR|= ENO;}while(0)
#define PWM15_SET_G2_CH6_OUT_DISABLE   do{PWM_P26_CR&=~ENO;}while(0)
#define PWM15_SET_G2_CH6_INIT_H        do{PWM_P26_CR|= INI;}while(0)
#define PWM15_SET_G2_CH6_INIT_L        do{PWM_P26_CR&=~INI;}while(0)
#define PWM15_SET_G2_CH6_IT_ENABLE     do{PWM_P26_CR|= ENI;}while(0)
#define PWM15_SET_G2_CH6_IT_DISABLE    do{PWM_P26_CR&=~ENI;}while(0)
#define PWM15_SET_G2_CH6_T1_IT_ENABLE  do{PWM_P26_CR|= ENT1I;}while(0)
#define PWM15_SET_G2_CH6_T1_IT_DISABLE do{PWM_P26_CR&=~ENT1I;}while(0)
#define PWM15_SET_G2_CH6_T2_IT_ENABLE  do{PWM_P26_CR|= ENT2I;}while(0)
#define PWM15_SET_G2_CH6_T2_IT_DISABLE do{PWM_P26_CR&=~ENT2I;}while(0)
#define PWM15_SET_G2_CH6_HOLD_H        do{PWM_P26_HLD=0x02;}while(0)
#define PWM15_SET_G2_CH6_HOLD_L        do{PWM_P26_HLD=0x01;}while(0)
#define PWM15_SET_G2_CH6_HOLD_OFF      do{PWM_P26_HLD=0x00;}while(0)
#define PWM15_SET_G2_CH7_OUT_ENABLE    do{PWM_P27_CR|= ENO;}while(0)
#define PWM15_SET_G2_CH7_OUT_DISABLE   do{PWM_P27_CR&=~ENO;}while(0)
#define PWM15_SET_G2_CH7_INIT_H        do{PWM_P27_CR|= INI;}while(0)
#define PWM15_SET_G2_CH7_INIT_L        do{PWM_P27_CR&=~INI;}while(0)
#define PWM15_SET_G2_CH7_IT_ENABLE     do{PWM_P27_CR|= ENI;}while(0)
#define PWM15_SET_G2_CH7_IT_DISABLE    do{PWM_P27_CR&=~ENI;}while(0)
#define PWM15_SET_G2_CH7_T1_IT_ENABLE  do{PWM_P27_CR|= ENT1I;}while(0)
#define PWM15_SET_G2_CH7_T1_IT_DISABLE do{PWM_P27_CR&=~ENT1I;}while(0)
#define PWM15_SET_G2_CH7_T2_IT_ENABLE  do{PWM_P27_CR|= ENT2I;}while(0)
#define PWM15_SET_G2_CH7_T2_IT_DISABLE do{PWM_P27_CR&=~ENT2I;}while(0)
#define PWM15_SET_G2_CH7_HOLD_H        do{PWM_P27_HLD=0x02;}while(0)
#define PWM15_SET_G2_CH7_HOLD_L        do{PWM_P27_HLD=0x01;}while(0)
#define PWM15_SET_G2_CH7_HOLD_OFF      do{PWM_P27_HLD=0x00;}while(0)

#define PWM15_SET_G3_CH0_OUT_ENABLE    do{PWM_P30_CR|= ENO;}while(0)
#define PWM15_SET_G3_CH0_OUT_DISABLE   do{PWM_P30_CR&=~ENO;}while(0)
#define PWM15_SET_G3_CH0_INIT_H        do{PWM_P30_CR|= INI;}while(0)
#define PWM15_SET_G3_CH0_INIT_L        do{PWM_P30_CR&=~INI;}while(0)
#define PWM15_SET_G3_CH0_IT_ENABLE     do{PWM_P30_CR|= ENI;}while(0)
#define PWM15_SET_G3_CH0_IT_DISABLE    do{PWM_P30_CR&=~ENI;}while(0)
#define PWM15_SET_G3_CH0_T1_IT_ENABLE  do{PWM_P30_CR|= ENT1I;}while(0)
#define PWM15_SET_G3_CH0_T1_IT_DISABLE do{PWM_P30_CR&=~ENT1I;}while(0)
#define PWM15_SET_G3_CH0_T2_IT_ENABLE  do{PWM_P30_CR|= ENT2I;}while(0)
#define PWM15_SET_G3_CH0_T2_IT_DISABLE do{PWM_P30_CR&=~ENT2I;}while(0)
#define PWM15_SET_G3_CH0_HOLD_H        do{PWM_P30_HLD=0x02;}while(0)
#define PWM15_SET_G3_CH0_HOLD_L        do{PWM_P30_HLD=0x01;}while(0)
#define PWM15_SET_G3_CH0_HOLD_OFF      do{PWM_P30_HLD=0x00;}while(0)
#define PWM15_SET_G3_CH1_OUT_ENABLE    do{PWM_P31_CR|= ENO;}while(0)
#define PWM15_SET_G3_CH1_OUT_DISABLE   do{PWM_P31_CR&=~ENO;}while(0)
#define PWM15_SET_G3_CH1_INIT_H        do{PWM_P31_CR|= INI;}while(0)
#define PWM15_SET_G3_CH1_INIT_L        do{PWM_P31_CR&=~INI;}while(0)
#define PWM15_SET_G3_CH1_IT_ENABLE     do{PWM_P31_CR|= ENI;}while(0)
#define PWM15_SET_G3_CH1_IT_DISABLE    do{PWM_P31_CR&=~ENI;}while(0)
#define PWM15_SET_G3_CH1_T1_IT_ENABLE  do{PWM_P31_CR|= ENT1I;}while(0)
#define PWM15_SET_G3_CH1_T1_IT_DISABLE do{PWM_P31_CR&=~ENT1I;}while(0)
#define PWM15_SET_G3_CH1_T2_IT_ENABLE  do{PWM_P31_CR|= ENT2I;}while(0)
#define PWM15_SET_G3_CH1_T2_IT_DISABLE do{PWM_P31_CR&=~ENT2I;}while(0)
#define PWM15_SET_G3_CH1_HOLD_H        do{PWM_P31_HLD=0x02;}while(0)
#define PWM15_SET_G3_CH1_HOLD_L        do{PWM_P31_HLD=0x01;}while(0)
#define PWM15_SET_G3_CH1_HOLD_OFF      do{PWM_P31_HLD=0x00;}while(0)
#define PWM15_SET_G3_CH2_OUT_ENABLE    do{PWM_P32_CR|= ENO;}while(0)
#define PWM15_SET_G3_CH2_OUT_DISABLE   do{PWM_P32_CR&=~ENO;}while(0)
#define PWM15_SET_G3_CH2_INIT_H        do{PWM_P32_CR|= INI;}while(0)
#define PWM15_SET_G3_CH2_INIT_L        do{PWM_P32_CR&=~INI;}while(0)
#define PWM15_SET_G3_CH2_IT_ENABLE     do{PWM_P32_CR|= ENI;}while(0)
#define PWM15_SET_G3_CH2_IT_DISABLE    do{PWM_P32_CR&=~ENI;}while(0)
#define PWM15_SET_G3_CH2_T1_IT_ENABLE  do{PWM_P32_CR|= ENT1I;}while(0)
#define PWM15_SET_G3_CH2_T1_IT_DISABLE do{PWM_P32_CR&=~ENT1I;}while(0)
#define PWM15_SET_G3_CH2_T2_IT_ENABLE  do{PWM_P32_CR|= ENT2I;}while(0)
#define PWM15_SET_G3_CH2_T2_IT_DISABLE do{PWM_P32_CR&=~ENT2I;}while(0)
#define PWM15_SET_G3_CH2_HOLD_H        do{PWM_P32_HLD=0x02;}while(0)
#define PWM15_SET_G3_CH2_HOLD_L        do{PWM_P32_HLD=0x01;}while(0)
#define PWM15_SET_G3_CH2_HOLD_OFF      do{PWM_P32_HLD=0x00;}while(0)
#define PWM15_SET_G3_CH3_OUT_ENABLE    do{PWM_P33_CR|= ENO;}while(0)
#define PWM15_SET_G3_CH3_OUT_DISABLE   do{PWM_P33_CR&=~ENO;}while(0)
#define PWM15_SET_G3_CH3_INIT_H        do{PWM_P33_CR|= INI;}while(0)
#define PWM15_SET_G3_CH3_INIT_L        do{PWM_P33_CR&=~INI;}while(0)
#define PWM15_SET_G3_CH3_IT_ENABLE     do{PWM_P33_CR|= ENI;}while(0)
#define PWM15_SET_G3_CH3_IT_DISABLE    do{PWM_P33_CR&=~ENI;}while(0)
#define PWM15_SET_G3_CH3_T1_IT_ENABLE  do{PWM_P33_CR|= ENT1I;}while(0)
#define PWM15_SET_G3_CH3_T1_IT_DISABLE do{PWM_P33_CR&=~ENT1I;}while(0)
#define PWM15_SET_G3_CH3_T2_IT_ENABLE  do{PWM_P33_CR|= ENT2I;}while(0)
#define PWM15_SET_G3_CH3_T2_IT_DISABLE do{PWM_P33_CR&=~ENT2I;}while(0)
#define PWM15_SET_G3_CH3_HOLD_H        do{PWM_P33_HLD=0x02;}while(0)
#define PWM15_SET_G3_CH3_HOLD_L        do{PWM_P33_HLD=0x01;}while(0)
#define PWM15_SET_G3_CH3_HOLD_OFF      do{PWM_P33_HLD=0x00;}while(0)
#define PWM15_SET_G3_CH4_OUT_ENABLE    do{PWM_P34_CR|= ENO;}while(0)
#define PWM15_SET_G3_CH4_OUT_DISABLE   do{PWM_P34_CR&=~ENO;}while(0)
#define PWM15_SET_G3_CH4_INIT_H        do{PWM_P34_CR|= INI;}while(0)
#define PWM15_SET_G3_CH4_INIT_L        do{PWM_P34_CR&=~INI;}while(0)
#define PWM15_SET_G3_CH4_IT_ENABLE     do{PWM_P34_CR|= ENI;}while(0)
#define PWM15_SET_G3_CH4_IT_DISABLE    do{PWM_P34_CR&=~ENI;}while(0)
#define PWM15_SET_G3_CH4_T1_IT_ENABLE  do{PWM_P34_CR|= ENT1I;}while(0)
#define PWM15_SET_G3_CH4_T1_IT_DISABLE do{PWM_P34_CR&=~ENT1I;}while(0)
#define PWM15_SET_G3_CH4_T2_IT_ENABLE  do{PWM_P34_CR|= ENT2I;}while(0)
#define PWM15_SET_G3_CH4_T2_IT_DISABLE do{PWM_P34_CR&=~ENT2I;}while(0)
#define PWM15_SET_G3_CH4_HOLD_H        do{PWM_P34_HLD=0x02;}while(0)
#define PWM15_SET_G3_CH4_HOLD_L        do{PWM_P34_HLD=0x01;}while(0)
#define PWM15_SET_G3_CH4_HOLD_OFF      do{PWM_P34_HLD=0x00;}while(0)
#define PWM15_SET_G3_CH5_OUT_ENABLE    do{PWM_P35_CR|= ENO;}while(0)
#define PWM15_SET_G3_CH5_OUT_DISABLE   do{PWM_P35_CR&=~ENO;}while(0)
#define PWM15_SET_G3_CH5_INIT_H        do{PWM_P35_CR|= INI;}while(0)
#define PWM15_SET_G3_CH5_INIT_L        do{PWM_P35_CR&=~INI;}while(0)
#define PWM15_SET_G3_CH5_IT_ENABLE     do{PWM_P35_CR|= ENI;}while(0)
#define PWM15_SET_G3_CH5_IT_DISABLE    do{PWM_P35_CR&=~ENI;}while(0)
#define PWM15_SET_G3_CH5_T1_IT_ENABLE  do{PWM_P35_CR|= ENT1I;}while(0)
#define PWM15_SET_G3_CH5_T1_IT_DISABLE do{PWM_P35_CR&=~ENT1I;}while(0)
#define PWM15_SET_G3_CH5_T2_IT_ENABLE  do{PWM_P35_CR|= ENT2I;}while(0)
#define PWM15_SET_G3_CH5_T2_IT_DISABLE do{PWM_P35_CR&=~ENT2I;}while(0)
#define PWM15_SET_G3_CH5_HOLD_H        do{PWM_P35_HLD=0x02;}while(0)
#define PWM15_SET_G3_CH5_HOLD_L        do{PWM_P35_HLD=0x01;}while(0)
#define PWM15_SET_G3_CH5_HOLD_OFF      do{PWM_P35_HLD=0x00;}while(0)
#define PWM15_SET_G3_CH6_OUT_ENABLE    do{PWM_P36_CR|= ENO;}while(0)
#define PWM15_SET_G3_CH6_OUT_DISABLE   do{PWM_P36_CR&=~ENO;}while(0)
#define PWM15_SET_G3_CH6_INIT_H        do{PWM_P36_CR|= INI;}while(0)
#define PWM15_SET_G3_CH6_INIT_L        do{PWM_P36_CR&=~INI;}while(0)
#define PWM15_SET_G3_CH6_IT_ENABLE     do{PWM_P36_CR|= ENI;}while(0)
#define PWM15_SET_G3_CH6_IT_DISABLE    do{PWM_P36_CR&=~ENI;}while(0)
#define PWM15_SET_G3_CH6_T1_IT_ENABLE  do{PWM_P36_CR|= ENT1I;}while(0)
#define PWM15_SET_G3_CH6_T1_IT_DISABLE do{PWM_P36_CR&=~ENT1I;}while(0)
#define PWM15_SET_G3_CH6_T2_IT_ENABLE  do{PWM_P36_CR|= ENT2I;}while(0)
#define PWM15_SET_G3_CH6_T2_IT_DISABLE do{PWM_P36_CR&=~ENT2I;}while(0)
#define PWM15_SET_G3_CH6_HOLD_H        do{PWM_P36_HLD=0x02;}while(0)
#define PWM15_SET_G3_CH6_HOLD_L        do{PWM_P36_HLD=0x01;}while(0)
#define PWM15_SET_G3_CH6_HOLD_OFF      do{PWM_P36_HLD=0x00;}while(0)
#define PWM15_SET_G3_CH7_OUT_ENABLE    do{PWM_P37_CR|= ENO;}while(0)
#define PWM15_SET_G3_CH7_OUT_DISABLE   do{PWM_P37_CR&=~ENO;}while(0)
#define PWM15_SET_G3_CH7_INIT_H        do{PWM_P37_CR|= INI;}while(0)
#define PWM15_SET_G3_CH7_INIT_L        do{PWM_P37_CR&=~INI;}while(0)
#define PWM15_SET_G3_CH7_IT_ENABLE     do{PWM_P37_CR|= ENI;}while(0)
#define PWM15_SET_G3_CH7_IT_DISABLE    do{PWM_P37_CR&=~ENI;}while(0)
#define PWM15_SET_G3_CH7_T1_IT_ENABLE  do{PWM_P37_CR|= ENT1I;}while(0)
#define PWM15_SET_G3_CH7_T1_IT_DISABLE do{PWM_P37_CR&=~ENT1I;}while(0)
#define PWM15_SET_G3_CH7_T2_IT_ENABLE  do{PWM_P37_CR|= ENT2I;}while(0)
#define PWM15_SET_G3_CH7_T2_IT_DISABLE do{PWM_P37_CR&=~ENT2I;}while(0)
#define PWM15_SET_G3_CH7_HOLD_H        do{PWM_P37_HLD=0x02;}while(0)
#define PWM15_SET_G3_CH7_HOLD_L        do{PWM_P37_HLD=0x01;}while(0)
#define PWM15_SET_G3_CH7_HOLD_OFF      do{PWM_P37_HLD=0x00;}while(0)

#define PWM15_SET_G4_CH0_OUT_ENABLE    do{PWM_P40_CR|= ENO;}while(0)
#define PWM15_SET_G4_CH0_OUT_DISABLE   do{PWM_P40_CR&=~ENO;}while(0)
#define PWM15_SET_G4_CH0_INIT_H        do{PWM_P40_CR|= INI;}while(0)
#define PWM15_SET_G4_CH0_INIT_L        do{PWM_P40_CR&=~INI;}while(0)
#define PWM15_SET_G4_CH0_IT_ENABLE     do{PWM_P40_CR|= ENI;}while(0)
#define PWM15_SET_G4_CH0_IT_DISABLE    do{PWM_P40_CR&=~ENI;}while(0)
#define PWM15_SET_G4_CH0_T1_IT_ENABLE  do{PWM_P40_CR|= ENT1I;}while(0)
#define PWM15_SET_G4_CH0_T1_IT_DISABLE do{PWM_P40_CR&=~ENT1I;}while(0)
#define PWM15_SET_G4_CH0_T2_IT_ENABLE  do{PWM_P40_CR|= ENT2I;}while(0)
#define PWM15_SET_G4_CH0_T2_IT_DISABLE do{PWM_P40_CR&=~ENT2I;}while(0)
#define PWM15_SET_G4_CH0_HOLD_H        do{PWM_P40_HLD=0x02;}while(0)
#define PWM15_SET_G4_CH0_HOLD_L        do{PWM_P40_HLD=0x01;}while(0)
#define PWM15_SET_G4_CH0_HOLD_OFF      do{PWM_P40_HLD=0x00;}while(0)
#define PWM15_SET_G4_CH1_OUT_ENABLE    do{PWM_P41_CR|= ENO;}while(0)
#define PWM15_SET_G4_CH1_OUT_DISABLE   do{PWM_P41_CR&=~ENO;}while(0)
#define PWM15_SET_G4_CH1_INIT_H        do{PWM_P41_CR|= INI;}while(0)
#define PWM15_SET_G4_CH1_INIT_L        do{PWM_P41_CR&=~INI;}while(0)
#define PWM15_SET_G4_CH1_IT_ENABLE     do{PWM_P41_CR|= ENI;}while(0)
#define PWM15_SET_G4_CH1_IT_DISABLE    do{PWM_P41_CR&=~ENI;}while(0)
#define PWM15_SET_G4_CH1_T1_IT_ENABLE  do{PWM_P41_CR|= ENT1I;}while(0)
#define PWM15_SET_G4_CH1_T1_IT_DISABLE do{PWM_P41_CR&=~ENT1I;}while(0)
#define PWM15_SET_G4_CH1_T2_IT_ENABLE  do{PWM_P41_CR|= ENT2I;}while(0)
#define PWM15_SET_G4_CH1_T2_IT_DISABLE do{PWM_P41_CR&=~ENT2I;}while(0)
#define PWM15_SET_G4_CH1_HOLD_H        do{PWM_P41_HLD=0x02;}while(0)
#define PWM15_SET_G4_CH1_HOLD_L        do{PWM_P41_HLD=0x01;}while(0)
#define PWM15_SET_G4_CH1_HOLD_OFF      do{PWM_P41_HLD=0x00;}while(0)
#define PWM15_SET_G4_CH2_OUT_ENABLE    do{PWM_P42_CR|= ENO;}while(0)
#define PWM15_SET_G4_CH2_OUT_DISABLE   do{PWM_P42_CR&=~ENO;}while(0)
#define PWM15_SET_G4_CH2_INIT_H        do{PWM_P42_CR|= INI;}while(0)
#define PWM15_SET_G4_CH2_INIT_L        do{PWM_P42_CR&=~INI;}while(0)
#define PWM15_SET_G4_CH2_IT_ENABLE     do{PWM_P42_CR|= ENI;}while(0)
#define PWM15_SET_G4_CH2_IT_DISABLE    do{PWM_P42_CR&=~ENI;}while(0)
#define PWM15_SET_G4_CH2_T1_IT_ENABLE  do{PWM_P42_CR|= ENT1I;}while(0)
#define PWM15_SET_G4_CH2_T1_IT_DISABLE do{PWM_P42_CR&=~ENT1I;}while(0)
#define PWM15_SET_G4_CH2_T2_IT_ENABLE  do{PWM_P42_CR|= ENT2I;}while(0)
#define PWM15_SET_G4_CH2_T2_IT_DISABLE do{PWM_P42_CR&=~ENT2I;}while(0)
#define PWM15_SET_G4_CH2_HOLD_H        do{PWM_P42_HLD=0x02;}while(0)
#define PWM15_SET_G4_CH2_HOLD_L        do{PWM_P42_HLD=0x01;}while(0)
#define PWM15_SET_G4_CH2_HOLD_OFF      do{PWM_P42_HLD=0x00;}while(0)
#define PWM15_SET_G4_CH3_OUT_ENABLE    do{PWM_P43_CR|= ENO;}while(0)
#define PWM15_SET_G4_CH3_OUT_DISABLE   do{PWM_P43_CR&=~ENO;}while(0)
#define PWM15_SET_G4_CH3_INIT_H        do{PWM_P43_CR|= INI;}while(0)
#define PWM15_SET_G4_CH3_INIT_L        do{PWM_P43_CR&=~INI;}while(0)
#define PWM15_SET_G4_CH3_IT_ENABLE     do{PWM_P43_CR|= ENI;}while(0)
#define PWM15_SET_G4_CH3_IT_DISABLE    do{PWM_P43_CR&=~ENI;}while(0)
#define PWM15_SET_G4_CH3_T1_IT_ENABLE  do{PWM_P43_CR|= ENT1I;}while(0)
#define PWM15_SET_G4_CH3_T1_IT_DISABLE do{PWM_P43_CR&=~ENT1I;}while(0)
#define PWM15_SET_G4_CH3_T2_IT_ENABLE  do{PWM_P43_CR|= ENT2I;}while(0)
#define PWM15_SET_G4_CH3_T2_IT_DISABLE do{PWM_P43_CR&=~ENT2I;}while(0)
#define PWM15_SET_G4_CH3_HOLD_H        do{PWM_P43_HLD=0x02;}while(0)
#define PWM15_SET_G4_CH3_HOLD_L        do{PWM_P43_HLD=0x01;}while(0)
#define PWM15_SET_G4_CH3_HOLD_OFF      do{PWM_P43_HLD=0x00;}while(0)
#define PWM15_SET_G4_CH4_OUT_ENABLE    do{PWM_P44_CR|= ENO;}while(0)
#define PWM15_SET_G4_CH4_OUT_DISABLE   do{PWM_P44_CR&=~ENO;}while(0)
#define PWM15_SET_G4_CH4_INIT_H        do{PWM_P44_CR|= INI;}while(0)
#define PWM15_SET_G4_CH4_INIT_L        do{PWM_P44_CR&=~INI;}while(0)
#define PWM15_SET_G4_CH4_IT_ENABLE     do{PWM_P44_CR|= ENI;}while(0)
#define PWM15_SET_G4_CH4_IT_DISABLE    do{PWM_P44_CR&=~ENI;}while(0)
#define PWM15_SET_G4_CH4_T1_IT_ENABLE  do{PWM_P44_CR|= ENT1I;}while(0)
#define PWM15_SET_G4_CH4_T1_IT_DISABLE do{PWM_P44_CR&=~ENT1I;}while(0)
#define PWM15_SET_G4_CH4_T2_IT_ENABLE  do{PWM_P44_CR|= ENT2I;}while(0)
#define PWM15_SET_G4_CH4_T2_IT_DISABLE do{PWM_P44_CR&=~ENT2I;}while(0)
#define PWM15_SET_G4_CH4_HOLD_H        do{PWM_P44_HLD=0x02;}while(0)
#define PWM15_SET_G4_CH4_HOLD_L        do{PWM_P44_HLD=0x01;}while(0)
#define PWM15_SET_G4_CH4_HOLD_OFF      do{PWM_P44_HLD=0x00;}while(0)
#define PWM15_SET_G4_CH5_OUT_ENABLE    do{PWM_P45_CR|= ENO;}while(0)
#define PWM15_SET_G4_CH5_OUT_DISABLE   do{PWM_P45_CR&=~ENO;}while(0)
#define PWM15_SET_G4_CH5_INIT_H        do{PWM_P45_CR|= INI;}while(0)
#define PWM15_SET_G4_CH5_INIT_L        do{PWM_P45_CR&=~INI;}while(0)
#define PWM15_SET_G4_CH5_IT_ENABLE     do{PWM_P45_CR|= ENI;}while(0)
#define PWM15_SET_G4_CH5_IT_DISABLE    do{PWM_P45_CR&=~ENI;}while(0)
#define PWM15_SET_G4_CH5_T1_IT_ENABLE  do{PWM_P45_CR|= ENT1I;}while(0)
#define PWM15_SET_G4_CH5_T1_IT_DISABLE do{PWM_P45_CR&=~ENT1I;}while(0)
#define PWM15_SET_G4_CH5_T2_IT_ENABLE  do{PWM_P45_CR|= ENT2I;}while(0)
#define PWM15_SET_G4_CH5_T2_IT_DISABLE do{PWM_P45_CR&=~ENT2I;}while(0)
#define PWM15_SET_G4_CH5_HOLD_H        do{PWM_P45_HLD=0x02;}while(0)
#define PWM15_SET_G4_CH5_HOLD_L        do{PWM_P45_HLD=0x01;}while(0)
#define PWM15_SET_G4_CH5_HOLD_OFF      do{PWM_P45_HLD=0x00;}while(0)
#define PWM15_SET_G4_CH6_OUT_ENABLE    do{PWM_P46_CR|= ENO;}while(0)
#define PWM15_SET_G4_CH6_OUT_DISABLE   do{PWM_P46_CR&=~ENO;}while(0)
#define PWM15_SET_G4_CH6_INIT_H        do{PWM_P46_CR|= INI;}while(0)
#define PWM15_SET_G4_CH6_INIT_L        do{PWM_P46_CR&=~INI;}while(0)
#define PWM15_SET_G4_CH6_IT_ENABLE     do{PWM_P46_CR|= ENI;}while(0)
#define PWM15_SET_G4_CH6_IT_DISABLE    do{PWM_P46_CR&=~ENI;}while(0)
#define PWM15_SET_G4_CH6_T1_IT_ENABLE  do{PWM_P46_CR|= ENT1I;}while(0)
#define PWM15_SET_G4_CH6_T1_IT_DISABLE do{PWM_P46_CR&=~ENT1I;}while(0)
#define PWM15_SET_G4_CH6_T2_IT_ENABLE  do{PWM_P46_CR|= ENT2I;}while(0)
#define PWM15_SET_G4_CH6_T2_IT_DISABLE do{PWM_P46_CR&=~ENT2I;}while(0)
#define PWM15_SET_G4_CH6_HOLD_H        do{PWM_P46_HLD=0x02;}while(0)
#define PWM15_SET_G4_CH6_HOLD_L        do{PWM_P46_HLD=0x01;}while(0)
#define PWM15_SET_G4_CH6_HOLD_OFF      do{PWM_P46_HLD=0x00;}while(0)
#define PWM15_SET_G4_CH7_OUT_ENABLE    do{PWM_P47_CR|= ENO;}while(0)
#define PWM15_SET_G4_CH7_OUT_DISABLE   do{PWM_P47_CR&=~ENO;}while(0)
#define PWM15_SET_G4_CH7_INIT_H        do{PWM_P47_CR|= INI;}while(0)
#define PWM15_SET_G4_CH7_INIT_L        do{PWM_P47_CR&=~INI;}while(0)
#define PWM15_SET_G4_CH7_IT_ENABLE     do{PWM_P47_CR|= ENI;}while(0)
#define PWM15_SET_G4_CH7_IT_DISABLE    do{PWM_P47_CR&=~ENI;}while(0)
#define PWM15_SET_G4_CH7_T1_IT_ENABLE  do{PWM_P47_CR|= ENT1I;}while(0)
#define PWM15_SET_G4_CH7_T1_IT_DISABLE do{PWM_P47_CR&=~ENT1I;}while(0)
#define PWM15_SET_G4_CH7_T2_IT_ENABLE  do{PWM_P47_CR|= ENT2I;}while(0)
#define PWM15_SET_G4_CH7_T2_IT_DISABLE do{PWM_P47_CR&=~ENT2I;}while(0)
#define PWM15_SET_G4_CH7_HOLD_H        do{PWM_P47_HLD=0x02;}while(0)
#define PWM15_SET_G4_CH7_HOLD_L        do{PWM_P47_HLD=0x01;}while(0)
#define PWM15_SET_G4_CH7_HOLD_OFF      do{PWM_P47_HLD=0x00;}while(0)

#define PWM15_SET_G5_CH0_OUT_ENABLE    do{PWM_P50_CR|= ENO;}while(0)
#define PWM15_SET_G5_CH0_OUT_DISABLE   do{PWM_P50_CR&=~ENO;}while(0)
#define PWM15_SET_G5_CH0_INIT_H        do{PWM_P50_CR|= INI;}while(0)
#define PWM15_SET_G5_CH0_INIT_L        do{PWM_P50_CR&=~INI;}while(0)
#define PWM15_SET_G5_CH0_IT_ENABLE     do{PWM_P50_CR|= ENI;}while(0)
#define PWM15_SET_G5_CH0_IT_DISABLE    do{PWM_P50_CR&=~ENI;}while(0)
#define PWM15_SET_G5_CH0_T1_IT_ENABLE  do{PWM_P50_CR|= ENT1I;}while(0)
#define PWM15_SET_G5_CH0_T1_IT_DISABLE do{PWM_P50_CR&=~ENT1I;}while(0)
#define PWM15_SET_G5_CH0_T2_IT_ENABLE  do{PWM_P50_CR|= ENT2I;}while(0)
#define PWM15_SET_G5_CH0_T2_IT_DISABLE do{PWM_P50_CR&=~ENT2I;}while(0)
#define PWM15_SET_G5_CH0_HOLD_H        do{PWM_P50_HLD=0x02;}while(0)
#define PWM15_SET_G5_CH0_HOLD_L        do{PWM_P50_HLD=0x01;}while(0)
#define PWM15_SET_G5_CH0_HOLD_OFF      do{PWM_P50_HLD=0x00;}while(0)
#define PWM15_SET_G5_CH1_OUT_ENABLE    do{PWM_P51_CR|= ENO;}while(0)
#define PWM15_SET_G5_CH1_OUT_DISABLE   do{PWM_P51_CR&=~ENO;}while(0)
#define PWM15_SET_G5_CH1_INIT_H        do{PWM_P51_CR|= INI;}while(0)
#define PWM15_SET_G5_CH1_INIT_L        do{PWM_P51_CR&=~INI;}while(0)
#define PWM15_SET_G5_CH1_IT_ENABLE     do{PWM_P51_CR|= ENI;}while(0)
#define PWM15_SET_G5_CH1_IT_DISABLE    do{PWM_P51_CR&=~ENI;}while(0)
#define PWM15_SET_G5_CH1_T1_IT_ENABLE  do{PWM_P51_CR|= ENT1I;}while(0)
#define PWM15_SET_G5_CH1_T1_IT_DISABLE do{PWM_P51_CR&=~ENT1I;}while(0)
#define PWM15_SET_G5_CH1_T2_IT_ENABLE  do{PWM_P51_CR|= ENT2I;}while(0)
#define PWM15_SET_G5_CH1_T2_IT_DISABLE do{PWM_P51_CR&=~ENT2I;}while(0)
#define PWM15_SET_G5_CH1_HOLD_H        do{PWM_P51_HLD=0x02;}while(0)
#define PWM15_SET_G5_CH1_HOLD_L        do{PWM_P51_HLD=0x01;}while(0)
#define PWM15_SET_G5_CH1_HOLD_OFF      do{PWM_P51_HLD=0x00;}while(0)
#define PWM15_SET_G5_CH2_OUT_ENABLE    do{PWM_P52_CR|= ENO;}while(0)
#define PWM15_SET_G5_CH2_OUT_DISABLE   do{PWM_P52_CR&=~ENO;}while(0)
#define PWM15_SET_G5_CH2_INIT_H        do{PWM_P52_CR|= INI;}while(0)
#define PWM15_SET_G5_CH2_INIT_L        do{PWM_P52_CR&=~INI;}while(0)
#define PWM15_SET_G5_CH2_IT_ENABLE     do{PWM_P52_CR|= ENI;}while(0)
#define PWM15_SET_G5_CH2_IT_DISABLE    do{PWM_P52_CR&=~ENI;}while(0)
#define PWM15_SET_G5_CH2_T1_IT_ENABLE  do{PWM_P52_CR|= ENT1I;}while(0)
#define PWM15_SET_G5_CH2_T1_IT_DISABLE do{PWM_P52_CR&=~ENT1I;}while(0)
#define PWM15_SET_G5_CH2_T2_IT_ENABLE  do{PWM_P52_CR|= ENT2I;}while(0)
#define PWM15_SET_G5_CH2_T2_IT_DISABLE do{PWM_P52_CR&=~ENT2I;}while(0)
#define PWM15_SET_G5_CH2_HOLD_H        do{PWM_P52_HLD=0x02;}while(0)
#define PWM15_SET_G5_CH2_HOLD_L        do{PWM_P52_HLD=0x01;}while(0)
#define PWM15_SET_G5_CH2_HOLD_OFF      do{PWM_P52_HLD=0x00;}while(0)
#define PWM15_SET_G5_CH3_OUT_ENABLE    do{PWM_P53_CR|= ENO;}while(0)
#define PWM15_SET_G5_CH3_OUT_DISABLE   do{PWM_P53_CR&=~ENO;}while(0)
#define PWM15_SET_G5_CH3_INIT_H        do{PWM_P53_CR|= INI;}while(0)
#define PWM15_SET_G5_CH3_INIT_L        do{PWM_P53_CR&=~INI;}while(0)
#define PWM15_SET_G5_CH3_IT_ENABLE     do{PWM_P53_CR|= ENI;}while(0)
#define PWM15_SET_G5_CH3_IT_DISABLE    do{PWM_P53_CR&=~ENI;}while(0)
#define PWM15_SET_G5_CH3_T1_IT_ENABLE  do{PWM_P53_CR|= ENT1I;}while(0)
#define PWM15_SET_G5_CH3_T1_IT_DISABLE do{PWM_P53_CR&=~ENT1I;}while(0)
#define PWM15_SET_G5_CH3_T2_IT_ENABLE  do{PWM_P53_CR|= ENT2I;}while(0)
#define PWM15_SET_G5_CH3_T2_IT_DISABLE do{PWM_P53_CR&=~ENT2I;}while(0)
#define PWM15_SET_G5_CH3_HOLD_H        do{PWM_P53_HLD=0x02;}while(0)
#define PWM15_SET_G5_CH3_HOLD_L        do{PWM_P53_HLD=0x01;}while(0)
#define PWM15_SET_G5_CH3_HOLD_OFF      do{PWM_P53_HLD=0x00;}while(0)
#define PWM15_SET_G5_CH4_OUT_ENABLE    do{PWM_P54_CR|= ENO;}while(0)
#define PWM15_SET_G5_CH4_OUT_DISABLE   do{PWM_P54_CR&=~ENO;}while(0)
#define PWM15_SET_G5_CH4_INIT_H        do{PWM_P54_CR|= INI;}while(0)
#define PWM15_SET_G5_CH4_INIT_L        do{PWM_P54_CR&=~INI;}while(0)
#define PWM15_SET_G5_CH4_IT_ENABLE     do{PWM_P54_CR|= ENI;}while(0)
#define PWM15_SET_G5_CH4_IT_DISABLE    do{PWM_P54_CR&=~ENI;}while(0)
#define PWM15_SET_G5_CH4_T1_IT_ENABLE  do{PWM_P54_CR|= ENT1I;}while(0)
#define PWM15_SET_G5_CH4_T1_IT_DISABLE do{PWM_P54_CR&=~ENT1I;}while(0)
#define PWM15_SET_G5_CH4_T2_IT_ENABLE  do{PWM_P54_CR|= ENT2I;}while(0)
#define PWM15_SET_G5_CH4_T2_IT_DISABLE do{PWM_P54_CR&=~ENT2I;}while(0)
#define PWM15_SET_G5_CH4_HOLD_H        do{PWM_P54_HLD=0x02;}while(0)
#define PWM15_SET_G5_CH4_HOLD_L        do{PWM_P54_HLD=0x01;}while(0)
#define PWM15_SET_G5_CH4_HOLD_OFF      do{PWM_P54_HLD=0x00;}while(0)
#define PWM15_SET_G5_CH5_OUT_ENABLE    do{PWM_P55_CR|= ENO;}while(0)
#define PWM15_SET_G5_CH5_OUT_DISABLE   do{PWM_P55_CR&=~ENO;}while(0)
#define PWM15_SET_G5_CH5_INIT_H        do{PWM_P55_CR|= INI;}while(0)
#define PWM15_SET_G5_CH5_INIT_L        do{PWM_P55_CR&=~INI;}while(0)
#define PWM15_SET_G5_CH5_IT_ENABLE     do{PWM_P55_CR|= ENI;}while(0)
#define PWM15_SET_G5_CH5_IT_DISABLE    do{PWM_P55_CR&=~ENI;}while(0)
#define PWM15_SET_G5_CH5_T1_IT_ENABLE  do{PWM_P55_CR|= ENT1I;}while(0)
#define PWM15_SET_G5_CH5_T1_IT_DISABLE do{PWM_P55_CR&=~ENT1I;}while(0)
#define PWM15_SET_G5_CH5_T2_IT_ENABLE  do{PWM_P55_CR|= ENT2I;}while(0)
#define PWM15_SET_G5_CH5_T2_IT_DISABLE do{PWM_P55_CR&=~ENT2I;}while(0)
#define PWM15_SET_G5_CH5_HOLD_H        do{PWM_P55_HLD=0x02;}while(0)
#define PWM15_SET_G5_CH5_HOLD_L        do{PWM_P55_HLD=0x01;}while(0)
#define PWM15_SET_G5_CH5_HOLD_OFF      do{PWM_P55_HLD=0x00;}while(0)
#define PWM15_SET_G5_CH6_OUT_ENABLE    do{PWM_P56_CR|= ENO;}while(0)
#define PWM15_SET_G5_CH6_OUT_DISABLE   do{PWM_P56_CR&=~ENO;}while(0)
#define PWM15_SET_G5_CH6_INIT_H        do{PWM_P56_CR|= INI;}while(0)
#define PWM15_SET_G5_CH6_INIT_L        do{PWM_P56_CR&=~INI;}while(0)
#define PWM15_SET_G5_CH6_IT_ENABLE     do{PWM_P56_CR|= ENI;}while(0)
#define PWM15_SET_G5_CH6_IT_DISABLE    do{PWM_P56_CR&=~ENI;}while(0)
#define PWM15_SET_G5_CH6_T1_IT_ENABLE  do{PWM_P56_CR|= ENT1I;}while(0)
#define PWM15_SET_G5_CH6_T1_IT_DISABLE do{PWM_P56_CR&=~ENT1I;}while(0)
#define PWM15_SET_G5_CH6_T2_IT_ENABLE  do{PWM_P56_CR|= ENT2I;}while(0)
#define PWM15_SET_G5_CH6_T2_IT_DISABLE do{PWM_P56_CR&=~ENT2I;}while(0)
#define PWM15_SET_G5_CH6_HOLD_H        do{PWM_P56_HLD=0x02;}while(0)
#define PWM15_SET_G5_CH6_HOLD_L        do{PWM_P56_HLD=0x01;}while(0)
#define PWM15_SET_G5_CH6_HOLD_OFF      do{PWM_P56_HLD=0x00;}while(0)
#define PWM15_SET_G5_CH7_OUT_ENABLE    do{PWM_P57_CR|= ENO;}while(0)
#define PWM15_SET_G5_CH7_OUT_DISABLE   do{PWM_P57_CR&=~ENO;}while(0)
#define PWM15_SET_G5_CH7_INIT_H        do{PWM_P57_CR|= INI;}while(0)
#define PWM15_SET_G5_CH7_INIT_L        do{PWM_P57_CR&=~INI;}while(0)
#define PWM15_SET_G5_CH7_IT_ENABLE     do{PWM_P57_CR|= ENI;}while(0)
#define PWM15_SET_G5_CH7_IT_DISABLE    do{PWM_P57_CR&=~ENI;}while(0)
#define PWM15_SET_G5_CH7_T1_IT_ENABLE  do{PWM_P57_CR|= ENT1I;}while(0)
#define PWM15_SET_G5_CH7_T1_IT_DISABLE do{PWM_P57_CR&=~ENT1I;}while(0)
#define PWM15_SET_G5_CH7_T2_IT_ENABLE  do{PWM_P57_CR|= ENT2I;}while(0)
#define PWM15_SET_G5_CH7_T2_IT_DISABLE do{PWM_P57_CR&=~ENT2I;}while(0)
#define PWM15_SET_G5_CH7_HOLD_H        do{PWM_P57_HLD=0x02;}while(0)
#define PWM15_SET_G5_CH7_HOLD_L        do{PWM_P57_HLD=0x01;}while(0)
#define PWM15_SET_G5_CH7_HOLD_OFF      do{PWM_P57_HLD=0x00;}while(0)
#endif



#if     ((ECBM_MCU&0xF0F000)==0x201000)
#define PWM15_RESET                 do{PWMSET|= PWMRST;}while(0)
#define PWM15_POWER_ON              do{PWMSET|= ENPWM; }while(0)
#define PWM15_POWER_OFF             do{PWMSET&=~ENPWM; }while(0)
#define PWM15_START                 do{PWMCFG|= PWMCEN;}while(0)
#define PWM15_STOP                  do{PWMCFG&=~PWMCEN;}while(0)
#elif   ((ECBM_MCU&0xF0F000)==0x200000)
#define PWM15_RESET                 do{}while(0)
#define PWM15_POWER_ON              do{}while(0)
#define PWM15_POWER_OFF             do{}while(0)
#define PWM15_START                 do{PWMCR|= PWM_EN;}while(0)
#define PWM15_STOP                  do{PWMCR&=~PWM_EN;}while(0)
#elif   ((ECBM_MCU&0xFF0000)==0x320000)
#define PWM15_RESET                 do{PWMSET|= PWMRST;}while(0)

#define PWM15_G0_POWER_ON           do{PWMSET|= 0x01;}while(0)
#define PWM15_G1_POWER_ON           do{PWMSET|= 0x02;}while(0)
#define PWM15_G2_POWER_ON           do{PWMSET|= 0x04;}while(0)
#define PWM15_G3_POWER_ON           do{PWMSET|= 0x08;}while(0)
#define PWM15_G4_POWER_ON           do{PWMSET|= 0x10;}while(0)
#define PWM15_G5_POWER_ON           do{PWMSET|= 0x20;}while(0)

#define PWM15_G0_POWER_OFF          do{PWMSET&=~0x01;}while(0)
#define PWM15_G1_POWER_OFF          do{PWMSET&=~0x02;}while(0)
#define PWM15_G2_POWER_OFF          do{PWMSET&=~0x04;}while(0)
#define PWM15_G3_POWER_OFF          do{PWMSET&=~0x08;}while(0)
#define PWM15_G4_POWER_OFF          do{PWMSET&=~0x10;}while(0)
#define PWM15_G5_POWER_OFF          do{PWMSET&=~0x20;}while(0)

#define PWM15_G0_START              do{PWMCFG01|= 0x01;}while(0)
#define PWM15_G1_START              do{PWMCFG01|= 0x10;}while(0)
#define PWM15_G2_START              do{PWMCFG23|= 0x01;}while(0)
#define PWM15_G3_START              do{PWMCFG23|= 0x10;}while(0)
#define PWM15_G4_START              do{PWMCFG45|= 0x01;}while(0)
#define PWM15_G5_START              do{PWMCFG45|= 0x10;}while(0)

#define PWM15_G0_STOP               do{PWMCFG01&=~0x01;}while(0)
#define PWM15_G1_STOP               do{PWMCFG01&=~0x10;}while(0)
#define PWM15_G2_STOP               do{PWMCFG23&=~0x01;}while(0)
#define PWM15_G3_STOP               do{PWMCFG23&=~0x10;}while(0)
#define PWM15_G4_STOP               do{PWMCFG45&=~0x01;}while(0)
#define PWM15_G5_STOP               do{PWMCFG45&=~0x10;}while(0)
#endif






#if     ((ECBM_MCU&0xF00000)==0x200000)
#define PWM15_SET_REG_CLK(value)    do{PWM_CKS=(u8)(value);}while(0)
#define PWM15_GET_REG_CLK           (PWM_CKS)
#define PWM15_SET_REG_COUNT(value)  do{PWM_C=(u16)(value);}while(0)
#define PWM15_GET_REG_COUNT         (PWM_C)

#define PWM15_SET_REG_CH0_T1(value) do{PWM_CH0_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_CH1_T1(value) do{PWM_CH1_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_CH2_T1(value) do{PWM_CH2_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_CH3_T1(value) do{PWM_CH3_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_CH4_T1(value) do{PWM_CH4_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_CH5_T1(value) do{PWM_CH5_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_CH6_T1(value) do{PWM_CH6_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_CH7_T1(value) do{PWM_CH7_T1=(u16)(value);}while(0)

#define PWM15_SET_REG_CH0_T2(value) do{PWM_CH0_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_CH1_T2(value) do{PWM_CH1_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_CH2_T2(value) do{PWM_CH2_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_CH3_T2(value) do{PWM_CH3_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_CH4_T2(value) do{PWM_CH4_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_CH5_T2(value) do{PWM_CH5_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_CH6_T2(value) do{PWM_CH6_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_CH7_T2(value) do{PWM_CH7_T2=(u16)(value);}while(0)

#define PWM15_SET_REG_CH0_CR(value) do{PWM_CH0_CR=(u8)(value);}while(0)
#define PWM15_SET_REG_CH1_CR(value) do{PWM_CH1_CR=(u8)(value);}while(0)
#define PWM15_SET_REG_CH2_CR(value) do{PWM_CH2_CR=(u8)(value);}while(0)
#define PWM15_SET_REG_CH3_CR(value) do{PWM_CH3_CR=(u8)(value);}while(0)
#define PWM15_SET_REG_CH4_CR(value) do{PWM_CH4_CR=(u8)(value);}while(0)
#define PWM15_SET_REG_CH5_CR(value) do{PWM_CH5_CR=(u8)(value);}while(0)
#define PWM15_SET_REG_CH6_CR(value) do{PWM_CH6_CR=(u8)(value);}while(0)
#define PWM15_SET_REG_CH7_CR(value) do{PWM_CH7_CR=(u8)(value);}while(0)

#define PWM15_GET_REG_CH0_T1        (PWM_CH0_T1)
#define PWM15_GET_REG_CH1_T1        (PWM_CH1_T1)
#define PWM15_GET_REG_CH2_T1        (PWM_CH2_T1)
#define PWM15_GET_REG_CH3_T1        (PWM_CH3_T1)
#define PWM15_GET_REG_CH4_T1        (PWM_CH4_T1)
#define PWM15_GET_REG_CH5_T1        (PWM_CH5_T1)
#define PWM15_GET_REG_CH6_T1        (PWM_CH6_T1)
#define PWM15_GET_REG_CH7_T1        (PWM_CH7_T1)

#define PWM15_GET_REG_CH0_T2        (PWM_CH0_T2)
#define PWM15_GET_REG_CH1_T2        (PWM_CH1_T2)
#define PWM15_GET_REG_CH2_T2        (PWM_CH2_T2)
#define PWM15_GET_REG_CH3_T2        (PWM_CH3_T2)
#define PWM15_GET_REG_CH4_T2        (PWM_CH4_T2)
#define PWM15_GET_REG_CH5_T2        (PWM_CH5_T2)
#define PWM15_GET_REG_CH6_T2        (PWM_CH6_T2)
#define PWM15_GET_REG_CH7_T2        (PWM_CH7_T2)

#define PWM15_GET_REG_CH0_CR        (PWM_CH0_CR)
#define PWM15_GET_REG_CH1_CR        (PWM_CH1_CR)
#define PWM15_GET_REG_CH2_CR        (PWM_CH2_CR)
#define PWM15_GET_REG_CH3_CR        (PWM_CH3_CR)
#define PWM15_GET_REG_CH4_CR        (PWM_CH4_CR)
#define PWM15_GET_REG_CH5_CR        (PWM_CH5_CR)
#define PWM15_GET_REG_CH6_CR        (PWM_CH6_CR)
#define PWM15_GET_REG_CH7_CR        (PWM_CH7_CR)

#elif   ((ECBM_MCU&0xFF0000)==0x320000)
#define PWM15_SET_REG_G0_CLK(value)    do{PWM_P0_CKS=(u8)(value);}while(0)
#define PWM15_GET_REG_G0_CLK           (PWM_P0_CKS)
#define PWM15_SET_REG_G0_COUNT(value)  do{PWM_P0_C=(u16)(value);}while(0)
#define PWM15_GET_REG_G0_COUNT         (PWM_P0_C)
#define PWM15_SET_REG_G1_CLK(value)    do{PWM_P1_CKS=(u8)(value);}while(0)
#define PWM15_GET_REG_G1_CLK           (PWM_P1_CKS)
#define PWM15_SET_REG_G1_COUNT(value)  do{PWM_P1_C=(u16)(value);}while(0)
#define PWM15_GET_REG_G1_COUNT         (PWM_P1_C)
#define PWM15_SET_REG_G2_CLK(value)    do{PWM_P2_CKS=(u8)(value);}while(0)
#define PWM15_GET_REG_G2_CLK           (PWM_P2_CKS)
#define PWM15_SET_REG_G2_COUNT(value)  do{PWM_P2_C=(u16)(value);}while(0)
#define PWM15_GET_REG_G2_COUNT         (PWM_P2_C)
#define PWM15_SET_REG_G3_CLK(value)    do{PWM_P3_CKS=(u8)(value);}while(0)
#define PWM15_GET_REG_G3_CLK           (PWM_P3_CKS)
#define PWM15_SET_REG_G3_COUNT(value)  do{PWM_P3_C=(u16)(value);}while(0)
#define PWM15_GET_REG_G3_COUNT         (PWM_P3_C)
#define PWM15_SET_REG_G4_CLK(value)    do{PWM_P4_CKS=(u8)(value);}while(0)
#define PWM15_GET_REG_G4_CLK           (PWM_P4_CKS)
#define PWM15_SET_REG_G4_COUNT(value)  do{PWM_P4_C=(u16)(value);}while(0)
#define PWM15_GET_REG_G4_COUNT         (PWM_P4_C)
#define PWM15_SET_REG_G5_CLK(value)    do{PWM_P5_CKS=(u8)(value);}while(0)
#define PWM15_GET_REG_G5_CLK           (PWM_P5_CKS)
#define PWM15_SET_REG_G5_COUNT(value)  do{PWM_P5_C=(u16)(value);}while(0)
#define PWM15_GET_REG_G5_COUNT         (PWM_P5_C)

#define PWM15_SET_REG_G0_CH0_T1(value) do{PWM_P00_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH1_T1(value) do{PWM_P01_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH2_T1(value) do{PWM_P02_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH3_T1(value) do{PWM_P03_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH4_T1(value) do{PWM_P04_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH5_T1(value) do{PWM_P05_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH6_T1(value) do{PWM_P06_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH7_T1(value) do{PWM_P07_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH0_T1(value) do{PWM_P10_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH1_T1(value) do{PWM_P11_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH2_T1(value) do{PWM_P12_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH3_T1(value) do{PWM_P13_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH4_T1(value) do{PWM_P14_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH5_T1(value) do{PWM_P15_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH6_T1(value) do{PWM_P16_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH7_T1(value) do{PWM_P17_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH0_T1(value) do{PWM_P20_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH1_T1(value) do{PWM_P21_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH2_T1(value) do{PWM_P22_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH3_T1(value) do{PWM_P23_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH4_T1(value) do{PWM_P24_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH5_T1(value) do{PWM_P25_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH6_T1(value) do{PWM_P26_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH7_T1(value) do{PWM_P27_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH0_T1(value) do{PWM_P30_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH1_T1(value) do{PWM_P31_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH2_T1(value) do{PWM_P32_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH3_T1(value) do{PWM_P33_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH4_T1(value) do{PWM_P34_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH5_T1(value) do{PWM_P35_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH6_T1(value) do{PWM_P36_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH7_T1(value) do{PWM_P37_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH0_T1(value) do{PWM_P40_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH1_T1(value) do{PWM_P41_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH2_T1(value) do{PWM_P42_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH3_T1(value) do{PWM_P43_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH4_T1(value) do{PWM_P44_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH5_T1(value) do{PWM_P45_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH6_T1(value) do{PWM_P46_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH7_T1(value) do{PWM_P47_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH0_T1(value) do{PWM_P50_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH1_T1(value) do{PWM_P51_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH2_T1(value) do{PWM_P52_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH3_T1(value) do{PWM_P53_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH4_T1(value) do{PWM_P54_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH5_T1(value) do{PWM_P55_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH6_T1(value) do{PWM_P56_T1=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH7_T1(value) do{PWM_P57_T1=(u16)(value);}while(0)

#define PWM15_SET_REG_G0_CH0_T2(value) do{PWM_P00_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH1_T2(value) do{PWM_P01_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH2_T2(value) do{PWM_P02_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH3_T2(value) do{PWM_P03_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH4_T2(value) do{PWM_P04_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH5_T2(value) do{PWM_P05_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH6_T2(value) do{PWM_P06_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH7_T2(value) do{PWM_P07_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH0_T2(value) do{PWM_P10_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH1_T2(value) do{PWM_P11_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH2_T2(value) do{PWM_P12_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH3_T2(value) do{PWM_P13_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH4_T2(value) do{PWM_P14_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH5_T2(value) do{PWM_P15_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH6_T2(value) do{PWM_P16_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH7_T2(value) do{PWM_P17_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH0_T2(value) do{PWM_P20_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH1_T2(value) do{PWM_P21_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH2_T2(value) do{PWM_P22_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH3_T2(value) do{PWM_P23_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH4_T2(value) do{PWM_P24_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH5_T2(value) do{PWM_P25_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH6_T2(value) do{PWM_P26_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH7_T2(value) do{PWM_P27_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH0_T2(value) do{PWM_P30_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH1_T2(value) do{PWM_P31_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH2_T2(value) do{PWM_P32_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH3_T2(value) do{PWM_P33_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH4_T2(value) do{PWM_P34_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH5_T2(value) do{PWM_P35_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH6_T2(value) do{PWM_P36_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH7_T2(value) do{PWM_P37_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH0_T2(value) do{PWM_P40_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH1_T2(value) do{PWM_P41_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH2_T2(value) do{PWM_P42_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH3_T2(value) do{PWM_P43_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH4_T2(value) do{PWM_P44_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH5_T2(value) do{PWM_P45_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH6_T2(value) do{PWM_P46_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH7_T2(value) do{PWM_P47_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH0_T2(value) do{PWM_P50_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH1_T2(value) do{PWM_P51_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH2_T2(value) do{PWM_P52_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH3_T2(value) do{PWM_P53_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH4_T2(value) do{PWM_P54_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH5_T2(value) do{PWM_P55_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH6_T2(value) do{PWM_P56_T2=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH7_T2(value) do{PWM_P57_T2=(u16)(value);}while(0)

#define PWM15_SET_REG_G0_CH0_CR(value) do{PWM_P00_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH1_CR(value) do{PWM_P01_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH2_CR(value) do{PWM_P02_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH3_CR(value) do{PWM_P03_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH4_CR(value) do{PWM_P04_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH5_CR(value) do{PWM_P05_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH6_CR(value) do{PWM_P06_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G0_CH7_CR(value) do{PWM_P07_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH0_CR(value) do{PWM_P10_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH1_CR(value) do{PWM_P11_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH2_CR(value) do{PWM_P12_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH3_CR(value) do{PWM_P13_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH4_CR(value) do{PWM_P14_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH5_CR(value) do{PWM_P15_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH6_CR(value) do{PWM_P16_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G1_CH7_CR(value) do{PWM_P17_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH0_CR(value) do{PWM_P20_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH1_CR(value) do{PWM_P21_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH2_CR(value) do{PWM_P22_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH3_CR(value) do{PWM_P23_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH4_CR(value) do{PWM_P24_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH5_CR(value) do{PWM_P25_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH6_CR(value) do{PWM_P26_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G2_CH7_CR(value) do{PWM_P27_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH0_CR(value) do{PWM_P30_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH1_CR(value) do{PWM_P31_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH2_CR(value) do{PWM_P32_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH3_CR(value) do{PWM_P33_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH4_CR(value) do{PWM_P34_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH5_CR(value) do{PWM_P35_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH6_CR(value) do{PWM_P36_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G3_CH7_CR(value) do{PWM_P37_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH0_CR(value) do{PWM_P40_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH1_CR(value) do{PWM_P41_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH2_CR(value) do{PWM_P42_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH3_CR(value) do{PWM_P43_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH4_CR(value) do{PWM_P44_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH5_CR(value) do{PWM_P45_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH6_CR(value) do{PWM_P46_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G4_CH7_CR(value) do{PWM_P47_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH0_CR(value) do{PWM_P50_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH1_CR(value) do{PWM_P51_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH2_CR(value) do{PWM_P52_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH3_CR(value) do{PWM_P53_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH4_CR(value) do{PWM_P54_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH5_CR(value) do{PWM_P55_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH6_CR(value) do{PWM_P56_CR=(u16)(value);}while(0)
#define PWM15_SET_REG_G5_CH7_CR(value) do{PWM_P57_CR=(u16)(value);}while(0)

#define PWM15_GET_REG_G0_CH0_T1        (PWM_P00_T1)
#define PWM15_GET_REG_G0_CH1_T1        (PWM_P01_T1)
#define PWM15_GET_REG_G0_CH2_T1        (PWM_P02_T1)
#define PWM15_GET_REG_G0_CH3_T1        (PWM_P03_T1)
#define PWM15_GET_REG_G0_CH4_T1        (PWM_P04_T1)
#define PWM15_GET_REG_G0_CH5_T1        (PWM_P05_T1)
#define PWM15_GET_REG_G0_CH6_T1        (PWM_P06_T1)
#define PWM15_GET_REG_G0_CH7_T1        (PWM_P07_T1)
#define PWM15_GET_REG_G1_CH0_T1        (PWM_P10_T1)
#define PWM15_GET_REG_G1_CH1_T1        (PWM_P11_T1)
#define PWM15_GET_REG_G1_CH2_T1        (PWM_P12_T1)
#define PWM15_GET_REG_G1_CH3_T1        (PWM_P13_T1)
#define PWM15_GET_REG_G1_CH4_T1        (PWM_P14_T1)
#define PWM15_GET_REG_G1_CH5_T1        (PWM_P15_T1)
#define PWM15_GET_REG_G1_CH6_T1        (PWM_P16_T1)
#define PWM15_GET_REG_G1_CH7_T1        (PWM_P17_T1)
#define PWM15_GET_REG_G2_CH0_T1        (PWM_P20_T1)
#define PWM15_GET_REG_G2_CH1_T1        (PWM_P21_T1)
#define PWM15_GET_REG_G2_CH2_T1        (PWM_P22_T1)
#define PWM15_GET_REG_G2_CH3_T1        (PWM_P23_T1)
#define PWM15_GET_REG_G2_CH4_T1        (PWM_P24_T1)
#define PWM15_GET_REG_G2_CH5_T1        (PWM_P25_T1)
#define PWM15_GET_REG_G2_CH6_T1        (PWM_P26_T1)
#define PWM15_GET_REG_G2_CH7_T1        (PWM_P27_T1)
#define PWM15_GET_REG_G3_CH0_T1        (PWM_P30_T1)
#define PWM15_GET_REG_G3_CH1_T1        (PWM_P31_T1)
#define PWM15_GET_REG_G3_CH2_T1        (PWM_P32_T1)
#define PWM15_GET_REG_G3_CH3_T1        (PWM_P33_T1)
#define PWM15_GET_REG_G3_CH4_T1        (PWM_P34_T1)
#define PWM15_GET_REG_G3_CH5_T1        (PWM_P35_T1)
#define PWM15_GET_REG_G3_CH6_T1        (PWM_P36_T1)
#define PWM15_GET_REG_G3_CH7_T1        (PWM_P37_T1)
#define PWM15_GET_REG_G4_CH0_T1        (PWM_P40_T1)
#define PWM15_GET_REG_G4_CH1_T1        (PWM_P41_T1)
#define PWM15_GET_REG_G4_CH2_T1        (PWM_P42_T1)
#define PWM15_GET_REG_G4_CH3_T1        (PWM_P43_T1)
#define PWM15_GET_REG_G4_CH4_T1        (PWM_P44_T1)
#define PWM15_GET_REG_G4_CH5_T1        (PWM_P45_T1)
#define PWM15_GET_REG_G4_CH6_T1        (PWM_P46_T1)
#define PWM15_GET_REG_G4_CH7_T1        (PWM_P47_T1)
#define PWM15_GET_REG_G5_CH0_T1        (PWM_P50_T1)
#define PWM15_GET_REG_G5_CH1_T1        (PWM_P51_T1)
#define PWM15_GET_REG_G5_CH2_T1        (PWM_P52_T1)
#define PWM15_GET_REG_G5_CH3_T1        (PWM_P53_T1)
#define PWM15_GET_REG_G5_CH4_T1        (PWM_P54_T1)
#define PWM15_GET_REG_G5_CH5_T1        (PWM_P55_T1)
#define PWM15_GET_REG_G5_CH6_T1        (PWM_P56_T1)
#define PWM15_GET_REG_G5_CH7_T1        (PWM_P57_T1)

#define PWM15_GET_REG_G0_CH0_T2        (PWM_P00_T2)
#define PWM15_GET_REG_G0_CH1_T2        (PWM_P01_T2)
#define PWM15_GET_REG_G0_CH2_T2        (PWM_P02_T2)
#define PWM15_GET_REG_G0_CH3_T2        (PWM_P03_T2)
#define PWM15_GET_REG_G0_CH4_T2        (PWM_P04_T2)
#define PWM15_GET_REG_G0_CH5_T2        (PWM_P05_T2)
#define PWM15_GET_REG_G0_CH6_T2        (PWM_P06_T2)
#define PWM15_GET_REG_G0_CH7_T2        (PWM_P07_T2)
#define PWM15_GET_REG_G1_CH0_T2        (PWM_P10_T2)
#define PWM15_GET_REG_G1_CH1_T2        (PWM_P11_T2)
#define PWM15_GET_REG_G1_CH2_T2        (PWM_P12_T2)
#define PWM15_GET_REG_G1_CH3_T2        (PWM_P13_T2)
#define PWM15_GET_REG_G1_CH4_T2        (PWM_P14_T2)
#define PWM15_GET_REG_G1_CH5_T2        (PWM_P15_T2)
#define PWM15_GET_REG_G1_CH6_T2        (PWM_P16_T2)
#define PWM15_GET_REG_G1_CH7_T2        (PWM_P17_T2)
#define PWM15_GET_REG_G2_CH0_T2        (PWM_P20_T2)
#define PWM15_GET_REG_G2_CH1_T2        (PWM_P21_T2)
#define PWM15_GET_REG_G2_CH2_T2        (PWM_P22_T2)
#define PWM15_GET_REG_G2_CH3_T2        (PWM_P23_T2)
#define PWM15_GET_REG_G2_CH4_T2        (PWM_P24_T2)
#define PWM15_GET_REG_G2_CH5_T2        (PWM_P25_T2)
#define PWM15_GET_REG_G2_CH6_T2        (PWM_P26_T2)
#define PWM15_GET_REG_G2_CH7_T2        (PWM_P27_T2)
#define PWM15_GET_REG_G3_CH0_T2        (PWM_P30_T2)
#define PWM15_GET_REG_G3_CH1_T2        (PWM_P31_T2)
#define PWM15_GET_REG_G3_CH2_T2        (PWM_P32_T2)
#define PWM15_GET_REG_G3_CH3_T2        (PWM_P33_T2)
#define PWM15_GET_REG_G3_CH4_T2        (PWM_P34_T2)
#define PWM15_GET_REG_G3_CH5_T2        (PWM_P35_T2)
#define PWM15_GET_REG_G3_CH6_T2        (PWM_P36_T2)
#define PWM15_GET_REG_G3_CH7_T2        (PWM_P37_T2)
#define PWM15_GET_REG_G4_CH0_T2        (PWM_P40_T2)
#define PWM15_GET_REG_G4_CH1_T2        (PWM_P41_T2)
#define PWM15_GET_REG_G4_CH2_T2        (PWM_P42_T2)
#define PWM15_GET_REG_G4_CH3_T2        (PWM_P43_T2)
#define PWM15_GET_REG_G4_CH4_T2        (PWM_P44_T2)
#define PWM15_GET_REG_G4_CH5_T2        (PWM_P45_T2)
#define PWM15_GET_REG_G4_CH6_T2        (PWM_P46_T2)
#define PWM15_GET_REG_G4_CH7_T2        (PWM_P47_T2)
#define PWM15_GET_REG_G5_CH0_T2        (PWM_P50_T2)
#define PWM15_GET_REG_G5_CH1_T2        (PWM_P51_T2)
#define PWM15_GET_REG_G5_CH2_T2        (PWM_P52_T2)
#define PWM15_GET_REG_G5_CH3_T2        (PWM_P53_T2)
#define PWM15_GET_REG_G5_CH4_T2        (PWM_P54_T2)
#define PWM15_GET_REG_G5_CH5_T2        (PWM_P55_T2)
#define PWM15_GET_REG_G5_CH6_T2        (PWM_P56_T2)
#define PWM15_GET_REG_G5_CH7_T2        (PWM_P57_T2)

#define PWM15_GET_REG_G0_CH0_CR        (PWM_P00_CR)
#define PWM15_GET_REG_G0_CH1_CR        (PWM_P01_CR)
#define PWM15_GET_REG_G0_CH2_CR        (PWM_P02_CR)
#define PWM15_GET_REG_G0_CH3_CR        (PWM_P03_CR)
#define PWM15_GET_REG_G0_CH4_CR        (PWM_P04_CR)
#define PWM15_GET_REG_G0_CH5_CR        (PWM_P05_CR)
#define PWM15_GET_REG_G0_CH6_CR        (PWM_P06_CR)
#define PWM15_GET_REG_G0_CH7_CR        (PWM_P07_CR)
#define PWM15_GET_REG_G1_CH0_CR        (PWM_P10_CR)
#define PWM15_GET_REG_G1_CH1_CR        (PWM_P11_CR)
#define PWM15_GET_REG_G1_CH2_CR        (PWM_P12_CR)
#define PWM15_GET_REG_G1_CH3_CR        (PWM_P13_CR)
#define PWM15_GET_REG_G1_CH4_CR        (PWM_P14_CR)
#define PWM15_GET_REG_G1_CH5_CR        (PWM_P15_CR)
#define PWM15_GET_REG_G1_CH6_CR        (PWM_P16_CR)
#define PWM15_GET_REG_G1_CH7_CR        (PWM_P17_CR)
#define PWM15_GET_REG_G2_CH0_CR        (PWM_P20_CR)
#define PWM15_GET_REG_G2_CH1_CR        (PWM_P21_CR)
#define PWM15_GET_REG_G2_CH2_CR        (PWM_P22_CR)
#define PWM15_GET_REG_G2_CH3_CR        (PWM_P23_CR)
#define PWM15_GET_REG_G2_CH4_CR        (PWM_P24_CR)
#define PWM15_GET_REG_G2_CH5_CR        (PWM_P25_CR)
#define PWM15_GET_REG_G2_CH6_CR        (PWM_P26_CR)
#define PWM15_GET_REG_G2_CH7_CR        (PWM_P27_CR)
#define PWM15_GET_REG_G3_CH0_CR        (PWM_P30_CR)
#define PWM15_GET_REG_G3_CH1_CR        (PWM_P31_CR)
#define PWM15_GET_REG_G3_CH2_CR        (PWM_P32_CR)
#define PWM15_GET_REG_G3_CH3_CR        (PWM_P33_CR)
#define PWM15_GET_REG_G3_CH4_CR        (PWM_P34_CR)
#define PWM15_GET_REG_G3_CH5_CR        (PWM_P35_CR)
#define PWM15_GET_REG_G3_CH6_CR        (PWM_P36_CR)
#define PWM15_GET_REG_G3_CH7_CR        (PWM_P37_CR)
#define PWM15_GET_REG_G4_CH0_CR        (PWM_P40_CR)
#define PWM15_GET_REG_G4_CH1_CR        (PWM_P41_CR)
#define PWM15_GET_REG_G4_CH2_CR        (PWM_P42_CR)
#define PWM15_GET_REG_G4_CH3_CR        (PWM_P43_CR)
#define PWM15_GET_REG_G4_CH4_CR        (PWM_P44_CR)
#define PWM15_GET_REG_G4_CH5_CR        (PWM_P45_CR)
#define PWM15_GET_REG_G4_CH6_CR        (PWM_P46_CR)
#define PWM15_GET_REG_G4_CH7_CR        (PWM_P47_CR)
#define PWM15_GET_REG_G5_CH0_CR        (PWM_P50_CR)
#define PWM15_GET_REG_G5_CH1_CR        (PWM_P51_CR)
#define PWM15_GET_REG_G5_CH2_CR        (PWM_P52_CR)
#define PWM15_GET_REG_G5_CH3_CR        (PWM_P53_CR)
#define PWM15_GET_REG_G5_CH4_CR        (PWM_P54_CR)
#define PWM15_GET_REG_G5_CH5_CR        (PWM_P55_CR)
#define PWM15_GET_REG_G5_CH6_CR        (PWM_P56_CR)
#define PWM15_GET_REG_G5_CH7_CR        (PWM_P57_CR)
#endif


#define RUNRTC      0X01
#define RTCCKS      0X02
#define SETRTC      0X01
#define EALAI       0X80
#define EDAYI       0X40
#define EHOURI      0X20
#define EMINI       0X10
#define ESECI       0X08
#define ESEC2I      0X04
#define ESEC8I      0X02
#define ESEC32I     0X01
#define ALAIF       0X80
#define DAYIF       0X40
#define HOURIF      0X20
#define MINIF       0X10
#define SECIF       0X08
#define SEC2IF      0X04
#define SEC8IF      0X02
#define SEC32IF     0X01

#define RTC_POWER_ON                do{RTCCR=1;}while(0)
#define RTC_POWER_OFF               do{RTCCR=0;}while(0)
#define RTC_SET_CLK_LSE             REG_RESET_BIT(RTCCFG,RTCCKS)
#define RTC_SET_CLK_LSI             REG_SET_BIT(RTCCFG,RTCCKS)
#define RTC_RESET                   REG_SET_BIT(RTCCFG,SETRTC)
#define RTC_ALARM_IT_ENABLE         REG_SET_BIT(RTCIEN,EALAI)
#define RTC_ALARM_IT_DISBLE         REG_RESET_BIT(RTCIEN,EALAI)
#define RTC_DAY_IT_ENABLE           REG_SET_BIT(RTCIEN,EDAYI)
#define RTC_DAY_IT_DISBLE           REG_RESET_BIT(RTCIEN,EDAYI)
#define RTC_HOUR_IT_ENABLE          REG_SET_BIT(RTCIEN,EHOURI)
#define RTC_HOUR_IT_DISBLE          REG_RESET_BIT(RTCIEN,EHOURI)
#define RTC_MIN_IT_ENABLE           REG_SET_BIT(RTCIEN,EMINI)
#define RTC_MIN_IT_DISBLE           REG_RESET_BIT(RTCIEN,EMINI)
#define RTC_SEC_IT_ENABLE           REG_SET_BIT(RTCIEN,ESECI)
#define RTC_SEC_IT_DISBLE           REG_RESET_BIT(RTCIEN,ESECI)
#define RTC_SEC2_IT_ENABLE          REG_SET_BIT(RTCIEN,ESEC2I)
#define RTC_SEC2_IT_DISBLE          REG_RESET_BIT(RTCIEN,ESEC2I)
#define RTC_SEC8_IT_ENABLE          REG_SET_BIT(RTCIEN,ESEC8I)
#define RTC_SEC8_IT_DISBLE          REG_RESET_BIT(RTCIEN,ESEC8I)
#define RTC_SEC32_IT_ENABLE         REG_SET_BIT(RTCIEN,ESEC32I)
#define RTC_SEC32_IT_DISBLE         REG_RESET_BIT(RTCIEN,ESEC32I)

#define RTC_GET_ALARM_IT_FLAG       (RTCIF & ALAIF)
#define RTC_CLS_ALARM_IT_FLAG       REG_RESET_BIT(RTCIF,ALAIF)
#define RTC_GET_DAY_IT_FLAG         (RTCIF & DAYIF)
#define RTC_CLS_DAY_IT_FLAG         REG_RESET_BIT(RTCIF,DAYIF)
#define RTC_GET_HOUR_IT_FLAG        (RTCIF & HOURIF)
#define RTC_CLS_HOUR_IT_FLAG        REG_RESET_BIT(RTCIF,HOURIF)
#define RTC_GET_MIN_IT_FLAG         (RTCIF & MINIF)
#define RTC_CLS_MIN_IT_FLAG         REG_RESET_BIT(RTCIF,MINIF)
#define RTC_GET_SEC_IT_FLAG         (RTCIF & SECIF)
#define RTC_CLS_SEC_IT_FLAG         REG_RESET_BIT(RTCIF,SECIF)
#define RTC_GET_SEC2_IT_FLAG        (RTCIF & SEC2IF)
#define RTC_CLS_SEC2_IT_FLAG        REG_RESET_BIT(RTCIF,SEC2IF)
#define RTC_GET_SEC8_IT_FLAG        (RTCIF & SEC8IF)
#define RTC_CLS_SEC8_IT_FLAG        REG_RESET_BIT(RTCIF,SEC8IF)
#define RTC_GET_SEC32_IT_FLAG       (RTCIF & SEC32IF)
#define RTC_CLS_SEC32_IT_FLAG       REG_RESET_BIT(RTCIF,SEC32IF)

#define RTC_SET_REG_CR(value)       do{RTCCR=(u8)(value);}while(0)
#define RTC_GET_REG_CR              (RTCCR)
#define RTC_SET_REG_CFG(value)      do{RTCCFG=(u8)(value);}while(0)
#define RTC_GET_REG_CFG             (RTCCFG)
#define RTC_SET_REG_IEN(value)      do{RTCIEN=(u8)(value);}while(0)
#define RTC_GET_REG_IEN             (RTCIEN)
#define RTC_SET_REG_IF(value)       do{RTCIF=(u8)(value);}while(0)
#define RTC_GET_REG_IF              (RTCIF)

#define RTC_SET_REG_ALAHOUR(value)  do{ALAHOUR=(u8)(value);}while(0)
#define RTC_GET_REG_ALAHOUR         (ALAHOUR)
#define RTC_SET_REG_ALAMIN(value)   do{ALAMIN=(u8)(value);}while(0)
#define RTC_GET_REG_ALAMIN          (ALAMIN)
#define RTC_SET_REG_ALASEC(value)   do{ALASEC=(u8)(value);}while(0)
#define RTC_GET_REG_ALASEC          (ALASEC)
#define RTC_SET_REG_ALASSEC(value)  do{ALASSEC=(u8)(value);}while(0)
#define RTC_GET_REG_ALASSEC         (ALASSEC)
#define RTC_SET_REG_INIYEAR(value)  do{INIYEAR=(u8)(value);}while(0)
#define RTC_GET_REG_INIYEAR         (INIYEAR)
#define RTC_SET_REG_INIMONTH(value) do{INIMONTH=(u8)(value);}while(0)
#define RTC_GET_REG_INIMONTH        (INIMONTH)
#define RTC_SET_REG_INIDAY(value)   do{INIDAY=(u8)(value);}while(0)
#define RTC_GET_REG_INIDAY          (INIDAY)
#define RTC_SET_REG_INIHOUR(value)  do{INIHOUR=(u8)(value);}while(0)
#define RTC_GET_REG_INIHOUR         (INIHOUR)
#define RTC_SET_REG_INIMIN(value)   do{INIMIN=(u8)(value);}while(0)
#define RTC_GET_REG_INIMIN          (INIMIN)
#define RTC_SET_REG_INISEC(value)   do{INISEC=(u8)(value);}while(0)
#define RTC_GET_REG_INISEC          (INISEC)
#define RTC_SET_REG_INISSEC(value)  do{INISSEC=(u8)(value);}while(0)
#define RTC_GET_REG_INISSEC         (INISSEC)

#define C7EN    0X80
#define C6EN    0X40
#define C5EN    0X20
#define C4EN    0X10
#define C3EN    0X08
#define C2EN    0X04
#define C1EN    0X02
#define C0EN    0X01

#define S15EN   0X80
#define S14EN   0X40
#define S13EN   0X20
#define S12EN   0X10
#define S11EN   0X08
#define S10EN   0X04
#define S9EN    0X02
#define S8EN    0X01
#define S7EN    0X80
#define S6EN    0X40
#define S5EN    0X20
#define S4EN    0X10
#define S3EN    0X08
#define S2EN    0X04
#define S1EN    0X02
#define S0EN    0X01

#define LEDON   0X80
#define LEDMODE 0X30
#define LEDDUTY 0X07

#define LED_COM0_ENABLE      REG_SET_BIT(COMEN,C0EN)
#define LED_COM0_DISABLE     REG_RESET_BIT(COMEN,C0EN)
#define LED_COM1_ENABLE      REG_SET_BIT(COMEN,C1EN)
#define LED_COM1_DISABLE     REG_RESET_BIT(COMEN,C1EN)
#define LED_COM2_ENABLE      REG_SET_BIT(COMEN,C2EN)
#define LED_COM2_DISABLE     REG_RESET_BIT(COMEN,C2EN)
#define LED_COM3_ENABLE      REG_SET_BIT(COMEN,C3EN)
#define LED_COM3_DISABLE     REG_RESET_BIT(COMEN,C3EN)
#define LED_COM4_ENABLE      REG_SET_BIT(COMEN,C4EN)
#define LED_COM4_DISABLE     REG_RESET_BIT(COMEN,C4EN)
#define LED_COM5_ENABLE      REG_SET_BIT(COMEN,C5EN)
#define LED_COM5_DISABLE     REG_RESET_BIT(COMEN,C5EN)
#define LED_COM6_ENABLE      REG_SET_BIT(COMEN,C6EN)
#define LED_COM6_DISABLE     REG_RESET_BIT(COMEN,C6EN)
#define LED_COM7_ENABLE      REG_SET_BIT(COMEN,C7EN)
#define LED_COM7_DISABLE     REG_RESET_BIT(COMEN,C7EN)

#define LED_SEG0_ENABLE      REG_SET_BIT(SEGENL,S0EN)
#define LED_SEG0_DISABLE     REG_RESET_BIT(SEGENL,S0EN)
#define LED_SEG1_ENABLE      REG_SET_BIT(SEGENL,S1EN)
#define LED_SEG1_DISABLE     REG_RESET_BIT(SEGENL,S1EN)
#define LED_SEG2_ENABLE      REG_SET_BIT(SEGENL,S2EN)
#define LED_SEG2_DISABLE     REG_RESET_BIT(SEGENL,S2EN)
#define LED_SEG3_ENABLE      REG_SET_BIT(SEGENL,S3EN)
#define LED_SEG3_DISABLE     REG_RESET_BIT(SEGENL,S3EN)
#define LED_SEG4_ENABLE      REG_SET_BIT(SEGENL,S4EN)
#define LED_SEG4_DISABLE     REG_RESET_BIT(SEGENL,S4EN)
#define LED_SEG5_ENABLE      REG_SET_BIT(SEGENL,S5EN)
#define LED_SEG5_DISABLE     REG_RESET_BIT(SEGENL,S5EN)
#define LED_SEG6_ENABLE      REG_SET_BIT(SEGENL,S6EN)
#define LED_SEG6_DISABLE     REG_RESET_BIT(SEGENL,S6EN)
#define LED_SEG7_ENABLE      REG_SET_BIT(SEGENL,S7EN)
#define LED_SEG7_DISABLE     REG_RESET_BIT(SEGENL,S7EN)

#define LED_SEG8_ENABLE      REG_SET_BIT(SEGENH,S8EN)
#define LED_SEG8_DISABLE     REG_RESET_BIT(SEGENH,S8EN)
#define LED_SEG9_ENABLE      REG_SET_BIT(SEGENH,S9EN)
#define LED_SEG9_DISABLE     REG_RESET_BIT(SEGENH,S9EN)
#define LED_SEG10_ENABLE      REG_SET_BIT(SEGENH,S10EN)
#define LED_SEG10_DISABLE     REG_RESET_BIT(SEGENH,S10EN)
#define LED_SEG11_ENABLE      REG_SET_BIT(SEGENH,S11EN)
#define LED_SEG11_DISABLE     REG_RESET_BIT(SEGENH,S11EN)
#define LED_SEG12_ENABLE      REG_SET_BIT(SEGENH,S12EN)
#define LED_SEG12_DISABLE     REG_RESET_BIT(SEGENH,S12EN)
#define LED_SEG13_ENABLE      REG_SET_BIT(SEGENH,S13EN)
#define LED_SEG13_DISABLE     REG_RESET_BIT(SEGENH,S13EN)
#define LED_SEG14_ENABLE      REG_SET_BIT(SEGENH,S14EN)
#define LED_SEG14_DISABLE     REG_RESET_BIT(SEGENH,S14EN)
#define LED_SEG15_ENABLE      REG_SET_BIT(SEGENH,S15EN)
#define LED_SEG15_DISABLE     REG_RESET_BIT(SEGENH,S15EN)

#define LED_POWER_ON          REG_SET_BIT(LEDCTRL,LEDON)
#define LED_POWER_OFF         REG_RESET_BIT(LEDCTRL,LEDON)

#define LED_SET_MODE_DC       REG_IN_MASK(LEDCTRL,LEDMODE,0x00)
#define LED_SET_MODE_DA       REG_IN_MASK(LEDCTRL,LEDMODE,0x10)
#define LED_SET_MODE_DCA      REG_IN_MASK(LEDCTRL,LEDMODE,0x20)
#define LED_SET_DUTY(value)   REG_IN_MASK(LEDCTRL,LEDDUTY,value)
#define LED_SET_CLK_DIV(value)       do{LEDCKS=(u8)(value);}while(0)

#define LED_SET_REG_COMEN(value)    do{COMEN=(u8)(value);}while(0)
#define LED_GET_REG_COMEN           (COMEN)
#define LED_SET_REG_SEGENL(value)   do{SEGENL=(u8)(value);}while(0)
#define LED_GET_REG_SEGENL          (SEGENL)
#define LED_SET_REG_SEGENH(value)   do{SEGENH=(u8)(value);}while(0)
#define LED_GET_REG_SEGENH          (SEGENH)
#define LED_SET_REG_CTRL(value)     do{LEDCTRL=(u8)(value);}while(0)
#define LED_GET_REG_CTRL            (LEDCTRL)
#define LED_SET_REG_CKS(value)      do{LEDCKS=(u8)(value);}while(0)
#define LED_GET_REG_CKS             (LEDCKS)

#define LED_SET_REG_COM0_DA_L(value)      do{COM0_DA_L=(u8)(value);}while(0)
#define LED_GET_REG_COM0_DA_L             (COM0_DA_L)
#define LED_SET_REG_COM1_DA_L(value)      do{COM1_DA_L=(u8)(value);}while(0)
#define LED_GET_REG_COM1_DA_L             (COM1_DA_L)
#define LED_SET_REG_COM2_DA_L(value)      do{COM2_DA_L=(u8)(value);}while(0)
#define LED_GET_REG_COM2_DA_L             (COM2_DA_L)
#define LED_SET_REG_COM3_DA_L(value)      do{COM3_DA_L=(u8)(value);}while(0)
#define LED_GET_REG_COM3_DA_L             (COM3_DA_L)
#define LED_SET_REG_COM4_DA_L(value)      do{COM4_DA_L=(u8)(value);}while(0)
#define LED_GET_REG_COM4_DA_L             (COM4_DA_L)
#define LED_SET_REG_COM5_DA_L(value)      do{COM5_DA_L=(u8)(value);}while(0)
#define LED_GET_REG_COM5_DA_L             (COM5_DA_L)
#define LED_SET_REG_COM6_DA_L(value)      do{COM6_DA_L=(u8)(value);}while(0)
#define LED_GET_REG_COM6_DA_L             (COM6_DA_L)
#define LED_SET_REG_COM7_DA_L(value)      do{COM7_DA_L=(u8)(value);}while(0)
#define LED_GET_REG_COM7_DA_L             (COM7_DA_L)

#define LED_SET_REG_COM0_DA_H(value)      do{COM0_DA_H=(u8)(value);}while(0)
#define LED_GET_REG_COM0_DA_H             (COM0_DA_H)
#define LED_SET_REG_COM1_DA_H(value)      do{COM1_DA_H=(u8)(value);}while(0)
#define LED_GET_REG_COM1_DA_H             (COM1_DA_H)
#define LED_SET_REG_COM2_DA_H(value)      do{COM2_DA_H=(u8)(value);}while(0)
#define LED_GET_REG_COM2_DA_H             (COM2_DA_H)
#define LED_SET_REG_COM3_DA_H(value)      do{COM3_DA_H=(u8)(value);}while(0)
#define LED_GET_REG_COM3_DA_H             (COM3_DA_H)
#define LED_SET_REG_COM4_DA_H(value)      do{COM4_DA_H=(u8)(value);}while(0)
#define LED_GET_REG_COM4_DA_H             (COM4_DA_H)
#define LED_SET_REG_COM5_DA_H(value)      do{COM5_DA_H=(u8)(value);}while(0)
#define LED_GET_REG_COM5_DA_H             (COM5_DA_H)
#define LED_SET_REG_COM6_DA_H(value)      do{COM6_DA_H=(u8)(value);}while(0)
#define LED_GET_REG_COM6_DA_H             (COM6_DA_H)
#define LED_SET_REG_COM7_DA_H(value)      do{COM7_DA_H=(u8)(value);}while(0)
#define LED_GET_REG_COM7_DA_H             (COM7_DA_H)

#define LED_SET_REG_COM0_DC_L(value)      do{COM0_DC_L=(u8)(value);}while(0)
#define LED_GET_REG_COM0_DC_L             (COM0_DC_L)
#define LED_SET_REG_COM1_DC_L(value)      do{COM1_DC_L=(u8)(value);}while(0)
#define LED_GET_REG_COM1_DC_L             (COM1_DC_L)
#define LED_SET_REG_COM2_DC_L(value)      do{COM2_DC_L=(u8)(value);}while(0)
#define LED_GET_REG_COM2_DC_L             (COM2_DC_L)
#define LED_SET_REG_COM3_DC_L(value)      do{COM3_DC_L=(u8)(value);}while(0)
#define LED_GET_REG_COM3_DC_L             (COM3_DC_L)
#define LED_SET_REG_COM4_DC_L(value)      do{COM4_DC_L=(u8)(value);}while(0)
#define LED_GET_REG_COM4_DC_L             (COM4_DC_L)
#define LED_SET_REG_COM5_DC_L(value)      do{COM5_DC_L=(u8)(value);}while(0)
#define LED_GET_REG_COM5_DC_L             (COM5_DC_L)
#define LED_SET_REG_COM6_DC_L(value)      do{COM6_DC_L=(u8)(value);}while(0)
#define LED_GET_REG_COM6_DC_L             (COM6_DC_L)
#define LED_SET_REG_COM7_DC_L(value)      do{COM7_DC_L=(u8)(value);}while(0)
#define LED_GET_REG_COM7_DC_L             (COM7_DC_L)

#define LED_SET_REG_COM0_DC_H(value)      do{COM0_DC_H=(u8)(value);}while(0)
#define LED_GET_REG_COM0_DC_H             (COM0_DC_H)
#define LED_SET_REG_COM1_DC_H(value)      do{COM1_DC_H=(u8)(value);}while(0)
#define LED_GET_REG_COM1_DC_H             (COM1_DC_H)
#define LED_SET_REG_COM2_DC_H(value)      do{COM2_DC_H=(u8)(value);}while(0)
#define LED_GET_REG_COM2_DC_H             (COM2_DC_H)
#define LED_SET_REG_COM3_DC_H(value)      do{COM3_DC_H=(u8)(value);}while(0)
#define LED_GET_REG_COM3_DC_H             (COM3_DC_H)
#define LED_SET_REG_COM4_DC_H(value)      do{COM4_DC_H=(u8)(value);}while(0)
#define LED_GET_REG_COM4_DC_H             (COM4_DC_H)
#define LED_SET_REG_COM5_DC_H(value)      do{COM5_DC_H=(u8)(value);}while(0)
#define LED_GET_REG_COM5_DC_H             (COM5_DC_H)
#define LED_SET_REG_COM6_DC_H(value)      do{COM6_DC_H=(u8)(value);}while(0)
#define LED_GET_REG_COM6_DC_H             (COM6_DC_H)
#define LED_SET_REG_COM7_DC_H(value)      do{COM7_DC_H=(u8)(value);}while(0)
#define LED_GET_REG_COM7_DC_H             (COM7_DC_H)

#define COM0EN  0x01
#define COM1EN  0x02
#define COM2EN  0x04
#define COM3EN  0x08

#define SEG0EN  0x01
#define SEG1EN  0x02
#define SEG2EN  0x04
#define SEG3EN  0x08
#define SEG4EN  0x10
#define SEG5EN  0x20
#define SEG6EN  0x40
#define SEG7EN  0x80

#define SEG8EN  0x01
#define SEG9EN  0x02
#define SEG10EN 0x04
#define SEG11EN 0x08
#define SEG12EN 0x10
#define SEG13EN 0x20
#define SEG14EN 0x40
#define SEG15EN 0x80

#define SEG16EN 0x01
#define SEG17EN 0x02
#define SEG18EN 0x04
#define SEG19EN 0x08
#define SEG20EN 0x10
#define SEG21EN 0x20
#define SEG22EN 0x40
#define SEG23EN 0x80

#define SEG24EN 0x01
#define SEG25EN 0x02
#define SEG26EN 0x04
#define SEG27EN 0x08
#define SEG28EN 0x10
#define SEG29EN 0x20
#define SEG30EN 0x40
#define SEG31EN 0x80

#define SEG32EN 0x01
#define SEG33EN 0x02
#define SEG34EN 0x04
#define SEG35EN 0x08
#define SEG36EN 0x10
#define SEG37EN 0x20
#define SEG38EN 0x40
#define SEG39EN 0x80

#define LCD_EN  0x01
#define LCD_MODE_NORMAL 0x00
#define LCD_MODE_LIGHT  0x02
#define LCD_MODE_DARK   0x04
#define LCD_MODE_BLINK  0x06

#define LCD_CLKSEL  0x80

#define SEG0PS  0x01
#define SEG1PS  0x02
#define SEG2PS  0x04
#define SEG3PS  0x08

#define LCD_POWER_ON         REG_SET_BIT(LCDCR,LCD_EN)
#define LCD_POWER_OFF        REG_RESET_BIT(LCDCR,LCD_EN)

#define LCD_SET_DISMODE_NORMAL  REG_IN_MASK(LCDCR,0x06,LCD_MODE_NORMAL)
#define LCD_SET_DISMODE_LIGHT   REG_IN_MASK(LCDCR,0x06,LCD_MODE_LIGHT)
#define LCD_SET_DISMODE_DARK    REG_IN_MASK(LCDCR,0x06,LCD_MODE_DARK)
#define LCD_SET_DISMODE_BLINK   REG_IN_MASK(LCDCR,0x06,LCD_MODE_BLINK)

#define LCD_COM0_ENABLE      REG_SET_BIT(COMON,COM0EN)
#define LCD_COM0_DISABLE     REG_RESET_BIT(COMON,COM0EN)
#define LCD_COM1_ENABLE      REG_SET_BIT(COMON,COM1EN)
#define LCD_COM1_DISABLE     REG_RESET_BIT(COMON,COM1EN)
#define LCD_COM2_ENABLE      REG_SET_BIT(COMON,COM2EN)
#define LCD_COM2_DISABLE     REG_RESET_BIT(COMON,COM2EN)
#define LCD_COM3_ENABLE      REG_SET_BIT(COMON,COM3EN)
#define LCD_COM3_DISABLE     REG_RESET_BIT(COMON,COM3EN)

#define LCD_SEG0_ENABLE      REG_SET_BIT(SEGON1,SEG0EN)
#define LCD_SEG0_DISABLE     REG_RESET_BIT(SEGON1,SEG0EN)
#define LCD_SEG1_ENABLE      REG_SET_BIT(SEGON1,SEG1EN)
#define LCD_SEG1_DISABLE     REG_RESET_BIT(SEGON1,SEG1EN)
#define LCD_SEG2_ENABLE      REG_SET_BIT(SEGON1,SEG2EN)
#define LCD_SEG2_DISABLE     REG_RESET_BIT(SEGON1,SEG2EN)
#define LCD_SEG3_ENABLE      REG_SET_BIT(SEGON1,SEG3EN)
#define LCD_SEG3_DISABLE     REG_RESET_BIT(SEGON1,SEG3EN)
#define LCD_SEG4_ENABLE      REG_SET_BIT(SEGON1,SEG4EN)
#define LCD_SEG4_DISABLE     REG_RESET_BIT(SEGON1,SEG4EN)
#define LCD_SEG5_ENABLE      REG_SET_BIT(SEGON1,SEG5EN)
#define LCD_SEG5_DISABLE     REG_RESET_BIT(SEGON1,SEG5EN)
#define LCD_SEG6_ENABLE      REG_SET_BIT(SEGON1,SEG6EN)
#define LCD_SEG6_DISABLE     REG_RESET_BIT(SEGON1,SEG6EN)
#define LCD_SEG7_ENABLE      REG_SET_BIT(SEGON1,SEG7EN)
#define LCD_SEG7_DISABLE     REG_RESET_BIT(SEGON1,SEG7EN)

#define LCD_SEG8_ENABLE      REG_SET_BIT(SEGON2,SEG8EN)
#define LCD_SEG8_DISABLE     REG_RESET_BIT(SEGON2,SEG8EN)
#define LCD_SEG9_ENABLE      REG_SET_BIT(SEGON2,SEG9EN)
#define LCD_SEG9_DISABLE     REG_RESET_BIT(SEGON2,SEG9EN)
#define LCD_SEG10_ENABLE     REG_SET_BIT(SEGON2,SEG10EN)
#define LCD_SEG10_DISABLE    REG_RESET_BIT(SEGON2,SEG10EN)
#define LCD_SEG11_ENABLE     REG_SET_BIT(SEGON2,SEG11EN)
#define LCD_SEG11_DISABLE    REG_RESET_BIT(SEGON2,SEG11EN)
#define LCD_SEG12_ENABLE     REG_SET_BIT(SEGON2,SEG12EN)
#define LCD_SEG12_DISABLE    REG_RESET_BIT(SEGON2,SEG12EN)
#define LCD_SEG13_ENABLE     REG_SET_BIT(SEGON2,SEG13EN)
#define LCD_SEG13_DISABLE    REG_RESET_BIT(SEGON2,SEG13EN)
#define LCD_SEG14_ENABLE     REG_SET_BIT(SEGON2,SEG14EN)
#define LCD_SEG14_DISABLE    REG_RESET_BIT(SEGON2,SEG14EN)
#define LCD_SEG15_ENABLE     REG_SET_BIT(SEGON2,SEG15EN)
#define LCD_SEG15_DISABLE    REG_RESET_BIT(SEGON2,SEG15EN)

#define LCD_SEG16_ENABLE     REG_SET_BIT(SEGON3,SEG16EN)
#define LCD_SEG16_DISABLE    REG_RESET_BIT(SEGON3,SEG16EN)
#define LCD_SEG17_ENABLE     REG_SET_BIT(SEGON3,SEG17EN)
#define LCD_SEG17_DISABLE    REG_RESET_BIT(SEGON3,SEG17EN)
#define LCD_SEG18_ENABLE     REG_SET_BIT(SEGON3,SEG18EN)
#define LCD_SEG18_DISABLE    REG_RESET_BIT(SEGON3,SEG18EN)
#define LCD_SEG19_ENABLE     REG_SET_BIT(SEGON3,SEG19EN)
#define LCD_SEG19_DISABLE    REG_RESET_BIT(SEGON3,SEG19EN)
#define LCD_SEG20_ENABLE     REG_SET_BIT(SEGON3,SEG20EN)
#define LCD_SEG20_DISABLE    REG_RESET_BIT(SEGON3,SEG20EN)
#define LCD_SEG21_ENABLE     REG_SET_BIT(SEGON3,SEG21EN)
#define LCD_SEG21_DISABLE    REG_RESET_BIT(SEGON3,SEG21EN)
#define LCD_SEG22_ENABLE     REG_SET_BIT(SEGON3,SEG22EN)
#define LCD_SEG22_DISABLE    REG_RESET_BIT(SEGON3,SEG22EN)
#define LCD_SEG23_ENABLE     REG_SET_BIT(SEGON3,SEG23EN)
#define LCD_SEG23_DISABLE    REG_RESET_BIT(SEGON3,SEG23EN)

#define LCD_SEG24_ENABLE     REG_SET_BIT(SEGON4,SEG24EN)
#define LCD_SEG24_DISABLE    REG_RESET_BIT(SEGON4,SEG24EN)
#define LCD_SEG25_ENABLE     REG_SET_BIT(SEGON4,SEG25EN)
#define LCD_SEG25_DISABLE    REG_RESET_BIT(SEGON4,SEG25EN)
#define LCD_SEG26_ENABLE     REG_SET_BIT(SEGON4,SEG26EN)
#define LCD_SEG26_DISABLE    REG_RESET_BIT(SEGON4,SEG26EN)
#define LCD_SEG27_ENABLE     REG_SET_BIT(SEGON4,SEG27EN)
#define LCD_SEG27_DISABLE    REG_RESET_BIT(SEGON4,SEG27EN)
#define LCD_SEG28_ENABLE     REG_SET_BIT(SEGON4,SEG28EN)
#define LCD_SEG28_DISABLE    REG_RESET_BIT(SEGON4,SEG28EN)
#define LCD_SEG29_ENABLE     REG_SET_BIT(SEGON4,SEG29EN)
#define LCD_SEG29_DISABLE    REG_RESET_BIT(SEGON4,SEG29EN)
#define LCD_SEG30_ENABLE     REG_SET_BIT(SEGON4,SEG30EN)
#define LCD_SEG30_DISABLE    REG_RESET_BIT(SEGON4,SEG30EN)
#define LCD_SEG31_ENABLE     REG_SET_BIT(SEGON4,SEG31EN)
#define LCD_SEG31_DISABLE    REG_RESET_BIT(SEGON4,SEG31EN)

#define LCD_SEG24_ENABLE     REG_SET_BIT(SEGON4,SEG24EN)
#define LCD_SEG24_DISABLE    REG_RESET_BIT(SEGON4,SEG24EN)
#define LCD_SEG25_ENABLE     REG_SET_BIT(SEGON4,SEG25EN)
#define LCD_SEG25_DISABLE    REG_RESET_BIT(SEGON4,SEG25EN)
#define LCD_SEG26_ENABLE     REG_SET_BIT(SEGON4,SEG26EN)
#define LCD_SEG26_DISABLE    REG_RESET_BIT(SEGON4,SEG26EN)
#define LCD_SEG27_ENABLE     REG_SET_BIT(SEGON4,SEG27EN)
#define LCD_SEG27_DISABLE    REG_RESET_BIT(SEGON4,SEG27EN)
#define LCD_SEG28_ENABLE     REG_SET_BIT(SEGON4,SEG28EN)
#define LCD_SEG28_DISABLE    REG_RESET_BIT(SEGON4,SEG28EN)
#define LCD_SEG29_ENABLE     REG_SET_BIT(SEGON4,SEG29EN)
#define LCD_SEG29_DISABLE    REG_RESET_BIT(SEGON4,SEG29EN)
#define LCD_SEG30_ENABLE     REG_SET_BIT(SEGON4,SEG30EN)
#define LCD_SEG30_DISABLE    REG_RESET_BIT(SEGON4,SEG30EN)
#define LCD_SEG31_ENABLE     REG_SET_BIT(SEGON4,SEG31EN)
#define LCD_SEG31_DISABLE    REG_RESET_BIT(SEGON4,SEG31EN)

#define LCD_SEG32_ENABLE     REG_SET_BIT(SEGON5,SEG32EN)
#define LCD_SEG32_DISABLE    REG_RESET_BIT(SEGON5,SEG32EN)
#define LCD_SEG33_ENABLE     REG_SET_BIT(SEGON5,SEG33EN)
#define LCD_SEG33_DISABLE    REG_RESET_BIT(SEGON5,SEG33EN)
#define LCD_SEG34_ENABLE     REG_SET_BIT(SEGON5,SEG34EN)
#define LCD_SEG34_DISABLE    REG_RESET_BIT(SEGON5,SEG34EN)
#define LCD_SEG35_ENABLE     REG_SET_BIT(SEGON5,SEG35EN)
#define LCD_SEG35_DISABLE    REG_RESET_BIT(SEGON5,SEG35EN)
#define LCD_SEG36_ENABLE     REG_SET_BIT(SEGON5,SEG36EN)
#define LCD_SEG36_DISABLE    REG_RESET_BIT(SEGON5,SEG36EN)
#define LCD_SEG37_ENABLE     REG_SET_BIT(SEGON5,SEG37EN)
#define LCD_SEG37_DISABLE    REG_RESET_BIT(SEGON5,SEG37EN)
#define LCD_SEG38_ENABLE     REG_SET_BIT(SEGON5,SEG38EN)
#define LCD_SEG38_DISABLE    REG_RESET_BIT(SEGON5,SEG38EN)
#define LCD_SEG39_ENABLE     REG_SET_BIT(SEGON5,SEG39EN)
#define LCD_SEG39_DISABLE    REG_RESET_BIT(SEGON5,SEG39EN)

#define LCD_SET_REG_CFG(value)      do{LCDCFG=(u8)(value);}while(0)
#define LCD_GET_REG_CFG             (LCDCFG)
#define LCD_SET_REG_CFG2(value)     do{LCDCFG2=(u8)(value);}while(0)
#define LCD_GET_REG_CFG2            (LCDCFG2)
#define LCD_SET_REG_DBLEN(value)    do{DBLEN=(u8)(value);}while(0)
#define LCD_GET_REG_DBLEN           (DBLEN)
#define LCD_SET_REG_COMLENL(value)  do{COMLENL=(u8)(value);}while(0)
#define LCD_GET_REG_COMLENL         (COMLENL)
#define LCD_SET_REG_COMLENM(value)  do{COMLENM=(u8)(value);}while(0)
#define LCD_GET_REG_COMLENM         (COMLENM)
#define LCD_SET_REG_COMLENH(value)  do{COMLENH=(u8)(value);}while(0)
#define LCD_GET_REG_COMLENH         (COMLENH)
#define LCD_SET_REG_BLINKRATE(value) do{BLINKRATE=(u8)(value);}while(0)
#define LCD_GET_REG_BLINKRATE       (BLINKRATE)
#define LCD_SET_REG_CR(value)       do{LCDCR=(u8)(value);}while(0)
#define LCD_GET_REG_CR              (LCDCR)

#define LCD_SET_REG_COMON(value)    do{COMON=(u8)(value);}while(0)
#define LCD_GET_REG_COMON           (COMON)

#define LCD_SET_REG_SEGON1(value)   do{SEGON1=(u8)(value);}while(0)
#define LCD_GET_REG_SEGON1          (SEGON1)
#define LCD_SET_REG_SEGON2(value)   do{SEGON2=(u8)(value);}while(0)
#define LCD_GET_REG_SEGON2          (SEGON2)
#define LCD_SET_REG_SEGON3(value)   do{SEGON3=(u8)(value);}while(0)
#define LCD_GET_REG_SEGON3          (SEGON3)
#define LCD_SET_REG_SEGON4(value)   do{SEGON4=(u8)(value);}while(0)
#define LCD_GET_REG_SEGON4          (SEGON4)
#define LCD_SET_REG_SEGON5(value)   do{SEGON5=(u8)(value);}while(0)
#define LCD_GET_REG_SEGON5          (SEGON5)

#define LCD_SET_REG_C0S0_7(value)   do{C0SEGV0=(u8)(value);}while(0)
#define LCD_GET_REG_C0S0_7          (C0SEGV0)
#define LCD_SET_REG_C0S8_15(value)  do{C0SEGV1=(u8)(value);}while(0)
#define LCD_GET_REG_C0S8_15         (C0SEGV1)
#define LCD_SET_REG_C0S16_23(value) do{C0SEGV2=(u8)(value);}while(0)
#define LCD_GET_REG_C0S16_23        (C0SEGV2)
#define LCD_SET_REG_C0S24_31(value) do{C0SEGV3=(u8)(value);}while(0)
#define LCD_GET_REG_C0S24_31        (C0SEGV3)
#define LCD_SET_REG_C0S32_39(value) do{C0SEGV4=(u8)(value);}while(0)
#define LCD_GET_REG_C0S32_39        (C0SEGV4)

#define LCD_SET_REG_C1S0_7(value)   do{C1SEGV0=(u8)(value);}while(0)
#define LCD_GET_REG_C1S0_7          (C1SEGV0)
#define LCD_SET_REG_C1S8_15(value)  do{C1SEGV1=(u8)(value);}while(0)
#define LCD_GET_REG_C1S8_15         (C1SEGV1)
#define LCD_SET_REG_C1S16_23(value) do{C1SEGV2=(u8)(value);}while(0)
#define LCD_GET_REG_C1S16_23        (C1SEGV2)
#define LCD_SET_REG_C1S24_31(value) do{C1SEGV3=(u8)(value);}while(0)
#define LCD_GET_REG_C1S24_31        (C1SEGV3)
#define LCD_SET_REG_C1S32_39(value) do{C1SEGV4=(u8)(value);}while(0)
#define LCD_GET_REG_C1S32_39        (C1SEGV4)

#define LCD_SET_REG_C2S0_7(value)   do{C2SEGV0=(u8)(value);}while(0)
#define LCD_GET_REG_C2S0_7          (C2SEGV0)
#define LCD_SET_REG_C2S8_15(value)  do{C2SEGV1=(u8)(value);}while(0)
#define LCD_GET_REG_C2S8_15         (C2SEGV1)
#define LCD_SET_REG_C2S16_23(value) do{C2SEGV2=(u8)(value);}while(0)
#define LCD_GET_REG_C2S16_23        (C2SEGV2)
#define LCD_SET_REG_C2S24_31(value) do{C2SEGV3=(u8)(value);}while(0)
#define LCD_GET_REG_C2S24_31        (C2SEGV3)
#define LCD_SET_REG_C2S32_39(value) do{C2SEGV4=(u8)(value);}while(0)
#define LCD_GET_REG_C2S32_39        (C2SEGV4)

#define LCD_SET_REG_C3S0_7(value)   do{C3SEGV0=(u8)(value);}while(0)
#define LCD_GET_REG_C3S0_7          (C3SEGV0)
#define LCD_SET_REG_C3S8_15(value)  do{C3SEGV1=(u8)(value);}while(0)
#define LCD_GET_REG_C3S8_15         (C3SEGV1)
#define LCD_SET_REG_C3S16_23(value) do{C3SEGV2=(u8)(value);}while(0)
#define LCD_GET_REG_C3S16_23        (C3SEGV2)
#define LCD_SET_REG_C3S24_31(value) do{C3SEGV3=(u8)(value);}while(0)
#define LCD_GET_REG_C3S24_31        (C3SEGV3)
#define LCD_SET_REG_C3S32_39(value) do{C3SEGV4=(u8)(value);}while(0)
#define LCD_GET_REG_C3S32_39        (C3SEGV4)
#endif





