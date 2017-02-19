#pragma once

#ifndef SAFE_RELEASE
#define SAFE_RELEASE( x ) \
	if ( NULL != x ) \
{ \
	x->Release( ); \
	x = NULL; \
}
#endif

class  __declspec(dllexport) CCommTools
{
public:
	static CCommTools *GetInstance()
	{
		if ( m_Instance == nullptr )
		{
			m_Instance = new CCommTools();
		}

		return m_Instance;
	}

	static void RealeaseInstance()
	{
		delete m_Instance;
		m_Instance = nullptr;
	}

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
	WCHAR*string_A2W(const char *pstr, int iStrlen);
	char* string_W2UTF8(CString csBuffer);
	char* string_Encode2UTF8(const char* mbcsStr);
	CString string_ucharformat(unsigned char *pBuf, int iMode, int iLen);
	unsigned char *string_W2Byte(CString csframe);
	template<class T>
	void to_string(string & result,const T& t);
	template<class out_type, class in_value>
	out_type string_convert(const in_value & t);

	/** imagedealctrl */
	void imagedeal_closewindow(char *title);
	bool imagedeal_ispic(CString csType);
	void imagedeal_openpicdlg(CStringArray &csPath, int iCount = 0);
	int imagedeal_angle(CPoint center, CPoint startPoint, CPoint desPooint);
	int imagedeal_direction(CPoint startPoint, CPoint endPoint, CPoint cenPoint);

	/** windowsctrl */
	ULIB_RETURN windows_getmac(vector<CString> &v_mac);
	ULIB_RETURN windows_openURL(CString csUrl);
	void windows_filedlg(CString csFileFilter, CStringArray &csPath);
	void windows_transparentwnd(HWND hWnd,COLORREF clr,BYTE byAlpha,DWORD dwFlags);
	void windows_show2List(CListBox *pList, CString csMessage);
	void windows_setfont(CFont *pfont, long lHeight, CString csFaceName);
	void windows_setfont(CFont *pfont, long lHeight, long lWeight, CString csFaceName);

	/** pathctrl */
	ULIB_RETURN path_filename(string strPath, string &strfilename);
	ULIB_RETURN path_extension(string strPath, string &strextension);
	ULIB_RETURN path_stem(string strPath, string &strstem);
	ULIB_RETURN path_withoutfilename(string strPath, string &strDesPath);

	/** filectrl */
	ULIB_RETURN file_exist(string strPath, string &strError);
	ULIB_RETURN file_currentpath(string &strcurrentpath, string &strError);
	ULIB_RETURN file_remove(string strPath, string &strError);
	ULIB_RETURN file_creat(string strPath, string &strError);
	ULIB_RETURN file_initialpath(string &strcurrentpath, string &strError);

protected:

private:
	CCommTools(void){}
	~CCommTools(void){}
	static CCommTools* m_Instance;
};

