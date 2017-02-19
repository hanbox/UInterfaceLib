#pragma once

/************************************************* 
Copyright:forour
Author: 
Date:2015-06-28
Description:工具类接口
**************************************************/  
class   CCommTools
{
public:
	CCommTools(void);
	~CCommTools(void);

public:
	/* 字串转16进制 */
	UCHAR *ToByte(CString csframe);

	/* 设置字体 */
	void SetFont(CFont *pfont, long lHeight, CString csFaceName);

	/* 校验和 */
	UCHAR CheckSum(UCHAR *pRecvBuf, int iLen);

	/* 二进制转16进制 */
	CString BinaryToHex(CString strBin);

	/* 显示消息于List */
	void ShowInList(CListBox *pList, CString csMessage);

	//void  MajorMap(CImage *pImage);

	CString FormatString(UCHAR *pBuf, int iMode, int iLen);

	CString Deal16ByteFomat(CString &csData);

	UCHAR BCC(UCHAR *pData, int ilen);

	char* CCommTools::EncodeToUTF8(const char* mbcsStr);

	std::string GetLocTime(int iMode = 0);

	std::string GetLocDate(int iMode = 0);

	static char*   WToA(CString csData);

	static WCHAR*  AToW(char *pstr, int ilen);

	char* WTUTF8(CString csBuffer);

	// hWnd 设置为透明窗口
	// clr 透明颜色
	// byAlpha 透明度数，0-255
	// dwFlags==LWA_COLORKEY clr有效
	// dwFlags==LWA_ALPHA byAlpha有效
	void SetTransparentWnd(HWND hWnd,COLORREF clr,BYTE byAlpha,DWORD dwFlags);

	void CloseDisable(char *title);

	BOOL DeleteMyFile(CString csPath);

	bool FindMyFile(CString csPath);

	bool ChkFileType(CString csType);

	void OpenFileWithDlg(CString csFileFilter, CStringArray &csPath);

	void OpenPicWithDlg(CStringArray &csPath);

	int GetAngle(CPoint center, CPoint startPoint, CPoint desPooint);

	int DealDirection(CPoint startPoint, CPoint endPoint);

	void WriteDataToIni(CString csA, CString csB, CString csC);

	bool FileIsExist(CString csPath);

	void SetiniPath(CString csPath)
	{
		m_csIniPath = csPath;
	}

protected:
	CString m_csIniPath;

private:
};

namespace ulib
{
	/************************************************* 
	Function:				InitTools
	Description:		初始化工具类
	Input:					void 
	Return:					int：成功后返回1，否则为错误
	Others:					NULL
	*************************************************/  

	extern "C" __declspec(dllexport) CCommTools* InitTools();

	/************************************************* 
	Function:				ReleaseTools
	Description:		释放工具类
	Input:					void 
	Return:					int：成功后返回1，否则为错误
	Others:					NULL
	*************************************************/  
	extern "C" __declspec(dllexport) void ReleaseTools();
}