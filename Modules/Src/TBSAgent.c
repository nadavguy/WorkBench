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

uint8_t IdleMessageArray[26] = {0xC8, 0x18, 0x16, 0xAC, 0x60, 0x05, 0x2B, 0x58, 0xC1, 0x0A, 0x56, 0xB0, 0x82, 0x15, 0xAC, 0x60, 0x05, 0x2B, 0x58, 0xC1, 0x0A, 0x56, 0xB0, 0x82, 0x15, 0x5B};
uint8_t TriggerMessageArray[26] = {0xC8, 0x18, 0x16, 0xA4, 0x26, 0x35, 0xA9, 0x49, 0x4D, 0x6A, 0x52, 0x93, 0x9A, 0xD4, 0xA4, 0x26, 0x35, 0xA9, 0x49, 0x4D, 0x6A, 0x52, 0x93, 0x9A, 0xD4, 0x64};

int16_t channelPWMValues[16] = {((1000 - 1500) * 8 / 5 + 992)};

tRC_LINK rcLinkStatus;

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

void tbsInit(void)
{
//	rc_telem.init(RC_USART, 115200);
}

void sendMessageToRC(void)
{
	uint8_t tempState = 0x06;
//	if (isInHardFault)
//	{
//		tempState = 0x4;
//	}
//	else if (pyro_enabled)
//	{
//		tempState = 0x3;
//	}
//	else if ( (!pyro_enabled) && (arm_state) )
//	{
//		tempState = 0x2;
//	}
//	else if ( (!pyro_enabled) && (!arm_state) && (ee.start_trg_mode != 2) )
//	{
//		tempState = 0x1;
//	}
//	else if ( (!pyro_enabled) && (!arm_state) && (ee.start_trg_mode == 2) )
//	{
//		tempState = 0x5;
//	}
//	else
//	{
//		tempState = 0x6;
//	}
//
//	rc_tx_buffer[0] = 0x00;
//	rc_tx_buffer[1] = 0x11; // len
//	rc_tx_buffer[2] = 0xDD; // OpCode
//	rc_tx_buffer[3] = ec_main_supply_iir * 10; // Battery
//	rc_tx_buffer[4] = tempState; // State
//	rc_tx_buffer[5] = ee.start_trg_mode; //trigger
//	rc_tx_buffer[6] = (uint8_t)(((int16_t)(Filtered_Altitude * 10 -28000) & 0xff00)>>8); // Alt High Byte
//	rc_tx_buffer[7] = (uint8_t)((int16_t)(Filtered_Altitude * 10 -28000) & 0x00ff);// Alt Low Byte
//	rc_tx_buffer[8] = (uint8_t)(((int16_t)(Aabs * 100) & 0xff00)>>8); // Abs Acc High Byte
//	rc_tx_buffer[9] = (uint8_t)((int16_t)(Aabs * 100) & 0x00ff); // Abs Acc Low Byte
//	rc_tx_buffer[10] = 0x00; // BIT High byte
//	rc_tx_buffer[11] = 0x00; // BIT Low byte
//	rc_tx_buffer[12] = (uint8_t)((uint16_t)(((systick_counter/1000) * 10) & 0xff00)>>8); // Unit time High Byte
//	rc_tx_buffer[13] = (uint8_t)((uint16_t)(((systick_counter/1000) * 10) & 0x00ff)); // Unit time Low Byte
//	rc_tx_buffer[14] = 0x00; // FFU1
//	rc_tx_buffer[15] = 0x00; // FFU2
//	rc_tx_buffer[16] = 0x00; // FFU3 High Byte
//	rc_tx_buffer[17] = 0x00; // FFU3 Low Byte
//	rc_tx_buffer[18] = calcCrossfireTelemetryFrameCRC(); //crc
//
//	// memcpy(rc_tx_buffer_char,rc_tx_buffer,64);
//	// rc_telem.putstr(rc_tx_buffer_char);
//	rc_telem.putbyte(rc_tx_buffer,19);
}

void sendChannelMessageToRX(void)
{
//	uint16_t R = 0;
	if ( HAL_GetTick() - lastCRSFChannelMessage > 6)
	{
		memset(rcChannelsFrame, 0, 26);
		createCrossfireChannelsFrame(rcChannelsFrame, channelPWMValues);
		HAL_UART_Transmit_IT(&TBS_UART, rcChannelsFrame, 26);
		lastCRSFChannelMessage = HAL_GetTick();
	}
	else if ( ( HAL_GetTick() - lastCRSFChannelMessage <= 6)  && (( HAL_GetTick() - lastCRSFChannelMessage > 1)) )
	{
		HAL_UART_Receive_DMA(&TBS_UART, tbsRXArray,TBS_RX_BUFFER);
		parseTBSMessage();
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
	bool localRet = false;
	while ( i < TBS_RX_BUFFER - 3)
	{
		if ( (tbsRXArray[i] == 0xea) && (tbsRXArray[i + 1] == 0x0c) && (tbsRXArray[i + 2] == 0x14) && (TBS_RX_BUFFER - i >= 14) )
		{
			rcLinkStatus.UplinkRSSIAnt1 = tbsRXArray[i + 3];
			rcLinkStatus.UplinkRSSIAnt2 = tbsRXArray[i + 4];
			rcLinkStatus.UplinkPSRLQ 	= tbsRXArray[i + 5];
			rcLinkStatus.UplinkSNR 		= tbsRXArray[i + 6];
			rcLinkStatus.DiversityActiveAntena = tbsRXArray[i + 7];
			rcLinkStatus.RFMode = tbsRXArray[i + 8];
			rcLinkStatus.UplinkTXPower = tbsRXArray[i + 9];
			rcLinkStatus.DownlinkRSSI = tbsRXArray[i + 10];
			rcLinkStatus.DownlinkPSRLQ = tbsRXArray[i + 11];
			rcLinkStatus.DownlinkSNR = tbsRXArray[i + 12];
			i = i + 13;
			localRet = true;
		}
		i++;
	}
	memset(tbsRXArray, 0, TBS_RX_BUFFER);
	return localRet;
}
