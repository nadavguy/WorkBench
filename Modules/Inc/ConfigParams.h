/*
 * ConfigParams.h
 *
 *  Created on: Feb 7, 2021
 *      Author: gilad
 */

#ifndef INC_CONFIGPARAMS_H_
#define INC_CONFIGPARAMS_H_

typedef struct sEE_DATA
{
//	float vibration;
//	uint8_t vibrationRelevatAxis;
	uint16_t armPWMOffValue;
	uint16_t armPWMOnValue;
	uint16_t triggerPWMOffValue;
	uint16_t triggerPWMOnValue;
	uint16_t backLight;
	uint16_t motorDelayValue;
	uint8_t linkType;
	uint8_t debugLevel;
	uint8_t screenOreintation;
	uint8_t bluetoothStatus;
	float configuration;
	uint16_t fullChargeCycles;
	uint8_t rcMode;
	char lastPairedDevice[16];
	uint8_t lastStepInCVChargeCycle;
	uint8_t batteryType;
	char password[32];
	uint8_t legacySystemType;
	uint8_t informationLevel;
	char geoCagingFileName[16];
	char geoCagingDate[16];
	uint8_t geoCagingPolygons;
	uint8_t geoCagingCircles;
}tEE_DATA;


typedef struct sCONFIG_DATA
{
	uint16_t MTD;
	uint8_t armMode;
	uint8_t triggerMode;
	uint8_t platformType;
	uint8_t state;
	uint8_t forceDisarm;
	uint8_t formatSD;
	uint8_t loggingMode;
}tCONFIG_DATA;

extern tEE_DATA ee;
extern tCONFIG_DATA safeairConfiguration;

//extern tEEV_FLOAT EEV_Vibrations;
extern tEEV_U08 EEV_DebugLevel;
extern tEEV_U16 EEV_ArmPWMOffValue;
extern tEEV_U16 EEV_ArmPWMOnValue;
extern tEEV_U16 EEV_TriggerPWMOffValue;
extern tEEV_U16 EEV_TriggerPWMOnValue;
extern tEEV_U08 EEV_LinkType;
extern tEEV_U16 EEV_Backlight;
extern tEEV_U08 EEV_ScreenOrientation;
extern tEEV_U08 EEV_ChargeCycle;
extern tEEV_U08 EEV_BatteryType;
extern tEEV_U08 EEV_LegacySystemType;
extern tEEV_U16 EEV_MotorCutDelay;

extern bool ee_validate1(void);
extern void setParametersToDefaults(void);

#endif /* INC_CONFIGPARAMS_H_ */
