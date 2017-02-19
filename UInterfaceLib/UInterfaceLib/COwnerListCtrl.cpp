#include "StdAfx.h"
#include "COwnerListCtrl.h"


COwnerListCtrl::COwnerListCtrl(void)
{
	m_iHeightItem = 20;
}


COwnerListCtrl::~COwnerListCtrl(void)
{
}

void COwnerListCtrl::SetItemHeight( int nHeight )
{
	m_iHeightItem = nHeight;
	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void COwnerListCtrl::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (m_iHeightItem > 0)
	{
		lpMeasureItemStruct->itemHeight = m_iHeightItem;
	}
}

DWORD COwnerListCtrl::SetExtendedStyle( DWORD dwNewStyle )
{
	if ( dwNewStyle & LVS_EX_CHECKBOXES )
	{
		dwNewStyle &=~LVS_EX_CHECKBOXES;
		dwNewStyle &=~LVS_EX_GRIDLINES;
	}
	return __super::SetExtendedStyle(dwNewStyle);
}





