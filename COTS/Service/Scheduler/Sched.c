/*
 * Sched.c
 *
 *  Created on: Mar 18, 2023
 *      Author: alaa
 */

/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/
#include "SysTick.h"
#include "Sched.h"
#include "Sched_Cfg.h"

#define Tick  1000
static u8 SchedFlag = 0;
static u8 counter = 0;

Task_t Tasks[NumberOfTasks];

Sched_tenuErrorStatus Sched_Init(void) {
	volatile u32 Loc_u32idx = 0;
	Sched_tenuErrorStatus Loc_enuStatus = Sched_enuOK;
	STK_Init();
	STK_SetRegisterCallBack(tick_cbf);
	STK_SetPeriodMS(Tick, 25000000UL);
	for (Loc_u32idx = 0; Loc_u32idx < NumberOfTasks; Loc_u32idx++) {
		Tasks[Loc_u32idx].RemainTime = TaskInfo[Loc_u32idx].StartDelay;
	}
	return Loc_enuStatus;

}

Sched_tenuErrorStatus Sched_Start(void) {
	Sched_tenuErrorStatus Loc_enuStatus = Sched_enuOK;
	STK_Start();
	while (1) {
		if (SchedFlag == 1) {
			Sched();
			SchedFlag = 0;
		}
	}
	return Loc_enuStatus;
}
static void Sched(void) {
	volatile u32 Loc_u32idx = 0;

	for (Loc_u32idx = 0; Loc_u32idx < NumberOfTasks; Loc_u32idx++) {

		if (TaskInfo[Loc_u32idx].cbf) {
			if (Tasks[Loc_u32idx].RemainTime == 0) {
				TaskInfo[Loc_u32idx].cbf();
				Tasks[Loc_u32idx].RemainTime = TaskInfo[Loc_u32idx].Periodms
						- SCHED_Period_ms;
			} else {
				Tasks[Loc_u32idx].RemainTime -= SCHED_Period_ms;
			}
		}
	}

	/*	volatile u32 Loc_u32idx = 0;

	 for (Loc_u32idx = 0; Loc_u32idx < NumberOfTasks; Loc_u32idx++) {
	 if ((counter % TaskInfo[Loc_u32idx].Periodms) == 0) {
	 TaskInfo[Loc_u32idx].cbf();
	 }
	 }
	 counter++;*/
}

void tick_cbf(void) {
	if (SchedFlag == 0) {
		SchedFlag = 1;
	}
}
