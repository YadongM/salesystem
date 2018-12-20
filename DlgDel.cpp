// DlgDel.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "DlgDel.h"
#include "InfoFile.h"

// CDlgDel

IMPLEMENT_DYNCREATE(CDlgDel, CFormView)

CDlgDel::CDlgDel()
	: CFormView(CDlgDel::IDD)
	, m_price(0)
	, m_num(0)
{

}

CDlgDel::~CDlgDel()
{
}

void CDlgDel::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRICE3, m_price);
	DDX_Text(pDX, IDC_EDIT_NUM3, m_num);
	DDX_Control(pDX, IDC_COMBO3, m_comb);
}

BEGIN_MESSAGE_MAP(CDlgDel, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_ADD1, &CDlgDel::OnBnClickedButtonAdd1)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL1, &CDlgDel::OnBnClickedButtonCancel1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CDlgDel::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CDlgDel 诊断

#ifdef _DEBUG
void CDlgDel::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgDel::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgDel 消息处理程序


void CDlgDel::OnBnClickedButtonAdd1()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if (m_num <= 0)
	{
		MessageBox(_T("数量不能为空"));
		return;
	}

	//组合销售信息
	int index = m_comb.GetCurSel();
	CString str;
	m_comb.GetLBText(index, str);

	//读取产品信息
	CInfoFile info;
	info.ReadDocline();
	int lastnum = 0;
	//查找商品修改剩余数量
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
	{
		if (str == (CString(it->name.c_str())))
		{
			if (m_num > it->num)
			{
				m_num = it->num;
				
			}
			it->num = it->num - m_num;

			lastnum = it->num;
			//回写数据
			info.WirteDocline();
		}

	}
	//容器释放
	info.ls.clear();

	CString delinfo;
	delinfo.Format(TEXT("成功删除商品\r\n商品名：%s\r\n单价：%d\r\n删除数量：%d\r\n"), str, m_price, m_num, lastnum);
	MessageBox(delinfo);

	m_num = 0;

	UpdateData(FALSE);
}


void CDlgDel::OnBnClickedButtonCancel1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_num = 0;

	UpdateData(FALSE);
}


void CDlgDel::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	//读取产品信息
	CInfoFile info;
	info.ReadDocline();
	//将产品名添加到combox
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
	{
		m_comb.AddString(CString(it->name.c_str()));

	}
	//容器释放
	info.ls.clear();

	//默认选中第一个商品
	m_comb.SetCurSel(0);
	OnCbnSelchangeCombo3();
	m_num = 0;
	UpdateData(FALSE);
}


void CDlgDel::OnCbnSelchangeCombo3()
{
	// TODO:  在此添加控件通知处理程序代码
	int index = m_comb.GetCurSel();
	CString str;
	m_comb.GetLBText(index, str);

	//读取产品信息
	CInfoFile info;
	info.ReadDocline();
	//将产品名添加到combox
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
	{
		if (str == (CString(it->name.c_str())))
		{
			m_price = it->price;
			break;
		}

	}
	//容器释放
	info.ls.clear();

	//数据显示
	UpdateData(FALSE);

}
