/*
 * stm32f411xx_spi_driver.c
 *
 *  Created on: Jul 4, 2026
 *      Author: SV
 */


#include "stm32f11xx_spi_driver.h"
/*
 * Peripheral Clock setup
 */
/******************************************************************************
 * @fn          - GPIO_PerClockControl
 *
 * @brief       - This function enables and disables prehihpral clock for given GPIO port
 *
 * @param[in]   -base address of the gpio peripheral
 * @param[in]   -ENABLE or Disable macros
 * @param[in]   -
 *
 * @return      - none
 *
 * @Note        - none
 *
 *****************************************************************************/

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)

 {
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}else if (pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}else if (pSPIx== SPI3)
		{
			SPI3_PCLK_EN();

	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}else if (pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}else if (pSPIx== SPI3)
		{
			SPI3_PCLK_DI();
		}

}
}
 }

/*
 * Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)  // (void), the parameters will be written later
{

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	uint32_t tempreg =0;

	//Peripheral clock  enable


	//1. configure the device mode
	//Decive control wherthere to be master or slave
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode <<SPI_CR1_MSTR ; //SPI_CR1 Bit2

	//2.configure the bus config
	//At full duplex

	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi shall be cleared
		tempreg &=~(1<<SPI_CR1_BIDIMODE);  //bidi SPI_CR1 control bit 15
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi shall be set
		tempreg |= (1<<SPI_CR1_BIDIMODE);
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi shall be cleared
		tempreg &=~(1<<SPI_CR1_BIDIMODE);
		//RXONLY bit must be set
		tempreg |= (1 <<SPI_CR1_RXONLY); // RX only SPI_CR1 control bit 10
	}

	// 3. Configure the spi serial Clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed <<3 ;

	// 4. Configure the spi serial Clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << 11 ;

	// 5. Configure the spi serial Clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL <<1 ;

	// 6. Configure the spi serial Clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA <<0 ;

	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;


	pSPIHandle ->pSPIx->CR1 =tempreg;



	}




/*
 * Data read and write
 */


/*
 * Peripheral Clock setup
 */
/******************************************************************************
 * @fn          - GPIO_ReadFromInputPin
 *
 * @brief       -
 *
 * @param[in]   -
 * @param[in]   -
 * @param[in]   -
 *
 * @return      - 0 or 1
 *
 * @Note        - none
 *
 *****************************************************************************/

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{



}

uint8_t SPI_GETFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName)
{
	if(pSPIx->SR & FlagName) 		//if Flage name wehther it is  SPI_TXE_FLAG or any other on is
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}




/******************************************************************************
 * @fn          - GPIO_writeToOutpotPort
 *
 * @brief       - This function enables and disables prehihpral clock for given GPIO port
 *
 * @param[in]   -base address of the gpio peripheral
 * @param[in]   -ENABLE or Disable macros
 * @param[in]   -
 *
 * @return      - none
 *
 * @Note        - This is a blocking call , the function will waite until all the bytes transfare also it will waite until TX is ready
 *
 *****************************************************************************/

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len) //called send data api , blocking api, we called like that because the function call wight until all the bits are transmited
{
	while (Len > 0)
	{
		//1. waite until TXE is set
		while(SPI_GETFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET);
		// While (! (pSPIx->sr &(1 << 1); shift on by 1 bit the TXE position in sr register is the mask 1<<1 AND SR =0 and with ! it will be 1 the while will hange if not  the while will get out
		//FLAG_RESET=0, If FlagName(SPI_TXE_FLAG) is 1 the wile will exit and code will implemnt
		//if the FlagName(SPI_TXE_FLAG)=0 the wile will be wile(0=0) -> while(1) and will hang

		//2. check the DFF bit in CR1
		if (pSPIx-> CR1 & ( 1<< SPI_CR1_DFF)) // the 11th bit in CR1 regiater which is DFF if 1 mean 16 bit and if 0 mean 8 bits., make mask with SPI_CR1_DFF and And it with CR1 to check whether 16bit is enabeled or not
		{
			//16 bits DFF
			//1. load the data in to DR
			pSPIx->DR = *((uint16_t*)pTxBuffer); //DR, Data register,*pTxBuffer Go to address 0x20000100 and give me the value stored there.
			//First star mean go to than pointer and give me it value , the uint16_t* mean
			//Treat pTxBuffer as a pointer to uint16_t, then dereference it
			//and get the actual 16-bit value stored there.
			//((uint16_t*)pTxBuffer); without the fist d+star mean go to the address of pTxBuffer pointer not the value inside the pointer.
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++; // (uint16_t*) to incremnt pointer by 2

		}else
			{
			//8 bits DFF
			//1. load the data in to DR
			pSPIx->DR = *pTxBuffer; //DR, Data register, its by defult in this function uint8_t so no need (uint16_t*)
			Len--; //one time dicrese the leangth
			pTxBuffer++;

			}

	}

}


/******************************************************************************
 * @fn          - GPIO_ToggleOutputPin
 *
 * @brief       -
 * @param[in]   -
 * @param[in]   -
 * @param[in]   -
 *
 * @return      - none
 *
 * @Note        - none
 *
 *****************************************************************************/

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{

}

/*
 * IRQ Configuration and ISR Handling
 */


/******************************************************************************
 * @fn          - GPIO_IRQConfig
 *
 * @brief       - This function enables and disables prehihpral clock for given GPIO port
 *
 * @param[in]   -base address of the gpio peripheral
 * @param[in]   -ENABLE or Disable macros
 * @param[in]   -
 *
 * @return      - none
 *
 * @Note        - none
 *
 *****************************************************************************/

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)			// message the intrrupt ([config]enable and give the prioraty)
{

}


	/******************************************************************************
	 * @fn          - GPIO_PerClockControl
	 *
	 * @brief       - This function enables and disables prehihpral clock for given GPIO port
	 *
	 * @param[in]   -base address of the gpio peripheral
	 * @param[in]   -ENABLE or Disable macros
	 * @param[in]   -
	 *
	 * @return      - none
	 *
	 * @Note        - none
	 *
	 *****************************************************************************/

void SPI_IRQPriorityConfig(uint32_t IRQNumber, uint32_t IRQPriority)
{

}




/******************************************************************************
 * @fn          - GPIO_PerClockControl
 *
 * @brief       - This function enables and disables prehihpral clock for given GPIO port
 *
 * @param[in]   -base address of the gpio peripheral
 * @param[in]   -ENABLE or Disable macros
 * @param[in]   -
 *
 * @return      - none
 *
 * @Note        - none
 *
 *****************************************************************************/

void SPI_IRQHandling(SPI_Handle_t *pHandle)		//To prossesor that interrupt when it comes
{

}


/******************************************************************************
 * @fn          - GPIO_PerClockControl
 *
 * @brief       - This function enables and disables prehihpral clock for given GPIO port
 *
 * @param[in]   -base address of the gpio peripheral
 * @param[in]   -ENABLE or Disable macros
 * @param[in]   -
 *
 * @return      - none
 *
 * @Note        - none
 *
 *****************************************************************************/


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);  // if EnorDi is Enable =1 then let SPE Be one to run the SPI protocols , go to CR1 then then add 1 that shifted by 6 (which is SPI_CR1_SPE =6)
	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

/******************************************************************************
 * @fn          - GPIO_PerClockControl
 *
 * @brief       - This function enables and disables prehihpral clock for given GPIO port
 *
 * @param[in]   -base address of the gpio peripheral
 * @param[in]   -ENABLE or Disable macros
 * @param[in]   -
 *
 * @return      - none
 *
 * @Note        - none
 *
 *****************************************************************************/


void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{


		if(EnorDi == ENABLE)
		{
			pSPIx->CR1 |= (1 << SPI_CR1_SSI);  // if EnorDi is Enable =1 then let SPE Be one to run the SPI protocols , go to CR1 then then add 1 that shifted by 6 (which is SPI_CR1_SPE =6)
		}else
		{
			pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
		}

}
