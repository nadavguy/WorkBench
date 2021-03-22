/*
 * TBSAgent.h
 *
 *  Created on: Mar 22, 2021
 *      Author: gilad
 */

#ifndef INC_TBSAGENT_H_
#define INC_TBSAGENT_H_

void tbsInit(void);
void sendMessageToRC(void);
void sendChannelMessageToRX(void);
uint8_t calcCrossfireTelemetryFrameCRC(void);
uint8_t crc8(const uint8_t *ptr, uint32_t len);


#endif /* INC_TBSAGENT_H_ */
