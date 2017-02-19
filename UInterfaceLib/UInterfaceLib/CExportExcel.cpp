#include "StdAfx.h"
#include <comutil.h>

CExportExcel::CExportExcel(void)
{
	m_iExtraSheetsNum = 0;
	m_iMode = 0;
}


CExportExcel::~CExportExcel(void)
{

}

void CExportExcel::InitExcel()
{
	if (!m_exlApp.CreateDispatch(_T("Excel.Application"), NULL))  
	{  
		AfxMessageBox(_T("创建Excel服务失败!"));   
		return;   
	}  

	m_exlApp.put_Visible(TRUE);  
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  
	m_exlBooks.AttachDispatch(m_exlApp.get_Workbooks());  
	m_exlBook = m_exlBooks.Add(covOptional);  
	m_exlSheets.AttachDispatch(m_exlBook.get_Sheets(), TRUE);  
}

void CExportExcel::SetExtraNum(int iNum)
{
	m_iExtraSheetsNum = iNum;
}

void CExportExcel::SetExportMode(int iMode)
{
	m_iMode = iMode;
}

void CExportExcel::InitExportToExcel(CFormatData clsData)
{
	//if ( m_iExtraSheetsNum > 0 )
	//{
	//	m_exlSheets.Add(vtMissing, vtMissing, _variant_t((long)m_iExtraSheetsNum),vtMissing);  
	//}

	this->ShowExcel(clsData);

	//加载已使用的单元格   
	m_exlRge.AttachDispatch(m_exlSheet.get_UsedRange());
}

void CExportExcel::Realease()
{
	m_exlRge.ReleaseDispatch();   
	m_exlSheet.ReleaseDispatch();   
	m_exlSheets.ReleaseDispatch();   
	m_exlBook.ReleaseDispatch();   
	m_exlBooks.ReleaseDispatch();   
	//m_ExlApp一定要释放，否则程序结束后还会有一个Excel进程驻留在内存中，而且程序重复运行的时候会出错   
	m_exlApp.ReleaseDispatch();   
}

void CExportExcel::ShowExcel(CFormatData clsData)
{
	// TODO: Add your control notification handler code here
	m_exlSheet.AttachDispatch(m_exlSheets.get_Item(_variant_t((long)(1))),TRUE);   
	m_exlSheet.put_Name(clsData.m_csTable);  
	m_exlRge.AttachDispatch(m_exlSheet.get_Cells(),TRUE);

	for ( int i = 0; i < clsData.m_vField.size(); i++ )
	{
		//char *title = new char[10];
		//sprintf_s(title, 10, "第%d列", i + 1);
		m_exlRge.put_Item(_variant_t((long)1),_variant_t((long) i+ 1),_variant_t(clsData.m_vField[i]));   
	}

	long nRow = 2;  

	for ( int j = 0; j < clsData.m_vField.size(); j++)
	{
		nRow = 2;
		for ( int i = 0; i < clsData.m_vData.size(); i++ )
		{
			if ( clsData.m_vData[i].csTitle.Compare(clsData.m_vField[j]) == 0 )
			{
				m_exlRge.put_Item(_variant_t(nRow),_variant_t((long)j + 1),_variant_t(clsData.m_vData[i].csData)); 
				++nRow;  
			}
		}
	}
}

CExportExcel *m_ex = nullptr;

extern "C" __declspec(dllexport) void  InitExcel(CFormatData clsData)
{
	if ( m_ex == nullptr )
	{
		m_ex = new CExportExcel();
	}

	m_ex->InitExcel();
	m_ex->InitExportToExcel(clsData);
	m_ex->Realease();
}

extern "C" __declspec(dllexport) void  ReleaseExcel()
{
	if ( m_ex != nullptr )
	{
		delete m_ex;
		m_ex = nullptr;
	}
}
