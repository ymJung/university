// 08150070View.h : interface of the CMy08150070View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_08150070VIEW_H__B5E5D54F_9EAD_42D5_8D9B_58517F4F8973__INCLUDED_)
#define AFX_08150070VIEW_H__B5E5D54F_9EAD_42D5_8D9B_58517F4F8973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy08150070View : public CView
{
protected: // create from serialization only
	CMy08150070View();
	DECLARE_DYNCREATE(CMy08150070View)

// Attributes
public:
	CMy08150070Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy08150070View)
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
	virtual ~CMy08150070View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy08150070View)
	afx_msg void OnDownSampling();
	afx_msg void OnUpSampling();
	afx_msg void OnQuantization();
	afx_msg void OnSumConstant();
	afx_msg void OnSubConstant();
	afx_msg void OnMulConstant();
	afx_msg void OnDivConstant();
	afx_msg void OnBinarization();
	afx_msg void OnGammaCorrection();
	afx_msg void OnHistoStretch();
	afx_msg void OnNegaTransform();
	afx_msg void OnStressTransform();
	afx_msg void OnEndInSearch();
	afx_msg void OnHistogram();
	afx_msg void OnAndOperate();
	afx_msg void OnOrOperate();
	afx_msg void OnXorOperate();
	afx_msg void OnHistoEqual();
	afx_msg void OnEmbossing();
	afx_msg void OnBlurr();
	afx_msg void OnGaussianFilter();
	afx_msg void OnHrpsharp();
	afx_msg void OnLpfSharp();
	afx_msg void OnSharp();
	afx_msg void OnDiffOperatorHor();
	afx_msg void OnHomogenOperator();
	afx_msg void OnLaplacian();
	afx_msg void OnSobel();
	afx_msg void OnRoberts();
	afx_msg void OnPrewitt();
	afx_msg void OnBilinear();
	afx_msg void OnMeanSub();
	afx_msg void OnMedianSub();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 08150070View.cpp
inline CMy08150070Doc* CMy08150070View::GetDocument()
   { return (CMy08150070Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_08150070VIEW_H__B5E5D54F_9EAD_42D5_8D9B_58517F4F8973__INCLUDED_)
