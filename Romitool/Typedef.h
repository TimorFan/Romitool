//#pragma once
#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

/*------------------ Phrase definition -------------------*/
// Type definition
#define  BYTE     unsigned char            //size:  8 bits
#define  WORD     unsigned short           //Size: 16 bits
#define  LWORD    unsigned long            //Size: 32 bits
#define  SBYTE    signed char              //size:  8 bits
#define  SWORD    signed short             //Size: 16 bits
#define  SLWORD   signed long              //Size: 32 bits
#define  VBYTE    volatile unsigned char   //size:  8 bits
#define  VWORD    volatile unsigned short  //Size: 16 bits
#define  VLWORD   volatile unsigned long   //Size: 32 bits
#define  VSBYTE   volatile signed char     //size:  8 bits
#define  VSWORD   volatile signed short    //Size: 16 bits
#define  VSLWORD  volatile signed long     //Size: 32 bits

typedef BYTE	u08;
typedef WORD	u16;
typedef LWORD	u32;
typedef SBYTE	s08;
typedef SWORD	s16;
typedef SLWORD	s32;
typedef VBYTE	vu08;
typedef VWORD	vu16;
typedef VLWORD	vu32;
typedef VSBYTE	vs08;
typedef VSWORD	vs16;
typedef VSLWORD	vs32;


//set nth bit per byte
#define SetB0	0x01
#define SetB1	0x02
#define SetB2	0x04
#define SetB3	0x08
#define SetB4	0x10
#define SetB5	0x20
#define SetB6	0x40
#define SetB7	0x80

//clear nth bit per byte
#define ClrB0	0xFE
#define ClrB1	0xFD
#define ClrB2	0xFB
#define ClrB3	0xF7
#define ClrB4	0xEF
#define ClrB5	0xDF
#define ClrB6	0xBF
#define ClrB7	0x7F

// Set Nth bit in a word
#define  WSetB15            0x8000
#define  WSetB14            0x4000
#define  WSetB13            0x2000
#define  WSetB12            0x1000
#define  WSetB11            0x0800
#define  WSetB10            0x0400
#define  WSetB9             0x0200
#define  WSetB8             0x0100
#define  WSetB7             0x0080
#define  WSetB6             0x0040
#define  WSetB5             0x0020
#define  WSetB4             0x0010
#define  WSetB3             0x0008
#define  WSetB2             0x0004
#define  WSetB1             0x0002
#define  WSetB0             0x0001

// Clear Nth bit in a word
#define  WClrB15            0x7FFF
#define  WClrB14            0xBFFF
#define  WClrB13            0xDFFF
#define  WClrB12            0xEFFF
#define  WClrB11            0xF7FF
#define  WClrB10            0xFBFF
#define  WClrB9             0xFDFF
#define  WClrB8             0xFEFF
#define  WClrB7             0xFF7F
#define  WClrB6             0xFFBF
#define  WClrB5             0xFFDF
#define  WClrB4             0xFFEF
#define  WClrB3             0xFFF7
#define  WClrB2             0xFFFB
#define  WClrB1             0xFFFD
#define  WClrB0             0xFFFE

// Set Nth bit in a long word
#define  LWSetB31           0x80000000
#define  LWSetB30           0x40000000
#define  LWSetB29           0x20000000
#define  LWSetB28           0x10000000
#define  LWSetB27           0x08000000
#define  LWSetB26           0x04000000
#define  LWSetB25           0x02000000
#define  LWSetB24           0x01000000
#define  LWSetB23           0x00800000
#define  LWSetB22           0x00400000
#define  LWSetB21           0x00200000
#define  LWSetB20           0x00100000
#define  LWSetB19           0x00080000
#define  LWSetB18           0x00040000
#define  LWSetB17           0x00020000
#define  LWSetB16           0x00010000
#define  LWSetB15           0x00008000
#define  LWSetB14           0x00004000
#define  LWSetB13           0x00002000
#define  LWSetB12           0x00001000
#define  LWSetB11           0x00000800
#define  LWSetB10           0x00000400
#define  LWSetB9            0x00000200
#define  LWSetB8            0x00000100
#define  LWSetB7            0x00000080
#define  LWSetB6            0x00000040
#define  LWSetB5            0x00000020
#define  LWSetB4            0x00000010
#define  LWSetB3            0x00000008
#define  LWSetB2            0x00000004
#define  LWSetB1            0x00000002
#define  LWSetB0            0x00000001

// Clear Nth bit in a long word
#define  LWClrB31           0x7FFFFFFF
#define  LWClrB30           0xBFFFFFFF
#define  LWClrB29           0xDFFFFFFF
#define  LWClrB28           0xEFFFFFFF
#define  LWClrB27           0xF7FFFFFF
#define  LWClrB26           0xFBFFFFFF
#define  LWClrB25           0xFDFFFFFF
#define  LWClrB24           0xFEFFFFFF
#define  LWClrB23           0xFF7FFFFF
#define  LWClrB22           0xFFBFFFFF
#define  LWClrB21           0xFFDFFFFF
#define  LWClrB20           0xFFEFFFFF
#define  LWClrB19           0xFFF7FFFF
#define  LWClrB18           0xFFFBFFFF
#define  LWClrB17           0xFFFDFFFF
#define  LWClrB16           0xFFFEFFFF
#define  LWClrB15           0xFFFF7FFF
#define  LWClrB14           0xFFFFBFFF
#define  LWClrB13           0xFFFFDFFF
#define  LWClrB12           0xFFFFEFFF
#define  LWClrB11           0xFFFFF7FF
#define  LWClrB10           0xFFFFFBFF
#define  LWClrB9            0xFFFFFDFF
#define  LWClrB8            0xFFFFFEFF
#define  LWClrB7            0xFFFFFF7F
#define  LWClrB6            0xFFFFFFBF
#define  LWClrB5            0xFFFFFFDF
#define  LWClrB4            0xFFFFFFEF
#define  LWClrB3            0xFFFFFFF7
#define  LWClrB2            0xFFFFFFFB
#define  LWClrB1            0xFFFFFFFD
#define  LWClrB0            0xFFFFFFFE

//structure 
#pragma pack(push)

#pragma pack(1)
typedef struct _BITS_08
{
	BYTE BIT00 : 1;
	BYTE BIT01 : 1;
	BYTE BIT02 : 1;
	BYTE BIT03 : 1;
	BYTE BIT04 : 1;
	BYTE BIT05 : 1;
	BYTE BIT06 : 1;
	BYTE BIT07 : 1;
} BITS_08;

typedef struct _BITS_32
{
	BYTE BIT00 : 1;
	BYTE BIT01 : 1;
	BYTE BIT02 : 1;
	BYTE BIT03 : 1;
	BYTE BIT04 : 1;
	BYTE BIT05 : 1;
	BYTE BIT06 : 1;
	BYTE BIT07 : 1;
	BYTE BIT08 : 1;
	BYTE BIT09 : 1;
	BYTE BIT10 : 1;
	BYTE BIT11 : 1;
	BYTE BIT12 : 1;
	BYTE BIT13 : 1;
	BYTE BIT14 : 1;
	BYTE BIT15 : 1;
	BYTE BIT16 : 1;
	BYTE BIT17 : 1;
	BYTE BIT18 : 1;
	BYTE BIT19 : 1;
	BYTE BIT20 : 1;
	BYTE BIT21 : 1;
	BYTE BIT22 : 1;
	BYTE BIT23 : 1;
	BYTE BIT24 : 1;
	BYTE BIT25 : 1;
	BYTE BIT26 : 1;
	BYTE BIT27 : 1;
	BYTE BIT28 : 1;
	BYTE BIT29 : 1;
	BYTE BIT30 : 1;
	BYTE BIT31 : 1;
} BITS_32;
#pragma pack(pop)

#endif