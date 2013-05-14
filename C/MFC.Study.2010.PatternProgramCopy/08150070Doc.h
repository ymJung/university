// 08150070Doc.h : interface of the CMy08150070Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_08150070DOC_H__A42FF5E5_D957_487A_9466_C4CB915DA008__INCLUDED_)
#define AFX_08150070DOC_H__A42FF5E5_D957_487A_9466_C4CB915DA008__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy08150070Doc : public CDocument
{
protected: // create from serialization only
	CMy08150070Doc();
	DECLARE_DYNCREATE(CMy08150070Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy08150070Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnHistogram();
	void OnEndInSearch();
	void OnHistoStretch();
	void OnStressTransform();
	void OnBinarization();
	void OnGammaCorrection();
	void OnNegaTransform();
	void OnXorOperate();
	void OnOrOperate();
	void OnAndOperate();

	void OnDivConstant();
	void OnMulConstant();
	void OnSubConstant();
	void OnSumConstant();
	void OnQuantization();
	void OnUpSampling();
	int m_Re_size;
	int m_Re_height;
	int m_Re_width;
	unsigned char* m_OutputImage;
	void OnDownSampling();
	int m_size;
	int m_height;
	int m_width;
	unsigned char* m_InputImage;
	
	//히스토그램에서 사용할 변수 선언
	double m_HIST[256];
	double m_Sum_Of_HIST[256];
	unsigned char m_Scale_HIST[256];

	virtual ~CMy08150070Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy08150070Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_08150070DOC_H__A42FF5E5_D957_487A_9466_C4CB915DA008__INCLUDED_)
