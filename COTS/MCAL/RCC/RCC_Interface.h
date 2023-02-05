/*
 * RCC_Interface.h
 *
 *  Created on: Jan 28, 2023
 *      Author: alaa
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_
#include "Std_types.h"

/*******************************************************************************
 ***                            Types Declaration                            ***
 ******************************************************************************/
typedef enum {
	RCC_enuOK = 0, RCC_enuNotOK, RCC_enuTimeOut, RCC_enuWrongValue

} RCC_tenuErrorStatus;
typedef enum {
	RCC_enuHSE = 0, RCC_enuHSI, RCC_enuPLL
} RCC_tenuPLLSrcCLKSelection;

typedef enum {

	RCC_enuGPIOAEN = 0,
	RCC_enuGPIOBEN,
	RCC_enuGPIOCEN,
	RCC_enuGPIODEN,
	RCC_enuGPIOEEN,
	RCC_enuGPIOHEN,
	RCC_enuCRCEN = 12,
	RCC_enuDMA1EN = 21,
	RCC_enuDMA2EN
} RCC_tenuAHB1PeripheralEn;

typedef enum {
	RCC_enuEnPeripheral = 0, RCC_enuDisablePeripheral
} RCC_tenuEnDisPeripheral;

/*APB1 CLOCK PRESCALER*/
typedef enum {
	AHB_SYSCLK_not_divided,
	AHB_SYSCLK_divided_by_2 = 4,
	AHB_SYSCLK_divided_by_4,
	AHB_SYSCLK_divided_by_8,
	AHB_SYSCLK_divided_by_16
} RCC_tenuAPB_PRESCALER;
typedef enum {
	SYSCLK_not_divided,
	SYSCLK_divided_by_2 = 8,
	SYSCLK_divided_by_4,
	SYSCLK_divided_by_8,
	SYSCLK_divided_by_16,
	SYSCLK_divided_by_64,
	SYSCLK_divided_by_128,
	SYSCLK_divided_by_256,
	SYSCLK_divided_by_512
} RCC_tenuAHB_PRESCALER;

///////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 ****                    Functions Prototypes                              ****
 ******************************************************************************/

/******************************************************************************
 * @brief 	   Configure RCC module to operate in HSI(High Speed Internal) mode.
 * @param 					VOID
 * @return 					RCC_tenuErrorStatus
 *************************************************************************** */
RCC_tenuErrorStatus RCC_enuEnableHSI(void);
/******************************************************************************
 * @brief 	   Configure RCC module to operate in HSE(High Speed External) mode.
 * @param 					VOID
 * @return 					RCC_tenuErrorStatus
 *************************************************************************** */
RCC_tenuErrorStatus RCC_enuEnableHSE(void);
/******************************************************************************
 * @brief 	   Configure RCC module to operate in PLL(Phase Locked Loop) mode.
 * @param 					RCC_enuSelect
 * 							PLLN,PLLM,PLLP,PLLQ (PLL parameters)
 * @return 					RCC_tenuErrorStatus
 *************************************************************************** */
RCC_tenuErrorStatus RCC_enuConfigPLL(u16 PLLN, u8 PLLM, u8 PLLP, u8 PLLQ);
/******************************************************************************
 * @brief 					Enable clock for a specific peripheral on AHB1.
 * @param 					Select peripheral
 * 							Enable/Disable
 * @return 					VOID
 *************************************************************************** */
void RCC_vidEnableDisAHB1ClkPerpheral(
		RCC_tenuAHB1PeripheralEn RCC_enuPeripheralSelection,
		RCC_tenuEnDisPeripheral RCC_enuSelect);

void RCC_vidSetPrescalerAPB1(RCC_tenuAPB_PRESCALER APB1Select);
void RCC_vidSetPrescalerAPB2(RCC_tenuAPB_PRESCALER APB2Select);
void RCC_vidGetClockSelection(RCC_tenuPLLSrcCLKSelection *CLkSelection);

RCC_tenuErrorStatus RCC_enuEnablePLL(RCC_tenuPLLSrcCLKSelection RCC_enuSelect);
void RCC_vidDisableHSI(void);
void RCC_vidDisableHSE(void);
#endif /* RCC_INTERFACE_H_ */
