#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;

// ListBox中Item项
struct stLISTITEM
{
	HICON hIcon;             // 图标
	CString csData;         // 数据
	CString csTime;
	COLORREF cTextColor;
	COLORREF cBGColor;
};

class COwnerListBox :
	public CListBox
{
	DECLARE_DYNAMIC(COwnerListBox)

public:
	COwnerListBox(void);
	~COwnerListBox(void);

	void ShowTime(BOOL bState)
	{
		this->m_bShowTime = bState;
	}

protected:
	CRect m_rectListBox;          // 列表项到绘制Rect
	HWND m_hParWnd;           // 父窗口句柄
	UINT	  m_iListheight; 

	BOOL m_bShowTime;

	DECLARE_MESSAGE_MAP()

public:
	// 设置自绘ListBox的Item到宽和高
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	// 重绘ListBox的Item
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// 在自绘ListBox中添加一个新的Item项
	int AddListItem(CString csData, COLORREF TextColor = RGB(0, 0, 0), COLORREF BGColor = RGB(255, 255, 255), HICON hIcon = NULL);

	// 用来清理堆栈
	afx_msg void OnDestroy();
	virtual int CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/);

	// 将父窗口句柄传入类
	void SetParWndHandle(HWND hWnd);

	CString GetLocTime(void);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

