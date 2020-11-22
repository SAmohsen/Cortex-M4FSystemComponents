/******************************************************************************
 *
 * Module: Nested Vectored Interrupt Controller
 *
 * File Name: NVIC.c
 *
 * Description:Core Module Facilitates low-latency exception and interrupt handling 
 *
 * Author: Sayed Mohsen
 *
 *******************************************************************************/
#include "Nvic.h"
#include "Nvic_map.h"

/********************************************************************************************************************
*                                    LOCAL MACROS CONSTANT\FUNCTION                                                 *
*********************************************************************************************************************/

/*Preprocessor Macro To Enable interrupts and show which interrupts Through ENn Reg*/
#define IRQ_SET_ENABLE(ENn, IRQ_BIT) (*(ENABLE_REG_BASE + ENn) |= (1 << IRQ_BIT))

/*Preprocessor Macro To Disable interrupts and show which interrupts Through DISn Reg*/
#define IRQ_SET_DISABLE(DISn, IRQ_BIT) (*(DISABLE_REG_BASE + DISn) |= (1 << IRQ_BIT))

/*Preprocessor Macro To force interrupts into the pending state Through PENDn Reg*/
#define IRQ_SET_PENDING(PENDn, IRQ_BIT) (*(PEND_REG_BASE + PENDn) |= (1 << IRQ_BIT))

/*Preprocessor Macro remove the pending state from interrupts through UNPENDn reg*/
#define IRQ_CLEAR_PENDING(UNPENDn, IRQ_BIT) (*(UNPEND_REG_BASE + UNPENDn) |= (1 << IRQ_BIT))

/*Preprocessor Macro To Trigger interrupts By Software*/
#define IRQ_TRIGGER(IRQ_ID) (SWTRIG = IRQ_ID)

/*Preprocessor Macro  To Acess PRIn Reg*/
#define PRI_REG(PRIn) (PRIORITY_REG_BASE + PRIn)

/**********************************************************************************************************************
 *                                                  LOCAL DATA                                                        *
 *********************************************************************************************************************/
/*global Arr To Hold Intx (INTA-INTB-INTC-INTD) Mask Values in PRI Register*/
STATIC const uint32 g_IntXPriorityMask[4] = {INTA_MASK, INTB_MASK, INTC_MASK, INTD_MASK};

/*global Arr To Hold Intx (INTA-INTB-INTC-INTD) shift Values in PRI Register*/
STATIC const uint8 g_IntXPriorityShift[4] = {INTA_SHIFT, INTB_SHIFT, INTC_SHIFT, INTD_SHIFT};

/*global Pointer to Hold NVIC Module Configurations*/
const Nvic_ConfigIRQ *g_NvicConfiguration = NULL_PTR;

/******************************************************************************
* \Syntax          : void Nvic_Init(const Nvic_ConfigType * configPtr)     
* \Description     : Function To Init NVIC Module                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : None                                 
*******************************************************************************/
void Nvic_Init(const Nvic_ConfigType *configPtr)
{
    uint32 ENn;
    uint32 irqEnOffset;
    uint32 PRIn;
    uint32 irqPriOffset;
    uint32 totalPriority;

    if (configPtr != NULL_PTR)
    {
        /*Save NVIC Configurations*/
        g_NvicConfiguration = configPtr->configured_IRQS;

        /*Loop Over Enabled Interrupt Requests*/
        for (unsigned char itr = 0; itr < NVIC_CONFIGURED_IRQS; itr = itr + 1)
        {
            /*Get Offset Of ENn Register Which Irq resident in */
            ENn = g_NvicConfiguration[itr].irqNum / PLATFORM_WORD_LENGTH;

            /*Get Offset Of irqNum in ENn Register */
            irqEnOffset = g_NvicConfiguration[itr].irqNum % PLATFORM_WORD_LENGTH;

            /*Enable Interrupt*/
            IRQ_SET_ENABLE(ENn, irqEnOffset);

            /*Get Offset Of PRIn Register Which Irq resident in */
            PRIn = g_NvicConfiguration[itr].irqNum / NVIC_PRIORITY_FIELDS_PER_REG;

            /*Get Offset Of irqNum in PRIn Register (INTA/INTB/INTC/INTD) */
            irqPriOffset = g_NvicConfiguration[itr].irqNum % NVIC_PRIORITY_FIELDS_PER_REG;

            /*Caclulate Total Priority For Irq*/
            totalPriority = g_NvicConfiguration[itr].groupPriority | g_NvicConfiguration[itr].subGroupPriority;

            /*Make Sure That Total Priority Doesnot Exceed 3 Bits*/
            totalPriority &= 0x00000007;

            /*Set Irq Priority According TO PRiority Grouping System In APINT Reg*/
            *PRI_REG(PRIn) = ((*PRI_REG(PRIn)) & ~g_IntXPriorityMask[irqPriOffset]) | (totalPriority << g_IntXPriorityShift[irqPriOffset]);
        }
    }
    else
    {
        /* Report Error */
    }
}

/******************************************************************************
* \Syntax          : void Nvic_IrqSetPending(Nvic_IrqNumberType irqNum)     
* \Description     : Force interrupts into the pending state                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): irqNum : Interrupt Request ID                                                       
* \Return value:   : None                                 
*******************************************************************************/
void Nvic_IrqSetPending(Nvic_IrqNumberType irqNum)
{
    uint32 PENDn;
    uint32 irqPendOffset;

    /*Get Offset Of PENDn Register Which Irq resident in */
    PENDn = irqNum / PLATFORM_WORD_LENGTH;

    /*Get Offset Of irqNum in PENDn Register */
    irqPendOffset = irqNum % PLATFORM_WORD_LENGTH;

    /*Force interrupts into the pending state*/
    IRQ_SET_PENDING(PENDn, irqPendOffset);
}

/******************************************************************************
* \Syntax          : void Nvic_IrqClearPending(Nvic_IrqNumberType irqNum)    
* \Description     : remove the pending state from interrupts                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): irqNum : Interrupt Request ID                                                        
* \Return value:   : None                                 
*******************************************************************************/
void Nvic_IrqClearPending(Nvic_IrqNumberType irqNum)
{
    uint32 UNPENDn;
    uint32 irqUnPendOffset;

    /*Get Offset Of UNPENDn Register Which Irq resident in */
    UNPENDn = irqNum / PLATFORM_WORD_LENGTH;

    /*Get Offset Of irqNum in UNPENDn Register */
    irqUnPendOffset = irqNum % PLATFORM_WORD_LENGTH;
   
   /* remove the pending state from interrupts through UNPENDn reg*/
    IRQ_CLEAR_PENDING(UNPENDn, irqUnPendOffset);
}
/******************************************************************************
* \Syntax          : void Nvic_IrqSetEnable(Nvic_IrqNumberType irqNum)  
* \Description     : Enable Interrupt Request                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): irqNum : Interrupt Request ID                                                        
* \Return value:   : None                                 
*******************************************************************************/
void Nvic_IrqSetEnable(Nvic_IrqNumberType irqNum)
{
    uint32 ENn;
    uint32 irqEnOffset;
    /*Get Offset Of ENn Register Which Irq resident in */
    ENn = irqNum / PLATFORM_WORD_LENGTH;

    /*Get Offset Of irqNum in ENn Register */
    irqEnOffset = irqNum % PLATFORM_WORD_LENGTH;

    /*Enable Interrupt*/
    IRQ_SET_ENABLE(ENn, irqEnOffset);
}
/******************************************************************************
* \Syntax          : void Nvic_IrqSetDisable(Nvic_IrqNumberType irqNum) 
* \Description     : Disable Interrupt Request                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): irqNum : Interrupt Request ID                                                        
* \Return value:   : None                                 
*******************************************************************************/
void Nvic_IrqSetDisable(Nvic_IrqNumberType irqNum)
{
    uint32 DISn;
    uint32 irqDisOffset;

    DISn = irqNum / PLATFORM_WORD_LENGTH;
    irqDisOffset = irqNum % PLATFORM_WORD_LENGTH;
    IRQ_SET_PENDING(DISn, irqDisOffset);
}
