#pragma once
#include "cconfigbase.h"
#include "boost/property_tree/ptree.hpp"
#include <boost/property_tree/xml_parser.hpp>  

using namespace boost::property_tree;

class CCFileXml :
	public CCFileBase
{
public:
	CCFileXml(void);
	~CCFileXml(void);

public:
	virtual int InitFile(string strPath);
	virtual string Get(string strA, string strB);
	virtual void Add(string strA, string strB, string strC);
	virtual void Add(vector<STPAIR> v_stPair);
	virtual void WriteFile(string strPath);
	virtual void ClearnFile();

protected:
	ptree m_clsPt;

private:
};

