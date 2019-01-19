#include "stdafx.h"
#include "MainTab_Info.h"
#include "Romitool.h"

// CMainTab_Info 对话框

IMPLEMENT_DYNAMIC(CMainTab_Info, CDialogEx)

CMainTab_Info::CMainTab_Info(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INFO, pParent)
{
}


CMainTab_Info::~CMainTab_Info()
{
}


BOOL CMainTab_Info::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMainTab_Info::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainTab_Info, CDialogEx)
END_MESSAGE_MAP()