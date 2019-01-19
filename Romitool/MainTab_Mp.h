#pragma once
#include "afxcmn.h"
#include "MpTestDlg.h"
#include "MpParamDlg.h"


// CMainTab_Mp �Ի���

class CMainTab_Mp : public CDialogEx
{
	DECLARE_DYNAMIC(CMainTab_Mp)

public:
	CMainTab_Mp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainTab_Mp();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_MpSubTab;
	CMpTestDlg m_TabMpTest;
	CMpParamDlg m_TabMpParam;

	//init func
	void MpSubTabControlInit(void);

	//afx_msg func
	afx_msg void OnTcnSelMpSubTabPage(NMHDR *pNMHDR, LRESULT *pResult);
};
