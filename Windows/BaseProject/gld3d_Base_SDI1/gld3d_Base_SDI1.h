
// gld3d_Base_SDI1.h : main header file for the gld3d_Base_SDI1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cgld3d_Base_SDI1App:
// See gld3d_Base_SDI1.cpp for the implementation of this class
//

class Cgld3d_Base_SDI1App : public CWinAppEx
{
public:
	Cgld3d_Base_SDI1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cgld3d_Base_SDI1App theApp;
