
// 2020619004温国亮View.cpp: CMy2020619004温国亮View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "2020619004温国亮.h"
#endif

#include "2020619004温国亮Doc.h"
#include "2020619004温国亮View.h"
#include "MainInterfaceDlg.h"
#include "MainFrm.h"

#include "afxmt.h"


CEvent threadStart;
CEvent threadEnd;



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 线程全局变量
volatile int threadController;

//事件线程函数
UINT ThreadProcEvent(LPVOID param)
{
	CMy2020619004温国亮App* pApp = (CMy2020619004温国亮App*)AfxGetApp();
	CMainFrame* pMainFrame = (CMainFrame*)pApp->GetMainWnd();
	CMy2020619004温国亮View* pView = (CMy2020619004温国亮View*)pMainFrame->GetActiveView();
	::WaitForSingleObject(threadStart.m_hObject, INFINITE);
	pView->m_strMessage = "启动了一个线程！";
	BOOL keepRunning = TRUE;
	while (keepRunning)
	{
		::Sleep(1000);
		int result = ::WaitForSingleObject(threadEnd.m_hObject, 0);
		if (result == WAIT_OBJECT_0)
			keepRunning = FALSE;
		pView->m_iTime++;
		::PostMessage((HWND)param, WM_THREAD_SENDMESS, 0, 0);
	}
	pView->m_iTime = 0;
	pView->m_strMessage = "线程结束！";
	return 0;
}



//线程函数
UINT ThreadProc(LPVOID param)
{
	CMy2020619004温国亮App* pApp = (CMy2020619004温国亮App*)AfxGetApp();
	CMainFrame* pMainFrame = (CMainFrame*)pApp->GetMainWnd();
	CMy2020619004温国亮View* pView = (CMy2020619004温国亮View*)pMainFrame->GetActiveView();
	pView->m_strMessage = "启动了一个线程！";
	while (threadController)
	{
		::Sleep(1000);
		pView->m_iTime++;
		pView->Invalidate();
	}
	pView->m_iTime = 0;
	pView->m_strMessage = "线程结束！";
	return 0;
}


// CMy2020619004温国亮View

IMPLEMENT_DYNCREATE(CMy2020619004温国亮View, CView)

BEGIN_MESSAGE_MAP(CMy2020619004温国亮View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Operation, &CMy2020619004温国亮View::OnMainInterface)
	ON_COMMAND(ID_START, &CMy2020619004温国亮View::OnStart)
	ON_COMMAND(ID_STOP, &CMy2020619004温国亮View::OnStop)
	ON_COMMAND(ID_STARTEvent, &CMy2020619004温国亮View::OnStartevent)
	ON_COMMAND(ID_STOPEvent, &CMy2020619004温国亮View::OnStopevent)
	ON_MESSAGE(WM_THREAD_SENDMESS, OnThreadSendmess)

END_MESSAGE_MAP()

// CMy2020619004温国亮View 构造/析构

CMy2020619004温国亮View::CMy2020619004温国亮View() noexcept
{
	// TODO: 在此处添加构造代码
	m_strMessage = "没有启动任何线程";
	m_iTime = 0;

}

CMy2020619004温国亮View::~CMy2020619004温国亮View()
{
}

BOOL CMy2020619004温国亮View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy2020619004温国亮View 绘图

void CMy2020619004温国亮View::OnDraw(CDC* pDC)
{
	CMy2020619004温国亮Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CString str;
	str.Format(_T("%d"), m_iTime);

	pDC->TextOut(50, 50, m_strMessage);
	pDC ->TextOut(100, 100, str);

}


// CMy2020619004温国亮View 打印

BOOL CMy2020619004温国亮View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy2020619004温国亮View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy2020619004温国亮View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy2020619004温国亮View 诊断

#ifdef _DEBUG
void CMy2020619004温国亮View::AssertValid() const
{
	CView::AssertValid();
}

void CMy2020619004温国亮View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2020619004温国亮Doc* CMy2020619004温国亮View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2020619004温国亮Doc)));
	return (CMy2020619004温国亮Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2020619004温国亮View 消息处理程序


void CMy2020619004温国亮View::OnMainInterface()
{
	MainInterfaceDlg dlg;
	dlg.DoModal();// TODO: 在此添加命令处理程序代码
}


void CMy2020619004温国亮View::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	threadController = 1;
	HWND hWnd = GetSafeHwnd();
	AfxBeginThread(ThreadProc, hWnd, THREAD_PRIORITY_NORMAL);
}


void CMy2020619004温国亮View::OnStop()
{
	// TODO: 在此添加命令处理程序代码
	threadController = 0;
}


void CMy2020619004温国亮View::OnStartevent()
{
	// TODO: 在此添加命令处理程序代码
	HWND hWnd = GetSafeHwnd();
	AfxBeginThread(ThreadProcEvent, hWnd, THREAD_PRIORITY_NORMAL);
	threadStart.SetEvent();
}


void CMy2020619004温国亮View::OnStopevent()
{
	// TODO: 在此添加命令处理程序代码
	threadEnd.SetEvent();
}

LRESULT CMy2020619004温国亮View::OnThreadSendmess(WPARAM w, LPARAM l)
{
	Invalidate();
	return 0;
}
