/******************************************************************************
 *
 * Module: System Control Block
 *
 * File Name: SCB.h
 *
 * Description:Provides system implementation information and system control, including configuration, control,
 *             and reporting of system exceptions. 
 *
 * Author: Sayed Mohsen
 *
 *******************************************************************************/
#ifndef SCB_H_
#define SCB_H_
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Compiler.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define EXCEPTION_SET_ENABLE  1U
#define EXCEPTION_SET_DISABLE 0U

#define EXCEPTION_SET_PENDING  1U 
#define EXCEPTION_CLEAR_PENDING 1U

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
    SCB_RESET,
    SCB_NMI,
    SCB_HARD_FAULT,
    SCB_MEMORY_MANAGEMENT_FAULT,
    SCB_BUS_FAULT,
    SCB_USAGE_FAULT,
    SCB_SVCALL = 11,
    SCB_DEBUG_MONITOR,
    SCB_PENDSV = 14,
    SCB_SYSTICK,
} Scb_SysExceptionType;

typedef enum {

SCB_GROUP_PRIORITY_FIELD_XXX=4,
SCB_GROUP_PRIORITY_FIELD_XXY ,
SCB_GROUP_PRIORITY_FIELD_XYY ,
SCB_GROUP_PRIORITY_FIELD_YYY ,

}SCB_GroupPriorityType ; 

typedef enum {
    SCB_LITTLE_ENDIAN,
    SCB_BIG_ENDIAN
}Scb_CpuEndianType;

/**********************************************************************************************************************
 *                                        GLOBAL FUNCTION PROTOTYPES                                                *           
 *********************************************************************************************************************/

void SCB_SysExceptionEnable(Scb_SysExceptionType exception);
void SCB_SysExceptionDisable(Scb_SysExceptionType exception);
void SCB_SysExceptionSetPending(Scb_SysExceptionType exception);
void SCB_SysExceptionClearPending(Scb_SysExceptionType exception);
uint32 SCB_GetHighestPendingException(void);
void SCB_GroupPrioritySet(SCB_GroupPriorityType grPri);
Scb_CpuEndianType SCB_GetCpuEndian(void);
void SCB_PerformCoreReset(void);
void SCB_WakeOnPending(void);
void SCB_SleepOnIsrExit(void);

#endif /* SCB_H_ */
