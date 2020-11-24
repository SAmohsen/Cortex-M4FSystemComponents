#ifndef NVIC_MAP_H_
#define NVIC_MAP_H_


#include "Platform_Types.h"
#include "Std_Types.h"
#include "Compiler.h"


/*The PRIn registers (see also page 154) provide 3-bit priority fields for each interrupt. These registers
are byte accessible. Each register holds four priority fields that are assigned to interrupts as follows*/
#define INTA_MASK  0x000000E0 
#define INTB_MASK  0x0000E000
#define INTC_MASK  0x00E00000
#define INTD_MASK  0xE0000000

#define INTA_SHIFT 5 
#define INTB_SHIFT 13
#define INTC_SHIFT 21 
#define INTD_SHIFT 29 


#define ENABLE_REG_BASE ((volatile uint32 *)0xE000E100)/*EN0*/
#define DISABLE_REG_BASE ((volatile uint32 *)0xE000E180)/*DIS0*/
#define PEND_REG_BASE ((volatile uint32 *)0xE000E200)/*PEND0*/
#define UNPEND_REG_BASE ((volatile uint32 *)0xE000E280)/*UNPEND0*/
#define SWTRIG (*(volatile uint32 *)0xE000EF00)
#define PRIORITY_REG_BASE (volatile uint32 *)0xE000E400



#endif 
