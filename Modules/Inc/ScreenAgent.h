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

#define HorizontalDisplayCenterWidth 80
#define HorizontalDisplayCenterHeight 64

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
#define HorizontalWarningTextY HorizontalWarningIconY + 8

#define HorizontalSafeAirLogo599IconX 1
#define HorizontalSafeAirLogo599IconY 110

#define HorizontalSafeAirLogo7411IconX 1
#define HorizontalSafeAirLogo7411IconY 108

#define HorizontalSafeAirBatteryIconX 75
#define HorizontalSafeAirBatteryIconY 101

#define HorizontalSafeAirBatteryTextX 78
#define HorizontalSafeAirBatteryTextY 120

#define HorizontalAltitudeIconX 106
#define HorizontalAltitudeIconY HorizontalSafeAirBatteryIconY

#define HorizontalAltitudeText1X HorizontalAltitudeIconX - 5 + 24
#define HorizontalAltitudeText1Y HorizontalSafeAirBatteryIconY + 2

#define HorizontalAltitudeText2X HorizontalAltitudeIconX - 5 + 24
#define HorizontalAltitudeText2Y HorizontalSafeAirBatteryIconY + 2 + 12

#define HorizontalMenuRectangleStartX 24
#define HorizontalMenuRectangleStartY 12

#define HorizontalMenuRectangleWidth 114
#define HorizontalMenuRectangleHeight 14

#define HorizontalQuestionRectangleHeight 86
#define HorizontalPopupRectangleHeight HorizontalQuestionRectangleHeight + HorizontalMenuRectangleHeight

extern const unsigned char *previousBluetoothImage;
extern const unsigned char *previousPlatformImage;
extern const unsigned char *previousAutoPilotImage;
extern const unsigned char *previousTriggerModeImage;
extern const unsigned char *previousSignalImage;
extern const unsigned char *previousBatteryImage;

extern bool shouldRenderBatteryPercent;
extern bool shouldRenderMenu;
extern bool isMenuDisplayed;
extern bool shouldClearScreen;
extern bool shouldRenderItem;
extern bool isItemDisplayed;
extern bool isParameterUpdateRequired;
extern bool shouldRenderPopup;
extern bool isPopupDisplayed;

extern uint32_t lastBITStatusChange;

extern tUINT8_ITEM uint8Item;
extern tUINT16_ITEM uint16Item;
extern tUINT32_ITEM uint32Item;

extern tSTRING_ITEM stringItem;

extern MENUDRAWType menuDrawDirection;
extern MENUDRAWType itemDrawDirection;
extern MENUDRAWType popupDrawDirection;

extern tPOPUP popupToShow;

extern void screenInit(void);
extern void screenClear(void);
extern void centeredString(uint16_t XCenterstart, uint16_t Ystart, const char * pString, uint16_t textColor, uint16_t backgroundColor, uint8_t numberOfCharactersToClear);
extern void screenUpdate(bool drawDeltaImage);
extern void drawMenu(bool clearScreen, MENUDRAWType howToDraw);
extern void drawItem(bool clearScreen, MENUDRAWType howToDraw);
extern void drawPopup(void);
extern void setFullDisplay(void);


#endif /* SRC_SCREENAGENT_H_ */
