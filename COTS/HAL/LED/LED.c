/*
 * LED.c
 *
 *  Created on: Feb 23, 2023
 *      Author: alaa
 */

/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/

#include "GPIO.h"
#include "LED_Cfg.h"
#include "LED.h"

LED_tenuErrorStatus LED_Init(void) {
	LED_tenuErrorStatus LED_Status = LED_enuOK;
	GPIO_tInit GPIO_Cfg;
	u8 Loc_u8Counter = 0;
	for (Loc_u8Counter = 0; Loc_u8Counter < LED_Count; Loc_u8Counter++) {
		GPIO_Cfg.ModeSelect = GPIO_MODE_OUTPUT_PP;
		GPIO_Cfg.Port = LED_Config[Loc_u8Counter].LEDPort;
		GPIO_Cfg.Pin = LED_Config[Loc_u8Counter].LEDPin;
		GPIO_Cfg.Speed = LED_Config[Loc_u8Counter].LEDSpeed;
		LED_Status = GPIO_Init(&GPIO_Cfg);
	}
	return LED_Status;
}

LED_tenuErrorStatus LED_SetState(LEDCfgNumber_t LedID, u8 StateSelection) {
	LED_tenuErrorStatus LED_Status = LED_enuOK;
	GPIO_SetPinValue(LED_Config[LedID].LEDPort, LED_Config[LedID].LEDPin,
			(LED_Config[LedID].LEDMode ^ StateSelection));

	return LED_Status;
}
