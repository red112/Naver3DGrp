
// MRLab_GL2Holo.h : main header file for the PROJECT_NAME application
//

#pragma once


#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMRLab_GL2HoloApp:
// See MRLab_GL2Holo.cpp for the implementation of this class
//

class CMRLab_GL2HoloApp : public CWinAppEx
{
public:
	CMRLab_GL2HoloApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMRLab_GL2HoloApp theApp;