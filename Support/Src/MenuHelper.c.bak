/*
 * MenuHelper.c
 *
 *  Created on: Apr 20, 2021
 *      Author: gilad
 */


#include "main.h"

tMENU_PAGE MainPage;
tMENU_PAGE TestPage;

tMENU_PAGE pagesArray[5];

tUINT16_ITEM brightnessItem;

void initMenuPages(void)
{
	MainPage.pageID = 1;
	MainPage.numberOfItemsInPage = 4;
	memcpy(&MainPage.itemsArray[0],"Trigger Mode",strlen("Trigger Mode"));
	memcpy(&MainPage.itemsArray[1],"Arm Mode",strlen("Arm Mode"));
	memcpy(&MainPage.itemsArray[2],"Page 2",strlen("Page 2"));
	memcpy(&MainPage.itemsArray[3],"Close menu",strlen("Close menu"));
	MainPage.cellTypeArray[0] = UINT8_ITEM;
	MainPage.cellTypeArray[1] = UINT8_ITEM;
	MainPage.cellTypeArray[2] = PAGE;
	MainPage.cellTypeArray[3] = CLOSE;
	MainPage.nextCellIDArray[0] = 0;
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
}

void initMenuItems(void)
{
	brightnessItem.itemID = 1;
	brightnessItem.maxValue = 2000;
	brightnessItem.minValue = 0;
	brightnessItem.startValue = 2000;
	brightnessItem.deltaMultiplier = 1;
	brightnessItem.numberOfItemsInPage = 6;
	memcpy(&brightnessItem.itemsArray[0],"Brightness",strlen("Brightness"));
	memcpy(&brightnessItem.itemsArray[1],"Units: [uSec]",strlen("Units: [uSec]"));
	memcpy(&brightnessItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&brightnessItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&brightnessItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&brightnessItem.itemsArray[5],"OK",strlen("OK"));
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
//	else if ( pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == ITEM )
//	{
//
//	}
	else
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
//			if (currentCursorPosition.cursorPosition == 0x02)
//			{
//				currentCursorPosition.cursorPosition = VALUE;
//			}
//			else
//			{
//				currentCursorPosition.cursorPosition = 0x02;
//			}
//			currentCursorPosition.menuDepth++;
			shouldRenderMenu = false;
			shouldRenderItem = true;
		}
		else if ( ( (currentCursorPosition.cursorPosition == 0x03) || (currentCursorPosition.cursorPosition == MULTIPLIER) )
				&& (currentCursorPosition.currentPageID == 0x00) && (isItemDisplayed) )
		{
//			if (currentCursorPosition.cursorPosition == 0x03)
//			{
//				currentCursorPosition.cursorPosition = MULTIPLIER;
//			}
//			else
//			{
//				currentCursorPosition.cursorPosition = 0x03;
//			}
//			currentCursorPosition.menuDepth++;
			shouldRenderMenu = false;
			shouldRenderItem = true;
		}
	}
}
