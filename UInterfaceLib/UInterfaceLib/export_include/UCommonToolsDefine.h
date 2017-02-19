#pragma once
/************************************************* 
Copyright:forour
Author: 
Date:2015-06-28
Description:工具类接口
**************************************************/  
class CCommTools
{
public:
	static CCommTools *GetInstance();
	static void RealeaseInstance();

public:
	/** checkctrl */
	unsigned char check_bcc(unsigned char *pData, int iLen, int iOffset = 0);
	unsigned char check_sum(unsigned char *pData, int iLen, int iOffset = 0);

	/** timectrl */
	string date_getloctime(int iMode = 0);
	string date_getlocdate(int iMode = 0);

	/** stringctrl */
	char* string_W2A(CString csData);
	WCHAR*string_A2W(char *pstr, int ilen);
	char* string_W2UTF8(CString csBuffer);
	char* string_Encode2UTF8(const char* mbcsStr);
	CString string_ucharformat(unsigned char *pBuf, int iMode, int iLen);
	unsigned char *string_W2Byte(CString csframe);

	/** imagedealctrl */
	void imagedeal_closewindow(char *title);
	bool imagedeal_ispic(CString csType);
	void imagedeal_openpicdlg(CStringArray &csPath, int iCount = 0);
	int imagedeal_angle(CPoint center, CPoint startPoint, CPoint desPooint);
	int imagedeal_direction(CPoint startPoint, CPoint endPoint, CPoint cenPoint);
	void imagedeal_showimage(IplImage *image, CWnd* pWnd);

	/** windowsctrl */
	ULIB_RETURN windows_getmac(vector<CString> &v_mac);
	ULIB_RETURN windows_openURL(CString csUrl);
	void windows_filedlg(CString csFileFilter, CStringArray &csPath);
	void windows_transparentwnd(HWND hWnd,COLORREF clr,BYTE byAlpha,DWORD dwFlags);
	void windows_show2List(CListBox *pList, CString csMessage);
	void windows_setfont(CFont *pfont, long lHeight, CString csFaceName);

	/** pathctrl */
	ULIB_RETURN path_filename(string strPath, string &strfilename);
	ULIB_RETURN path_extension(string strPath, string &strextension);
	ULIB_RETURN path_stem(string strPath, string &strstem);
	ULIB_RETURN path_withoutfilename(string strPath, string &strDesPath);

	/** filectrl */
	ULIB_RETURN file_exist(string strPath, string &strError);
	ULIB_RETURN file_currentpath(string &strcurrentpath, string &strError);
	ULIB_RETURN file_remove(string strPath, string &strError);
	ULIB_RETURN file_initialpath(string &strcurrentpath, string &strError);

protected:

private:
	CCommTools(void){}
	~CCommTools(void){}
};

extern "C" __declspec(dllimport) void  InitExcel(CFormatData clsData);
extern "C" __declspec(dllimport) void  ReleaseExcel();

//config
struct STPAIR 
{
	string strTitle;
	string strA;
	string strB;
};
#define ULIB_FILE_TYPE_XML						1
#define ULIB_FILE_TYPE_INI						2
#define ULIB_FILE_TYPE_JSON						3
extern "C" __declspec(dllimport) int LoadConfig(int iType, string strPath, vector<STPAIR> &v_stPair);
extern "C" __declspec(dllimport) int SaveConfig(int iType, string strPath, vector<STPAIR> &v_stPair);

