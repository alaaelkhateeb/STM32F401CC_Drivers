// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "RCC_Interface.h"
#include "GPIO.h"
#include "GPIO_Private.h"
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
	RCC_vidEnableDisAHB1ClkPerpheral(RCC_enuGPIOAEN, RCC_enuEnPeripheral);



	GPIO_SetPinMode(GPIOC, GPIO_PIN13, GPIO_MODE_OUTPUT_PP,
			GPIO_OUTPUT_SPEED_MEDIUM);
	GPIO_SetPinValue(GPIOC, GPIO_PIN13, GPIO_High);

	GPIO_SetPinMode(GPIOA, GPIO_PIN5, GPIO_MODE_INPUT_OD_PU,
			GPIO_OUTPUT_SPEED_MEDIUM);
	GPIO_SetPinValue(GPIOC, GPIO_PIN13, GPIO_Low);

	GPIO_GetPinValue(GPIOA, GPIO_PIN5, &data);
	if (data == GPIO_High) {
		GPIO_SetPinValue(GPIOC, GPIO_PIN13, GPIO_Low);
	} else if (data == GPIO_Low) {
		GPIO_SetPinValue(GPIOC, GPIO_PIN13, GPIO_Low);
	}
	while (1) {
		// Add your code here.
	}
}

