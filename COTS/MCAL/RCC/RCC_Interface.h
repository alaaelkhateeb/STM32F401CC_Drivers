/*
 * RCC_Interface.h
 *
 *  Created on: Jan 28, 2023
 *      Author: alaa
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_


typedef enum{
	RCC_enuOK=0,
	RCC_enuNotOK,
	RCC_enuTimeOut

}RCC_tenuErrorStatus;
typedef enum {
	RCC_enuHSE=0,
	RCC_enuHSI
}RCC_tenuPLLSrcCLKSelection;

typedef enum{

	RCC_enuGPIOAEN=0,
	RCC_enuGPIOBEN,
	RCC_enuGPIOCEN,
	RCC_enuGPIODEN,
	RCC_enuGPIOEEN,
	RCC_enuGPIOHEN,
	RCC_enuCRCEN=12,
	RCC_enuDMA1EN=21,
	RCC_enuDMA2EN
}RCC_tenuAHB1PeripheralEn;

typedef enum{
	RCC_enuEnPeripheral=0,
	RCC_enuDisablePeripheral
}RCC_tenuEnDisPeripheral;

RCC_tenuErrorStatus RCC_enuEnableHSI(void);
RCC_tenuErrorStatus RCC_enuEnableHSE(void);
RCC_tenuErrorStatus RCC_enuEnablePLL(RCC_tenuPLLSrcCLKSelection RCC_enuSelect,u8 PLLN,u8 PLLM,u8 PLLP,u8 PLLQ);
void RCC_enuEnableDisAHB1ClkPerpheral(RCC_tenuAHB1PeripheralEn RCC_enuPeripheralSelection,RCC_tenuEnDisPeripheral RCC_enuSelect);

#endif /* RCC_INTERFACE_H_ */
