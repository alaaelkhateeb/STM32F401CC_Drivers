/*
 * Motor.h
 *
 *  Created on: Jun 9, 2023
 *      Author: alaa
 */

#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum {
	Motor_enuOK = 0,
	Motor_enuNotOK,
	Motor_enuTimeOut,
	Motor_enuWrongValue,
	Motor_NullPtr

} Motor_tenuErrorStatus;


Motor_tenuErrorStatus Motor_enuForwardMovement(void);
Motor_tenuErrorStatus Motor_enuBackwardMovement(void);
Motor_tenuErrorStatus Motor_enuLeftMovement(void);
Motor_tenuErrorStatus Motor_enuRightMovement(void);
Motor_tenuErrorStatus Motor_enuStopMovement(void);


#endif /* MOTOR_H_ */
