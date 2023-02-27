/*
 * LED.h
 *
 *  Created on: Feb 23, 2023
 *      Author: alaa
 */

#ifndef LED_H_
#define LED_H_

#include "Std_types.h"
#include "LED_Cfg.h"


#define StateON		    1
#define StateOFF		0



#define ActiveHigh		1
#define ActiveLow		0


extern const  LEDCfg_t LED_Config[LED_Count];

typedef enum{
	LED_enuOK = 0,
	LED_enuNotOK,
	LED_enuTimeOut,
	LED_enuWrongValue,
	LED_NullPtr
}LED_tenuErrorStatus;





LED_tenuErrorStatus LED_Init(void);

LED_tenuErrorStatus LED_SetState(LEDCfgNumber_t LedID, u8 StateSelection);







#endif /* LED_H_ */
