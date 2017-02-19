#pragma once
class CCSoftUpdate
{
public:
	CCSoftUpdate(void);
	~CCSoftUpdate(void);

public:
	CString CheckUrlLink(CString csUrl);
	CString UpdateCheck(CString csFilePath);

protected:
	CCProjectInfo m_clsProIfo;
	CCFtpCtrl m_clsFtp;

	CString m_csServerPath;
	CString m_csLocalPath;

private:
	CString CheckVersion(CString csFileVersion, CString csProName);
};


