
// RomitoolDlg.h : 头文件
//

#pragma once

#include "CommonFunc.h"
#include "afxcmn.h"
#include "MainTab_Mp.h"
#include "MainTab_Info.h"

// CRomitoolDlg 对话框
class CRomitoolDlg : public CDialogEx
{
// 构造
public:
	CRomitoolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROMITOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
