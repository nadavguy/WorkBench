/*
 * TBSAgent.c
 *
 *  Created on: Mar 22, 2021
 *      Author: gilad
 */

#include "main.h"
#include "usart.h"
#include "TBSAgent.h"
#include "Common.h"

#define CROSSFIRE_CH_CENTER         0x3E0
#define CROSSFIRE_CH_BITS           11
#define CROSSFIRE_CHANNELS_COUNT    16

uint8_t tbsRXArray[TBS_RX_BUFFER] = {0};
uint8_t rcChannelsFrame[26] = {0};
uint8_t tbsPingMessage[8] = {0};
uint8_t safeairConfigurationFrame[29] = {0};

uint8_t IdleMessageArray[26] = {0xC8, 0x18, 0x16, 0xAC, 0x60, 0x05, 0x2B, 0x58, 0xC1, 0x0A, 0x56, 0xB0, 0x82, 0x15, 0xAC, 0x60, 0x05, 0x2B, 0x58, 0xC1, 0x0A, 0x56, 0xB0, 0x82, 0x15, 0x5B};
uint8_t TriggerMessageArray[26] = {0xC8, 0x18, 0x16, 0xA4, 0x26, 0x35, 0xA9, 0x49, 0x4D, 0x6A, 0x52, 0x93, 0x9A, 0xD4, 0xA4, 0x26, 0x35, 0xA9, 0x49, 0x4D, 0x6A, 0x52, 0x93, 0x9A, 0xD4, 0x64};
uint8_t messagesMissed = 0;

int16_t channelPWMValues[16] = {((1000 - 1500) * 8 / 5 + 992)};
uint16_t previousBITStatus = 0;

uint32_t lastCRSFChannelMessage = 0;
uint32_t lastLoggedLinkMessage = 0;
uint32_t lastLoggedSafeAirStatusMessage = 0;
uint32_t lastReceivedDroneDataMessage = 0;
uint32_t lastReceivedLinkMessage = 0;
uint32_t configurationMessageCounter = 0;
uint32_t configurationMessageCounterReceived = 0;
uint32_t lastConfigurationMessageSent = 0;
uint32_t safeAirLogID = 0;
uint32_t safeAirTime = 0;
uint32_t lastReceivedCRSFMessage = 0;
uint32_t durationMultiplier = 0;
uint32_t remainingCalibrationTime = 0;

bool isTBSDisconnected = false;
bool isTailIDAlreadyReceived = false;
bool shouldAddTimeToConfigurationMessage = false;
bool isLegacyDronePlatform = false;
bool isSMABatteryCritical = false;
bool isSMABatteryLow = false;
bool isSMABatteryMedium = false;
bool everReceivedConfigurationMessage = false;

char safeAirTailID[12] = "";

tRC_LINK rcLinkStatus;
tSMA_Status previousSmaStatus;
tSMA_Status currentSmaStatus;

// CRC8 implementation with polynom = x^8+x^7+x^6+x^4+x^2+1 (0xD5)
const unsigned char crc8tab[256] = {
  0x00, 0xD5, 0x7F, 0xAA, 0xFE, 0x2B, 0x81, 0x54,
  0x29, 0xFC, 0x56, 0x83, 0xD7, 0x02, 0xA8, 0x7D,
  0x52, 0x87, 0x2D, 0xF8, 0xAC, 0x79, 0xD3, 0x06,
  0x7B, 0xAE, 0x04, 0xD1, 0x85, 0x50, 0xFA, 0x2F,
  0xA4, 0x71, 0xDB, 0x0E, 0x5A, 0x8F, 0x25, 0xF0,
  0x8D, 0x58, 0xF2, 0x27, 0x73, 0xA6, 0x0C, 0xD9,
  0xF6, 0x23, 0x89, 0x5C, 0x08, 0xDD, 0x77, 0xA2,
  0xDF, 0x0A, 0xA0, 0x75, 0x21, 0xF4, 0x5E, 0x8B,
  0x9D, 0x48, 0xE2, 0x37, 0x63, 0xB6, 0x1C, 0xC9,
  0xB4, 0x61, 0xCB, 0x1E, 0x4A, 0x9F, 0x35, 0xE0,
  0xCF, 0x1A, 0xB0, 0x65, 0x31, 0xE4, 0x4E, 0x9B,
  0xE6, 0x33, 0x99, 0x4C, 0x18, 0xCD, 0x67, 0xB2,
  0x39, 0xEC, 0x46, 0x93, 0xC7, 0x12, 0xB8, 0x6D,
  0x10, 0xC5, 0x6F, 0xBA, 0xEE, 0x3B, 0x91, 0x44,
  0x6B, 0xBE, 0x14, 0xC1, 0x95, 0x40, 0xEA, 0x3F,
  0x42, 0x97, 0x3D, 0xE8, 0xBC, 0x69, 0xC3, 0x16,
  0xEF, 0x3A, 0x90, 0x45, 0x11, 0xC4, 0x6E, 0xBB,
  0xC6, 0x13, 0xB9, 0x6C, 0x38, 0xED, 0x47, 0x92,
  0xBD, 0x68, 0xC2, 0x17, 0x43, 0x96, 0x3C, 0xE9,
  0x94, 0x41, 0xEB, 0x3E, 0x6A, 0xBF, 0x15, 0xC0,
  0x4B, 0x9E, 0x34, 0xE1, 0xB5, 0x60, 0xCA, 0x1F,
  0x62, 0xB7, 0x1D, 0xC8, 0x9C, 0x49, 0xE3, 0x36,
  0x19, 0xCC, 0x66, 0xB3, 0xE7, 0x32, 0x98, 0x4D,
  0x30, 0xE5, 0x4F, 0x9A, 0xCE, 0x1B, 0xB1, 0x64,
  0x72, 0xA7, 0x0D, 0xD8, 0x8C, 0x59, 0xF3, 0x26,
  0x5B, 0x8E, 0x24, 0xF1, 0xA5, 0x70, 0xDA, 0x0F,
  0x20, 0xF5, 0x5F, 0x8A, 0xDE, 0x0B, 0xA1, 0x74,
  0x09, 0xDC, 0x76, 0xA3, 0xF7, 0x22, 0x88, 0x5D,
  0xD6, 0x03, 0xA9, 0x7C, 0x28, 0xFD, 0x57, 0x82,
  0xFF, 0x2A, 0x80, 0x55, 0x01, 0xD4, 0x7E, 0xAB,
  0x84, 0x51, 0xFB, 0x2E, 0x7A, 0xAF, 0x05, 0xD0,
  0xAD, 0x78, 0xD2, 0x07, 0x53, 0x86, 0x2C, 0xF9
};

void sendChannelMessageToTBS(void)
{
	if ( (HAL_GetTick() - lastCRSFChannelMessage > 8) && ( (messagesMissed < 30) || (triggerPinState == GPIO_PIN_RESET) ) )
	{
		memset(rcChannelsFrame, 0, 26);
		createCrossfireChannelsFrame(rcChannelsFrame, channelPWMValues);
		HAL_UART_Transmit_IT(&TBS_UART, rcChannelsFrame, 26);
		lastCRSFChannelMessage = HAL_GetTick();
		messagesMissed++;
	}
	else if ( ( (HAL_GetTick() - lastCRSFChannelMessage <= 8)  && ( HAL_GetTick() - lastCRSFChannelMessage > 1) )
			|| messagesMissed >= 30)
	{
		HAL_UART_Receive_DMA(&TBS_UART, tbsRXArray,TBS_RX_BUFFER);
		HAL_Delay(2);
		parseTBSMessage();
		sendSafeAirConfigurationMessage(shouldAddTimeToConfigurationMessage);
		messagesMissed = 0;
//		char test[1024] = "";
//		logData((char *)"TBS RX: ", true, true);
//		for (int i = 0 ; i < 64 ; i ++)
//		{
//			sprintf(&test[i*3], "-%02x",tbsRXArray[i]);
//		}
//		logData(test, true, true);
//		memset(test, 0, 1024);
//		memset(tbsRXArray, 0, 256);
	}
}

uint8_t calcCrossfireTelemetryFrameCRC(void)
{
	uint8_t len = tbsRXArray[1];
	uint8_t crc = crc8(&tbsRXArray[2], len-1);
	return crc;
}

uint8_t crc8(const uint8_t *ptr, uint32_t len)
{
	uint8_t crc = 0;
	for (uint32_t i = 0; i < len; i++)
	{
		crc = crc8tab[crc ^ *ptr++];
	}
	return crc;
}

// Range for pulses (channels output) is [-1024:+1024]
uint8_t createCrossfireChannelsFrame(uint8_t * frame, int16_t * pulses)
{
	uint8_t * buf = frame;
	*buf++ = MODULE_ADDRESS;
	*buf++ = 24; // 1(ID) + 22 + 1(CRC)
	uint8_t * crc_start = buf;
	*buf++ = CHANNELS_ID;
	uint32_t bits = 0;
	uint8_t bitsavailable = 0;
	for (int i=0; i<CROSSFIRE_CHANNELS_COUNT; i++)
	{
		uint32_t val = limitInt32(0, CROSSFIRE_CH_CENTER + (((pulses[i]) * 4) / 5), 2*CROSSFIRE_CH_CENTER);
		bits |= val << bitsavailable;
		bitsavailable += CROSSFIRE_CH_BITS;
		while (bitsavailable >= 8)
		{
			*buf++ = bits;
			bits >>= 8;
			bitsavailable -= 8;
		}
	}
	*buf++ = crc8(crc_start, 23);
	return buf - frame;
}

bool parseTBSMessage(void)
{
	int i = 0;
	uint8_t crc = 0;
	bool localRet = false;

//	char test[1024] = "";
//	logData((char *)"TBS RX: ", true, true, false);
//	for (int i = 0 ; i < 128 ; i ++)
//	{
//		sprintf(&test[i*3], "-%02x",tbsRXArray[i]);
//		if (tbsRXArray[i] == 0x29)
//		{
//			int y = 1;
//		}
//	}
//	logData(test, true, true, false);
//	memset(test, 0, 1024);
	uint8_t localRxArray[TBS_RX_BUFFER] = {0};
	memcpy(localRxArray,tbsRXArray,TBS_RX_BUFFER);

	while ( i < TBS_RX_BUFFER - 3)
	{
		if (TBS_RX_BUFFER - (i + 2) > 0x0c-1)
		{
			crc = crc8(&localRxArray[i + 2], 0x0c-1);
		}
		if ( (localRxArray[i] == 0xEA) && (localRxArray[i + 1] == 0x0c) && (localRxArray[i + 2] == 0x14) && (TBS_RX_BUFFER - i >= 0x0c)
				&& (crc == localRxArray[i + 0x0c + 1]) )
		{
			rcLinkStatus.UplinkRSSIAnt1 = localRxArray[i + 3];
			rcLinkStatus.UplinkRSSIAnt2 = localRxArray[i + 4];
			rcLinkStatus.UplinkPSRLQ 	= localRxArray[i + 5];
			rcLinkStatus.UplinkSNR 		= localRxArray[i + 6];
			rcLinkStatus.DiversityActiveAntena = localRxArray[i + 7];
			rcLinkStatus.RFMode = localRxArray[i + 8];
			rcLinkStatus.UplinkTXPower = localRxArray[i + 9];
			rcLinkStatus.DownlinkRSSI = localRxArray[i + 10];
			rcLinkStatus.DownlinkPSRLQ = localRxArray[i + 11];
			rcLinkStatus.DownlinkSNR = localRxArray[i + 12];
			i = i + 0x0c - 1;
			localRet = true;
			logRCLinkStatus(false);
			lastReceivedLinkMessage = HAL_GetTick();
			lastReceivedCRSFMessage = lastReceivedLinkMessage;
			isTBSDisconnected = false;
		}

		if (TBS_RX_BUFFER - (i + 2) > 0x1B-1)
		{
			crc = crc8(&localRxArray[i + 2], 0x1B-1);
		}
		if ( (localRxArray[i] == 0xEA) && (localRxArray[i + 1] == 0x1B) && (localRxArray[i + 2] == 0xDD) && (TBS_RX_BUFFER - i >= 0x1B)
				&& (crc == localRxArray[i + 0x1B + 1]) && (!waitForAckResponse) )
		{
			if (!everReceivedConfigurationMessage)
			{
				everReceivedConfigurationMessage = true;
			}
			previousSmaStatus = currentSmaStatus;
			previousBITStatus = displayWarning.BITStatus;

			if (localRxArray[i + 3] / 50.0 >= 4.6)
			{
				currentSmaStatus.batteryVoltage = localRxArray[i + 3] / 50.0;
//				currentSmaStatus.batteryStrength = CHARGING;
			}
			else
			{
				currentSmaStatus.batteryVoltage = fmin(localRxArray[i + 3] / 50.0 + 0.05, 4.2);
			}
			if ( (currentSmaStatus.batteryVoltage > 4.6) /*&& (!isSMABatteryLow) && (!isSMABatteryCritical)*/ )
			{
				currentSmaStatus.batteryStrength = CHARGING;
				isSMABatteryMedium = false;
				isSMABatteryLow = false;
				isSMABatteryCritical = false;
			}
			else if ( (currentSmaStatus.batteryVoltage >= 3.9) && (!isSMABatteryLow) && (!isSMABatteryCritical) && (!isSMABatteryMedium))
			{
				currentSmaStatus.batteryStrength = STRONG;
			}
			else if ( (currentSmaStatus.batteryVoltage >= 3.8) && (!isSMABatteryLow) && (!isSMABatteryCritical) )
			{
				currentSmaStatus.batteryStrength = MEDIUM;
			}
			else if ( (currentSmaStatus.batteryVoltage >= 3.65) && (!isSMABatteryCritical) )
			{
				currentSmaStatus.batteryStrength = LOW;
			}
			else
			{
				currentSmaStatus.batteryStrength = EMPTY;
			}

			currentSmaStatus.smaState = localRxArray[i + 4];
			if (currentSmaStatus.smaState == 6)
			{
				isAutoCalibActive = true;
				isTestCalibActive = false;
			}
			else if (currentSmaStatus.smaState == 7)
			{
				isAutoCalibActive = false;
				isTestCalibActive = true;
			}
			else
			{
				isAutoCalibActive = false;
				isTestCalibActive = false;
			}
			currentSmaStatus.triggerMode = (localRxArray[i + 5] & 0x0F) - 1;
			currentSmaStatus.rcMenuLevel = ( (localRxArray[i + 5] & 0xF0) >> 4 );
			currentSmaStatus.Altitude = ((int16_t)(localRxArray[i + 6] * 256) + localRxArray[i + 7] + 28000)/10.0;
			if ( (fabs(1 - previousSmaStatus.Altitude / currentSmaStatus.Altitude) > 0.1)
					|| (fabs(previousSmaStatus.Altitude - currentSmaStatus.Altitude) > 1) )
			{
				shouldDrawSafeAirAltitude = true;
			}
			currentSmaStatus.Acceleration = (localRxArray[i + 8] * 256 + localRxArray[i + 9])/100.0;
			currentSmaStatus.BITStatus = localRxArray[i + 10] * 256 + localRxArray[i + 11];

			if ( fabs(previousSmaStatus.batteryVoltage - currentSmaStatus.batteryVoltage) > 0.05 )
			{
				shouldRedrawSafeAirBatteryIcon = true;
			}

			if ( (localRxArray[i + 12] == 1) && (ee.legacySystemType == 0) )
			{
				currentSmaStatus.smaPlatformName = M200;
			}
			else if ( (localRxArray[i + 12] == 2)  && (ee.legacySystemType == 0) )
			{
				currentSmaStatus.smaPlatformName = M300;
			}
			else if ( (localRxArray[i + 12] == 3)  && (ee.legacySystemType == 0) )
			{
				currentSmaStatus.smaPlatformName = M600;
			}
			else if ( (localRxArray[i + 12] == 4) && (ee.legacySystemType == 0) )
			{
				currentSmaStatus.smaPlatformName = PHANTOM;
			}
			else if ( (localRxArray[i + 12] == 5)  && (ee.legacySystemType == 0) )
			{
				currentSmaStatus.smaPlatformName = MAVIC;
			}
			else if ( (localRxArray[i + 12] == 6)  && (ee.legacySystemType == 0) )
			{
				currentSmaStatus.smaPlatformName = TAILID;
			}
			else if (ee.legacySystemType != 0)
			{
				currentSmaStatus.smaPlatformName = ee.legacySystemType;
			}

			if (localRxArray[i + 13] == 1)
			{
				currentSmaStatus.smaPlatfom = MULTICOPTER;
			}
			else if (localRxArray[i + 13] == 2)
			{
				currentSmaStatus.smaPlatfom = VTOLVERTICAL;
			}
			else if (localRxArray[i + 13] == 3)
			{
				currentSmaStatus.smaPlatfom = VTOLTRANSITION;
			}
			else if (localRxArray[i + 13] == 4)
			{
				currentSmaStatus.smaPlatfom = VTOLHORIZONTAL;
			}

			uint16_t localSMATime = 256 * localRxArray[i + 14] + localRxArray[i + 15];
			if (localSMATime & 0x8000)
			{
				// Calibration duration
				localSMATime &= ~0x8000;
				//                 M    S    mSec   LSB
//				if (localSMATime > 30 * 60 * 1000 * 10)
//				{
//					durationMultiplier = (localSMATime - 30 * 60 * 1000 * 10) / 10;
//					remainingCalibrationTime = 0;
//				}
//				else
//				{
//					durationMultiplier = 0;
//					remainingCalibrationTime = localSMATime / 10;
//				}
				remainingCalibrationTime = localSMATime;
			}
			else
			{
				//Unit time
//				remainingCalibrationTime = 0;
			}
			i = i + 0x1B - 1;

			if (currentSmaStatus.BITStatus & 0x01)
			{
				displayWarning.BITStatus |= smaFlashError;
			}
			else
			{
				displayWarning.BITStatus &= ~smaFlashError;
			}

			if (currentSmaStatus.BITStatus & 0x02)
			{
				displayWarning.BITStatus |= smaOutOfBounds;
			}
			else
			{
				displayWarning.BITStatus &= ~smaOutOfBounds;
			}

			if (currentSmaStatus.BITStatus & 0x04)
			{
				displayWarning.BITStatus |= smaPyroError;
			}
			else
			{
				displayWarning.BITStatus &= ~smaPyroError;
			}

			if ( (!isSMABatteryLow) && (!isSMABatteryCritical) && (!isSMABatteryMedium) && (currentSmaStatus.batteryVoltage >= 3.9 ) )
			{
				displayWarning.BITStatus &= ~smaCritBat;
				displayWarning.BITStatus &= ~smaLowBat;
			}
			else if ( ( (currentSmaStatus.batteryVoltage >= 3.8 ) && (currentSmaStatus.batteryVoltage < 3.9 )
					&& (!isSMABatteryCritical) && (!isSMABatteryLow)) || (!isSMABatteryMedium) )
			{
				isSMABatteryMedium = true;
			}
			else if ( ( (currentSmaStatus.batteryVoltage >= 3.65 ) && (currentSmaStatus.batteryVoltage < 3.8 )
					&& (!isSMABatteryCritical) ) || (!isSMABatteryLow) )
			{
				displayWarning.BITStatus &= ~smaCritBat;
				displayWarning.BITStatus |= smaLowBat;
				isSMABatteryLow = true;
			}
			else if ( (currentSmaStatus.batteryVoltage < 3.65 ) || (isSMABatteryCritical) )
			{
				displayWarning.BITStatus |= smaCritBat;
				isSMABatteryCritical = true;
			}

			if (currentSmaStatus.BITStatus & 0x40)
			{
				displayWarning.BITStatus |= manualTrigger;
			}
			else
			{
				displayWarning.BITStatus &= ~manualTrigger;
			}

			if (currentSmaStatus.BITStatus & 0x80)
			{
				displayWarning.BITStatus |= geoFencing;
			}
			else
			{
				displayWarning.BITStatus &= ~geoFencing;
			}

			if (currentSmaStatus.BITStatus & 0x100)
			{
				displayWarning.BITStatus |= autoPilot;
				currentSmaStatus.isAutoPilotConnected = true;

			}
			else
			{
				displayWarning.BITStatus &= ~autoPilot;
				currentSmaStatus.isAutoPilotConnected = false;
			}

			if (currentSmaStatus.BITStatus & 0x200)
			{
				displayWarning.BITStatus |= freeFall;
			}
			else
			{
				displayWarning.BITStatus &= ~freeFall;
			}

			if (currentSmaStatus.BITStatus & 0x400)
			{
				displayWarning.BITStatus |= criticalAngle;
			}
			else
			{
				displayWarning.BITStatus &= ~criticalAngle;
			}

			if (currentSmaStatus.BITStatus & 0x1000)
			{
				displayWarning.BITStatus |= abnormalGyro;
			}
			else
			{
				displayWarning.BITStatus &= ~abnormalGyro;
			}

			if (currentSmaStatus.BITStatus & 0x2000)
			{
				displayWarning.BITStatus |= abnormalAcceleration;
			}
			else
			{
				displayWarning.BITStatus &= ~abnormalAcceleration;
			}

			if (currentSmaStatus.BITStatus & 0x4000)
			{
				displayWarning.BITStatus |= abnormalAngle;
			}
			else
			{
				displayWarning.BITStatus &= ~abnormalAngle;
			}

			if (currentSmaStatus.triggerMode == 0)
			{
				currentSmaStatus.safeairTriggerMode = MANUAL;
			}
			else
			{
				currentSmaStatus.safeairTriggerMode = AUTO;
			}

			if (previousSmaStatus.rcMenuLevel != currentSmaStatus.rcMenuLevel)
			{
				menuLevel = currentSmaStatus.rcMenuLevel;
				initMenuPages();
			}

			lastReceivedDroneDataMessage = HAL_GetTick();
			lastReceivedCRSFMessage = lastReceivedDroneDataMessage;
		}
		else if ( (localRxArray[i] == 0xEA) && (localRxArray[i + 1] == 0x1B) && (localRxArray[i + 2] == 0xDD) && (TBS_RX_BUFFER - i >= 0x1B)
				&& (crc != localRxArray[i + 0x1B + 1]))
		{
//			i = i + 0x1B - 1;
		}

		if (TBS_RX_BUFFER - (i + 2) > 0x06-1)
		{
			crc = crc8(&localRxArray[i + 2], 0x06-1);
		}
		if ( (localRxArray[i] == 0xEA) && (localRxArray[i + 1] == 0x06) && (localRxArray[i + 2] == 0xCA) && (TBS_RX_BUFFER - i >= 0x06)
				&& (crc == localRxArray[i + 0x06 + 1]) )
		{
			configurationMessageCounterReceived = (uint32_t)((localRxArray[i + 3] << 24) + (localRxArray[i + 4] << 16) + (localRxArray[i + 5] << 8) + localRxArray[i + 6]);
			if (configurationMessageCounter == configurationMessageCounterReceived)
			{
				shouldAddTimeToConfigurationMessage = false;
				waitForAckResponse = false;
			}
			i = i + 0x06 - 1;
			lastReceivedCRSFMessage = HAL_GetTick();
		}
		else if ( (localRxArray[i] == 0xEA) && (localRxArray[i + 1] == 0x06) && (localRxArray[i + 2] == 0xCA) && (TBS_RX_BUFFER - i >= 0x06)
				&& (crc != localRxArray[i + 0x06 + 1]) )
		{

		}

		if ( TBS_RX_BUFFER - (i + 2) > 0x0E - 1 )
		{
			crc = crc8(&localRxArray[i + 2], 0x0E - 1);
		}
		if ( (localRxArray[i] == 0xEA) && (localRxArray[i + 1] == 0x0E) && (localRxArray[i + 2] == 0xD1) && (TBS_RX_BUFFER - i >= 0x0E)
				&& (crc == localRxArray[i + 0x0E + 1]) )
		{
			safeAirTailID[0] = (char)(localRxArray[i + 3]);
			safeAirTailID[1] = (char)(localRxArray[i + 4]);
			safeAirTailID[2] = (char)(localRxArray[i + 5]);
			safeAirTailID[3] = (char)(localRxArray[i + 6]);
			safeAirTailID[4] = (char)(localRxArray[i + 7]);
			safeAirTailID[5] = (char)(localRxArray[i + 8]);
			safeAirTailID[6] = (char)(localRxArray[i + 9]);
			safeAirTailID[7] = (char)(localRxArray[i + 10]);
			safeAirTailID[8] = (char)(localRxArray[i + 11]);
			safeAirTailID[9] = (char)(localRxArray[i + 12]);
			safeAirTailID[10] = (char)(localRxArray[i + 13]);
			safeAirTailID[11] = (char)(0x00);
			if (!isTailIDAlreadyReceived)
			{
				isTailIDAlreadyReceived = true;
				sprintf(terminalBuffer,"Received Tail-ID: %s", safeAirTailID);
				memcpy(ee.lastPairedDevice,safeAirTailID,12);
				ee_save1();
				logData(terminalBuffer, false, false, false);
			}
			lastReceivedCRSFMessage = HAL_GetTick();
			i = i + 0x0E - 1;
		}
		else if ( (localRxArray[i] == 0xEA) && (localRxArray[i + 1] == 0x0E) && (localRxArray[i + 2] == 0xD1) && (TBS_RX_BUFFER - i >= 0x0E)
				&& (crc != localRxArray[i + 0x0E + 1]) )
		{

		}

		if ( TBS_RX_BUFFER - (i + 2) > 0x0A - 1 )
		{
			crc = crc8(&localRxArray[i + 2], 0x0A - 1);
		}
		if ( (localRxArray[i] == 0xEA) && (localRxArray[i + 1] == 0x0A) && (localRxArray[i + 2] == 0xED) && (TBS_RX_BUFFER - i >= 0x0A)
				&& (crc == localRxArray[i + 0x0A + 1]) )
		{
			uint32_t previousSafeAirTime = safeAirTime;
			safeAirLogID = (uint32_t)((localRxArray[i + 3] << 24) + (localRxArray[i + 4] << 16) + (localRxArray[i + 5] << 8) + localRxArray[i + 6]);
			safeAirTime = (uint32_t)((localRxArray[i + 7] << 24) + (localRxArray[i + 8] << 16) + (localRxArray[i + 9] << 8) + localRxArray[i + 10]);
			if (safeAirTime != previousSafeAirTime)
			{
				sprintf(terminalBuffer,"Received Log ID: %ld", safeAirLogID);
				logData(terminalBuffer, false, false, false);

				sprintf(terminalBuffer,"Current SafeAir time: %ld", safeAirTime);
				logData(terminalBuffer, false, false, false);
			}
			i = i + 0x0A - 1;
			lastReceivedCRSFMessage = HAL_GetTick();
		}
		else if ( (localRxArray[i] == 0xEA) && (localRxArray[i + 1] == 0x0A) && (localRxArray[i + 2] == 0xED) && (TBS_RX_BUFFER - i >= 0x0A)
				&& (crc != localRxArray[i + 0x0A + 1]) )
		{

		}

		i++;
	}
	memset(tbsRXArray, 0, TBS_RX_BUFFER);
	memset(localRxArray, 0, TBS_RX_BUFFER);
	return localRet;
}

void createPingMessage(void)
{
	uint8_t Counter = 0;
	while (1)
	{
	tbsPingMessage[0] = 0xC8;
	tbsPingMessage[1] = 0x06;
	tbsPingMessage[2] = 0x28;
	tbsPingMessage[3] = 0x00;
	tbsPingMessage[4] = 0xC8;
	tbsPingMessage[5] = 0x00;
	tbsPingMessage[6] = 0xC8;
	tbsPingMessage[7] = Counter;



		HAL_UART_Receive_DMA(&TBS_UART, tbsRXArray,TBS_RX_BUFFER);
		HAL_Delay(1);
		HAL_UART_Transmit_IT(&TBS_UART, tbsPingMessage, 8);
		HAL_Delay(1);
//		char test[1024] = "";
//		logData((char *)"TBS RX: ", true, true);
//		for (int i = 0 ; i < 128 ; i ++)
//		{
//			sprintf(&test[i*3], "-%02x",tbsRXArray[i]);
//			if (tbsRXArray[i] == 0x29)
//			{
//				int y = 1;
//			}
//		}
//		logData(test, true, true);
//		memset(test, 0, 1024);
		memset(tbsRXArray, 0, TBS_RX_BUFFER);
		Counter++;
	}
}

void sendSafeAirConfigurationMessage(bool includeTimeInMessage)
{
	if ( ( (configurationMessageCounter != configurationMessageCounterReceived) && ( HAL_GetTick() - lastConfigurationMessageSent > 1000 ) ) || (includeTimeInMessage) )
	{
		safeairConfigurationFrame[0] = MODULE_ADDRESS; // Change to P2P value
		safeairConfigurationFrame[1] = 0x1B; // len
		safeairConfigurationFrame[2] = 0xDC; // OpCode
		safeairConfigurationFrame[3] = (uint8_t)(((uint32_t)(configurationMessageCounter & 0xff000000))>>24); // Message ID Highest Byte
		safeairConfigurationFrame[4] = (uint8_t)(((uint32_t)(configurationMessageCounter & 0x00ff0000))>>16);
		safeairConfigurationFrame[5] = (uint8_t)(((uint32_t)(configurationMessageCounter & 0x0000ff00))>>8);
		safeairConfigurationFrame[6] = (uint8_t)(((uint32_t)(configurationMessageCounter & 0x000000ff))); // Message ID Lowest Byte
		safeairConfigurationFrame[7] = safeairConfiguration.armMode;
		safeairConfigurationFrame[8] = safeairConfiguration.triggerMode;
		safeairConfigurationFrame[9] = safeairConfiguration.platformType;
		uint8_t localState = 0;
		if (isAutoCalibActive)
		{
			localState = 4;
		}
		else if (isTestCalibActive)
		{
			localState = 5;
		}
		else
		{
			localState = safeairConfiguration.state;
		}
		safeairConfigurationFrame[10] = localState;
		if (forceDisarmEnabled)
		{
			safeairConfiguration.forceDisarm = 0x85;
		}
		else
		{
			safeairConfiguration.forceDisarm = 0x17;
		}
		safeairConfigurationFrame[11] = safeairConfiguration.forceDisarm;

		if (formatSDEnabled)
		{
			safeairConfiguration.formatSD = 0x85;
		}
		else
		{
			safeairConfiguration.formatSD = 0x17;
		}
		safeairConfigurationFrame[12] = safeairConfiguration.formatSD;
		safeairConfigurationFrame[13] = safeairConfiguration.loggingMode;
		safeairConfigurationFrame[14] = (uint8_t)((uint16_t)((safeairConfiguration.MTD) & 0xff00)>>8); // MTD High Byte
		safeairConfigurationFrame[15] = (uint8_t)((uint16_t)((safeairConfiguration.MTD) & 0x00ff)); // MTD Low Byte
		safeairConfigurationFrame[16] = includeTimeInMessage * 0x85 + (1 - includeTimeInMessage) * 0x17; //Time Included
		safeairConfigurationFrame[17] = sDate.Year; //YY
		safeairConfigurationFrame[18] = sDate.Month; //MM
		safeairConfigurationFrame[19] = sDate.Date; //DD
		safeairConfigurationFrame[20] = sTime.Hours; //HH
		safeairConfigurationFrame[21] = sTime.Minutes; //mm
		safeairConfigurationFrame[22] = sTime.Seconds; //SS
		if (testMotorCut)
		{
			safeairConfigurationFrame[23] = 0x85;
		}
		else
		{
			safeairConfigurationFrame[23] = 0x17;
		}
		safeairConfigurationFrame[24] = 0x00; //
		safeairConfigurationFrame[25] = 0x00; //
		safeairConfigurationFrame[26] = 0x00; //
		safeairConfigurationFrame[27] = 0x00; //
		safeairConfigurationFrame[28] = crc8(&safeairConfigurationFrame[2], safeairConfigurationFrame[1]-1); //crc

		HAL_UART_Transmit_IT(&TBS_UART, safeairConfigurationFrame, 29);
		lastConfigurationMessageSent = HAL_GetTick();
	}
}
