/*
 * LED_Cfg.c
 *
 *  Created on: Feb 23, 2023
 *      Author: alaa
 */

#include "LED.h"
#include "LED_Cfg.h"
#include "GPIO.h"
#include "GPIO_Private.h"



const LEDCfg_t LED_Config[LED_Count] = {
		[LED_Alarm]= {
				.LEDPin = GPIO_PIN13,
				.LEDPort = GPIOC,
				.LEDSpeed = GPIO_OUTPUT_SPEED_MEDIUM,
				.LEDMode =ActiveLow
				 },
};
