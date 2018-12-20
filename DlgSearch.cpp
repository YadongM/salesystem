#include "stdafx.h"
#include "SaleSystem.h"
#include "DlgSearch.h"
#include "InfoFile.h"
#include <iostream>

IMPLEMENT_DYNCREATE(CDlgSearch, CFormView)

CDlgSearch::CDlgSearch()
	: CFormView(CDlgSearch::IDD)
{

}

CDlgSearch::~CDlgSearch()
{

}

void CDlgSearch::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FUN, m_comb);
	DDX_Text(pDX, IDC_EDIT_CONTENT, content);
	DDX_Control(pDX, IDC_LIST_RESULT, m_list);
}

#ifdef _DEBUG
void CDlgSearch::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgSearch::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CDlgSearch::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	//将搜索方法添加到combox
	m_comb.AddString(CString("商品名称"));
	m_comb.AddString(CString("供应商名称"));
	m_comb.AddString(CString("商品编号"));

	//设置列表的风格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//设置表头
	CString head[] = { TEXT("商品ID"), TEXT("商品名称"), TEXT("商品价格"), TEXT("库存数量") , TEXT("供应商") };
	m_list.InsertColumn(0, head[0], LVCFMT_CENTER, 100);
	m_list.InsertColumn(1, head[1], LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, head[2], LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, head[3], LVCFMT_CENTER, 100);
	m_list.InsertColumn(4, head[4], LVCFMT_CENTER, 100);

	UpdateData(FALSE);
}BEGIN_MESSAGE_MAP(CDlgSearch, CFormView)
ON_CBN_SELCHANGE(IDC_COMBO_FUN, &CDlgSearch::OnCbnSelchangeComboFun)
ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgSearch::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


void CDlgSearch::OnCbnSelchangeComboFun()
{
	// TODO: 在此添加控件通知处理程序代码
	index = m_comb.GetCurSel();
}


void CDlgSearch::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	CInfoFile info, rst;
	info.ReadDocline();
	UpdateData(TRUE);
	//筛选
	if (content.IsEmpty())
	{
		rst = info;
	}
	else
	{
		switch (index)
		{
		case 2://商品名称
			for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
			{
				CStringA tmp;
				tmp = content;
				if (!it->name.compare(tmp.GetBuffer()))
				{
					rst.ls.push_back(*it);
				}
			}
			break;
		case 0://供应商名称
			for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
			{
				CStringA tmp;
				tmp = content;
				if (!it->supplier.compare(tmp.GetBuffer()))
				{
					rst.ls.push_back(*it);
				}
			}
			break;
		default:
			break;
		}
	}
	//将产品名添加到combox
	int i = 0;
	m_list.DeleteAllItems();
	for (list<msg>::iterator it = rst.ls.begin(); it != rst.ls.end(); it++)
	{
		//插入第一个节点确定一行
		CString sid;
		sid.Format(TEXT("%d"), it->id);
		m_list.InsertItem(i, sid);

		int j = 0;
		//插入本行其他数据
		m_list.SetItemText(i, ++j, CString(it->name.c_str()));
		sid.Format(TEXT("%d"), it->price);
		m_list.SetItemText(i, ++j, sid);
		sid.Format(TEXT("%d"), it->num);
		m_list.SetItemText(i, ++j, sid);
		m_list.SetItemText(i, ++j, CString(it->supplier.c_str()));
		i++;
	}
	UpdateData(FALSE);
}
