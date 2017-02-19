#include "StdAfx.h"
#include "CDBbase.h"


CDBbase::CDBbase(void)
{
}


CDBbase::~CDBbase(void)
{
}


void CDBbase::SetDBType(int iType)
{
	if ( iType == 1 )
	{
		m_db = boost::shared_ptr<CDBCtrlBase>(new CSqliteCtrl());
	}
	else if ( iType == 2 )
	{

	}
}

int CDBbase::InsertData(CString csSql)
{
	int iRet = -1;
	if ( !m_db )
	{
		return iRet;
	}

	iRet = m_db->CtrlData(csSql);

	return iRet;
}

int CDBbase::ConnectDB(CString csDB, CString csName, CString csPwd)
{
	int iRet = -1;
	if ( !m_db )
	{
		return iRet;
	}

	iRet = m_db->Connect(csDB, csName, csPwd);
	
	return iRet;
}

int CDBbase::CloseDB()
{
	int iRet = -1;

	if ( !m_db )
	{
		return iRet;
	}

	iRet = m_db->Close();

	return iRet;
}

int CDBbase::ClearTable(CString csTable)
{
	int iRet = -1;

	if ( !m_db )
	{
		return iRet;
	}

	iRet = m_db->ClearTable(csTable);

	return iRet;
}

int CDBbase::SelectData(CFormatData &clsData)
{
	int iRet = -1;

	if ( !m_db )
	{
		return iRet;
	}

	if ( clsData.m_vField.size() > 0 && !clsData.m_csTable.IsEmpty() )
	{
		iRet = m_db->SelectData(clsData);
	}

	return iRet;
}

int CDBbase::Connect( CString csHost, CString csDB, CString csName, CString csPwd )
{
	int iRet = -1;

	if ( m_iDBType == 1 )
	{
		if ( !m_db )
		{
			return iRet;
		}

		iRet = m_db->Connect(csHost, csName, csPwd);
	}

	return iRet;
}
