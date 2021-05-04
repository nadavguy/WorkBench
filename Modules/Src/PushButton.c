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
GPIO_PinState upPinState;
GPIO_PinState downPinState;
GPIO_PinState okPinState;
GPIO_PinState leftPinState;
GPIO_PinState rightPinState;

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

	if ( (rcState == PREINIT) && (armPinState == GPIO_PIN_RESET) )
	{
		rcState = MAINTENANCE;
	}

	/*Accumulate Button Press Pattern  */
	if (armPinState == GPIO_PIN_RESET)
	{
		if ( (armButtonIsHigh) && (!armButtonIsLow) )
		{
			logData("Arm button pressed", false, false, false);
		}
		armButtonIsHigh = false;
		armButtonIsLow = true;
		if ( (ee.linkType == PWM) && (rcState == OPERATIONAL) )
		{
			channelPWMValues[0] =  ((ee.armPWMOnValue - 1500) * 2);
		}
		else
		{
			channelPWMValues[0] =  ((ee.armPWMOffValue - 1500) * 2);
		}
	}
	else
	{
		if (armButtonIsLow)
		{
			if ( (ee.linkType == PWM) && (rcState == OPERATIONAL) )
			{
				channelPWMValues[0] = ((ee.armPWMOffValue - 1500) * 2);
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

		if ( (!armButtonIsHigh) && (armButtonIsLow) )
		{
			logData("Arm button released", false, false, false);
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
			logData("Trigger button pressed", false, false, false);
		}
		triggerButtonIsHigh = false;
		triggerButtonIsLow = true;
		if ( (ee.linkType == PWM) && (rcState == OPERATIONAL) )
		{
			channelPWMValues[1] = ((ee.triggerPWMOnValue - 1500) * 2);
		}
		else
		{
			channelPWMValues[1] = ((ee.triggerPWMOffValue - 1500) * 2);
		}
	}
	else
	{
		if ( (ee.linkType == PWM) && (rcState == OPERATIONAL) )
		{
			channelPWMValues[1] = ((ee.triggerPWMOffValue - 1500) * 2);
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

		if ( (!triggerButtonIsHigh) && (triggerButtonIsLow) )
		{
			logData("Trigger button released", false, false, false);
		}

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
		if ( (rcState == OPERATIONAL) && (ee.linkType == DIGITAL) )
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

	if ( (currentSmaStatus.smaState != ARMED) && (currentSmaStatus.smaState != TRIGGERED) )
	{
		if ( (okPinState == GPIO_PIN_RESET) && (!isMenuDisplayed) && (!isPopupDisplayed) && (HAL_GetTick() - lastOkButtonPress > 100))
		{
			isMenuDisplayed = true;
			shouldRenderMenu = true;
			shouldClearScreen = true;
			currentCursorPosition.currentPageID = 1;
			currentCursorPosition.cursorPosition = 0;
			lastOkButtonPress = HAL_GetTick();
			menuDrawDirection = FULL;
		}
		else if ( (okPinState == GPIO_PIN_RESET) && (isMenuDisplayed) && (!isItemDisplayed) && (HAL_GetTick() - lastOkButtonPress > 100) )
		{
			shouldClearScreen = true;
			itemDrawDirection = FULL;
			updateSelection();
			lastOkButtonPress = HAL_GetTick();
			menuDrawDirection = FULL;
		}
		else if ( (okPinState == GPIO_PIN_RESET) && (isMenuDisplayed) && (isItemDisplayed) && (HAL_GetTick() - lastOkButtonPress > 100) )
		{
			shouldClearScreen = false;
			if (currentCursorPosition.cursorPosition == 0x2)
			{
				currentCursorPosition.cursorPosition = VALUE;
				itemDrawDirection = RIGHT;
			}
			else if (currentCursorPosition.cursorPosition == 0x3)
			{
				currentCursorPosition.cursorPosition = MULTIPLIER;
				itemDrawDirection = RIGHT;
			}
			else if (currentCursorPosition.cursorPosition == 0x4)
			{
				isItemDisplayed = false;

			}
			else if (currentCursorPosition.cursorPosition == 0x5)
			{
				isParameterUpdateRequired = true;
				isItemDisplayed = false;
			}
			else if (currentCursorPosition.cursorPosition == VALUE)
			{
				currentCursorPosition.cursorPosition = 0x2;
				itemDrawDirection = LEFT;
			}
			else if (currentCursorPosition.cursorPosition == MULTIPLIER)
			{
				currentCursorPosition.cursorPosition = 0x3;
				itemDrawDirection = LEFT;
			}
			updateSelection();
			if (isParameterUpdateRequired)
			{
				updateSelectedParameter();
				isParameterUpdateRequired = false;
			}
			lastOkButtonPress = HAL_GetTick();

		}
		else if ( (downPinState == GPIO_PIN_RESET) && (isMenuDisplayed) && (!isItemDisplayed) && (HAL_GetTick() - lastDownButtonPress > 100) )
		{
			shouldRenderMenu = true;
			shouldClearScreen = false;
			currentCursorPosition.cursorPosition = fmin(currentCursorPosition.cursorPosition+1,
					pagesArray[currentCursorPosition.currentPageID].numberOfItemsInPage - 1);
			lastDownButtonPress = HAL_GetTick();
			menuDrawDirection = DOWN;
		}
		else if ( (downPinState == GPIO_PIN_RESET) && (isItemDisplayed) && (HAL_GetTick() - lastDownButtonPress > 100) )
		{
			shouldRenderItem = true;
			shouldClearScreen = false;
			if (currentCursorPosition.cursorPosition == 0x2)
			{
				currentCursorPosition.cursorPosition = 0x3;
			}
			else if (currentCursorPosition.cursorPosition == 0x3)
			{
				currentCursorPosition.cursorPosition = 0x4;
			}
			else if (currentCursorPosition.cursorPosition == 0x4)
			{
				currentCursorPosition.cursorPosition = 0x5;
			}
			else if (currentCursorPosition.cursorPosition == 0x5)
			{
				currentCursorPosition.cursorPosition = 0x5;
			}
			else if (currentCursorPosition.cursorPosition == VALUE)
			{
				currentCursorPosition.cursorPosition = VALUE;
			}
			else if (currentCursorPosition.cursorPosition == MULTIPLIER)
			{
				currentCursorPosition.cursorPosition = MULTIPLIER;
			}
			updateSelection();
			lastDownButtonPress = HAL_GetTick();
			itemDrawDirection = DOWN;
		}
		else if ((downPinState == GPIO_PIN_RESET) && (isPopupDisplayed) && (HAL_GetTick() - lastDownButtonPress > 100))
		{
			if (popupToShow.isQuestion)
			{
				shouldRenderPopup = true;
				popupDrawDirection = DOWN;
			}
		}
		else if ( (upPinState == GPIO_PIN_RESET) && (isMenuDisplayed) && (!isItemDisplayed) && (HAL_GetTick() - lastUpButtonPress > 100) )
		{
			shouldRenderMenu = true;
			shouldClearScreen = false;

			currentCursorPosition.cursorPosition = fmax(currentCursorPosition.cursorPosition - 1 , 0);
			lastUpButtonPress = HAL_GetTick();
			menuDrawDirection = UP;
		}
		else if ( (upPinState == GPIO_PIN_RESET) && (isItemDisplayed) && (HAL_GetTick() - lastUpButtonPress > 100) )
		{
			shouldRenderItem = true;
			shouldClearScreen = false;
			if (currentCursorPosition.cursorPosition == 0x2)
			{
				currentCursorPosition.cursorPosition = 0x2;
			}
			else if (currentCursorPosition.cursorPosition == 0x3)
			{
				currentCursorPosition.cursorPosition = 0x2;
			}
			else if (currentCursorPosition.cursorPosition == 0x4)
			{
				currentCursorPosition.cursorPosition = 0x3;
			}
			else if (currentCursorPosition.cursorPosition == 0x5)
			{
				currentCursorPosition.cursorPosition = 0x4;
			}
			else if (currentCursorPosition.cursorPosition == VALUE)
			{
				currentCursorPosition.cursorPosition = VALUE;
			}
			else if (currentCursorPosition.cursorPosition == MULTIPLIER)
			{
				currentCursorPosition.cursorPosition = MULTIPLIER;
			}
			updateSelection();
			lastUpButtonPress = HAL_GetTick();
			itemDrawDirection = UP;
		}
		else if ((upPinState == GPIO_PIN_RESET) && (isPopupDisplayed) && (HAL_GetTick() - lastDownButtonPress > 100))
		{
			if (popupToShow.isQuestion)
			{
				shouldRenderPopup = true;
				popupDrawDirection = UP;
			}
		}
//		if ( (okPinState == GPIO_PIN_SET) /*&& (isPopupDisplayed)*/ )
//		{
//			lastOkButtonUnpress = HAL_GetTick();
//			okButtonPressDuration = 0;
//		}
//		else
//		{
//			if (HAL_GetTick() - lastOkButtonUnpress > 100)
//			{
//				okButtonPressDuration = HAL_GetTick() - lastOkButtonUnpress;
//			}
//		}
	}
	else if ( (currentSmaStatus.smaState == ARMED) && (currentSmaStatus.smaState != TRIGGERED) )
	{
		//TODO: force disarm logic
		if ( (!isPopupDisplayed) && (okButtonPressDuration > 1000) )
		{
			isPopupDisplayed = true;
			shouldRenderPopup = true;
			memcpy(&popupToShow, &safeairForceDisarmMessage, sizeof(popupToShow));
			screenUpdate(false);
		}
//		if ( (isPopupDisplayed) && (okButtonPressDuration > 1000) )
//		{
//			isPopupDisplayed = true;
//			shouldRenderPopup = true;
//			memcpy(&popupToShow, &safeairForceDisarmMessage, sizeof(popupToShow));
//			screenUpdate(false);
//		}
	}
}
