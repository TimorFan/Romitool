#pragma once
#include "afxdialogex.h"

class CMainTab_Info :
	public CDialogEx
{
	DECLARE_DYNAMIC(CMainTab_Info)

public:
	CMainTab_Info(CWnd* pParent = NULL);
	virtual ~CMainTab_Info();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFO };
#endif

	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

