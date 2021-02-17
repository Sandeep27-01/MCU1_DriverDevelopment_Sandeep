/*
 * 001led_toggling.c
 *
 *  Created on: 10-Feb-2021
 *      Author: sande
 */
#include<string.h>
#include"stm32f407xx.h"

#define HIGH         1
#define LOW          0
#define BTN_PRESSED  LOW

void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; i ++);
}

int main(void)
{
	GPIO_Handle_t GpioLed,GpioBtn;

	memset(&GpioLed,0,sizeof(GpioLed));
	memset(&GpioBtn,0,sizeof(GpioLed));

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//enable clock initialization

	//GPIO_PeriClockControl(GPIOD, ENABLE);

	//Call the API

	GPIO_Init(&GpioLed);

	GpioBtn.pGPIOx = GPIOD;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;


	//enable clock initialization

	//GPIO_PeriClockControl(GPIOD, ENABLE);

	//Call the API

	GPIO_Init(&GpioBtn);
	//IRQ Configurations
	//GPIO_WriteTo_Pin(GPIOD,GPIO_PIN_NO_12,GPIO_PIN_RESET);

	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5, ENABLE);

	while(1);

}
void EXTI9_5_IRQHandler(void)
{
    delay();
	GPIO_IRQHandling(GPIO_PIN_NO_5);
	//then write the toggle programme
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}
