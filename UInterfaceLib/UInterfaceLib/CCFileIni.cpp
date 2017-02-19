#include "StdAfx.h"
#include "CCFileIni.h"


CCFileIni::CCFileIni(void)
{
}


CCFileIni::~CCFileIni(void)
{
}

int CCFileIni::InitFile(string strPath)
{
	int iRet = 0;

	string strError = "";
	if ( CCommTools::GetInstance()->file_exist(strPath, strError) == ULIB_RETURN_FALSE )
	{
		std::ofstream file(strPath);  
	}

	m_strPath = strPath;

	return iRet;
}

string CCFileIni::Get(string strTitle, string strA)
{
	string strC = "";

	CString csRet;
	::GetPrivateProfileString(CCommTools::GetInstance()->string_A2W(strTitle.c_str(), strTitle.length()), 
							CCommTools::GetInstance()->string_A2W(strA.c_str(), strA.length()), 
							_T("Default"),
							csRet.GetBuffer(MAX_PATH), 
							MAX_PATH, 
							CCommTools::GetInstance()->string_A2W(m_strPath.c_str(), m_strPath.length()));
	strC = CCommTools::GetInstance()->string_W2A(csRet);

	return strC;
}

void CCFileIni::Add(string strA, string strB, string strC)
{
	::WritePrivateProfileString(CCommTools::GetInstance()->string_A2W(strA.c_str(), strA.length()), 
								CCommTools::GetInstance()->string_A2W(strB.c_str(), strB.length()), 
								CCommTools::GetInstance()->string_A2W(strC.c_str(), strC.length()), 
								CCommTools::GetInstance()->string_A2W(m_strPath.c_str(), m_strPath.length()));
}

void CCFileIni::Add( vector<STPAIR> v_stPair )
{

}

void CCFileIni::WriteFile(string strPath)
{
	
}

void CCFileIni::ClearnFile()
{
	
}
