
// 2020619004温国亮View.h: CMy2020619004温国亮View 类的接口
//

#pragma once

const int WM_THREAD_SENDMESS = WM_USER + 20;


class CMy2020619004温国亮View : public CView
{
protected: // 仅从序列化创建
	CMy2020619004温国亮View() noexcept;
	DECLARE_DYNCREATE(CMy2020619004温国亮View)

// 特性
public:
	CMy2020619004温国亮Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy2020619004温国亮View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMainInterface();
	afx_msg void OnStart();
	afx_msg void OnStop();
	CString m_strMessage;
	int m_iTime;
	afx_msg void OnStartevent();
	afx_msg void OnStopevent();
	afx_msg LRESULT  OnThreadSendmess(WPARAM w, LPARAM l);

};

#ifndef _DEBUG  // 2020619004温国亮View.cpp 中的调试版本
inline CMy2020619004温国亮Doc* CMy2020619004温国亮View::GetDocument() const
   { return reinterpret_cast<CMy2020619004温国亮Doc*>(m_pDocument); }
#endif

