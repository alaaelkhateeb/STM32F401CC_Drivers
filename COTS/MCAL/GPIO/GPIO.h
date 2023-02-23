/*
 * GPIO.h
 *
 *  Created on: Feb 17, 2023
 *      Author: alaa
 */


/*******************************************************************************
 ***                            Types Declaration                            ***
 ******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_
								/*Mode Selection */
#define GPIO_MODE_OUTPUT_Digital		0b01
#define GPIO_MODE_AF					0b10
#define GPIO_MODE_INTPUT_Digital		0b00

							/*push(1bit) pull(2bits) mode(2bits)*/
#define GPIO_MODE_OUTPUT_PP				0b00001
#define GPIO_MODE_OUTPUT_PP_PU			0b00101
#define GPIO_MODE_OUTPUT_PP_PD			0b01001

#define GPIO_MODE_OUTPUT_OD				0b10001
#define GPIO_MODE_OUTPUT_OD_PU			0b10101
#define GPIO_MODE_OUTPUT_OD_PD			0b11001



#define GPIO_MODE_AF_PP					0b00010
#define GPIO_MODE_AF_PP_PU				0b00110
#define GPIO_MODE_AF_PP_PD				0b01010

#define GPIO_MODE_AF_OD					0b10010
#define GPIO_MODE_AF_OD_PU				0b10110
#define GPIO_MODE_AF_OD_PD				0b11010



#define GPIO_MODE_INPUT_Floating		0b00000
#define GPIO_MODE_INPUT_OD_PU			0b00100
#define GPIO_MODE_INPUT_OD_PD			0b01000

#define GPIO_MODE_Analog				0b00011
					/*Speed Selection */

#define GPIO_OUTPUT_SPEED_LOW			0b00
#define GPIO_OUTPUT_SPEED_MEDIUM		0b01
#define GPIO_OUTPUT_SPEED_HIGH			0b10
#define GPIO_OUTPUT_SPEED_VHIGH			0b11

typedef enum {
	GPIO_enuOK = 0,
	GPIOenuNotOK,
	GPIO_enuTimeOut,
	GPIO_enuWrongValue,
	GPIO_NullPtr

} GPIO_tenuErrorStatus;

typedef enum {
	GPIO_PORTA = 0,
	GPIO_PORTB,
	GPIO_PORTC
} GPIO_tenuPortId;

typedef enum {
	GPIO_PIN0 = 0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15,
	GPIO_PINNumbers
} GPIO_tenuPinNumber;


typedef enum {
	GPIO_Low=0,
	GPIO_High
} GPIO_tenuValue;

typedef struct{
	void* Port;
	u8 Pin;
	u32 ModeSelect;
	u8 OutPutValue;
	u8 Speed;
}GPIO_tInit;
///////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 ****                    Functions Prototypes                              ****
 ******************************************************************************/

/******************************************************************************
 * @brief 	  			 GPIO_Init (for initialize certain pin in port with parameter)	.
 * @param 					PTR to Init struct
 * @return 					GPIO_tenuErrorStatus
 *************************************************************************** */
GPIO_tenuErrorStatus GPIO_Init(GPIO_tInit* GPIO_Init);
/******************************************************************************
 * @brief 	  			 GPIO_SetPinMode (for setting pin mode )	.
 * @param 					Port :pin in it
 * 							Pin:to set its mode
 * 							Mode:between Input/out OD PP....
 * 							Speed
 * @return 					GPIO_tenuErrorStatus
 *************************************************************************** */
GPIO_tenuErrorStatus GPIO_SetPinMode(void* PortSelection,GPIO_tenuPinNumber PinSelection ,u8 ModeSelection,u8 SpeedSelection);
/******************************************************************************
 * @brief 	  			 GPIO_SetPinValue (for setting Output Pin value )	.
 * @param 					Port :pin in it
 * 							Pin:to set its value
 * 							Value :High or Low
 * @return 					GPIO_tenuErrorStatus
 *************************************************************************** */
GPIO_tenuErrorStatus GPIO_SetPinValue(void* PortSelection,GPIO_tenuPinNumber PinSelection ,GPIO_tenuValue	valueSelection);
/******************************************************************************
 * @brief 	  			 GPIO_GetPinValue (for setting input Pin value )	.
 * @param 					Port :pin in it
 * 							Pin:to get value from
 * 							PTR :to hold the value
 * @return 					GPIO_tenuErrorStatus
 *************************************************************************** */
GPIO_tenuErrorStatus GPIO_GetPinValue(void* PortSelection,GPIO_tenuPinNumber PinSelection ,u8* Add_u32Data);
/******************************************************************************
 * @brief 	  			 GPIO_SetPortMode (for setting port mode )	.
 * @param 					Port :to set mode
 * 							Mode:between Input/out OD PP....
 * 							Speed
 * @return 					GPIO_tenuErrorStatus
 *************************************************************************** */
GPIO_tenuErrorStatus GPIO_SetPortMode(void* PortSelection,u8 ModeSelection,u8 SpeedSelection);
/******************************************************************************
 * @brief 	  			 GPIO_SetPortValue (for setting Output port value )	.
 * @param 					Port :to set value
 * 							Value :High or Low
 * @return 					GPIO_tenuErrorStatus
 *************************************************************************** */
GPIO_tenuErrorStatus GPIO_SetPortValue(void* PortSelection,GPIO_tenuValue valueSelection);
GPIO_tenuErrorStatus GPIO_GetPortValue(void* PortSelection,u32* Add_u32Data);
#endif /* GPIO_H_ */



