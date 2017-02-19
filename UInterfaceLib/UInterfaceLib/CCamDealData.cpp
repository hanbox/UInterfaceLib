#include "StdAfx.h"
#include "CCamDealData.h"


CCamDealData::CCamDealData(void)
{
	m_pBuf = new BYTE[VIDEO_WIDTH*VIDEO_HEIGHT*3];
	memset(m_pBuf, 0x00, sizeof(m_pBuf));
}

CCamDealData::~CCamDealData(void)
{
}

void CCamDealData::DealCamData(BYTE * pBuffer, long lWidth,long lHeight)
{
	this->ProcessBuf(pBuffer, lWidth, lHeight);
}

void CCamDealData::ProcessBuf(BYTE * pBuffer, long lWidth,long lHeight)
{
	if ((lWidth!=VIDEO_WIDTH)||(lHeight!=VIDEO_HEIGHT))
	{
		return;
	}

	int count = 0;
	for (int j = lHeight-1; j >=0; j--)	
	{
		for (int i = 0; i < lWidth; i++)
		{
			memcpy(m_pBuf+count*3,pBuffer+(j*lWidth+i)*3,3);
			count++;
		}
	}
}

cv::Mat CCamDealData::SceenShot()
{
	BYTE  *pBuf = new BYTE[VIDEO_WIDTH * VIDEO_HEIGHT * 3];
	memset(pBuf, 0x00, sizeof(pBuf));

	memcpy(pBuf,m_pBuf,VIDEO_WIDTH*VIDEO_HEIGHT*3);

	Mat mImage(VIDEO_HEIGHT, VIDEO_WIDTH, CV_8UC3, pBuf);  

	return mImage;
}

void CCamDealData::GrabVideoFrames(BOOL bGrabVideoFrames)
{
	if ( bGrabVideoFrames )
	{
		m_Cam.GrabVideoFrames(bGrabVideoFrames, this);
	}
	else
	{
		m_Cam.GrabVideoFrames(bGrabVideoFrames, nullptr);
	}
}

HRESULT CCamDealData::Open(int iDeviceID,HWND hWnd)
{
	if ( hWnd == nullptr )
	{
		return S_FALSE;
	}

	return m_Cam.Open(iDeviceID, hWnd);
}

HRESULT CCamDealData::Close()
{
	return m_Cam.Close();
}

int CCamDealData::EnumDevices(HWND hList)
{
	if ( hList == nullptr )
	{
		return -1;
	}

	return m_Cam.EnumDevices(hList);
}

