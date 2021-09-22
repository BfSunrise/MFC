
// 2020619004温国亮.h: 2020619004温国亮 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CMy2020619004温国亮App:
// 有关此类的实现，请参阅 2020619004温国亮.cpp
//

class CMy2020619004温国亮App : public CWinApp
{
public:
	CMy2020619004温国亮App() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy2020619004温国亮App theApp;
