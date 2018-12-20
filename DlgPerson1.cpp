// DlgPerson1.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "DlgPerson1.h"
#include "InfoFile.h"

// CDlgPerson1

IMPLEMENT_DYNCREATE(CDlgPerson1, CFormView)

CDlgPerson1::CDlgPerson1()
	: CFormView(CDlgPerson1::IDD)
	, m_role(_T(""))
	, m_name(_T(""))
	, m_newpwd(_T(""))
	, m_surepwd(_T(""))
{

}

CDlgPerson1::~CDlgPerson1()
{
}

void CDlgPerson1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROLE, m_role);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_NEWPWD, m_newpwd);
	DDX_Text(pDX, IDC_EDIT_SUREPWD, m_surepwd);
}

BEGIN_MESSAGE_MAP(CDlgPerson1, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SURE, &CDlgPerson1::OnBnClickedButtonSure)
END_MESSAGE_MAP()


// CDlgPerson1 诊断

#ifdef _DEBUG
void CDlgPerson1::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgPerson1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgPerson1 消息处理程序


void CDlgPerson1::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类

	m_role = TEXT("经理");

	CInfoFile file;
	CString role, name;
	file.ReadLogin(role, name);

	m_name = name;

	m_newpwd.Empty();
	m_surepwd.Empty();

	UpdateData(FALSE);

}


void CDlgPerson1::OnBnClickedButtonSure()
{
	// TODO:  在此添加控件通知处理程序代码

	//读取页面数据
	UpdateData(TRUE);

	if (m_newpwd.IsEmpty() || m_surepwd.IsEmpty())
	{
		MessageBox(_T("密码不能为空"));
		return;
	}
	if (m_newpwd != m_surepwd)
	{
		MessageBox(_T("密码不一致"));
		return;
	}

	CInfoFile file;
	CString npwd, spwd;
	file.ReadLogin(npwd, spwd);

	if (m_newpwd == spwd)
	{
		MessageBox(_T("新旧密码不能一样"));
		return;
	}

	CStringA tmp1, tmp2;
	tmp1 = npwd;
	tmp2 = m_newpwd;

	char* tname = tmp1.GetBuffer();
	char* tpwd = tmp2.GetBuffer();

	file.WritePwd(tname, tpwd);
	MessageBox(_T("修改密码成功"));

	m_newpwd.Empty();
	m_surepwd.Empty();

	UpdateData(FALSE);
}
