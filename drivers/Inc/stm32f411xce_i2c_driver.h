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



#endif /* INC_STM32F411XCE_I2C_DRIVER_H_ */
