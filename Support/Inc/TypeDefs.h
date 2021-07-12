/*
 * TypeDefs.h
 *
 *  Created on: Feb 7, 2021
 *      Author: gilad
 */

#ifndef INC_TYPEDEFS_H_
#define INC_TYPEDEFS_H_

// EEPROM Data Validation Structures
typedef struct
{
  uint8_t min;
  uint8_t std;
  uint8_t max;
} tEEV_U08;

typedef struct
{
  int8_t min;
  int8_t std;
  int8_t max;
} tEEV_S08;

typedef struct
{
  uint16_t min;
  uint16_t std;
  uint16_t max;
} tEEV_U16;

typedef struct
{
  int16_t min;
  int16_t std;
  int16_t max;
} tEEV_S16;

typedef struct
{
  uint32_t min;
  uint32_t std;
  uint32_t max;
} tEEV_U32;

typedef struct
{
   int32_t min;
   int32_t std;
   int32_t max;
} tEEV_S32;

typedef struct
{
  float min;
  float std;
  float max;
} tEEV_FLOAT;

// Pointer types of EEPROM Data Validation Structures
typedef tEEV_U08* pEEV_U08;
typedef tEEV_S08* pEEV_S08;
typedef tEEV_U16* pEEV_U16;
typedef tEEV_S16* pEEV_S16;
typedef tEEV_U32* pEEV_U32;
typedef tEEV_S32* pEEV_S32;
typedef tEEV_FLOAT* pEEV_FLOAT;

// Enumeration of EEPROM Data Validation types
typedef enum
{
  EEV_U08 = 0,
  EEV_S08,
  EEV_U16,
  EEV_S16,
  EEV_U32, //  = 0
  EEV_S32,
  EEV_FLOAT
} eEEV_DATA_TYPE;

typedef uint8_t* pU08;
typedef const uint8_t* cpU08;
typedef int8_t* pS08;
typedef uint16_t* pU16;
typedef int16_t* pS16;
typedef uint32_t* pU32;
typedef int32_t* pS32;
typedef float* pFLOAT;

extern uint8_t phrase[256];
//-----------------------------------------------------------------------------

uint32_t ee_validate_data(eEEV_DATA_TYPE data_type, void* value_ptr, void* eev_ptr);
void ee_disp_memory(void);
extern bool ee_save1(void);
extern void ee_init1(pU32 data_base1, uint32_t data_size1);

#endif /* INC_TYPEDEFS_H_ */
