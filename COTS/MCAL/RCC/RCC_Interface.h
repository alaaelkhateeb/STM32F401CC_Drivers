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
} RCC_tenuSrcCLKSelection;

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

	RCC_enuTIM2EN = 0,
	RCC_enuTIM3EN,
	RCC_enuTIM4EN,
	RCC_enuTIM5EN,
	RCC_enuWWDGEN=11,
	RCC_enuSPI2EN=14,
	RCC_enuSPI3EN ,
	RCC_enuUSART2EN=17,
	RCC_enuI2C1EN=21,
	RCC_enuI2C2EN,
	RCC_enuI2C3EN,
	RCC_enuPWREN
} RCC_tenuAPB1PeripheralEn;
typedef enum {

	RCC_enuTIM1EN = 0,
	RCC_enuUSART1EN=4,
	RCC_enuUSART6EN,
	RCC_enuADC1EN=8,
	RCC_enuSDIOEN=11,
	RCC_enuSPI1EN,
	RCC_enuSPI4EN,
	RCC_enuSYSCFGEN,
	RCC_enuTIM9EN=16,
	RCC_enuTIM10EN,
	RCC_enuTIM11EN

} RCC_tenuAPB2PeripheralEn;
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
 * @brief 	   Enable HSI(High Speed Internal) mode.
 * @param 					VOID
 * @return 					RCC_tenuErrorStatus
 *************************************************************************** */
RCC_tenuErrorStatus RCC_enuEnableHSI(void);
/******************************************************************************
 * @brief 	   Enable HSE(High Speed External) mode.
 * @param 					VOID
 * @return 					RCC_tenuErrorStatus
 *************************************************************************** */
RCC_tenuErrorStatus RCC_enuEnableHSE(void);
/******************************************************************************
 * @brief 	   Configure  PLL(Phase Locked Loop) mode.
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
/******************************************************************************
 * @brief 					Enable clock for a specific peripheral on APB1.
 * @param 					Select peripheral
 * 							Enable/Disable
 * @return 					VOID
 *************************************************************************** */
void RCC_vidEnableDisAPB1ClkPerpheral(
		RCC_tenuAPB1PeripheralEn RCC_enuPeripheralSelection,
		RCC_tenuEnDisPeripheral RCC_enuSelect);
/******************************************************************************
 * @brief 					Enable clock for a specific peripheral on APB2.
 * @param 					Select peripheral
 * 							Enable/Disable
 * @return 					VOID
 *************************************************************************** */
void RCC_vidEnableDisAPB2ClkPerpheral(
		RCC_tenuAPB2PeripheralEn RCC_enuPeripheralSelection,
		RCC_tenuEnDisPeripheral RCC_enuSelect);
/******************************************************************************
 * @brief 					Set prescalar of clock for  APB1.
 * @param 					Select prescalar

 * @return 					VOID
 *************************************************************************** */
void RCC_vidSetPrescalerAPB1(RCC_tenuAPB_PRESCALER APB1Select);
/******************************************************************************
 * @brief 					Set prescalar of clock for  APB2.
 * @param 					Select prescalar

 * @return 					VOID
 *************************************************************************** */
void RCC_vidSetPrescalerAPB2(RCC_tenuAPB_PRESCALER APB2Select);
/******************************************************************************
 * @brief 					Get which clk source selected as system clock.
 * @param 					*CLkSelection:pointer holds clk selected

 * @return 					VOID
 *************************************************************************** */
void RCC_vidGetClockSelection(RCC_tenuSrcCLKSelection *CLkSelection);
/******************************************************************************
 * @brief 	   Enable RCC module to operate in PLL(Phase Locked Loop) mode.
 * @param 					RCC_enuSelect:which source
 * @return 					RCC_tenuErrorStatus
 *************************************************************************** */
RCC_tenuErrorStatus RCC_enuEnablePLL(RCC_tenuSrcCLKSelection RCC_enuSelect);
/******************************************************************************
 * @brief 	   Disable RCC HSI Clk.
 * @param 					VOID
 * @return 					VOID
 *************************************************************************** */
void RCC_vidDisableHSI(void);
/******************************************************************************
 * @brief 	   Disable RCC HSE Clk.
 * @param 					VOID
 * @return 					VOID
 *************************************************************************** */
void RCC_vidDisableHSE(void);
/******************************************************************************
 * @brief 	   Enable System clk with selected source.
 * @param 					RCC_enuSelect:which source
 * @return 					RCC_tenuErrorStatus
 *************************************************************************** */
RCC_tenuErrorStatus	RCC_enuEnableSystemCLK(RCC_tenuSrcCLKSelection Rcc_ClkSelect);

#endif /* RCC_INTERFACE_H_ */
