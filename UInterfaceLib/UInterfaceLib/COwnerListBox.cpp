#include "StdAfx.h"
#include "COwnerListBox.h"

IMPLEMENT_DYNAMIC(COwnerListBox, CListBox)

	COwnerListBox::COwnerListBox()
{
	this->m_iListheight = 20;
	this->m_bShowTime = FALSE;
}

COwnerListBox::~COwnerListBox()
{

}

BEGIN_MESSAGE_MAP(COwnerListBox, CListBox)
	ON_WM_DESTROY()
	ON_WM_MOVE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// COwnerDrawListBox 消息处理程序
void COwnerListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO:  添加您的代码以确定指定项的大小
	lpMeasureItemStruct->itemHeight = this->m_iListheight;
}

void COwnerListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	UpdateData(FALSE);

	if ( lpDrawItemStruct->itemID == -1 ) 
	{
		DrawFocusRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem);
		return;
	}

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	COLORREF crOldTextColor = pDC->GetTextColor();
	COLORREF crOldBkColor = pDC->GetBkColor();

	m_rectListBox = lpDrawItemStruct->rcItem;

	// 列表Item中的图标位置
	CRect rectIcon(m_rectListBox.left + 10, m_rectListBox.top, m_rectListBox.left + 50, m_rectListBox.top);

	// 列表Item中的文本位置
	CRect rectData(m_rectListBox.left + 60, m_rectListBox.top,m_rectListBox.left + 1000, m_rectListBox.top + 20);
	CRect rectNoIconData(m_rectListBox.left + 0, m_rectListBox.top,m_rectListBox.left + 1000, m_rectListBox.top + 20);

	//列表Item中的时间
	CRect rectTime(m_rectListBox.right  - 50, m_rectListBox.top,m_rectListBox.right, m_rectListBox.top + 20);

	stLISTITEM *pItem = (stLISTITEM*)GetItemDataPtr(lpDrawItemStruct->itemID);
	if ( pItem == NULL )
	{
		return;
	}

	if ( ::IsBadStringPtrW(pItem->csData, MAX_PATH) )
	{
		return;
	}

	if ((lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED))
	{
		// 选中状态
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->FillSolidRect(&m_rectListBox,RGB(8,129,222));
	}
	else
	{
		// 未选中状态
		pDC->SetTextColor(pItem->cTextColor);
		pDC->FillSolidRect(&m_rectListBox, pItem->cBGColor);
	}

	if ( pItem->hIcon == NULL )
	{
		pDC->DrawText(pItem->csData, pItem->csData.GetLength(), &rectNoIconData, DT_VCENTER|DT_SINGLELINE|DT_VCENTER);
	}
	else
	{
		pDC->DrawIcon(rectIcon.left, rectIcon.top, pItem->hIcon);
		pDC->DrawText(pItem->csData, pItem->csData.GetLength(), &rectData, DT_VCENTER|DT_SINGLELINE|DT_VCENTER);
	}

	if ( this->m_bShowTime )
	{
		pDC->SetTextColor(RGB(0xAA,0xAA,0xAA));
		pDC->DrawText(pItem->csTime,pItem->csTime.GetLength(), &rectTime, DT_VCENTER|DT_SINGLELINE|DT_VCENTER);
	}

	pDC->SetTextColor(crOldTextColor);
	pDC->SetBkColor(crOldBkColor);
}

int COwnerListBox::AddListItem(CString csData, COLORREF TextColor, COLORREF BGColor, HICON hIcon)
{
	stLISTITEM *stItem = new stLISTITEM;
	stItem->hIcon = hIcon;
	stItem->csData = csData;
	stItem->csTime = this->GetLocTime();
	stItem->cTextColor = TextColor;
	stItem->cBGColor = BGColor;

	int iIndex = this->AddString(_T(""));
	SetItemDataPtr(iIndex, stItem);

	return iIndex;
}

void COwnerListBox::OnDestroy()
{
	int ItemCount;
	ItemCount = GetCount();

	if (ItemCount != 0 )
	{
		for (int i = 0; i < ItemCount; i++)
		{
			stLISTITEM *stItem = (stLISTITEM*)GetItemDataPtr(i);
			delete stItem;
			stItem = NULL;
		}
	}

	CListBox::OnDestroy();
}

int COwnerListBox::CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/)
{

	// TODO:  添加您的代码以确定指定项的排序顺序
	// 返回-1 表示项1 排在项2 之前
	// 返回0 表示项1 和项2 顺序相同
	// 返回1 表示项1 排在项2 之后

	return 0;
}

void COwnerListBox::SetParWndHandle(HWND hWnd)
{
	m_hParWnd = hWnd;
}

CString COwnerListBox::GetLocTime(void)
{
	CString csTime;
	SYSTEMTIME stLoctime; 
	GetLocalTime(&stLoctime); 
	csTime.Format(_T("%02d:%02d:%02d"),stLoctime.wHour, stLoctime.wMinute, stLoctime.wSecond);

	return csTime;
}

void COwnerListBox::OnMove(int x, int y)
{
	CListBox::OnMove(x, y);

	// TODO: Add your message handler code here
}


void COwnerListBox::OnSize(UINT nType, int cx, int cy)
{
	CListBox::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	this->RedrawWindow();
}
