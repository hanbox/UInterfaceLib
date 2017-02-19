#pragma once

#define ULIB_FILE_TYPE_XML						1
#define ULIB_FILE_TYPE_INI						2
#define ULIB_FILE_TYPE_JSON						3

struct STPAIR 
{
	string strTitle;
	string strA;
	string strB;
};

class CCFileBase
{
public:
	CCFileBase(){}
	~CCFileBase(){}

public:
	virtual int InitFile(string strPath) = 0;
	virtual string Get(string strA, string strB) = 0;
	virtual void Add(string strA, string strB, string strC) = 0;
	virtual void Add(vector<STPAIR> v_stPair) = 0;
	virtual void WriteFile(string strPath) = 0;
	virtual void ClearnFile() = 0;

protected:
	string m_strPath;

private:

};

class CConfigBase
{
public:
	CConfigBase(void);
	~CConfigBase(void);

public:
	int LoadConfig(string strPath, vector<STPAIR> &v_stPair);
	int SaveConfig(string strPath, vector<STPAIR> v_stPair);
	boolean SetFileType(int iType);

protected:
	boost::shared_ptr<CCFileBase> m_pFile;
	string m_strPath;
	int m_iType;

private:

};

