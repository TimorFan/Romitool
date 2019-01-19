// MpParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Romitool.h"
#include "MpParamDlg.h"
#include "afxdialogex.h"


// CMpParamDlg 对话框

IMPLEMENT_DYNAMIC(CMpParamDlg, CDialogEx)

CMpParamDlg::CMpParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MPPARAM, pParent)
{

}

CMpParamDlg::~CMpParamDlg()
{
}

void CMpParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMpParamDlg, CDialogEx)
END_MESSAGE_MAP()


// CMpParamDlg 消息处理程序
