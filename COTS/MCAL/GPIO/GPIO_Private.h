/*
 * GPIO_Private.h
 *
 *  Created on: Feb 17, 2023
 *      Author: alaa
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#define GPIOA_BaseAddress		    (0x40020000)
#define GPIOB_BaseAddress 	    	(0x40020400)
#define GPIOC_BaseAddress		    (0x40020800)
#define GPIOD_BaseAddress 			(0x40020C00)
#define GPIOE_BaseAddress		    (0x40021000)
#define GPIOH_BaseAddress		    (0x40021C00)

typedef struct{
	u32 MODER;			//00
	u32 OTYPER;			//04
	u32 OSPEEDR;		//08
	u32 PUPDR;			//0c
	u32 IDR;			//10
	u32 ODR;			//14
	u32 BSRR;			//18
	u32 LCKR;			//1c
	u32 AFRL;			//20
	u32 AFRH;			//24
}GPIOx_t;



GPIOx_t* const GPIOA=(GPIOx_t*)GPIOA_BaseAddress;
GPIOx_t* const GPIOB=(GPIOx_t*)GPIOB_BaseAddress;
GPIOx_t* const GPIOC=(GPIOx_t*)GPIOC_BaseAddress;
GPIOx_t* const GPIOD=(GPIOx_t*)GPIOD_BaseAddress;
GPIOx_t* const GPIOE=(GPIOx_t*)GPIOE_BaseAddress;
GPIOx_t* const GPIOH=(GPIOx_t*)GPIOH_BaseAddress;


#endif /* GPIO_PRIVATE_H_ */
