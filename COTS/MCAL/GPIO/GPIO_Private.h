/*
 * GPIO_Private.h
 *
 *  Created on: Feb 17, 2023
 *      Author: alaa
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#define GPIOA		    (void*)(0x40020000)
#define GPIOB 	    	(void*)(0x40020400)
#define GPIOC		    (void*)(0x40020800)
#define GPIOD 			(void*)(0x40020C00)
#define GPIOE		    (void*)(0x40021000)
#define GPIOH		    (void*)(0x40021C00)


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





#endif /* GPIO_PRIVATE_H_ */
