// UInterfaceLib.h : main header file for the UInterfaceLib DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUInterfaceLibApp
// See UInterfaceLib.cpp for the implementation of this class
//

class CUInterfaceLibApp : public CWinApp
{
public:
	CUInterfaceLibApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
