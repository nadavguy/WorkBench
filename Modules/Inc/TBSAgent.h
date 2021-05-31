/*
 * TBSAgent.h
 *
 *  Created on: Mar 22, 2021
 *      Author: gilad
 */

#ifndef INC_TBSAGENT_H_
#define INC_TBSAGENT_H_

#include "stdint.h"

#define BROADCAST_ADDRESS           0x00
#define RADIO_ADDRESS               0xEA
#define MODULE_ADDRESS              0xC8

#define GPS_ID                      0x02
#define CF_VARIO_ID                 0x07
#define BATTERY_ID                  0x08
#define LINK_ID                     0x14
#define CHANNELS_ID                 0x16
#define ATTITUDE_ID                 0x1E
#define FLIGHT_MODE_ID              0x21
#define PING_DEVICES_ID             0x28
#define DEVICE_INFO_ID              0x29
#define REQUEST_SETTINGS_ID         0x2A
#define TBS_UART					huart1
#define TBS_RX_BUFFER				128


typedef enum {NOPLATFORM, M200, M300, M600, PHANTOM, MAVIC, TAILID} PLATFORMName;

typedef enum {MULTICOPTER, VTOLHORIZONTAL, VTOLTRANSITION, VTOLVERTICAL} PLATFORMType;

typedef enum {PREINIT, IDLE, ARMED, TRIGGERED, UNKNOWN, MAINTENANCE, AUTOCALIBRATION, INIT, OPERATIONAL} SYSTEMState;

typedef enum {MANUAL, AUTO} TRIGGERMode;

typedef enum {DISCONNECTED, CONNECTED, PAIRING, SEARCHING} SYSTEMConnectionStatus;

typedef enum {STRONG, MEDIUM, LOW, NOSIGNAL, CHARGING , EMPTY} SIGNALStrength;

typedef enum {CRITICALANGLE, FREEFALL, MANUALTRIGGER, GEOFENCING, AUTOPILOTTRIGGER, NOTTRIGGERED} TRIGGERReason;

typedef struct sRC_LINK
{
	uint8_t UplinkRSSIAnt1; //Uplink is ground to UAV
	uint8_t UplinkRSSIAnt2;
	uint8_t UplinkPSRLQ;
	int8_t UplinkSNR;
	uint8_t DiversityActiveAntena;
	uint8_t RFMode;
	uint8_t UplinkTXPower;
	uint8_t DownlinkRSSI; //Downlink is UAV to ground
	uint8_t DownlinkPSRLQ;
	int8_t DownlinkSNR;
}tRC_LINK;

typedef struct sSMA_Status
{
	float batteryVoltage;
//	uint8_t smaState;
	uint8_t triggerMode;
	float Altitude;
	float Acceleration;
	uint16_t BITStatus;
	PLATFORMName smaPlatformName;
	PLATFORMType smaPlatfom;
	bool isAutoPilotConnected;
	SYSTEMState smaState;
	SYSTEMConnectionStatus autoPilotConnection;
//	PLATFORMType safeairPlatform;
	TRIGGERMode safeairTriggerMode;
	SIGNALStrength batteryStrength;
	TRIGGERReason smaTriggerReason;
	MENULEVELType rcMenuLevel;
}tSMA_Status;

typedef struct sWarning
{
	bool displayWarning;
	uint16_t BITStatus; // 1 - SMA Crit Bat, 2 - SMA Low Bat, 4 - SMA Flash Error, 8 - SMA Out Of Bounds, 16 - Pyro Error, 32 - RC Low Bat
}tWarning;

extern uint8_t tbsRXArray[TBS_RX_BUFFER];
extern int16_t channelPWMValues[16];

extern uint8_t rcChannelsFrame[26];
extern uint8_t IdleMessageArray[26];
extern uint8_t TriggerMessageArray[26];
extern uint8_t tbsPingMessage[8];

extern uint16_t previousBITStatus;
extern uint32_t lastCRSFChannelMessage;
extern uint32_t lastLoggedLinkMessage;
extern uint32_t lastReceivedLinkMessage;
extern uint32_t configurationMessageCounter;
extern uint32_t configurationMessageCounterReceived;
extern uint32_t lastConfigurationMessageSent;
extern uint32_t safeAirLogID;
extern uint32_t safeAirTime;
extern uint32_t lastReceivedCRSFMessage;

extern bool isTBSDisconnected;
extern bool isTailIDAlreadyReceived;

extern char safeAirTailID[11];

extern tRC_LINK rcLinkStatus;
extern tSMA_Status previousSmaStatus;
extern tSMA_Status currentSmaStatus;

void tbsInit(void);
void sendMessageToRC(void);
void sendChannelMessageToTBS(void);
uint8_t calcCrossfireTelemetryFrameCRC(void);
uint8_t crc8(const uint8_t *ptr, uint32_t len);
uint8_t createCrossfireChannelsFrame(uint8_t * frame, int16_t * pulses);
bool parseTBSMessage(void);
extern void createPingMessage(void);
extern void sendSafeAirConfigurationMessage(bool includeTimeInMessage);


#endif /* INC_TBSAGENT_H_ */
