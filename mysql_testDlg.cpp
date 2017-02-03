
// mysql_testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mysql_test.h"
#include "mysql_testDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmysql_testDlg 对话框



Cmysql_testDlg::Cmysql_testDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmysql_testDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmysql_testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(Cmysql_testDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cmysql_testDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cmysql_testDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cmysql_testDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cmysql_testDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// Cmysql_testDlg 消息处理程序

BOOL Cmysql_testDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	LONG lStyle;
	lStyle = GetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_ListCtrl.SetExtendedStyle(dwStyle); //设置扩展风格

	m_ListCtrl.InsertColumn(0, _T("学号"), LVCFMT_CENTER, 100, -10);
	m_ListCtrl.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 100, -10);
	m_ListCtrl.InsertColumn(2, _T("性别"), LVCFMT_CENTER, 100, -10);
	m_ListCtrl.InsertColumn(3, _T("出生年月"), LVCFMT_CENTER, 150, -10);
	//int nRow = m_ListCtrl.InsertItem(0, L"");//插入行
	//nRow = m_ListCtrl.InsertItem(2, L"11");//插入行
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cmysql_testDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cmysql_testDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cmysql_testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//获取输入数据
void Cmysql_testDlg::GetInputData(Student & stu)
{
	GetDlgItem(IDC_EDIT_ID)->GetWindowText(stu.student_id);
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(stu.name_);
	GetDlgItem(IDC_EDIT_SEX)->GetWindowText(stu.sex_);
	GetDlgItem(IDC_EDIT_BIRTH)->GetWindowText(stu.birth_);
}

//删除数据
void Cmysql_testDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	Student stu_temp;
	GetInputData(stu_temp);
	if (m_sqltest.DeleteData(&stu_temp))
	{
		AfxMessageBox(L"删除数据成功");
	}
	else
	{
		AfxMessageBox(L"删除数据失败");
	}
}

//插入数据
void Cmysql_testDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	Student stu_temp;
	GetInputData(stu_temp);
	if (m_sqltest.InsertData(&stu_temp))
	{
		AfxMessageBox(L"插入数据成功");
	}
	else
	{
		AfxMessageBox(L"插入数据失败");
	}
	
}

//更新数据
void Cmysql_testDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	Student stu_temp;
	GetInputData(stu_temp);
	if (m_sqltest.UpdateData(&stu_temp))
	{
		AfxMessageBox(L"更新数据成功");
	}
	else
	{
		AfxMessageBox(L"更新数据失败");
	}
}

//查询数据
void Cmysql_testDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	Student stu_temp;
	GetInputData(stu_temp);
	vector<Student*>stutab;
	if (m_sqltest.SelectData(&stu_temp, stutab))
	{
		
		int nRow = 0;
		for (int i = 0; i<stutab.size();i++)
		{
			nRow = m_ListCtrl.InsertItem(0, L"");//插入行
			m_ListCtrl.SetItemText(nRow, 0, stutab.at(i)->student_id);//设置数据
			m_ListCtrl.SetItemText(nRow, 1, stutab.at(i)->name_);//设置数据
			m_ListCtrl.SetItemText(nRow, 2, stutab.at(i)->sex_);//设置数据
			m_ListCtrl.SetItemText(nRow, 3, stutab.at(i)->birth_);//设置数据
			
		}
		for (int i = 0; i < stutab.size(); i++)
		{
			delete  stutab.at(i);
		}
		stutab.clear();
		AfxMessageBox(L"查询数据成功");
	}
	else
	{
		AfxMessageBox(L"查询数据失败");
	}
}
