/*
 * ConfigurationHelper.c
 *
 *  Created on: Mar 5, 2021
 *      Author: nadav
 */
#include "main.h"
#include "FlashQSPIAgent.h"

void printRCConfiguration(bool toDisplayOnly)
{

    logData("", false, toDisplayOnly);
    logData("General Information", false, toDisplayOnly);
    sprintf(terminalBuffer,"RC Firmware - Version: %3.2f, BuildID: %3.2f", fwVersion, BuildID);
    logData(terminalBuffer, false, toDisplayOnly);

    logData("-----------------System configuration----------------", false, toDisplayOnly);


    logData("", false, toDisplayOnly);
    logData("<Storage>", false, toDisplayOnly);
    sprintf(terminalBuffer,"Total storage volume: %6.2f MB", total_kb);
    logData(terminalBuffer, false, toDisplayOnly);
    sprintf(terminalBuffer,"Free storage volume: %6.2f MB", free_kb);
    logData(terminalBuffer, false, toDisplayOnly);
    sprintf(terminalBuffer,"Current log filename: %s", currentLogFilename);
    logData(terminalBuffer, false, toDisplayOnly);

    logData("----------------- EEPROM Saved Data ----------------", false, toDisplayOnly);
    sprintf(terminalBuffer, "Debug Level.........................[N/A].DBG: %d [%d/%d/%d]",
            ee.debugLevel, EEV_DebugLevel.min, EEV_DebugLevel.std, EEV_DebugLevel.max);
    logData(terminalBuffer, false, toDisplayOnly);
//    logData("Bitmap: 1 - M4 Debug Data, 2 - BMI160 (Acc & Gyro),  4 - BMM150 (Mag)", false, toDisplayOnly);

    // sprintf(term_buffer, "\r\n<External Applications>");
    logData("", false, toDisplayOnly);

    // sprintf(term_buffer, "\r\n<Kalman Filter Parameters>");

     sprintf(terminalBuffer, "\r\n<Channels Parameters>");
     logData(terminalBuffer, false, toDisplayOnly);
     sprintf(terminalBuffer, "Arm PWM Off Value...................[N/A].APOF: %d [%d/%d/%d]",
    		 ee.armPWMOffValue, EEV_ArmPWMOffValue.min, EEV_ArmPWMOffValue.std, EEV_ArmPWMOffValue.max);
     logData(terminalBuffer, false, toDisplayOnly);
     sprintf(terminalBuffer, "Arm PWM On Value....................[N/A].APON: %d [%d/%d/%d]",
    		 ee.armPWMOnValue, EEV_ArmPWMOnValue.min, EEV_ArmPWMOnValue.std, EEV_ArmPWMOnValue.max);
     logData(terminalBuffer, false, toDisplayOnly);
     sprintf(terminalBuffer, "Trigger PWM Off Value...............[N/A].TPOF: %d [%d/%d/%d]",
    		 ee.triggerPWMOffValue, EEV_TriggerPWMOffValue.min, EEV_TriggerPWMOffValue.std, EEV_TriggerPWMOffValue.max);
     logData(terminalBuffer, false, toDisplayOnly);
     sprintf(terminalBuffer, "Trigger PWM On Value................[N/A].TPON: %d [%d/%d/%d]",
    		 ee.triggerPWMOnValue, EEV_TriggerPWMOnValue.min, EEV_TriggerPWMOnValue.std, EEV_TriggerPWMOnValue.max);
     logData(terminalBuffer, false, toDisplayOnly);
     sprintf(terminalBuffer, "Link Type...........................[N/A].LNKT: %d [%d/%d/%d]",
    		 ee.linkType, EEV_LinkType.min, EEV_LinkType.std, EEV_LinkType.max);
     logData(terminalBuffer, false, toDisplayOnly);
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
}
