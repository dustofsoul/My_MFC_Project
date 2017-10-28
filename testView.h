// 1401150312View.h : interface of the CMy1401150312View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_1401150312VIEW_H__AF4E40B4_DB8E_4120_A71C_C3D68CE450DD__INCLUDED_)
#define AFX_1401150312VIEW_H__AF4E40B4_DB8E_4120_A71C_C3D68CE450DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy1401150312View : public CView
{
protected: // create from serialization only
	CMy1401150312View();
	DECLARE_DYNCREATE(CMy1401150312View)

// Attributes
public:
	CMy1401150312Doc* GetDocument();
	void BresenhamLine(CPoint sp,CPoint ep);
	void BresenhamCircle(CPoint sp,CPoint ep);
	void BresenhamOval(CPoint sp,CPoint ep);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1401150312View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool flag;
	int drawtype;
	CPoint endpoint;
	CPoint startpoint;
	virtual ~CMy1401150312View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy1401150312View)
	afx_msg void OnDrawLine();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawOval();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 1401150312View.cpp
inline CMy1401150312Doc* CMy1401150312View::GetDocument()
   { return (CMy1401150312Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1401150312VIEW_H__AF4E40B4_DB8E_4120_A71C_C3D68CE450DD__INCLUDED_)
