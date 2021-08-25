/*
 * ConfigurationHelper.c
 *
 *  Created on: Mar 5, 2021
 *      Author: nadav
 */
#include "main.h"
//#include "FlashQSPIAgent.h"

void printRCConfiguration(bool toDisplayOnly)
{

	logData("", false, toDisplayOnly, false);
	logData("General Information", false, toDisplayOnly, false);
	sprintf(terminalBuffer,"RC Firmware Version: %2.2f, BuildID: %2.2f, Configuration: %2.2f \3",fwVersion, buildID, ee.configuration);
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer,"Unit Unique ID.................................: %ld %ld %ld\3",UID1, UID2, UID3);
	logData(terminalBuffer, false, toDisplayOnly, false);
	char localPairedDevice[17] = "";
	memcpy(localPairedDevice,ee.lastPairedDevice,16);
	localPairedDevice[16] = 0x00;
	sprintf(terminalBuffer,"Last Paired Device ID..........................: %s\3",localPairedDevice);
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer,"Battery voltage: %1.2f V\3", batteryVoltage);
	logData(terminalBuffer, false, toDisplayOnly, false);

	logData("-----------------System configuration----------------", false, toDisplayOnly, false);


	logData("", false, toDisplayOnly, false);
	logData("<Storage>", false, toDisplayOnly, false);
	sprintf(terminalBuffer,"Total storage volume: %6.2f MB", total_kb);
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer,"Free storage volume: %6.2f MB", free_kb);
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer,"Current log filename: %s", currentLogFilename);
	logData(terminalBuffer, false, toDisplayOnly, false);

	logData("----------------- EEPROM Saved Data ----------------", false, toDisplayOnly, false);
	sprintf(terminalBuffer, "Debug Level..........................[N/A].DBG: %d [%d/%d/%d]",
			ee.debugLevel, EEV_DebugLevel.min, EEV_DebugLevel.std, EEV_DebugLevel.max);
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer, "Screen Orientation..................[N/A].SCOR: %d [%d/%d/%d]",
			ee.screenOreintation, EEV_ScreenOrientation.min, EEV_ScreenOrientation.std, EEV_ScreenOrientation.max);
	logData(terminalBuffer, false, toDisplayOnly, false);
	logData("Enum: 0 - Landscape, 1 - Portrait", false, toDisplayOnly, false);
	sprintf(terminalBuffer, "Battery Type........................[N/A].UPBT: %d [%d/%d/%d]",
			ee.batteryType, EEV_BatteryType.min, EEV_BatteryType.std, EEV_BatteryType.max);
	logData(terminalBuffer, false, toDisplayOnly, false);
	logData("Enum: 1 - HCP902", false, toDisplayOnly, false);
	sprintf(terminalBuffer, "Legacy System...........................[N/A].: %d [%d/%d/%d]",
			ee.legacySystemType, EEV_LegacySystemType.min, EEV_LegacySystemType.std, EEV_LegacySystemType.max);
	logData(terminalBuffer, false, toDisplayOnly, false);

	// sprintf(term_buffer, "\r\n<External Applications>");
	logData("", false, toDisplayOnly, false);

	// sprintf(term_buffer, "\r\n<Kalman Filter Parameters>");

	sprintf(terminalBuffer, "<Channels Parameters>");
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer, "Arm PWM Off Value...................[N/A].APOF: %d [%d/%d/%d]",
			ee.armPWMOffValue, EEV_ArmPWMOffValue.min, EEV_ArmPWMOffValue.std, EEV_ArmPWMOffValue.max);
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer, "Arm PWM On Value....................[N/A].APON: %d [%d/%d/%d]",
			ee.armPWMOnValue, EEV_ArmPWMOnValue.min, EEV_ArmPWMOnValue.std, EEV_ArmPWMOnValue.max);
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer, "Trigger PWM Off Value...............[N/A].TPOF: %d [%d/%d/%d]",
			ee.triggerPWMOffValue, EEV_TriggerPWMOffValue.min, EEV_TriggerPWMOffValue.std, EEV_TriggerPWMOffValue.max);
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer, "Trigger PWM On Value................[N/A].TPON: %d [%d/%d/%d]",
			ee.triggerPWMOnValue, EEV_TriggerPWMOnValue.min, EEV_TriggerPWMOnValue.std, EEV_TriggerPWMOnValue.max);
	logData(terminalBuffer, false, toDisplayOnly, false);
	sprintf(terminalBuffer, "Link Type...........................[N/A].LNKT: %d [%d/%d/%d]",
			ee.linkType, EEV_LinkType.min, EEV_LinkType.std, EEV_LinkType.max);
	logData(terminalBuffer, false, toDisplayOnly, false);
	// sprintf(term_buffer, "\r\n<IO & Power Management Parameters>");

	// sprintf(term_buffer, "\r\n<Pyro Parameters>");

	//    logData("", false, toDisplayOnly);
	//    logData("<Active Arm/Disarm logic parameters>", false, toDisplayOnly);
	//    sendToM4Core("vib");
	//    sleep_ms(250);
	// sprintf(terminalBuffer, "%s, Vibrations threshold...................[N/A].VIB: %s", CT(), );
	// logData(terminalBuffer, false, toDisplayOnly);

	// sprintf(terminalBuffer, "%s, Velocity Threshold..........[m/Sec]....VAT: %-6.1f [%-6.1f/%-6.1f/%-6.1f]", CT(), ee.VelocityAbnormalThreshold, EEV_VelocityAbnormalThreshold.min, EEV_VelocityAbnormalThreshold.std, EEV_VelocityAbnormalThreshold.max);
	// logData(terminalBuffer, false, toDisplayOnly);

	// sprintf(term_buffer, "\r\n<VTOL Full Arming Parameters>");
	//    logData("", false, toDisplayOnly);
	//    logData("<Active Triggering Parameters>", false, toDisplayOnly);


	// sprintf(term_buffer, "\r\n<Triggering Logic>");

	// sprintf(term_buffer, "\r\n<VTOL Full Triggering Parameters>");

	// sprintf(term_buffer, "\r\n------------------Current Status---------------------");

	// logData("-----------------Triggering parameters---------------", false, toDisplayOnly);

	// logData("------------------Initialization---------------------", false, toDisplayOnly);

	logData("--------------Initialization Ended---------------------\3", false, toDisplayOnly, false);
	if (!sessionUnlocked)
	{
		logData("!Unit locked", false, true, false);
	}
	logData("\r\n", false, toDisplayOnly, true);
}
