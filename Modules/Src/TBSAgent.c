/*
 * TBSAgent.c
 *
 *  Created on: Mar 22, 2021
 *      Author: gilad
 */

#include "TBSAgent.h"

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

}

uint8_t calcCrossfireTelemetryFrameCRC(void)
{
	uint8_t len = rc_tx_buffer[1];
	uint8_t crc = crc8(&rc_tx_buffer[2], len-1);
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
