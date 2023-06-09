/*
 * TIM2.h
 *
 *  Created on: Jun 8, 2023
 *      Author: alaa
 */

#ifndef TIM2_H_
#define TIM2_H_
#include "Std_Types.h"


typedef enum {
	TIMx_enuOK = 0,
	TIMx_enuNotOK,
	TIMx_enuTimeOut,
	TIMx_enuWrongValue,
	TIMx_NullPtr

} TIMx_tenuErrorStatus;


/* Timer 2 Interrupts */
#define TIM2_U8_UPDATE_EVENT             0



typedef enum {
	TIMx_enu_CHANNEL1=1,
	TIMx_enu_CHANNEL2 ,
	TIMx_enu_CHANNEL3 ,
	TIMx_enu_CHANNEL4 ,

} TIMx_tChannelOptions;


#define TIMxOption_TIM2			TIM2
#define TIMxOption_TIM3			TIM3
#define TIMxOption_TIM4		TIM4
#define TIMxOption_TIM5		TIM5








TIMx_tenuErrorStatus TIMx_enuSetCompareMatch_us(void* TIMSelection,u16 Cpy_u16CompareMatch);

TIMx_tenuErrorStatus TIMx_enuSetCompareMatch_ms(void* TIMSelection,u16 Cpy_u16CompareMatch);

/* Initialize Channel Pin enuConfig:Alternate function output Push-pull 2MHz (GPIO) */
TIMx_tenuErrorStatus TIMx_enuGenerateKHzPWM(void* TIMSelection,TIMx_tChannelOptions Cpy_enuChannel,u16 Cpy_u16KHzFreq,u8 Cpy_u8DutyCycle);


TIMx_tenuErrorStatus TIMx_enuSetCallBack(void* TIMSelection,u8 Cpy_u8TIM2Int,void (*Cbf)(void));

TIMx_tenuErrorStatus TIMx_enuDelay_us(void* TIMSelection,u16 Cpy_u16DelayTime);


TIMx_tenuErrorStatus TIMx_enuDelay_ms(void* TIMSelection,u16 Cpy_u16DelayTime);


#endif /* TIM2_H_ */
