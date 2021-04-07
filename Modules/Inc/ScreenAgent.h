/*
 * ScreenAgent.h
 *
 *  Created on: Mar 25, 2021
 *      Author: gilad
 */

#ifndef SRC_SCREENAGENT_H_
#define SRC_SCREENAGENT_H_

#include "main.h"

#define iconWidth 24
#define iconHeight 24

#define HorizontalLogoX 0
#define HorizontalLogoY 0

#define HorizontalPltfomTypeX 36
#define HorizontalPltfomTypeY 0

#define HorizontalAutoPilotX 60
#define HorizontalAutoPilotY 0

#define HorizontalTBSSignalX 84
#define HorizontalTBSSignalY 0

#define HorizontalBluetoothX 108
#define HorizontalBluetoothY 0

#define HorizontalBatteryX 132
#define HorizontalBatteryY 0

#define HorizontalWarningIconX 26
#define HorizontalWarningIconY 24+12

#define HorizontalWarningTextX 50
#define HorizontalWarningTextY HorizontalWarningIconY + 8 + 12

extern void screenInit(void);
extern void screenClear(void);
extern void centeredString(uint16_t XCenterstart, uint16_t Ystart, const char * pString, uint16_t textColor);
extern void screenUpdate(void);


#endif /* SRC_SCREENAGENT_H_ */
