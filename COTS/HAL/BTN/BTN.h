/*
 * BTN.h
 *
 *  Created on: Mar 9, 2023
 *      Author: alaa
 */

#ifndef BTN_H_
#define BTN_H_

#include "Std_types.h"
#include "BTN_Cfg.h"

#define PullUP 	0
#define PullDown 1

typedef enum{
	BTN_enuOK = 0,
	BTN_enuNotOK,
	BTN_enuTimeOut,
	BTN_enuWrongValue,
	BTN_NullPtr
}BTN_tenuErrorStatus;
typedef enum{
	BTN_enuReleased = 0,
	BTN_enuPressed
}BTN_tenuStatus;


extern const  BTNCfg_t BTN_Config[BTN_Count];



BTN_tenuErrorStatus BTN_Init(void);

BTN_tenuErrorStatus BTN_GetState(BTNCfgNumber_t BTNID, u8* Cpy_u8ReturnedState);







#endif /* BTN_H_ */
