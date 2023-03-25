/*
 * Sched_Cfg.c
 *
 *  Created on: Mar 18, 2023
 *      Author: alaa
 */

/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/

#include "Sched.h"
#include "Sched_Cfg.h"
extern void App2(void);
extern void App1(void);

const TaskInfo_t TaskInfo[NumberOfTasks]= {
	[0]= {
		.name="App1",
		.Periodms=1000,
		.StartDelay=0,
		.cbf=App1,
	},
	[1]= {
		.name="App2",
		.Periodms=2000,
		.StartDelay=0,
		.cbf=App2,
	},
};
