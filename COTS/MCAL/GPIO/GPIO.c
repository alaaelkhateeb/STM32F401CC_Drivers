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
#define RegOffset 15
GPIO_tenuErrorStatus GPIO_Init(void) {

}
GPIO_tenuErrorStatus GPIO_SetPinMode(GPIO_tenuPortId PortSelection,
		GPIO_tenuPinNumber PinSelection, u8 ModeSelection, u8 SpeedSelection) {
	u32 Loc_u32RegTemp = 0;
	u32 Mode = 0, OutMode = 0, InMode = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;

	/*push(1bit) pull(2bits) mode(2bits)*/
	Mode = ModeSelection & 0x00000003;
	OutMode = ModeSelection & 0x00000010;
	InMode = ModeSelection & 0x0000000C;

	switch (PortSelection) {
	case GPIO_PORTA:
		/*reset value */
		//GPIOA->MODER=(u32)0x0C000000;
		Loc_u32RegTemp = GPIOA->MODER;
		Loc_u32RegTemp |= (Mode << (PinSelection * OFFSET));
		GPIOA->MODER = Loc_u32RegTemp;

		Loc_u32RegTemp = GPIOA->OTYPER;
		Loc_u32RegTemp |= (OutMode << PinSelection);
		GPIOA->OTYPER = Loc_u32RegTemp;

		Loc_u32RegTemp = GPIOA->PUPDR;
		Loc_u32RegTemp |= (InMode << (PinSelection * OFFSET));
		GPIOA->PUPDR = Loc_u32RegTemp;
		/*speed selection*/
		Loc_u32RegTemp = GPIOA->OSPEEDR;
		Loc_u32RegTemp |= (SpeedSelection << (PinSelection * OFFSET));
		GPIOA->OSPEEDR = Loc_u32RegTemp;
		break;
	case GPIO_PORTB:
		/*reset value */
		//GPIOB->MODER=(u32)0x00000280;
		Loc_u32RegTemp = GPIOB->MODER;
		Loc_u32RegTemp |= (Mode << (PinSelection * OFFSET));
		GPIOB->MODER = Loc_u32RegTemp;

		Loc_u32RegTemp = GPIOB->OTYPER;
		Loc_u32RegTemp |= (OutMode << PinSelection);
		GPIOB->OTYPER = Loc_u32RegTemp;

		Loc_u32RegTemp = GPIOB->PUPDR;
		Loc_u32RegTemp |= (InMode << (PinSelection * OFFSET));
		GPIOB->PUPDR = Loc_u32RegTemp;
		/*speed selection*/
		Loc_u32RegTemp = GPIOB->OSPEEDR;
		Loc_u32RegTemp |= (SpeedSelection << (PinSelection * OFFSET));
		GPIOB->OSPEEDR = Loc_u32RegTemp;
		break;

	case GPIO_PORTC:
		/*reset value */
		//GPIOC->MODER=(u32)0x00000000;
		Loc_u32RegTemp = GPIOC->MODER;
		Loc_u32RegTemp |= (Mode << (PinSelection * OFFSET));
		GPIOC->MODER = Loc_u32RegTemp;

		Loc_u32RegTemp = GPIOC->OTYPER;
		Loc_u32RegTemp |= (OutMode << PinSelection);
		GPIOC->OTYPER = Loc_u32RegTemp;

		Loc_u32RegTemp = GPIOC->PUPDR;
		Loc_u32RegTemp |= (InMode << (PinSelection * OFFSET));
		GPIOC->PUPDR = Loc_u32RegTemp;

		/*speed selection*/
		Loc_u32RegTemp = GPIOC->OSPEEDR;
		Loc_u32RegTemp |= (SpeedSelection << (PinSelection * OFFSET));
		GPIOC->OSPEEDR = Loc_u32RegTemp;
		break;
	}

	return Loc_enuStatus;
}
GPIO_tenuErrorStatus GPIO_SetPinValue(GPIO_tenuPortId PortSelection,
		GPIO_tenuPinNumber PinSelection, GPIO_tenuValue valueSelection) {
	u32 Loc_u32RegTemp = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;
	switch (PortSelection) {
	case GPIO_PORTA:
		if ((valueSelection == GPIO_High) && (PinSelection < GPIO_PINNumbers)) {
			/*atomic set*/
			Loc_u32RegTemp = GPIOA->BSRR;
			Loc_u32RegTemp |= (1 << PinSelection);
			/*outputdata*/
			GPIOA->BSRR = Loc_u32RegTemp;
			Loc_u32RegTemp = GPIOA->ODR;
			Loc_u32RegTemp |= (1 << PinSelection);
			GPIOA->ODR = Loc_u32RegTemp;
		} else if ((valueSelection == GPIO_Low)
				&& (PinSelection < GPIO_PINNumbers)) {
			Loc_u32RegTemp = GPIOA->BSRR;
			Loc_u32RegTemp |= (1 << (PinSelection + RegOffset));

			GPIOA->BSRR = Loc_u32RegTemp;
			/*outputdata*/
			Loc_u32RegTemp = GPIOA->ODR;

			Loc_u32RegTemp &= ~(1 << (PinSelection + RegOffset));
			GPIOA->ODR = Loc_u32RegTemp;
		} else if ((PinSelection > GPIO_PINNumbers)) {
			Loc_enuStatus = GPIO_enuWrongValue;
		}
		break;
	case GPIO_PORTB:
		if ((valueSelection == GPIO_High) && (PinSelection < GPIO_PINNumbers)) {
			/*atomic set*/
			Loc_u32RegTemp = GPIOB->BSRR;
			Loc_u32RegTemp |= (1 << PinSelection);

			GPIOB->BSRR = Loc_u32RegTemp;
			/*outputdata*/
			Loc_u32RegTemp = GPIOB->ODR;
			Loc_u32RegTemp |= (1 << PinSelection);
			GPIOB->ODR = Loc_u32RegTemp;
		} else if ((valueSelection == GPIO_Low)
				&& (PinSelection < GPIO_PINNumbers)) {
			Loc_u32RegTemp = GPIOB->BSRR;
			Loc_u32RegTemp |= (1 << (PinSelection + RegOffset));

			GPIOB->BSRR = Loc_u32RegTemp;
			/*outputdata*/
			Loc_u32RegTemp = GPIOB->ODR;

			Loc_u32RegTemp &= ~(1 << (PinSelection + RegOffset));
			GPIOB->ODR = Loc_u32RegTemp;
		} else if ((PinSelection > GPIO_PINNumbers)) {
			Loc_enuStatus = GPIO_enuWrongValue;
		}
		break;

	case GPIO_PORTC:
		if ((valueSelection == GPIO_High) && (PinSelection < GPIO_PINNumbers)) {
			/*atomic set*/
			Loc_u32RegTemp = GPIOC->BSRR;
			Loc_u32RegTemp |= ((u32) 1 << PinSelection);
			GPIOC->BSRR = Loc_u32RegTemp;
			//GPIOC->BSRR |= ((u32)1 << PinSelection);
			/*outputdata*/
			Loc_u32RegTemp = GPIOC->ODR;
			Loc_u32RegTemp |= (1 << PinSelection);
			GPIOC->ODR = Loc_u32RegTemp;
		} else if ((valueSelection == GPIO_Low)
				&& (PinSelection < GPIO_PINNumbers)) {
			Loc_u32RegTemp = GPIOC->BSRR;
			Loc_u32RegTemp |= (1 << (PinSelection + RegOffset));
			GPIOC->BSRR = Loc_u32RegTemp;
			/*outputdata*/
			Loc_u32RegTemp = GPIOC->ODR;
			Loc_u32RegTemp &= ~(1 << (PinSelection + RegOffset));
			GPIOC->ODR = Loc_u32RegTemp;
		} else if ((PinSelection > GPIO_PINNumbers)) {
			Loc_enuStatus = GPIO_enuWrongValue;
		}
		break;
	}

	return Loc_enuStatus;
}
GPIO_tenuErrorStatus GPIO_GetPinValue(GPIO_tenuPortId PortSelection,
		GPIO_tenuPinNumber PinSelection, u8* Add_u32Data) {
	//u32 Loc_u32RegTemp = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;

	switch (PortSelection) {
	case GPIO_PORTA:

		if(GPIOA->IDR & (1<<PinSelection)) {
			*Add_u32Data=1;
		}else{
			*Add_u32Data=0;
		}
		break;
	case GPIO_PORTB:
		if(GPIOB->IDR & (1<<PinSelection)) {
			*Add_u32Data=1;
		}else{
			*Add_u32Data=0;
		}
		break;

	case GPIO_PORTC:
		if(GPIOC->IDR & (1<<PinSelection)) {
			*Add_u32Data=1;
		}else{
			*Add_u32Data=0;
		}
	//	*Add_u32Data= GET_BIT(GPIOC->IDR , Add_u32Data );
		break;
	}

	return Loc_enuStatus;
}

GPIO_tenuErrorStatus GPIO_SetPortMode(GPIO_tenuPortId PortSelection,
		u8 ModeSelection) {
	u32 Loc_u32RegTemp = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;
	return Loc_enuStatus;
}
GPIO_tenuErrorStatus GPIO_SetPortValue(GPIO_tenuPortId PortSelection,
		GPIO_tenuValue valueSelection) {
	u32 Loc_u32RegTemp = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;
	return Loc_enuStatus;
}
GPIO_tenuErrorStatus GPIO_GetPortValue(GPIO_tenuPortId PortSelection,
		u32* Add_u32Data) {
	u32 Loc_u32RegTemp = 0;
	GPIO_tenuErrorStatus Loc_enuStatus = GPIO_enuOK;
	return Loc_enuStatus;
}
