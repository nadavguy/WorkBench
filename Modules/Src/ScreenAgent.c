/*
 * ScreenAgent.c
 *
 *  Created on: Mar 25, 2021
 *      Author: gilad
 */


#include "main.h"
#include "image.h"
#include "BatteryImages.h"
#include "LogoImages.h"
#include "LocationImages.h"
#include "AutoPilotImages.h"
#include "SignalImages.h"
#include "SafeAirImages.h"
#include "BluetoothImages.h"
#include "PlatformImages.h"
#include "LCD_Test.h"
#include "LCD_1in8.h"
#include "DEV_Config.h"

const unsigned char *previousBluetoothImage;
const unsigned char *previousPlatformImage;
const unsigned char *previousAutoPilotImage;
const unsigned char *previousTriggerModeImage;
const unsigned char *previousSignalImage;
const unsigned char *previousBatteryImage;
const unsigned char *previousRCBatteryImage;
const unsigned char *previousAltitudeOrGPSImage;

bool shouldRenderBatteryPercent = false;
bool shouldRenderMenu = false;
bool isMenuDisplayed = false;
bool shouldClearScreen = false;
bool shouldRenderItem = false;
bool isItemDisplayed = false;
bool isParameterUpdateRequired = false;
bool shouldRenderPopup = false;
bool isPopupDisplayed = false;
bool isPortrait = false;
bool renderCompleteFrame = false;
bool isBluetoothDisplayed = false;
bool isAutoPilotDisplayed = false;
bool isPlatformDisplayed = false;
bool isTriggerModeDisplayed = true;
bool isSafeAirBatteryDisplayed = true;
bool isAltitudeDisplayed = true;
bool isGPSPositionDisplayed = false;

uint8_t PlatfomTypeX = 0;
uint8_t PlatfomTypeY = 0;
uint8_t AutoPilotX = 0;
uint8_t AutoPilotY = 0;
uint8_t TBSSignalX = 0;
uint8_t TBSSignalY = 0;
uint8_t BluetoothX = 0;
uint8_t BluetoothY = 0;
uint8_t TriggerModeX = 0;
uint8_t TriggerModeY = 0;
uint8_t BatteryX = 0;
uint8_t BatteryY = 0;
uint8_t SystemTextX = 0;
uint8_t SystemTextY = 0;
uint8_t SafeAirBatteryX = 0;
uint8_t SafeAirBatteryY = 0;
uint8_t Parachute1X = 0;
uint8_t Parachute1Y = 0;
uint8_t Parachute2X = 0;
uint8_t Parachute2Y = 0;
uint8_t SystemStatusTextX = 0;
uint8_t SystemStatusTextY = 0;
uint8_t WarningIconX = 0;
uint8_t WarningIconY = 0;
uint8_t WarningTextX = 0;
uint8_t WarningTextY = 0;
uint8_t LineStartX = 0;
uint8_t LineEndX = 0;
uint8_t LineY = 0;
uint8_t AltitudeOrGPSX = 0;
uint8_t AltitudeOrGPSY = 0;

uint32_t lastBatteryRefresh = 0;
uint32_t lastBITStatusChange = 0;
uint32_t lastFrameDisplayed = 0;
uint32_t lastFullFrameDisplayed = 0 ;

tUINT8_ITEM uint8Item;
tUINT16_ITEM uint16Item;
tUINT32_ITEM uint32Item;

tSTRING_ITEM stringItem;

MENUDRAWType menuDrawDirection = FULL;
MENUDRAWType itemDrawDirection = FULL;
MENUDRAWType popupDrawDirection = FULL;

tPOPUP popupToShow;

tIMAGE_DATA statusBarImageArray[5];
tIMAGE_DATA safeairBarImageArray[5];

uint8_t nextFrameToDraw[40960] = {0xFF};

void screenInit(void)
{
	isPortrait = (bool)ee.screenOreintation;
	DEV_Module_Init();
	LCD_1IN8_SetBackLight(ee.backLight * 2000);
	if (isPortrait)
	{
		LCD_1IN8_Init(L2R_U2D);
		LCD_1IN8_Clear(BLACK);
		Paint_NewImage(LCD_1IN8_HEIGHT,LCD_1IN8_WIDTH, 0, WHITE);
	}
	else
	{
		LCD_1IN8_Init(U2D_R2L);
		LCD_1IN8_Clear(BLACK);
		Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);
	}

	Paint_SetClearFuntion(LCD_1IN8_Clear);
	Paint_SetDisplayFuntion(LCD_1IN8_DrawPaint);

//	printf("Paint_Clear\r\n");
	Paint_Clear(WHITE);
	DEV_Delay_ms(1000);

	if (isPortrait)
	{
		Paint_DrawImage(gImage_ParaZero_Logo_100_121_LSB, 14, 1, 100, 121);
		Paint_DrawString_EN(1, 130, "Version", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (1, 142 ,fwVersion, 2,  &Font12, BLACK, WHITE);
		Paint_DrawString_EN(70, 130, "BuildID", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (70, 142 ,buildID, 2,  &Font12, BLACK, WHITE);
	}
	else
	{
		Paint_DrawImage(gImage_Logo, 16, 0, 128, 128);
		Paint_DrawString_EN(1, 98, "Version", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (1, 110 ,fwVersion, 2,  &Font12, BLACK, WHITE);
		Paint_DrawString_EN(104, 98, "BuildID", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (124, 110 ,buildID, 2,  &Font12, BLACK, WHITE);
	}


	HAL_Delay(1000);
}

void screenClear(void)
{
	if (isPortrait)
	{
		Paint_NewImage(LCD_1IN8_HEIGHT,LCD_1IN8_WIDTH, 0, WHITE);
	}
	else
	{
		Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);
	}

	Paint_Clear(WHITE);
	DEV_Delay_ms(1000);
}

void centeredString(UWORD XCenterstart, UWORD Ystart, const char * pString, uint16_t textColor, uint16_t backgroundColor, uint8_t numberOfCharactersToClear, sFONT localFont)
{
	uint8_t Xstart = 0;

	Xstart = fmax( XCenterstart - numberOfCharactersToClear * localFont.Width / 2, 0) ;
//	Paint_DrawString_EN(Xstart, Ystart, "MAINTENANCE", &Font12, WHITE,  WHITE);
	if (!renderCompleteFrame)
	{
		Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * localFont.Width, Ystart + localFont.Height, WHITE);
	}
	else if ( (renderCompleteFrame) && (!isMenuDisplayed) && (!isPopupDisplayed) )
	{
		Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * localFont.Width, Ystart + localFont.Height, backgroundColor);
	}
	else if ( (renderCompleteFrame) && ( (isMenuDisplayed) || (isPopupDisplayed) ) )
	{
		Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * localFont.Width, Ystart + localFont.Height, WHITE);
	}
	Xstart = strlen(pString);
	Xstart = fmax( XCenterstart - strlen(pString) * localFont.Width / 2, 0) ;
	Paint_DrawString_EN(Xstart, Ystart, pString, &localFont, backgroundColor,  textColor);
}

void renderSafeAirBattery(bool drawDeltaImage)
{
//	char batteryPercentString[4] = "";
//	char pr[1] = "%";
//	char tempBatteryPercentString[5] = "";
//	uint8_t batteryPercent = 0;
//	batteryPercent = (uint8_t) ((currentSmaStatus.batteryVoltage * 166.6667
//			- 600) / 5) * 5;
//	sprintf(batteryPercentString, "%03d%s", batteryPercent, pr);
//	memcpy(tempBatteryPercentString, batteryPercentString, 5);
//	tempBatteryPercentString[4] = 0;
//	//TODO: Clear text before updating, generate value dynamically
//	Paint_ClearWindows(SafeAirBatteryX,
//			SafeAirBatteryY,
//			SafeAirBatteryX + 5 * Font8.Width,
//			SafeAirBatteryY + Font8.Height, WHITE);
//	Paint_DrawString_EN(SafeAirBatteryX,
//			SafeAirBatteryY, tempBatteryPercentString, &Font8,
//			WHITE, BLACK);


	switch (currentSmaStatus.batteryStrength)
	{
		case EMPTY:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Battery_Alert, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Battery_Alert, previousBatteryImage,
						SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousBatteryImage = gImage_SafeAir_Battery_Alert;
			break; /* optional */
		}

		case LOW:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Battery_Low, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Battery_Low, previousBatteryImage,
						SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousBatteryImage = gImage_SafeAir_Battery_Low;
			break; /* optional */
		}

		case MEDIUM:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Battery_Medium, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Battery_Medium, previousBatteryImage,
						SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousBatteryImage = gImage_SafeAir_Battery_Medium;
			break; /* optional */
		}

		case STRONG:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Battery_Full, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Battery_Full, previousBatteryImage,
						SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousBatteryImage = gImage_SafeAir_Battery_Full;
			break; /* optional */
		}

//		case CHARGING:
//		{
//			if (!drawDeltaImage)
//			{
//				Paint_DrawImage(gImage_Battery_Charging, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
//			}
//			else
//			{
//				Paint_DrawDeltaImage(gImage_Battery_Charging, previousBatteryImage,
//						BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
//			}
//			previousBatteryImage = gImage_Battery_Charging;
//			break; /* optional */
//		}

			/* you can have any number of case statements */
		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Battery_Alert, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Battery_Alert, previousBatteryImage,
						SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousBatteryImage = gImage_SafeAir_Battery_Alert;
		}

	}
}

void updateStatusText(void)
{
	if (currentSmaStatus.smaState == TRIGGERED)
	{
//		Paint_DrawImage(gImage_Parachute_24, Parachute1X, Parachute1Y, 24, 24);
//		Paint_DrawImage(gImage_Parachute_24, Parachute2X, Parachute2Y, 24, 24);
//		centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "TRIGGERED", BLACK, RED);
		addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, RED);
		if (displayWarning.BITStatus & 0x40)
		{
			centeredString(SystemStatusTextX, SystemStatusTextY, "Manual Trigger", WHITE, RED, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x80)
		{
			centeredString(SystemStatusTextX, SystemStatusTextY, "GeoFencing", WHITE, RED, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x100)
		{
			centeredString(SystemStatusTextX, SystemStatusTextY, "AutoPilot", WHITE, RED, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x200)
		{
			centeredString(SystemStatusTextX, SystemStatusTextY, "Freefall", WHITE, RED, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x400)
		{
			centeredString(SystemStatusTextX, SystemStatusTextY, "Critical Angle", WHITE, RED, 14, Font12);
		}
	}
	else if ((currentSmaStatus.smaState == IDLE) && (!displayWarning.displayWarning) && (displayWarning.BITStatus == 0))
	{
		addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3,BLUE);
		centeredString(SystemStatusTextX, SystemStatusTextY, "Idle", WHITE, BLUE, 14, Font12);
		previousBITStatus = displayWarning.BITStatus;
	}
	else if ((currentSmaStatus.smaState == ARMED) && (!displayWarning.displayWarning) && (displayWarning.BITStatus == 0))
	{
		addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, PZGREEN);
		centeredString(SystemStatusTextX, SystemStatusTextY, "Armed", WHITE, PZGREEN, 14, Font12);
		previousBITStatus = displayWarning.BITStatus;
	}
	else if (currentSmaStatus.smaState == AUTOCALIBRATION)
	{
		addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, GRAYBLUE);
		centeredString(SystemStatusTextX, SystemStatusTextY, "Calibration", WHITE, GRAYBLUE, 14, Font12);
	}
	else if (currentSmaStatus.smaState == MAINTENANCE)
	{
		addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, CYAN);
		centeredString(SystemStatusTextX, SystemStatusTextY, "Maintenance", BLACK, CYAN, 14, Font12);
	}

	if (displayWarning.displayWarning)
	{
		if (shouldDrawRedAlertIcon)
		{
			if (currentSmaStatus.smaState != ARMED)
			{
				addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, YELLOW);
				centeredString(SystemStatusTextX, SystemStatusTextY, "Error", BLACK, YELLOW, 14, Font12);
			}
//			Paint_DrawImage(gImage_WarningRed_Icon_24, WarningIconX, WarningIconY, statusBarIconWidth, statusBarIconHeight);
//			shouldDrawRedAlertIcon = false;
			shouldUpdateStatusText = false;
		}
		if (displayWarning.BITStatus & 0x01)
		{
//			Paint_DrawString_EN(WarningTextX, WarningTextY, "SA Critical Bat", &Font12, BLACK, BACKGROUND);
			centeredString(WarningTextX, WarningTextY, "SA Critical Bat", BLACK, BACKGROUND, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x02)
		{
//			Paint_DrawString_EN(WarningTextX, WarningTextY, "SA Low Bat", &Font12, BLACK, BACKGROUND);
			centeredString(WarningTextX, WarningTextY, "SA Low Bat", BLACK, BACKGROUND, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x04)
		{
//			Paint_DrawString_EN(WarningTextX, WarningTextY, "SA Flash Err", &Font12, BLACK, BACKGROUND);
			centeredString(WarningTextX, WarningTextY, "SA Flash Err", BLACK, BACKGROUND, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x08)
		{
//			Paint_DrawString_EN(WarningTextX, WarningTextY, "SA Orientation", &Font12, BLACK, BACKGROUND);
			centeredString(WarningTextX, WarningTextY, "SA Orientation", BLACK, BACKGROUND, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x10)
		{
//			Paint_DrawString_EN(WarningTextX, WarningTextY, "SA Pyro Err", &Font12, BLACK, BACKGROUND);
			centeredString(WarningTextX, WarningTextY, "SA Pyro Err", BLACK, BACKGROUND, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x20)
		{
//			Paint_DrawString_EN(WarningTextX, WarningTextY, "RC Low Bat", &Font12, BLACK, BACKGROUND);
			centeredString(WarningTextX, WarningTextY, "RC Low Bat", BLACK, BACKGROUND, 14, Font12);
		}
//		displayWarning.displayWarning = false;
		//			shouldClearDisplayedWarning = true;
	}
	else if ((!displayWarning.displayWarning) && (shouldClearDisplayedWarning))
	{

		if (!isPortrait)
		{
			Paint_ClearWindows(WarningIconX, WarningIconY, WarningIconX + statusBarIconWidth, WarningIconY + statusBarIconHeight, WHITE);
			Paint_ClearWindows(WarningTextX, WarningTextY, WarningTextX + 14 * Font12.Width, WarningTextY + Font12.Height, WHITE);
		}
		else
		{
			Paint_ClearWindows(0, WarningTextY, VerticalDisplayCenterWidth * 2, WarningTextY + Font12.Height, BACKGROUND);
		}
		shouldClearDisplayedWarning = false;
	}
}

void updatePlatformText(void)
{
	switch (currentSmaStatus.smaPlatformName)
	{
		case M200:
		{
			centeredString(SystemTextX, SystemTextY, "SafeAir M200 Pro", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		case M300:
		{
			centeredString(SystemTextX, SystemTextY, "SafeAir M300 Pro", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		case M600:
		{
			centeredString(SystemTextX, SystemTextY, "SafeAir M600 Pro", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		case PHANTOM:
		{
			centeredString(SystemTextX, SystemTextY, "SafeAir Phantom", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		case MAVIC:
		{
			centeredString(SystemTextX, SystemTextY, "SafeAir Mavic", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		case TAILID:
		{
			if (isTailIDAlreadyReceived)
			{
				centeredString(SystemTextX, SystemTextY, safeAirTailID, BLACK, BACKGROUND, 11, Font16);
			}
			else
			{
				centeredString(SystemTextX, SystemTextY, "Waiting TailID", BLACK, BACKGROUND, 16, Font12);
			}
			break;
		}
		default: /* Optional */
		{
			centeredString(SystemTextX, SystemTextY, "Unknown platform", BLACK, BACKGROUND, 16, Font12);
		}
	}
	previousSmaStatus.smaPlatformName = currentSmaStatus.smaPlatformName;
}

void redrawBatteryIcon(bool drawDeltaImage)
{
	switch (batteryStrength)
	{
	case EMPTY:
		if (!drawDeltaImage)
		{
			Paint_DrawImage(gImage_RC_Battery_Alert, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		else
		{
			Paint_DrawDeltaImage(gImage_RC_Battery_Alert, previousRCBatteryImage,
					BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		previousRCBatteryImage = gImage_RC_Battery_Alert;
		break; /* optional */

	case LOW:
		if (!drawDeltaImage)
		{
			Paint_DrawImage(gImage_RC_Battery_Low, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		else
		{
			Paint_DrawDeltaImage(gImage_RC_Battery_Low, previousRCBatteryImage,
					BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		previousRCBatteryImage = gImage_RC_Battery_Low;
		break; /* optional */

	case MEDIUM:
		if (!drawDeltaImage)
		{
			Paint_DrawImage(gImage_RC_Battery_Medium, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		else
		{
			Paint_DrawDeltaImage(gImage_RC_Battery_Medium, previousRCBatteryImage,
					BatteryX, BatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
		}
		previousRCBatteryImage = gImage_RC_Battery_Medium;
		break; /* optional */

	case STRONG:
		if (!drawDeltaImage)
		{
			Paint_DrawImage(gImage_RC_Battery_Full, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		else
		{
			Paint_DrawDeltaImage(gImage_RC_Battery_Full, previousRCBatteryImage,
					BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		previousRCBatteryImage = gImage_RC_Battery_Full;
		break; /* optional */

	case CHARGING:
		if (!drawDeltaImage)
		{
			Paint_DrawImage(gImage_RC_Battery_Charging, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		else
		{
			Paint_DrawDeltaImage(gImage_RC_Battery_Charging, previousRCBatteryImage,
					BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		previousRCBatteryImage = gImage_RC_Battery_Charging;
		break; /* optional */

			   /* you can have any number of case statements */
	default: /* Optional */
		if (!drawDeltaImage)
		{
			Paint_DrawImage(gImage_RC_Battery_Alert, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		else
		{
			Paint_DrawDeltaImage(gImage_RC_Battery_Alert, previousRCBatteryImage,
					BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
		}
		previousRCBatteryImage = gImage_RC_Battery_Alert;
	}
}

void redrawTriggerModeIcon(bool drawDeltaImage)
{
	switch (currentSmaStatus.safeairTriggerMode)
	{
		case AUTO:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Auto_Trigger, TriggerModeX, TriggerModeY,
						safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Auto_Trigger, previousTriggerModeImage,
						TriggerModeX, TriggerModeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousTriggerModeImage = gImage_SafeAir_Auto_Trigger;
			break; /* optional */
		}

		case MANUAL:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Manual_Trigger, TriggerModeX, TriggerModeY,
						safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Manual_Trigger, previousTriggerModeImage,
						TriggerModeX, TriggerModeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousTriggerModeImage = gImage_SafeAir_Manual_Trigger;
			break; /* optional */
		}

		/* you can have any number of case statements */
		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Manual_Trigger, TriggerModeX, TriggerModeY,
						safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Manual_Trigger, previousTriggerModeImage,
						TriggerModeX, TriggerModeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousTriggerModeImage = gImage_SafeAir_Manual_Trigger;
		}
	}
}

void redrawBluetoothIcon(bool drawDeltaImage)
{
	switch (bluetoothConnection)
	{
		case DISCONNECTED:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Bluetooth_Disconnected, BluetoothX, BluetoothY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Bluetooth_Disconnected, previousBluetoothImage,
						BluetoothX, BluetoothY, statusBarIconWidth, statusBarIconHeight);
			}
			previousBluetoothImage = gImage_Bluetooth_Disconnected;
			break; /* optional */
		}

		case CONNECTED:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Bluetooth_Connected, BluetoothX, BluetoothY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Bluetooth_Connected, previousBluetoothImage,
						BluetoothX, BluetoothY, statusBarIconWidth, statusBarIconHeight);
			}
			previousBluetoothImage = gImage_Bluetooth_Connected;
			break; /* optional */
		}

		//		case PAIRING:
		//			Paint_DrawImage(gImage_Bluetooth_Connected_24, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, statusBarIconHeight);
		//			break; /* optional */

		case SEARCHING:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Bluetooth_Searching, BluetoothX, BluetoothY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Bluetooth_Searching, previousBluetoothImage,
						BluetoothX, BluetoothY, statusBarIconWidth, statusBarIconHeight);
			}
			previousBluetoothImage = gImage_Bluetooth_Searching;
			break; /* optional */
		}

		/* you can have any number of case statements */
		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Bluetooth_Disconnected, BluetoothX, BluetoothY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Bluetooth_Disconnected, previousBluetoothImage,
						BluetoothX, BluetoothY, statusBarIconWidth, statusBarIconHeight);
			}
			previousBluetoothImage = gImage_Bluetooth_Disconnected;
		}
	}
}

void redrawSignalStrengthIcon(bool drawDeltaImage)
{
	switch (tbsLink)
	{
		case NOSIGNAL:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_RedNone, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_RedNone, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);

			}
			previousSignalImage = gImage_Signal_RedNone;
			break; /* optional */
		}

		case LOW:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_Low, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_Low, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			previousSignalImage = gImage_Signal_Low;
			break; /* optional */
		}

		case MEDIUM:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_Medium, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_Medium, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			previousSignalImage = gImage_Signal_Medium;
			break; /* optional */
		}

		case STRONG:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_Strong, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_Strong, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			previousSignalImage = gImage_Signal_Strong;
			break; /* optional */
		}

		/* you can have any number of case statements */
		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_RedNone, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_RedNone, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			previousSignalImage = gImage_Signal_RedNone;
		}
	}
}

void redrawAutoPilotIcon(bool drawDeltaImage)
{
	switch (currentSmaStatus.autoPilotConnection)
	{
		case DISCONNECTED:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_AutoPilot_Disconnected, AutoPilotX, AutoPilotY,
						safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_AutoPilot_Disconnected, previousAutoPilotImage,
						AutoPilotX, AutoPilotY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousAutoPilotImage = gImage_AutoPilot_Disconnected;
			break; /* optional */
		}

		case CONNECTED:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_AutoPilot_Connected, AutoPilotX, AutoPilotY,
						safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_AutoPilot_Connected, previousAutoPilotImage,
						AutoPilotX, AutoPilotY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousAutoPilotImage = gImage_AutoPilot_Connected;
			break; /* optional */
		}

		/* you can have any number of case statements */
		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_AutoPilot_Disconnected, AutoPilotX, AutoPilotY,
						safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_AutoPilot_Disconnected, previousAutoPilotImage,
						AutoPilotX, AutoPilotY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousAutoPilotImage = gImage_AutoPilot_Disconnected;
		}
	}
}

void redrawPlatformIcon(bool drawDeltaImage)
{
	switch (currentSmaStatus.smaPlatfom)
	{
		case MULTICOPTER:
		{
			if (!drawDeltaImage)
			{

				Paint_DrawImage(gImage_Multicopter, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);

			}
			else
			{
				Paint_DrawDeltaImage(gImage_Multicopter, previousPlatformImage,
						PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousPlatformImage = gImage_Multicopter;
			break; /* optional */
		}

		case VTOLHORIZONTAL:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_VTOLHorizontal, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_VTOLHorizontal, previousPlatformImage,
						PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousPlatformImage = gImage_VTOLHorizontal;
			break; /* optional */
		}

		case VTOLTRANSITION:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_VTOLTransition, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_VTOLTransition, previousPlatformImage,
						PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousPlatformImage = gImage_VTOLTransition;
			break; /* optional */
		}

		case VTOLVERTICAL:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_VTOLVertical, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_VTOLVertical, previousPlatformImage,
						PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousPlatformImage = gImage_VTOLVertical;
			break; /* optional */
		}

		/* you can have any number of case statements */
		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Multicopter, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Multicopter, previousPlatformImage,
						PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
			}
			previousPlatformImage = gImage_Multicopter;
		}
	}
}

void drawAltitudeIcon(bool drawDeltaImage)
{

	if (!drawDeltaImage)
	{
		Paint_DrawImage(gImage_Altitude, AltitudeOrGPSX, AltitudeOrGPSY, statusBarIconWidth, statusBarIconHeight);
	}
	else
	{
		Paint_DrawDeltaImage(gImage_Altitude, previousAltitudeOrGPSImage,
				AltitudeOrGPSX, AltitudeOrGPSY, statusBarIconWidth, statusBarIconHeight);
	}
	previousAltitudeOrGPSImage = gImage_Altitude;

}

void screenUpdate(bool drawDeltaImage)
{
	numberOfDisplayedSafeAirIcons = 1 * isAutoPilotDisplayed + 1 * isPlatformDisplayed +
			1 * isTriggerModeDisplayed + 1 * isSafeAirBatteryDisplayed;
	setIconPositionOnScreen();
	if ( (!isMenuDisplayed) && (!isPopupDisplayed) )
	{
		if ( (shouldReDrawPlatformIcon) && (isPlatformDisplayed) )
		{
			redrawPlatformIcon(drawDeltaImage);
			shouldReDrawPlatformIcon = false;
		} // End of Should draw platform icon

		if ( (shouldReDrawAutoPilotIcon) && (isAutoPilotDisplayed) )
		{
			redrawAutoPilotIcon(drawDeltaImage);
			shouldReDrawAutoPilotIcon = false;
		} // End of should draw Auto-pilot icon

		if (shouldRedrawSignalStrengthIcon)
		{
			redrawSignalStrengthIcon(drawDeltaImage);
			shouldRedrawSignalStrengthIcon = false;
		} // end of should draw signal strength icon

		if (shouldReDrawBluetoothIcon)
		{
			redrawBluetoothIcon(drawDeltaImage);
			shouldReDrawBluetoothIcon = false;
		}// End of should draw bluetooth icon

		if ( (shouldReDrawTriggerModeIcon) && (isTriggerModeDisplayed) )
		{
			redrawTriggerModeIcon(drawDeltaImage);
			shouldReDrawTriggerModeIcon = false;
		}// End of should redraw trigger mode

		if (shouldRedrawBatteryIcon)
		{
			redrawBatteryIcon(drawDeltaImage);
			shouldRedrawBatteryIcon = false;
		} // End of should redraw battery icon

		if (shouldUpdatePlatformText)
		{
			//TODO: update to display Tail ID or PlatformType
			updatePlatformText();
			shouldUpdatePlatformText = false;
		} // End of should update platform text

		if ( (shouldUpdateStatusText)  && (HAL_GetTick() - lastBITStatusChange > 500) )
		{
			lastBITStatusChange = HAL_GetTick();
			updateStatusText();
			shouldUpdateStatusText = false;
		} // End of should update status text

		if ( (shouldRedrawSafeAirBatteryIcon) && (isSafeAirBatteryDisplayed) )
		{
			renderSafeAirBattery(drawDeltaImage);
			shouldRedrawSafeAirBatteryIcon = false;
		}

		if ( (shouldDrawSafeAirAltitude) )
		{
			char localText[12] = "";
			if ((currentSmaStatus.smaState != ARMED) && (currentSmaStatus.smaState != TRIGGERED))
			{
				sprintf(localText, "%06.1f m", 0.0);
			}
			else
			{
				sprintf(localText, "%06.1f m", currentSmaStatus.Altitude);
			}
 			centeredString(74, 138, localText, BLACK, BACKGROUND, 14, Font16);
			drawAltitudeIcon(drawDeltaImage);
			shouldDrawSafeAirAltitude = false;
		}

//		if (!drawDeltaImage)
//		{
//			Paint_DrawImage(gImage_SafeAir_Logo_74_11, HorizontalSafeAirLogo7411IconX, HorizontalSafeAirLogo7411IconY, 74, 11);
//			Paint_DrawImage(gImage_Battery_Full, HorizontalSafeAirBatteryIconX, HorizontalSafeAirBatteryIconY,
//					iconWidth, iconHeight);
//			Paint_DrawImage(gImage_Altitude_24, HorizontalAltitudeIconX, HorizontalAltitudeIconY, iconWidth, iconHeight);
//		}

//		if ( (shouldRenderBatteryPercent) || (HAL_GetTick() - lastBatteryRefresh > 60000) ) //|| (lastBatteryRefresh == 0)
//		{
//			renderSafeAirBatteryPercent(bool drawDeltaImage);
			//	  Paint_DrawString_EN(HorizontalAltitudeText1X, HorizontalAltitudeText1Y, "Alt[m]", &Font8, WHITE, BLACK);
			//TODO: Clear text before updating, generate value dynamically
			//	  Paint_DrawString_EN(HorizontalAltitudeText2X, HorizontalAltitudeText2Y, "999.9", &Font8, WHITE, BLACK);
//			lastBatteryRefresh = HAL_GetTick();
//			shouldRenderBatteryPercent = false;
//		} // End of should draw SafeAir battery value
	} // end of RC and SafeAir data display
	else if (isMenuDisplayed)
	{
		if (shouldRenderMenu)
		{
			drawMenu(shouldClearScreen, menuDrawDirection);
			shouldRenderMenu = false;
		}
		if (shouldRenderItem)
		{
			drawItem(false, itemDrawDirection);
			shouldRenderItem = false;
		}

	} // End of is Menu displayed
	if(shouldRenderPopup)
	{
		drawPopup();
		shouldRenderPopup = false;
	}
}

void drawMenu(bool clearScreen, MENUDRAWType howToDraw)
{
	if (clearScreen)
	{
		Paint_Clear(WHITE);
		createEmptyFrame(true);
	}

	uint8_t MenuRectangleStartX = 0;
	uint8_t MenuRectangleStartY = 0;
	uint8_t MenuRectangleHeight = 0;
	uint8_t MenuRectangleWidth = 0;
	uint8_t DisplayCenterWidth = 0;

	if (isPortrait)
	{
		MenuRectangleStartX = VerticalMenuRectangleStartX;
		MenuRectangleStartY = VerticalMenuRectangleStartY;
		MenuRectangleHeight = VerticalMenuRectangleHeight;
		MenuRectangleWidth = VerticalMenuRectangleWidth;
		DisplayCenterWidth = VerticalDisplayCenterWidth;
	}
	else
	{
		MenuRectangleStartX = HorizontalMenuRectangleStartX;
		MenuRectangleStartY = HorizontalMenuRectangleStartY;
		MenuRectangleHeight = HorizontalMenuRectangleHeight;
		MenuRectangleWidth = HorizontalMenuRectangleWidth;
		DisplayCenterWidth = HorizontalDisplayCenterWidth;
	}

	if (howToDraw == FULL)
	{
		for (int i = 0; i < pagesArray[currentCursorPosition.currentPageID].numberOfItemsInPage; i++)
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * ( i + 1),
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			if (i == currentCursorPosition.cursorPosition)
			{
				centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * i,
						pagesArray[currentCursorPosition.currentPageID].itemsArray[i], BLACK, LGRAY, 16, Font12);
			}
			else
			{
				centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * i,
						pagesArray[currentCursorPosition.currentPageID].itemsArray[i], BLACK, WHITE, 16, Font12);
			}
		}
	}
	else if (howToDraw == UP)
	{
		centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * (currentCursorPosition.cursorPosition + 1),
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition + 1], BLACK, WHITE, 16, Font12);
		centeredString(DisplayCenterWidth, MenuRectangleStartY+ 1 + MenuRectangleHeight * currentCursorPosition.cursorPosition,
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition], BLACK, LGRAY, 16, Font12);
	}
	else if (howToDraw == DOWN)
	{
		centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * (currentCursorPosition.cursorPosition - 1),
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition - 1], BLACK, WHITE, 16, Font12);
		centeredString(DisplayCenterWidth, MenuRectangleStartY+ 1 + MenuRectangleHeight * currentCursorPosition.cursorPosition,
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition], BLACK, LGRAY, 16, Font12);
	}
}

void drawItem(bool clearScreen, MENUDRAWType howToDraw)
{
	if ((clearScreen) || (!isItemDisplayed) )
	{
		Paint_Clear(WHITE);
		createEmptyFrame(true);
	}
	if ( pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
			cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == UINT16_ITEM )
	{
		if ( !(isItemDisplayed) )
		{
			multiplierIndex = 0;
			memcpy(&uint16Item, (uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
					nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], sizeof(tUINT16_ITEM));
			itemIDtoUpdate = uint16Item.itemID;
		}
		isItemDisplayed = true;
		updateUint16Item(howToDraw);
	}
	if ( pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
			cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == STRING_ITEM )
	{
		if ( !(isItemDisplayed) )
		{
			multiplierIndex = 0;
			memcpy(&stringItem, (uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
					nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], sizeof(tSTRING_ITEM));
			itemIDtoUpdate = stringItem.itemID;
		}
		isItemDisplayed = true;
		updateStringItem(howToDraw);
	}
}

void drawPopup(void)
{
	uint8_t MenuRectangleStartX = 0;
	uint8_t MenuRectangleStartY = 0;
	uint8_t MenuRectangleHeight = 0;
	uint8_t MenuRectangleWidth = 0;
	uint8_t DisplayCenterWidth = 0;
	uint8_t PopupRectangleHeight = 0;
	uint8_t QuestionRectangleHeight = 0;

	if (isPortrait)
	{
		MenuRectangleStartX = VerticalMenuRectangleStartX;
		MenuRectangleStartY = VerticalMenuRectangleStartY;
		MenuRectangleHeight = VerticalMenuRectangleHeight;
		MenuRectangleWidth = VerticalMenuRectangleWidth;
		DisplayCenterWidth = VerticalDisplayCenterWidth;
		PopupRectangleHeight = VerticalPopupRectangleHeight;
		QuestionRectangleHeight = VerticalQuestionRectangleHeight;
	}
	else
	{
		MenuRectangleStartX = HorizontalMenuRectangleStartX;
		MenuRectangleStartY = HorizontalMenuRectangleStartY;
		MenuRectangleHeight = HorizontalMenuRectangleHeight;
		MenuRectangleWidth = HorizontalMenuRectangleWidth;
		DisplayCenterWidth = HorizontalDisplayCenterWidth;
		PopupRectangleHeight = HorizontalPopupRectangleHeight;
		QuestionRectangleHeight = HorizontalQuestionRectangleHeight;
	}

	isPopupDisplayed = true;
	isItemDisplayed = false;
	isMenuDisplayed = false;
	if (popupDrawDirection == FULL)
	{
		Paint_Clear(WHITE);
		createEmptyFrame(true);
		Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY ,
				MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + PopupRectangleHeight,
				BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );

		if (popupToShow.isQuestion)
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + QuestionRectangleHeight,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + QuestionRectangleHeight + MenuRectangleHeight,
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
		}

		Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + PopupRectangleHeight,
				MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + PopupRectangleHeight + MenuRectangleHeight,
				BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );

		for (int i = 0 ; i < popupToShow.numberOfItemsInPopup - 2; i++)
		{
			centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1) + 1,
					popupToShow.itemsArray[i], BLACK, WHITE, 16, Font12);
		}
	}

	if (popupToShow.isQuestion)
	{
		if ( (popupDrawDirection == FULL) || (popupDrawDirection == UP))
		{
			centeredString( DisplayCenterWidth, MenuRectangleStartY + QuestionRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 2], BLACK, LGRAY, 16, Font12);

			centeredString( DisplayCenterWidth, MenuRectangleStartY + PopupRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, WHITE, 16, Font12);
		}
		else
		{
			centeredString( DisplayCenterWidth, MenuRectangleStartY + QuestionRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 2], BLACK, WHITE, 16, Font12);

			centeredString( DisplayCenterWidth, MenuRectangleStartY + PopupRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, LGRAY, 16, Font12);
		}
	}
	else
	{
		centeredString( DisplayCenterWidth, MenuRectangleStartY + PopupRectangleHeight + 1,
				popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, LGRAY, 16, Font12);
	}
}

void setFullDisplay(void)
{
	shouldRedrawBatteryIcon = true;
	shouldRedrawSignalStrengthIcon = true;
	shouldReDrawBluetoothIcon = isBLEOn;

	shouldUpdatePlatformText = true;

	shouldUpdateStatusText = true;

	shouldReDrawAutoPilotIcon = false;
	shouldReDrawPlatformIcon = false;
	shouldReDrawTriggerModeIcon = true;
	shouldRedrawSafeAirBatteryIcon = true;
	shouldDrawSafeAirAltitude = true;

	shouldClearDisplayedWarning = false;
	isPopupDisplayed = false;
	isMenuDisplayed = false;
	isItemDisplayed = false;
	shouldRenderPopup = false;
	shouldRenderItem = false;
	shouldRenderMenu = false;

//	shouldDrawRedAlertIcon = false;
}

void setIconPositionOnScreen(void)
{
	if (isPortrait)
	{

		BluetoothX = VerticalBluetoothX;
		BluetoothY = VerticalBluetoothY;
		TBSSignalX = VerticalTBSSignalX;
		TBSSignalY = VerticalTBSSignalY;
		BatteryX = VerticalBatteryX;
		BatteryY = VerticalBatteryY;

		AutoPilotY = VerticalAutoPilotY;

		SystemStatusTextX = VerticalSystemStatusTextX;
		SystemStatusTextY = VerticalSystemStatusTextY;

		SystemTextX = VerticalSystemTextX;
		SystemTextY = VerticalSystemTextY;

		WarningTextX = VerticalWarningTextX;
		WarningTextY = VerticalWarningTextY;

		LineStartX = VerticalSafeAirLineStartX;
		LineEndX = VerticalSafeAirLineEndX;
		LineY = VerticalSafeAirLineY;

		AltitudeOrGPSX = VerticalAltitudeOrGPSX;
		AltitudeOrGPSY = VerticalAltitudeOrGPSY;


		SafeAirBatteryX = (numberOfDisplayedSafeAirIcons /2 - 1 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;//VerticalSafeAirBatteryX;
		SafeAirBatteryY = VerticalSafeAirBatteryY;
		TriggerModeX = (numberOfDisplayedSafeAirIcons /2 - 2 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;
		TriggerModeY = VerticalTriggerModeY;
		PlatfomTypeX = (numberOfDisplayedSafeAirIcons /2 - 3 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;
		PlatfomTypeY = VerticalPltfomTypeY;
		AutoPilotX = (numberOfDisplayedSafeAirIcons /2 - 4 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;
		AutoPilotY = VerticalAutoPilotY;
	}
	else
	{
		PlatfomTypeX = HorizontalPltfomTypeX;
		PlatfomTypeY = HorizontalPltfomTypeY;
		AutoPilotX = HorizontalAutoPilotX;
		AutoPilotY = HorizontalAutoPilotY;
		TBSSignalX = HorizontalTBSSignalX;
		TBSSignalY = HorizontalTBSSignalY;
		BluetoothX = HorizontalBluetoothX;
		BluetoothY = HorizontalBluetoothY;
		TriggerModeX = HorizontalTriggerModeX;
		TriggerModeY = HorizontalTriggerModeY;
		BatteryX = HorizontalBatteryX;
		BatteryY = HorizontalBatteryY;
		SystemTextX = HorizontalSystemTextX;
		SystemTextY = HorizontalSystemTextY;
		SafeAirBatteryX = HorizontalSafeAirBatteryTextX;
		SafeAirBatteryY = HorizontalSafeAirBatteryTextY;

	}
}
