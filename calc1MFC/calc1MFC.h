
// calc1MFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ccalc1MFCApp:
// See calc1MFC.cpp for the implementation of this class
//

class Ccalc1MFCApp : public CWinApp
{
public:
	Ccalc1MFCApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ccalc1MFCApp theApp;
