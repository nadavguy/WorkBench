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

#define HorizontalPltfomTypeX 1
#define HorizontalPltfomTypeY 0

#define HorizontalAutoPilotX 1 + 26
#define HorizontalAutoPilotY HorizontalPltfomTypeY

#define HorizontalBluetoothX 1 + 52
#define HorizontalBluetoothY 0

#define HorizontalTriggerModeX 1 + 78
#define HorizontalTriggerModeY HorizontalPltfomTypeY

#define HorizontalTBSSignalX 1 + 106
#define HorizontalTBSSignalY HorizontalPltfomTypeY

#define HorizontalBatteryX 1 + 132
#define HorizontalBatteryY HorizontalPltfomTypeY

#define HorizontalSystemTextX 80
#define HorizontalSystemTextY 32

#define HorizontalParachute1X 0
#define HorizontalParachute1Y 48

#define HorizontalParachute2X 136
#define HorizontalParachute2Y HorizontalParachute1Y

#define HorizontalSystemStatusTextX 80
#define HorizontalSystemStatusTextY HorizontalParachute1Y + 8

#define HorizontalWarningIconX 1
#define HorizontalWarningIconY 80

#define HorizontalWarningTextX HorizontalWarningIconX + 24
#define HorizontalWarningTextY HorizontalWarningIconY

#define HorizontalSafeAirLogo599IconX 1
#define HorizontalSafeAirLogo599IconY 110

#define HorizontalSafeAirBatteryIconX 60
#define HorizontalSafeAirBatteryIconY 104

#define HorizontalSafeAirBatteryTextX 78
#define HorizontalSafeAirBatteryTextY 110

#define HorizontalAltitudeIconX 106
#define HorizontalAltitudeIconY HorizontalSafeAirBatteryIconY

#define HorizontalAltitudeText1X HorizontalAltitudeIconX - 5 + 24
#define HorizontalAltitudeText1Y HorizontalSafeAirBatteryIconY + 2

#define HorizontalAltitudeText2X HorizontalAltitudeIconX - 5 + 24
#define HorizontalAltitudeText2Y HorizontalSafeAirBatteryIconY + 2 + 12

extern void screenInit(void);
extern void screenClear(void);
extern void centeredString(uint16_t XCenterstart, uint16_t Ystart, const char * pString, uint16_t textColor);
extern void screenUpdate(void);


#endif /* SRC_SCREENAGENT_H_ */
