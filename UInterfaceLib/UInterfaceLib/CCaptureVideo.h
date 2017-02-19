#pragma once
#include <dshow.h>
#include <qedit.h>

#ifdef _DEBUG
#pragma comment(lib, "strmbasd.lib")
#else
#pragma comment(lib, "STRMBASE.lib")
#endif

class __declspec(dllexport) CCamDataDealBase
{
public:
	virtual void DealCamData(BYTE * pBuffer, long lWidth,long lHeight) = 0 ; 
};

class __declspec(dllexport) CSampleGrabberCB : public ISampleGrabberCB 
{
public:
	long       lWidth ; 
	long       lHeight ; 
	CCamDataDealBase* m_pDataDeal; 
	BOOL       bGrabVideo; 

public:
	CSampleGrabberCB()
	{ 
		lWidth = 0 ; 
		lHeight = 0 ; 
		bGrabVideo = FALSE ; 
		m_pDataDeal = nullptr ; 
	} 

	STDMETHODIMP_(ULONG) AddRef()
	{
		return 2;
	}

	STDMETHODIMP_(ULONG) Release()
	{
		return 1;
	}

	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{
		if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown )
		{ 
			*ppv = (void *) static_cast<ISampleGrabberCB*> ( this );

			return NOERROR;
		} 

		return E_NOINTERFACE;
	}

	STDMETHODIMP SampleCB(double SampleTime, IMediaSample * pSample)
	{
		return 0;
	}

	/** 视频流图像更新回调函数 */
	STDMETHODIMP BufferCB(double dblSampleTime, BYTE * pBuffer, long lBufferSize)
	{
		if ( pBuffer == nullptr)
		{
			return E_POINTER;
		}	

		if ( m_pDataDeal != nullptr )
		{
			m_pDataDeal->DealCamData(pBuffer,lWidth,lHeight);
		}

		return 0;
	}
};

class __declspec(dllexport)  CCaptureVideo
{
	friend class CSampleGrabberCB;

public:
	void GrabVideoFrames(BOOL bGrabVideoFrames, CCamDataDealBase *pDeal); 
	HRESULT Open(int iDeviceID,HWND hWnd);
	HRESULT Close(); 
	int EnumDevices(HWND hList);
	CCaptureVideo();
	virtual ~CCaptureVideo();

protected:
	HWND     m_hWnd;
	IGraphBuilder *   m_pGB;
	ICaptureGraphBuilder2* m_pCapture;
	IBaseFilter*   m_pBF;
	IMediaControl*   m_pMC;
	IVideoWindow*   m_pVW;
	ISampleGrabber*   m_pGrabber;
	CSampleGrabberCB mCB;

protected:
	void FreeMediaType(AM_MEDIA_TYPE& mt);
	bool BindFilter(int deviceId, IBaseFilter **pFilter);
	void ResizeVideoWindow();
	HRESULT SetupVideoWindow();
	HRESULT InitCaptureGraphBuilder();
};