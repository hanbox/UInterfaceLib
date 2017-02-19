#include "StdAfx.h"
#include "CCFileXml.h"


CCFileXml::CCFileXml(void)
{
}


CCFileXml::~CCFileXml(void)
{
}

int CCFileXml::InitFile(string strPath)
{
	int iRet = 0;

	string strError = "";
	if ( CCommTools::GetInstance()->file_exist(strPath, strError) == ULIB_RETURN_FALSE )
	{
		std::ofstream file(strPath);  
	}

	boost::property_tree::read_xml(strPath, m_clsPt);
	m_strPath = strPath;

	return iRet;
}

string CCFileXml::Get(string strA, string strB)  
{
	string strC = "";

	ptree ptChild = m_clsPt.get_child(strA);
	strC = ptChild.get<string>(strB);

	ptChild.clear();

	return strC;
}

void CCFileXml::Add(string strA, string strB, string strC)
{
	ptree ptChild;
	ptChild.put(strB, strC);
	m_clsPt.add_child(strA, ptChild);
}

void CCFileXml::Add( vector<STPAIR> v_stPair )
{
	ptree ptChild;
	for ( int i = 0; i < v_stPair.size(); i++ )
	{
		ptChild.put(v_stPair[i].strA, v_stPair[i].strB);
	}
	m_clsPt.add_child(v_stPair[0].strTitle, ptChild);
}

void CCFileXml::WriteFile(string strPath)
{
	write_xml(strPath, m_clsPt);
}

void CCFileXml::ClearnFile()
{
	m_clsPt.clear();
}
