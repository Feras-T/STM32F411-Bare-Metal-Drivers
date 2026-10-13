/*
 * stm32f411xce_i2c_driver.h
 *
 *  Created on: Sep 29, 2026
 *      Author: SV
 */

#ifndef INC_STM32F411XCE_I2C_DRIVER_H_
#define INC_STM32F411XCE_I2C_DRIVER_H_

#include "stm32f411xx.h"

/*
 * Configuration structure for I2C peripheral
 */
typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t  I2C_DeviceAddress; //this will be initialize by the user so no pre-modification
	uint8_t  I2C_ACKControl;
	uint8_t  I2C_FMDutyCycle;

}I2C_Config_t;

/*
 * Handle structure for I2C peripheral
 */
typedef struct
{
	I2C_RegDef_t  *pI2Cx;
	I2C_Config_t  I2C_Config;


}I2C_Handle_t;

/*
 * @I2C_SCLSpeed
 * You can create any speed value between 100khz and 400khz
 */
#define I2C_SCL_SPEED_SM	100000 		//Normal I2C Speed
#define I2C_SCL_SPEED_FM4K	400000		//Fast I2C Speed
#define I2C_SCL_SPEED_FM2K	200000

/*
 * @I2C_ACK
 * Note ACK is disable by default
 * To Enable ACK it shall be  1
 * To Disable ACK it shall be 0
 *
 */
#define I2C_ACK_EN		1
#define I2C_ACK_DI		0


/*
 * @I2C_FMDutyCycle
 * Duty cycle in data sheet
 * might be 2 or 16/9 (page 499) Clock control register CCR
 * If you want duty cycle 2 (DUTY bit in CCR register) shall be    0
 * If you want Duty cycle 16/9 (DUTY bit in CCR register) shall be 1
 */
#define I2C_FM_DUTY_2			0
#define I2C_FM_DUTY_16_9		1


/******************************************************************************************
*                         APIs supported by this driver
*     For more information about the APIs check the function definitions
******************************************************************************************/

/*
 * Peripheral Clock setup.
 */
void I2C_PeriClockControl(I2C_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 * Init and De-init.
 */
void I2C_Init(I2C_Handle_t *pSPIHandle);  // (void), the parameters will be written later
void I2C_DeInit(I2C_RegDef_t *pSPIx);

/*
 * Data Send and Receive.
 */



/*
 * IRQ Configuration and ISR Handling.
 */
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);			// Message the interrupt ([config]enable and give the priority).
void I2C_IRQPriorityConfig(uint32_t IRQNumber, uint32_t IRQPriority);


/*
 * flag status.
 */

uint8_t I2C_GETFlagStatus(I2C_RegDef_t *pSPIx , uint32_t FlagName);

/*
 * Other Peripheral Control APIs.
 */
void I2C_PeripheralControl(I2C_RegDef_t *pSPIx, uint8_t EnorDi);
uint8_t I2C_GETFlagStatus(I2C_RegDef_t *pSPIx , uint32_t FlagName);


/*
 * Application Callback.
 */

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv);


#endif /* INC_STM32F411XCE_I2C_DRIVER_H_ */
