/*
 * MenuHelper.c
 *
 *  Created on: Apr 20, 2021
 *      Author: gilad
 */


#include "main.h"
#include "LCD_1in8.h"

MENULEVELType menuLevel = BASIC;

tMENU_PAGE MainPage;
tMENU_PAGE rcSettingsPage;
tMENU_PAGE safeAirSettingsPage;
tMENU_PAGE blueToothSettingsPage;
tMENU_PAGE integrationPage;

tMENU_PAGE pagesArray[6];

tUINT16_ITEM brightnessItem;
tUINT16_ITEM motorDelayItem;

tSTRING_ITEM triggerModeItem;
tSTRING_ITEM armModeItem;
tSTRING_ITEM loggingModeItem;
tSTRING_ITEM platformTypeItem;
tSTRING_ITEM safeairStateItem;
tSTRING_ITEM legacySystemItem;
tSTRING_ITEM LowerBarDisplayItem;
//tSTRING_ITEM bleMakeVisibleItem;
//tSTRING_ITEM bleDisableItem;

tPOPUP noConnectionMessage;
tPOPUP safeairForceDisarmMessage;
tPOPUP rcClearStorageMessage;
tPOPUP safeAirClearStorageMessage;
tPOPUP bleMakeVisibleMessage;
tPOPUP bleDisableMessage;
tPOPUP massStorageMessage;
tPOPUP aboutRCMessage;
tPOPUP aboutBLEMessage;
tPOPUP tbsInChargeModeMessage;
tPOPUP autoCalibrationMessage;
tPOPUP testFlightMessage;
tPOPUP testMotorCutMessage;
tPOPUP returnToIdleMessage;
tPOPUP disconnectPyroMessage;

bool isTestCalibActive = false;
bool isAutoCalibActive = false;

uint32_t itemIDtoUpdate = 0;

void initMenuPages(void)
{

	for (int i = 0 ; i < MAX_ITEMS_IN_PAGE ; i++ )
	{
		memset(MainPage.itemsArray[i],0 , MAX_CHARACTERS_IN_ITEM);
		memset(rcSettingsPage.itemsArray[i],0 , MAX_CHARACTERS_IN_ITEM);
		memset(safeAirSettingsPage.itemsArray[i],0 , MAX_CHARACTERS_IN_ITEM);
		memset(blueToothSettingsPage.itemsArray[i],0 , MAX_CHARACTERS_IN_ITEM);
	}

	MainPage.pageID = 1;
	if ( (menuLevel == DEVELOPER) || (menuLevel == OEM) )
	{
		MainPage.numberOfItemsInPage = 5;
		memcpy(&MainPage.itemsArray[0],"RC Settings",strlen("RC Settings"));
		memcpy(&MainPage.itemsArray[1],"SA Settings",strlen("SA Settings"));
		memcpy(&MainPage.itemsArray[2],"Integration",strlen("Integration"));
		memcpy(&MainPage.itemsArray[3],"About RC",strlen("About RC"));
		memcpy(&MainPage.itemsArray[4],"Close menu",strlen("Close menu"));

		MainPage.cellTypeArray[0] = PAGE;
		MainPage.cellTypeArray[1] = PAGE;
		MainPage.cellTypeArray[2] = PAGE;
		MainPage.cellTypeArray[3] = POPUP;
		MainPage.cellTypeArray[4] = CLOSE;

		MainPage.nextCellIDArray[0] = 2;
		MainPage.nextCellIDArray[1] = 3;
		MainPage.nextCellIDArray[2] = 5;
		MainPage.nextCellIDArray[3] = (uint32_t)&aboutRCMessage;
		MainPage.nextCellIDArray[4] = 0;
	}
	else
	{
		MainPage.numberOfItemsInPage = 3;
		memcpy(&MainPage.itemsArray[0],"RC Settings",strlen("RC Settings"));
		memcpy(&MainPage.itemsArray[1],"About RC",strlen("About RC"));
		memcpy(&MainPage.itemsArray[2],"Close menu",strlen("Close menu"));

		MainPage.cellTypeArray[0] = PAGE;
		MainPage.cellTypeArray[1] = POPUP;
		MainPage.cellTypeArray[2] = CLOSE;

		MainPage.nextCellIDArray[0] = 2;
		MainPage.nextCellIDArray[1] = (uint32_t)&aboutRCMessage;
		MainPage.nextCellIDArray[2] = 0;
	}

	rcSettingsPage.pageID = 2;
	if (menuLevel == DEVELOPER)
	{
		rcSettingsPage.numberOfItemsInPage = 7;
		memcpy(&rcSettingsPage.itemsArray[0],"Brightness",strlen("Brightness"));
		memcpy(&rcSettingsPage.itemsArray[1],"Mass Storage",strlen("Mass Storage"));
		memcpy(&rcSettingsPage.itemsArray[2],"Clear RC Flash",strlen("Clear RC Flash"));
		memcpy(&rcSettingsPage.itemsArray[3],"Safeair Systems",strlen("Safeair Systems"));
		memcpy(&rcSettingsPage.itemsArray[4],"BlueTooth",strlen("BlueTooth"));
		memcpy(&rcSettingsPage.itemsArray[5],"Back",strlen("Back"));
		memcpy(&rcSettingsPage.itemsArray[6],"Close menu",strlen("Close menu"));
		rcSettingsPage.cellTypeArray[0] = UINT16_ITEM;
		rcSettingsPage.cellTypeArray[1] = POPUP;
		rcSettingsPage.cellTypeArray[2] = POPUP;
		rcSettingsPage.cellTypeArray[3] = STRING_ITEM;
		rcSettingsPage.cellTypeArray[4] = PAGE;
		rcSettingsPage.cellTypeArray[5] = BACK;
		rcSettingsPage.cellTypeArray[6] = CLOSE;
		rcSettingsPage.nextCellIDArray[0] = (uint32_t)&brightnessItem;
		rcSettingsPage.nextCellIDArray[1] = (uint32_t)&massStorageMessage;
		rcSettingsPage.nextCellIDArray[2] = (uint32_t)&rcClearStorageMessage;
		rcSettingsPage.nextCellIDArray[3] = (uint32_t)&legacySystemItem;
		rcSettingsPage.nextCellIDArray[4] = 4;
		rcSettingsPage.nextCellIDArray[5] = 0;
		rcSettingsPage.nextCellIDArray[6] = 0;
	}
	else
	{
		rcSettingsPage.numberOfItemsInPage = 6;
		memcpy(&rcSettingsPage.itemsArray[0],"Brightness",strlen("Brightness"));
		memcpy(&rcSettingsPage.itemsArray[1],"Mass Storage",strlen("Mass Storage"));
		memcpy(&rcSettingsPage.itemsArray[2],"Clear RC Flash",strlen("Clear RC Flash"));
		memcpy(&rcSettingsPage.itemsArray[3],"Safeair Systems",strlen("Safeair Systems"));
		memcpy(&rcSettingsPage.itemsArray[4],"Back",strlen("Back"));
		memcpy(&rcSettingsPage.itemsArray[5],"Close menu",strlen("Close menu"));
		rcSettingsPage.cellTypeArray[0] = UINT16_ITEM;
		rcSettingsPage.cellTypeArray[1] = POPUP;
		rcSettingsPage.cellTypeArray[2] = POPUP;
		rcSettingsPage.cellTypeArray[3] = STRING_ITEM;
		rcSettingsPage.cellTypeArray[4] = BACK;
		rcSettingsPage.cellTypeArray[5] = CLOSE;
		rcSettingsPage.nextCellIDArray[0] = (uint32_t)&brightnessItem;
		rcSettingsPage.nextCellIDArray[1] = (uint32_t)&massStorageMessage;
		rcSettingsPage.nextCellIDArray[2] = (uint32_t)&rcClearStorageMessage;
		rcSettingsPage.nextCellIDArray[3] = (uint32_t)&legacySystemItem;
		rcSettingsPage.nextCellIDArray[4] = 0;
		rcSettingsPage.nextCellIDArray[5] = 0;
	}

	safeAirSettingsPage.pageID = 3;
	safeAirSettingsPage.numberOfItemsInPage = 9;
	memcpy(&safeAirSettingsPage.itemsArray[0],"Trigger Mode",strlen("Trigger Mode"));
	memcpy(&safeAirSettingsPage.itemsArray[1],"Arm Mode",strlen("Arm Mode"));
	memcpy(&safeAirSettingsPage.itemsArray[2],"Logging Mode",strlen("Logging Mode"));
	memcpy(&safeAirSettingsPage.itemsArray[3],"Motors Delay",strlen("Motors Delay"));
	memcpy(&safeAirSettingsPage.itemsArray[4],"Platform Type",strlen("Platform Type"));
	memcpy(&safeAirSettingsPage.itemsArray[5],"Change State",strlen("Change State"));
	memcpy(&safeAirSettingsPage.itemsArray[6],"Clear SA Flash",strlen("Clear SA Flash"));
	memcpy(&safeAirSettingsPage.itemsArray[7],"Back",strlen("Back"));
	memcpy(&safeAirSettingsPage.itemsArray[8],"Close menu",strlen("Close menu"));
	safeAirSettingsPage.cellTypeArray[0] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[1] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[2] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[3] = UINT16_ITEM;
	safeAirSettingsPage.cellTypeArray[4] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[5] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[6] = POPUP;
	safeAirSettingsPage.cellTypeArray[7] = BACK;
	safeAirSettingsPage.cellTypeArray[8] = CLOSE;
	safeAirSettingsPage.nextCellIDArray[0] = (uint32_t)&triggerModeItem;
	safeAirSettingsPage.nextCellIDArray[1] = (uint32_t)&armModeItem;
	safeAirSettingsPage.nextCellIDArray[2] = (uint32_t)&loggingModeItem;
	safeAirSettingsPage.nextCellIDArray[3] = (uint32_t)&motorDelayItem;
	safeAirSettingsPage.nextCellIDArray[4] = (uint32_t)&platformTypeItem;
	safeAirSettingsPage.nextCellIDArray[5] = (uint32_t)&safeairStateItem;
	safeAirSettingsPage.nextCellIDArray[6] = (uint32_t)&safeAirClearStorageMessage;
	safeAirSettingsPage.nextCellIDArray[7] = 0;
	safeAirSettingsPage.nextCellIDArray[8] = 0;

	blueToothSettingsPage.pageID = 4;
	blueToothSettingsPage.numberOfItemsInPage = 5;
	memcpy(&blueToothSettingsPage.itemsArray[0],"Make visible",strlen("Make visible"));
	memcpy(&blueToothSettingsPage.itemsArray[1],"Disable BLE",strlen("Disable BLE"));
	memcpy(&blueToothSettingsPage.itemsArray[2],"About BLE",strlen("About BLE"));
	memcpy(&blueToothSettingsPage.itemsArray[3],"Back",strlen("Back"));
	memcpy(&blueToothSettingsPage.itemsArray[4],"Close menu",strlen("Close menu"));
	blueToothSettingsPage.cellTypeArray[0] = POPUP;
	blueToothSettingsPage.cellTypeArray[1] = POPUP;
	blueToothSettingsPage.cellTypeArray[2] = POPUP;
	blueToothSettingsPage.cellTypeArray[3] = BACK;
	blueToothSettingsPage.cellTypeArray[4] = CLOSE;
	blueToothSettingsPage.nextCellIDArray[0] = (uint32_t)&bleMakeVisibleMessage;
	blueToothSettingsPage.nextCellIDArray[1] = (uint32_t)&bleDisableMessage;
	blueToothSettingsPage.nextCellIDArray[2] = (uint32_t)&aboutBLEMessage;
	blueToothSettingsPage.nextCellIDArray[3] = 0;
	blueToothSettingsPage.nextCellIDArray[4] = 0;


	integrationPage.pageID = 5;
	if ( (menuLevel == DEVELOPER) || (menuLevel == OEM) )
	{
		integrationPage.numberOfItemsInPage = 6;
		if (!isAutoCalibActive)
		{
			memcpy(&integrationPage.itemsArray[0],"Init Auto-Calib",strlen("Init Auto-Calib"));
		}
		else
		{
			memcpy(&integrationPage.itemsArray[0],"Stop Auto-Calib",strlen("Stop Auto-Calib"));
		}
		if (!isTestCalibActive)
		{
			memcpy(&integrationPage.itemsArray[1],"Init Calib Test",strlen("Init Calib Test"));
		}
		else
		{
			memcpy(&integrationPage.itemsArray[1],"Stop Calib Test",strlen("Stop Calib Test"));
		}
		memcpy(&integrationPage.itemsArray[2],"Test Motor-Cut",strlen("Test Motor-Cut"));
		memcpy(&integrationPage.itemsArray[3],"Lower Bar Info",strlen("Lower Bar Info"));
		memcpy(&integrationPage.itemsArray[4],"Back",strlen("Back"));
		memcpy(&integrationPage.itemsArray[5],"Close menu",strlen("Close menu"));

		integrationPage.cellTypeArray[0] = POPUP;
		integrationPage.cellTypeArray[1] = POPUP;
		integrationPage.cellTypeArray[2] = POPUP;
		integrationPage.cellTypeArray[3] = STRING_ITEM;
		integrationPage.cellTypeArray[4] = BACK;
		integrationPage.cellTypeArray[5] = CLOSE;

		if (!(currentSmaStatus.BITStatus & 0x04) && (!isAutoCalibActive) && (!isTestCalibActive))
		{
			integrationPage.nextCellIDArray[0] = (uint32_t)&disconnectPyroMessage;
			integrationPage.nextCellIDArray[1] = (uint32_t)&disconnectPyroMessage;
		}
		else if (currentSmaStatus.smaState == IDLE)
		{
			integrationPage.nextCellIDArray[0] = (uint32_t)&autoCalibrationMessage;
			integrationPage.nextCellIDArray[1] = (uint32_t)&testFlightMessage;
			integrationPage.nextCellIDArray[2] = (uint32_t)&testMotorCutMessage;
		}
		else
		{
			if (isAutoCalibActive)
			{
				integrationPage.nextCellIDArray[0] = (uint32_t)&autoCalibrationMessage;
			}
			else
			{
				integrationPage.nextCellIDArray[0] = (uint32_t)&returnToIdleMessage;
			}

			if (isTestCalibActive)
			{
				integrationPage.nextCellIDArray[1] = (uint32_t)&testFlightMessage;
			}
			else
			{
				integrationPage.nextCellIDArray[1] = (uint32_t)&returnToIdleMessage;
			}

//			if (currentSmaStatus.smaState != IDLE)
//			{
				integrationPage.nextCellIDArray[2] = (uint32_t)&returnToIdleMessage;
//			}
		}
		integrationPage.nextCellIDArray[3] = (uint32_t)&LowerBarDisplayItem;
		integrationPage.nextCellIDArray[4] = 0;
		integrationPage.nextCellIDArray[5] = 0;
	}
//	else
//	{
//		integrationPage.numberOfItemsInPage = 3;
//		memcpy(&integrationPage.itemsArray[0],"RC Settings",strlen("RC Settings"));
//		memcpy(&integrationPage.itemsArray[1],"About RC",strlen("About RC"));
//		memcpy(&integrationPage.itemsArray[2],"Close menu",strlen("Close menu"));
//
//		integrationPage.cellTypeArray[0] = PAGE;
//		integrationPage.cellTypeArray[1] = POPUP;
//		integrationPage.cellTypeArray[2] = CLOSE;
//
//		integrationPage.nextCellIDArray[0] = 2;
//		integrationPage.nextCellIDArray[1] = (uint32_t)&aboutRCMessage;
//		integrationPage.nextCellIDArray[2] = 0;
//	}


	pagesArray[1] = MainPage;
	pagesArray[2] = rcSettingsPage;
	pagesArray[3] = safeAirSettingsPage;
	pagesArray[4] = blueToothSettingsPage;
	pagesArray[5] = integrationPage;

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

	armModeItem.itemID = 3;
	armModeItem.maxValue = 1;
	armModeItem.minValue = 0;
	armModeItem.startValue = 0;
	armModeItem.deltaMultiplier = 1;
	armModeItem.numberOfItemsInPage = 6;
	memcpy(&armModeItem.itemsArray[0],"Arm Mode",strlen("Arm Mode"));
	memcpy(&armModeItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&armModeItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&armModeItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&armModeItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&armModeItem.itemsArray[5],"OK",strlen("OK"));
	armModeItem.numberOfValuesInArray = 2;
	memcpy(&armModeItem.valuesArray[0],"Manual",strlen("Manual"));
	memcpy(&armModeItem.valuesArray[1],"Auto  ",strlen("Auto  "));
	armModeItem.parameterPointer = (uint32_t)&safeairConfiguration.armMode;

	loggingModeItem.itemID = 4;
	loggingModeItem.maxValue = 3;
	loggingModeItem.minValue = 0;
	loggingModeItem.startValue = 0;
	loggingModeItem.deltaMultiplier = 1;
	loggingModeItem.numberOfItemsInPage = 6;
	memcpy(&loggingModeItem.itemsArray[0],"Logging Mode",strlen("Logging Mode"));
	memcpy(&loggingModeItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&loggingModeItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&loggingModeItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&loggingModeItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&loggingModeItem.itemsArray[5],"OK",strlen("OK"));
	loggingModeItem.numberOfValuesInArray = 4;
	memcpy(&loggingModeItem.valuesArray[0],"0 - Raw ",strlen("0 - Raw "));
	memcpy(&loggingModeItem.valuesArray[1],"Minimal ",strlen("Minimal "));
	memcpy(&loggingModeItem.valuesArray[2],"Ext. IMU",strlen("Ext. IMU"));
	memcpy(&loggingModeItem.valuesArray[3],"Diluted ",strlen("Diluted "));
	loggingModeItem.parameterPointer = (uint32_t)&safeairConfiguration.loggingMode;

	motorDelayItem.itemID = 5;
	motorDelayItem.maxValue = 5000;
	motorDelayItem.minValue = 50;
	motorDelayItem.startValue = ee.motorDelayValue;
	motorDelayItem.deltaMultiplier = 1;
	motorDelayItem.numberOfItemsInPage = 6;
	motorDelayItem.parameterPointer = 0x00;
	memcpy(&motorDelayItem.itemsArray[0],"Motor Delay",strlen("Motor Delay"));
	memcpy(&motorDelayItem.itemsArray[1],"Units: [mSec]",strlen("Units: [mSec]"));
	memcpy(&motorDelayItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&motorDelayItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&motorDelayItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&motorDelayItem.itemsArray[5],"OK",strlen("OK"));

	platformTypeItem.itemID = 6;
	platformTypeItem.maxValue = 4;
	platformTypeItem.minValue = 1;
	platformTypeItem.startValue = 1;
	platformTypeItem.deltaMultiplier = 1;
	platformTypeItem.numberOfItemsInPage = 6;
	memcpy(&platformTypeItem.itemsArray[0],"Platform Type",strlen("Platform Type"));
	memcpy(&platformTypeItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&platformTypeItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&platformTypeItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&platformTypeItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&platformTypeItem.itemsArray[5],"OK",strlen("OK"));
	platformTypeItem.numberOfValuesInArray = 4;
	memcpy(&platformTypeItem.valuesArray[0],"Mlt-rtr",strlen("Mlt-rtr"));
	memcpy(&platformTypeItem.valuesArray[1],"Vrtcl  ",strlen("Vrtcl  "));
	memcpy(&platformTypeItem.valuesArray[2],"Trnsmtn",strlen("Trnsmtn"));
	memcpy(&platformTypeItem.valuesArray[3],"Hrzntl ",strlen("Hrzntl "));
	platformTypeItem.parameterPointer = (uint32_t)&safeairConfiguration.platformType;

	safeairStateItem.itemID = 7;
	safeairStateItem.maxValue = 4;
	safeairStateItem.minValue = 3;
	safeairStateItem.startValue = 3;
	safeairStateItem.deltaMultiplier = 1;
	safeairStateItem.numberOfItemsInPage = 6;
	memcpy(&safeairStateItem.itemsArray[0],"SA state",strlen("SA state"));
	memcpy(&safeairStateItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&safeairStateItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&safeairStateItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&safeairStateItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&safeairStateItem.itemsArray[5],"OK",strlen("OK"));
	safeairStateItem.numberOfValuesInArray = 2;
	memcpy(&safeairStateItem.valuesArray[0],"Mntnnc",strlen("Mntnnc"));
	memcpy(&safeairStateItem.valuesArray[1],"At-Clb",strlen("At-Clb"));
	safeairStateItem.parameterPointer = (uint32_t)&safeairConfiguration.state;

	legacySystemItem.itemID = 8;
	legacySystemItem.maxValue = 3;
	legacySystemItem.minValue = 0;
	legacySystemItem.startValue = 2;
	legacySystemItem.deltaMultiplier = 1;
	legacySystemItem.numberOfItemsInPage = 6;
	memcpy(&legacySystemItem.itemsArray[0],"Drone Type",strlen("Drone Type"));
	memcpy(&legacySystemItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&legacySystemItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&legacySystemItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&legacySystemItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&legacySystemItem.itemsArray[5],"OK",strlen("OK"));
	legacySystemItem.numberOfValuesInArray = 3;
	memcpy(&legacySystemItem.valuesArray[0],"Phantom",strlen("Phantom"));
	memcpy(&legacySystemItem.valuesArray[1],"Mavic  ",strlen("Mavic  "));
	memcpy(&legacySystemItem.valuesArray[2],"SafeAir",strlen("SafeAir"));
	memcpy(&legacySystemItem.valuesArray[3],"Auto   ",strlen("Auto   "));
	legacySystemItem.parameterPointer = (uint32_t)&currentSmaStatus.smaPlatformName;

	LowerBarDisplayItem.itemID = 9 ;
	LowerBarDisplayItem.maxValue = 2;
	LowerBarDisplayItem.minValue = 0;
	LowerBarDisplayItem.startValue = 0;
	LowerBarDisplayItem.deltaMultiplier = 1;
	LowerBarDisplayItem.numberOfItemsInPage = 6;
	memcpy(&LowerBarDisplayItem.itemsArray[0],"Data Display",strlen("Data Display"));
	memcpy(&LowerBarDisplayItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&LowerBarDisplayItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&LowerBarDisplayItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&LowerBarDisplayItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&LowerBarDisplayItem.itemsArray[5],"OK",strlen("OK"));
	LowerBarDisplayItem.numberOfValuesInArray = 3;
	memcpy(&LowerBarDisplayItem.valuesArray[0],"Alt    ",strlen("Alt    "));
	memcpy(&LowerBarDisplayItem.valuesArray[1],"Clb Tmr",strlen("Clb Tmr"));
	memcpy(&LowerBarDisplayItem.valuesArray[2],"Auto   ",strlen("Auto   "));
	LowerBarDisplayItem.parameterPointer = (uint32_t)&lowerBarDisplayID;

//	bleMakeVisibleItem.itemID = 4;
//	bleMakeVisibleItem.maxValue = 1;
//	bleMakeVisibleItem.minValue = 0;
//	bleMakeVisibleItem.startValue = 0;
//	bleMakeVisibleItem.deltaMultiplier = 1;
//	bleMakeVisibleItem.numberOfItemsInPage = 6;
//	memcpy(&bleMakeVisibleItem.itemsArray[0],"Bluetooth",strlen("Bluetooth"));
//	memcpy(&bleMakeVisibleItem.itemsArray[1],"Make visible",strlen("Make visible"));
//	memcpy(&bleMakeVisibleItem.itemsArray[2],"Value",strlen("Value"));
//	memcpy(&bleMakeVisibleItem.itemsArray[3],"Delta",strlen("Delta"));
//	memcpy(&bleMakeVisibleItem.itemsArray[4],"Cancel",strlen("Cancel"));
//	memcpy(&bleMakeVisibleItem.itemsArray[5],"OK",strlen("OK"));
//	bleMakeVisibleItem.numberOfValuesInArray = 2;
//	memcpy(&bleMakeVisibleItem.valuesArray[0],"On ",strlen("On "));
//	memcpy(&bleMakeVisibleItem.valuesArray[1],"Off",strlen("Off"));
//	bleMakeVisibleItem.parameterPointer = (uint32_t)&isBLEOn;
}

void initPopupMessages(void)
{
	noConnectionMessage.popupID = 1;
	noConnectionMessage.numberOfItemsInPopup = 8;
	noConnectionMessage.isQuestion = false;
	memcpy(&noConnectionMessage.itemsArray[0],"SafeAir unit",strlen("SafeAir unit"));
	memcpy(&noConnectionMessage.itemsArray[1],"not detected,",strlen("not detected,"));
	memcpy(&noConnectionMessage.itemsArray[2],"Changes will",strlen("Changes will "));
	memcpy(&noConnectionMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&noConnectionMessage.itemsArray[4],"",strlen(""));
	memcpy(&noConnectionMessage.itemsArray[5],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&noConnectionMessage.itemsArray[6],"Cancel",strlen("Cancel"));
	memcpy(&noConnectionMessage.itemsArray[7],"OK",strlen("OK"));

	safeairForceDisarmMessage.popupID = 2;
	safeairForceDisarmMessage.numberOfItemsInPopup = 7;
	safeairForceDisarmMessage.isQuestion = true;
	memcpy(&safeairForceDisarmMessage.itemsArray[0],"Force Disarm",strlen("Force Disarm"));
	memcpy(&safeairForceDisarmMessage.itemsArray[1],"SafeAir unit?,",strlen("SafeAir unit?"));
	memcpy(&safeairForceDisarmMessage.itemsArray[2],"Are you sure?",strlen("Are you sure?"));
	memcpy(&safeairForceDisarmMessage.itemsArray[3],"",strlen(""));
	memcpy(&safeairForceDisarmMessage.itemsArray[4],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&safeairForceDisarmMessage.itemsArray[5],"Cancel",strlen("Cancel"));
	memcpy(&safeairForceDisarmMessage.itemsArray[6],"OK",strlen("OK"));

	rcClearStorageMessage.popupID = 3;
	rcClearStorageMessage.numberOfItemsInPopup = 7;
	rcClearStorageMessage.isQuestion = true;
	memcpy(&rcClearStorageMessage.itemsArray[0],"Clear RC",strlen("Clear RC"));
	memcpy(&rcClearStorageMessage.itemsArray[1],"Storage,",strlen("Storage,"));
	memcpy(&rcClearStorageMessage.itemsArray[2],"Are you sure?",strlen("Are you sure?"));
	memcpy(&rcClearStorageMessage.itemsArray[3],"",strlen(""));
	memcpy(&rcClearStorageMessage.itemsArray[4],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&rcClearStorageMessage.itemsArray[5],"Cancel",strlen("Cancel"));
	memcpy(&rcClearStorageMessage.itemsArray[6],"OK",strlen("OK"));

	safeAirClearStorageMessage.popupID = 4;
	safeAirClearStorageMessage.numberOfItemsInPopup = 7;
	safeAirClearStorageMessage.isQuestion = true;
	memcpy(&safeAirClearStorageMessage.itemsArray[0],"Clear SafeAir",strlen("Clear SafeAir"));
	memcpy(&safeAirClearStorageMessage.itemsArray[1],"Storage,",strlen("Storage,"));
	memcpy(&safeAirClearStorageMessage.itemsArray[2],"Are you sure?",strlen("Are you sure?"));
	memcpy(&safeAirClearStorageMessage.itemsArray[3],"",strlen(""));
	memcpy(&safeAirClearStorageMessage.itemsArray[4],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&safeAirClearStorageMessage.itemsArray[5],"Cancel",strlen("Cancel"));
	memcpy(&safeAirClearStorageMessage.itemsArray[6],"OK",strlen("OK"));

	bleMakeVisibleMessage.popupID = 5;
	bleMakeVisibleMessage.numberOfItemsInPopup = 5;
	bleMakeVisibleMessage.isQuestion = true;
	memcpy(&bleMakeVisibleMessage.itemsArray[0],"Make bluetooth",strlen("Make bluetooth"));
	memcpy(&bleMakeVisibleMessage.itemsArray[1],"visible for",strlen("visible for"));
	memcpy(&bleMakeVisibleMessage.itemsArray[2],"detection?",strlen("detection?"));
	//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&bleMakeVisibleMessage.itemsArray[3],"No",strlen("No"));
	memcpy(&bleMakeVisibleMessage.itemsArray[4],"Yes",strlen("Yes"));

	bleDisableMessage.popupID = 6;
	bleDisableMessage.numberOfItemsInPopup = 4;
	bleDisableMessage.isQuestion = true;
	memcpy(&bleDisableMessage.itemsArray[0],"Disable bluetooth",strlen("Disable bluetooth"));
	memcpy(&bleDisableMessage.itemsArray[1],"module?",strlen("module?"));
//	memcpy(&bleDisableMessage.itemsArray[2],"detection?",strlen("detection?"));
	//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&bleDisableMessage.itemsArray[2],"No",strlen("No"));
	memcpy(&bleDisableMessage.itemsArray[3],"Yes",strlen("Yes"));

	massStorageMessage.popupID = 7;
	massStorageMessage.numberOfItemsInPopup = 4;
	massStorageMessage.isQuestion = true;
	memcpy(&massStorageMessage.itemsArray[0],"Change to mass",strlen("Change to mass"));
	memcpy(&massStorageMessage.itemsArray[1],"storage device?",strlen("storage device?"));
//	memcpy(&massStorageMessage.itemsArray[2],"storage?",strlen("detection?"));
	//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&massStorageMessage.itemsArray[2],"No",strlen("No"));
	memcpy(&massStorageMessage.itemsArray[3],"Yes",strlen("Yes"));

	aboutRCMessage.popupID = 8;
	aboutRCMessage.numberOfItemsInPopup = 5;
	aboutRCMessage.isQuestion = false;
	sprintf(aboutRCMessage.itemsArray[0],"FW: %1.2f", fwVersion);
	sprintf(aboutRCMessage.itemsArray[1],"BuildID: %1.2f", buildID);
	sprintf(aboutRCMessage.itemsArray[2],"Config: %1.2f", ee.configuration);
	//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&aboutRCMessage.itemsArray[3],"No",strlen("No"));
	memcpy(&aboutRCMessage.itemsArray[4],"OK",strlen("OK"));

	aboutBLEMessage.popupID = 9;
	aboutBLEMessage.numberOfItemsInPopup = 5;
	aboutBLEMessage.isQuestion = false;
	sprintf(aboutBLEMessage.itemsArray[0],"MAC: %s", bleParameters.macAddress);
	sprintf(aboutBLEMessage.itemsArray[1],"Name:");
	sprintf(aboutBLEMessage.itemsArray[2],"%s", bleParameters.bleName);
	//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&aboutBLEMessage.itemsArray[3],"No",strlen("No"));
	memcpy(&aboutBLEMessage.itemsArray[4],"OK",strlen("OK"));

	tbsInChargeModeMessage.popupID = 10;
	tbsInChargeModeMessage.numberOfItemsInPopup = 8;
	tbsInChargeModeMessage.isQuestion = false;
	memcpy(&tbsInChargeModeMessage.itemsArray[0],"RC in charge",strlen("RC in charge"));
	memcpy(&tbsInChargeModeMessage.itemsArray[1],"mode, TX module",strlen("mode, TX module"));
	memcpy(&tbsInChargeModeMessage.itemsArray[2],"is not powered",strlen("is not powered"));
	memcpy(&tbsInChargeModeMessage.itemsArray[3],"",strlen(""));
	memcpy(&tbsInChargeModeMessage.itemsArray[4],"",strlen(""));
	memcpy(&tbsInChargeModeMessage.itemsArray[5],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&tbsInChargeModeMessage.itemsArray[6],"Cancel",strlen("Cancel"));
	memcpy(&tbsInChargeModeMessage.itemsArray[7],"OK",strlen("OK"));

	autoCalibrationMessage.popupID = 11;
	autoCalibrationMessage.numberOfItemsInPopup = 8;
	autoCalibrationMessage.isQuestion = true;
	if (!isAutoCalibActive)
	{
		memcpy(&autoCalibrationMessage.itemsArray[0],"Approve to init",strlen("Approve to init"));
		memcpy(&autoCalibrationMessage.itemsArray[1],"auto-calib",strlen("auto-calib"));
	}
	else
	{
		memcpy(&autoCalibrationMessage.itemsArray[0],"Approve to stop",strlen("Approve to stop"));
		memcpy(&autoCalibrationMessage.itemsArray[1],"auto-calib",strlen("auto-calib"));
	}
	memcpy(&autoCalibrationMessage.itemsArray[2],"",strlen(""));
	memcpy(&autoCalibrationMessage.itemsArray[3],"",strlen(""));
	memcpy(&autoCalibrationMessage.itemsArray[4],"",strlen(""));
	memcpy(&autoCalibrationMessage.itemsArray[5],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&autoCalibrationMessage.itemsArray[6],"Cancel",strlen("Cancel"));
	memcpy(&autoCalibrationMessage.itemsArray[7],"OK",strlen("OK"));

	testFlightMessage.popupID = 12;
	testFlightMessage.numberOfItemsInPopup = 8;
	testFlightMessage.isQuestion = true;
	if (!isTestCalibActive)
	{
		memcpy(&testFlightMessage.itemsArray[0],"Approve to init",strlen("Approve to init"));
		memcpy(&testFlightMessage.itemsArray[1],"calib test",strlen("calib test"));
	}
	else
	{
		memcpy(&testFlightMessage.itemsArray[0],"Approve to stop",strlen("Approve to stop"));
		memcpy(&testFlightMessage.itemsArray[1],"calib test",strlen("calib test"));
	}
	memcpy(&testFlightMessage.itemsArray[2],"",strlen(""));
	memcpy(&testFlightMessage.itemsArray[3],"",strlen(""));
	memcpy(&testFlightMessage.itemsArray[4],"",strlen(""));
	memcpy(&testFlightMessage.itemsArray[5],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&testFlightMessage.itemsArray[6],"Cancel",strlen("Cancel"));
	memcpy(&testFlightMessage.itemsArray[7],"OK",strlen("OK"));

	testMotorCutMessage.popupID = 13;
	testMotorCutMessage.numberOfItemsInPopup = 8;
	testMotorCutMessage.isQuestion = true;
	memcpy(&testMotorCutMessage.itemsArray[0],"Approve to init",strlen("Approve to init"));
	memcpy(&testMotorCutMessage.itemsArray[1],"motor-cut test",strlen("motor-cut test"));
	memcpy(&testMotorCutMessage.itemsArray[2],"",strlen(""));
	memcpy(&testMotorCutMessage.itemsArray[3],"",strlen(""));
	memcpy(&testMotorCutMessage.itemsArray[4],"",strlen(""));
	memcpy(&testMotorCutMessage.itemsArray[5],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&testMotorCutMessage.itemsArray[6],"Cancel",strlen("Cancel"));
	memcpy(&testMotorCutMessage.itemsArray[7],"OK",strlen("OK"));

	returnToIdleMessage.popupID = 14;
	returnToIdleMessage.numberOfItemsInPopup = 8;
	returnToIdleMessage.isQuestion = false;
	memcpy(&returnToIdleMessage.itemsArray[0],"SafeAir is not",strlen("SafeAir is not"));
	memcpy(&returnToIdleMessage.itemsArray[1],"in Idle state,",strlen("in Idle state,"));
	memcpy(&returnToIdleMessage.itemsArray[2],"Change SafeAir",strlen("Change SafeAir"));
	memcpy(&returnToIdleMessage.itemsArray[3],"state and try",strlen("state and try"));
	memcpy(&returnToIdleMessage.itemsArray[4],"again",strlen("again"));
	memcpy(&returnToIdleMessage.itemsArray[5],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&returnToIdleMessage.itemsArray[6],"Cancel",strlen("Cancel"));
	memcpy(&returnToIdleMessage.itemsArray[7],"OK",strlen("OK"));

	disconnectPyroMessage.popupID = 15;
	disconnectPyroMessage.numberOfItemsInPopup = 8;
	disconnectPyroMessage.isQuestion = false;
	memcpy(&disconnectPyroMessage.itemsArray[0],"SafeAir's pyro",strlen("SafeAir's pyro"));
	memcpy(&disconnectPyroMessage.itemsArray[1],"is connected.",strlen("is connected."));
	memcpy(&disconnectPyroMessage.itemsArray[2],"Disconnect it",strlen("Disconnect it"));
	memcpy(&disconnectPyroMessage.itemsArray[3],"and try again",strlen("and try again"));
	memcpy(&disconnectPyroMessage.itemsArray[4],"",strlen(""));
	memcpy(&disconnectPyroMessage.itemsArray[5],"->Long Press<-",strlen("->Long Press<-"));
	memcpy(&disconnectPyroMessage.itemsArray[6],"Cancel",strlen("Cancel"));
	memcpy(&disconnectPyroMessage.itemsArray[7],"OK",strlen("OK"));
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
		createEmptyFrame(false, true);
		screenUpdate(false);
		if (ee.informationLevel & 0x02)
		{
			sprintf(terminalBuffer, "Analytics, Closed Menu - Page ID:, 0");
			logData(terminalBuffer, true, false, false);
		}
	}
	else if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == BACK)
			&& (currentCursorPosition.currentPageID != 0x00) )
	{
		currentCursorPosition.cursorPosition = currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1];
		currentCursorPosition.currentPageID = currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1];
		currentCursorPosition.menuDepth--;
		shouldRenderMenu = true;
		shouldRenderItem = false;
		shouldRenderPopup = false;
		if (ee.informationLevel & 0x02)
		{
			sprintf(terminalBuffer, "Analytics, Moved back in menu - Page ID:, %d", currentCursorPosition.currentPageID);
			logData(terminalBuffer, true, false, false);
		}
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
		shouldRenderItem = false;
		shouldRenderPopup = false;
		if (ee.informationLevel & 0x02)
		{
			sprintf(terminalBuffer, "Analytics, Opened Menu - Page ID:, %d", currentCursorPosition.currentPageID);
			logData(terminalBuffer, true, false, false);
		}
	}
	else if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == POPUP)
			&& (currentCursorPosition.currentPageID != 0x00) )
	{
		initMenuPages();
		memcpy(&popupToShow, (uint32_t *)pagesArray[currentCursorPosition.currentPageID].nextCellIDArray[currentCursorPosition.cursorPosition] , sizeof(popupToShow));
		shouldRenderMenu = false;
		shouldRenderItem = false;
		shouldRenderPopup = true;
		popupDrawDirection = FULL;
		waitForPopupInput();

		isMenuDisplayed = true;
		shouldRenderMenu = true;
		shouldRenderItem = false;
		shouldRenderPopup = false;
		if (ee.informationLevel & 0x02)
		{
			sprintf(terminalBuffer, "Analytics, Displayed Popup ID:, %d, Is Question: ,%s", popupToShow.popupID, popupToShow.isQuestion ? "true" : "false");
			logData(terminalBuffer, true, false, false);
		}
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
			shouldRenderPopup = false;
		}
		else if ( ( (currentCursorPosition.cursorPosition == 0x02) || (currentCursorPosition.cursorPosition == VALUE) )
				&& (currentCursorPosition.currentPageID == 0x00) && (isItemDisplayed) )
		{
			shouldRenderMenu = false;
			shouldRenderItem = true;
			shouldRenderPopup = false;
		}
		else if ( ( (currentCursorPosition.cursorPosition == 0x03) || (currentCursorPosition.cursorPosition == MULTIPLIER) )
				&& (currentCursorPosition.currentPageID == 0x00) && (isItemDisplayed) )
		{
			shouldRenderMenu = false;
			shouldRenderItem = true;
			shouldRenderPopup = false;
		}
		else if ( (currentCursorPosition.cursorPosition == 0x04)
				&& (currentCursorPosition.currentPageID == 0x00) && (isMenuDisplayed) && (!isItemDisplayed) )
		{
			currentCursorPosition.cursorPosition = currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1];
			currentCursorPosition.currentPageID = currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1];
			currentCursorPosition.menuDepth--;
			isMenuDisplayed = true;
			shouldClearScreen = true;
			shouldRenderMenu = true;
			shouldRenderItem = false;
			shouldRenderPopup = false;

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
			shouldRenderMenu = true;
			shouldRenderItem = false;
			shouldRenderPopup = false;
		}
	}
}

void updateSelectedParameter(void)
{
	if (ee.informationLevel & 0x02)
	{
		sprintf(terminalBuffer, "Analytics, Updated Item ID:, %ld", itemIDtoUpdate);
		logData(terminalBuffer, true, false, false);
	}
	if (itemIDtoUpdate == 1)
	{
		ee.backLight = brightnessItem.startValue;
		LCD_1IN8_SetBackLight(ee.backLight * 2000);
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
	else if (itemIDtoUpdate == 3)
	{
		safeairConfiguration.armMode = stringItem.startValue + 1;
		configurationMessageCounter++;
	}
	else if (itemIDtoUpdate == 4)
	{
		safeairConfiguration.loggingMode = stringItem.startValue + 1;
		configurationMessageCounter++;
	}
	else if (itemIDtoUpdate == 5)
	{
		safeairConfiguration.MTD = stringItem.startValue;
		configurationMessageCounter++;
	}
	else if (itemIDtoUpdate == 6)
	{
		safeairConfiguration.platformType = stringItem.startValue + 1;
		configurationMessageCounter++;
	}
//	else if (itemIDtoUpdate == 7)
//	{
//		safeairConfiguration.platformType = stringItem.startValue + 1;
//		configurationMessageCounter++;
//	}
	else if (itemIDtoUpdate == 8)
	{
//		currentSmaStatus.smaPlatformName = stringItem.startValue + 4;
		if (stringItem.startValue + 4 != 7)
		{
			ee.legacySystemType = stringItem.startValue + 4;
			currentSmaStatus.smaPlatformName = stringItem.startValue + 4;
			isLegacyDronePlatform = true;
			logData("RC set to legacy mode", false, false, false);
		}
		else
		{
			currentSmaStatus.smaPlatformName = 0;
			ee.legacySystemType = 0;
			isLegacyDronePlatform = false;
			logData("RC exited to legacy mode", false, false, false);
		}
		ee_save1();
	}
	else if (itemIDtoUpdate == 9)
	{
		lowerBarDisplayID = stringItem.startValue;
	}
}
