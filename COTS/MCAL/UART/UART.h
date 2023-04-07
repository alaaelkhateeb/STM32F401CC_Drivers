/*
 * UART.h
 *
 *  Created on: Mar 28, 2023
 *      Author: alaa
 */

#ifndef UART_H_
#define UART_H_

#define USART_BaudRate 9600
#define USART_F_CLK			16000000
#if USART_OverSamplingSelection==USART_OverSamplingby16
#define USART_OverSampling		16
#else
#define USART_OverSampling		8

#endif


#define  USART_EnDisableSelection    USART_Enable
#define  USART_EnDisableMask       0xFFFFDFFF
#define USART_Disable   0
#define USART_Enable      1

#define USART_WordLengthSelection 		USART_WordLen8dataBits
#define  USART_WordLengtheMask       0xFFFFEFFF
#define USART_WordLen8dataBits		0
#define USART_WordLen9dataBits  	1

#define  USART_ParitySelection    USART_ParityDisable
#define  USART_ParityMask			 0xFFFFFDFF
#define USART_ParityDisable   0
#define USART_ParityEnable      1

#define  USART_StopBitSelection      USART_OneStopBit
#define  USART_StopBitMask           0xFFFF9FFF
#define  USART_OneStopBit              0
#define  USART_HalfStopBit           1
#define  USART_2StopBit              2
#define  USART_1andHalfStopBit       3

#define USART_ClkEnDisableSelection 	USART_ClkEnable
#define USART_ClkEnDisableMask		0xFFFFDFFF
#define USART_ClkEnable			1
#define USART_ClkDisable		0



#define USART_OverSamplingSelection		USART_OverSamplingby16
#define USART_OverSamplingMask      0xFFFF7FFF
#define USART_OverSamplingby16		0
#define USART_OverSamplingby8		1

#define  USART_ClkPolaritySelection      USART_ClkSteadyLow
#define  USART_ClkPolarityMask		0XFFFF7FFF
#define  USART_ClkSteadyLow        0
#define  USART_ClkSteadyHigh         1


typedef enum {
	USART_TxStateIdle=0,
	USART_TxStateBusy
} USART_TxState;
typedef enum {
	USART_RxStateIdle=0,
	USART_RxStateBusy
} USART_RxState;
typedef enum{
	USART_StateIdle=0,
	USART_StateBusy
}USART_enuStatus;

void USART_Init(void* USARTSelection);

USART_enuStatus  USART_SendBuffer(void* USARTSelection,u8* Buffer ,u32 Size);
USART_enuStatus  USART_ReceiveBuffer(void* USARTSelection,u8* Buffer ,u32 Size);

#endif /* UART_H_ */
