/*
 * SysTick.h
 *
 *  Created on: Mar 11, 2023
 *      Author: alaa
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

typedef void (*stkcbf_t)(void);

#define SysTick_IntCLRMask		0xFFFFFFF8
#define SysTick_EnDisMask  		0xFFFFFFFE
#define SysTick_ClkSrcMask      0xFFFFFFFB

#define SysTick_Enable			0x00000001
#define SysTick_Disable			0x00000000

#define SysTick_EXReqSelection	SysTick_EXReqON
#define SysTick_EXReqON			0x00000002
#define SysTick_EXReqOFF		    0x00000000

#define SysTick_ClkSrc_Selection		SysTick_ClkSrc_AHB_Div8
#define SysTick_ClkSrc_AHB_Div8			0x00000000
#define SysTick_ClkSrc_AHB				0x00000004

typedef enum {
	STK_enuOK = 0, STKenuNotOK, STK_enuTimeOut, STK_enuWrongValue, STK_NullPtr

} STK_tenuErrorStatus;
STK_tenuErrorStatus STK_Init(void);
STK_tenuErrorStatus STK_Start(void);
STK_tenuErrorStatus STK_Stop(void);
STK_tenuErrorStatus STK_SetRegisterCallBack(stkcbf_t cbf);
STK_tenuErrorStatus STK_SetPeriodMS(u16 Cpy_u16TickTime, u32 Cpy_u32Clock);

STK_tenuErrorStatus STK_ReadFlag(u8* Add_u8ReturnF);
#endif /* SYSTICK_H_ */
