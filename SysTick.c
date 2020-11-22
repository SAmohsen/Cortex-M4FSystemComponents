/******************************************************************************
 *
 * Module: SYSTICK
 *
 * File Name: SysTick.c
 *
 * Description: Source file for SYSTick Module.
 *
 * Author: sayed mohsen
 *
 * TODO : RunTime Analysis For System Timer
 ******************************************************************************/

#include "SysTick.h"
#include "SysTick_map.h"

void (*g_SysTick_Call_Back_Ptr)(void) = NULL_PTR;

STATIC SysTick_ModuleStatusType sysTick_status = SYSTICK_NOT_INITIALIZED;

/*
*Interrupt Service Routine For SysTick Exceptions
* Dont Forget To Activate Systick Exceptions From SCB Module
*/
void SysTick_Handler(void)
{

    /* Check if the Systick_setCallBack is already called */
    if (g_SysTick_Call_Back_Ptr != NULL_PTR)
    {
        (*g_SysTick_Call_Back_Ptr)(); /*call-back Function In Upper SW Layer*/
    }
    /*Clear Count Flag  By Writing Any Value In Current Register*/
    SysTick->STCURRENT = FALSE;
}

void SysTick_Init(SysTick_clockSrcType clkSrc)
{
    /*Disable SysTick Timer During Setup*/
    SysTick->STCTRL &= ~(1 << SYSTICK_ENABLE);

    /*Set ClockSource For System Timer*/
    SysTick->STCTRL = (SysTick->STCTRL & ~(1 << SYSTICK_CLKSRC)) | (clkSrc << SYSTICK_CLKSRC);

    /*
     * SysTick can be configured as a multi-shot timer, repeated over and over, firing every N+1 clock
     * pulses, where N is any value from 1 to SYSTICK_MAX_TIMER_VALUE.
     */
    SysTick->STRELOAD = SYSTICK_MAX_TIMER_VALUE; /* Reload SYSTICK with MAx Timer Value */

    /*Clear Current Register By Writing Any Value In It*/
    SysTick->STCURRENT = FALSE;

    /*Module Initlization Complete*/
    sysTick_status = SYSTICK_INITIALIZED;
}

void SysTick_setCallBack(void (*ptr2Fun)(void))
{
    g_SysTick_Call_Back_Ptr = ptr2Fun;
}

void SysTick_start(uint32 time_ms)
{
    /*
     * timer Frequency  = SYSTEM_CLOCK
    * Timer Resolution  = 1 / (Timer Frequency) = 1/SYSTEM_CLOCK -> Time Required To Count One Tick
    * Time Required = Resolution * Counts
    * time_ms / 1000  =(1/SYSTEM_CLOCK) * counts
    * counts = (SYSTEM_CLOCK * time_ms)/1000 ; 
    */
    if (sysTick_status == SYSTICK_INITIALIZED)
    {
        uint32 steps = (time_ms * SYSTEM_CLOCK) / 1000UL;

        /* Reload SYSTICK with steps Required To Count One Tick*/
        SysTick->STRELOAD = (steps & SYSTICK_TIMER_MASK) - 1; /*a tick IRQ genereted After N+1 Steps*/

        /*Enable SysTick Timer After Setup*/
        SysTick->STCTRL |= (1 << SYSTICK_ENABLE);
    }
    else
    {
        /*report Error*/
    }
}
