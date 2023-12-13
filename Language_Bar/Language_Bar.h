
// Language_Bar.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CLanguageBarApp:
// See Language_Bar.cpp for the implementation of this class
//

class CLanguageBarApp : public CWinApp
{
public:
	int x;
	int y;
public:
	CLanguageBarApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CLanguageBarApp theApp;
