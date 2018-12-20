// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "DlgLogin.h"
#include "afxdialogex.h"
#include "InfoFile.h"

// CDlgLogin 对话框

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLogin::IDD, pParent)
	, m_name(_T(""))
	, m_pwd(_T(""))
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgLogin::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_Login, &CDlgLogin::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CDlgLogin 消息处理程序


void CDlgLogin::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	exit(1);
	CDialogEx::OnClose();
}


void CDlgLogin::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDlgLogin::OnBnClickedButtonCancel()
{
	// TODO:  在此添加控件通知处理程序代码

	exit(1);
}


BOOL CDlgLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//初始化数据用于测试
	m_name = TEXT("MYD");
	m_pwd = TEXT("123");
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgLogin::OnBnClickedButtonLogin()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if (m_name.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("用户名或者密码不可以为空"));
		return;
	}

	CInfoFile file;
	CString name, pwd;

	file.ReadLogin(name, pwd);


	if (name != m_name)
	{
		MessageBox(TEXT("用户名不存在"));
		return;
	}
	
	if (pwd != m_pwd)
	{
		MessageBox(TEXT("密码错误"));
		return;
	}

	CDialogEx::OnOK();

}
