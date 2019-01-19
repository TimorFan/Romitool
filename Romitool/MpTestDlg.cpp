// MpTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Romitool.h"
#include "MpTestDlg.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(CMpTestDlg, CDialogEx)
END_MESSAGE_MAP()


// CMpTestDlg 消息处理程序


BOOL CMpTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

