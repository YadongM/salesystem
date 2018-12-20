#pragma once
#include "afxwin.h"
#include "Resource.h"


// CDlgSearch 窗体视图

class CDlgSearch : public CFormView
{
	DECLARE_DYNCREATE(CDlgSearch)

protected:
	CDlgSearch();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgSearch();

public:
	enum { IDD = IDD_DIALOG_SEARCH};
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

private:
	CComboBox m_comb;
	int index = 0;
	CString content;
	CListCtrl m_list;
public:
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeComboFun();
	afx_msg void OnBnClickedButtonSearch();
};