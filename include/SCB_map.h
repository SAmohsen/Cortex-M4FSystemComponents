#ifndef SCB_MAP_H_
#define SCB_MAP_H_
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Compiler.h"


typedef struct
{
    uint32 MEMA : 1;
    uint32 BUSA : 1;
    uint32 : 1;
    uint32 USGA : 1;
    uint32 : 3;
    uint32 SVCA : 1;
    uint32 MON : 1;
    uint32 : 1;
    uint32 PNDSV : 1;
    uint32 TICK : 1;
    uint32 USAGEP : 1;
    uint32 MEMP : 1;
    uint32 BUSP : 1;
    uint32 SVC : 1;
    uint32 MEM : 1;
    uint32 BUS : 1;
    uint32 USAGE : 1;
    uint32 :13;
} SYSHNDCTRL_Bits;

typedef union
{

    SYSHNDCTRL_Bits Bits;
    uint32 Reg;
} SYSHNDCTRL_Tag;

typedef struct
{
    uint32 VECACT : 8;
    uint32 : 3;
    uint32 RETBASE : 1;
    uint32 VECPEND : 8;
    uint32 : 2;
    uint32 ISRPEND : 1;
    uint32 ISRPRE : 1;
    uint32 : 1;
    uint32 PENDSTCLR : 1;
    uint32 PENDSTSET : 1;
    uint32 UNPENDSV : 1;
    uint32 PENDSV : 1;
    uint32 : 2;
    uint32 NMISET : 1;

} INTCTRL_BITS;

typedef union
{

    INTCTRL_BITS Bits;
    uint32 Reg;
} INTCTRL_Tag;
#define INTCTRL (*(volatile INTCTRL_Tag *)0xE000ED04)

#define SYSHNDCTRL (*((volatile SYSHNDCTRL_Tag *)0xE000ED24))
#define SYSTICK_CTRL_R (*((volatile unsigned long *)0xE000E010))
/*
 * An interrupt is generated to the NVIC when SysTick counts to 0.
 */
#define SYSTICK_INTEN 1
#define ENDIANESS 15 
#define SYSCTRL  (*((volatile unsigned long *)0xE000ED10))
#define SEVONPEND 4 
#define SLEEPEXIT 1 

#define VTABLE (*(volatile uint32 *)0xE000ED08)
#define APINT (*(volatile uint32 *)0xE000ED0C)

#define NVIC_APINT_VECTKEY_M 0xFFFF0000 // Register Key
#define APINT_VECTKEY 0x05FA            // Vector key

#define SYSRESREQ 2


#endif
