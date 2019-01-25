// MpTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Romitool.h"
#include "MpTestDlg.h"
#include "afxdialogex.h"


DEFINE_GUID(GUID_DEVINTERFACE_DISK, 0x53f56307L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_CDROM, 0x53f56308L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE, 0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED);

// CMpTestDlg 对话框

IMPLEMENT_DYNAMIC(CMpTestDlg, CDialogEx)

CMpTestDlg::CMpTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MPTEST, pParent)
{

}

CMpTestDlg::~CMpTestDlg()
{
}

void CMpTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT2_TEST_STATUS, m_CRichEditTestStatus);
	DDX_Control(pDX, IDC_RICHEDIT2_TEST_MESSAGE, m_CRichEditTestMsg);
}


BEGIN_MESSAGE_MAP(CMpTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MPSCAN, &CMpTestDlg::OnBnClickedButtonMpScan)
END_MESSAGE_MAP()


// CMpTestDlg 消息处理程序


BOOL CMpTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//init rich edit control
	m_CRichEditTestMsg.LimitText(UINT_MAX); 
	m_CRichEditTestMsg.SetWindowTextW(_T(""));
	m_CRichEditTestMsg.SetSel(0, -1); // select all the text in this

	m_CRichEditTestMsg.LimitText(UINT_MAX);
	m_CRichEditTestStatus.SetWindowTextW(_T(""));
	m_CRichEditTestStatus.SetSel(0, -1); // select all the text in this

	//scan usb device
	OnBnClickedButtonMpScan();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CMpTestDlg::OnBnClickedButtonMpScan()
{
	u32 u32PhyDriveCapacity = 0xFFFFFFFF;
	int i = 0, iRet = FUN_SUC;
	CString strTmp, strMsg;
	u08 u08Buf[BYTES_PER_SECT] = { 0 };
	HANDLE hDev = INVALID_HANDLE_VALUE;
	STORAGE_DEVICE_DESCRIPTOR DevDescriptor;

	GetDevPath(); //get usb device path

	//query device property and check sm333 exist or not
	for (i = 0; i < MAX_SUPPORT_DEV_CNT; i++) {
		//step.1 create device handle 
		hDev = CreateFileA(&gPhyDriveInfo[i].cDrivePath[0],
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (hDev == INVALID_HANDLE_VALUE) { //err
			continue;
		}
		else {
			gPhyDriveInfo[i].hDisk = hDev;
		}

		//step.2 query usb property is removable or not
		ZeroMemory(&DevDescriptor, sizeof(DevDescriptor));
		iRet = SCSI_QueryProperty(hDev, &gPhyDriveInfo[i].cDrivePath[0], &DevDescriptor);
		if (iRet != FUN_SUC) { //err 
			continue;
		}
		else if((DevDescriptor.BusType != BusTypeUsb) || (DevDescriptor.RemovableMedia != TRUE)){
			continue;
		}

		//step.3 check main id/ sub id/ sm333 exist or not
		ZeroMemory(u08Buf, sizeof(u08Buf));
		iRet = eMMC_CheckSm333(hDev, &gPhyDriveInfo[i].cDrivePath[0], u08Buf);
		if (iRet != FUN_SUC) {
			strTmp.Format(_T("%02d, CheckSm333 Fail_%d !!! \r\n"), i, GetLastError());
			m_CRichEditTestMsg.ReplaceSel(strTmp, 0);
			continue;
		}
		else if ((u08Buf[7] != 'O') || (u08Buf[8] != 'K')) {
			continue;
		}
		else {
			gPhyDriveInfo[i].u08PortMainId = ((u08Buf[16] >> 4) & 0x0F);
			gPhyDriveInfo[i].u08PortSubId = (u08Buf[16] & 0x0F);
		}

		//step.4 inquiry sm333 descriptor
		ZeroMemory(&u08Buf[0], sizeof(u08Buf));
		iRet = SCSI_Inquiry(hDev, &gPhyDriveInfo[i].cDrivePath[0], u08Buf);
		if ((iRet == FUN_SUC) &&
			(u08Buf[16] == 'S') &&
			(u08Buf[17] == 'M') &&
			(u08Buf[18] == '3') &&
			(u08Buf[19] == '3') &&
			(u08Buf[20] == '3')) {
			gPhyDriveInfo[i].u08Sm333Exist = TRUE;
		}

		//step.5 read capacity after init sm333
		ZeroMemory(&u08Buf[0], sizeof(u08Buf));
		iRet = eMMC_Initial(hDev, &gPhyDriveInfo[i].cDrivePath[0], u08Buf, 0x0, 1);
		if ((iRet != FUN_SUC) ||
			(u08Buf[0] != 'O') ||
			(u08Buf[1] != 'K')) { //detail err code(TBC)
			this->MessageBox(_T("eMMC Init Fail :("), _T("Read Capacity"), MB_ICONWARNING | MB_OK);
			continue;
		}

		ZeroMemory(&u08Buf[0], sizeof(u08Buf));
		iRet = SCSI_ReadCapacity(hDev, &gPhyDriveInfo[i].cDrivePath[0], u08Buf);
		u32PhyDriveCapacity = (u08Buf[0] << 24) + (u08Buf[1] << 16) + (u08Buf[2] << 8) + u08Buf[3]; //sector cnt
		if ((iRet == FUN_SUC) && (u32PhyDriveCapacity != 0)){
			gPhyDriveInfo[i].u32Capacity += 1;
			gPhyDriveInfo[i].u32Capacity = u32PhyDriveCapacity;
		}


	} //~~ for (i = 0; i < MAX_SUPPORT_DEV_CNT; i++)
	
	//display all device drive info
	USES_CONVERSION;
	LPWSTR lpwStr = NULL;
	strMsg.Format(_T(""));
	for (i = 0; i < MAX_SUPPORT_DEV_CNT; i++) {
		if (gPhyDriveInfo[i].u08Sm333Exist) {
			lpwStr = A2T(gPhyDriveInfo[i].cDrivePath);
			strTmp.Format(_T("%02x, MainId:%02x, SubId:%02x, Cap:%04dGB, %s \r\n"), i, 
				gPhyDriveInfo[i].u08PortMainId, 
				gPhyDriveInfo[i].u08PortSubId, 
				((gPhyDriveInfo[i].u32Capacity + 1023) / 1024 + 1023) / 1024 / 2,
				lpwStr);
			strMsg += strTmp;
		}
	}
	m_CRichEditTestMsg.ReplaceSel(strMsg, 0);
}


void CMpTestDlg::GetDevPath(void)
{
	BOOL bResult = FALSE;
	int i = 0, nCnt = 0, nDevCnt = 0;
	CString strTmp, strMsg;
	char *pcDrivePath = NULL;
	CStringArray SymbLinkNameList;

	if (u08MpMode == MP_FACTORY) {//factory mode enum usb devices
		//bResult = EnumUsbDevSymbLinkName(&GUID_DEVINTERFACE_USB_DEVICE, SymbLinkNameList);
		bResult = EnumUsbDevSymbLinkName(&GUID_DEVINTERFACE_DISK, SymbLinkNameList);
		nCnt = SymbLinkNameList.GetSize();
		if ((nCnt) && (bResult == TRUE)) {
			USES_CONVERSION;
			nDevCnt = 0;
			for (i = 0; i < nCnt; i++) {
				strTmp = SymbLinkNameList.GetAt(i);
				pcDrivePath = T2A(strTmp);
				if (pcDrivePath != NULL) {
					strcpy_s(&gPhyDriveInfo[nDevCnt].cDrivePath[0], MAX_PATH * sizeof(char), pcDrivePath);
					nDevCnt++;
				}
			}
		}
	} //~~ended if(MpMode == MP_FACTORY)
	else if(u08MpMode == MP_COMMON){ //common mode(TBC)
	
	}

	//display dev path to test message
	strMsg.Format(_T(""));
	LPWSTR lpwStr = NULL;
	USES_CONVERSION;
	for (i = 0; i < nDevCnt; i++) {
		lpwStr = A2T(gPhyDriveInfo[i].cDrivePath);
		strTmp.Format(_T("%02d, %s \r\n"), i, lpwStr);
		strMsg += strTmp;
	}
	m_CRichEditTestMsg.ReplaceSel(strMsg, 0);

}
