#pragma once


// CMpParamDlg �Ի���

class CMpParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMpParamDlg)

public:
	CMpParamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMpParamDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MPPARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
