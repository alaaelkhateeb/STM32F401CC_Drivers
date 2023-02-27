/*
 * LED_Cfg.h
 *
 *  Created on: Feb 23, 2023
 *      Author: alaa
 */

#ifndef LED_CFG_H_
#define LED_CFG_H_

/*#include "LED.h"*/


typedef enum{
	LED_Alarm,
	LED_Count
}LEDCfgNumber_t;

typedef struct {
	void* LEDPort;
	u8 LEDPin;
	u8 LEDMode;
	u8 LEDSpeed;
} LEDCfg_t;

#endif /* LED_CFG_H_ */
