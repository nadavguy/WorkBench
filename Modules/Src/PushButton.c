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
#include "LCD_1in8.h"
uint8_t armButtonCycle = 0;
uint8_t triggerButtonCycle = 0;

uint16_t armButtonPreviousValue = 0;
uint16_t triggerButtonPreviousValue = 0;

GPIO_PinState armPinState;
GPIO_PinState triggerPinState;
GPIO_PinState upPinState;
GPIO_PinState downPinState;
GPIO_PinState okPinState;
GPIO_PinState leftPinState;
GPIO_PinState rightPinState;
GPIO_PinState muxPinState;

uint32_t armButtonPressStart = 0;
uint32_t armButtonPressCycleStart = 0;
uint32_t armButtonPressDurationmSec[5] = {0};
uint32_t triggerButtonPressStart = 0;
uint32_t triggerButtonPressCycleStart = 0;
uint32_t triggerButtonPressDurationmSec[5] = {0};
uint32_t lastOkButtonPress = 0;
uint32_t lastDownButtonPress = 0;
uint32_t lastUpButtonPress = 0;
uint32_t lastOkButtonUnpress = 0;
uint32_t okButtonPressDuration = 0;
uint32_t lastAnyButtonPress = 0;
uint32_t lastMUXCheck = 0;
uint32_t buttonPressCounter = 0;


bool armButtonIsHigh = true;
bool armButtonIsLow = false;

bool triggerButtonIsHigh = true;
bool triggerButtonIsLow = false;

bool wasOKButtonPressed = false;


void CheckButtons(void)
{
	/*Get Buttons State */
	armPinState = HAL_GPIO_ReadPin(armGPIO, armPIN);
	triggerPinState = HAL_GPIO_ReadPin(triggerGPIO, triggerPIN);
	upPinState = HAL_GPIO_ReadPin(upGPIO, upPIN);
	downPinState = HAL_GPIO_ReadPin(downGPIO, downPIN);
	okPinState = HAL_GPIO_ReadPin(okGPIO, okPIN);

	if ( (armPinState == GPIO_PIN_RESET) || (triggerPinState == GPIO_PIN_RESET) || (upPinState == GPIO_PIN_RESET)
			|| (downPinState == GPIO_PIN_RESET) || (okPinState == GPIO_PIN_RESET) )
	{
		buttonPressCounter++;
		if (buttonPressCounter > 10)
		{
			lastAnyButtonPress = HAL_GetTick();
			buttonPressCounter= 0 ;
		}
	}

	if ( ((isDisableButtonDetection) && (HAL_GetTick() - lastAnyButtonPress > 500)) || (triggerPinState == GPIO_PIN_RESET) )
	{
		isDisableButtonDetection = false;
	}
	else if ( (isDisableButtonDetection) && (HAL_GetTick() - lastAnyButtonPress < 500) )
	{
		return;
	}

	if ( (!isScreenBrightFull) && (triggerPinState == GPIO_PIN_RESET) )
	{

	}
	else if (!isScreenBrightFull)
	{
		return;
	}
	else if ((isScreenBrightFull) && (isChargingMode) && (!isPopupDisplayed))
	{
		return;
	}

	/*Accumulate Button Press Pattern  */
	if (armPinState == GPIO_PIN_RESET)
	{
		if ( (armButtonIsHigh) && (!armButtonIsLow) )
		{
//			logData("Arm button pressed", false, false, false);
		}
	}
	else
	{
		if (armButtonIsLow)
		{

		}

		if ( (!armButtonIsHigh) && (armButtonIsLow) )
		{
//			logData("Arm button released", false, false, false);
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
		if ( (triggerButtonIsHigh) && (!triggerButtonIsLow) )
		{
//			logData("Trigger button pressed", false, false, false);
		}
		shouldRedrawButtonDotIcon = true;
		triggerButtonIsHigh = false;
		triggerButtonIsLow = true;

	}
	else
	{

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

		if ( (!triggerButtonIsHigh) && (triggerButtonIsLow) )
		{
//			logData("Trigger button relea/sed", false, false, false);
		}
		shouldRedrawButtonDotIcon = true;
		triggerButtonIsHigh = true;
		triggerButtonIsLow = false;
		triggerButtonPressStart = HAL_GetTick();
		if (triggerButtonCycle == 0)
		{
			triggerButtonPressCycleStart = HAL_GetTick();
		}
	}

	if ( (okPinState == GPIO_PIN_SET) /*&& (isPopupDisplayed)*/ )
	{
		lastOkButtonUnpress = HAL_GetTick();
		okButtonPressDuration = 0;
	}
	else
	{
		if (HAL_GetTick() - lastOkButtonUnpress > 100)
		{
			okButtonPressDuration = HAL_GetTick() - lastOkButtonUnpress;
		}
	}

	/* Act Upon Received Pattern */
	if ( (armButtonIsHigh) && (triggerButtonIsHigh) )
	{

	}
}

void checkChargerMux(void)
{
	if (HAL_GetTick() - lastMUXCheck > 1000)
	{
		muxPinState = HAL_GPIO_ReadPin(muxGPIO, muxPIN);
		if (muxPinState == GPIO_PIN_SET)
		{
//			isChargingMode = true;
		}
		else
		{
			isChargingMode = false;
		}
		lastMUXCheck = HAL_GetTick();
	}
}
