
// RomitoolDlg.h : ͷ�ļ�
//

#pragma once

#include "CommonFunc.h"
#include "afxcmn.h"
#include "MainTab_Mp.h"
#include "MainTab_Info.h"

// CRomitoolDlg �Ի���
class CRomitoolDlg : public CDialogEx
{
// ����
public:
	CRomitoolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROMITOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabMainFrame;
	CMainTab_Mp m_TabMp;
	CMainTab_Info m_TabInfo;
	CMenu m_Menu;


	//init func
	void MainTabControlInit(void);

	//afx mesage func
	afx_msg void OnTcnSelTabChange(NMHDR *pNMHDR, LRESULT *pResult);

};
