/*
 * Sched.h
 *
 *  Created on: Mar 18, 2023
 *      Author: alaa
 */

#ifndef SCHED_H_
#define SCHED_H_


#define SCHED_Period_ms		1
typedef void (*RunnableCbf_t)(void);

typedef struct {
	u8* name;
	u32 Periodms;
	u32 StartDelay;
	RunnableCbf_t cbf;

}TaskInfo_t;

typedef struct{
	//TaskInfo_t* taskinfo;
	u32 RemainTime;
}Task_t;


typedef enum {
	Sched_enuOK = 0,
	Sched_enuNotOK,
	Sched_enuTimeOut,
	Sched_enuWrongValue,
	Sched_NullPtr

} Sched_tenuErrorStatus;

Sched_tenuErrorStatus Sched_Init(void);
Sched_tenuErrorStatus Sched_Start(void);
static void Sched(void);
void tick_cbf(void);

#endif /* SCHED_H_ */
