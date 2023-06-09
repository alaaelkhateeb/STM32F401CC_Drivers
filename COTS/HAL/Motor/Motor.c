/*
 * Motor.c
 *
 *  Created on: Jun 9, 2023
 *      Author: alaa
 */

#include "Std_Types.h"
#include "Bit_Math.h"
#include "TIM2_Private.h"
#include "TIM2.h"
#include "Motor.h"

Motor_tenuErrorStatus Motor_enuForwardMovement(void) {
	Motor_tenuErrorStatus Loc_enuStatus = Motor_enuOK;
	/* Speed PWM for Right Motor */
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL1,1,0);	//Left
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL2,1,30);	//Right

	/* Speed PWM for Left Motor */
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL3,1,0);	//Left
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL4,1,30);	//Right
	return Loc_enuStatus;
}
Motor_tenuErrorStatus Motor_enuBackwardMovement(void) {
	Motor_tenuErrorStatus Loc_enuStatus = Motor_enuOK;

	/* Speed PWM for Right Motor */
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL1,1,30);	//Left
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL2,1,0);	//Right

	/* Speed PWM for Left Motor */
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL3,1,30);	//Left
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL4,1,0);	//Right
	return Loc_enuStatus;

}
Motor_tenuErrorStatus Motor_enuLeftMovement(void) {
	Motor_tenuErrorStatus Loc_enuStatus = Motor_enuOK;
	/* Speed PWM for Right Motor */
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL1,1,0);	//Left
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL2,1,30);	//Right

		/* Speed PWM for Left Motor */
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL3,1,30);	//Left
	Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL4,1,0);	//Right
	return Loc_enuStatus;
}
Motor_tenuErrorStatus Motor_enuRightMovement(void) {
	Motor_tenuErrorStatus Loc_enuStatus = Motor_enuOK;
	/* Speed PWM for Right Motor */
		Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL1,1,30);	//Left
		Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL2,1,0);	//Right

		/* Speed PWM for Left Motor */
		Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL3,1,0);	//Left
		Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL4,1,30);	//Right
	return Loc_enuStatus;
}
Motor_tenuErrorStatus Motor_enuStopMovement(void) {
	Motor_tenuErrorStatus Loc_enuStatus = Motor_enuOK;
	/* Speed PWM for Right Motor */
		Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL1,1,0);	//Left
		Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL2,1,0);	//Right

		/* Speed PWM for Left Motor */
		Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL3,1,0);	//Left
		Loc_enuStatus=TIMx_enuGenerateKHzPWM(TIMxOption_TIM2,TIMx_enu_CHANNEL4,1,0);	//Right
	return Loc_enuStatus;
}
