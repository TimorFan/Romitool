#pragma once


// CMpParam 对话框

class CMpParam : public CDialogEx
{
	DECLARE_DYNAMIC(CMpParam)

public:
	CMpParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMpParam();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MPPARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
