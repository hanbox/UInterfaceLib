#include "StdAfx.h"
#include "CCSoftUpdate.h"

#include "Wininet.h"
#include "Mmsystem.h"
#pragma comment(lib, "winsocklib/WININET.LIB")
#pragma comment(lib, "winsocklib/WINMM.LIB")

#include "afxsock.h" 
#include <afxinet.h> 

CCSoftUpdate::CCSoftUpdate(void)
{
	m_csServerPath = _T("/myfolder/update.db");
	m_csLocalPath = _T("D:\\update.db");
}


CCSoftUpdate::~CCSoftUpdate(void)
{
}

CString CCSoftUpdate::CheckUrlLink(CString csUrl)
{
    DWORD dwFlags;
	InternetGetConnectedState(&dwFlags, 0);
	CString reValue,strContent;
	reValue=_T("Error");
	CHAR strAgent[64];
	memset(strAgent,0,sizeof(strAgent));
	sprintf(strAgent, "Agent%ld", timeGetTime());
	HINTERNET hOpen;
	if(!(dwFlags & INTERNET_CONNECTION_LAN))
		hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
	else
		hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(!hOpen)
	{
		return reValue;
	}

	DWORD dwSize;
	TCHAR   szHead[] = _T("Accept: */*\r\n\r\n");
	VOID* szTemp[16384];
	HINTERNET  hConnect;

	if ( !(hConnect = InternetOpenUrl( hOpen, csUrl, szHead,
		 lstrlen (szHead), INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0)))
	{
		InternetCloseHandle(hOpen);
	    return reValue;
	}

	DWORD dwByteToRead = 0;
	DWORD dwSizeOfRq = 4;
	DWORD dwBytes = 0;

	CString strInfoTemp;

    if (!HttpQueryInfo(hConnect, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, 
                  (LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
	{
		dwByteToRead = 0;
	}


	memset(szTemp,0,sizeof(szTemp));
	do
	{
		if (!InternetReadFile (hConnect, szTemp, 16384,  &dwSize))
		{
			return reValue;
		}
		if (dwSize==0)
		{
			break;
		}
		else
		{
			strInfoTemp.Format(_T("%s"),szTemp);
			strContent+=strInfoTemp;
		}
		
	}while (TRUE);

	InternetCloseHandle(hConnect);
	InternetCloseHandle(hOpen);

	return strContent;
}

CString CCSoftUpdate::UpdateCheck(CString csFilePath)
{
	TCHAR   szFullPath[MAX_PATH]; 
	GetModuleFileName(NULL,   szFullPath,   sizeof(szFullPath)); 
	m_csLocalPath = szFullPath;
	m_csLocalPath = m_csLocalPath.Left(m_csLocalPath.ReverseFind('\\'));
	m_csLocalPath+= _T("\\db\\update.db");

	CString csState;

	CString csFileVersion;
	CString csOriginalFileName;

	CFileFind find;
	if ( find.FindFile(m_csLocalPath) )
	{
		string strError = "";
		CCommTools::GetInstance()->file_remove(CCommTools::GetInstance()->string_W2A(m_csLocalPath), strError);
	}

	if ( m_clsProIfo.GetPrejectInfo(csFilePath) )
	{
		csFileVersion = m_clsProIfo.GetVersion();
		csOriginalFileName = m_clsProIfo.GetOriginalFileName();
		if ( m_clsFtp.Updown(m_csServerPath, m_csLocalPath) )
		{
			csState = CheckVersion(csFileVersion, csOriginalFileName);
		}
	}

	return csState;
}

CString  CCSoftUpdate::CheckVersion(CString csFileVersion, CString csProName)
{
	CString csState = _T("该版本为最新，无需更新！");

	CFileFind find;
	if ( find.FindFile(m_csLocalPath) )
	{
		try
		{
			CppSQLite3DB db;
			db.open(m_csLocalPath);

			CString csSql;
			csSql.Format(_T("select * from USoft"));
			CppSQLite3Query Query = db.execQuery(csSql);
			while ( !Query.eof() )          
			{     
				CString csVersionTmp;
				CString csProductTmp;
				csProductTmp = Query.getStringField(_T("productname"));
				csVersionTmp = Query.getStringField(_T("version"));

				csProName.Trim();
				if ( csProName.Compare(csProductTmp) == 0 )
				{
					if ( csFileVersion.Compare(csVersionTmp) != 0 )
					{
						csState = Query.getStringField(_T("fileurl"));

						break;
					}
				}

				Query.nextRow(); 
			}   
		}
		catch(CppSQLite3Exception e)      
		{          
			TRACE(e.errorMessage());     
		} 
	}

	return csState;
}

boost::shared_ptr<CCSoftUpdate> m_pLink = nullptr;

extern "C" __declspec(dllexport) CString  CheckUrlLink(CString csUrl)
{
	CString csState;

	if ( m_pLink == nullptr )
	{
		m_pLink = boost::shared_ptr<CCSoftUpdate>(new CCSoftUpdate());
	}

	csState = m_pLink->CheckUrlLink(csUrl);

	return csState;
}

extern "C" __declspec(dllexport) CString  UpdateCheck(CString csFilePath)
{
	CString csState;

	if ( m_pLink == nullptr )
	{
		m_pLink = boost::shared_ptr<CCSoftUpdate>(new CCSoftUpdate());
	}

	csState = m_pLink->UpdateCheck(csFilePath);

	return csState;
}
