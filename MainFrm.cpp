
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SaleSystem.h"

#include "MainFrm.h"
#include "SelectView.h"
#include "DisplayView.h"
#include "DlgPerson1.h"
#include "DlgSell.h"
#include "DlgInfo.h"
#include "DlgAdd.h"
#include "DlgDel.h"
#include "DlgSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

//消息映射入口定义
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)
	ON_MESSAGE(NM_F, OnMyChange)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//加载图标
	//GetClassLong(m_hWnd, (LONG)AfxGetApp()->LoadIcon(IDI_ICON1));
	SetClassLong(m_hWnd,GCL_HICON, (LONG)AfxGetApp()->LoadIcon(IDI_ICON2));


	//设置窗口显示位置和大小
	MoveWindow(100, 50, 900, 600);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序


//拆分窗口
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	
	//静态拆分
	m_splitter.CreateStatic(this, 1, 2);

	//拆分窗口
	m_splitter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(240, 600),pContext);
	m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(660, 600), pContext);


	return TRUE;
}
//自定义映射消息函数功能实现
LRESULT CMainFrame::OnMyChange(WPARAM wparam, LPARAM lparam)
{
	CCreateContext Context;
	switch (wparam)
	{
	case NM_A:
	{
		//CUserDlg类需要包含头文件#include "UserDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CDlgPerson1);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDlgPerson1), CSize(600, 0), &Context);
		CDlgPerson1 *pNewView = (CDlgPerson1 *)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_B:
	{
		//CUserDlg类需要包含头文件#include "UserDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CDlgSell);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDlgSell), CSize(600, 0), &Context);
		CDlgSell *pNewView = (CDlgSell *)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
		break;
	case NM_C:
	{
		//CUserDlg类需要包含头文件#include "UserDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CDlgInfo);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDlgInfo), CSize(600, 0), &Context);
		CDlgInfo *pNewView = (CDlgInfo *)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}		
		break;
	case NM_D:
	{
		//CUserDlg类需要包含头文件#include "UserDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CDlgAdd);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDlgAdd), CSize(600, 0), &Context);
		CDlgAdd *pNewView = (CDlgAdd *)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}		
		break;
	case NM_E:
	{
		//CUserDlg类需要包含头文件#include "UserDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CDlgDel);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDlgDel), CSize(600, 0), &Context);
		CDlgDel *pNewView = (CDlgDel *)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
	break;
	case NM_F:
	{
		//CUserDlg类需要包含头文件#include "UserDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CDlgSearch);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDlgSearch), CSize(600, 0), &Context);
		CDlgSearch *pNewView = (CDlgSearch *)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
	break;
	default:
		break;
	}

	return 0;
}

