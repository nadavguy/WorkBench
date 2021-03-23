/*
 * ConfigParams.c
 *
 *  Created on: Feb 7, 2021
 *      Author: gilad
 */

#include "main.h"

tEEV_FLOAT EEV_Vibrations = {0.0f, 0.08f, 12.0f}; 	//	[m/s^2] //Vibrations value to check landing
tEEV_U08 EEV_VibrationRelevantAxis = {1, 4, 7}; 	// 	Vibrations relevant axes
tEEV_U08 EEV_DebugLevel = {0, 0, 255}; 				// 	Debug Level
tEEV_U16 EEV_ActiveSensors = {0, 7, 255};			// 	Active Sensors used in safety logic

tEE_DATA ee;

uint32_t ee_invalid_counter = 0;

bool ee_validate1(void)
{
	ee_invalid_counter = 0;
	ee_invalid_counter += ee_validate_data(EEV_FLOAT, (pFLOAT)&ee.vibration, (pEEV_FLOAT)&EEV_Vibrations);
	ee_invalid_counter += ee_validate_data(EEV_U08, (pU08)&ee.vibrationRelevatAxis, (pEEV_U08)&EEV_VibrationRelevantAxis);
	ee_invalid_counter += ee_validate_data(EEV_U08, (pU08)&ee.debugLevel, (pEEV_U08)&EEV_DebugLevel);
	ee_invalid_counter += ee_validate_data(EEV_U16, (pU16)&ee.activeSensors, (pEEV_U16)&EEV_ActiveSensors);

	return (ee_invalid_counter == 0);
}
