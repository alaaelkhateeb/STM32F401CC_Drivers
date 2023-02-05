/*
 * RCC_Program.c
 *
 *  Created on: Jan 28, 2023
 *      Author: alaa
 */

/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/
#include "RCC_Interface.h"
#include "RCC_Private.h"
#include "RCC_Config.h"

//#define TimeOut_Flag 0xFF

RCC_tenuErrorStatus RCC_enuEnableHSI(void) {
	u16 Loc_u16ErrorCount = 0xFFFF;
	u32 Loc_u32RegTemp = 0;
	RCC_tenuErrorStatus Loc_enuStatus = RCC_enuOK;
	Loc_u32RegTemp = RCC_CR_REG;
	if ((GET_BIT(Loc_u32RegTemp, 16)) == 1) {
		CLR_BIT(Loc_u32RegTemp, 16);
	}
	RCC_CR_REG = Loc_u32RegTemp;
	Loc_u32RegTemp = RCC_CR_REG;
	/*set HSION*/

	SET_BIT(Loc_u32RegTemp, 0);
	RCC_CR_REG = Loc_u32RegTemp;

	/*wait until HSIRDY*/
	while ((GET_BIT(RCC_CR_REG, 1)) == 0 && (Loc_u16ErrorCount--) > 0)
		;
	if (Loc_u16ErrorCount > 0 && (GET_BIT(RCC_CR_REG, 1)) == 1) {
		Loc_enuStatus = RCC_enuOK;
	} else {
		Loc_enuStatus = RCC_enuTimeOut;
	}

	/*ENABLE HSI SW */

	//RCC_CFGR_REG=(RCC_CFGR_REG&0xFFFFFFF0);
	Loc_u32RegTemp = RCC_CFGR_REG;

	CLR_BIT(Loc_u32RegTemp, 0);
	CLR_BIT(Loc_u32RegTemp, 1);
	RCC_CFGR_REG = Loc_u32RegTemp;

	/*WAIT TO CHECK SWS FOR HSI */
	while (!((GET_BIT(RCC_CFGR_REG, 2)) == 0 && (GET_BIT(RCC_CFGR_REG, 3)) == 0)
			&& (Loc_u16ErrorCount--) > 0)
		;
	if (Loc_u16ErrorCount > 0 && (GET_BIT(RCC_CFGR_REG, 2)) == 0
			&& (GET_BIT(RCC_CFGR_REG, 3)) == 0) {
		Loc_enuStatus = RCC_enuOK;
	} else {
		Loc_enuStatus = RCC_enuTimeOut;
	}
	return Loc_enuStatus;
}
RCC_tenuErrorStatus RCC_enuEnableHSE(void) {
	u16 Loc_u16ErrorCount = 0xFFFF;
	u32 Loc_u32RegTemp = 0;
	RCC_tenuErrorStatus Loc_enuStatus = RCC_enuOK;
	/*reset reg value*/
	RCC_CR_REG = 0x00000081;
	Loc_u32RegTemp = RCC_CR_REG;

	/*set HSEON*/
	/*RCC_CR_REG=(RCC_CR_REG&0xFFF0FFFF)|0x00010000*/
	SET_BIT(Loc_u32RegTemp, 16);
	RCC_CR_REG = Loc_u32RegTemp;

	/*wait until HSERDY*/
	while ((GET_BIT(RCC_CR_REG, 17)) == 0 && (Loc_u16ErrorCount--) > 0)
		;
	if (Loc_u16ErrorCount > 0 && (GET_BIT(RCC_CR_REG, 17)) == 1) {
		Loc_enuStatus = RCC_enuOK;
	} else {
		Loc_enuStatus = RCC_enuTimeOut;
	}

	/*ENABLE HSE SW */
	/*RCC_CFGR_REG=(RCC_CFGR_REG&0xFFFFFFF0)|0X00000001*/

	Loc_u32RegTemp = RCC_CFGR_REG;
	SET_BIT(Loc_u32RegTemp, 0);
	CLR_BIT(Loc_u32RegTemp, 1);

	RCC_CFGR_REG = Loc_u32RegTemp;

	/*WAIT TO CHECK SWS FOR HSE */
	while (((GET_BIT(RCC_CFGR_REG, 2)) == 1 && (GET_BIT(RCC_CFGR_REG, 3)) == 0)
			&& (Loc_u16ErrorCount--) > 0)
		;
	if (Loc_u16ErrorCount > 0 && (GET_BIT(RCC_CFGR_REG, 2)) == 1
			&& (GET_BIT(RCC_CFGR_REG, 3)) == 0) {
		Loc_enuStatus = RCC_enuOK;
	} else {
		Loc_enuStatus = RCC_enuTimeOut;
	}
	return Loc_enuStatus;

}

void RCC_vidDisableHSI(void) {
	u32 Loc_u32RegTemp = 0;
	Loc_u32RegTemp = RCC_CR_REG;
	/*check if on*/
	if ((GET_BIT(Loc_u32RegTemp, 0)) == 1) {
		CLR_BIT(Loc_u32RegTemp, 0);
	}
	RCC_CR_REG = Loc_u32RegTemp;
}
void RCC_vidDisableHSE(void) {
	u32 Loc_u32RegTemp = 0;
	/*reset reg value*/
	RCC_CR_REG = 0x00000081;

	Loc_u32RegTemp = RCC_CR_REG;
	/*check if on*/
	if ((GET_BIT(Loc_u32RegTemp, 16)) == 1) {
		CLR_BIT(Loc_u32RegTemp, 16);
	}
	RCC_CR_REG = Loc_u32RegTemp;

}

RCC_tenuErrorStatus RCC_enuConfigPLL(u16 PLLN, u8 PLLM, u8 PLLP, u8 PLLQ) {
	/*parametr configuraton */
	/*
	 f(VCO clock) = f(PLL clock input) × (PLLN / PLLM)
	 f(PLL general clock output) = f(VCO clock) / PLLP
	 f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLL*/

	u32 Loc_u32RegTemp = 0;

	RCC_tenuErrorStatus Loc_enuStatus = RCC_enuOK;

	/*turn pll off to configure it */
	Loc_u32RegTemp = RCC_CR_REG;
	CLR_BIT(Loc_u32RegTemp, 24);

	RCC_CR_REG = Loc_u32RegTemp;
	/*config PLL parameters*/
	if (PLLQ > 15) {
		Loc_enuStatus = RCC_enuWrongValue;
	}
	if (PLLN > 511) {
		Loc_enuStatus = RCC_enuWrongValue;
	}
	if (PLLM > 63) {
		Loc_enuStatus = RCC_enuWrongValue;
	}
	if (PLLP > 8 && (PLLP % 2 != 0)) {
		Loc_enuStatus = RCC_enuWrongValue;
	}

	/*clearing 6->14 bits and adding value*/
	RCC_PLLCFGR_REG = (RCC_PLLCFGR_REG & 0xFFFFC03F) | (PLLN << 6);

	/*clearing 0->5 bits and adding value*/
	RCC_PLLCFGR_REG = (RCC_PLLCFGR_REG & 0xFFFFFFC0) | (PLLM << 0);

	/*clearing 16,17 bits and adding value*/
	RCC_PLLCFGR_REG = (RCC_PLLCFGR_REG & 0xFFF3FFFF) | (PLLP << 16);

	/*clearing 24->27 bits and adding value*/
	RCC_PLLCFGR_REG = (RCC_PLLCFGR_REG & 0xF0FFFFFF) | (PLLQ << 24);

	return Loc_enuStatus;

}
RCC_tenuErrorStatus RCC_enuEnablePLL(RCC_tenuPLLSrcCLKSelection RCC_enuSelect) {
	u16 Loc_u16ErrorCount = 0xFF;
	u32 Loc_u32RegTemp = 0;

	RCC_tenuErrorStatus Loc_enuStatus = RCC_enuOK;

	/*select source of pll clock*/
	if (RCC_enuSelect == RCC_enuHSE) {
		RCC_enuEnableHSE();
		/*enable source pll*/
		Loc_u32RegTemp = RCC_PLLCFGR_REG;
		SET_BIT(Loc_u32RegTemp, 22);
	} else if (RCC_enuSelect == RCC_enuHSI) {
		Loc_enuStatus = RCC_enuEnableHSI();
		/*enable source pll*/
		Loc_u32RegTemp = RCC_PLLCFGR_REG;
		CLR_BIT(Loc_u32RegTemp, 22);
	}
	RCC_PLLCFGR_REG = Loc_u32RegTemp;
	/*turn pll on*/
	Loc_u32RegTemp = RCC_CR_REG;
	SET_BIT(Loc_u32RegTemp, 24);
	RCC_CR_REG = Loc_u32RegTemp;

	/*wait until PLLRDY*/
	while ((GET_BIT(RCC_CR_REG, 25)) == 0 && (Loc_u16ErrorCount--) > 0)
		;
	if (Loc_u16ErrorCount > 0 && (GET_BIT(RCC_CR_REG, 25)) == 1) {
		Loc_enuStatus = RCC_enuOK;
	} else {
		Loc_enuStatus = RCC_enuTimeOut;
	}

	/*ENABLE PLL SW */
	/*RCC_CFGR_REG=(RCC_CFGR_REG&0xFFFFFFF0)|0X00000010*/
	Loc_u32RegTemp = RCC_CFGR_REG;
	SET_BIT(Loc_u32RegTemp, 1);
	CLR_BIT(Loc_u32RegTemp, 0);
	RCC_CFGR_REG = Loc_u32RegTemp;
	/*WAIT TO CHECK SWS FOR PLL */
	while (!((GET_BIT(RCC_CFGR_REG, 2)) == 0 && (GET_BIT(RCC_CFGR_REG, 3)) == 1)
			&& (Loc_u16ErrorCount--) > 0)
		;
	if (Loc_u16ErrorCount > 0 && (GET_BIT(RCC_CFGR_REG, 2)) == 0
			&& (GET_BIT(RCC_CFGR_REG, 3)) == 1) {
		Loc_enuStatus = RCC_enuOK;
	} else {
		Loc_enuStatus = RCC_enuTimeOut;
	}
	return Loc_enuStatus;
}

void RCC_vidEnableDisAHB1ClkPerpheral(
		RCC_tenuAHB1PeripheralEn RCC_enuPeripheralSelection,
		RCC_tenuEnDisPeripheral RCC_enuSelect) {

	u32 Loc_u32RegTemp = 0;
	Loc_u32RegTemp = RCC_AHB1ENR_REG;
	/*set peripheral pin to enable clk*/
	if (RCC_enuSelect == RCC_enuEnPeripheral) {

		SET_BIT(Loc_u32RegTemp, RCC_enuPeripheralSelection);
		RCC_AHB1ENR_REG = Loc_u32RegTemp;
		/*clear peripheral pin to disable clk*/
	} else if (RCC_enuSelect == RCC_enuDisablePeripheral) {
		CLR_BIT(Loc_u32RegTemp, RCC_enuPeripheralSelection);
		RCC_AHB1ENR_REG = Loc_u32RegTemp;
	}

}

void RCC_vidSetPrescalerAPB1(RCC_tenuAPB_PRESCALER APB1Select) {
	u32 Loc_u32RegTemp = 0;
	Loc_u32RegTemp = RCC_CFGR_REG;
	/*clearing 10->12 bits and adding value*/
	Loc_u32RegTemp = (Loc_u32RegTemp & 0xFFFFE3FF) | (APB1Select << 10);
	RCC_CFGR_REG = Loc_u32RegTemp;

}
void RCC_vidSetPrescalerAPB2(RCC_tenuAPB_PRESCALER APB2Select) {
	u32 Loc_u32RegTemp = 0;
	Loc_u32RegTemp = RCC_CFGR_REG;
	/*clearing 13->15 bits and adding value*/
	Loc_u32RegTemp = (Loc_u32RegTemp & 0xFFFF1FFF) | (APB2Select << 13);
	RCC_CFGR_REG = Loc_u32RegTemp;

}
void RCC_vidGetClockSelection(RCC_tenuPLLSrcCLKSelection *CLkSelection) {
	if ((GET_BIT(RCC_CFGR_REG, 2)) == 0 && (GET_BIT(RCC_CFGR_REG, 3)) == 0) {
		*CLkSelection = RCC_enuHSI;
	} else if ((GET_BIT(RCC_CFGR_REG, 2)) == 1
			&& (GET_BIT(RCC_CFGR_REG, 3)) == 0) {
		*CLkSelection = RCC_enuHSE;
	} else if ((GET_BIT(RCC_CFGR_REG, 2)) == 0
			&& (GET_BIT(RCC_CFGR_REG, 3)) == 1) {
		*CLkSelection = RCC_enuPLL;
	}
}
