#pragma once
class CSqliteCtrl : public CDBCtrlBase
{
public:
	CSqliteCtrl(void);
	~CSqliteCtrl(void);

public:
	virtual int Connect(CString csHost, CString csDB, CString csName, CString csPwd);
	virtual int Connect(CString csDB, CString csName, CString csPwd);
	virtual int Close();
	virtual int SelectData(CFormatData &clsData, CString csDB = _T(""));
	virtual int CtrlData(CString csSql, CString csDB = _T(""));
	virtual int ClearTable(CString csTable, CString csDB = _T(""));
	virtual int DeleteTable(CString csTable, CString csDB = _T(""));

protected:
	CppSQLite3DB m_db;

private:

};

