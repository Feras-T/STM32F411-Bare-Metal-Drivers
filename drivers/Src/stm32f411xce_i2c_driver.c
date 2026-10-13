/*
 * stm32f411xce_i2c_driver.c
 *
 *  Created on: Sep 29, 2026
 *      Author: SV
 */

#include "stm32f411xce_i2c_driver.h"

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint16_t APB1_Prescaler[4]= {2,4,8,16};

//Shall be review
/*
 * Peripheral Clock setup
 */
/*****************************************************************
 * @fn          - I2C_PeriClockControl
 *
 * @brief       - This function enables or disables peripheral
 *                clock for the given I2C port
 *
 * @param[in]   - Base address of the I2C peripheral
 * @param[in]   - Macros: Enable or Disable
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pI2Cx == I2C1)
        {
            I2C1_PCLK_EN();
        }
        else if(pI2Cx == I2C2)
        {
            I2C2_PCLK_EN();
        }
        else if(pI2Cx == I2C3)
        {
            I2C3_PCLK_EN();
        }
    }
    else
    {
        if(pI2Cx == I2C1)
        {
            I2C1_PCLK_DI();
        }
        else if(pI2Cx == I2C2)
        {
            I2C2_PCLK_DI();
        }
        else if(pI2Cx == I2C3)
        {
            I2C3_PCLK_DI();
        }
    }
}

uint32_t RCC_GetPLLOutpuClock();

void I2C_DeInit(I2C_RegDef_t *pSPIx);



uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1,SystemClk;
	uint8_t clksrc,temp,ahbp,apb1p;

	// system clock , at CFGR register at 2:3 bit , we shift by to
	//to be at begining then we mask by and (all zeros expept the first shifted two bits)
	clksrc = ((RCC ->CFGR >> 2) & 0x3);

	if(clksrc == 0)
	{
		SystemClk = 1600000;

	}else if (clksrc ==1)
	{
		SystemClk = 8000000;

	}else if ( clksrc == 2 ) // That mean it will be decided by PLL.
	{
		SystemClk = RCC_GetPLLOutpuClock();
	}
	//ahbp
	temp = ((RCC ->CFGR >> 4) & 0xF); // The AHB Prescaler which is start at bit 4 to 7 so we shift 4 and mask the regiser after shit with and

	if (temp < 8)
	{
		ahbp= 1;
	}else if (clksrc == 1)
	{
		//if temp is 8 then 8-8 is zero so it will be [0]=2
		//in AHB_Prescaler function if temp is 9 then 9-8 =[1] which
		//is 4 and so on 10,11,12,13->8,16,32,64...
		ahbp = AHB_PreScaler[temp-8];
	}

	//apb1
	temp = ((RCC ->CFGR >> 10) & 0x7); // The apb1 Prescaler which is start at bit 10 so we shift 10 and mask the CFGR regiser after shit and Do AND

	if (temp < 8)
	{
		apb1p= 1;
	}else if (clksrc == 1)
	{
		//if temp is 4 then 4-4 is zero so it will be [0]=2
		//in apb_Prescaler function if temp is 5 then 5 =[1] which
		//is 1 and so on 6,7->8,17
		apb1p = APB1_Prescaler[temp-4];
	}
	//first we had found system clock then we devided it by ahp prescaler then all diveded by abp1 prescaler
	pclk1 = (SystemClk/ahbp)/apb1p;
	return pclk1;

}
void I2C_Init (I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg =0;
	tempreg =0;
	tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << 10;

	//Configure the FREQ filed of CR2
	tempreg =0;
	tempreg = RCC_GetPCLK1Value()/1000000U;
	//FREQ is from 0 to fifth bit at CR2
	//for saftey reason we will mask with 3F which is the bits form 0 to 5
	// &3F = 111111
	pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3FU); // By this mask tempreg will be just in 0-5th bit

	//Program the device own adress
	//the address is save on OAR1 register At ADD
	//we have to save the address at just at ADD if we
	//want to save 7bit addre
	//and ADD+ADD0 if we want to save 10bit address
	//Here we will save it just at 7bit so we will shift by1
	//to only take ADD without ADD0
	tempreg = pI2CHandle-> I2C_Config.I2C_DeviceAddress <<1;
	//In OAR1 we have to code the bit , 1 mean 10 bit and zero mean 7bit and bydefault it is 0 so we will not program it.
	//At OAR1 register it says that bit 14 shall be 1 (manifactour purpose)
	tempreg |= (1 << 14);
	pI2CHandle->pI2Cx->OAR1 =tempreg;

	//CCR Calculation
	//you have first to configure the mode (F/S 15th bit) at I2C_CCR register
	//for standared mode =0 Fast mode =1;
	// fo standred mode we dont have to pregram the bit
	//because by default is = 0;
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		//mode is standared mode
		//Check the equation at the muc1 note P5 Pic 16.
		ccr_vale= RCC_GetPCLK1Value()/ (2 *PI2CHandle->I2C_Config.I2C_SCLSpeed);
		tempreg |= (ccr_value & 0xFFF); //we mask with the first 12 bit (at CCR REGISTE page 499.
	}else
	{
		//mode is fast mode
		//We have to modify F/S 15th bit in CCR register to be 1 (Fast Mode)
		tempreg |= (1 <<15);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{
			//Equation in note MCU1 P5 Pic 17.
			ccr_vale= RCC_GetPCLK1Value()/ (3 *PI2CHandle->I2C_Config.I2C_SCLSpeed);

		}else
		{
			//Equation in note MCU1 P5 Pic 17.
			ccr_vale= RCC_GetPCLK1Value()/ (25 *PI2CHandle->I2C_Config.I2C_SCLSpeed);
		}

		tempreg |= (ccr_value & 0xFFF);


	}
	pI2CHandle->pI2Cx->CCR =tempreg;


}










