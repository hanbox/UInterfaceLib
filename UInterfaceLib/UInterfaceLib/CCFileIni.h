#pragma once
#include "cconfigbase.h"

class CCFileIni :
	public CCFileBase
{
public:
	CCFileIni(void);
	~CCFileIni(void);

public:
	virtual int InitFile(string strPath);
	virtual string Get(string strA, string strB);
	virtual void Add(string strA, string strB, string strC);
	virtual void Add(vector<STPAIR> v_stPair);
	virtual void WriteFile(string strPath);
	virtual void ClearnFile();

protected:
	string m_strPath;

private:

};

