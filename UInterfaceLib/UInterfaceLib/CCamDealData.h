#pragma once
#include "ccapturevideo.h"

#define  VIDEO_WIDTH		640
#define  VIDEO_HEIGHT	480

class __declspec(dllexport) CCamDealData :
	public CCamDataDealBase
{
public:
	CCamDealData(void);
	~CCamDealData(void);

public:
	void GrabVideoFrames(BOOL bGrabVideoFrames); 
	HRESULT Open(int iDeviceID,HWND hWnd);
	HRESULT Close(); 
	int EnumDevices(HWND hList);
	cv::Mat SceenShot();

protected:
	CCaptureVideo m_Cam;
	BYTE* m_pBuf;	

private:
	void ProcessBuf(BYTE * pBuffer, long lWidth,long lHeight);
	void DealCamData(BYTE * pBuffer, long lWidth,long lHeight);
};

