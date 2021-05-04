/*
 * MenuHelper.c
 *
 *  Created on: Apr 20, 2021
 *      Author: gilad
 */


#include "main.h"
#include "LCD_1in8.h"

tMENU_PAGE MainPage;
tMENU_PAGE TestPage;

tMENU_PAGE pagesArray[5];

tUINT16_ITEM brightnessItem;
tSTRING_ITEM triggerModeItem;

tPOPUP noConnectionMessage;
tPOPUP safeairForceDisarmMessage;


uint32_t itemIDtoUpdate = 0;

void initMenuPages(void)
{
	MainPage.pageID = 1;
	MainPage.numberOfItemsInPage = 4;
	memcpy(&MainPage.itemsArray[0],"Trigger Mode",strlen("Trigger Mode"));
	memcpy(&MainPage.itemsArray[1],"Arm Mode",strlen("Arm Mode"));
	memcpy(&MainPage.itemsArray[2],"Page 2",strlen("Page 2"));
	memcpy(&MainPage.itemsArray[3],"Close menu",strlen("Close menu"));
	MainPage.cellTypeArray[0] = STRING_ITEM;
	MainPage.cellTypeArray[1] = UINT8_ITEM;
	MainPage.cellTypeArray[2] = PAGE;
	MainPage.cellTypeArray[3] = CLOSE;
	MainPage.nextCellIDArray[0] = (uint32_t)&triggerModeItem;
	MainPage.nextCellIDArray[1] = 0;
	MainPage.nextCellIDArray[2] = 2;
	MainPage.nextCellIDArray[3] = 0;

	TestPage.pageID = 2;
	TestPage.numberOfItemsInPage = 4;
	memcpy(&TestPage.itemsArray[0],"Brightness",strlen("Brightness"));
	memcpy(&TestPage.itemsArray[1],"Page 3",strlen("Page 3"));
	memcpy(&TestPage.itemsArray[2],"Back",strlen("Back"));
	memcpy(&TestPage.itemsArray[3],"Close menu",strlen("Close menu"));
	TestPage.cellTypeArray[0] = UINT16_ITEM;
	TestPage.cellTypeArray[1] = PAGE;
	TestPage.cellTypeArray[2] = BACK;
	TestPage.cellTypeArray[3] = CLOSE;
	TestPage.nextCellIDArray[0] = (uint32_t)&brightnessItem;
	TestPage.nextCellIDArray[1] = 3;
	TestPage.nextCellIDArray[2] = 0;
	TestPage.nextCellIDArray[3] = 0;


	pagesArray[1] = MainPage;
	pagesArray[2] = TestPage;

	safeairConfiguration.MTD = 0;
	safeairConfiguration.armMode = 0;
	safeairConfiguration.forceDisarm = 0;
	safeairConfiguration.formatSD = 0;
	safeairConfiguration.loggingMode = 0;
	safeairConfiguration.platformType = 0;
	safeairConfiguration.state = 0;
	safeairConfiguration.triggerMode = 0;
}

void initMenuItems(void)
{
	brightnessItem.itemID = 1;
	brightnessItem.maxValue = EEV_Backlight.max;
	brightnessItem.minValue = EEV_Backlight.min;
	brightnessItem.startValue = ee.backLight;
	brightnessItem.deltaMultiplier = 1;
	brightnessItem.numberOfItemsInPage = 6;
	brightnessItem.parameterPointer = 0x00;
	memcpy(&brightnessItem.itemsArray[0],"Brightness",strlen("Brightness"));
	memcpy(&brightnessItem.itemsArray[1],"Units: [uSec]",strlen("Units: [uSec]"));
	memcpy(&brightnessItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&brightnessItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&brightnessItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&brightnessItem.itemsArray[5],"OK",strlen("OK"));

	triggerModeItem.itemID = 2;
	triggerModeItem.maxValue = 1;
	triggerModeItem.minValue = 0;
	triggerModeItem.startValue = 0;
	triggerModeItem.deltaMultiplier = 1;
	triggerModeItem.numberOfItemsInPage = 6;
	memcpy(&triggerModeItem.itemsArray[0],"Trigger Mode",strlen("Trigger Mode"));
	memcpy(&triggerModeItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&triggerModeItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&triggerModeItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&triggerModeItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&triggerModeItem.itemsArray[5],"OK",strlen("OK"));
	triggerModeItem.numberOfValuesInArray = 2;
	memcpy(&triggerModeItem.valuesArray[0],"Manual",strlen("Manual"));
	memcpy(&triggerModeItem.valuesArray[1],"Auto  ",strlen("Auto  "));
	triggerModeItem.parameterPointer = (uint32_t)&safeairConfiguration.triggerMode;
}

void initPopupMessages(void)
{
	noConnectionMessage.popupID = 1;
	noConnectionMessage.numberOfItemsInPopup = 6;
	noConnectionMessage.isQuestion = true;
	memcpy(&noConnectionMessage.itemsArray[0],"SafeAir unit",strlen("SafeAir unit"));
	memcpy(&noConnectionMessage.itemsArray[1],"not detected,",strlen("not detected,"));
	memcpy(&noConnectionMessage.itemsArray[2],"Changes will",strlen("Changes will "));
	memcpy(&noConnectionMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&noConnectionMessage.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&noConnectionMessage.itemsArray[5],"OK (Long Press)",strlen("OK (Long Press)"));

	safeairForceDisarmMessage.popupID = 2;
	safeairForceDisarmMessage.numberOfItemsInPopup = 5;
	safeairForceDisarmMessage.isQuestion = true;
	memcpy(&safeairForceDisarmMessage.itemsArray[0],"Force Disarm",strlen("Force Disarm"));
	memcpy(&safeairForceDisarmMessage.itemsArray[1],"SafeAir unit?,",strlen("SafeAir unit?"));
	memcpy(&safeairForceDisarmMessage.itemsArray[2],"Are you sure?",strlen("Are you sure?"));
//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&safeairForceDisarmMessage.itemsArray[3],"Cancel",strlen("Cancel"));
	memcpy(&safeairForceDisarmMessage.itemsArray[4],"OK (Long Press)",strlen("OK (Long Press)"));
}

void updateSelection(void)
{
	if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == CLOSE)
			&& (currentCursorPosition.currentPageID != 0x00) )
	{
		shouldRenderMenu = false;
		isMenuDisplayed = false;
		shouldReDrawPlatformIcon = true;
		shouldReDrawAutoPilotIcon = true;
		shouldRedrawSignalStrengthIcon = true;
		shouldReDrawBluetoothIcon = true;
		shouldReDrawTriggerModeIcon = true;
		shouldRedrawBatteryIcon = true;
		shouldUpdatePlatformText = true;
		shouldUpdateStatusText = true;
		setFullDisplay();
		screenClear();
		screenUpdate(false);
	}
	else if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == BACK)
			&& (currentCursorPosition.currentPageID != 0x00) )
	{
		currentCursorPosition.cursorPosition = currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1];
		currentCursorPosition.currentPageID = currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1];
		currentCursorPosition.menuDepth--;
		shouldRenderMenu = true;
	}
	else if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == PAGE)
			&& (currentCursorPosition.currentPageID != 0x00) )
	{
		currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth] = currentCursorPosition.cursorPosition;
		currentCursorPosition.previousPageID[currentCursorPosition.menuDepth] = currentCursorPosition.currentPageID;
		currentCursorPosition.currentPageID = pagesArray[currentCursorPosition.currentPageID].nextCellIDArray[currentCursorPosition.cursorPosition];
		currentCursorPosition.cursorPosition = 0;
		currentCursorPosition.menuDepth++;
		shouldRenderMenu = true;
	}
	else // handling Item navigation
	{
		if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] != VALUE)
				&& (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] != MULTIPLIER)
				&& (currentCursorPosition.currentPageID != 0x00))
		{
			currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth] = currentCursorPosition.cursorPosition;
			currentCursorPosition.previousPageID[currentCursorPosition.menuDepth] = currentCursorPosition.currentPageID;
			currentCursorPosition.currentPageID = 0;
			currentCursorPosition.cursorPosition = 2;
			currentCursorPosition.menuDepth++;
			shouldRenderMenu = false;
			shouldRenderItem = true;
		}
		else if ( ( (currentCursorPosition.cursorPosition == 0x02) || (currentCursorPosition.cursorPosition == VALUE) )
				&& (currentCursorPosition.currentPageID == 0x00) && (isItemDisplayed) )
		{
			shouldRenderMenu = false;
			shouldRenderItem = true;
		}
		else if ( ( (currentCursorPosition.cursorPosition == 0x03) || (currentCursorPosition.cursorPosition == MULTIPLIER) )
				&& (currentCursorPosition.currentPageID == 0x00) && (isItemDisplayed) )
		{
			shouldRenderMenu = false;
			shouldRenderItem = true;
		}
		else if ( (currentCursorPosition.cursorPosition == 0x04)
				&& (currentCursorPosition.currentPageID == 0x00) && (isMenuDisplayed) && (!isItemDisplayed) )
		{
			currentCursorPosition.cursorPosition = currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1];
			currentCursorPosition.currentPageID = currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1];
			currentCursorPosition.menuDepth--;
			isMenuDisplayed = true;
			shouldClearScreen = true;
			shouldRenderItem = false;
			shouldRenderMenu = true;
		}
		else if ( (currentCursorPosition.cursorPosition == 0x05)
				&& (currentCursorPosition.currentPageID == 0x00) && (isMenuDisplayed) && (!isItemDisplayed) )
		{
			if ( pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
					cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == UINT16_ITEM )
			{
				memcpy((uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
						nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], &uint16Item,  sizeof(tUINT16_ITEM));
			}
			else if (pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
					cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == STRING_ITEM)
			{
				memcpy((uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
						nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], &stringItem,  sizeof(tSTRING_ITEM));
			}
			currentCursorPosition.cursorPosition = currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1];
			currentCursorPosition.currentPageID = currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1];
			currentCursorPosition.menuDepth--;
			isItemDisplayed = false;
			isMenuDisplayed = true;
			shouldClearScreen = true;
			shouldRenderItem = false;
			shouldRenderMenu = true;
		}
	}
}

void updateSelectedParameter(void)
{
	if (itemIDtoUpdate == 1)
	{
		ee.backLight = brightnessItem.startValue;
		LCD_1IN8_SetBackLight(ee.backLight);
		ee_save1();
	}
	else if (itemIDtoUpdate == 2)
	{
		//Send to Sma - How to Block if SMA not connected
		safeairConfiguration.triggerMode = stringItem.startValue + 1;
//		sendSafeAirConfigurationMessage();
		configurationMessageCounter++;
//		memset(stringItem, 0, sizeof(stringItem));
	}
}
