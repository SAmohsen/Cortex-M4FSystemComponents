 /******************************************************************************
 *
 * Module: cpu
 *
 * File Name: CPU.h
 *
 * Description:Wrapper Macros  for the Cortex-M4 instructions.
 *
 * Author: Sayed Mohsen
 *
 *******************************************************************************/
#ifndef CPU_H_
#define CPU_H_

#include "Platform_Types.h"
#include "Std_Types.h"
#include "Compiler.h"



/**********************************************************************************************************************
 *                                          GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/*Change processor state, enable -interrupts...*/
#define CPU_EnableIRQ() ASM("cpsie i")

/*Change processor state, Disable -interrupts...*/
/*disable all exceptions except NMI and Hard-Fault.*/
#define CPU_DisableIRQ() ASM("cpsid i")

/*Change processor state, Enable -interrupts ...*/
#define CPU_EnableFIQ()  ASM("cpsie f")

/*Change processor state, Disable -interrupts...*/
/*Only the NMI exception handler can be executed when FAULTMASK is set.*/
#define CPU_DisableFIQ() ASM("cpsid f")

/*Enter Sleep Mode And Wait For An Interrupt Request To WakeUp*/
#define CPU_WaitForInterrupt()  ASM("WFI");

/*Enter Sleep Mode And Wait For An Event,interrupt To Wake Up*/
#define CPU_WaitForEvent()  ASM("WFE");

/*SuperVisor Call Exception Used To Make Thread Mode Access Privilege Software*/
#define CPU_SwitchToPrivileged()   ASM(" SVC 2");

/**********************************************************************************************************************
 *                                         GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void CPU_EnterCritical(void);
void CPU_ExitCritical(void) ;

#endif /* CPU_H_ */
