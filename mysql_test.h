
// mysql_test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmysql_testApp: 
// �йش����ʵ�֣������ mysql_test.cpp
//

class Cmysql_testApp : public CWinApp
{
public:
	Cmysql_testApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmysql_testApp theApp;