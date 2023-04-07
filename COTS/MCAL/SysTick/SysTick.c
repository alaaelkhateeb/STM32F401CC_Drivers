/*
 * SysTick.c
 *
 *  Created on: Mar 11, 2023
 *      Author: alaa
 */

/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/
#include "SysTick.h"
#include "SysTick_Private.h"

static stkcbf_t AppCbf;

STK_tenuErrorStatus STK_Init(void){
	STK_tenuErrorStatus STK_Status = STK_enuOK;
	STK_CTRL &= SysTick_EnDisMask;
	STK_CTRL |= SysTick_Disable;
	STK_CTRL &= SysTick_ClkSrcMask;
	STK_CTRL |= SysTick_ClkSrc_Selection;

	return STK_Status;
}
STK_tenuErrorStatus STK_Start(void) {
	STK_tenuErrorStatus STK_Status = STK_enuOK;
	STK_CTRL &= SysTick_IntCLRMask;
	STK_CTRL |= SysTick_EXReqON;


	STK_CTRL &= SysTick_EnDisMask;
	STK_CTRL |= SysTick_Enable;
	STK_VAL=0;
	return STK_Status;
}
STK_tenuErrorStatus STK_Stop(void) {
	STK_tenuErrorStatus STK_Status = STK_enuOK;
	STK_CTRL &= SysTick_EnDisMask;
	STK_CTRL |= SysTick_Disable;
	STK_CTRL &= SysTick_IntCLRMask;
	STK_CTRL |= SysTick_EXReqOFF;

	return STK_Status;

}
STK_tenuErrorStatus STK_SetRegisterCallBack(stkcbf_t cbf) {
	STK_tenuErrorStatus STK_Status = STK_enuOK;
	if (cbf) {
		AppCbf = cbf;
	} else {
		STK_Status = STK_NullPtr;
	}
	return STK_Status;
}
STK_tenuErrorStatus STK_SetPeriodMS(u16 Cpy_u16TickTime, u32 Cpy_u32Clock) {
	STK_tenuErrorStatus STK_Status = STK_enuOK;
	u32 Loc_u32LoadTemp = 0;


	Loc_u32LoadTemp=Cpy_u32Clock*Cpy_u16TickTime;
	Loc_u32LoadTemp/=1000;
	if (SysTick_ClkSrc_Selection==SysTick_ClkSrc_AHB_Div8) {

		Loc_u32LoadTemp/=8;
	}
	Loc_u32LoadTemp-=1;
	STK_LOAD = Loc_u32LoadTemp;
	return STK_Status;
}
STK_tenuErrorStatus STK_ReadFlag(u8* Add_u8ReturnF){
	STK_tenuErrorStatus STK_Status = STK_enuOK;
	if ((STK_CTRL) & (1 << 16)) {
		*Add_u8ReturnF = 1;
	} else {
		*Add_u8ReturnF = 0;
	}

	return STK_Status;
}

void SysTick_Handler() {
	if (AppCbf) {
		AppCbf();
	}
}



