/*
 * NVIC.c
 *
 *  Created on: Mar 3, 2023
 *      Author: alaa
 */

/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/
#include "NVIC_Private.h"
#include "NVIC.h"

NVIC_tenuErrorStatus NVIC_EnableIRQ(NVIC_enuIRQ_t Cpy_u8IRQn) {
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;
	u8 Loc_u8BitLocation = 0, Loc_u8RegLocation = 0;

	Loc_u8BitLocation = Cpy_u8IRQn % 32;
	Loc_u8RegLocation = Cpy_u8IRQn / 32;

	/* ENABLE THE INTERRUPT */
	(NVIC_ISER_BASE + Loc_u8RegLocation) |= (1 << Loc_u8BitLocation);

	if ((NVIC_ISER_BASE + Loc_u8RegLocation) & (1 << Loc_u8BitLocation)) {
		Loc_enuStatus = NVIC_enuOK;
	} else {
		Loc_enuStatus = NVICenuNotOK;
	}

	return Loc_enuStatus;
}
NVIC_tenuErrorStatus NVIC_DisableIRQ(NVIC_enuIRQ_t Cpy_u8IRQn) {
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;
	u8 Loc_u8BitLocation = 0, Loc_u8RegLocation = 0;

	Loc_u8BitLocation = Cpy_u8IRQn % 32;
	Loc_u8RegLocation = Cpy_u8IRQn / 32;

	/* DISABLE INTERRUPT */
	(NVIC_ICER_BASE + Loc_u8RegLocation) |= (1 << Loc_u8BitLocation);
	if ((NVIC_ICER_BASE + Loc_u8RegLocation) & (1 << Loc_u8BitLocation) == 0) {
		Loc_enuStatus = NVIC_enuOK;
	} else {
		Loc_enuStatus = NVICenuNotOK;
	}

	return Loc_enuStatus;
}
NVIC_tenuErrorStatus NVIC_SetPending(NVIC_enuIRQ_t Cpy_u8IRQn) {
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;
	u8 Loc_u8BitLocation = 0, Loc_u8RegLocation = 0;

	Loc_u8BitLocation = Cpy_u8IRQn % 32;
	Loc_u8RegLocation = Cpy_u8IRQn / 32;

	(NVIC_ISPR_BASE + Loc_u8RegLocation) |= (1 << Loc_u8BitLocation);
	if ((NVIC_ISPR_BASE + Loc_u8RegLocation) & (1 << Loc_u8BitLocation)) {
		Loc_enuStatus = NVIC_enuOK;
	} else {
		Loc_enuStatus = NVICenuNotOK;
	}

	return Loc_enuStatus;
}
NVIC_tenuErrorStatus NVIC_ClearPending(NVIC_enuIRQ_t Cpy_u8IRQn) {
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;
	u8 Loc_u8BitLocation = 0, Loc_u8RegLocation = 0;

	Loc_u8BitLocation = Cpy_u8IRQn % 32;
	Loc_u8RegLocation = Cpy_u8IRQn / 32;

	(NVIC_ICPR_BASE + Loc_u8RegLocation) |= (1 << Loc_u8BitLocation);
	if ((NVIC_ICPR_BASE + Loc_u8RegLocation) & (1 << Loc_u8BitLocation) == 0) {
		Loc_enuStatus = NVIC_enuOK;
	} else {
		Loc_enuStatus = NVICenuNotOK;
	}

	return Loc_enuStatus;
}

NVIC_tenuErrorStatus NVIC_GetActiveStatus(NVIC_enuIRQ_t Cpy_u8IRQn,
		u8* ADD_pu8Status) {
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;
	u8 Loc_u8BitLocation = 0, Loc_u8RegLocation = 0;

	Loc_u8BitLocation = Cpy_u8IRQn % 32;
	Loc_u8RegLocation = Cpy_u8IRQn / 32;

	if ((NVIC_IABR_BASE + Loc_u8RegLocation) & (1 << Loc_u8BitLocation)) {
		*ADD_pu8Status = NVIC_IRQ_Active;
	} else {
		*ADD_pu8Status = NVIC_IRQ_NotActive;
	}

	return Loc_enuStatus;
}
NVIC_tenuErrorStatus NVIC_SetPriority(NVIC_enuIRQ_t Cpy_u8IRQn,
		u8 Cpy_u8GroupPriority) {
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;
	u8 Loc_u8BitLocation = 0, Loc_u8RegLocation = 0;

	Loc_u8BitLocation = Cpy_u8IRQn % 4;
	Loc_u8RegLocation = Cpy_u8IRQn / 4; /////or /32 not sure

	(NVIC_IPR_BASE + Loc_u8RegLocation) |= Cpy_u8GroupPriority;

	return Loc_enuStatus;
}
NVIC_tenuErrorStatus NVIC_GenerateSwIRQ(NVIC_enuIRQ_t Cpy_u8IRQn) {
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;

	if (Cpy_u8IRQn > NVIC_INT_NUMBERS) {
		Loc_enuStatus = NVIC_enuWrongValue;
	} else {
		NVIC_STIR &= 0XFFFFFF00;
		NVIC_STIR |= Cpy_u8IRQn;
	}

	return Loc_enuStatus;

}
NVIC_tenuErrorStatus NVIC_GetPriority(NVIC_enuIRQ_t Cpy_u8IRQn,
		u32* Add_u32Priority) {
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;
	u8 Loc_u8BitLocation = 0, Loc_u8RegLocation = 0;

	if (Cpy_u8IRQn > NVIC_INT_NUMBERS) {
		Loc_enuStatus = NVIC_enuWrongValue;
	} else {

		Loc_u8BitLocation = Cpy_u8IRQn % 4;
		Loc_u8RegLocation = Cpy_u8IRQn / 4; /////or /32 not sure

		*Add_u32Priority = ((NVIC_IPR_BASE + Loc_u8RegLocation)
				>> (4 * Loc_u8BitLocation));
	}

	return Loc_enuStatus;
}

NVIC_tenuErrorStatus NVIC_SetSubPriority(
		NVIC_enuPriorityGroup_t Cpy_u8GroupPriority) {
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;


	/*enable writing to reg*/
	NVIC_AIRCR |= (NVIC_VECTKEY_EN << 16);

	NVIC_AIRCR &= SUBGROUP_CLR_MASK;
	NVIC_AIRCR |= Cpy_u8GroupPriority;

	return Loc_enuStatus;

}

NVIC_tenuErrorStatus NVIC_GetEncodingPriority(u8 Cpy_u8NumberOfSubGroup, u8 Cpy_u8SubGroupPriority,
		u8 Cpy_u8PreemptionPriority,u32* Add_u32ReturnPriority){
	NVIC_tenuErrorStatus Loc_enuStatus = NVIC_enuOK;
	*Add_u32ReturnPriority=0;
if(Cpy_u8NumberOfSubGroup>4){
	Loc_enuStatus = NVIC_enuWrongValue;
}else{
	*Add_u32ReturnPriority|=(Cpy_u8SubGroupPriority<<4);
	*Add_u32ReturnPriority|=(Cpy_u8PreemptionPriority<<(4+Cpy_u8NumberOfSubGroup));
}

	return Loc_enuStatus;

}
