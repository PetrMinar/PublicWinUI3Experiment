#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

class CMFCWinUI3App : public CWinApp
{
public:
	CMFCWinUI3App() noexcept;

public:
	BOOL InitInstance() override;
	int ExitInstance() override;
	BOOL PreTranslateMessage(MSG* pMsg) override;
public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCWinUI3App theApp;
