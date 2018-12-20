// DlgSell.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "DlgSell.h"
#include "InfoFile.h"

// CDlgSell

IMPLEMENT_DYNCREATE(CDlgSell, CFormView)

CDlgSell::CDlgSell()
	: CFormView(CDlgSell::IDD)
	, m_info(_T(""))
	, m_num(0)
	, m_price(0)
{

}

CDlgSell::~CDlgSell()
{
}

void CDlgSell::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comb);
	DDX_Text(pDX, IDC_EDIT_INFO, m_info);
	//  DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	//  DDX_Text(pDX, IDC_EDIT_PRICE, m_price);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_price);
}

BEGIN_MESSAGE_MAP(CDlgSell, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgSell::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_NOBUY, &CDlgSell::OnBnClickedButtonNobuy)
	ON_BN_CLICKED(IDC_BUTTON_BUY, &CDlgSell::OnBnClickedButtonBuy)
END_MESSAGE_MAP()


// CDlgSell 诊断

#ifdef _DEBUG
void CDlgSell::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgSell::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgSell 消息处理程序


void CDlgSell::OnInitialUpdate()
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


}

//商品选择发生单价改变
void CDlgSell::OnCbnSelchangeCombo1()
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

	m_num = 0;

	//数据显示
	UpdateData(FALSE);

}


void CDlgSell::OnBnClickedButtonNobuy()
{
	// TODO:  在此添加控件通知处理程序代码
	m_num = 0;
	UpdateData(FALSE);

}


void CDlgSell::OnBnClickedButtonBuy()
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
	//查找商品修改剩余数量
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
	{
		if (str == (CString(it->name.c_str())))
		{
			if (m_num > it->num)
			{
				CString err;
				err.Format(TEXT("库存不足，只剩数量%d"), it->num);
				MessageBox(err);
				info.ls.clear();
				return;
			}
			it->num = it->num - m_num;

			//回写数据
			info.WirteDocline();
		}

	}
	//容器释放
	info.ls.clear();

	CString sellinfo;
	sellinfo.Format(TEXT("商品名：%s\r\n单价：%d\r\n数量：%d\r\n总价：%d\r\n客户信息：客户1\r\n"), str, m_price, m_num, m_price * m_num);
	m_num = 0;

	m_info = sellinfo;
	//m_info.Empty();
	UpdateData(FALSE);

}
