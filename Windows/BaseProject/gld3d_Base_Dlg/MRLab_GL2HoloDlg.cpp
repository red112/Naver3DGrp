
// MRLab_GL2HoloDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MRLab_GL2Holo.h"
#include "MRLab_GL2HoloDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMRLab_GL2HoloDlg dialog




CMRLab_GL2HoloDlg::CMRLab_GL2HoloDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMRLab_GL2HoloDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pMRGLView = new CMRGLView;

}

void CMRLab_GL2HoloDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMRLab_GL2HoloDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_LOADOBJ, &CMRLab_GL2HoloDlg::OnBnClickedBtnFileOpen)
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDOK, &CMRLab_GL2HoloDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMRLab_GL2HoloDlg message handlers

BOOL CMRLab_GL2HoloDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//CREATE GL VIEW
	//선택 랜더링 뷰
	GetDlgItem(IDC_GL_CONTROL)->GetWindowRect(m_rctGLView);
	ScreenToClient(m_rctGLView);
	//view생성
	m_pMRGLView->CreateGLView((CView*)this,m_rctGLView);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMRLab_GL2HoloDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMRLab_GL2HoloDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMRLab_GL2HoloDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMRLab_GL2HoloDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	if(m_pMRGLView)		delete m_pMRGLView;

}

void CMRLab_GL2HoloDlg::OnBnClickedBtnFileOpen()
{
	// TODO: Add your control notification handler code here
	//Filter 설정 - 적당한 필터 적용
	const char imagefileFilter[] = "All(*.*)|*.*|PCD(*.pcd)|*.pcd|OBJ file|*.obj;*.OBJ||";
	CFileDialog dlgFile(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, imagefileFilter, NULL,0);

	//대화상자 열기
	if(dlgFile.DoModal() == IDOK)
	{
		//경로 얻기
		CString path = dlgFile.GetPathName();

		////데이터 입력 처리


	}

}

BOOL CMRLab_GL2HoloDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	return m_pMRGLView->OnMouseWheel(nFlags, zDelta, pt);
}

void CMRLab_GL2HoloDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_rctGLView.PtInRect(point))
	{
		m_pMRGLView->OnMouseMove(nFlags, point);
	}
	else
		CDialog::OnMouseMove(nFlags, point);
}

void CMRLab_GL2HoloDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_rctGLView.PtInRect(point))
	{
		m_pMRGLView->OnLButtonDown(nFlags, point);
	}
	else
		CDialog::OnLButtonDown(nFlags, point);
}

void CMRLab_GL2HoloDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_pMRGLView->OnLButtonUp(nFlags, point);
}

void CMRLab_GL2HoloDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	return;
	OnOK();
}

void CMRLab_GL2HoloDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	/* 타이머가 필요하면 SetTimer를 하고 여기서 처리
	if(nIDEvent==1)
	{

	}
	*/
	CDialog::OnTimer(nIDEvent);
}

