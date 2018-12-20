// DlgInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "DlgInfo.h"
#include "InfoFile.h"

// CDlgInfo

IMPLEMENT_DYNCREATE(CDlgInfo, CFormView)

CDlgInfo::CDlgInfo()
	: CFormView(CDlgInfo::IDD)
{

}

CDlgInfo::~CDlgInfo()
{
}

void CDlgInfo::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CDlgInfo, CFormView)
END_MESSAGE_MAP()


// CDlgInfo 诊断

#ifdef _DEBUG
void CDlgInfo::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgInfo::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgInfo 消息处理程序


void CDlgInfo::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类

	//设置列表的风格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//设置表头
	CString head[] = { TEXT("商品ID"), TEXT("商品名称"), TEXT("商品价格"), TEXT("库存数量") , TEXT("供应商")};
	m_list.InsertColumn(0, head[0], LVCFMT_CENTER, 100);
	m_list.InsertColumn(1, head[1], LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, head[2], LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, head[3], LVCFMT_CENTER, 100);
	m_list.InsertColumn(4, head[4], LVCFMT_CENTER, 100);

	//插入列表数据

	//读取产品信息
	CInfoFile info;
	info.ReadDocline();
	//将产品名添加到combox
	int i = 0;
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++)
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
	//容器释放
	info.ls.clear();
}
