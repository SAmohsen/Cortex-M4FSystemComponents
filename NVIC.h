/******************************************************************************
 *
 * Module: Nested Vectored Interrupt Controller
 *
 * File Name: NVIC.h
 *
 * Description:Core Module Facilitates low-latency exception and interrupt handling 
 *
 * Author: Sayed Mohsen
 *
 *******************************************************************************/

#ifndef NVIC_H_
#define NVIC_H_

#include "Platform_Types.h"
#include "Std_Types.h"
#include "Compiler.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define NVIC_CONFIGURED_IRQS 3
#define NVIC_PRIORITY_FIELDS_PER_REG 4

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*Typedef For IRQ signals From TM4C123GH6PM peripherals To Cortex-M4F Core*/
typedef enum
{
  NVIC_GPIO_PORT_A_IRQ = 0,
  NVIC_GPIO_PORT_B_IRQ,
  NVIC_GPIO_PORT_C_IRQ,
  NVIC_GPIO_PORT_D_IRQ,
  NVIC_GPIO_PORT_E_IRQ,
  NVIC_UART0_IRQ,
  NVIC_UART1_IRQ,
  NVIC_SSI0_IRQ,
  NVIC_I2C0_IRQ,
  NVIC_PWM0_FAULT_IRQ,
  NVIC_PWM0_GENERATOR_0_IRQ,
  NVIC_PWM0_GENERATOR_1_IRQ,
  NVIC_PWM0_GENERATOR_2_IRQ,
  NVIC_QEI0_IRQ,
  NVIC_ADC0_SEQUENCE0_IRQ,
  NVIC_ADC0_SEQUENCE1_IRQ,
  NVIC_ADC0_SEQUENCE2_IRQ,
  NVIC_ADC0_SEQUENCE3_IRQ,
  NVIC_WATCHDOG_TIMERS_0_AND_1,
  NVIC_16_32_TIMER_0A_IRQ,
  NVIC_16_32_TIMER_0B_IRQ,
  NVIC_16_32_TIMER_1A_IRQ,
  NVIC_16_32_TIMER_1B_IRQ,
  NVIC_16_32_TIMER_2A_IRQ,
  NVIC_16_32_TIMER_2B_IRQ,
  NVIC_ANALOG_COMPARATOR0_IRQ,
  NVIC_ANALOG_COMPARATOR1_IRQ,
  /*Reserved*/
  NVIC_SYSTEM_CONTROL_IRQ = 28,
  NVIC_FLASH_MEMORY_CONTROL_AND_EEPROM_CONTROL_IRQ,
  NVIC_GPIO_PORT_F_IRQ,
  NVIC_UART2_IRQ = 33,
  NVIC_SSI1_IRQ,
  NVIC_TIMER_3A_IRQ,
  NVIC_TIMER_3B_IRQ,
  NVIC_I2C1_IRQ,
  NVIC_QEI1_IRQ,
  NVIC_CAN0_IRQ,
  NVIC_CAN1_IRQ,
  /*Reserved*/
  NVIC_HIBERNATION_MODULE_IRQ = 43,
  NVIC_USB_IRQ,
  NVIC_PWM_GENERATOR3_IRQ,
  NVIC_MDMA_SOFTWARE_IRQ,
  NVIC_MDMA_ERROR_IRQ,
  NVIC_ADC1_SEQUENCE0_IRQ,
  NVIC_ADC1_SEQUENCE1_IRQ,
  NVIC_ADC1_SEQUENCE2_IRQ,
  NVIC_ADC1_SEQUENCE3_IRQ,
  NVIC_SSI2_IRQ = 57,
  NVIC_SSI3_IRQ,
  NVIC_UART3_IRQ,
  NVIC_UART4_IRQ,
  NVIC_UART5_IRQ,
  NVIC_UART6_IRQ,
  NVIC_UART7_IRQ,
  NVIC_I2C2_IRQ = 68,
  NVIC_I2C3_IRQ,
  NVIC_16_32_TIMER_4A_IRQ,
  NVIC_16_32_TIMER_4B_IRQ,
  NVIC_16_32_TIMER_5A_IRQ = 92,
  NVIC_16_32_TIMER_5B_IRQ,
  NVIC_32_64_TIMER_0A_IRQ,
  NVIC_32_64_TIMER_0B_IRQ,
  NVIC_32_64_TIMER_1A_IRQ,
  NVIC_32_64_TIMER_1B_IRQ,
  NVIC_32_64_TIMER_2A_IRQ,
  NVIC_32_64_TIMER_2B_IRQ,
  NVIC_32_64_TIMER_3A_IRQ,
  NVIC_32_64_TIMER_3B_IRQ,
  NVIC_32_64_TIMER_4A_IRQ,
  NVIC_32_64_TIMER_4B_IRQ,
  NVIC_32_64_TIMER_5A_IRQ,
  NVIC_32_64_TIMER_5B_IRQ,
  NVIC_32_64_SYSTEM_EXCEPTION_IRQ,
  /*reserved*/
  NVIC_PWM1_GENERATOR0_IRQ = 134,
  NVIC_PWM1_GENERATOR1_IRQ,
  NVIC_PWM1_GENERATOR2_IRQ,
  NVIC_PWM1_GENERATOR3_IRQ,
  NVIC_PWM1_FAULT_IRQ
} Nvic_IrqNumberType;

/*Typdef For IRQ Group Priority According To Sys_Grouping_select in APIN Reg */
typedef uint8 Nvic_GroupPriorityType;

/*Typdef For IRQ subGroup Priority According To Sys_Grouping_select in APIN Reg */
typedef uint8 Nvic_SubGroupPriorityType;

/*Typdef For Configuring an IRQ*/
typedef struct
{
  Nvic_IrqNumberType irqNum;
  Nvic_GroupPriorityType groupPriority;
  Nvic_SubGroupPriorityType subGroupPriority;
} Nvic_ConfigIRQ;

/*Typdef For NVIC Module Configurations*/
typedef struct
{
  Nvic_ConfigIRQ configured_IRQS[NVIC_CONFIGURED_IRQS];
} Nvic_ConfigType;

/**********************************************************************************************************************
 *                                        GLOBAL FUNCTION PROTOTYPES                                                *           
 *********************************************************************************************************************/
void Nvic_Init(const Nvic_ConfigType *configPtr);
void Nvic_IrqSetPending(Nvic_IrqNumberType irqNum);
void Nvic_IrqClearPending(Nvic_IrqNumberType irqNum);
void Nvic_IrqSetEnable(Nvic_IrqNumberType irqNum);
void Nvic_IrqSetDisable(Nvic_IrqNumberType irqNum);
#endif /* NVIC_H_ */
