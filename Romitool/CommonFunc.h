#pragma once

#include "Typedef.h"
#include "resource.h"
#include "winioctl.h"
#include "ntddscsi.h"
//extern "C" {
#include "spti.h"
//}

#include <windows.h>
#include <windef.h>

#include "Setupapi.h"
#include "winioctl.h"
#include "cfgmgr32.h"
#include <initguid.h>

#define ROMITELLI_EDIT	1

#if ROMITELLI_EDIT

#define FUN_SUC		0
#define FUN_ERR_BASE	1
#define FUN_RETRY_CNT	3

#define MAX_SUPPORT_DEV_CNT	32
#define BYTES_PER_SECT		512
#define SCSI_MAX_TRANS_LEN	0xFFFF

typedef enum: unsigned char{
	MP_FACTORY = 0,
	MP_COMMON
}MP_MODE;


#endif

typedef struct _PHY_DRIVE_INFO {
	u08 u08Sm333Exist;
	u08 u08PortMainId;
	u08 u08PortSubId;
	u32 u32Capacity;
	HANDLE hDisk;
	char cDrivePath[MAX_PATH];
}PHY_DRIVE_INFO, *PPHY_DRIVE_INFO;

#if 0
/*============ usb mass storage(UFI command specification) ===========*/
#define SPT_CDB_LENGTH 32 
#define SPT_SENSE_LENGTH 32 
#define SPTWB_DATA_LENGTH 512 

typedef struct _SCSI_DEV_INFO {
	SCSI_PASS_THROUGH	Spt;
	BYTE Sense[18];
	BYTE Data[36];
}SCSI_DEV_INFO, *PSCSI_DEV_INFO;


typedef struct _SCSI_PASS_THROUGH_WITH_BUFFERS{
	SCSI_PASS_THROUGH	Spt;
	ULONG Filler;
	UCHAR ucSenseBuf[SPT_SENSE_LENGTH];
	UCHAR ucDataBuf[SPTWB_DATA_LENGTH];
}SCSI_PASS_THROUGH_WITH_BUFFERS, *PSCSI_PASS_THROUGH_WITH_BUFFERS;

/*============ usb mass storage(UFI command specification) ended ===========*/
#endif

//global variables
extern u08 gu08Wbuf[SCSI_MAX_TRANS_LEN];
extern PHY_DRIVE_INFO	gPhyDriveInfo[MAX_SUPPORT_DEV_CNT];

//enum usb device info 
extern BOOL EnumUsbDevSymbLinkName(const GUID* lpClassGuid, CStringArray &SymbLinkName);

//SCSI basic command
extern int SCSI_QueryProperty(HANDLE hDev, char *cDrivePath, PSTORAGE_DEVICE_DESCRIPTOR pDevDescriptor);
extern int SCSI_Read10_Sm333(HANDLE hDev, char *cDrivePath, BYTE *pSm333Arg, BYTE* pu08Buf, u16 u16ReadSectCnt);
extern int SCSI_Read10(HANDLE hDev, char *cDrivePath, u32 u32PosSec, BYTE* pu08Buf, u16 u16ReadSectCnt);
extern int SCSI_Write10_Sm333(HANDLE hDev, char *cDrivePath, BYTE *pSm333Arg, BYTE* pu08Buf, u16 u16WriteSectCnt);
extern int SCSI_Write10(HANDLE hDev, char *cDrivePath, u32 u32PosSec, BYTE* pu08Buf, u16 u16WriteSectCnt);
extern int SCSI_Inquiry(HANDLE hDev, char *cDrivePath, BYTE* pu08Buf);
extern int SCSI_ReadCapacity(HANDLE hDev, char *cDrivePath, BYTE *pu08Buf);

//emmc basic function
extern int eMMC_CheckSm333(HANDLE hDev, char *cDrivePath, BYTE* pu08Buf);
extern int eMMC_CheckReady(HANDLE hDev, char *cDrivePath, BYTE *pu08Buf, u16 u16ReadSectCnt);
extern int eMMC_PollingReady(HANDLE hDev, char *cDrivePath, u16 u16Delay, u32 u32Timeout);
extern int eMMC_Initial(HANDLE hDev, char *cDrivePath, BYTE *pu08Buf, BYTE u08Opt, u16 u16ReadSectCnt);