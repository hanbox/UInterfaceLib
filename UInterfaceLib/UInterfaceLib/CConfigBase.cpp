#include "StdAfx.h"
#include "CConfigBase.h"


CConfigBase::CConfigBase(void)
{
}


CConfigBase::~CConfigBase(void)
{
}

int CConfigBase::LoadConfig(string strPath, vector<STPAIR> &v_stPair)
{
	int iRet = ULIB_FALSE;

	

	m_strPath = strPath;

	iRet = m_pFile->InitFile(strPath);
	for ( int i = 0; i < v_stPair.size(); i++ )
	{
		string strData = m_pFile->Get(v_stPair[i].strTitle, v_stPair[i].strA);
		v_stPair[i].strB = strData;
	}

	return iRet;
}

int CConfigBase::SaveConfig(string strPath, vector<STPAIR> v_stPair)
{
	int iRet = ULIB_FALSE;

	m_pFile->InitFile(strPath);
	m_pFile->ClearnFile();

	m_pFile->Add(v_stPair);

	m_pFile->WriteFile(strPath);
	
	return iRet;
}

boolean CConfigBase::SetFileType(int iType)
{
	boolean bRet = true;
	m_iType = iType;

	if ( iType == ULIB_FILE_TYPE_XML )
	{
		m_pFile =  boost::shared_ptr<CCFileBase>(new CCFileXml());
	}
	else if (  iType == ULIB_FILE_TYPE_INI )
	{
		m_pFile =  boost::shared_ptr<CCFileBase>(new CCFileIni());
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

boost::shared_ptr<CConfigBase> m_pConfig = nullptr;

extern "C" __declspec(dllexport) int LoadConfig(int iType, string strPath, vector<STPAIR> &v_stPair)
{
	if ( m_pConfig == nullptr )
	{
		m_pConfig = boost::shared_ptr<CConfigBase>(new CConfigBase());
	}

	m_pConfig->SetFileType(iType);
	int iRet = m_pConfig->LoadConfig(strPath, v_stPair);

	return iRet;
}

extern "C" __declspec(dllexport) int SaveConfig(int iType, string strPath, vector<STPAIR> &v_stPair)
{
	if ( m_pConfig == nullptr )
	{
		m_pConfig = boost::shared_ptr<CConfigBase>(new CConfigBase());
	}

	m_pConfig->SetFileType(iType);
	int iRet = m_pConfig->SaveConfig(strPath, v_stPair);

	return iRet;
}