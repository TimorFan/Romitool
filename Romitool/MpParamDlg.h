#pragma once


// CMpParamDlg 对话框

class CMpParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMpParamDlg)

public:
	CMpParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMpParamDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MPPARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
