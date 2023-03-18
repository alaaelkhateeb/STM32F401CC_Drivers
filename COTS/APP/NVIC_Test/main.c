// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "RCC_Interface.h"
#include "GPIO.h"
#include "GPIO_Private.h"
#include "LED.h"
#include "BTN.h"
#include "NVIC.h"
int main() {

	volatile RCC_tenuSrcCLKSelection status;
	volatile RCC_tenuErrorStatus clockStatus;
	 u8 data = 0;
	clockStatus = RCC_enuEnableHSE();
	//clockStatus=RCC_enuEnablePLL(RCC_enuHSI);
	//clockStatus=RCC_enuEnableSystemCLK(RCC_enuPLL);
	clockStatus = RCC_enuEnableSystemCLK(RCC_enuHSE);
	RCC_vidGetClockSelection(&status);

	RCC_vidEnableDisAHB1ClkPerpheral(RCC_enuGPIOCEN, RCC_enuEnPeripheral);
	RCC_vidEnableDisAHB1ClkPerpheral(RCC_enuGPIOBEN, RCC_enuEnPeripheral);
	GPIO_SetPinMode(GPIOC, GPIO_PIN13, GPIO_MODE_OUTPUT_PP,
				GPIO_OUTPUT_SPEED_MEDIUM);




	NVIC_EnableIRQ(6);
	NVIC_SetPending(6);

	NVIC_EnableIRQ(7);
	NVIC_SetPending(7);
	while (1) {
		// Add your code here.
	}
}

void EXTI0_IRQHandler(void){
	GPIO_SetPinValue(GPIOC, GPIO_PIN13, GPIO_Low);

}
void EXTI1_IRQHandler(void){
	GPIO_SetPinValue(GPIOC, GPIO_PIN13, GPIO_High);
}
