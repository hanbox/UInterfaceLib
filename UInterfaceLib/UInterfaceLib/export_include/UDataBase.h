#pragma once

#define ULIB_DB_TYPE_SQLITE						1
#define ULIB_DB_TYPE_MYSQL						2
#define ULIB_DB_TYPE_SQLSERVICE			3
#define ULIB_DB_TYPE_MONGODB				4

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

class CDBCtrlBase
{
public:
	CDBCtrlBase(){}
	virtual ~CDBCtrlBase(){}

public:
	virtual int Connect(CString csDB, CString csName = _T(""), CString csPwd =_T("")) = 0;
	virtual int Close() = 0;
	virtual void SelectData() = 0;
	virtual void CtrlData(CString csSql) = 0;
	virtual int ClearTable(CString csTable) = 0;
	virtual int DeleteTable(CString csTable) = 0;
	bool IsOpen()
	{
		return m_bOpen;
	}

protected:
	CString m_csDB;
	bool m_bOpen;
};

class  CDBbase
{
public:
	CDBbase(void);
	~CDBbase(void);

public:
	void SetDBType(int iMode);
	int ConnectDB(CString csDB, CString csName = _T(""), CString csPwd =_T(""));
	int CloseDB();
	int InsertData(CString csSql);
	int ClearTable(CString csDB);
	int SelectData(CFormatData &clsData);

protected:
	boost::shared_ptr<CDBCtrlBase> m_db; 

private:
};

