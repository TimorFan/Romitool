#pragma once


// CMpTestDlg �Ի���

class CMpTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMpTestDlg)

public:
	CMpTestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMpTestDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MPTEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
