/*
 * i2c_driver.c
 *
 *  Created on: May 21, 2026
 *      Author: sethu
 *
 */
#include "stm32f407xx_i2c_driver.h"
uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint16_t APB_PreScaler[8] = {2,4,8,16,64,128,256,512};


static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
//static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr);
//static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr);
//static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle);
//static void I2C_MasterHandleTXEInterrupt(I2C_Handle_t *pI2CHandle);
//static void I2C_MasterHandleRXNEInterrupt(I2C_Handle_t *pI2CHandle);


/*	Generating Start Condition - CR1 reg: bit 8 - start bit )*/

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->I2C_CR1 |= (1 << I2C_CR1_START);
}

/*
 * Peripheral Clock setup
 */
/********************************************************************
 * @fn                  - GPIO_Init
 *
 * @brief               - This function enables or disables peripheral clock for given GPIO port
 *
 * @param[in]           - base address of the GPIO peripheral
 * @param[in]           - enable or disbale macros
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pI2Cx ==  I2C1)
			I2C1_PCLK_EN();
		else if(pI2Cx == I2C2)
			I2C2_PCLK_EN();
		else if(pI2Cx == I2C3)
			I2C3_PCLK_EN();
	}
	else
	{
		if(pI2Cx ==  I2C1)
			I2C1_PCLK_DI();
		else if(pI2Cx == I2C2)
			I2C2_PCLK_DI();
		else if(pI2Cx == I2C3)
			I2C3_PCLK_DI();
	}
}

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pI2Cx->I2C_CR1 |= (1 << I2C_CR1_PE);
	}else
	{
		pI2Cx->I2C_CR1 &= ~(1 << 0);
	}

}

/*
 * Init and De-init
 */

uint32_t RCC_GetPLLOutputClock()
{
	return 0; // not using PLL
}
//Apb1 Clock frequency Calculation (16 - but user will change - FGRQ)
uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1,SystemClk;

	uint8_t clksrc,temp,ahbp,apb1;
	clksrc = ((RCC->CFGR >> 2) & 0x03); // in RCC reg - CFGR Reg - SWS bit

	if(clksrc == 0)   //HSI
		SystemClk = 16000000;
	else if(clksrc == 1)    //HSE
		SystemClk = 8000000;
	else if(clksrc == 2)     // PLL  - We need to calculate
		SystemClk = RCC_GetPLLOutputClock();

	// for ahb - prescalarvalue  - Decided by HPRE - RCC-CFGR REG
	temp = ((RCC->CFGR >> 4) & 0xF);
	if(temp < 8)
		ahbp = 1;
	else
		ahbp = AHB_PreScaler[temp-8];

	// for apb1
	temp = ((RCC->CFGR >> 10) & 0x7);
		if(temp < 8)
			apb1 = 1;
		else
			apb1 = APB_PreScaler[temp-4];

		pclk1 = (SystemClk / ahbp) / apb1;

	return pclk1;
}

/********************************************************************
 * @fn                  - I2C_Init
 *
 * @brief               - This function enables or disables peripheral clock for given GPIO port
 *
 * @param[in]           - base address of the GPIO peripheral
 * @param[in]           - enable or disbale macros
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0;

	// enable the clock for the i2cx peripheral
	I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

	// ack control bit
	tempreg |= pI2CHandle->I2C_Config.I2C_AckControl << 10;
	pI2CHandle->pI2Cx->I2C_CR1 = tempreg;

	//configure the FGRQ field of CR2
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value() / 1000000U;
	pI2CHandle->pI2Cx->I2C_CR2 = (tempreg & 0x3F);

	//program the device own address
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	tempreg |= (1 << 14);
	pI2CHandle->pI2Cx->I2C_OAR1 = tempreg;

	//CCR calculations - clock control register.- serial clk for i2c
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		// mode id standard mode
		ccr_value = (RCC_GetPCLK1Value() / (2*pI2CHandle->I2C_Config.I2C_SCLSpeed));
		tempreg |= ccr_value & 0xFF;
	}
	else
	{
		// fast mode - depends on duty cycle two calculation
		tempreg |= (1 << 15);  //bit no 15
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14); // 14th bit position
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{
			ccr_value = (RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		else
		{
			ccr_value = (RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		tempreg |= ccr_value & 0xFF;
	}
	pI2CHandle->pI2Cx->I2C_CCR = tempreg;

	// TRISE configuration
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		// mode is standard mode
		tempreg = (RCC_GetPCLK1Value() /1000000U) + 1;
	}
	else
	{
		// mode is fast mode
		tempreg = ((RCC_GetPCLK1Value() * 300) / 1000000000 ) + 1;
	}
	pI2CHandle->pI2Cx->I2C_TRISE = (tempreg & 0x3F);
}

/********************************************************************
 * @fn                  - I2C_DeInit
 *
 * @brief               - This function enables or disables peripheral clock for given GPIO port
 *
 * @param[in]           - base address of the GPIO peripheral
 * @param[in]           - enable or disbale macros
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{

}
//reading the SR1 : SB Flag
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName)
{
	if(pI2Cx->I2C_SR1 & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}



/********************************************************************
 * @fn                  - I2C_Master_Send_Data
 *
 * @brief               - This function enables or disables peripheral clock for given GPIO port
 *
 * @param[in]           - base address of the GPIO peripheral
 * @param[in]           - enable or disbale macros
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 **/

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t len,uint8_t SlaveAddr,uint8_t Sr)
{
	uint32_t len_initial = len;
	//1. Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while(! (I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_SB)) );

	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )
	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx,SlaveAddr);

	//4. Confirm that address phase is completed by checking the ADDR flag in the SR1
	while(! (I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR)) );

	//5. clear the ADDR flag according to its software sequence
	// Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)
	I2C_ClearADDRFlag(pI2CHandle);

	//6. send the data until len becomes 0
	while(len > 0)
	{
		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));
		pI2CHandle->pI2Cx->I2C_DR = *pTxbuffer;
		pTxbuffer++;
		len--;

		if(len > 0)
		{
			while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF));
		}
	}

	//7. when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
	//   Note: TXE=1 , BTF=1 , means that both SR and DR are empty and next transmission should begin
	//   when BTF=1 SCL will be stretched (pulled to LOW)

	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));

	if(len_initial > 1)
	{
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF));
	}

	//8. Generate STOP condition and master need not to wait for the completion of stop condition.
	//   Note: generating STOP, automatically clears the BTF

	if(Sr == I2C_DISABLE_SR)
	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

}

