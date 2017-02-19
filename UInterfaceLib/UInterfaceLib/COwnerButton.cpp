#include "StdAfx.h"
#include "COwnerButton.h"


IMPLEMENT_DYNAMIC(COwnerButton, CButton)

COwnerButton::COwnerButton()
{
	m_bOver = FALSE;
}

COwnerButton::~COwnerButton()
{

}


BEGIN_MESSAGE_MAP(COwnerButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseOut)
END_MESSAGE_MAP()



// COwnerDrawButton 消息处理程序



void COwnerButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CRect rectButton(&lpDrawItemStruct->rcItem);
	CRect rectTxt;

	COLORREF crOldTextColor = pDC->GetTextColor();
	COLORREF crOldBkColor = pDC->GetBkColor();

	HDC hDC = lpDrawItemStruct->hDC;
	//int btnWidth = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	//int btnHeight = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;

	UINT state = lpDrawItemStruct->itemState;

	if((state & ODS_DISABLED) ||
		(!m_bOver &&!(state & ODS_SELECTED)))
	{
		//普通状态、禁用、拥有焦点三种情况下
		if(state &ODS_DISABLED)
		{
			//灰色字：禁用状态
			pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));//灰色字：禁用状态
			pDC->FillSolidRect(&rectButton,RGB(0xBD,0xBD,0xBD));
		}
		else
		{
			 pDC->FillSolidRect(&rectButton,RGB(65,153,221));
			//DrawBitmap(hDC,m_hUpBitmap, btnWidth, btnHeight);
		}
	}
	else
	{
		if( state & ODS_SELECTED)
		{
			//按钮按下时
			 pDC->FillSolidRect(&rectButton,RGB(149,190,222));
			//DrawBitmap(hDC,m_hDownBitmap, btnWidth, btnHeight);
		}
		else
		{
			//鼠标在区域内
			pDC->FillSolidRect(&rectButton,RGB(103,170,222));
			//DrawBitmap(hDC,m_hOverBitmap, btnWidth, btnHeight);
		}
	}

	// 绘制按钮上文本
	CString strName;
	GetWindowText(strName);

	CFont font;
	
	CCommTools::GetInstance()->windows_setfont(&font, 19, _T("微软雅黑"));

	pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255,255,255));
	rectTxt = this->GetTextRect(strName.GetLength() );
	if ( rectTxt == NULL )
	{
		return;
	}

	pDC->DrawText(strName, strName.GetLength(), &rectTxt,DT_VCENTER|DT_SINGLELINE|DT_VCENTER);

	pDC->SetTextColor(crOldTextColor);
	pDC->SetBkColor(crOldBkColor);
}

CRect COwnerButton::GetTextRect(int iLen)
{
	CRect rect;
	CRect rectWnd;
	this->GetClientRect(rectWnd);

	if ( iLen == 0 )
	{
		return NULL;
	}
	else if ( iLen == 1 )
	{
		rect = CRect(rectWnd.left + 25, rectWnd.top, rectWnd.right, rectWnd.bottom);
	}
	else if ( iLen == 2 )
	{
		rect = CRect(rectWnd.left + 20, rectWnd.top, rectWnd.right, rectWnd.bottom);
	}
	else if ( iLen == 3 )
	{
		rect = CRect(rectWnd.left + 15, rectWnd.top, rectWnd.right, rectWnd.bottom);
	}
	else if ( iLen == 4 )
	{
		rect = CRect(rectWnd.left + 10, rectWnd.top, rectWnd.right, rectWnd.bottom);
	}
	else if ( iLen == 5 )
	{
		rect = CRect(rectWnd.left + 5, rectWnd.top, rectWnd.right, rectWnd.bottom);
	}
	
	return rect;
}

void COwnerButton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0,BS_OWNERDRAW);

	CButton::PreSubclassWindow();
}

void COwnerButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bOver == FALSE)
	{
		//鼠标在按钮之上
		m_bOver = TRUE;

		//按钮重绘
		InvalidateRect(NULL,FALSE);

		//跟踪鼠标
		//当鼠标离开按钮区域会收到WM_MOUSELEAVE,该消息直接调用OnMouseOut()
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = 0;
		tme.hwndTrack = m_hWnd;
		::TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);
}

LRESULT COwnerButton::OnMouseOut(WPARAM wParam, LPARAM lParam)
{
	//鼠标已离开按钮区域
	m_bOver = FALSE;

	//重绘按钮
	InvalidateRect(NULL,FALSE);

	return 0;
}

void COwnerButton::DrawBitmap(HDC hDC, HBITMAP hBitmap,int w, int h)
{
	if (hBitmap == NULL) return;

	// Set the bitmap to dialog.
	HDC hMemDC = CreateCompatibleDC(hDC);

	SelectObject(hMemDC,hBitmap);

	BITMAP bmp;
	GetObject(hBitmap,sizeof(BITMAP),&bmp);

	BitBlt(hDC,0,0,w,h,hMemDC,0,0,SRCCOPY);

	DeleteDC(hMemDC);
}

BOOL COwnerButton::InitButton(HINSTANCE hInstance, int nUpID, int nDownID, int nOverID)
{
	m_hUpBitmap   = ::LoadBitmap(hInstance,MAKEINTRESOURCE(nUpID));
	m_hDownBitmap = ::LoadBitmap(hInstance,MAKEINTRESOURCE(nDownID));
	m_hOverBitmap = ::LoadBitmap(hInstance,MAKEINTRESOURCE(nOverID));

	return TRUE;
}

void COwnerButton::ReleaseButton()
{
	delete m_hUpBitmap;
	delete m_hDownBitmap;
	delete m_hOverBitmap;
}