
// RomitoolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Romitool.h"
#include "RomitoolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRomitoolDlg �Ի���



CRomitoolDlg::CRomitoolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ROMITOOL_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ALFAMEMORY); //AlfaMemory icon
}

void CRomitoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAINFRAME, m_TabMainFrame);
}

BEGIN_MESSAGE_MAP(CRomitoolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAINFRAME, CRomitoolDlg::OnTcnSelTabChange)
END_MESSAGE_MAP()


// CRomitoolDlg ��Ϣ�������

BOOL CRomitoolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

#ifdef ROMITELLI_EDIT
	//set main dialog title
	::SetWindowText(m_hWnd, _T("Alfa_debug"));

	//set tab control
	MainTabControlInit();

	//set menu 
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);
	m_Menu.Detach(); //if not add this, it could collapse, but why???

#endif

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRomitoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRomitoolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRomitoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//tab control init, setting size && pos
void CRomitoolDlg::MainTabControlInit(void)
{
	//tab page insert
	m_TabMainFrame.InsertItem(0, _T("MP"));
	m_TabMainFrame.InsertItem(1, _T("INFO"));
	//m_TabMainFrame.InsertItem(2, _T("PAGE NAME"));

	m_TabMp.Create(IDD_DIALOG_MP, &m_TabMainFrame);
	m_TabInfo.Create(IDD_DIALOG_INFO, &m_TabMainFrame);

	//specific tab control size && position
	CRect rMainTab, rItem;
	m_TabMainFrame.GetItemRect(0, &rItem); //bounding rectangle of tab item
	m_TabMainFrame.GetClientRect(&rMainTab); //client coordinates of tab control
	int x = rItem.left;
	int y = rItem.bottom + 1;
	int cx = rMainTab.right - x - 3; //rMainTab.left == 0
	int cy = rMainTab.bottom - y - 2; //rMainTab.top == 0
	int TabSel = m_TabMainFrame.GetCurSel();
	m_TabMp.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	m_TabInfo.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);

	m_TabMp.ShowWindow(TRUE);
	m_TabInfo.ShowWindow(FALSE);

	m_TabMainFrame.SetCurSel(0); //set position to 0
}


//TCN_SELCHANGE msg notify tab control for changing page
void CRomitoolDlg::OnTcnSelTabChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	//specific tab control size && position
	CRect rMainTab, rItem;
	m_TabMainFrame.GetItemRect(0, &rItem); 
	m_TabMainFrame.GetClientRect(&rMainTab);
	int x = rItem.left;
	int y = rItem.bottom + 1;
	int cx = rMainTab.right - x - 3;
	int cy = rMainTab.bottom - y - 2;
	int TabSel = m_TabMainFrame.GetCurSel();
	m_TabMp.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	m_TabInfo.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);

	switch (TabSel) {
	case 0:
		m_TabMp.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
		break;
	case 1:
		m_TabInfo.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
		break;
	default:
		break;
	}

	*pResult = 0;
}
