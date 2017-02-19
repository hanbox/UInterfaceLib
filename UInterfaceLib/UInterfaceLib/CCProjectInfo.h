#pragma once
class CCProjectInfo
{
public:
	CCProjectInfo(void);
	~CCProjectInfo(void);

public:
	bool GetPrejectInfo(CString csFilePath);
	CString GetVersion()
	{
		return m_csVersion;
	}
	CString GetOriginalFileName()
	{
		return m_csOriginalFileName;
	}
	CString GetProductName()
	{
		return m_csProductName;
	}

protected:
	CString m_csVersion;
	CString m_csOriginalFileName;
	CString m_csProductName;
	CString m_csLan;

private:
};

