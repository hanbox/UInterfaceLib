#include "stdafx.h"

CCmdStation::CCmdStation(void)
{
	this->m_pRecvBuf = new UCHAR[COM_BUF_LEN];
	this->m_nRcvIndex = 0;

	this->m_nFrameLength = 0;
	this->m_bFrameStart = FALSE;
}

CCmdStation::~CCmdStation(void)
{
	if (this->m_pRecvBuf != NULL)
	{
		delete[] this->m_pRecvBuf;
		this->m_pRecvBuf = NULL;
	}
}

void CCmdStation::RecvData(unsigned char nData)
{
	if (nData== 0xFE && !m_bFrameStart)
	{
		m_pRecvBuf[0] = 0xFE;
		m_nRcvIndex = 1;
		m_bFrameStart = true;
		return;
	}

	if (m_bFrameStart)
	{
		//put received data into buffer
		m_pRecvBuf[m_nRcvIndex] = nData;
		if ( m_nRcvIndex == 1 )
		{
			this->m_nFrameLength = nData + 5;
		}
		m_nRcvIndex++;

		////receive one frame, invoke ParseFrame to parse
		if ( this->m_nRcvIndex == this->m_nFrameLength )
		{ 
			//if ( this->m_pRecvBuf[this->m_nFrameLength - 1] != this->m_Tools.BCC(&this->m_pRecvBuf[1], m_nFrameLength - 2)  )
			//{
			//	this->ResetRcvBuf();
			//	return;
			//}

			SetRecvBuf();

			this->ResetRcvBuf();
		}

		if ( m_nRcvIndex > 100 )
		{
			this->ResetRcvBuf();
			return;
		}
	}
}

void CCmdStation::ResetRcvBuf()
{
	memset(m_pRecvBuf, 0x00, COM_BUF_LEN);
	m_nRcvIndex = 0;
	this->m_nFrameLength = 0;
	m_bFrameStart = false;
}

void CCmdStation::SetRecvBuf()
{	
	this->ResetRcvBuf();
}

void CCmdStation::SetRecvLine()
{	
	this->ResetRcvBuf();
}