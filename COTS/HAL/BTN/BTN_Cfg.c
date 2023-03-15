/*
 * BTN_Cfg.c
 *
 *  Created on: Mar 9, 2023
 *      Author: alaa
 */




#include "BTN.h"
#include "BTN_Cfg.h"
#include "GPIO.h"
#include "GPIO_Private.h"



const BTNCfg_t BTN_Config[BTN_Count] = {
		[BTN_Alarm]= {
				.BTNPin = GPIO_PIN13,
				.BTNPort = GPIOB,
				.BTNSpeed = GPIO_OUTPUT_SPEED_MEDIUM,
				.BTNMode =PullDown
				 },
};
