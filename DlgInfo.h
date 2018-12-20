#pragma once
#include "afxcmn.h"



// CDlgInfo 窗体视图

class CDlgInfo : public CFormView
{
	DECLARE_DYNCREATE(CDlgInfo)

protected:
	CDlgInfo();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgInfo();

public:
	enum { IDD = IDD_DIALOG_INFO };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_list;
public:
	virtual void OnInitialUpdate();
};


