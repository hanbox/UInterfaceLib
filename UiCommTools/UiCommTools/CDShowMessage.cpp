// CDShowMessage.cpp : implementation file
//

#include "stdafx.h"
#include "CDShowMessage.h"
#include "afxdialogex.h"

// CDShowMessage dialog
#define SHOW_MESSAGE_COLOR_SYS			0
#define SHOW_MESSAGE_COLOR_SEND		1
#define SHOW_MESSAGE_COLOR_RECV		2

IMPLEMENT_DYNAMIC(CDShowMessage, CDialogEx)

CDShowMessage::CDShowMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDShowMessage::IDD, pParent)
{
	this->m_iBGChange = 0;
}

CDShowMessage::~CDShowMessage()
{
}

void CDShowMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CDShowMessage, CDialogEx)
	ON_COMMAND(ID_MENU_SHOWMESSAGE_CLEARN, &CDShowMessage::OnMenuShowmessageClearn)
	ON_WM_PAINT()
	ON_COMMAND(ID_MENU_COPY, &CDShowMessage::OnMenuCopy)

	//自定义消息
	//ON_MESSAGE(WM_PASSMESSAGE, &CDShowMessage::ShowMessage)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENU_MESSAGE_SHOWMESSAGE, &CDShowMessage::OnMenuMessageShowmessage)
END_MESSAGE_MAP()


// CDShowMessage message handlers

LRESULT CDShowMessage::ShowMessage(WPARAM wParam, LPARAM lParam)
{
	CString csMessage;
	csMessage.Format(_T("%s"), lParam);

	COLORREF BGColor = RGB(255, 255, 255);
	if ( this->m_iBGChange == 0 )
	{
		BGColor = RGB(255, 255, 255);
		this->m_iBGChange = 1;
	}
	else
	{
		BGColor = RGB(0xED, 0xED, 0xED);
		this->m_iBGChange = 0;
	}

	if ( wParam == SHOW_MESSAGE_COLOR_SYS )
	{
			this->m_List.SetCurSel (this->m_List.AddListItem(csMessage, RGB(0x7A, 0x7A, 0x7A), BGColor));
	}
	else if ( wParam == SHOW_MESSAGE_COLOR_SEND )
	{
			this->m_List.SetCurSel (this->m_List.AddListItem(csMessage ,RGB(0x10, 0x4E, 0x8B), BGColor));
	}
	else if ( wParam == SHOW_MESSAGE_COLOR_RECV )
	{
			this->m_List.SetCurSel (this->m_List.AddListItem(csMessage, RGB(0xEE, 0xAD, 0x0E), BGColor));
	}

	return 0;
}

void CDShowMessage::ShowMessage(CString csMessage, int iMode)
{
	COLORREF BGColor = RGB(255, 255, 255);
	if ( this->m_iBGChange == 0 )
	{
		BGColor = RGB(255, 255, 255);
		this->m_iBGChange = 1;
	}
	else
	{
		BGColor = RGB(0xF0, 0xF8, 0xFF);
		this->m_iBGChange = 0;
	}

	if ( iMode == SHOW_MESSAGE_COLOR_SYS )
	{
		this->m_List.SetCurSel (this->m_List.AddListItem(csMessage, RGB(0x7A, 0x7A, 0x7A), BGColor));
	}
	else if ( iMode == SHOW_MESSAGE_COLOR_SEND )
	{
		this->m_List.SetCurSel (this->m_List.AddListItem(csMessage ,RGB(0x10, 0x4E, 0x8B), BGColor));
	}
	else if ( iMode == SHOW_MESSAGE_COLOR_RECV )
	{
		this->m_List.SetCurSel (this->m_List.AddListItem(csMessage, RGB(0xEE, 0xAD, 0x0E), BGColor));
	}
}

BOOL CDShowMessage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//IDR_ICON为图标资源名
	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	this->m_hMenu = LoadMenu(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MENU_SHOWMESSAGE));
	::SetMenu(this->GetSafeHwnd(),this->m_hMenu);//添加到对话框

	if ( !this->m_csTitle.IsEmpty() )
	{
		this->SetWindowText(this->m_csTitle);
	}

	CCommTools::GetInstance()->windows_setfont(&m_font, 17, _T("微软雅黑"));

	this->m_List.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDShowMessage::OnMenuShowmessageClearn()
{
	this->m_List.ResetContent();
}


void CDShowMessage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CRect rect;
	this->GetClientRect(rect);
	this->m_List.MoveWindow(0, 0, rect.Width(), rect.Height());
}


BOOL CDShowMessage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if ( WM_RBUTTONDOWN == pMsg->message )
	{
		if ( pMsg->hwnd == this->m_List.m_hWnd )
		{
			this->DealRMenu(&this->m_List);
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDShowMessage::DealRMenu(CListBox *pList)
{
	if ( pList == NULL )
	{
		return;
	}

	CMenu menu;
	menu.LoadMenu(IDR_MENU_RIGHT); 
	CMenu *pSubMenu = menu.GetSubMenu(0);

	int iState = pList->GetCurSel();
	if ( iState != -1  )
	{
		CPoint Point; 
		GetCursorPos( &Point); 

		CString csMessage;
		//pList->GetText(iState, csMessage);
		stLISTITEM *pItem = (stLISTITEM*)this->m_List.GetItemDataPtr(iState);
		csMessage = pItem->csData;

		if ( csMessage.IsEmpty() )
		{
			return;
		}
		else
		{
			m_csMessage = csMessage;
		}

		pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, Point.x, Point.y, this);
	}
}

void CDShowMessage::CopyMessage()
{
	CString csMessage = m_csMessage;

	BOOL bRet = FALSE;
	if ( !OpenClipboard() )
	{
		MessageBox(_T("剪贴板打开失败！"));
		return;
	}

	if ( !EmptyClipboard() )
	{
		MessageBox(_T("剪贴板清空失败！"));
		return;
	}

	int iLen = csMessage.GetLength() * 2;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, iLen + 2);
	wchar_t *p = (wchar_t*)GlobalLock(hGlobal);
	wmemset(p, 0, csMessage.GetLength() + 1);
	wmemcpy(p, csMessage.GetBuffer(), csMessage.GetLength() + 1);
	bRet = GlobalUnlock(hGlobal);
	HANDLE hResult = SetClipboardData(CF_UNICODETEXT, hGlobal);
	if ( !SUCCEEDED(hResult) )
	{
		return;
	}

	CloseClipboard();
}

void CDShowMessage::OnMenuCopy()
{
	// TODO: Add your command handler code here
	this->CopyMessage();
}


HBRUSH CDShowMessage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}


void CDShowMessage::OnMenuMessageShowmessage()
{
	DWORD dwResult = ::CheckMenuItem(m_hMenu, ID_MENU_MESSAGE_SHOWMESSAGE, MF_BYCOMMAND);
	if ( dwResult == MF_UNCHECKED )
	{
		CheckMenuItem(m_hMenu, ID_MENU_MESSAGE_SHOWMESSAGE, MF_BYCOMMAND | MF_CHECKED);
		this->m_List.ShowTime(TRUE);
	}
	else
	{
		CheckMenuItem(m_hMenu, ID_MENU_MESSAGE_SHOWMESSAGE, MF_BYCOMMAND | MF_UNCHECKED);
		this->m_List.ShowTime(FALSE);
	}

	this->m_List.Invalidate(FALSE);
}

CDShowMessage *m_pDlg = nullptr;

extern "C" __declspec(dllexport) int  InitMessageDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int iRet = -1;

	m_pDlg = new CDShowMessage();
	iRet = m_pDlg->Create(IDD_DLG_SHOWMESSAGE, NULL);

	return iRet;
}

extern "C" __declspec(dllexport) int  ShowMessageWindow(int iShowMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int iRet = -1;

	if ( m_pDlg != nullptr )
	{
		iRet = m_pDlg->ShowWindow(iShowMode);
	}

	return iRet;
}

extern "C" __declspec(dllexport) int  ShowMessage(CString csMessage, int iMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int iRet = -1;

	if ( m_pDlg != nullptr )
	{
		m_pDlg->ShowMessage(csMessage, iMode);
		iRet = 1;
	}

	return iRet;
}

extern "C" __declspec(dllexport) int  MoveMessageWindow(CRect rect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int iRet = -1;

	if ( m_pDlg != nullptr )
	{
		m_pDlg->MoveWindow(rect);
		iRet = 1;
	}

	return iRet;
}

extern "C" __declspec(dllexport) int  ReleaseMessageDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int iRet = -1;

	if ( m_pDlg != nullptr )
	{
		delete m_pDlg;
		m_pDlg = nullptr;
	}

	return iRet;
}
