#pragma once
#include "CommonFunc.h"
#include "afxcmn.h"

// CMpTestDlg 对话框

class CMpTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMpTestDlg)

public:
	CMpTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMpTestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MPTEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonMpScan();

public:
	u08 u08MpMode;
	CRichEditCtrl m_CRichEditTestStatus;
	CRichEditCtrl m_CRichEditTestMsg;

	void GetDevPath(void);

};
