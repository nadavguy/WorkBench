/*
 * PushButton.c
 *
 *  Created on: Mar 22, 2021
 *      Author: gilad
 */

#include <stdbool.h>
#include "PushButton.h"
uint8_t armButtonCycle = 0;
uint8_t triggerButtonCycle = 0;

uint16_t armButtonPreviousValue = 0;
uint16_t triggerButtonPreviousValue = 0;

GPIO_PinState armPinState;
GPIO_PinState triggerPinState;

uint32_t armButtonPressStart = 0;
uint32_t armButtonPressCycleStart = 0;
uint32_t armButtonPressDurationmSec[5] = {0};
uint32_t triggerButtonPressStart = 0;
uint32_t triggerButtonPressCycleStart = 0;
uint32_t triggerButtonPressDurationmSec[5] = {0};

bool armButtonIsHigh = false;
bool armButtonIsLow = false;

bool triggerButtonIsHigh = false;
bool triggerButtonIsLow = false;

void CheckButtons(void)
{
	armPinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
	if (armPinState == GPIO_PIN_RESET)
	{
		armButtonIsHigh = false;
		armButtonIsLow = true;
	}
	else
	{
		if (armButtonIsLow)
		{
			if (armButtonCycle < 5)
			{
				armButtonPressDurationmSec[armButtonCycle] = ((HAL_GetTick()
						- armButtonPressStart) / 100) * 100;
				armButtonCycle++;
			}
			if (armButtonCycle >= 5)
			{
				armButtonCycle = 0;
				memset(armButtonPressDurationmSec, 0, 20);
			}
		}

		if (HAL_GetTick() - armButtonPressCycleStart > 3000)
		{
			if (armButtonPressDurationmSec[0] >= 2000)
			{
				//Do this
//				sprintf(USBTXArray, "%6.3f, Do this\r\n", CurrentTime());
//				Print(false, true, true);
			}
			else if ((armButtonPressDurationmSec[0] >= 1000)
					&& (armButtonPressDurationmSec[1] >= 1000))
			{
				//Do that
//				sprintf(USBTXArray, "%6.3f, Do that\r\n", CurrentTime());
//				Print(false, true, true);
			}
			else if ((armButtonPressDurationmSec[0] >= 1000)
					&& (armButtonPressDurationmSec[1] == 0))
			{
				//Do that
//				sprintf(USBTXArray, "%6.3f, Do that Single Press\r\n",
//						CurrentTime());
//				Print(false, true, true);
			}
			else if ((armButtonPressDurationmSec[0] >= 500)
					&& (armButtonPressDurationmSec[1] >= 1000))
			{
				//Or maybe this
//				sprintf(USBTXArray, "%6.3f, Or maybe this\r\n", CurrentTime());
//				Print(false, true, true);

			}
			else if ((armButtonPressDurationmSec[0] >= 500)
					&& (armButtonPressDurationmSec[1] >= 500))
			{
				//Or maybe that
//				sprintf(USBTXArray, "%6.3f, Or maybe that\r\n", CurrentTime());
//				Print(false, true, true);
			}
			armButtonCycle = 0;
			memset(armButtonPressDurationmSec, 0, 20);
		}
//		SetRGB(250, 0, 0);
		armButtonIsHigh = true;
		armButtonIsLow = false;
		armButtonPressStart = HAL_GetTick();
		if (armButtonCycle == 0)
		{
			armButtonPressCycleStart = HAL_GetTick();
		}
	}
}
