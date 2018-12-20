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

	// TODO:  �ڴ����ר�ô����/����û���
	//������������ӵ�combox
	m_comb.AddString(CString("��Ʒ����"));
	m_comb.AddString(CString("��Ӧ������"));
	m_comb.AddString(CString("��Ʒ���"));

	//�����б�ķ��
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//���ñ�ͷ
	CString head[] = { TEXT("��ƷID"), TEXT("��Ʒ����"), TEXT("��Ʒ�۸�"), TEXT("�������") , TEXT("��Ӧ��") };
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	index = m_comb.GetCurSel();
}


void CDlgSearch::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CInfoFile info, rst;
	info.ReadDocline();
	UpdateData(TRUE);
	//ɸѡ
	if (content.IsEmpty())
	{
		rst = info;
	}
	else
	{
		switch (index)
		{
		case 2://��Ʒ����
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
		case 0://��Ӧ������
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
	//����Ʒ����ӵ�combox
	int i = 0;
	m_list.DeleteAllItems();
	for (list<msg>::iterator it = rst.ls.begin(); it != rst.ls.end(); it++)
	{
		//�����һ���ڵ�ȷ��һ��
		CString sid;
		sid.Format(TEXT("%d"), it->id);
		m_list.InsertItem(i, sid);

		int j = 0;
		//���뱾����������
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
