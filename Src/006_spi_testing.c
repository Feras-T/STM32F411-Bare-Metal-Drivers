/*
 * 006_spi_testing.c
 *
 *  Created on: Jul 27, 2026
 *      Author: SV
 */

//Learning notes, The AF06 and AF05 related to one same gourbe so you may fine spi2 written
//in af06 but it is in AF05

// PA6 SPI1_MISO
// PA7 SPI1_MOSI
// PA5 SPI1_SCLK
// PA4 SPI1_NSS
//ALT Fun mode : AF05

#include "stm32f411xx.h"

void SPI_GPIOInit(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx =GPIOA;
	SPIPins.GPIO_PinConfig.GPIO_PinMode =GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode= 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType =GPIO_OP_TYPE_PP;        //use pushpull open drain is not required for SPI its just required for I2c  because the specification said that the i2c has to be open drain
	SPIPins.GPIO_PinConfig.GPIO_PinPUPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST; 			//Dosent matter for this application.

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPIPins); // at gpio drive its init the pin by goint to its adress and do gpio_init function

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&SPIPins);


	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&SPIPins);

}
