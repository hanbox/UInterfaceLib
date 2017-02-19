// UiCommTools.h : main header file for the UiCommTools DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUiCommToolsApp
// See UiCommTools.cpp for the implementation of this class
//

class CUiCommToolsApp : public CWinApp
{
public:
	CUiCommToolsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
