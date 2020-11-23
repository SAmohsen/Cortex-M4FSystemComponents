 /******************************************************************************
 *
 * Module: cpu
 *
 * File Name: CPU.c
 *
 * Description: Working With ARM Cortex-M4 Core Registers
 *
 * Author: Sayed Mohsen
 *
 *******************************************************************************/
#include "Cpu.h"

/*Global Counter Flag To Avoid NestedGlobal Critical Sections Problems*/

STATIC uint8  g_criticalSectionsCounterFlag = 0 ;



/******************************************************************************
* Syntax          : void CPU_EnterCritical(void)
*
*
* Description     : protect shared resource to  avoid the concurrent access.
* Typically, the critical section accesses a shared resource, such as a data structure, a peripheral device
*******************************************************************************/
void CPU_EnterCritical(void)
{
    if(g_criticalSectionsCounterFlag==0)
    {
        CPU_DisableIRQ();/*Disable interrupts in order to access critical sectionS of code */
    }
    g_criticalSectionsCounterFlag++;/*Increment Counter Of Current Opened Critical Sections*/
}


/******************************************************************************
* Syntax          : void CPU_ExitCritical(void)
*
*
* Description     : Exit From Critical Section After Accessing A shared Resource
*******************************************************************************/
void CPU_ExitCritical(void)
{
    g_criticalSectionsCounterFlag--;/*Decrement Counter Of Current Opened Critical Sections*/
    if(g_criticalSectionsCounterFlag==0)
    {
        CPU_EnableIRQ() ; /* re-enable interrupts After accessin critical sectionS of code */
    }
}

/**********************************************************************************************************************
 *  END OF FILE: CPU.c
 *********************************************************************************************************************/
