#include "stdafx.h"

#include "CommonFunc.h"



//global variables
u08 gu08Wbuf[SCSI_MAX_TRANS_LEN];
PHY_DRIVE_INFO	gPhyDriveInfo[MAX_SUPPORT_DEV_CNT];



BOOL EnumUsbDevSymbLinkName(const GUID* lpClassGuid, CStringArray &SymbLinkName)
{
	BOOL bResult = FALSE;
	int i = 0, nDevIdx = 0, nListCnt = 0;
	DWORD dwRequiredSize = 0, dwSize = 0;
	TCHAR    szDevSymbLinkName[MAX_PATH] = { 0 };
	HDEVINFO hDevInfo = NULL;
	SP_INTERFACE_DEVICE_DATA	     devInterfaceData;
	PSP_INTERFACE_DEVICE_DETAIL_DATA_W devInterfaceDetailData = NULL;
	SP_DEVINFO_DATA                  devInfoData;
	
	//get a list of devices with specific interface
	hDevInfo = SetupDiGetClassDevs(lpClassGuid,
		NULL,
		NULL,
		DIGCF_DEVICEINTERFACE |
		DIGCF_PRESENT);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	devInterfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
	nListCnt = (int)SymbLinkName.GetSize();
	//loop of enumerating dev interfaces
	for (nDevIdx = 0, i = nListCnt;
		SetupDiEnumDeviceInterfaces(hDevInfo, NULL, lpClassGuid, nDevIdx, &devInterfaceData);
		nDevIdx++) {
		if (devInterfaceData.Flags != SPINT_ACTIVE) {
			continue;
		}
		
		//get size of symbolic link name
		SetupDiGetDeviceInterfaceDetail(hDevInfo, &devInterfaceData, NULL, 0, &dwRequiredSize, NULL);
		devInterfaceDetailData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(dwRequiredSize + 2);
		if (devInterfaceDetailData == NULL) {
			continue;
		}

		//get symbolic link name
		devInterfaceDetailData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
		devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
		if (!SetupDiGetDeviceInterfaceDetail(hDevInfo,
			&devInterfaceData,
			devInterfaceDetailData,
			dwRequiredSize + 2,
			&dwSize,
			&devInfoData)) {
			dwSize = GetLastError();
			free(devInterfaceDetailData);
			devInterfaceDetailData = NULL;
			continue;
		}

		ZeroMemory(szDevSymbLinkName, sizeof(szDevSymbLinkName));
		_tcscpy_s(szDevSymbLinkName, _countof(szDevSymbLinkName), devInterfaceDetailData->DevicePath);
		free(devInterfaceDetailData);
		devInterfaceDetailData = NULL;

		if (_tcsnicmp(szDevSymbLinkName, _T("\\\\?\\usbstor#disk&ven_smi&prod_sm333"), 16) == 0)
		//if (_tcsnicmp(szDevSymbLinkName, _T("\\\\?\\usb#vid_090c"), 16) == 0) //sm333 dev path
		{
			SymbLinkName.Add(CString(szDevSymbLinkName));
			i++;
			bResult = TRUE;
		}
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);
	return bResult;
}


int SCSI_QueryProperty(HANDLE hDev, char *cDrivePath, PSTORAGE_DEVICE_DESCRIPTOR pDevDescriptor)
{
	int iRet = FUN_SUC;
	DWORD nBytesReturn = 0;
	STORAGE_PROPERTY_QUERY DevPropertyQuery;
	ZeroMemory(&DevPropertyQuery, sizeof(DevPropertyQuery));
	DevPropertyQuery.PropertyId = StorageDeviceProperty;
	DevPropertyQuery.QueryType = PropertyStandardQuery;

#if 0
	char cDevPath[] = "\\\\.\\D:";
	HANDLE hDevTmp = CreateFileA(cDevPath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hDevTmp == INVALID_HANDLE_VALUE) {
		//TBC
	}

	// Query using IOCTL_STORAGE_QUERY_PROPERTY
	iRet = DeviceIoControl(hDevTmp,                     // device handle
		IOCTL_STORAGE_QUERY_PROPERTY,
		&DevPropertyQuery,
		sizeof(DevPropertyQuery),
		pDevDescriptor,
		sizeof(STORAGE_DEVICE_DESCRIPTOR),
		&nBytesReturn,
		NULL);
	iRet = iRet ? FUN_SUC : FUN_ERR_BASE;
#else

	// Query using IOCTL_STORAGE_QUERY_PROPERTY
	iRet = DeviceIoControl(hDev,                     // device handle
		IOCTL_STORAGE_QUERY_PROPERTY, // return the properties of a storage device or adapter, not interface hahh~
		&DevPropertyQuery,
		sizeof(DevPropertyQuery),
		pDevDescriptor,
		sizeof(STORAGE_DEVICE_DESCRIPTOR),
		&nBytesReturn,
		NULL);
	iRet = iRet ? FUN_SUC : FUN_ERR_BASE;
#endif

	return iRet;
}


int SCSI_Read10_Sm333(HANDLE hDev, char *cDrivePath, BYTE *pSm333Arg, BYTE* pu08Buf, u16 u16ReadSectCnt)
{
	int iRet = FUN_SUC, i = 0;
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER Sptdwb;
	ULONG nLen = 0, nBytesRet = 0;

	ZeroMemory(&Sptdwb, sizeof(Sptdwb));
	Sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	Sptdwb.sptd.PathId = 0;
	Sptdwb.sptd.TargetId = 1;
	Sptdwb.sptd.Lun = 0;
	Sptdwb.sptd.CdbLength = 16; 
	Sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
	Sptdwb.sptd.SenseInfoLength = 24;
	Sptdwb.sptd.DataTransferLength = BYTES_PER_SECT *u16ReadSectCnt;
	Sptdwb.sptd.TimeOutValue = 10;
	Sptdwb.sptd.DataBuffer = pu08Buf;
	Sptdwb.sptd.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);

	Sptdwb.sptd.Cdb[0] = pSm333Arg[0];
	Sptdwb.sptd.Cdb[1] = pSm333Arg[1];
	Sptdwb.sptd.Cdb[2] = pSm333Arg[2];
	Sptdwb.sptd.Cdb[3] = pSm333Arg[3];
	Sptdwb.sptd.Cdb[4] = pSm333Arg[4];
	Sptdwb.sptd.Cdb[5] = pSm333Arg[5];
	Sptdwb.sptd.Cdb[6] = pSm333Arg[6];
	Sptdwb.sptd.Cdb[7] = pSm333Arg[7];
	Sptdwb.sptd.Cdb[8] = pSm333Arg[8];
	Sptdwb.sptd.Cdb[9] = pSm333Arg[9];
	Sptdwb.sptd.Cdb[10] = pSm333Arg[10];
	Sptdwb.sptd.Cdb[11] = pSm333Arg[11];
	Sptdwb.sptd.Cdb[12] = pSm333Arg[12];
	Sptdwb.sptd.Cdb[13] = pSm333Arg[13];
	Sptdwb.sptd.Cdb[14] = pSm333Arg[14];
	Sptdwb.sptd.Cdb[15] = pSm333Arg[15];

	nLen = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);

	for (i = 0; i < FUN_RETRY_CNT; i++) {
		iRet = DeviceIoControl(hDev,
			IOCTL_SCSI_PASS_THROUGH_DIRECT,
			&Sptdwb,
			nLen,
			&Sptdwb,
			nLen,
			&nBytesRet,
			FALSE);
		if (iRet) {
			break;
		}
	}
	if (!iRet) {
		int iErr = GetLastError();

	}
	iRet = iRet ? FUN_SUC : FUN_ERR_BASE; //modify return value, zero means success


	return iRet;
}


int SCSI_Read10(HANDLE hDev, char *cDrivePath, u32 u32PosSec, BYTE* pu08Buf, u16 u16ReadSectCnt)
{
	int iRet = FUN_SUC, i = 0;
	ULONG nLen = 0 , nBytesRet = 0;
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER Sptdwb;

	ZeroMemory(&Sptdwb, sizeof(Sptdwb));
	Sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	Sptdwb.sptd.PathId = 0;
	Sptdwb.sptd.TargetId = 1;
	Sptdwb.sptd.Lun = 0;
	Sptdwb.sptd.CdbLength = 10;
	Sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
	Sptdwb.sptd.SenseInfoLength = 24;
	Sptdwb.sptd.DataTransferLength = BYTES_PER_SECT *u16ReadSectCnt;
	Sptdwb.sptd.TimeOutValue = 10;
	Sptdwb.sptd.DataBuffer = pu08Buf;
	Sptdwb.sptd.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);

	Sptdwb.sptd.Cdb[0] = SCSIOP_READ;
	Sptdwb.sptd.Cdb[2] = (byte)(u32PosSec >> 24);
	Sptdwb.sptd.Cdb[3] = (byte)(u32PosSec >> 16);
	Sptdwb.sptd.Cdb[4] = (byte)(u32PosSec >> 8);
	Sptdwb.sptd.Cdb[5] = (byte)u32PosSec;
	Sptdwb.sptd.Cdb[7] = (byte)(u16ReadSectCnt >> 8);
	Sptdwb.sptd.Cdb[8] = (byte)u16ReadSectCnt;


	nLen = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);

	for (i = 0; i < FUN_RETRY_CNT; i++) { //if fail, retry 3 cycles
		iRet = DeviceIoControl(hDev,
			IOCTL_SCSI_PASS_THROUGH_DIRECT,
			&Sptdwb,
			nLen,
			&Sptdwb,
			nLen,
			&nBytesRet,
			FALSE);
		if (iRet) {
			break;
		}
	}
	if (!iRet) {
		int iErr = GetLastError();

	}
	iRet = iRet ? FUN_SUC : FUN_ERR_BASE; //modify return value, zero means success

	return iRet;
}


int SCSI_Write10_Sm333(HANDLE hDev, char *cDrivePath, BYTE *pSm333Arg, BYTE* pu08Buf, u16 u16WriteSectCnt)
{
	int iRet = FUN_SUC, i = 0;
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER Sptdwb;
	ULONG nLen = 0, nBytesRet = 0;

	ZeroMemory(&Sptdwb, sizeof(Sptdwb));
	Sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	Sptdwb.sptd.PathId = 0;
	Sptdwb.sptd.TargetId = 1;
	Sptdwb.sptd.Lun = 0;
	Sptdwb.sptd.CdbLength = 16;
	Sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
	Sptdwb.sptd.SenseInfoLength = 24;
	Sptdwb.sptd.DataTransferLength = BYTES_PER_SECT *u16WriteSectCnt;
	Sptdwb.sptd.TimeOutValue = 100;
	Sptdwb.sptd.DataBuffer = pu08Buf;
	Sptdwb.sptd.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);

	Sptdwb.sptd.Cdb[0] = pSm333Arg[0];
	Sptdwb.sptd.Cdb[1] = pSm333Arg[1];
	Sptdwb.sptd.Cdb[2] = pSm333Arg[2];
	Sptdwb.sptd.Cdb[3] = pSm333Arg[3];
	Sptdwb.sptd.Cdb[4] = pSm333Arg[4];
	Sptdwb.sptd.Cdb[5] = pSm333Arg[5];
	Sptdwb.sptd.Cdb[6] = pSm333Arg[6];
	Sptdwb.sptd.Cdb[7] = pSm333Arg[7];
	Sptdwb.sptd.Cdb[8] = pSm333Arg[8];
	Sptdwb.sptd.Cdb[9] = pSm333Arg[9];
	Sptdwb.sptd.Cdb[10] = pSm333Arg[10];
	Sptdwb.sptd.Cdb[11] = pSm333Arg[11];
	Sptdwb.sptd.Cdb[12] = pSm333Arg[12];
	Sptdwb.sptd.Cdb[13] = pSm333Arg[13];
	Sptdwb.sptd.Cdb[14] = pSm333Arg[14];
	Sptdwb.sptd.Cdb[15] = pSm333Arg[15];

	nLen = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);

	for (i = 0; i < FUN_RETRY_CNT; i++) {
		iRet = DeviceIoControl(hDev,
			IOCTL_SCSI_PASS_THROUGH_DIRECT,
			&Sptdwb,
			nLen,
			&Sptdwb,
			nLen,
			&nBytesRet,
			FALSE);
		if (iRet) {
			break;
		}
	}
	if (!iRet) {
		int iErr = GetLastError();

	}
	iRet = iRet ? FUN_SUC : FUN_ERR_BASE; //modify return value, zero means success


	return iRet;
}


int SCSI_Write10(HANDLE hDev, char *cDrivePath, u32 u32PosSec, BYTE* pu08Buf, u16 u16WriteSectCnt)
{
	int iRet = FUN_SUC, i = 0;
	ULONG nLen = 0, nBytesRet = 0;
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER Sptdwb;

	ZeroMemory(&Sptdwb, sizeof(Sptdwb));
	Sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	Sptdwb.sptd.PathId = 0;
	Sptdwb.sptd.TargetId = 1;
	Sptdwb.sptd.Lun = 0;
	Sptdwb.sptd.CdbLength = 10;
	Sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_OUT;
	Sptdwb.sptd.SenseInfoLength = 24;
	Sptdwb.sptd.DataTransferLength = BYTES_PER_SECT *u16WriteSectCnt;
	Sptdwb.sptd.TimeOutValue = 100;
	Sptdwb.sptd.DataBuffer = pu08Buf;
	Sptdwb.sptd.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);

	Sptdwb.sptd.Cdb[0] = SCSIOP_WRITE;
	Sptdwb.sptd.Cdb[2] = (byte)(u32PosSec >> 24);
	Sptdwb.sptd.Cdb[3] = (byte)(u32PosSec >> 16);
	Sptdwb.sptd.Cdb[4] = (byte)(u32PosSec >> 8);
	Sptdwb.sptd.Cdb[5] = (byte)u32PosSec;
	Sptdwb.sptd.Cdb[7] = (byte)(u16WriteSectCnt >> 8);
	Sptdwb.sptd.Cdb[8] = (byte)u16WriteSectCnt;


	nLen = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);

	for (i = 0; i < FUN_RETRY_CNT; i++) { //if fail, retry 3 cycles
		iRet = DeviceIoControl(hDev,
			IOCTL_SCSI_PASS_THROUGH_DIRECT,
			&Sptdwb,
			nLen,
			&Sptdwb,
			nLen,
			&nBytesRet,
			FALSE);
		if (iRet) {
			break;
		}
	}
	if (!iRet) {
		int iErr = GetLastError();

	}
	iRet = iRet ? FUN_SUC : FUN_ERR_BASE; //modify return value, zero means success

	return iRet;
}


int SCSI_Inquiry(HANDLE hDev, char *cDrivePath, BYTE* pu08Buf)
{
	int iRet = FUN_SUC, i = 0;
	ULONG nLen = 0, nBytesRet = 0;
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER Sptdwb;

	ZeroMemory(&Sptdwb, sizeof(Sptdwb));
	Sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	Sptdwb.sptd.PathId = 0;
	Sptdwb.sptd.TargetId = 1;
	Sptdwb.sptd.Lun = 0;
	Sptdwb.sptd.CdbLength = 10;
	Sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
	Sptdwb.sptd.SenseInfoLength = 24;
	Sptdwb.sptd.DataTransferLength = 36;
	Sptdwb.sptd.TimeOutValue = 10;
	Sptdwb.sptd.DataBuffer = pu08Buf;
	Sptdwb.sptd.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);

	Sptdwb.sptd.Cdb[0] = SCSIOP_INQUIRY;
	Sptdwb.sptd.Cdb[1] = 0;
	Sptdwb.sptd.Cdb[2] = 0;
	Sptdwb.sptd.Cdb[3] = 0;
	Sptdwb.sptd.Cdb[4] = 0x24;
	Sptdwb.sptd.Cdb[5] = 0;
	

	nLen = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);

	iRet = DeviceIoControl(hDev,
		IOCTL_SCSI_PASS_THROUGH_DIRECT,
		&Sptdwb,
		nLen,
		&Sptdwb,
		nLen,
		&nBytesRet,
		FALSE);
	if (!iRet) {
		int iErr = GetLastError();

	}
	iRet = iRet ? FUN_SUC : FUN_ERR_BASE; //modify return value, zero means success

	return iRet;
}


int SCSI_ReadCapacity(HANDLE hDev, char *cDrivePath, BYTE *pu08Buf)
{
	int iRet = FUN_SUC, i = 0;
	ULONG nLen = 0, nBytesRet = 0;
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER Sptdwb;

	ZeroMemory(&Sptdwb, sizeof(Sptdwb));
	Sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	Sptdwb.sptd.PathId = 0;
	Sptdwb.sptd.TargetId = 1;
	Sptdwb.sptd.Lun = 0;
	Sptdwb.sptd.CdbLength = 10;
	Sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
	Sptdwb.sptd.SenseInfoLength = 24;
	Sptdwb.sptd.DataTransferLength = 8;
	Sptdwb.sptd.TimeOutValue = 10;
	Sptdwb.sptd.DataBuffer = pu08Buf;
	Sptdwb.sptd.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);

	Sptdwb.sptd.Cdb[0] = SCSIOP_READ_CAPACITY;
	Sptdwb.sptd.Cdb[1] = 0;
	Sptdwb.sptd.Cdb[2] = 0;
	Sptdwb.sptd.Cdb[3] = 0;
	Sptdwb.sptd.Cdb[4] = 0;
	Sptdwb.sptd.Cdb[5] = 0;


	nLen = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);

	iRet = DeviceIoControl(hDev,
		IOCTL_SCSI_PASS_THROUGH_DIRECT,
		&Sptdwb,
		nLen,
		&Sptdwb,
		nLen,
		&nBytesRet,
		FALSE);
	if (!iRet) {
		int iErr = GetLastError();

	}
	iRet = iRet ? FUN_SUC : FUN_ERR_BASE; //modify return value, zero means success

	return iRet;
}


int eMMC_CheckSm333(HANDLE hDev, char *cDrivePath, BYTE* pu08Buf)
{
	int iRet = 0;
	u08 u08SectCnt = 1;
	u08 u08Arg[16] = { 0 };

	memset(u08Arg, 0x0, 16);
	u08Arg[0] = 0xF0;
	u08Arg[1] = 0xF5;
	u08Arg[2] = 0x00;
	u08Arg[3] = 0x00;
	u08Arg[4] = 0x00;
	u08Arg[5] = 0x00;
	u08Arg[6] = 0x00;
	u08Arg[7] = 0;
	u08Arg[8] = 0x00;
	u08Arg[9] = 0;
	u08Arg[10] = 0;
	u08Arg[11] = u08SectCnt;
	u08Arg[12] = 0;
	u08Arg[13] = 0;
	u08Arg[14] = 0;
	u08Arg[15] = 0;

	iRet = SCSI_Read10_Sm333(hDev, cDrivePath, &u08Arg[0], pu08Buf, u08SectCnt);

	return iRet;
}


int eMMC_CheckReady(HANDLE hDev, char *cDrivePath, BYTE *pu08Buf, u16 u16ReadSectCnt)
{
	int iRet = FUN_SUC;
	u08 u08Arg[16] = { 0 };

	memset(u08Arg, 0x0, 16);
	u08Arg[0] = 0xF0;
	u08Arg[1] = 0xF3;
	u08Arg[2] = 0x00;
	u08Arg[3] = 0x00;
	u08Arg[4] = 0x00;
	u08Arg[5] = 0x00;
	u08Arg[6] = 0x00;
	u08Arg[7] = 0;
	u08Arg[8] = 0x00;
	u08Arg[9] = 0;
	u08Arg[10] = 0;
	u08Arg[11] = (u08)(u16ReadSectCnt & 0xFF);
	u08Arg[12] = 0;
	u08Arg[13] = 0;
	u08Arg[14] = 0;
	u08Arg[15] = 0;

	iRet = SCSI_Read10_Sm333(hDev, cDrivePath, &u08Arg[0], pu08Buf, u16ReadSectCnt);

	return iRet;
}


int eMMC_PollingReady(HANDLE hDev, char *cDrivePath, u16 u16Delay, u32 u32Timeout)
{
	int iRet = FUN_SUC;
	u08 u08TmpBuf[512] = { 0 };
	u32 u32Cnt = 0;
	memset(u08TmpBuf, 0x0, 512);

	u32Cnt = 0;
	if (u32Timeout != 0)
	{
		do
		{
			Sleep(u16Delay);
			u08TmpBuf[8] = u08TmpBuf[7] = 0;
			iRet = eMMC_CheckReady(hDev, cDrivePath, u08TmpBuf, 1);
			if (iRet != FUN_SUC) {
				break;
			}

			if (u32Cnt > u32Timeout)
			{
				iRet = FUN_ERR_BASE;
				break;
			}

			u32Cnt++;
		} while ((u08TmpBuf[7] != 'O') || (u08TmpBuf[8] != 'K'));
	}

	//Sleep(u16Delay);
	return iRet;
}


int eMMC_Initial(HANDLE hDev, char *cDrivePath, BYTE *pu08Buf, BYTE u08Opt, u16 u16ReadSectCnt)
{
	//int iRet = FUN_SUC;
	u08 u08Arg[16] = { 0 };
	memset(u08Arg, 0x0, 16);
	u08Arg[0] = 0xF0;
	u08Arg[1] = 0xF1;
	u08Arg[2] = 0x00;
	u08Arg[3] = u08Opt;
	u08Arg[4] = 0x00;
	u08Arg[5] = 0x00;
	u08Arg[6] = 0x00;
	u08Arg[7] = 0;
	u08Arg[8] = 0x00;
	u08Arg[9] = 0;
	u08Arg[10] = 0;
	u08Arg[11] = (u08)(u16ReadSectCnt & 0xFF);
	u08Arg[12] = 0;
	u08Arg[13] = 0;
	u08Arg[14] = 0;
	u08Arg[15] = 0;

	//if (SCSI_Read10_Sm333(hDev, cDrivePath, &u08Arg[0], pu08Buf, u16ReadSectCnt)) {
	//	return FUN_ERR_BASE;
	//}

	//if (eMMC_PollingReady(hDev, cDrivePath, 10, 40)) {
	//	return FUN_ERR_BASE;
	//}

	return SCSI_Read10_Sm333(hDev, cDrivePath, &u08Arg[0], pu08Buf, u16ReadSectCnt);
}