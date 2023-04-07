/*
 * UART_Private.h
 *
 *  Created on: Mar 31, 2023
 *      Author: alaa
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define USART1  (void*)(0x40011000)
#define USART2  (void*)(0x40004400)
#define USART6  (void*)(0x40011400)


typedef struct {
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
} USARTx_t;

#endif /* UART_PRIVATE_H_ */
