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
	uint8_t debugLevel;
	uint16_t armPWMOffValue;
	uint16_t armPWMOnValue;
	uint16_t triggerPWMOffValue;
	uint16_t triggerPWMOnValue;
	uint8_t linkType;
}tEE_DATA;

extern tEE_DATA ee;

//extern tEEV_FLOAT EEV_Vibrations;
extern tEEV_U08 EEV_DebugLevel;
extern tEEV_U16 EEV_ArmPWMOffValue;
extern tEEV_U16 EEV_ArmPWMOnValue;
extern tEEV_U16 EEV_TriggerPWMOffValue;
extern tEEV_U16 EEV_TriggerPWMOnValue;
extern tEEV_U08 EEV_LinkType;

extern bool ee_validate1(void);

#endif /* INC_CONFIGPARAMS_H_ */
