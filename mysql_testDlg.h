
// mysql_testDlg.h : 头文件
//

#pragma once
#include "student_data.h"
#include "afxwin.h"
#include "afxcmn.h"

// Cmysql_testDlg 对话框
class Cmysql_testDlg : public CDialogEx
{
// 构造
public:
	Cmysql_testDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYSQL_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public: 
		//CListBox m_listBox;
	   // CListCtrl m_ListCtrl;
	    Student_DataManager m_sqltest;
		void GetInputData(Student & stu);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	
	CListCtrl m_ListCtrl;
};
