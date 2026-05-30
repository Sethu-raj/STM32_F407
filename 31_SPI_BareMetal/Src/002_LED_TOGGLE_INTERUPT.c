/*
 * 002_LED_TOGGLE_INTERUPT.c
 *
 *  Created on: May 17, 2026
 *      Author: sethu
 */


#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include <stdint.h>
#include "string.h"
#define HIGH 1
#define LOW 0
#define BTN_PRESSED LOW

void delay(void)
{
	//this will introduce ~200ms delay when system clock is 16MZ
	for(uint32_t i=0; i<500000/2;i++);
}


int main()
{
	GPIO_Handle_t GpioLed, GpioBtn;

	memset(&GpioLed,0,sizeof(GpioLed));   // clear gpioled & gpiiobin handle structure before gpio init avoide unwanted random value
	memset(&GpioBtn,0,sizeof(GpioBtn));

	// LED configuration
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPtype = GPIO_OP_TYPE_PP;  // imp - otherwise it will take random value
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Init(&GpioLed);

	// Button configuration
	GpioBtn.pGPIOx = GPIOA;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT; // interupt Falling Edge
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&GpioBtn);

	// IRQ config (FIXED) Enable the Irq
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, NVIC_IRQ_PR0); // Consider more interupt
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);

	while(1);
}


// IrQ handler- we will get this function in startup code
void EXTI0_IRQHandler(void)
{
delay(); // 200ms - to avaoid debouncing
	GPIO_IRQHandling(GPIO_PIN_NO_0);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
}
