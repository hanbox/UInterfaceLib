#pragma once

/************************************************* 
Copyright:forour
Author: 
Date:2015-06-28
Description:自绘控件类
**************************************************/  

/************************************************* 
Function:				COwnerButton
Description:		自绘按钮类
Input:					
Return:					
Others:					
*************************************************/  
class COwnerButton : public CButton
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

	// 绘制位图
	void DrawBitmap(HDC hDC, HBITMAP hBitmap, int w, int h);

	// 初始化自绘按钮
	BOOL InitButton(HINSTANCE hInstance, int nUpID, int nDownID, int nOverID);

	// 释放自绘按钮
	void ReleaseButton();

	CRect GetTextRect(int iLen);

protected:
	// 自绘按钮的三种状态对应的位图句柄
	HBITMAP m_hUpBitmap, m_hDownBitmap, m_hOverBitmap; // Up, Down, Over
	BOOL m_bOver;
};

/************************************************* 
Function:				COwnerPicSta
Description:		自绘静态框类
Input:					
Return:					
Others:					
*************************************************/  
class COwnerPicSta : public CStatic
{
public:
	COwnerPicSta(void);
	~COwnerPicSta(void);
	void LoadImage(cv::Mat img, int iMethod = 1);
	void  LoadImage(CString csPath, int iMethod = 1);
	cv::Mat GetImage();

protected:
	cv::Mat m_Image;
	CRect m_Rect;
	CString m_csPath;
};