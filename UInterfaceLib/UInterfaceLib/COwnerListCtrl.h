#pragma once
#include "afxcmn.h"
class COwnerListCtrl :
	public CListCtrl
{
public:
	COwnerListCtrl(void);
	~COwnerListCtrl(void);

protected:
	void SetItemHeight( int nHeight );
	void MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	DWORD SetExtendedStyle( DWORD dwNewStyle );

private:
	int m_iHeightItem;
};

