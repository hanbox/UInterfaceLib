#pragma once

typedef unsigned __int16    INT16U;

//发送指令的缓冲列表成员
struct CMDBUF 
{
	UCHAR * pCmdBuf;	//指令数组指针
	UINT nLen;			//指令长度
};

class CBaseCmdStation
{
public:
	CBaseCmdStation(){};
	virtual ~CBaseCmdStation(){};

public:
	virtual void RecvData(unsigned char inData) = 0;
	virtual void ResetRcvBuf() = 0;
	virtual void SetRecvBuf() = 0;
	virtual void SetRecvLine() = 0;
};

class __declspec(dllexport) CSerialCom
{
public:
	CSerialCom();
	virtual ~CSerialCom();	

public:
	BOOL IsRunning();

	BOOL Create(int iCom, int iBaudrate);
	
	void Close();

	void Send(const void *pBuffer, const int iLength);		//通过缓冲列表进行指令发送（标准接口）

		/*!	@func	CSerialCom::GetSerialPortParam
	|*	@brief	获取串口连接参数
	|*	@param	comNo	串口号
	|*	@param	baud	波特率
	|*	@return null
	\**/
	void GetSerialPortParam(int & comNo, int & baud);

	void SetCmdStation(CBaseCmdStation * pCmdStation);

	void InitCom(int iComNo[]);

protected:
	void SendData(int nodeID, int memAddr, int data);

	/*!	@func	CSerialCom::ParseByte
	|*	@brief	接收到数据
	|*	@param	inChar	接收到的一个字节
	|*	@return null
	\**/
	virtual void ParseByte(BYTE* inChar);

protected:
	//串口属性
	int			m_iCom;												
	int			m_iBaudrate;
	HANDLE		m_hSingleEvent;
	BYTE		m_bytesize;
	BYTE		m_parity;
	BYTE		m_stopbits;
	CRITICAL_SECTION	m_cComCS;							//临界区保护对象

protected:
	CPtrList		m_cmdlist;									//发送指令的缓冲列表
	CMDBUF   *	m_pTempCmd;									//发送指令缓冲成员临时指针
	HANDLE		m_hCom;										//已打开的串口句柄
	BOOL			m_bIsRuning;									//运行状态标记
	BOOL			m_bSending;									//发送标记

	CBaseCmdStation *	m_pParser;

private:
	static UINT ComMonitor(LPVOID pParam);
	static UINT SendingThread(LPVOID pParam);
	void SetComProp(DCB* inProp);
	void ComSend(const void *pBuffer, const int iLength);	//直接发送指令

protected:
	CWinThread	*	m_pSendThread;		//发送线程
	CWinThread	*	m_pRecvThread;		//接收线程
};
