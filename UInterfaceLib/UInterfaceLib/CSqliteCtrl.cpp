#include "StdAfx.h"
#include "CSqliteCtrl.h"


CSqliteCtrl::CSqliteCtrl(void)
{
	m_csDB = _T("");
	m_bOpen = false;
}


CSqliteCtrl::~CSqliteCtrl(void)
{
}

int CSqliteCtrl::Connect( CString csHost, CString csDB, CString csName /*= _T("")*/, CString csPwd /*=_T("")*/ )
{
	int iRet = -1;
	try
	{
		m_db.open(csDB);
	}
	catch(CppSQLite3Exception e)
	{
		TRACE(e.errorMessage());
		return iRet;
	} 

	m_bOpen = true;
	m_csDB = csDB;
	iRet = true;

	return iRet;
}

int CSqliteCtrl::Connect( CString csDB, CString csName /*= _T("")*/, CString csPwd /*=_T("")*/ )
{
	int iRet = -1;
	try
	{
		m_db.open(csDB);
	}
	catch(CppSQLite3Exception e)
	{
		TRACE(e.errorMessage());
		return iRet;
	} 

	m_bOpen = true;
	m_csDB = csDB;
	iRet = true;

	return iRet;
}

int CSqliteCtrl::CtrlData( CString csSql, CString csDB /*= _T("")*/ )
{
	int iRet = ULIB_FALSE;
	try
	{
		iRet = m_db.execDML(csSql);  
		if (iRet != SQLITE_OK)    
		{  
			return ULIB_FALSE;
		} 
		//db.close(); 

		iRet = ULIB_TRUE;
	}
	catch(CppSQLite3Exception e)
	{          
		TRACE(e.errorMessage());     
	} 

	return iRet;
}

int CSqliteCtrl::Close()
{
	int iRet  = -1;

	if( m_bOpen )
	{
		m_db.close();
		m_bOpen = false;
		iRet = true;
	}

	return iRet;
}

int CSqliteCtrl::DeleteTable( CString csTable, CString csDB /*= _T("")*/ )
{
	int nRes = -1;

	try
	{
		CString csSql;
		csSql.Format(_T("drop table %s"), csTable);
		nRes = m_db.execDML(csSql);  
		if (nRes != SQLITE_OK)    
		{  
			return nRes;
		} 
		//db.close(); 
	}
	catch(CppSQLite3Exception e)      
	{          
		TRACE(e.errorMessage());     
	} 

	return nRes;
}

int CSqliteCtrl::SelectData( CFormatData &clsData, CString csDB )
{
	int nRes = ULIB_FALSE;

	try
	{
		CString csSql;
		csSql.Format(_T("select * from %s"), clsData.m_csTable);
		CppSQLite3Query Query = m_db.execQuery(csSql);
		while ( !Query.eof() )          
		{     
			for ( int i = 0; i < clsData.m_vField.size(); i++ )
			{
				STDBDATA stData;
				stData.csTitle = clsData.m_vField[i];
				stData.csData = Query.getStringField(clsData.m_vField[i]);
				clsData.m_vData.push_back(stData);
			}

			Query.nextRow(); 
		}   

		nRes = ULIB_TRUE;
	}
	catch(CppSQLite3Exception e)      
	{          
		TRACE(e.errorMessage());     
	} 

	return nRes;
}

int CSqliteCtrl::ClearTable( CString csTable, CString csDB /*= _T("")*/ )
{
	int nRes = -1;

	try
	{
		CString csSql;
		csSql.Format(_T("delete from %s"), csTable);
		nRes = m_db.execDML(csSql);  
		if (nRes != SQLITE_OK)    
		{  
			return nRes;
		} 
		//db.close(); 
	}
	catch(CppSQLite3Exception e)      
	{          
		TRACE(e.errorMessage());     
	} 

	return nRes;
}
