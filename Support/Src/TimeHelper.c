/*
 * TimwHelper.c
 *
 *  Created on: Mar 24, 2021
 *      Author: gilad
 */

#include "main.h"

char CTime[20] = {0};

char *CT()
{
	sprintf(CTime,"%7.3f", (float)HAL_GetTick()/1000.0);
    return CTime;
}
