/*
 * App2.c
 *
 *  Created on: Mar 23, 2023
 *      Author: alaa
 */


#include "RCC_Interface.h"
#include "GPIO.h"
#include "GPIO_Private.h"
#include "LED.h"
#include "BTN.h"
#include "NVIC.h"
#include "Delay.h"


extern void App2(void){

		GPIO_SetPinValue(GPIOC, GPIO_PIN13, GPIO_High);


}
