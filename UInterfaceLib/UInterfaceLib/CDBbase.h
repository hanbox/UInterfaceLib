#pragma once

struct STDBDATA
{
	CString csTitle;
	CString csData;
};

class CFormatData
{
public:
	CFormatData(){}
	~CFormatData(){}
	vector<CString> m_vField;
	vector<STDBDATA> m_vData;
	CString m_csTable;

public:

protected:

private:
};

class __declspec(dllexport) CDBCtrlBase
{
public:
	CDBCtrlBase(){}
	virtual ~CDBCtrlBase(){}

public:
	virtual int Connect(CString csHost, CString csDB, CString csName, CString csPwd) = 0;
	virtual int Connect(CString csDB, CString csName, CString csPwd) = 0;
	virtual int Close() = 0;
	virtual int SelectData(CFormatData &clsData, CString csDB = _T("")) = 0;
	virtual int CtrlData(CString csSql, CString csDB = _T("")) = 0;
	virtual int ClearTable(CString csTable, CString csDB = _T("")) = 0;
	virtual int DeleteTable(CString csTable, CString csDB = _T("")) = 0;
	virtual bool IsOpen()
	{
		return m_bOpen;
	}

protected:
	CString m_csDB;
	bool m_bOpen;
};

class __declspec(dllexport) CDBbase
{
public:
	CDBbase(void);
	~CDBbase(void);

public:
	void SetDBType(int iMode);
	int ConnectDB(CString csDB, CString csName = _T(""), CString csPwd =_T(""));
	int Connect(CString csHost, CString csDB, CString csName, CString csPwd);
	int CloseDB();
	int InsertData(CString sql);
	int ClearTable(CString csDB);
	int SelectData(CFormatData &clsData);
	int GetDBType();

protected:
	boost::shared_ptr<CDBCtrlBase> m_db; 
	int m_iDBType;

private:
};

