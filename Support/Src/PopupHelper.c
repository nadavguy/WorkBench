/*
 * popupHelper.c
 *
 *  Created on: May 2, 2021
 *      Author: gilad
 */


#include "main.h"

void waitForPopupInput(void)
{
	if (popupToShow.popupID != 0)
	{
		shouldRenderPopup = true;
		screenUpdate(false);
		switch (popupToShow.popupID)
		{
			case 1:
			{

				while ( (tbsLink == NOSIGNAL) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{
						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
//					HAL_Delay(50);
					screenUpdate(false);
				}
				break;
			}
			case 2:
			{
				while ( (okButtonPressDuration < 1000) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{
						forceDisarmEnabled = true;
						waitForAckResponse = true;
						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
//					HAL_Delay(50);
					screenUpdate(false);
				}
				while (waitForAckResponse)
				{
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
				}
				break;
			}
			default:
			{
				break;
			}
		}
		memset(&popupToShow, 0, sizeof(popupToShow));
		screenClear();
		setFullDisplay();
		screenUpdate(false);
	}
}
