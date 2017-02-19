#pragma once
#include "afxwin.h"
using namespace cv;

class __declspec(dllexport) COwnerPicSta : public CStatic
{
public:
	COwnerPicSta(void);
	~COwnerPicSta(void);
	void LoadImage(Mat img, int iMethod = 1);
	void LoadImage(CString csPath, int iMethod = 1);
	cv::Mat GetImage();
	CString GetImagePath()
	{
		return m_csPath;
	}
	void SetID(int iID)
	{
		m_iID = iID;
	}

public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
	cv::Mat m_Image;
	CRect m_Rect;
	CString m_csPath;

	int m_iID;

private:
	void ResizeImage(Mat &img,CRect rect,Mat &dst_img,int method);
};



