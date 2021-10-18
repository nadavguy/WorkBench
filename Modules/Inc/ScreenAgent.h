/*
 * ScreenAgent.h
 *
 *  Created on: Mar 25, 2021
 *      Author: gilad
 */

#ifndef SRC_SCREENAGENT_H_
#define SRC_SCREENAGENT_H_

#include "main.h"

#define statusBarIconWidth 24
#define statusBarIconHeight 24

#define safeAirBarIconWidth 30
#define safeAirBarIconHeight 30

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



#define VerticalDisplayCenterWidth 64
#define VerticalDisplayCenterHeight 80

#define VerticalBluetoothX 56
#define VerticalBluetoothY 1

#define VerticalTBSSignalX 80
#define VerticalTBSSignalY 1

#define VerticalBatteryX 104
#define VerticalBatteryY 1

#define VerticalLogoX 0
#define VerticalLogoY 0

#define VerticalSafeAirBatteryX 78
#define VerticalSafeAirBatteryY 92

#define VerticalPltfomTypeX 1
#define VerticalPltfomTypeY VerticalSafeAirBatteryY

#define VerticalAutoPilotX 1 + 26
#define VerticalAutoPilotY VerticalSafeAirBatteryY

#define VerticalTriggerModeX 1 + 78
#define VerticalTriggerModeY VerticalSafeAirBatteryY

#define VerticalSystemTextX VerticalDisplayCenterWidth
#define VerticalSystemTextY 30

#define VerticalParachute1X 0
#define VerticalParachute1Y 48

#define VerticalParachute2X 136
#define VerticalParachute2Y VerticalParachute1Y

#define VerticalSystemStatusTextX VerticalDisplayCenterWidth
#define VerticalSystemStatusTextY 47

#define VerticalWarningIconX 1
#define VerticalWarningIconY 80

#define VerticalWarningTextX VerticalDisplayCenterWidth
#define VerticalWarningTextY 70

#define VerticalSafeAirLogo599IconX 1
#define VerticalSafeAirLogo599IconY 110

#define VerticalSafeAirLogo7411IconX 1
#define VerticalSafeAirLogo7411IconY 108

#define VerticalSafeAirBatteryIconX 75
#define VerticalSafeAirBatteryIconY 101

#define VerticalAltitudeIconX 106
#define VerticalAltitudeIconY VerticalSafeAirBatteryIconY

#define VerticalAltitudeText1X VerticalAltitudeIconX - 5 + 24
#define VerticalAltitudeText1Y VerticalSafeAirBatteryIconY + 2

#define VerticalAltitudeText2X VerticalAltitudeIconX - 5 + 24
#define VerticalAltitudeText2Y VerticalSafeAirBatteryIconY + 2 + 12

#define VerticalMenuRectangleStartX 2
#define VerticalMenuRectangleStartY 12

#define VerticalMenuRectangleWidth 124
#define VerticalMenuRectangleHeight 14

#define VerticalQuestionRectangleHeight 86
#define VerticalPopupRectangleHeight VerticalQuestionRectangleHeight + VerticalMenuRectangleHeight

#define VerticalSafeAirLineStartX 5
#define VerticalSafeAirLineEndX 123
#define VerticalSafeAirLineY 128

#define VerticalAltitudeOrGPSX 5
#define	VerticalAltitudeOrGPSY 132

#define VerticalChargingModeX 43
#define VerticalChargingModeY 40

#define VerticalChargingModePercentX 64
#define VerticalChargingModePercentY 130

#define VerticalChargingModeFirstDotX 34
#define VerticalChargingModeSecondDotX VerticalChargingModeFirstDotX+12
#define VerticalChargingModeThirdDotX VerticalChargingModeFirstDotX+12*2
#define VerticalChargingModeForthDotX VerticalChargingModeFirstDotX+12*3
#define VerticalChargingModeFifthDotX VerticalChargingModeFirstDotX+12*4
#define VerticalChargingModeSixthDotX VerticalChargingModeFirstDotX+12*5
#define VerticalChargingModeDotY 148

#define VerticalFullLogoX 26
#define VerticalFullLogoY 68

#define VerticalFullLogoWidth 75
#define VerticalFullLogoHeight 92

typedef struct sIMAGE_DATA
{
	uint32_t imagePointer;
	uint16_t imageID;
	uint8_t width;
	uint8_t height;
	bool isDisplayed;
}tIMAGE_DATA;

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
extern bool isPortrait;
extern bool renderCompleteFrame;
extern bool isBluetoothDisplayed;
extern bool isAutoPilotDisplayed;
extern bool isPlatformDisplayed;
extern bool isTriggerModeDisplayed;
extern bool isSafeAirBatteryDisplayed;
extern bool isAltitudeDisplayed;
extern bool isGPSPositionDisplayed;

extern uint8_t LineStartX;
extern uint8_t LineEndX;
extern uint8_t LineY;

extern uint8_t ChargingModeImageX;
extern uint8_t ChargingModeImageY;
extern uint8_t ChargingModePercentTextX;
extern uint8_t ChargingModePercentTextY;
extern uint8_t lowerBarDisplayID;

extern uint32_t lastBITStatusChange;
extern uint32_t lastFrameDisplayed;
extern uint32_t lastFullFrameDisplayed;

extern tUINT8_ITEM uint8Item;
extern tUINT16_ITEM uint16Item;
extern tUINT32_ITEM uint32Item;

extern tSTRING_ITEM stringItem;

extern MENUDRAWType menuDrawDirection;
extern MENUDRAWType itemDrawDirection;
extern MENUDRAWType popupDrawDirection;

extern tPOPUP popupToShow;

extern tIMAGE_DATA statusBarImageArray[5];

extern uint8_t nextFrameToDraw[40960];

extern void screenInit(void);
extern void screenClear(void);
extern void centeredString(uint16_t XCenterstart, uint16_t Ystart, const char * pString, uint16_t textColor, uint16_t backgroundColor, uint8_t numberOfCharactersToClear, sFONT localFont);
extern void screenUpdate(bool drawDeltaImage);
extern void drawMenu(bool clearScreen, MENUDRAWType howToDraw);
extern void drawItem(bool clearScreen, MENUDRAWType howToDraw);
extern void drawPopup(void);
extern void setFullDisplay(void);
extern void setIconPositionOnScreen(void);
extern void drawChargingDots(void);
extern void updateBITStatus(void);


#endif /* SRC_SCREENAGENT_H_ */
