#include "stdafx.h"
#include "MainTab_Info.h"
#include "Romitool.h"

// CMainTab_Info �Ի���

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CMainTab_Info::DoDataExchange(CDataExchange* pDX)
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainTab_Info, CDialogEx)
END_MESSAGE_MAP()