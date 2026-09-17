/*
 * stm32f411_gpio_driver.h
 *
 *       Author: Eng. Fersa Abuhaimed.
 *      **************************************************************
 *      (Note/ The using data sheet rm0383 and include with repository)
 *      **************************************************************
 */

#ifndef INC_STM32F411_GPIO_DRIVER_H_
#define INC_STM32F411_GPIO_DRIVER_H_

#include "stm32f411xx.h"

/*
 * This is the Configuration structure for GPIO pin
 */

typedef struct
{
	uint8_t GPIO_PinNumber;						    /*!< possible values from @GPIO_PIN_NUMBERS>*/
	uint8_t GPIO_PinMode;							/*!< possible values from @GPIO_PIN_MODES>*/
	uint8_t GPIO_PinSpeed;							/*!< possible values from @GPIO_PIN_SPEED>*/
	uint8_t GPIO_PinPUPdControl;					/*!< possible values from @GPIO_PIN_PuPd>*/
	uint8_t GPIO_PinOPType;							/*!< possible values from @GPIO_PIN_OPType>*/
	uint8_t GPIO_PinAltFunMode;						/*!< possible values from @GPIO_PIN_ALT_FUN_MODES>*/
}GPIO_PinConfig_t;

/*
 * This is a Handle strucure for a GPIO pin
 */

typedef struct
{
	GPIO_RegDef_t *pGPIOx;							/*!<This Holds the base address of the GPIO port to wich the pin belongs >*/
	GPIO_PinConfig_t GPIO_PinConfig;			    /*!<This Holds the base address of the GPIO port to wich the pin belongs >*/
}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin numbers
 */

#define GPIO_PIN_NO_0			0
#define GPIO_PIN_NO_1			1
#define GPIO_PIN_NO_2			2
#define GPIO_PIN_NO_3			3
#define GPIO_PIN_NO_4			4
#define GPIO_PIN_NO_5			5
#define GPIO_PIN_NO_6			6
#define GPIO_PIN_NO_7			7
#define GPIO_PIN_NO_8			8
#define GPIO_PIN_NO_9			9
#define GPIO_PIN_NO_10			10
#define GPIO_PIN_NO_11			11
#define GPIO_PIN_NO_12			12
#define GPIO_PIN_NO_13			13
#define GPIO_PIN_NO_14			14
#define GPIO_PIN_NO_15			15

/*
 ****************************************************************************
 * We wrote these peripheral macros here instead of in the main MCU driver
 * because they are GPIO-specific configurations, not general MCU information.
 ****************************************************************************
 */

/*
 ****************
 * GPIO_PIN_MODES
 *****************
 */

/*
 * GPIO pin Possible modes.
 * This is main types of Pin modes (0) 00 input mode, (1) 01 output mode, (2) 10 Alternate, (3) 11 Analog mode.
 * The remianing Macros are for intrrupt
 * GPIO port mode register (GPIOx_MODER)
 */

#define GPIO_MODE_IN		 0			//(0) 00 input mode                          Its written in decimal but the prosseor will deal with it as binary 00
#define GPIO_MODE_OUT 		 1			//(1) 01 output mode						 Its written in decimal but the prosseor will deal with it as binary 00
#define GPIO_MODE_ALTFN		 2			//(2) 10 Alternate							 Its written in decimal but the prosseor will deal with it as binary 00
#define GPIO_MODE_ANALOG     3			//(3) 11 Analog mode						 Its written in decimal but the prosseor will deal with it as binary 00

#define GPIO_MODE_IT_FT      4			//Input Falling Edge						 Its written in decimal but the prosseor will deal with it as binary 00
#define GPIO_MODE_IT_RT      5			//Input Rising Edge					    	 Its written in decimal but the prosseor will deal with it as binary 00
#define GPIO_MODE_IT_RFT     6			//Input Raising Edge  Falling Edge			 Its written in decimal but the prosseor will deal with it as binary 00


/*
 *
 * GPIO pin Possible Output Types.
 * GPIO Port OutPut type register (GPIOx_OTYPER)
 */

#define GPIO_OP_TYPE_PP			0 		//GPIO OutPut Type PushPull.
#define GPIO_OP_TYPE_OD			1		//GPIO Output Type Open Drain

/*
 * GPIO_PIN_SPEED
 * GPIO pin Possible Output Speeds.
 * GPIO port output speed register (GPIOx_OSPEEDR)
 */

#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

/*
 * GPIO_PIN_PuPd
 * GPIO pin Pull up AND Pull down configuration macros.
 * GPIO port pull-up/pull-down register (GPIOx_PUPDR)
 */

#define GPIO_NO_PUPD		0				//GPIO NO Pull up No Pull down register.
#define GPIO_PIN_PU		    1 				//GPIO PIN Pull up register.
#define GPIO_PIN_PD			2 				//GPIO PIN Pull down register.




/******************************************************************************************
*                         APIs supported by this driver
*     For more information about the APIs check the function definitions
******************************************************************************************/

/*
 * Peripheral Clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);  // (void), the parameters will be written later
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);//only one bit 1,0 so unint8_t (the smallest uint value in c
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx); // beacuse each port has 16 bit
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t value); // to make value 1,0 , SET or RESET
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);

/*
 * IRQ Configuration and ISR Handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);			// message the intrrupt ([config]enable and give the prioraty)
//void GPIO_IRQPriorityConfig(uint8_t IRQPriority);
void GPIO_IRQPriorityConfig(uint32_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t pinNumber);		//To prossesor that interrupt when it comes




#endif /* INC_STM32F411_GPIO_DRIVER_H_ */
