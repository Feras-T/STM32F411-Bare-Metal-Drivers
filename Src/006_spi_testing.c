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


#include <string.h>
#include "stm32f411xx.h"

void SPI1_GPIOInit(void)
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
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	//GPIO_Init(&SPIPins);


	//NSS
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	//GPIO_Init(&SPIPins); // GPIO_Init writtenn in driver

}

void SPI1_Inits(void)
{


	//Review the type def and how mutiple tyedef works
	SPI_Handle_t SPI1handle;   //SPI1_Handle the varible that i want SPI_Handle_t do all of its rhings iside it in  SPI1_Handle (check it)
	 SPI1handle.pSPIx = SPI1;
	SPI1handle.SPIConfig.SPI_BusConfig= SPI_BUS_CONFIG_FD;
	SPI1handle.SPIConfig.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
	SPI1handle.SPIConfig.SPI_SclkSpeed= SPI_SCLK_SPEED_DIV2;
	SPI1handle.SPIConfig.SPI_DFF=SPI_DFF_8BITS;
	SPI1handle.SPIConfig.SPI_CPOL=SPI_CPOL_LOW;
	SPI1handle.SPIConfig.SPI_SSM=SPI_SSM_EN; //Softwer slave managemnt enabled for NSS pin
	SPI1handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1handle.SPIConfig.SPI_SSM = SPI_SSM_EN;
	SPI_Init(&SPI1handle);


}

int main(void)
{
	char user_data[]="Hello World";

	//This function is used to initialize the GPIO pins to behave like SPI1 pins
	SPI1_GPIOInit();

	//This function is used to initialize the SPI1preiphral parameters
	SPI1_Inits();

	SPI_SSIConfig(SPI1, ENABLE);

	//enable the SPI2 Peripheral
	//All registers configuration recomendded beforeenable SPI prehipral as we did
	SPI_PeripheralControl(SPI1,ENABLE); //We have to enavle The spi to transmite (the SPE in Control register 1)


	//TO send data
	SPI_SendData(SPI1, (uint8_t*)user_data, strlen(user_data));

	SPI_PeripheralControl(SPI1,DISABLE); //After sending the data, disable the prepheral

	while(1);

	return(0);


}
//
///*
// * 006_spi_testing.c
// *
// * SPI1 transmit test
// *
// * PA5  -> SPI1_SCLK
// * PA6  -> SPI1_MISO
// * PA7  -> SPI1_MOSI
// * PA4  -> SPI1_NSS
// *
// * Alternate function = AF5
// */
//
//#include <string.h>
//#include "stm32f411xx.h"
//
//
///*
// * Initialize GPIO pins used by SPI1
// */
//void SPI1_GPIOInit(void)
//{
//    GPIO_Handle_t SPIPins;
//
//    SPIPins.pGPIOx = GPIOA;
//
//    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
//    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
//    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
//    SPIPins.GPIO_PinConfig.GPIO_PinPUPdControl = GPIO_NO_PUPD;
//    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//
//
//    /*
//     * PA5 -> SPI1_SCLK
//     */
//    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
//    GPIO_Init(&SPIPins);
//
//
//    /*
//     * PA7 -> SPI1_MOSI
//     */
//    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
//    GPIO_Init(&SPIPins);
//
//
//    /*
//     * PA6 -> SPI1_MISO
//     *
//     * Not required for transmit-only testing.
//     */
//    /*
//    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
//    GPIO_Init(&SPIPins);
//    */
//
//
//    /*
//     * PA4 -> SPI1_NSS
//     *
//     * Not needed because we are using
//     * software slave management (SSM).
//     */
//    /*
//    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
//    GPIO_Init(&SPIPins);
//    */
//}
//
//
///*
// * Initialize SPI1 peripheral
// */
//void SPI1_Inits(void)
//{
//    SPI_Handle_t SPI1handle;
//
//    /*
//     * VERY IMPORTANT:
//     * Tell the handle which SPI peripheral we are configuring.
//     */
//    SPI1handle.pSPIx = SPI1;
//
//
//    /*
//     * SPI configuration
//     */
//    SPI1handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
//    SPI1handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
//
//    SPI1handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
//
//    SPI1handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
//
//    SPI1handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
//
//    SPI1handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
//
//    SPI1handle.SPIConfig.SPI_SSM = SPI_SSM_EN;
//
//
//    SPI_Init(&SPI1handle);
//}
//
//
//int main(void)
//{
//    char user_data[] = "Hello World";
//
//
//    /*
//     * 1. Configure GPIO pins for SPI1
//     */
//    SPI1_GPIOInit();
//
//
//    /*
//     * 2. Configure SPI1
//     */
//    SPI1_Inits();
//
//
//    /*
//     * Since software slave management is enabled,
//     * SSI must be HIGH.
//     *
//     * This internally tells SPI that NSS is HIGH.
//     */
//    SPI_SSIConfig(SPI1, ENABLE);
//
//
//    /*
//     * 3. Enable SPI1 peripheral
//     */
//    SPI_PeripheralControl(SPI1, ENABLE);
//
//
//    /*
//     * 4. Send data
//     *
//     * IMPORTANT:
//     * SPI1, not SPI2.
//     */
//    SPI_SendData(
//            SPI1,
//            (uint8_t *)user_data,
//            strlen(user_data)
//    );
//
//
//    /*
//     * Wait until SPI has actually finished transmitting.
//     */
//    while (SPI_GETFlagsStatus(SPI1, SPI_BUSY_FLAG));
//
//
//    /*
//     * Disable SPI after transmission
//     */
//    SPI_PeripheralControl(SPI1, DISABLE);
//
//
//    while (1)
//    {
//
//    }
//
//
//    return 0;
//}
