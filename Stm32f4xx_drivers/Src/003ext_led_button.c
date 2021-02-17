/*
 * 001led_toggling.c
 *
 *  Created on: 10-Feb-2021
 *      Author: sande
 */
#include"stm32f407xx.h"

#define HIGH         1
#define LOW          0
#define BTN_PRESSED  LOW

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed,GpioBtn;
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//enable clock initialization

	//GPIO_PeriClockControl(GPIOA, ENABLE);

	//Call the API

	GPIO_Init(&GpioLed);

	GpioBtn.pGPIOx = GPIOB;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;


	//enable clock initialization

	//GPIO_PeriClockControl(GPIOB, ENABLE);

	//Call the API

	GPIO_Init(&GpioBtn);
	while(1)
	{
		if (GPIO_ReadFrom_Pin(GPIOB, GPIO_PIN_NO_12) == BTN_PRESSED)
		{
			//This is to overcome debouncing of the button
			delay();
			//toggle coomand
			GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO_8);

		}

	}
	return 0;
}
