
// mysql_testDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mysql_test.h"
#include "mysql_testDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cmysql_testDlg �Ի���



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


// Cmysql_testDlg ��Ϣ�������

BOOL Cmysql_testDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	LONG lStyle;
	lStyle = GetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_ListCtrl.SetExtendedStyle(dwStyle); //������չ���

	m_ListCtrl.InsertColumn(0, _T("ѧ��"), LVCFMT_CENTER, 100, -10);
	m_ListCtrl.InsertColumn(1, _T("����"), LVCFMT_CENTER, 100, -10);
	m_ListCtrl.InsertColumn(2, _T("�Ա�"), LVCFMT_CENTER, 100, -10);
	m_ListCtrl.InsertColumn(3, _T("��������"), LVCFMT_CENTER, 150, -10);
	//int nRow = m_ListCtrl.InsertItem(0, L"");//������
	//nRow = m_ListCtrl.InsertItem(2, L"11");//������
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cmysql_testDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cmysql_testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��ȡ��������
void Cmysql_testDlg::GetInputData(Student & stu)
{
	GetDlgItem(IDC_EDIT_ID)->GetWindowText(stu.student_id);
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(stu.name_);
	GetDlgItem(IDC_EDIT_SEX)->GetWindowText(stu.sex_);
	GetDlgItem(IDC_EDIT_BIRTH)->GetWindowText(stu.birth_);
}

//ɾ������
void Cmysql_testDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Student stu_temp;
	GetInputData(stu_temp);
	if (m_sqltest.DeleteData(&stu_temp))
	{
		AfxMessageBox(L"ɾ�����ݳɹ�");
	}
	else
	{
		AfxMessageBox(L"ɾ������ʧ��");
	}
}

//��������
void Cmysql_testDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Student stu_temp;
	GetInputData(stu_temp);
	if (m_sqltest.InsertData(&stu_temp))
	{
		AfxMessageBox(L"�������ݳɹ�");
	}
	else
	{
		AfxMessageBox(L"��������ʧ��");
	}
	
}

//��������
void Cmysql_testDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Student stu_temp;
	GetInputData(stu_temp);
	if (m_sqltest.UpdateData(&stu_temp))
	{
		AfxMessageBox(L"�������ݳɹ�");
	}
	else
	{
		AfxMessageBox(L"��������ʧ��");
	}
}

//��ѯ����
void Cmysql_testDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Student stu_temp;
	GetInputData(stu_temp);
	vector<Student*>stutab;
	if (m_sqltest.SelectData(&stu_temp, stutab))
	{
		
		int nRow = 0;
		for (int i = 0; i<stutab.size();i++)
		{
			nRow = m_ListCtrl.InsertItem(0, L"");//������
			m_ListCtrl.SetItemText(nRow, 0, stutab.at(i)->student_id);//��������
			m_ListCtrl.SetItemText(nRow, 1, stutab.at(i)->name_);//��������
			m_ListCtrl.SetItemText(nRow, 2, stutab.at(i)->sex_);//��������
			m_ListCtrl.SetItemText(nRow, 3, stutab.at(i)->birth_);//��������
			
		}
		for (int i = 0; i < stutab.size(); i++)
		{
			delete  stutab.at(i);
		}
		stutab.clear();
		AfxMessageBox(L"��ѯ���ݳɹ�");
	}
	else
	{
		AfxMessageBox(L"��ѯ����ʧ��");
	}
}
