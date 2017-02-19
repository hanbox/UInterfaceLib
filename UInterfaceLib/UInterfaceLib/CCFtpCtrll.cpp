#include "StdAfx.h"
#include "CCFtpCtrl.h"


CCFtpCtrl::CCFtpCtrl(void)
	:m_pInetSession(new CInternetSession( AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS))
{
	
}


CCFtpCtrl::~CCFtpCtrl(void)
{
}

int CCFtpCtrl::ConnectFtp(CString csAddr, CString csName, CString csPwd, CString csPort)
{
	int iRet = ULIB_FALSE;

	try
	{
		m_pFtpConnection =  boost::shared_ptr<CFtpConnection>(m_pInetSession->GetFtpConnection(csAddr, csName, csPwd, _wtoi(csPort)));
	}
	catch(CInternetException *pEx)
	{
		TCHAR szError[1024] = {0x00};
		if(pEx->GetErrorMessage(szError,1024))
			AfxMessageBox(szError);
		else
			AfxMessageBox(_T("There was an exception"));
		pEx->Delete();
		m_pFtpConnection = NULL;
		return iRet;
	}

	return ULIB_TRUE;
}

int CCFtpCtrl::Login()
{
	return this->ConnectFtp(_T("www.forour.club"), _T("qxu1591330106"), _T("900316asd"));
}

void CCFtpCtrl::StopConnect()
{
	if(m_pFtpConnection != NULL)
	{
		m_pFtpConnection->Close();
	}
}

bool CCFtpCtrl::Updown (CString csSrcPath, CString csDesPath)
{  
	LPBYTE pBuffer = new BYTE[1024 * 1024];  
	memset(pBuffer, 0, 1024 * 1024);  

	CFile clsfile;  

	try  
	{  
		if (m_pFtpConnection == NULL)  
		{  
			if ( Login() != ULIB_TRUE )  
			{  
				return false;  
			}  
		}  

		if( !clsfile.Open(csDesPath, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))  
		{  
			//TRACE(csSrcPath + "  :文件创建失败");  
			return false;
		}

		m_pRemoteFile =  boost::shared_ptr<CInternetFile>(m_pFtpConnection->OpenFile(csSrcPath, GENERIC_READ));  
		if(m_pRemoteFile == NULL)  
		{  
			//AfxMessageBox(str_remoteFileName + "  :远程文件打开失败");  
			return false;  
		}  

		DWORD dRead = 0;  
		while( (dRead = m_pRemoteFile->Read( pBuffer, m_pRemoteFile->GetLength())) > 0  )   
		{  
			clsfile.Write( pBuffer, dRead );  
		}  

		clsfile.Close();  
	}  
	catch(CInternetException *pEx)  
	{  
		TCHAR szError[1024] = {0x00};
		pEx->GetErrorMessage( szError, 1024 );  
		pEx->Delete();  

		clsfile.Close();  
		return false;  
	}  
	catch (...)  
	{  
		clsfile.Close();  
		return false;  
	}  

	delete pBuffer;  
	pBuffer = nullptr;
	CloseRemoteFile();  

	return true;  
}  

void CCFtpCtrl::CloseRemoteFile()  
{  
	try  
	{  
		if(m_pRemoteFile)  
		{  
			m_pRemoteFile->Close();  
		}  
	}  
	catch(CInternetException *pEx)  
	{  
		TCHAR szError[1024] = {0x00};
		pEx->GetErrorMessage( szError, 1024 );  
		pEx->Delete();  
	}  
}  
