/*
 * SysTick_Private.h
 *
 *  Created on: Mar 11, 2023
 *      Author: alaa
 */

#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_



#define STK_CTRL     		 *((volatile u32 *)(0xE000E010))
#define STK_LOAD     		 *((volatile u32 *)(0xE000E014))
#define STK_VAL     		 *((volatile u32 *)(0xE000E018))
#define STK_CALIB     		 *((volatile u32 *)(0xE000E01C))

#endif /* SYSTICK_PRIVATE_H_ */
