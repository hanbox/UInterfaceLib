#pragma once

class __declspec(dllexport) CCmdStation : public CBaseCmdStation
{
public:
	CCmdStation(void);
	~CCmdStation(void);

	virtual void RecvData(unsigned char inData);

	virtual void ResetRcvBuf();

	virtual void SetRecvBuf();

	virtual void SetRecvLine();

protected:
	UCHAR*		m_pRecvBuf;				//接收数据缓冲区

	unsigned int m_nRcvIndex;		//已接收字节计数

	UINT		m_nFrameLength;	//当前指令长度

	BOOL		m_bFrameStart;
};