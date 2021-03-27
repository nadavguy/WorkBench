/*
 * PushButton.c
 *
 *  Created on: Mar 22, 2021
 *      Author: gilad
 */

#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "PushButton.h"
#include "TBSAgent.h"
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
	/*Get Buttons State */
	armPinState = HAL_GPIO_ReadPin(armGPIO, armPIN);
	triggerPinState = HAL_GPIO_ReadPin(triggerGPIO, triggerPIN);
	if ( (rcState == PREINIT) && (armPinState == GPIO_PIN_SET) )
	{

	}

	/*Accumulate Button Press Pattern  */
	if (armPinState == GPIO_PIN_RESET)
	{
		armButtonIsHigh = false;
		armButtonIsLow = true;
		if ( (linkType == PWM) && (rcState == OPERATIONAL) )
		{
			channelPWMValues[0] =  ((2000 - 1500) * 2);
//			memset(rcChannelsFrame,0,26);
//			memcpy(rcChannelsFrame, TriggerMessageArray,26);
		}
	}
	else
	{
		if (armButtonIsLow)
		{
			if ( (linkType == PWM) && (rcState == OPERATIONAL) )
			{
				channelPWMValues[0] = ((1000 - 1500) * 2);
//				memset(rcChannelsFrame,0,26);
//				memcpy(rcChannelsFrame, IdleMessageArray,26);
			}
			uint32_t armLocalDuration = ((HAL_GetTick()
					- armButtonPressStart) / 100) * 100;
			if ( (armButtonCycle < 5) && (armLocalDuration > 100) )
			{
				armButtonPressDurationmSec[armButtonCycle] = armLocalDuration;
				armButtonCycle++;
			}
			if (armButtonCycle > 5)
			{
				armButtonCycle = 0;
				memset(armButtonPressDurationmSec, 0, 20);
			}
		}
		armButtonIsHigh = true;
		armButtonIsLow = false;
		armButtonPressStart = HAL_GetTick();
		if (armButtonCycle == 0)
		{
			armButtonPressCycleStart = HAL_GetTick();
		}
	}

	if (triggerPinState == GPIO_PIN_RESET)
	{
		triggerButtonIsHigh = false;
		triggerButtonIsLow = true;
		if ( (linkType == PWM) && (rcState == OPERATIONAL) )
		{
			channelPWMValues[1] = ((2000 - 1500) * 8 / 5);
		}
	}
	else
	{
		if ( (linkType == PWM) && (rcState == OPERATIONAL) )
		{
			channelPWMValues[1] = ((1000 - 1500) * 8 / 5);
		}
		if (triggerButtonIsLow)
		{
			uint32_t triggerLocalDuration = ((HAL_GetTick()
					- triggerButtonPressStart) / 100) * 100;
			if ( (triggerButtonCycle < 5) && (triggerLocalDuration > 100) )
			{
				triggerButtonPressDurationmSec[triggerButtonCycle] = triggerLocalDuration;
				triggerButtonCycle++;
			}
			if (triggerButtonCycle > 5)
			{
				triggerButtonCycle = 0;
				memset(triggerButtonPressDurationmSec, 0, 20);
			}
		}
		triggerButtonIsHigh = true;
		triggerButtonIsLow = false;
		triggerButtonPressStart = HAL_GetTick();
		if (triggerButtonCycle == 0)
		{
			triggerButtonPressCycleStart = HAL_GetTick();
		}
	}

	/* Act Upon Received Pattern */
	if ( (armButtonIsHigh) && (triggerButtonIsHigh) )
	{
		if ( (rcState == OPERATIONAL) && (linkType == DIGITAL) )
		{
			if (HAL_GetTick() - armButtonPressCycleStart > 5000)
			{
				if (armButtonPressDurationmSec[0] >= 3000)
				{

					//Do this --> Arm System

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
		}
	}
	//		SetRGB(250, 0, 0);
}
