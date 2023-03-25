/*
 * Btn.c
 *
 *  Created on: Mar 9, 2023
 *      Author: alaa
 */
/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/

#include "GPIO.h"
#include "BTN.h"
#include "BTN_Cfg.h"

static BTN_tenuStatus BTN_State[BTN_Count];
static BTN_tenuStatus BTN_PrevState[BTN_Count];

static u32 BTN_Debounce[BTN_Count];

BTN_tenuErrorStatus BTN_Init(void) {
	BTN_tenuErrorStatus BTN_Status = BTN_enuOK;
	GPIO_tInit GPIO_Cfg;
	u8 Loc_u8Counter = 0;
	for (Loc_u8Counter = 0; Loc_u8Counter < BTN_Count; Loc_u8Counter++) {
		GPIO_Cfg.ModeSelect = GPIO_MODE_INPUT_OD_PU;
		GPIO_Cfg.Port = BTN_Config[Loc_u8Counter].BTNPort;
		GPIO_Cfg.Pin = BTN_Config[Loc_u8Counter].BTNPin;
		GPIO_Cfg.Speed = BTN_Config[Loc_u8Counter].BTNSpeed;
		BTN_Status = GPIO_Init(&GPIO_Cfg);
	}
	return BTN_Status;

}

BTN_tenuErrorStatus BTN_GetState(BTNCfgNumber_t BTNID, u8* Cpy_u8ReturnedState) {
	BTN_tenuErrorStatus BTN_Status = BTN_enuOK;
	GPIO_GetPinValue(BTN_Config[BTNID].BTNPort, BTN_Config[BTNID].BTNPin,
			&Cpy_u8ReturnedState);
	/**Cpy_u8ReturnedState^=BTN_Config[BTNID].BTNMode;*/
	return BTN_Status;
}

BTN_tenuStatus BTN_ReadState(BTNCfgNumber_t BTNID) {
	return BTN_State[BTNID];

}

void BTN_DebouceSCHED_Handler(void) {
	u32 Loc_u32idx = 0;
	BTN_tenuStatus BTN_CurrentState = BTN_enuReleased;
	for (Loc_u32idx = 0; Loc_u32idx < BTN_Count; Loc_u32idx++) {
		GPIO_GetPinValue(BTN_Config[Loc_u32idx].BTNPort, BTN_Config[Loc_u32idx].BTNPin,
				&BTN_CurrentState);
		if(BTN_CurrentState== BTN_PrevState[Loc_u32idx]){
			if(BTN_Debounce[Loc_u32idx]==Btn_DebounceMax){
				BTN_State[Loc_u32idx]=BTN_CurrentState;
			}else{
				BTN_Debounce[Loc_u32idx]++;
			}
		}else{
			 BTN_PrevState[Loc_u32idx]=BTN_CurrentState;
		}
	}

}

