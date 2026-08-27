/*
 * 008spi_cmd_handing.c
 *
 *  Created on: Aug 27, 2026
 *      Author: SV
 */


#include <string.h>
#include "stm32f411xx.h"


//Command Codes
#define COMMAND_LED_CTRL			0X50
#define COMMAND_SENSOR_READ			0X51
#define COMMAND_LED_READ			0X52
#define COMMAND_LED_PRINT			0X53
#define COMMAND_ID_READ				0X54

#define LED_ON		1
#define LED_OFF		0


//Arduino analog pins
#define ANALOG_PIN0		0
#define ANALOG_PIN1		1
#define ANALOG_PIN2		2
#define ANALOG_PIN3		3
#define ANALOG_PIN4		4

//Ardiuno Led
#define LED_PIN		9


void delay (void)
{
	for (volatile  uint32_t i=0; i< 500000/2 ; i++);
}


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
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&SPIPins);


	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&SPIPins); // GPIO_Init writtenn in driver

}

void SPI1_Inits(void)
{


	//Review the type def and how mutiple tyedef works
	SPI_Handle_t SPI1handle;   //SPI1_Handle the varible that i want SPI_Handle_t do all of its rhings iside it in  SPI1_Handle (check it)
	SPI1handle.pSPIx = SPI1;
	SPI1handle.SPIConfig.SPI_BusConfig= SPI_BUS_CONFIG_FD;
	SPI1handle.SPIConfig.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
	SPI1handle.SPIConfig.SPI_SclkSpeed= SPI_SCLK_SPEED_DIV8; //generate sclk 2MHZ
	SPI1handle.SPIConfig.SPI_DFF=SPI_DFF_8BITS;
	SPI1handle.SPIConfig.SPI_CPOL=SPI_CPOL_LOW;
	SPI1handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1handle.SPIConfig.SPI_SSM = SPI_SSM_DI;  //Hardwear slave managemnt enabled for NSS pin
	SPI_Init(&SPI1handle);


}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode =GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed= GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPUPdControl=GPIO_NO_PUPD;

	// GPIO_PeriClockControl(GPIOC, ENABLE); we did it automatically in driver code itself
	GPIO_Init (&GPIOBtn);
}

uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
	if(ackbyte == 0xF5)
	{
		//ack
		return 1;
	}else
	{
		//NACK
		return 0;
	}
}

int main(void)
{
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;

	GPIO_ButtonInit();
	//This function is used to initialize the GPIO pins to behave like SPI1 pins
	SPI1_GPIOInit();

	//This function is used to initialize the SPI1preiphral parameters
	SPI1_Inits();



	SPI_SSOEConfig(SPI1, ENABLE);

while(1)
	{
	while ( ! GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));

	delay();
//	SPI_SSIConfig(SPI1, ENABLE); no need for ssm_Di


	//enable the SPI2 Peripheral
	//All registers configuration recomendded beforeenable SPI prehipral as we did
	SPI_PeripheralControl(SPI1,ENABLE); //We have to enavle The spi to transmite (the SPE in Control register 1)

	// first send length information
	uint8_t commandcode = COMMAND_LED_CTRL;
	uint8_t ackbyte;
	uint8_t args[2];


	//send 1 byte of of commandcode= 0X50 , which is accully less than 1 byte is
	//if slave support this command it will send ACK
	SPI_SendData(SPI1, &commandcode, 1);

	//do dummy read to clear off RXNE
	SPI_ReceiveData(SPI1, &dummy_read, 1);


	//send some dummy bits (1byte) to fetch the response from slave
	SPI_SendData(SPI1,&dummy_write,1);

	//Read the ack byte recived
	SPI_ReceiveData(SPI1, &ackbyte, 1);

	if (SPI_VerifyResponse(ackbyte))
	{
		//send arguments
		args[0]= LED_PIN;
		args[1]= LED_ON;

		//send arguments
		SPI_SendData(SPI1, args,2);
	}

	//TO send data
	//SPI_SendData(SPI1, (uint8_t*)user_data, strlen(user_data));

	//Lets confirm SPI not Busy
	while(SPI_GETFlagStatus(SPI1, SPI_BUSY_FLAG));// w8 until all measage send.

	SPI_PeripheralControl(SPI1,DISABLE); //After sending the data, disable the prepheral
	}


	return(0);


}
