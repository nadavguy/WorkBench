/*
 * TBSAgent.h
 *
 *  Created on: Mar 22, 2021
 *      Author: gilad
 */

#ifndef INC_TBSAGENT_H_
#define INC_TBSAGENT_H_

#include "stdint.h"

#define BROADCAST_ADDRESS              0x00
#define RADIO_ADDRESS                  0xEA
#define MODULE_ADDRESS                 0xEE

#define GPS_ID                         0x02
#define CF_VARIO_ID                    0x07
#define BATTERY_ID                     0x08
#define LINK_ID                        0x14
#define CHANNELS_ID                    0x16
#define ATTITUDE_ID                    0x1E
#define FLIGHT_MODE_ID                 0x21
#define PING_DEVICES_ID                0x28
#define DEVICE_INFO_ID                 0x29
#define REQUEST_SETTINGS_ID            0x2A

extern uint8_t tbsRXArray[64];
extern int16_t channelPWMValues[16];

void tbsInit(void);
void sendMessageToRC(void);
void sendChannelMessageToRX(void);
uint8_t calcCrossfireTelemetryFrameCRC(void);
uint8_t crc8(const uint8_t *ptr, uint32_t len);
uint8_t createCrossfireChannelsFrame(uint8_t * frame, int16_t * pulses);
bool parseTBSMessage(void);


#endif /* INC_TBSAGENT_H_ */
