// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "RCC_Interface.h"
#include "GPIO.h"
#include "GPIO_Private.h"
#include "LED.h"
int main() {

	volatile RCC_tenuSrcCLKSelection status;
	volatile RCC_tenuErrorStatus clockStatus;
	volatile u8 data = 0;
	clockStatus = RCC_enuEnableHSE();
	//clockStatus=RCC_enuEnablePLL(RCC_enuHSI);
	//clockStatus=RCC_enuEnableSystemCLK(RCC_enuPLL);
	clockStatus=RCC_enuEnableSystemCLK(RCC_enuHSE);
	RCC_vidGetClockSelection(&status);

	RCC_vidEnableDisAHB1ClkPerpheral(RCC_enuGPIOCEN, RCC_enuEnPeripheral);

	GPIO_SetPinMode(GPIOC, GPIO_PIN13, GPIO_MODE_OUTPUT_PP,
			GPIO_OUTPUT_SPEED_MEDIUM);


	LED_Init();
	LED_SetState(LED_Alarm,StateOFF);
	LED_SetState(LED_Alarm,StateON);
	LED_SetState(LED_Alarm,StateOFF);

	while (1) {
		// Add your code here.
	}
}

