/*
 * ConfigParams.c
 *
 *  Created on: Feb 7, 2021
 *      Author: gilad
 */

#include "main.h"

//tEEV_FLOAT EEV_Vibrations = {0.0f, 0.08f, 12.0f}; 	//	[m/s^2] //Vibrations value to check landing
tEEV_U08 EEV_DebugLevel = {0, 0, 32}; 				// 	Debug Level
tEEV_U16 EEV_ArmPWMOffValue = {1000, 1000, 2000};
tEEV_U16 EEV_ArmPWMOnValue = {1000, 2000, 2000};
tEEV_U16 EEV_TriggerPWMOffValue = {1000, 1000, 2000};
tEEV_U16 EEV_TriggerPWMOnValue = {1000, 2000, 2000};
tEEV_U08 EEV_LinkType = {0, 0, 1};
tEEV_U16 EEV_Backlight = {0, 1000, 1000};
tEEV_U08 EEV_ScreenOrientation = {0, 0, 1};

tEE_DATA ee;
tCONFIG_DATA safeairConfiguration;

uint32_t ee_invalid_counter = 0;

bool ee_validate1(void)
{
	ee_invalid_counter = 0;
//	ee_invalid_counter += ee_validate_data(EEV_FLOAT, (pFLOAT)&ee.vibration, (pEEV_FLOAT)&EEV_Vibrations);
	ee_invalid_counter += ee_validate_data(EEV_U08, (pU08)&ee.debugLevel, (pEEV_U08)&EEV_DebugLevel);
	ee_invalid_counter += ee_validate_data(EEV_U16, (pU16)&ee.armPWMOffValue, (pEEV_U16)&EEV_ArmPWMOffValue);
	ee_invalid_counter += ee_validate_data(EEV_U16, (pU16)&ee.armPWMOnValue, (pEEV_U16)&EEV_ArmPWMOnValue);
	ee_invalid_counter += ee_validate_data(EEV_U16, (pU16)&ee.triggerPWMOffValue, (pEEV_U16)&EEV_TriggerPWMOffValue);
	ee_invalid_counter += ee_validate_data(EEV_U16, (pU16)&ee.triggerPWMOnValue, (pEEV_U16)&EEV_TriggerPWMOnValue);
	ee_invalid_counter += ee_validate_data(EEV_U08, (pU08)&ee.linkType, (pEEV_U08)&EEV_LinkType);
	ee_invalid_counter += ee_validate_data(EEV_U16, (pU16)&ee.backLight, (pEEV_U16)&EEV_Backlight);
	ee_invalid_counter += ee_validate_data(EEV_U08, (pU08)&ee.screenOreintation, (pEEV_U08)&EEV_ScreenOrientation);

	return (ee_invalid_counter == 0);
}
