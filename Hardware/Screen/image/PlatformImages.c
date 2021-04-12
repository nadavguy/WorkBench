/*
 * PlatformImages.c
 *
 *  Created on: Apr 6, 2021
 *      Author: gilad
 */

#include "PlatformImages.h"

const unsigned char gImage_Multicopter[1152] = { /* 0X00,0X10,0X18,0X00,0X18,0X00,0X01,0X1B, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0XBD,0X65,0X29,0X20,0X00,0X41,0X08,0X2C,0X63,
0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X14,0XA5,0X8A,0X52,0X49,0X4A,0X8E,0X73,0X9E,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X18,0XC6,0X41,0X08,0X51,0X8C,0X9A,0XD6,0X38,0XC6,0XC7,0X39,
0X08,0X42,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X2C,0X63,
0XA2,0X10,0X10,0X84,0X34,0XA5,0XE7,0X39,0X04,0X21,0X3C,0XE7,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X24,0X21,0X30,0X84,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XC3,0X18,0XF3,0X9C,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XD7,0XBD,0X41,0X08,
0X1C,0XE7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XAA,0X52,0X69,0X4A,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X00,0X00,0XDB,0XDE,0XFF,0XFF,0X49,0X4A,0XEB,0X5A,0XFF,0XFF,
0XCB,0X5A,0X0C,0X63,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0X2C,0X63,0X8A,0X52,
0XFF,0XFF,0X30,0X84,0X45,0X29,0X9E,0XF7,0XBA,0XD6,0X00,0X00,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X20,0X00,0X59,0XCE,0XFF,0XFF,0X0C,0X63,0X00,0X00,0XAE,0X73,
0XD7,0XBD,0X71,0X8C,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCF,0X7B,0X55,0XAD,
0XD3,0X9C,0X00,0X00,0X04,0X21,0XBE,0XF7,0XBA,0XD6,0X00,0X00,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X2C,0X63,0XA6,0X31,0XDF,0XFF,0XFF,0XFF,0XCF,0X7B,0X00,0X00,
0XEB,0X5A,0X9E,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0XEF,0X7B,
0X00,0X00,0XC7,0X39,0XFF,0XFF,0XFF,0XFF,0XCB,0X5A,0X28,0X42,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XDF,0XFF,0X28,0X42,0XE3,0X18,0X8A,0X52,0XD7,0XBD,0X0C,0X63,
0X00,0X00,0X65,0X29,0XF7,0XBD,0XFF,0XFF,0XFF,0XFF,0XBA,0XD6,0X8A,0X52,0X00,0X00,
0X65,0X29,0X38,0XC6,0X34,0XA5,0X69,0X4A,0X82,0X10,0XDB,0XDE,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X34,0XA5,0X8E,0X73,0X71,0X8C,0X9E,0XF7,
0X65,0X29,0X00,0X00,0X00,0X00,0XC3,0X18,0XE3,0X18,0X00,0X00,0X00,0X00,0X61,0X08,
0X1C,0XE7,0XEF,0X7B,0XE3,0X18,0X4D,0X6B,0X3C,0XE7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X59,0XCE,0X20,0X00,0X41,0X08,0XCF,0X7B,0X92,0X94,0XC3,0X18,0X00,0X00,0X51,0X8C,
0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XE3,0X18,0XCF,0X7B,0X2C,0X63,0X08,0X42,0X51,0X8C,0X82,0X10,0X7D,0XEF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X04,0X21,0X71,0X8C,0X49,0X4A,0X82,0X10,0X71,0X8C,0XC3,0X18,0XBE,0XF7,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFB,0XDE,0X20,0X00,0XA2,0X10,0X10,0X84,0X30,0X84,0X08,0X42,0X00,0X00,0X34,0XA5,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XD7,0XBD,0X8E,0X73,0XEF,0X7B,0XDF,0XFF,
0X69,0X4A,0X00,0X00,0X00,0X00,0X41,0X08,0XA2,0X10,0X00,0X00,0X00,0X00,0X04,0X21,
0X5D,0XEF,0X30,0X84,0XCB,0X5A,0X71,0X8C,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X0C,0X63,0XA2,0X10,0X28,0X42,0X14,0XA5,0XEF,0X7B,
0X00,0X00,0X82,0X10,0X71,0X8C,0X7D,0XEF,0XDF,0XFF,0X75,0XAD,0X45,0X29,0X00,0X00,
0X49,0X4A,0X18,0XC6,0X51,0X8C,0X45,0X29,0XA6,0X31,0X9E,0XF7,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XB2,0X94,0X61,0X08,0X1C,0XE7,0XFF,0XFF,0XB2,0X94,0X00,0X00,
0X86,0X31,0X1C,0XE7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X9E,0XF7,0X0C,0X63,
0X00,0X00,0X6D,0X6B,0XFF,0XFF,0XFF,0XFF,0XC7,0X39,0X4D,0X6B,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XA6,0X31,0XF3,0X9C,0XFF,0XFF,0X10,0X84,0X00,0X00,0X08,0X42,
0X18,0XC6,0X71,0X8C,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X30,0X84,0X18,0XC6,
0X10,0X84,0X00,0X00,0X8A,0X52,0XFF,0XFF,0X18,0XC6,0X41,0X08,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X04,0X21,0XF7,0XBD,0XFF,0XFF,0X24,0X21,0X65,0X29,0XDF,0XFF,
0X34,0XA5,0X45,0X29,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCB,0X5A,0XAE,0X73,
0XFF,0XFF,0X2C,0X63,0X00,0X00,0XBE,0XF7,0X79,0XCE,0X00,0X00,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XEB,0X5A,0X8A,0X52,0XFF,0XFF,0XBE,0XF7,0XFF,0XFF,0XFF,0XFF,
0XE7,0X39,0XAE,0X73,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XD3,0X9C,0XA2,0X10,
0XDF,0XFF,0XFF,0XFF,0XBE,0XF7,0XFF,0XFF,0XEB,0X5A,0X69,0X4A,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFB,0XDE,0X61,0X08,0X6D,0X6B,0XBA,0XD6,0X9A,0XD6,0XEB,0X5A,
0XA2,0X10,0X5D,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XFF,0X28,0X42,
0X24,0X21,0X75,0XAD,0X18,0XC6,0XCB,0X5A,0X61,0X08,0XDB,0XDE,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBA,0XD6,0XE7,0X39,0X00,0X00,0X00,0X00,0X69,0X4A,
0XFB,0XDE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XEF,0X7B,0X04,0X21,0X61,0X08,0XEB,0X5A,0X1C,0XE7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

const unsigned char gImage_VTOLTransition[1152] = { /* 0X00,0X10,0X18,0X00,0X18,0X00,0X01,0X1B, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X75,0XAD,0X00,0X00,0X65,0X29,0X9E,0XF7,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X1C,0XE7,0XEF,0X7B,0X10,0X84,0X92,0X94,
0XFF,0XFF,0XBA,0XD6,0X00,0X00,0X4D,0X6B,0XEB,0X5A,0XE7,0X39,0XFF,0XFF,0XBA,0XD6,
0X6D,0X6B,0X6D,0X6B,0X71,0X8C,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0XCB,0X52,0X00,0X00,0XD3,0X94,
0XFF,0XFF,0X08,0X42,0X10,0X7C,0X49,0X4A,0XFF,0XFF,0X81,0X08,0X9A,0XD6,0X5D,0XEF,
0X28,0X42,0X00,0X00,0X55,0XAD,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X59,0XC6,0X8D,0X6B,0XEF,0X7B,0X4D,0X63,0X61,0X08,0X71,0X84,
0X2C,0X63,0X00,0X00,0X48,0X42,0X0F,0X7C,0X0C,0X63,0XA2,0X10,0X04,0X19,0XCF,0X73,
0XEB,0X5A,0X82,0X08,0XB2,0X94,0X0B,0X5B,0X71,0X8C,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X9A,0XCE,0X24,0X21,0X30,0X84,0X08,0X3A,0X81,0X08,0XCE,0X73,0X00,0X00,
0XAE,0X73,0XD7,0XB5,0X10,0X84,0X14,0X9D,0XF3,0X9C,0X71,0X8C,0X75,0XAD,0XA6,0X31,
0X03,0X19,0XAE,0X73,0X00,0X00,0XF3,0X9C,0XAA,0X52,0X0C,0X5B,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X71,0X8C,0X4D,0X63,0X0C,0X63,0XF3,0X94,0X28,0X42,0X5D,0XEF,0XE3,0X18,
0XFF,0XFF,0X4D,0X6B,0XFF,0XFF,0X4D,0X6B,0X4D,0X6B,0XFF,0XFF,0X4D,0X6B,0X92,0X8C,
0XAA,0X52,0XFB,0XDE,0X03,0X19,0X2C,0X63,0XC3,0X18,0X61,0X08,0XDB,0XDE,0XFF,0XFF,
0XFF,0XFF,0X10,0X84,0XAA,0X4A,0X00,0X00,0XB6,0XB5,0X69,0X4A,0XFF,0XFF,0X04,0X19,
0X65,0X29,0X00,0X00,0XFF,0XFF,0X00,0X00,0X00,0X00,0X45,0X29,0X00,0X00,0X14,0XA5,
0X0C,0X63,0XDF,0XFF,0X24,0X21,0X00,0X00,0X14,0XA5,0X00,0X00,0X1C,0XE7,0XFF,0XFF,
0XFF,0XFF,0X5D,0XE7,0X82,0X10,0XA2,0X10,0X85,0X29,0X00,0X00,0X28,0X42,0X00,0X00,
0X24,0X21,0X69,0X4A,0X0C,0X5B,0XE3,0X18,0X45,0X29,0X08,0X42,0X08,0X42,0X04,0X19,
0X41,0X00,0X08,0X3A,0X00,0X00,0X86,0X31,0X40,0X00,0XAE,0X73,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF3,0X9C,0XAE,0X73,0X10,0X84,0X4D,0X6B,0X10,0X7C,
0XEF,0X7B,0X41,0X08,0X24,0X21,0XB6,0XB5,0X92,0X94,0X00,0X00,0XAA,0X52,0XCE,0X73,
0XCF,0X73,0X6D,0X6B,0X30,0X84,0X10,0X7C,0X18,0XC6,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XDF,0XFF,0X44,0X21,0X71,0X8C,0X0B,0X5B,0XCB,0X5A,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0X4D,0X6B,0X89,0X4A,
0X59,0XC6,0XD7,0XBD,0X00,0X00,0X49,0X4A,0XA2,0X10,0X86,0X31,0X7D,0XEF,0X71,0X8C,
0X28,0X42,0X18,0XBE,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X28,0X42,0XC7,0X31,0X6D,0X6B,
0XA2,0X10,0X00,0X00,0X38,0XC6,0X34,0XA5,0X3C,0XE7,0X48,0X42,0X00,0X00,0X07,0X3A,
0XAE,0X73,0X00,0X00,0X18,0XC6,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X45,0X29,0X30,0X84,0X1C,0XE7,
0X10,0X7C,0X00,0X00,0XBA,0XD6,0XC3,0X18,0XB2,0X94,0X6D,0X6B,0X04,0X21,0XB6,0XB5,
0X7D,0XEF,0X24,0X21,0X34,0XA5,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7D,0XEF,0X65,0X29,0XA2,0X10,
0X0C,0X63,0X2C,0X63,0X44,0X21,0X38,0XC6,0X10,0X84,0XC3,0X10,0X30,0X84,0XC7,0X39,
0X61,0X08,0XAE,0X73,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XB6,0XB5,0X55,0XAD,0XB6,0XB5,0X34,0XA5,0X59,0XCE,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X14,0XA5,0X00,0X00,0X08,0X3A,0X5D,0XEF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X51,0X8C,0X0C,0X63,0X00,0X00,0X6D,0X6B,0XD3,0X9C,0XFF,0XFF,0X18,0XC6,
0X51,0X8C,0XF3,0X9C,0XF7,0XBD,0X41,0X08,0X6D,0X6B,0XD7,0XB5,0X71,0X8C,0XD3,0X94,
0X5D,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XDF,0XFF,0X04,0X21,0XFF,0XFF,0XFF,0XFF,0X1C,0XE7,0X03,0X19,
0XEB,0X5A,0X86,0X29,0XA2,0X10,0X2C,0X63,0X69,0X4A,0X20,0X00,0XEB,0X5A,0XA6,0X31,
0X2C,0X63,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X1C,0XE7,0X04,0X21,0XBE,0XF7,0XFF,0XFF,0X38,0XC6,0X81,0X08,
0XFF,0XFF,0X92,0X94,0X08,0X3A,0XFF,0XFF,0X1C,0XE7,0X82,0X08,0XFF,0XFF,0X34,0XA5,
0X24,0X21,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFB,0XDE,0X00,0X00,0XBE,0XF7,0XFF,0XFF,0X3C,0XE7,0X61,0X08,
0X04,0X19,0X41,0X00,0X00,0X00,0X04,0X19,0XA2,0X10,0X00,0X00,0X24,0X21,0X61,0X08,
0X4D,0X6B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X5D,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X5D,0XEF,
0X18,0XC6,0X79,0XCE,0X9A,0XD6,0X18,0XC6,0X38,0XC6,0XBA,0XD6,0X18,0XC6,0X79,0XCE,
0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};
