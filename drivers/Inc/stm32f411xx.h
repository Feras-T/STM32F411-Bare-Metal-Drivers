/*
 * stm32fr411re.h
 *
 *  Created on: May 21, 2026
 *      Author: SV
 */

#ifndef INC_STM32F411XXH_
#define INC_STM32F411XXH_

#include <stdint.h>   // The shorthand notations are defined in standared library file (stdint.h)
#define __vo volatile

/*********************************************START:Processor Specific Details********************************/
/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */

#define NVIC_ISER0						   ( (__vo uint32_t*)0xE000E100 ) //"Treat this number as a memory address (pointer), not as a value"
#define NVIC_ISER1						   ( (__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2						   ( (__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3						   ( (__vo uint32_t*)0xE000E10C )

/*
 * ARM Cortex Mx Processor Priority Register Addresses calculation
 */
#define NVIC_PR_BASE_ADDR 	 ( (__vo uint32_t*)0xE000E400)


#define NO_BITS_IMPLENTED		    	4  // sometimes is 3 on other microcontrollers




/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0						   ( (__vo uint32_t*)0xE000E180 )
#define NVIC_ICER1						   ( (__vo uint32_t*)0xE000E184 )
#define NVIC_ICER2						   ( (__vo uint32_t*)0xE000E188 )
#define NVIC_ICER3						   ( (__vo uint32_t*)0xE000E18C )


#define FLASH_BASEADDR				    	0x08000000U
#define SRAM1_BASEADDR				        0x20000000U
#define ROM_BASEADDR				        0x1FFF0000U
#define SRAM						        SRAM1_BASEADDR

#define	PERIPH_BASEADDR						0x40000000U
#define APB1PERIPH_BASEADDR					PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR					0x40010000U
#define AHB1PERIPH_BASEADDR					0x40020000U
#define AHB2PERIPH_BASEADDR					0x50000000U

/*
 * Base addressess of peripherals wich are hanging on AHB1 bus
 */

#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0X0000) //(AHB1PERIPH+ OFFSET=0X0000)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0X0400) //(AHB1PERIPH+ OFFSET=0X0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0X0800) //(AHB1PERIPH+ OFFSET=0X0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0X0C00) //(AHB1PERIPH+ OFFSET=0X0C00)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0X1000) //(AHB1PERIPH+ OFFSET=0X1000)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0X1C00) //(AHB1PERIPH+ OFFSET=0X1C00)
#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR + 0X3800) //(AHB1PERIPH+ OFFSET=0X1C00)

/*
 * Base addressess of peripherals wich are hanging on APB1 bus
 */

#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0ء5400)   //(APB1PERIPH+ OFFSET=0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0X1C00) //(APB1PERIPH+ OFFSET=0X5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0X5C00) //(APB1PERIPH+ OFFSET=0X5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0X3800) //(APB1PERIPH+ OFFSET=0X3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0X3C00) //(APB1PERIPH+ OFFSET=0X3C00)

#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0X4400) //(APB1PERIPH+ OFFSET=0X4400)

//#define USART3_BASEADDR			(APB1PERIPH + 0X1C00) //(APB1PERIPH+ OFFSET=0X1C00)
//#define UART4_BASEADDR			(APB1PERIPH + 0X1C00) //(APB1PERIPH+ OFFSET=0X1C00)
//#define UART5_BASEADDR			(APB1PERIPH + 0X1C00) //(APB1PERIPH+ OFFSET=0X1C00)

/*
 * Base addressess of peripherals wich are hanging on APB2 bus
 */

#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0X3000) //(APB2PERIPH+ OFFSET=0X3000)
#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0X1000) //(APB2PERIPH+ OFFSET=0X1000)
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0X1400) //(APB2PERIPH+ OFFSET=0X1400)
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0X3C00) //(APB2PERIPH+ OFFSET=0X3C00)
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0X3800) //(APB2PERIPH+ OFFSET=0X3800)

/*
 * 	periphral register definition structure for GPIO
 * 	Note the offset is by default adjust it ofsset 0x00- MODER, offset 0x04 32bit OTYPER and so on
 */

typedef struct
{
	__vo uint32_t MODER;						//GPIO port mode register						Address offset: 0x00
	__vo uint32_t OTYPER;					    //GPIO port output type register				Address offset: 0x04
	__vo uint32_t OSPEEDR;						//GPIO port output speed register				Address offset: 0x08
	__vo uint32_t PUPDR;						//GPIO port pull-up/pull-down register			Address offset: 0x0C
	__vo uint32_t IDR;							//GPIO port input data register					Address offset: 0x10
	__vo uint32_t ODR;							//GPIO port output data register				Address offset: 0x14
	__vo uint32_t BSRR;							//GPIO port bit set/reset register				Address offset: 0x18
	__vo uint32_t LCKR;							//GPIO port configuration lock register			Address offset: 0x1C		AFR[0] : GPIO alternate function low register, AFR[1] : GPIO alternate function high register
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;

typedef struct
{
	__vo uint32_t CR;						// clock control register															Address offset: 0x00
	__vo uint32_t PLLCFGR;					//RCC PLL configuration register													Address offset: 0x04
	__vo uint32_t CFGR;						//RCC clock configuration register													Address offset: 0x08
	__vo uint32_t CIR;						//RCC clock interrupt register														Address offset: 0x0C
	__vo uint32_t AHB1RSTR;					//RCC AHB1 peripheral reset register												Address offset: 0x10
	__vo uint32_t AHB2RSTR;					//RCC AHB2 peripheral reset register												Address offset: 0x14
	uint32_t Reserved[2];
	__vo uint32_t APB1RSTR;					//RCC APB1 peripheral reset register												Address offset: 0x20
	__vo uint32_t APB2RSTR;					//RCC APB2 peripheral reset register												Address offset: 0x24
	uint32_t Reserved0[2];
	__vo uint32_t AHB1ENR;					//RCC AHB1 peripheral clock enable register											Address offset: 0x30
	__vo uint32_t AHB2ENR;					//RCC AHB2 peripheral clock enable register											Address offset: 0x34
	uint32_t Reserved1[2];
	__vo uint32_t APB1ENR;					//RCC APB1 peripheral clock enable register											Address offset: 0x40
	__vo uint32_t APB2ENR;					//RCC APB2 peripheral clock enable register											Address offset: 0x44
	uint32_t Reserved2[2];
	__vo uint32_t AHB1LPENR;				//RCC AHB1 peripheral clock enable in low power mode register						Address offset: 0x50
	__vo uint32_t AHB2LPENR;				//RCC AHB2 peripheral clock enable in low power mode register						Address offset: 0x54
	uint32_t Reserved3[2];
	__vo uint32_t APB1LPENR;				//RCC APB1 peripheral clock enable in low power mode register						Address offset: 0x60
	__vo uint32_t APB2LPENR;				//RCC APB2 peripheral clock enabled in low power mode register						Address offset: 0x64
	uint32_t Reserved4[2];
	__vo uint32_t BDCR;						//RCC Backup domain control register												Address offset: 0x70
	__vo uint32_t CSR;						//RCC clock control & status register												Address offset: 0x74
	uint32_t Reserved5[2];
	__vo uint32_t SSCGR;					//RCC spread spectrum clock generation register										Address offset: 0x80
	__vo uint32_t PLLI2SCFGR;				//RCC PLLI2S configuration register													Address offset: 0x84
	__vo uint32_t DCKCFGR;					//RCC Dedicated Clocks Configuration Register										Address offset: 0x8C

}RCC_RegDef_t;

/*
 * peripheral register definition stucture for SPI
 */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;

}SPI_RegDef_t;

/*
 * 	periphral  definition structure ( priphral base address typecasted to xxx_ReDef_t)
 */

/*
 *  periheral register structure for EXTI
 */

typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;

}EXTI_RegDef_t;

/*
 * periphral register definition structure for SYSCFG
 */

typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t RESERVED1[2];
	__vo uint32_t CMPCR;

}SYSCFG_RegDef_t;

/*
 * Preiphral definitions ( Peripheral base addresses typecasted to xx_RegDef_t)
 */

#define GPIOA				((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB				((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC				((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD				((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE				((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH				((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC 				((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI				((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG				((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define SPI1				((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2				((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3				((SPI_RegDef_t*)SPI3_BASEADDR)

/*
 * Clock Enable Macros for GPIOX prehihrals
 */

#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1 <<0) )			//To write afunction in macros you have to add (), GPIOA_PCLK_EN()= GPIOA_PERI_CLOCK_ENABLE()
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1 <<1) )			// rcc its is a pointer because its cast to as a pointer for rcc_baseadder to rcc_regdef struct thats what ((RCC_RegDef_t*)RCC_BASEADDR) mean
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1 <<2) )
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1 <<3) )
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1 <<4) )
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1 <<7) )

/*
 * Clock Enable Macros for I2Cx prehihrals
 */

#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 <<21) )
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 <<22) )
#define I2C3_PCLK_EN()		(RCC->APB1ENR |= (1 <<23) )
/*
 * Clock Enable Macros for SPIx prehihrals
 */

#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1 <<12) )
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1 <<14) )
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1 <<15) )

/*
 * Clock Enable Macros for USARTx prehihrals
 */
#define UXART1_PCLK_EN()		(RCC->APB2ENR |= (1 <<4) )
#define UXART2_PCLK_EN()		(RCC->APB1ENR |= (1 <<17) )
#define UXART6_PCLK_EN()		(RCC->APB2ENR |= (1 <<5) )

/*
 * Clock Enable Macros for SYCFGx prehihrals
 */
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 <<14) )

/*
 * Clock Disable Macros for GPIOx prehihrals
 */

#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1 <<0) )			//To write afunction in macros you have to add (), GPIOA_PCLK_EN()= GPIOA_PERI_CLOCK_ENABLE()
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1 <<1) )
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1 <<2) )
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1 <<3) )
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1 <<4) )
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1 <<7) )

/*
 * Clock Disable Macros for GPIOx prehihrals
 */

#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~(1 <<21) )
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= ~(1 <<22) )
#define I2C3_PCLK_DI()		(RCC->APB1ENR &= ~(1 <<23) )

/*
 * Clock Disable Macros for SPIx prehihrals
 */

#define SPI1_PCLK_DI()		(RCC->APB2ENR &= ~(1 <<12) )
#define SPI2_PCLK_DI()		(RCC->APB1ENR &= ~(1 <<14) )
#define SPI3_PCLK_DI()		(RCC->APB1ENR &= ~(1 <<15) )

/*
 * Clock Disable Macros for USARTx prehihrals
 */

#define UXART1_PCLK_DI()		(RCC->APB2ENR &= ~(1 <<4) )
#define UXART2_PCLK_DI()		(RCC->APB1ENR &= ~(1 <<17) )
#define UXART6_PCLK_DI()		(RCC->APB2ENR &= ~(1 <<5) )

/*
 * Clock Disable Macros for SYSCFG prehihrals
 */

#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1 <<14) )


/*
 * Macros to reset GPIOx peripherals
 * RCC AHB1 peripheral reset register (RCC_AHB1RSTR)
 * The main Goal of RCC_AHB1RSTR is to resert all the register of a specific PORT
 */

#define GPIOA_REG_RESET()				do{((RCC->AHB1RSTR |= ( 1 <<0) ));    (RCC->AHB1RSTR &= ~( 1 << 0));} while (0) // do [(Case1); (Case2);] while (0), it means do case1 and then case 2.
#define GPIOB_REG_RESET()				do{((RCC->AHB1RSTR |= ( 1 <<1) ));    (RCC->AHB1RSTR &= ~( 1 << 1));} while (0) // do [(Case1); (Case2);] while (0), it means do case1 and then case 2.
#define GPIOC_REG_RESET()				do{((RCC->AHB1RSTR |= ( 1 <<2) ));    (RCC->AHB1RSTR &= ~( 1 << 2));} while (0) // do [(Case1); (Case2);] while (0), it means do case1 and then case 2.
#define GPIOD_REG_RESET()				do{((RCC->AHB1RSTR |= ( 1 <<3) ));    (RCC->AHB1RSTR &= ~( 1 << 3));} while (0) // do [(Case1); (Case2);] while (0), it means do case1 and then case 2.
#define GPIOE_REG_RESET()				do{((RCC->AHB1RSTR |= ( 1 <<4) ));    (RCC->AHB1RSTR &= ~( 1 << 4));} while (0) // do [(Case1); (Case2);] while (0), it means do case1 and then case 2.
#define GPIOH_REG_RESET()				do{((RCC->AHB1RSTR |= ( 1 <<5) ));    (RCC->AHB1RSTR &= ~( 1 << 5));} while (0) // do [(Case1); (Case2);] while (0), it means do case1 and then case 2.


/*
 * returns port code for given GPIOx base address
 * Note://If x== GPIOA is true otherwise go and check the secound condition x== GPIOB
 */

#define GPIO_TO_CODE(x)		  ( (x == GPIOA)?0:\
								(x == GPIOB)?1:\
								(x == GPIOC)?2:\
								(x == GPIOD)?3:\
								(x == GPIOE)?4:\
								(x == GPIOH)?5:0 )

/*
 * IRQ(Interrupt Request) Numbers of STM32 MCU
 * TODO: You may have complete this list for other peripherals
 */

#define IRQ_NO_EXTI0        6
#define IRQ_NO_EXTI1        7
#define IRQ_NO_EXTI2        8
#define IRQ_NO_EXTI3        9
#define IRQ_NO_EXTI4        10
#define IRQ_NO_EXTI9_5      23   // EXTI lines 5 to 9 share this one IRQ
#define IRQ_NO_EXTI15_10    40   // EXTI lines 10 to 15 share this one IRQ

/*
 * Macros for all possible priority levels
 */
#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI1		1
#define NVIC_IRQ_PRI2		2
#define NVIC_IRQ_PRI3		3
#define NVIC_IRQ_PRI4		4
#define NVIC_IRQ_PRI5		5
#define NVIC_IRQ_PRI6		6
#define NVIC_IRQ_PRI7		7
#define NVIC_IRQ_PRI8		8
#define NVIC_IRQ_PRI9		9
#define NVIC_IRQ_PRI10		10
#define NVIC_IRQ_PRI11		11
#define NVIC_IRQ_PRI12		12
#define NVIC_IRQ_PRI13		13
#define NVIC_IRQ_PRI14		14
#define NVIC_IRQ_PRI15		15


/*
 * some generic Macros
 */

#define ENABLE			  1
#define DISABLE			  0
#define SET 			  ENABLE
#define RESET		      DISABLE
#define GPIO_PIN_SET	  SET
#define GPIO_PIN_RESET 	  RESET
#define FLAG_RESET		  RESET
#define FLAG_SET		  SET


/*********************************************************
  *Bit position definitions of SPI peripheral
 *********************************************************/

#define SPI_CR1_CPHA   		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR			3
#define SPI_CR1_SPE			6
#define SPI_CR1_LSBFIRST	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_DFF			11
#define SPI_CR1_CRCNEXT	12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15

/*
 * Bit position definition SPI_CR2
 */

#define SPI_CR1_RXDMAE		0
#define SPI_CR1_TXDMAEN		1
#define SPI_CR1_SSOE		2
#define SPI_CR1_FRF			4
#define SPI_CR1_ERRIE		5
#define SPI_CR1_RXNEIE		6
#define SPI_CR1_TXEIE		7


/*
 * Bit position definition SPI_SR (SPI_Sataus register
 */

#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCERR		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY          7
#define SPI_SR_FRE			8


#include "stm32f411_gpio_driver.h"
#include "stm32f11xx_spi_driver.h"

#endif /* INC_STM32F411XXH_ */



