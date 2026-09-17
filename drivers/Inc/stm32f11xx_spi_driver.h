/*
 * stm32f311xx_spi.h
 *
 *  Created on: Jul 4, 2026
 *       Author: Eng. Fersa Abuhaimed.
 *      **************************************************************
 *      (Note/ The using data sheet rm0383 and include with repository)
 *      **************************************************************
 */

/*
 * Configuration structure for SPIx peripheral.
 */

#ifndef INC_STM32F11XX_SPI_DRIVER_H_
#define INC_STM32F11XX_SPI_DRIVER_H_

#include "stm32f411xx.h"


typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;


/*
 * Handle structure for SPIx peripheral.
 */
typedef struct
{
	SPI_RegDef_t	*pSPIx;
	SPI_Config_t	 SPIConfig;
	uint8_t			*pTxBuffer;  /* < To store the application. Tx Buffer address > */
	uint8_t 		*pRxBuffer;  /* < To store the application. Rx Buffer address > */
	uint32_t		 TxLen;	   	 /* < To store TX Len > */
	uint32_t	 	 RxLen;		 /* < To store RX Len > */
	uint8_t			 TxState;	 /* < To store TX State > */
	uint8_t			 RxState;    /* < To store RX State > */
}SPI_Handle_t;

/*
 * SPI Application State.
 */
#define  SPI_READY			0
#define  SPI_BUSY_IN_RX		1
#define  SPI_BUSY_IN_TX     2


/*
 * SPI Application events.
 */

#define SPI_EVENT_TX_CMPLT		1
#define SPI_EVENT_RX_CMPLT		2
#define SPI_EVENT_OVR_ERR		3


/*
 * @SPI_DeviceMode. (Page 599).
 */

#define SPI_DEVICE_MODE_MASTER		1
#define SPI_DEVICE_MODE_SLAVE		0

/*
 * @SPI_BusConfig.
 */
#define SPI_BUS_CONFIG_FD						1	//Full duplex
#define SPI_BUS_CONFIG_HD						2	//Hlaf duplex
//#define SPI_BUS_CONFIG_SIMPLEX_TXONLY			3	Simplex Tx only , acculy we dont need to prgram it spimpex txonly is just full duplex and just remve rx line
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY			4	//Simplex RXONLY

/*
 * @SPI_SclkSpeed. (Page 599)
 */
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32 			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128	 		6
#define SPI_SCLK_SPEED_DIV256			7




/*
 * @SPI_DFF (Page 598).
 */
#define SPI_DFF_8BITS	0		//By default DFF is zero
#define SPI_DFF_16BITS	1


/*
 * @SPI_CPOL, CLK Polarity (Page 600).
 */
#define SPI_CPOL_HIGH	1
#define SPI_CPOL_LOW	0

/*
 * @SPI_CPHA (Page 600).
 */
#define SPI_CPHA_HIGH	1
#define SPI_CPHA_LOW	0

/*
 * @SPI_SSM (Page 599).
 */
#define SPI_SSM_EN	1 			//SPI_SSM hardware mode.
#define SPI_SSM_DI	0			//SPI_SSM software mode (the default mode).

/*
 * SPI related status flags definitions. (Page 601).
 * TXE is 1 in smt32xx.h, so the bit 1 is the register mask it with 1 it becomes 0000 0010
 * and when we need to operate it like The Flag example FlagGetStatus in spi.c we operate with AND
 *if(pSPIx->SR & FlagName) (SR value) & 0000 0010 is 1 becomes if(1) and do the function and
 *if TXE in SR not 1 becomes If(0).
 */
#define SPI_TXE_FLAG		(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG		(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG		(1 << SPI_SR_BSY)

/******************************************************************************************
*                         APIs supported by this driver
*     For more information about the APIs check the function definitions
******************************************************************************************/

/*
 * Peripheral Clock setup.
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 * Init and De-init.
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);  // (void), the parameters will be written later
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data Send and Receive.
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/*
 * Data Send and Receive interrupt base.
 */
uint8_t SPI_SendDataIT(SPI_Handle_t *SPIHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *SPIHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ Configuration and ISR Handling.
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);			// Message the interrupt ([config]enable and give the priority).
void SPI_IRQPriorityConfig(uint32_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);		//To process that interrupt when it comes.

/*
 * flag status.
 */

uint8_t SPI_GETFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName);

/*
 * Other Peripheral Control APIs.
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_ClearOverFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmisson(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

/*
 * Application Callback.
 */

void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv);

#endif /* INC_STM32F11XX_SPI_DRIVER_H_ */
