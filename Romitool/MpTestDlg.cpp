// MpTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Romitool.h"
#include "MpTestDlg.h"
#include "afxdialogex.h"


// CMpTestDlg �Ի���

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


// CMpTestDlg ��Ϣ�������


BOOL CMpTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

