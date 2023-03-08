/*
 * GPIO.c
 *
 *  Created on: Feb 17, 2023
 *      Author: alaa
 */

/*LIB Layer*/
#include "Std_types.h"
#include "Bit_math.h"

/*MCAL*/
#include "GPIO_Private.h"
#include "GPIO.h"

#define OFFSET 2
#define RegOffset 16

GPIO_tenuErrorStatus GPIO_Init(GPIO_tInit* GPIO_Init) {
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;
	u32 Loc_u32RegTemp = 0;
	u32 Mode = 0, OutMode = 0, InMode = 0, ModeSelection = 0;
	/*push(1bit) pull(2bits) mode(2bits)*/
	ModeSelection = GPIO_Init->ModeSelect;
	Mode = ModeSelection & 0x00000003;
	OutMode = ModeSelection & 0x00000010;
	InMode = ModeSelection & 0x0000000C;

	Loc_u32RegTemp = ((GPIOx_t*) GPIO_Init->Port)->MODER;
	Loc_u32RegTemp |= (Mode << (GPIO_Init->Pin * OFFSET));
	((GPIOx_t*) GPIO_Init->Port)->MODER = Loc_u32RegTemp;

	Loc_u32RegTemp = ((GPIOx_t*) GPIO_Init->Port)->OTYPER;
	Loc_u32RegTemp |= (OutMode << GPIO_Init->Pin);
	((GPIOx_t*) GPIO_Init->Port)->OTYPER = Loc_u32RegTemp;

	Loc_u32RegTemp = ((GPIOx_t*) GPIO_Init->Port)->PUPDR;
	Loc_u32RegTemp |= (InMode << ((GPIO_Init->Pin) * OFFSET));
	((GPIOx_t*) GPIO_Init->Port)->PUPDR = Loc_u32RegTemp;

	//speed selection
	Loc_u32RegTemp = ((GPIOx_t*) GPIO_Init->Port)->OSPEEDR;
	Loc_u32RegTemp |= (GPIO_Init->Speed << ((GPIO_Init->Pin) * OFFSET));
	((GPIOx_t*) GPIO_Init->Port)->OSPEEDR = Loc_u32RegTemp;

	if ((GPIO_Init->OutPutValue == GPIO_High)
			&& (GPIO_Init->Pin < GPIO_PINNumbers)) {
		/*atomic set*/
		Loc_u32RegTemp = ((GPIOx_t*) GPIO_Init->Port)->BSRR;
		Loc_u32RegTemp |= (1 << GPIO_Init->Pin);
		/*outputdata*/
		((GPIOx_t*) GPIO_Init->Port)->BSRR = Loc_u32RegTemp;
		Loc_u32RegTemp = ((GPIOx_t*) GPIO_Init->Port)->ODR;
		Loc_u32RegTemp |= (1 << GPIO_Init->Pin);
		((GPIOx_t*) GPIO_Init->Port)->ODR = Loc_u32RegTemp;
	} else if ((GPIO_Init->OutPutValue == GPIO_Low)
			&& (GPIO_Init->Pin < GPIO_PINNumbers)) {
		Loc_u32RegTemp = ((GPIOx_t*) GPIO_Init->Port)->BSRR;
		Loc_u32RegTemp |= (1 << (GPIO_Init->Pin + RegOffset));

		((GPIOx_t*) GPIO_Init->Port)->BSRR = Loc_u32RegTemp;
		/*outputdata*/
		Loc_u32RegTemp = ((GPIOx_t*) GPIO_Init->Port)->ODR;

		Loc_u32RegTemp &= ~(1 << (GPIO_Init->Pin + RegOffset));
		((GPIOx_t*) GPIO_Init->Port)->ODR = Loc_u32RegTemp;
	} else if ((GPIO_Init->Pin > GPIO_PINNumbers)) {
		Loc_enuStatus = GPIO_enuWrongValue;
	}

	return Loc_enuStatus;
}
GPIO_tenuErrorStatus GPIO_SetPinMode(void* PortSelection,
		GPIO_tenuPinNumber PinSelection, u8 ModeSelection, u8 SpeedSelection) {
	u32 Loc_u32RegTemp = 0;
	u32 Mode = 0, OutMode = 0, InMode = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;

	/*push(1bit) pull(2bits) mode(2bits)*/
	Mode = ModeSelection & 0x00000003;
	OutMode = ModeSelection & 0x00000010;
	InMode = ModeSelection & 0x0000000C;

	Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->MODER;
	Loc_u32RegTemp |= (Mode << (PinSelection * OFFSET));
	((GPIOx_t*) PortSelection)->MODER = Loc_u32RegTemp;

	Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->OTYPER;
	Loc_u32RegTemp |= (OutMode << PinSelection);
	((GPIOx_t*) PortSelection)->OTYPER = Loc_u32RegTemp;

	Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->PUPDR;
	Loc_u32RegTemp |= (InMode << (PinSelection * OFFSET));
	((GPIOx_t*) PortSelection)->PUPDR = Loc_u32RegTemp;

	/*speed selection*/
	Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->OSPEEDR;
	Loc_u32RegTemp |= (SpeedSelection << (PinSelection * OFFSET));
	((GPIOx_t*) PortSelection)->OSPEEDR = Loc_u32RegTemp;

	return Loc_enuStatus;
}
GPIO_tenuErrorStatus GPIO_SetPinValue(void* PortSelection,
		GPIO_tenuPinNumber PinSelection, GPIO_tenuValue valueSelection) {
	u32 Loc_u32RegTemp = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;

	if ((valueSelection == GPIO_High) && (PinSelection < GPIO_PINNumbers)) {
		/*atomic set*/
		Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->BSRR;
		Loc_u32RegTemp |= (1 << PinSelection);
		/*outputdata*/
		((GPIOx_t*) PortSelection)->BSRR = Loc_u32RegTemp;
		Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->ODR;
		Loc_u32RegTemp |= (1 << PinSelection);
		((GPIOx_t*) PortSelection)->ODR = Loc_u32RegTemp;
	} else if ((valueSelection == GPIO_Low)
			&& (PinSelection < GPIO_PINNumbers)) {
		Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->BSRR;
		Loc_u32RegTemp |= (1 << (PinSelection + RegOffset));

		((GPIOx_t*) PortSelection)->BSRR = Loc_u32RegTemp;
		/*outputdata*/
		Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->ODR;

		Loc_u32RegTemp &= ~(1 << (PinSelection + RegOffset));
		((GPIOx_t*) PortSelection)->ODR = Loc_u32RegTemp;
	} else if ((PinSelection > GPIO_PINNumbers)) {
		Loc_enuStatus = GPIO_enuWrongValue;
	}

	return Loc_enuStatus;
}
GPIO_tenuErrorStatus GPIO_GetPinValue(void* PortSelection,
		GPIO_tenuPinNumber PinSelection, u8* Add_u32Data) {
	//u32 Loc_u32RegTemp = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;

	if (((GPIOx_t*) PortSelection)->IDR & (1 << PinSelection)) {
		*Add_u32Data = 1;
	} else {
		*Add_u32Data = 0;
	}

	return Loc_enuStatus;
}

GPIO_tenuErrorStatus GPIO_SetPortMode(void* PortSelection, u8 ModeSelection,
		u8 SpeedSelection) {
	u32 Loc_u32RegTemp = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;
	u32 Mode = 0, OutMode = 0, InMode = 0;
	u8 Loc_u8Count = 0;

	/*push(1bit) pull(2bits) mode(2bits)*/
	Mode = ModeSelection & 0x00000003;
	OutMode = ModeSelection & 0x00000010;
	InMode = ModeSelection & 0x0000000C;
	for (Loc_u8Count = 0; Loc_u8Count < GPIO_PINNumbers; Loc_u8Count++) {
		Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->MODER;
		Loc_u32RegTemp |= (Mode << (Loc_u8Count * OFFSET));
		((GPIOx_t*) PortSelection)->MODER = Loc_u32RegTemp;

		Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->OTYPER;
		Loc_u32RegTemp |= (OutMode << Loc_u8Count);
		((GPIOx_t*) PortSelection)->OTYPER = Loc_u32RegTemp;

		Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->PUPDR;
		Loc_u32RegTemp |= (InMode << (Loc_u8Count * OFFSET));
		((GPIOx_t*) PortSelection)->PUPDR = Loc_u32RegTemp;

		/*speed selection*/
		Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->OSPEEDR;
		Loc_u32RegTemp |= (SpeedSelection << (Loc_u8Count * OFFSET));
		((GPIOx_t*) PortSelection)->OSPEEDR = Loc_u32RegTemp;
	}

	return Loc_enuStatus;
}
GPIO_tenuErrorStatus GPIO_SetPortValue(void* PortSelection,
		GPIO_tenuValue valueSelection) {
	u32 Loc_u32RegTemp = 0;
	u8 Loc_u8Count = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;

	for (Loc_u8Count = 0; Loc_u8Count < GPIO_PINNumbers; Loc_u8Count++) {
		if ((valueSelection == GPIO_High)) {
			/*atomic set*/
			Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->BSRR;
			Loc_u32RegTemp |= (1 << Loc_u8Count);
			/*outputdata*/
			((GPIOx_t*) PortSelection)->BSRR = Loc_u32RegTemp;
			Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->ODR;
			Loc_u32RegTemp |= (1 << Loc_u8Count);
			((GPIOx_t*) PortSelection)->ODR = Loc_u32RegTemp;
		} else if ((valueSelection == GPIO_Low)
				&& (Loc_u8Count < GPIO_PINNumbers)) {
			Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->BSRR;
			Loc_u32RegTemp |= (1 << (Loc_u8Count + RegOffset));

			((GPIOx_t*) PortSelection)->BSRR = Loc_u32RegTemp;
			/*outputdata*/
			Loc_u32RegTemp = ((GPIOx_t*) PortSelection)->ODR;

			Loc_u32RegTemp &= ~(1 << (Loc_u8Count + RegOffset));
			((GPIOx_t*) PortSelection)->ODR = Loc_u32RegTemp;
		}
	}
	return Loc_enuStatus;
}
GPIO_tenuErrorStatus GPIO_GetPortValue(void* PortSelection, u32* Add_u32Data) {
	u32 Loc_u32RegTemp = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;
	return Loc_enuStatus;
}
