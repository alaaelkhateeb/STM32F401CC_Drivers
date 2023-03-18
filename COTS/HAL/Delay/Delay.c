/*
 * Delay.c
 *
 *  Created on: Mar 15, 2023
 *      Author: alaa
 */
/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/
#include "SysTick.h"
#include "Delay.h"

void delay_ms(u32 cpy_u32Time) {
	u8 cpy_u8Temp = 0;
	STK_Init();
	STK_Stop();
	STK_SetPeriodMS(cpy_u32Time, CLkSystem);
	STK_Start();
	while (1) {
		STK_ReadFlag(&cpy_u8Temp);
		if (cpy_u8Temp == 1) {
			break;
		}
	}
}
