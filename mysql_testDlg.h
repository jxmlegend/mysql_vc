
// mysql_testDlg.h : ͷ�ļ�
//

#pragma once
#include "student_data.h"
#include "afxwin.h"
#include "afxcmn.h"

// Cmysql_testDlg �Ի���
class Cmysql_testDlg : public CDialogEx
{
// ����
public:
	Cmysql_testDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYSQL_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public: 
		//CListBox m_listBox;
	   // CListCtrl m_ListCtrl;
	    Student_DataManager m_sqltest;
		void GetInputData(Student & stu);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
