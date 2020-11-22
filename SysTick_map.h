
#ifndef SYSTICK_MAP_H_
#define SYSTICK_MAP_H_

#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"

typedef struct
{
    volatile uint32 STCTRL ;
    volatile uint32 STRELOAD ;
    volatile uint32 STCURRENT ;
}SysTick_Typedef;

#define SysTick ((SysTick_Typedef *)0xE000E010)/*Pointer To First SYSTICK Register (STCRL)*/

/*  STCTRL Register Pins */

/*
 * Enables SysTick to operate in a multi-shot way. That is, the
 * counter loads the RELOAD value and begins counting down. On reaching 0,
 */
#define SYSTICK_ENABLE 0

/*
 * An interrupt is generated to the NVIC when SysTick counts to 0.
 */
#define SYSTICK_INTEN  1

/*
 * Without activating the phase-lock-loop (PLL), TM4C123 LaunchPad will run at 16 MHz, meaning the SysTick counter decrements every 62.5 NANAO seconds.
 * we will activate the PLL to run the MCU at 80 MHz, so the SysTick counter decrements every 12.5 NaNO seconds
 */
#define SYSTICK_CLKSRC 2
/*
 * the COUNT bit is set and an interrupt is generated if enabled by INTEN. The counter then loads the
 * RELOAD value again and begins counting.
 */
#define SYSTICK_COUNTFLAG 16
#endif 
