// MainTab_Mp.cpp : 实现文件
//

#include "stdafx.h"
#include "Romitool.h"
#include "MainTab_Mp.h"
#include "afxdialogex.h"


// CMainTab_Mp 对话框

IMPLEMENT_DYNAMIC(CMainTab_Mp, CDialogEx)

CMainTab_Mp::CMainTab_Mp(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MP, pParent)
{

}

CMainTab_Mp::~CMainTab_Mp()
{
}

void CMainTab_Mp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MP, m_MpSubTab);
}


BEGIN_MESSAGE_MAP(CMainTab_Mp, CDialogEx)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MP, &CMainTab_Mp::OnTcnSelMpSubTabPage)
END_MESSAGE_MAP()


// CMainTab_Mp 消息处理程序


BOOL CMainTab_Mp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//init mp sub tab control
	MpSubTabControlInit();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMainTab_Mp::MpSubTabControlInit(void)
{
	m_MpSubTab.InsertItem(0, _T("MP_TEST"));
	m_MpSubTab.InsertItem(1, _T("MP_PARAM"));
	//m_MpSubTab.InsertItem(2, _T("MP_RESERVE"));

	m_TabMpTest.Create(IDD_DIALOG_MPTEST, &m_MpSubTab);
	m_TabMpParam.Create(IDD_DIALOG_MPPARAM, &m_MpSubTab);

	CRect rItem, rSubTab;
	m_MpSubTab.GetItemRect(0, &rItem);
	m_MpSubTab.GetClientRect(&rSubTab);
	int x = rItem.left;
	int y = rItem.bottom;
	int cx = rSubTab.right - x - 3;
	int cy = rSubTab.bottom - y - 2;
	int nTabSel = m_MpSubTab.GetCurSel();

	m_TabMpTest.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	m_TabMpParam.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	m_TabMpTest.ShowWindow(TRUE);
	m_TabMpParam.ShowWindow(FALSE);

	m_MpSubTab.SetCurSel(0);
}


void CMainTab_Mp::OnTcnSelMpSubTabPage(NMHDR *pNMHDR, LRESULT *pResult)
{
	CRect rItem, rSubTab;
	m_MpSubTab.GetItemRect(0, &rItem);
	m_MpSubTab.GetClientRect(&rSubTab);
	int x = rItem.left;
	int y = rItem.bottom;
	int cx = rSubTab.right - x - 3;
	int cy = rSubTab.bottom - y - 2;
	int nTabSel = m_MpSubTab.GetCurSel();
	m_TabMpTest.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	m_TabMpParam.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);

	switch (nTabSel) {
	case 0:
		m_TabMpTest.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
		break;
	case 1:
		m_TabMpParam.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
		break;
	default:
		break;
	}


	*pResult = 0;
}