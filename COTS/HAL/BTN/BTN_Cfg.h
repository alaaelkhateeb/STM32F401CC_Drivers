/*
 * BTN_Cfg.h
 *
 *  Created on: Mar 9, 2023
 *      Author: alaa
 */

#ifndef BTN_CFG_H_
#define BTN_CFG_H_




typedef enum{
	BTN_Alarm,
	BTN_Count
}BTNCfgNumber_t;

typedef struct {
	void* BTNPort;
	u8 BTNPin;
	u8 BTNMode;
	u8 BTNSpeed;
} BTNCfg_t;

#endif /* BTN_CFG_H_ */
