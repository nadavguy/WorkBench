/*
 * MenuHelper.h
 *
 *  Created on: Apr 20, 2021
 *      Author: gilad
 */

#ifndef INC_MENUHELPER_H_
#define INC_MENUHELPER_H_

#define MAX_ITEMS_IN_PAGE 32
#define MAX_CHARACTERS_IN_ITEM 16

typedef enum {PAGE, UINT8_ITEM, UINT16_ITEM, UINT32_ITEM, INT8_ITEM, INT16_ITEM, INT32_ITEM, FLOAT_ITEM, STRING_ITEM, BACK, CLOSE, VALUE, MULTIPLIER, POPUP} CELLType;
typedef enum {UP, DOWN, FULL, LEFT, RIGHT} MENUDRAWType;

typedef struct sCURSOR_DATA
{
	uint8_t cursorPosition;
	uint8_t currentPageID;
	uint8_t previousPageID[5];
	uint8_t previousPageCursorPosition[5];
	uint8_t menuDepth;
}tCURSOR_DATA;

typedef struct sMENU_PAGE
{
	uint8_t pageID;
	uint8_t numberOfItemsInPage;
	char itemsArray[MAX_ITEMS_IN_PAGE][MAX_CHARACTERS_IN_ITEM];
	CELLType cellTypeArray[MAX_ITEMS_IN_PAGE];
	uint32_t nextCellIDArray[MAX_ITEMS_IN_PAGE];
}tMENU_PAGE;

typedef struct sUINT8_ITEM
{
	uint8_t itemID;
	uint8_t minValue;
	uint8_t maxValue;
	uint8_t startValue;
	uint8_t delta; //Increment Or Decrement - always positive
	uint8_t deltaMultiplier; // 1, 2, 5, 10, 100, 500
	uint8_t numberOfItemsInPage;
	char itemsArray[MAX_ITEMS_IN_PAGE][MAX_CHARACTERS_IN_ITEM];

}tUINT8_ITEM;

typedef struct sUINT16_ITEM
{
	uint8_t itemID;
	uint16_t minValue;
	uint16_t maxValue;
	uint16_t startValue;
	uint16_t delta; //Increment Or Decrement
	uint16_t deltaMultiplier; // 1, 2, 5, 10, 100, 500
	uint8_t numberOfItemsInPage;
	char itemsArray[MAX_ITEMS_IN_PAGE][MAX_CHARACTERS_IN_ITEM];
}tUINT16_ITEM;

typedef struct sUINT32_ITEM
{
	uint8_t itemID;
	uint32_t minValue;
	uint32_t maxValue;
	uint32_t startValue;
	uint32_t delta; //Increment Or Decrement
	uint32_t deltaMultiplier; // 1, 2, 5, 10, 100, 500
	uint8_t numberOfItemsInPage;
	char itemsArray[MAX_ITEMS_IN_PAGE][MAX_CHARACTERS_IN_ITEM];

}tUINT32_ITEM;

typedef struct sINT8_ITEM
{
	uint8_t itemID;
	int8_t minValue;
	int8_t maxValue;
	int8_t startValue;
	int8_t delta; //Increment Or Decrement - always positive
	int8_t deltaMultiplier; // 1, 2, 5, 10, 100, 500
	uint8_t numberOfItemsInPage;
	char itemsArray[MAX_ITEMS_IN_PAGE][MAX_CHARACTERS_IN_ITEM];

}tINT8_ITEM;

typedef struct sINT16_ITEM
{
	uint8_t itemID;
	int16_t minValue;
	int16_t maxValue;
	int16_t startValue;
	int16_t delta; //Increment Or Decrement
	int16_t deltaMultiplier; // 1, 2, 5, 10, 100, 500
	uint8_t numberOfItemsInPage;
	char itemsArray[MAX_ITEMS_IN_PAGE][MAX_CHARACTERS_IN_ITEM];

}tINT16_ITEM;

typedef struct sINT32_ITEM
{
	uint8_t itemID;
	int32_t minValue;
	int32_t maxValue;
	int32_t startValue;
	int32_t delta; //Increment Or Decrement
	int32_t deltaMultiplier; // 1, 2, 5, 10, 100, 500
	uint8_t numberOfItemsInPage;
	char itemsArray[MAX_ITEMS_IN_PAGE][MAX_CHARACTERS_IN_ITEM];

}tINT32_ITEM;

typedef struct sFLOAT_ITEM
{
	uint8_t itemID;
	float minValue;
	float maxValue;
	float startValue;
	float delta; //Increment Or Decrement
	float deltaMultiplier; // 1, 0.2, 0.5, 0.10, 0.0100, 0.0200
	uint8_t numberOfItemsInPage;
	char itemsArray[MAX_ITEMS_IN_PAGE][MAX_CHARACTERS_IN_ITEM];

}tFLOAT_ITEM;

extern tMENU_PAGE MainPage;
extern tMENU_PAGE pagesArray[5];

extern tUINT16_ITEM brightnessItem;


extern void initMenuPages(void);
extern void updateSelection(void);
extern void initMenuItems(void);
#endif /* INC_MENUHELPER_H_ */
