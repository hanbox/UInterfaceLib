#include "StdAfx.h"

COwnerPicSta::COwnerPicSta(void)
{
}


COwnerPicSta::~COwnerPicSta(void)
{
}

BEGIN_MESSAGE_MAP(COwnerPicSta, CStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

//iMethod缩放的方式：0:图片原比例, 1:拉伸图片
void COwnerPicSta::LoadImage(Mat img, int iMethod)
{
	if ( img.empty() )
	{
		return;
	}

	this->GetClientRect(&m_Rect);
	m_Image = Mat(m_Rect.Height(),m_Rect.Width(),CV_8UC3);

	if (m_Image.size != img.size)
	{
		ResizeImage(img, m_Rect, m_Image, iMethod);
	}
	else
	{
		m_Image = img;
	}

	//OnPaint();
	Invalidate(FALSE);
}

//iMethod缩放的方式：0:图片原比例, 1:拉伸图片

void  COwnerPicSta::LoadImage(CString csPath, int iMethod)
{
	if ( csPath.IsEmpty() )
	{
		return;
	}

	Mat Image;
#ifdef _UNICODE
	Image = imread((string)CCommTools::GetInstance()->string_W2A(csPath));
#else
	Image = imread((string)csPath);
#endif
	
	if ( Image.data == nullptr)
	{
		CString csTmp;
		csTmp.Format(_T("加载文件路径%s错误"), csPath);
		MessageBox(csTmp, _T("操作失败"), MB_ICONERROR);

		return;
	}

	m_csPath = _T("");
	m_csPath = csPath;
	this->LoadImage(Image, iMethod);
}

//img输入的图像，rect希望调整成的大小（类型为MFC类的CRect），dst_img调整后的图，
//该函数先格式化dst_img,再将img画到dst_img,因此不能img与dst_img绝不能是同一个图
//method缩放的方式：0表示保持图片原比例去适应rect,1表示拉伸图片去适应rect
void COwnerPicSta::ResizeImage(Mat &img,CRect rect,Mat &dst_img,int method)
{
	// 读取图片的宽和高
	int h = img.rows;
	int w = img.cols;
	int nw,nh;

	if (0==method)
	{
		// 计算将图片缩放到dst_drawing区域所需的比例因子
		float scale1 = (float) ( (float)w /(float)rect.Width() );
		float scale2 = (float) ( (float)h /(float)rect.Height() );

		float scale=(scale1>scale2)?scale1:scale2;

		// 缩放后图片的宽和高
		nw = ((float)w)/scale;
		nh = ((float)h)/scale;

		//由于浮点也存在数据截断，为防止nw大于目标框大小，做个边界保护
		if (nw>rect.Width())
		{
			nw=rect.Width();
		}
		if (nh>rect.Height())
		{
			nh=rect.Height();
		}
	}else if (1==method)
	{
		// 缩放后图片的宽和高
		nw = rect.Width();
		nh = rect.Height();
	}

	// 为了将缩放后的图片存入 dst_drawing 的正中部位，需计算图片在 dst_drawing 左上角的期望坐标值
	int tlx = ( nw < rect.Width())? (((float)(rect.Width()-nw))/2.0f+0.5f):   0;
	int tly = ( nh < rect.Height())? (((float)(rect.Height()-nh))/2.0f+0.5f): 0;

	//重置矩阵大小在图比较大时也很费时间，加个判断可避免重复的重置矩阵大小
	if ( dst_img.rows!=rect.Height() || dst_img.cols!=rect.Width() || dst_img.type()!=img.type() )
	{
		dst_img=Mat(rect.Height(),rect.Width(),img.type());
	}
	if (0==method)
	{
		dst_img=0;
	}
	// 设置 dst_img 的 ROI 区域，用来存入更改后的图片 img
	Rect rect_roi=Rect(tlx,tly,nw,nh);

	// 对图片 img 进行缩放，并存入到 src_drawing 中
	Mat dst_img_roi=dst_img(rect_roi);

	//将img尺寸缩放至dst_img_roi尺寸,插值方法选用INTER_NEAREST，放到最大后无近似显示能将每个像素看清
	resize(img,dst_img_roi,cv::Size(nw,nh),0.0,0.0,INTER_NEAREST);
}

void COwnerPicSta::OnPaint()
{
	//用于响应窗口重绘消息,删除后 WM_PAINT消息无法从消息队列中清除，将引起不断的窗口重画
	CPaintDC dc(this);

	CDC* pDC=this->GetDC();	
	HDC hDC = pDC->GetSafeHdc();

	this->GetClientRect(&m_Rect);

	IplImage* pImage = &IplImage(m_Image);
	CvvImage Cvvimg;
	Cvvimg.CopyOf(pImage);
	Cvvimg.DrawToHDC(hDC, &m_Rect );

	ReleaseDC(pDC);		
}

void COwnerPicSta::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ( !m_csPath.IsEmpty() )
	{
		Mat tmp = imread((string)CCommTools::GetInstance()->string_W2A(m_csPath));
		
		imshow(CCommTools::GetInstance()->string_W2A(m_csPath), tmp);
	}

	CStatic::OnLButtonDblClk(nFlags, point);
}



cv::Mat COwnerPicSta::GetImage()
{
	return m_Image;
}
