/*
 * NVIC_Private.h
 *
 *  Created on: Mar 3, 2023
 *      Author: alaa
 */

#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_


#define NVIC_ISER_BASE ((volatile u32 *) 0xE000E100)
#define NVIC_ICER_BASE ((volatile u32 *) 0xE000E180)
#define NVIC_ISPR_BASE ((volatile u32 *) 0xE000E200)
#define NVIC_ICPR_BASE ((volatile u32 *) 0xE000E280)
#define NVIC_IABR_BASE  ((volatile u32 *) 0xE000E300)
#define NVIC_IPR_BASE  ((volatile u32 *) 0xE000E400)
#define NVIC_STIR      ((volatile u32 *) 0xE000EF00)
#define NVIC_AIRCR     ((volatile u32 *) 0xE000ED0C)


#endif /* NVIC_PRIVATE_H_ */
