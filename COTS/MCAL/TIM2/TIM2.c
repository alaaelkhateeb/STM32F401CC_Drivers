/*
 * TIM2.c
 *
 *  Created on: Jun 8, 2023
 *      Author: alaa
 */
#include "Std_Types.h"
#include "Bit_Math.h"
#include "TIM2_Private.h"
#include "TIM2.h"



static void (*TIM2_PtrFun[1])(void) = {NULL };
static u8 Glob_u8BusyFlag=1;

TIMx_tenuErrorStatus TIMx_enuSetCompareMatch_us(void* TIMSelection,
		u16 Cpy_u16CompareMatch) {
	TIMx_tenuErrorStatus Loc_enuStatus = TIMx_enuOK;
	u32 Loc_u32RegTemp = 0;

	/* ReSET_BIT Slave Mode Control Register */
	((TIMx_t*) TIMSelection)->SMCR = 0;
	/* ReSET_BIT Counter Mode to Edge-aligned mode & Up Direction*/
	((TIMx_t*) TIMSelection)->CR1 = 0;

	/* Initialize Counter Value to Zero */
	((TIMx_t*) TIMSelection)->CNT = 0;

	/* SET_BIT Prescaler Value to (Freq of APB1 BUS(MHz) - 1) to make tick time = 1us */
	((TIMx_t*) TIMSelection)->PSC = 7;

	/* SET_BIT Auto Reload Value to value of delay time */
	((TIMx_t*) TIMSelection)->ARR = Cpy_u16CompareMatch;

	/* Update Registers UG BIT */
	Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->EGR;
	SET_BIT(Loc_u32RegTemp, 0);
	((TIMx_t*) TIMSelection)->EGR = Loc_u32RegTemp;
	/* SET_BIT One Pulse Mode Bit to disable counter after Update Event */
	Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CR1;
	SET_BIT(Loc_u32RegTemp, 3);
	/* Enable Counter */
	SET_BIT(Loc_u32RegTemp, 0);
	((TIMx_t*) TIMSelection)->CR1 = Loc_u32RegTemp;
	return Loc_enuStatus;
}

TIMx_tenuErrorStatus TIMx_enuSetCompareMatch_ms(void* TIMSelection,
		u16 Cpy_u16CompareMatch) {
	TIMx_tenuErrorStatus Loc_enuStatus = TIMx_enuOK;
	u32 Loc_u32RegTemp = 0;

	/* ReSET_BIT Slave Mode Control Register */
	((TIMx_t*) TIMSelection)->SMCR = 0;
	/* ReSET_BIT Counter Mode to Edge-aligned mode & Up Direction*/
	((TIMx_t*) TIMSelection)->CR1 = 0;

	/* Initialize Counter Value to Zero */
	((TIMx_t*) TIMSelection)->CNT = 0;

	/* SET_BIT Prescaler Value to (Freq of APB1 BUS(MHz) - 1) to make tick time = 1us */
	((TIMx_t*) TIMSelection)->PSC = 7999;

	/* SET_BIT Auto Reload Value to value of delay time */
	((TIMx_t*) TIMSelection)->ARR = Cpy_u16CompareMatch;

	/* Update Registers UG BIT */
	Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->EGR;
	SET_BIT(Loc_u32RegTemp, 0);
	((TIMx_t*) TIMSelection)->EGR = Loc_u32RegTemp;
	/* SET_BIT One Pulse Mode Bit to disable counter after Update Event */
	Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CR1;
	SET_BIT(Loc_u32RegTemp, 3);
	/* Enable Counter */
	SET_BIT(Loc_u32RegTemp, 0);
	((TIMx_t*) TIMSelection)->CR1 = Loc_u32RegTemp;

	return Loc_enuStatus;
}

///////////not finsihed
TIMx_tenuErrorStatus TIMx_u8SetCallBack(void* TIMSelection, u8 Cpy_u8TIM2Int,
		void (*Cbf)(void)) {
	TIMx_tenuErrorStatus Loc_enuStatus = TIMx_enuOK;
	if (Cbf != NULL) {
		TIM2_PtrFun[Cpy_u8TIM2Int] = Cbf;
	} else {
		Loc_enuStatus = TIMx_enuNotOK;
	}
	return Loc_enuStatus;
}

TIMx_tenuErrorStatus TIMx_enuGenerateKHzPWM(void* TIMSelection,
		TIMx_tChannelOptions Cpy_enuChannel, u16 Cpy_u16KHzFreq,
		u8 Cpy_u8DutyCycle) {
	TIMx_tenuErrorStatus Loc_enuStatus = TIMx_enuOK;
	u32 Loc_u32RegTemp = 0;

	/* ReSET_BIT Slave Mode Control Register */
	((TIMx_t*) TIMSelection)->SMCR = 0;
	/* ReSET_BIT Counter Mode to Edge-aligned mode & Up Direction*/
	((TIMx_t*) TIMSelection)->CR1 = 0;
	/* Initialize Counter Value to Zero */
	((TIMx_t*) TIMSelection)->CNT = 0;
	if ((Cpy_u16KHzFreq != 0) && (Cpy_u8DutyCycle <= 100)) {
		switch (Cpy_enuChannel) {
		case TIMx_enu_CHANNEL1:
			/* SET_BIT Channel 1 as Output */
			Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CCMR1;
			CLR_BIT(Loc_u32RegTemp, 1);
			CLR_BIT(Loc_u32RegTemp, 0);
			/* Config Compare Mode : PWM mode 1 */
			SET_BIT(Loc_u32RegTemp, 6);
			SET_BIT(Loc_u32RegTemp, 5);
			CLR_BIT(Loc_u32RegTemp, 4);

			((TIMx_t*) TIMSelection)->CCMR1 = Loc_u32RegTemp;
			Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CCER;
			/* SET_BIT Polarity of Output Compare */
			CLR_BIT(Loc_u32RegTemp, 1);
			/* Enable Channel Output */
			SET_BIT(Loc_u32RegTemp, 0);

			((TIMx_t*) TIMSelection)->CCER = Loc_u32RegTemp;
			/* SET_BIT Value of Counter Compare (Active Period) */ //if we want accurate 100% ->CCR+1
			((TIMx_t*) TIMSelection)->CCR1 = (u16) ((u32) (Cpy_u8DutyCycle
					* ((1000) / Cpy_u16KHzFreq)) / 100);
			break;
		case TIMx_enu_CHANNEL2:
			Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CCMR1;
			/* SET_BIT Channel 2 as Output */
			CLR_BIT(Loc_u32RegTemp, 9);
			CLR_BIT(Loc_u32RegTemp, 8);
			/* Config Compare Mode : PWM mode 1 */
			SET_BIT(Loc_u32RegTemp, 14);
			SET_BIT(Loc_u32RegTemp, 13);
			CLR_BIT(Loc_u32RegTemp, 12);

			((TIMx_t*) TIMSelection)->CCMR1 = Loc_u32RegTemp;

			Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CCER;
			/* SET_BIT Polarity of Output Compare */
			CLR_BIT(Loc_u32RegTemp, 5);
			/* Enable Channel Output */
			SET_BIT(Loc_u32RegTemp, 4);
			((TIMx_t*) TIMSelection)->CCER = Loc_u32RegTemp;
			/* SET_BIT Value of Counter Compare (Active Period) */ //if we want accurate 100% ->CCR+1
			((TIMx_t*) TIMSelection)->CCR2 = (u16) ((u32) (Cpy_u8DutyCycle
					* ((1000) / Cpy_u16KHzFreq)) / 100); //if we want accurate 0% ->CCR
			break;
		case TIMx_enu_CHANNEL3:
			/* SET_BIT Channel 3 as Output */
			Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CCMR2;
			CLR_BIT(Loc_u32RegTemp, 1);
			CLR_BIT(Loc_u32RegTemp, 0);
			/* Config Compare Mode : PWM mode 1 */
			SET_BIT(Loc_u32RegTemp, 6);
			SET_BIT(Loc_u32RegTemp, 5);
			CLR_BIT(Loc_u32RegTemp, 4);

			((TIMx_t*) TIMSelection)->CCMR2 = Loc_u32RegTemp;
			Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CCER;
			/* SET_BIT Polarity of Output Compare */
			CLR_BIT(Loc_u32RegTemp, 9);
			/* Enable Channel Output */
			SET_BIT(Loc_u32RegTemp, 8);

			((TIMx_t*) TIMSelection)->CCER = Loc_u32RegTemp;
			/* SET_BIT Value of Counter Compare (Active Period) */ //if we want accurate 100% ->CCR+1
			((TIMx_t*) TIMSelection)->CCR3 = (u16) ((u32) (Cpy_u8DutyCycle
					* ((1000) / Cpy_u16KHzFreq)) / 100); //if we want accurate 0% ->CCR
			break;
		case TIMx_enu_CHANNEL4:
			Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CCMR2;
			/* SET_BIT Channel 4 as Output */
			CLR_BIT(Loc_u32RegTemp, 9);
			CLR_BIT(Loc_u32RegTemp, 8);
			/* Config Compare Mode : PWM mode 1 */
			SET_BIT(Loc_u32RegTemp, 14);
			SET_BIT(Loc_u32RegTemp, 13);
			CLR_BIT(Loc_u32RegTemp, 12);

			((TIMx_t*) TIMSelection)->CCMR2 = Loc_u32RegTemp;
			Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CCER;
			/* SET_BIT Polarity of Output Compare */
			CLR_BIT(Loc_u32RegTemp, 13);
			/* Enable Channel Output */
			SET_BIT(Loc_u32RegTemp, 12);
			((TIMx_t*) TIMSelection)->CCER = Loc_u32RegTemp;
			/* SET_BIT Value of Counter Compare (Active Period) */ //if we want accurate 100% ->CCR+1
			((TIMx_t*) TIMSelection)->CCR4 = (u16) ((u32) (Cpy_u8DutyCycle
					* ((1000) / Cpy_u16KHzFreq)) / 100); //if we want accurate 0% ->CCR
			break;
		default:
			Loc_enuStatus = TIMx_enuNotOK;
		}
		/* SET_BIT Prescaler Value to (Freq of APB1 BUS(MHz) - 1) to make tick time = 1us */
		((TIMx_t*) TIMSelection)->PSC = 7;
		/*  Auto-reload preload */
		Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CR1;
		SET_BIT(Loc_u32RegTemp, 7);
		((TIMx_t*) TIMSelection)->CR1 = Loc_u32RegTemp;
		/* Time Period (us) of PWM Signal */
		((TIMx_t*) TIMSelection)->ARR = ((1 * 1000) / (Cpy_u16KHzFreq));
		/* Update Registers UG BIT (Tip in PWM mode datasheet)*/

		Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->EGR;
		SET_BIT(Loc_u32RegTemp, 0);
		((TIMx_t*) TIMSelection)->EGR = Loc_u32RegTemp;
		/* Enable Counter */
		Loc_u32RegTemp = ((TIMx_t*) TIMSelection)->CR1;
		SET_BIT(Loc_u32RegTemp, 0);
		((TIMx_t*) TIMSelection)->CR1 = Loc_u32RegTemp;
	} else {
		Loc_enuStatus = TIMx_enuWrongValue;
	}

	return Loc_enuStatus;

}



TIMx_tenuErrorStatus TIMx_enuDelay_us(void* TIMSelection, u16 Cpy_u16DelayTime) {

	TIMx_tenuErrorStatus Loc_enuStatus = TIMx_enuOK;
	u32 Loc_u32TimeOut=0xFFFFFFFF;
	u32 Loc_u32RegTemp = 0;

	/***** COUNT UP ****/
	/* Reset Slave Mode Control Register */
	((TIMx_t*) TIMSelection)->SMCR = 0;

	/* Reset Counter Mode to Edge-aligned mode & Up Direction*/
	((TIMx_t*) TIMSelection)->CR1 = 0;
	/* Initialize Counter Value to Zero */

	((TIMx_t*) TIMSelection)->CNT = 0;
	/* Set Prescaler Value to (Freq of APB1 BUS(MHz) - 1) to make tick time = 1us */
	((TIMx_t*) TIMSelection)->PSC = 7;

	/* Set Auto Reload Value to value of delay time */
	((TIMx_t*) TIMSelection)->ARR = Cpy_u16DelayTime;



	Loc_u32RegTemp=((TIMx_t*) TIMSelection)->EGR;
	/* Update Registers UG BIT (Tip in datasheet) */
	SET_BIT(Loc_u32RegTemp, 0);
	((TIMx_t*) TIMSelection)->EGR=Loc_u32RegTemp;
	/* Set One Pulse Mode Bit to disable counter after delay time */
	Loc_u32RegTemp=((TIMx_t*) TIMSelection)->CR1;
	SET_BIT(Loc_u32RegTemp, 3);
	/* Enable Counter */
	SET_BIT(Loc_u32RegTemp, 0);
	((TIMx_t*) TIMSelection)->CR1=Loc_u32RegTemp;
	/* While Loop for delay time (until first update event) */
	while (GET_BIT(	((TIMx_t*) TIMSelection)->CR1, 0) ){
		 //Wait Until Counter Disabled
		if(Loc_u32TimeOut--<0 ){
			Loc_enuStatus=TIMx_enuTimeOut;
			break;
		}

	}


	return Loc_enuStatus;

}

TIMx_tenuErrorStatus TIMx_enuDelay_ms(void* TIMSelection, u16 Cpy_u16DelayTime){
	TIMx_tenuErrorStatus Loc_enuStatus = TIMx_enuOK;
	u32 Loc_u32TimeOut=0xFFFFFFFF;
	u32 Loc_u32RegTemp = 0;




	/***** COUNT UP ****/
	/* Reset Slave Mode Control Register */
	((TIMx_t*) TIMSelection)->SMCR = 0;

	/* Reset Counter Mode to Edge-aligned mode & Up Direction*/
	((TIMx_t*) TIMSelection)->CR1 = 0;
	/* Initialize Counter Value to Zero */

	((TIMx_t*) TIMSelection)->CNT = 0;
	/* Set Prescaler Value to (Freq of APB1 BUS(MHz) - 1) to make tick time = 1us */
	((TIMx_t*) TIMSelection)->PSC = 7;

	/* Set Auto Reload Value to value of delay time */
	((TIMx_t*) TIMSelection)->ARR = 1000;




	Loc_u32RegTemp=((TIMx_t*) TIMSelection)->EGR;
	/* Update Registers UG BIT (Tip in datasheet) */
	SET_BIT(Loc_u32RegTemp, 0);
	((TIMx_t*) TIMSelection)->EGR=Loc_u32RegTemp;
	/* Set One Pulse Mode Bit to disable counter after delay time */
	Loc_u32RegTemp=((TIMx_t*) TIMSelection)->CR1;
	SET_BIT(Loc_u32RegTemp, 3);
	((TIMx_t*) TIMSelection)->CR1=Loc_u32RegTemp;
	/* For Loop to count Delay Time (ms) */
	for(u16 Loc_u16Delayms=0;Loc_u16Delayms < Cpy_u16DelayTime;Loc_u16Delayms++){
		/* Enable Counter */
		Loc_u32RegTemp=((TIMx_t*) TIMSelection)->CR1;
		SET_BIT(Loc_u32RegTemp,0);
		((TIMx_t*) TIMSelection)->CR1=Loc_u32RegTemp;

		/* While Loop for delay time (until first update event) */
		while (GET_BIT(	((TIMx_t*) TIMSelection)->CR1, 0) ){
			 //Wait Until Counter Disabled
			if(Loc_u32TimeOut--<0 ){
				Loc_enuStatus=TIMx_enuTimeOut;
				break;
			}

		}

	}

	return Loc_enuStatus;
}



void TIM2_IRQHandler(void){
	if((Glob_u8BusyFlag!=0)&&(TIM2_PtrFun[TIM2_U8_UPDATE_EVENT]!=NULL)){
		/* Busy ISR */
		Glob_u8BusyFlag = 0;
		/* Call Function Interrupt */
		TIM2_PtrFun[TIM2_U8_UPDATE_EVENT]();
		/* Valid ISR */
		Glob_u8BusyFlag = 1;
	}
}

