/*
 * UART.c
 *
 *  Created on: Mar 28, 2023
 *      Author: alaa
 */

/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/
#include "UART_Private.h"
#include "UART.h"

static void (*cbf)(void) = NULL;

u8 DataBuffer[1024];
u8* TxBuffer;
u32 TxSize;
u32 TxIdx;
u8 TxState = USART_TxStateIdle;

u8* RxBuffer;
u32 RxSize;
u32 RxIdx;
u8 RxState = USART_RxStateIdle;

/*ENABLE INT IN  CR1*/

void USART_Init(void* USARTSelection) {
	u32 Loc_u32Temp = 0, Loc_u32Mantissa, Loc_u32Fraction;
	((USARTx_t*) USARTSelection)->CR1 &= USART_EnDisableMask;
	((USARTx_t*) USARTSelection)->CR1 |= (USART_EnDisableSelection << 13);

	((USARTx_t*) USARTSelection)->CR1 &= USART_WordLengtheMask;
	((USARTx_t*) USARTSelection)->CR1 |= (USART_WordLengthSelection << 12);

	((USARTx_t*) USARTSelection)->CR1 &= USART_ParityMask;
	((USARTx_t*) USARTSelection)->CR1 |= (USART_ParitySelection << 9);

	((USARTx_t*) USARTSelection)->CR1 &= USART_OverSamplingMask;
	((USARTx_t*) USARTSelection)->CR1 |= (USART_OverSamplingSelection << 15);

	((USARTx_t*) USARTSelection)->CR2 &= USART_StopBitMask;
	((USARTx_t*) USARTSelection)->CR2 |= (USART_StopBitSelection << 12);

	((USARTx_t*) USARTSelection)->CR2 &= USART_ClkEnDisableMask;
	((USARTx_t*) USARTSelection)->CR2 |= (USART_ClkEnDisableSelection << 11);

	((USARTx_t*) USARTSelection)->CR2 &= USART_ClkPolarityMask;
	((USARTx_t*) USARTSelection)->CR2 |= (USART_ClkPolaritySelection << 10);

	Loc_u32Temp = ((u64) USART_F_CLK * 1000)
			/ (USART_BaudRate * (8 * (2 - USART_OverSampling)));
	Loc_u32Fraction = (Loc_u32Temp % 1000) * (8 * (2 - USART_OverSampling));
	Loc_u32Fraction = Loc_u32Fraction / 1000;
	if (Loc_u32Fraction > 0xF) {
		Loc_u32Mantissa += (Loc_u32Fraction & 0xF0);
	}
	Loc_u32Mantissa = Loc_u32Temp / 1000;

	((USARTx_t*) USARTSelection)->BRR =(Loc_u32Mantissa<<4)|(Loc_u32Fraction&0x0F);
	/*tx int enable*/
	((USARTx_t*) USARTSelection)->CR1 |= (1 << 7);
	/*TX Complete int enable*/
	((USARTx_t*) USARTSelection)->CR1 |= (1 << 6);

	/*RX  int enable*/
	((USARTx_t*) USARTSelection)->CR1 |= (1 << 5);

	/*TX  enable*/
	((USARTx_t*) USARTSelection)->CR1 |= (1 << 3);
	/*RX enable*/
	((USARTx_t*) USARTSelection)->CR1 |= (1 << 2);

}

USART_enuStatus USART_SendBuffer(void* USARTSelection, u8* Buffer, u32 Size) {
	USART_enuStatus Loc_Res = USART_StateBusy;
	if (TxState == USART_TxStateIdle) {
		TxBuffer = Buffer;
		TxSize = Size;
		TxIdx = 0;
		TxState = USART_TxStateBusy;
		((USARTx_t*) USARTSelection)->DR = TxBuffer[TxIdx];
		TxIdx++;
		Loc_Res = USART_StateIdle;
	}

	return Loc_Res;
}
USART_enuStatus USART_ReceiveBuffer(void* USARTSelection, u8* Buffer, u32 Size) {
	USART_enuStatus Loc_Res = USART_StateBusy;
	if (RxState == USART_RxStateIdle) {
		RxBuffer = Buffer;
		RxSize = Size;
		RxIdx = 0;

		/*MISSING ARRANGEMENTS*/
		RxState = USART_RxStateBusy;

		Loc_Res = USART_StateIdle;
	}

	return Loc_Res;
}

void USART1_IRQHandler(void) {
	/*CHECK TX COMPLETE */
	if (((USARTx_t*) USART1 )->SR & (1 << 6)) {
		if (TxIdx < TxSize) {
			((USARTx_t*) USART1 )->DR = TxBuffer[TxIdx];
			TxIdx++;

		} else {
			TxState = USART_TxStateIdle;
			cbf();
		}
	}
	/*RX handling*/
	if ((((USARTx_t*) USART1 )->SR & (1 << 6))
			&& RxState == USART_RxStateBusy) {

		RxBuffer[RxIdx] = ((USARTx_t*) USART1 )->DR;
		RxIdx++;
		if (RxIdx == RxSize) {
			RxState = USART_RxStateIdle;
			cbf();
		}

	}
}
void USART2_IRQHandler(void) {
	/*CHECK TX COMPLETE */
	if (((USARTx_t*) USART2 )->SR & (1 << 6)) {
		if (TxIdx < TxSize) {
			((USARTx_t*) USART2 )->DR = TxBuffer[TxIdx];
			TxIdx++;

		} else {
			TxState = USART_TxStateIdle;
			cbf();
		}
	}
	/*RX handling*/
	if ((((USARTx_t*) USART2 )->SR & (1 << 6))
			&& RxState == USART_RxStateBusy) {

		RxBuffer[RxIdx] = ((USARTx_t*) USART2 )->DR;
		RxIdx++;
		if (RxIdx == RxSize) {
			RxState = USART_RxStateIdle;
			cbf();
		}

	}
}

void USART6_IRQHandler(void) {
	/*CHECK TX COMPLETE */
	if (((USARTx_t*) USART6 )->SR & (1 << 6)) {
		if (TxIdx < TxSize) {
			((USARTx_t*) USART6 )->DR = TxBuffer[TxIdx];
			TxIdx++;

		} else {
			TxState = USART_TxStateIdle;
			cbf();
		}
	}
	/*RX handling*/
	if ((((USARTx_t*) USART6 )->SR & (1 << 6))
			&& RxState == USART_RxStateBusy) {

		RxBuffer[RxIdx] = ((USARTx_t*) USART6 )->DR;
		RxIdx++;
		if (RxIdx == RxSize) {
			RxState = USART_RxStateIdle;
			cbf();
		}

	}
}
