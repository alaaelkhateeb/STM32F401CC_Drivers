/*
 * TIM2_Private.h
 *
 *  Created on: Jun 8, 2023
 *      Author: alaa
 */

#ifndef TIM2_PRIVATE_H_
#define TIM2_PRIVATE_H_

#define TIM2	    (void*)(0x40000000)
#define TIM3	    (void*)(0x40000400)
#define TIM4	    (void*)(0x40000800)
#define TIM5		(void*)(0x40000C00)


/*
#define TIM9	    (void*)(0x40014000)
#define TIM10	    (void*)(0x40014400)
#define TIM11	    (void*)(0x40014800)
*/

typedef struct{
	u32 CR1;		//00
	u32 CR2;		//04
	u32 SMCR;	//08
	u32 DIER;		//0c
	u32 SR;	//10
	u32 EGR;	//14
	u32 CCMR1;		//18
	u32 CCMR2;		//1c
	u32 CCER;		//20
	u32 CNT;		//24
	u32 PSC;
	u32 ARR;
	u32 CCR1;
	u32 CCR2;
	u32 CCR3;
	u32 CCR4;
	u32 DCR;
	u32 DMAR;
	u32 TIM2_OR;

}TIMx_t;
#endif /* TIM2_PRIVATE_H_ */
