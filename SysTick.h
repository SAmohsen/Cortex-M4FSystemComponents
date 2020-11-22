/******************************************************************************
 *
 * Module: SYSTICK
 *
 * File Name: SysTick.h
 *
 * Description: Header file for SYSTick Module.
 *
 * Author: sayed mohsen
 ******************************************************************************/
#ifndef SYSTICK_H_
#define SYSTICK_H_


#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"


/*Predefined MAcro For Delay Calculations*/

/*TODO:Dont Forget To Set System Clock Before Run System Timer*/
#define SYSTEM_CLOCK 16000000UL

/**********************************************************************************************************************
 *                               GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum {
SYSTICK_NOT_INITIALIZED , 
SYSTICK_INITIALIZED,
}SysTick_ModuleStatusType; 
/*Type definition For Timer Clock Source Type */
typedef enum {
  SYSTICK_CLOCKSRC_PIOSC_DIVDED_4,
  SYSTICK_CLOCKSRC_SYSTEM_CLOCK  
}SysTick_clockSrcType;

/*SYSTICK Timer is 24 bit wide Make Sure Timer Value Does not exceed 24 bit */
#define SYSTICK_TIMER_MASK 0x00FFFFFF

/*SYSTICK Timer is 24 bit wide -> max timer Value == 2^24*/
#define SYSTICK_MAX_TIMER_VALUE 0x00FFFFFF


/**********************************************************************************************************************
 *                                        GLOBAL FUNCTION PROTOTYPES                                                *           
 *********************************************************************************************************************/
void SysTick_Init(SysTick_clockSrcType clkSrc);
void SysTick_setCallBack(void (*ptr2Fun)(void));
void SysTick_start(uint32 time_ms); 
#endif /* SYSTICK_H_ */
