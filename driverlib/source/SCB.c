/******************************************************************************
 *
 * Module: System Control Block
 *
 * File Name: SCB.c
 *
 * Description:Provides system implementation information and system control, including configuration, control,
 *             and reporting of system exceptions. 
 *
 * Author: Sayed Mohsen
 *
 *******************************************************************************/
#include "SCB.h"
#include "SCB_map.h"


/******************************************************************************
* \Syntax          :void SVC_Handler(void)
* \Description     : SuperVisor Call Exception Used To Make Thread Mode Access Privilege Software
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                        
* \Return value:   : None                                 
*******************************************************************************/
void SVC_Handler(void){
	
/*
 *ARM Compiler toolchain v5.02 for µVision
 */
	uint32 privilegedModeRegMask = 0xFFFFFFFE; 
	uint32  controlReg ; 
  ASM("MRS controlReg ,CONTROL") ; 
	ASM("AND controlReg, privilegedModeRegMask ") ; 
  ASM("MSR CONTROL , controlReg") ; 
	
}

/******************************************************************************
* \Syntax          :void SCB_SysExceptionEnable(Scb_SysExceptionType exception) 
* \Description     : Enable EXception                               
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): exception : exception Request ID                                                        
* \Return value:   : None                                 
*******************************************************************************/

void SCB_SysExceptionEnable(Scb_SysExceptionType exception)
{
    if (exception == SCB_USAGE_FAULT)
    {
        SYSHNDCTRL.Bits.USAGE = EXCEPTION_SET_ENABLE;
    }
    else if (exception == SCB_BUS_FAULT)
    {
        SYSHNDCTRL.Bits.BUS = EXCEPTION_SET_ENABLE;
    }
    else if (exception == SCB_MEMORY_MANAGEMENT_FAULT)
    {
        SYSHNDCTRL.Bits.MEM = EXCEPTION_SET_ENABLE;
    }
    else if (exception == SCB_SYSTICK)
    {
        SYSTICK_CTRL_R |= (1 << SYSTICK_INTEN);
    }
}
/******************************************************************************
* \Syntax          : void SCB_SysExceptionDisable(Scb_SysExceptionType exception)
* \Description     : Disable exception Request                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): exception : exception Request ID                                                        
* \Return value:   : None                                 
*******************************************************************************/
void SCB_SysExceptionDisable(Scb_SysExceptionType exception)
{
    if (exception == SCB_USAGE_FAULT)
    {
        SYSHNDCTRL.Bits.USAGE = EXCEPTION_SET_DISABLE;
    }
    else if (exception == SCB_BUS_FAULT)
    {
        SYSHNDCTRL.Bits.BUS = EXCEPTION_SET_DISABLE;
    }
    else if (exception == SCB_MEMORY_MANAGEMENT_FAULT)
    {
        SYSHNDCTRL.Bits.MEM = EXCEPTION_SET_DISABLE;
    }
    else if (exception == SCB_SYSTICK)
    {
        SYSTICK_CTRL_R &= ~(1 << SYSTICK_INTEN);
    }
}

/******************************************************************************
* \Syntax          : void SCB_SysExceptionSetPending(Scb_SysExceptionType exception)    
* \Description     : Force System Exception into the pending state                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): exception : exception ID                                                       
* \Return value:   : None                                 
*******************************************************************************/

void SCB_SysExceptionSetPending(Scb_SysExceptionType exception)
{
    if (exception == SCB_NMI)
    {
        INTCTRL.Bits.NMISET = EXCEPTION_SET_PENDING;
    }
    else if (exception == SCB_PENDSV)
    {
        INTCTRL.Bits.PENDSV = EXCEPTION_SET_PENDING;
    }
    else if (exception == SCB_SYSTICK)
    {
        INTCTRL.Bits.PENDSTSET = EXCEPTION_SET_PENDING;
    }
}

/******************************************************************************
* \Syntax          : void SCB_SysExceptionClearPending(Scb_SysExceptionType exception)    
* \Description     : remove the pending state from Exception                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): exception : exception ID                                                        
* \Return value:   : None                                 
*******************************************************************************/

void SCB_SysExceptionClearPending(Scb_SysExceptionType exception)
{
    if (exception == SCB_PENDSV)
    {
        INTCTRL.Bits.UNPENDSV = EXCEPTION_CLEAR_PENDING;
    }
    else if (exception == SCB_SYSTICK)
    {
        INTCTRL.Bits.PENDSTCLR = EXCEPTION_CLEAR_PENDING;
    }
}

/******************************************************************************
* \Syntax          : uint32 SCB_GetHighestPendingException(void)  
* \Description     : Get Highest Pending Exception ID                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out):  NONE                                                      
* \Return value:   :  exception ID                                 
*******************************************************************************/

uint32 SCB_GetHighestPendingException(void)
{
    return INTCTRL.Bits.VECPEND;
}
void SCB_GroupPrioritySet(SCB_GroupPriorityType grPri)
{
    APINT = (APINT_VECTKEY << 16) | (grPri << 8);
}


Scb_CpuEndianType SCB_GetCpuEndian(void)
{
    Scb_CpuEndianType endian = (APINT & (1 << ENDIANESS)) ? SCB_BIG_ENDIAN : SCB_LITTLE_ENDIAN;
    return endian;
}
void SCB_PerformCoreReset(void)
{
    APINT = (APINT_VECTKEY << 16) | (1 << SYSRESREQ);
}

void SCB_WakeOnPending(void)
{
    SYSCTRL |= (1 << SEVONPEND);
}
void SCB_SleepOnIsrExit(void)
{
    SYSCTRL |= (1 << SLEEPEXIT);
}
