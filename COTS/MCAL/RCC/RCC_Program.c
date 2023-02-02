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

#include "RCC_Private.h"
#include "RCC_Interface.h"
#include "RCC_Config.h"

#define TimeOut_Flag 1000


RCC_tenuErrorStatus RCC_enuEnableHSI(void){
	u16 Loc_u16ErrorCount=0;
	RCC_tenuErrorStatus Loc_enuStatus=RCC_enuOK;
	/*reset reg value*/
	RCC_CR_REG=0x00000081;
	/*set HSION*/

	RCC_CR_REG=(RCC_CR_REG&0xFFFFFFF0)|(0b0001);
		/*SET_BIT(RCC_CR_REG,0);*/

	/*wait until HSIRDY*/
	while((GET_BIT(RCC_CR_REG,1))== 0&& (Loc_u16ErrorCount++)<TimeOut_Flag);
	if(Loc_u16ErrorCount==TimeOut_Flag){
		Loc_enuStatus=RCC_enuTimeOut;
	}

	/*ENABLE HSI SW */
	RCC_CFGR_REG=(RCC_CFGR_REG&0xFFFFFFF0);

/*	CLR_BIT(RCC_CFGR_REG,0);
	CLR_BIT(RCC_CFGR_REG,1);*/

	/*WAIT TO CHECK SWS FOR HSI */
	while((GET_BIT(RCC_CFGR_REG,2))==0 && (GET_BIT(RCC_CFGR_REG,3))== 0&& (Loc_u16ErrorCount++)<TimeOut_Flag);
	if(Loc_u16ErrorCount==TimeOut_Flag){
		Loc_enuStatus=RCC_enuTimeOut;
	}
	return Loc_enuStatus;
}
RCC_tenuErrorStatus RCC_enuEnableHSE(void){
	u16 Loc_u16ErrorCount=0;
	RCC_tenuErrorStatus Loc_enuStatus=RCC_enuOK;
	/*reset reg value*/
	RCC_CR_REG=0x00000081;


	/*set HSEON*/
	/*RCC_CR_REG=(RCC_CR_REG&0xFFF0FFFF)|0x00010000*/
		SET_BIT(RCC_CR_REG,16);


	/*wait until HSIRDY*/
	while((GET_BIT(RCC_CR_REG,17))== 0 && (Loc_u16ErrorCount++)<TimeOut_Flag);
	if(Loc_u16ErrorCount==TimeOut_Flag){
		Loc_enuStatus=RCC_enuTimeOut;
	}

	/*ENABLE HSE SW */
	/*RCC_CFGR_REG=(RCC_CFGR_REG&0xFFFFFFF0)|0X00000001*/
	SET_BIT(RCC_CFGR_REG,0);
	CLR_BIT(RCC_CFGR_REG,1);
	/*WAIT TO CHECK SWS FOR HSE */
	while((GET_BIT(RCC_CFGR_REG,2))==1 && (GET_BIT(RCC_CFGR_REG,3))== 0 && (Loc_u16ErrorCount++)<TimeOut_Flag);
	if(Loc_u16ErrorCount==TimeOut_Flag){
		Loc_enuStatus=RCC_enuTimeOut;
	}
	return Loc_enuStatus;

}

RCC_tenuErrorStatus RCC_enuEnablePLL(RCC_tenuPLLSrcCLKSelection RCC_enuSelect,u8 PLLN,u8 PLLM,u8 PLLP,u8 PLLQ){
	u16 Loc_u16ErrorCount=0;
	RCC_tenuErrorStatus Loc_enuStatus=RCC_enuOK;
	/*select source of pll clock*/
	if(RCC_enuSelect==RCC_enuHSE){
		RCC_enuEnableHSE();
		/*enable source pll*/
		SET_BIT(RCC_PLLCFGR_REG,22);
	}else if(RCC_enuSelect==RCC_enuHSI){
		RCC_enuEnableHSI();
		/*enable source pll*/
		CLR_BIT(RCC_PLLCFGR_REG,22);
	}


	/*turn pll off to configure it */
	CLR_BIT(RCC_CR_REG,24);

	/*config PLL parameters*/

	/*clearing 6->14 bits and adding value*/
	RCC_PLLCFGR_REG=(RCC_PLLCFGR_REG&0xFFFFC03F)|(PLLN<<6);

	/*clearing 0->5 bits and adding value*/
	RCC_PLLCFGR_REG=(RCC_PLLCFGR_REG&0xFFFFFFC0)|(PLLM<<0);

	/*clearing 16,17 bits and adding value*/
	RCC_PLLCFGR_REG=(RCC_PLLCFGR_REG&0xFFF3FFFF)|(PLLP<<16);

	/*clearing 24->27 bits and adding value*/
	RCC_PLLCFGR_REG=(RCC_PLLCFGR_REG&0xF0FFFFFF)|(PLLQ<<24);

	/*turn pll on*/
	SET_BIT(RCC_CR_REG,24);


	/*wait until PLLRDY*/
	while((GET_BIT(RCC_CR_REG,25))== 0 && (Loc_u16ErrorCount++)<TimeOut_Flag);
	if(Loc_u16ErrorCount==TimeOut_Flag){
		Loc_enuStatus=RCC_enuTimeOut;
	}

	/*ENABLE PLL SW */
	/*RCC_CFGR_REG=(RCC_CFGR_REG&0xFFFFFFF0)|0X00000010*/
	SET_BIT(RCC_CFGR_REG,1);
	CLR_BIT(RCC_CFGR_REG,0);

	/*WAIT TO CHECK SWS FOR PLL */
	while((GET_BIT(RCC_CFGR_REG,2))==0 && (GET_BIT(RCC_CFGR_REG,3))== 1 && (Loc_u16ErrorCount++)<TimeOut_Flag);
	if(Loc_u16ErrorCount==TimeOut_Flag){
		Loc_enuStatus=RCC_enuTimeOut;
	}
	return Loc_enuStatus;
}


void RCC_enuEnableDisAHB1ClkPerpheral(RCC_tenuAHB1PeripheralEn RCC_enuPeripheralSelection,RCC_tenuEnDisPeripheral	RCC_enuSelect){
		/*set peripheral pin to enable clk*/
		if(RCC_enuSelect==RCC_enuEnPeripheral){
			SET_BIT(RCC_AHB1ENR_REG,RCC_enuPeripheralSelection);
			/*clear peripheral pin to disable clk*/
		}else if(RCC_enuSelect==RCC_enuDisablePeripheral){
			CLR_BIT(RCC_AHB1ENR_REG,RCC_enuPeripheralSelection);
		}

}



