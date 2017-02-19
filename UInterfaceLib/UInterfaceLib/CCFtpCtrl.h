#pragma once

#include <afxinet.h>

class CCFtpCtrl
{
public:
	CCFtpCtrl(void);
	~CCFtpCtrl(void);
	int Login();
	int ConnectFtp(CString csAddr, CString csName, CString csPwd, CString csPort = _T("21"));
	void StopConnect();
	bool Updown(CString csSrcPath, CString csDesPath);
	
protected:
	boost::shared_ptr<CInternetSession>  m_pInetSession;
	boost::shared_ptr<CFtpConnection>    m_pFtpConnection;
	boost::shared_ptr<CInternetFile> m_pRemoteFile;

private:
	void CloseRemoteFile();
};

