#include "StdAfx.h"
#include "CCProjectInfo.h"

#pragma   comment(lib, "Version.lib ")

CCProjectInfo::CCProjectInfo(void)
{
}


CCProjectInfo::~CCProjectInfo(void)
{
}

bool CCProjectInfo::GetPrejectInfo(CString csFilePath)
{
	bool bRet = false;

	if ( csFilePath.IsEmpty() )
	{
		return bRet;
	}

	DWORD   dwVerInfoSize   =   GetFileVersionInfoSize(csFilePath,  NULL);
	if (dwVerInfoSize) 
	{ 
		char* pVerValue = nullptr;
		HANDLE     hMem = nullptr; 
		LPVOID     lpvMem = nullptr; 
		UINT   uInfoSize   =   0; 

		hMem   =   GlobalAlloc(GMEM_MOVEABLE,   dwVerInfoSize); 
		lpvMem   =   GlobalLock(hMem); 
		if ( !GetFileVersionInfo(csFilePath,  NULL, dwVerInfoSize,   lpvMem) )
		{
			return bRet;
		}

		if ( !::VerQueryValue(lpvMem,   _T( "\\VarFileInfo\\Translation"),   (LPVOID*)&pVerValue,   &uInfoSize) )
		{
			return bRet;
		}

		CString csTranslation;
		CString csTemp; 
		if ( pVerValue!= nullptr )
		{
			csTemp.Format(_T("000%x"),*((unsigned short int *)pVerValue)); 
			csTranslation = csTemp.Right(4); 
			csTemp.Format(_T("000%x"),*((unsigned short int *)&pVerValue[2])); 
			csTranslation += csTemp.Right(4); 
		}
		m_csLan = csTranslation;

		//工程名获取
		pVerValue = nullptr;
		CString csSubBlock;
		csSubBlock.Format(_T("\\StringFileInfo\\%s\\ProductName"), csTranslation); 
		if ( !::VerQueryValue(lpvMem, csSubBlock, (LPVOID*)&pVerValue,   &uInfoSize) )
		{
			return bRet;
		}

		if ( pVerValue!= nullptr )
		{
			m_csProductName.Format(_T( "%s "), pVerValue); 
		}

		//原始工程名获取
		pVerValue = nullptr;
		csSubBlock.Format(_T("\\StringFileInfo\\%s\\OriginalFileName"), csTranslation); 
		if ( !::VerQueryValue(lpvMem, csSubBlock, (LPVOID*)&pVerValue,   &uInfoSize) )
		{
			return bRet;
		}

		if ( pVerValue!= nullptr )
		{
			m_csOriginalFileName.Format(_T( "%s "), pVerValue); 
		}

		//版本号获取
		pVerValue = nullptr;
		csSubBlock.Format(_T("\\StringFileInfo\\%s\\ProductVersion"), csTranslation); 
		if ( !::VerQueryValue(lpvMem, csSubBlock, (LPVOID*)&pVerValue,   &uInfoSize) )
		{
			return bRet;
		}

		if ( pVerValue!= nullptr )
		{
			m_csVersion.Format(_T( "%s "), pVerValue); 
		}

		GlobalUnlock(hMem); 
		GlobalFree(hMem); 

		bRet = true;
	}

	return bRet;
}