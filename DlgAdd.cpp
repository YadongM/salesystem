// DlgAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "DlgAdd.h"
#include "InfoFile.h"

// CDlgAdd

IMPLEMENT_DYNCREATE(CDlgAdd, CFormView)

CDlgAdd::CDlgAdd()
	: CFormView(CDlgAdd::IDD)
	, m_editSp(_T(""))
	, m_price3(0)
	, m_price2(0)
	, m_num3(0)
	, m_num2(0)
{

}

CDlgAdd::~CDlgAdd()
{
}

void CDlgAdd::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THING, m_editSp);
	DDX_Text(pDX, IDC_EDIT_PRICE3, m_price3);
	DDX_Text(pDX, IDC_EDIT_PRICE2, m_price2);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_num3);
	DDX_Text(pDX, IDC_EDIT_NU, m_num2);
	DDX_Text(pDX, IDC_EDIT_SUPPLIER, m_editSupplier);
	DDX_Control(pDX, IDC_COMBO2, m_comb2);
}

BEGIN_MESSAGE_MAP(CDlgAdd, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDlgAdd::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON_ADD1, &CDlgAdd::OnBnClickedButtonAdd1)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL1, &CDlgAdd::OnBnClickedButtonCancel1)
	ON_BN_CLICKED(IDC_BUTTON_ADD2, &CDlgAdd::OnBnClickedButtonAdd2)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL2, &CDlgAdd::OnBnClickedButtonCancel2)
END_MESSAGE_MAP()


// CDlgAdd 诊断

#ifdef _DEBUG
void CDlgAdd::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgAdd::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgAdd 消息处理程序


void CDlgAdd::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类


	//读取产品信息
	CInfoFile info;
	info.ReadDocline();
	//将产品名添加到combox
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
	{
		m_comb2.AddString(CString(it->name.c_str()));

	}
	//容器释放
	info.ls.clear();

	//默认选中第一个商品
	m_comb2.SetCurSel(0);
	OnCbnSelchangeCombo2();

	m_price3 = 0;
	m_num2 = 0;
	m_num3 = 0;
	m_editSp.Empty();
	UpdateData(FALSE);
}


void CDlgAdd::OnCbnSelchangeCombo2()
{
	// TODO:  在此添加控件通知处理程序代码
	int index = m_comb2.GetCurSel();
	CString str;
	m_comb2.GetLBText(index, str);

	//读取产品信息
	CInfoFile info;
	info.ReadDocline();
	//将产品名添加到combox
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
	{
		if (str == (CString(it->name.c_str())))
		{
			m_price2 = it->price;
			break;
		}

	}
	//容器释放
	info.ls.clear();

	//数据显示
	UpdateData(FALSE);

}


void CDlgAdd::OnBnClickedButtonAdd1()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if (m_num2 <= 0)
	{
		MessageBox(_T("数量不能为空"));
		return;
	}

	//组合销售信息
	int index = m_comb2.GetCurSel();
	CString str;
	m_comb2.GetLBText(index, str);

	//读取产品信息
	CInfoFile info;
	info.ReadDocline();
	//查找商品修改剩余数量
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
	{
		if (str == (CString(it->name.c_str())))
		{
			if (m_num2 > it->num)
			{
				CString err;
				err.Format(TEXT("库存不足，只剩数量%d"), it->num);
				MessageBox(err);
				info.ls.clear();
				return;
			}
			it->num = it->num + m_num2;

			//回写数据
			info.WirteDocline();
			break;
		}

	}
	//容器释放
	info.ls.clear();

	CString infostr;
	infostr.Format(TEXT("增加商品\r\n商品名：%s\r\n单价：%d\r\n数量：%d\r\n"), str, m_price2, m_num2);
	
	MessageBox(infostr);

	m_num2 = 0;
	UpdateData(FALSE);
}


void CDlgAdd::OnBnClickedButtonCancel1()
{
	// TODO:  在此添加控件通知处理程序代码

	m_num2 = 0;
	UpdateData(FALSE);
}

//添加新产品
void CDlgAdd::OnBnClickedButtonAdd2()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if (m_num3 <= 0 || m_price3 <= 0 || m_editSp.IsEmpty())
	{
		MessageBox(_T("不能为空"));
		return;
	}
	//读取产品信息
	CInfoFile info;
	info.ReadDocline();
	//增加商品
	info.Addline(m_editSp, m_num3, m_price3, m_editSupplier);

	info.WirteDocline();

	CString infostr;
	infostr.Format(TEXT("成功增加商品\r\n商品名：%s\r\n单价：%d\r\n数量：%d\r\n供应商： %s\r\n"), m_editSp, m_price3, m_num3, m_editSupplier);

	MessageBox(infostr);

	m_editSp.Empty();
	m_editSupplier.Empty();
	m_price3 = 0;
	m_num3 = 0;

	UpdateData(FALSE);
}


void CDlgAdd::OnBnClickedButtonCancel2()
{
	// TODO:  在此添加控件通知处理程序代码

	m_editSp.Empty();
	m_editSupplier.Empty();
	m_price3 = 0;
	m_num3 = 0;

	UpdateData(FALSE);
}
