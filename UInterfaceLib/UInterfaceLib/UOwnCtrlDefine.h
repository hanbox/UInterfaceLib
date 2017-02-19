#pragma once
/************************************************* 
Copyright:forour
Author: 
Date:2015-06-28
Description:自绘控件类
**************************************************/  

#pragma once

class COwnerButton :
	public CButton
{
	DECLARE_DYNAMIC(COwnerButton)

public:
	COwnerButton(void);
	~COwnerButton(void);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

public:
	// 自绘按钮
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// 响应鼠标移动时消息

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	// 自定义鼠标移出按钮时消息
	afx_msg LRESULT OnMouseOut(WPARAM wParam, LPARAM lParam);

	BOOL m_bOver;

	// 绘制位图
	void DrawBitmap(HDC hDC, HBITMAP hBitmap, int w, int h);

	// 初始化自绘按钮
	BOOL InitButton(HINSTANCE hInstance, int nUpID, int nDownID, int nOverID);

	// 释放自绘按钮
	void ReleaseButton();

	// 自绘按钮的三种状态对应的位图句柄
	HBITMAP m_hUpBitmap, m_hDownBitmap, m_hOverBitmap; // Up, Down, Over

	CRect GetTextRect(int iLen);
};