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

#define Tick  100
static u8 SchedFlag = 0;
//static u8 counter = 0;

Task_t Tasks[NumberOfTasks];
Sched_tenuErrorStatus Sched_Init(void) {
	 u32 Loc_u32idx = 0;
	Sched_tenuErrorStatus Loc_enuStatus = Sched_enuOK;
	STK_Stop();
	STK_Init();
	STK_SetRegisterCallBack(tick_cbf);
	STK_SetPeriodMS(Tick,16000000);
	for (Loc_u32idx = 0; Loc_u32idx < NumberOfTasks; Loc_u32idx++) {
		Tasks[Loc_u32idx].taskinfo=&TaskInfo[Loc_u32idx];
		Tasks[Loc_u32idx].RemainTime = Tasks[Loc_u32idx].taskinfo->StartDelay;
	}
	return Loc_enuStatus;

}

void Sched_Start(void) {
	//Sched_tenuErrorStatus Loc_enuStatus = Sched_enuOK;
	STK_Start();
	while (1) {
		if (SchedFlag == 1) {
			Sched();
			SchedFlag = 0;
		}
	}
//	return Loc_enuStatus;
}
static void Sched(void) {
	 u32 Loc_u32idx = 0;

	for (Loc_u32idx = 0; Loc_u32idx < NumberOfTasks; Loc_u32idx++) {

		if (Tasks[Loc_u32idx].taskinfo) {
			if (Tasks[Loc_u32idx].RemainTime == 0) {
				Tasks[Loc_u32idx].taskinfo->cbf();
				Tasks[Loc_u32idx].RemainTime = Tasks[Loc_u32idx].taskinfo->Periodms
						;
			}
				Tasks[Loc_u32idx].RemainTime -= Tick;

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
