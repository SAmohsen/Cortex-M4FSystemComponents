 /******************************************************************************
 *
 * Module: Common - Compiler Abstraction
 *
 * File Name: Compiler.h
 *
 * Description: Abstraction of compiler specific keywords.
 *
 * Author: Sayed Mohsen
 *
 *******************************************************************************/

#ifndef COMPILER_H_
#define COMPILER_H_



/* This is used to define the void pointer to zero definition */
#define NULL_PTR          ((void *)0)

/* This is used to define the abstraction of compiler keyword inline */
#define INLINE            inline

/* This is used to define the abstraction of compiler keyword static */
#define STATIC            static

/* This is used to define the abstraction of compiler inline Assembly  */
#define ASM  __asm

#endif /* COMPILER_H_ */
