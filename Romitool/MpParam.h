#pragma once


// CMpParam �Ի���

class CMpParam : public CDialogEx
{
	DECLARE_DYNAMIC(CMpParam)

public:
	CMpParam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMpParam();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MPPARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
