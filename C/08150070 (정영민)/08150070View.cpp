// 08150070View.cpp : implementation of the CMy08150070View class
//

#include "stdafx.h"
#include "08150070.h"

#include "08150070Doc.h"
#include "08150070View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy08150070View

IMPLEMENT_DYNCREATE(CMy08150070View, CView)

BEGIN_MESSAGE_MAP(CMy08150070View, CView)
	//{{AFX_MSG_MAP(CMy08150070View)
	ON_COMMAND(ID_DOWN_SAMPLING, OnDownSampling)
	ON_COMMAND(ID_UP_SAMPLING, OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, OnQuantization)
	ON_COMMAND(ID_SUM_CONSTANT, OnSumConstant)
	ON_COMMAND(ID_SUB_CONSTANT, OnSubConstant)
	ON_COMMAND(ID_MUL_CONSTANT, OnMulConstant)
	ON_COMMAND(ID_DIV_CONSTANT, OnDivConstant)
	ON_COMMAND(ID_BINARIZATION, OnBinarization)
	ON_COMMAND(ID_GAMMA_CORRECTION, OnGammaCorrection)
	ON_COMMAND(ID_HISTO_STRETCH, OnHistoStretch)
	ON_COMMAND(ID_NEGA_TRANSFORM, OnNegaTransform)
	ON_COMMAND(ID_STRESS_TRANSFORM, OnStressTransform)
	ON_COMMAND(ID_END_IN_SEARCH, OnEndInSearch)
	ON_COMMAND(ID_HISTOGRAM, OnHistogram)
	ON_COMMAND(ID_AND_OPERATE, OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, OnXorOperate)
	ON_COMMAND(ID_HISTO_EQUAL, OnHistoEqual)
	ON_COMMAND(ID_EMBOSSING, OnEmbossing)
	ON_COMMAND(ID_BLURR, OnBlurr)
	ON_COMMAND(ID_GAUSSIAN_FILTER, OnGaussianFilter)
	ON_COMMAND(ID_HRPSHARP, OnHrpsharp)
	ON_COMMAND(ID_LPF_SHARP, OnLpfSharp)
	ON_COMMAND(ID_SHARP, OnSharp)
	ON_COMMAND(ID_DIFF_OPERATOR_HOR, OnDiffOperatorHor)
	ON_COMMAND(ID_HOMOGEN_OPERATOR, OnHomogenOperator)
	ON_COMMAND(ID_LAPLACIAN, OnLaplacian)
	ON_COMMAND(ID_SOBEL, OnSobel)
	ON_COMMAND(ID_ROBERTS, OnRoberts)
	ON_COMMAND(ID_PREWITT, OnPrewitt)
	ON_COMMAND(ID_BILINEAR, OnBilinear)
	ON_COMMAND(ID_MEAN_SUB, OnMeanSub)
	ON_COMMAND(ID_MEDIAN_SUB, OnMedianSub)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy08150070View construction/destruction

CMy08150070View::CMy08150070View()
{
	// TODO: add construction code here

}

CMy08150070View::~CMy08150070View()
{
}

BOOL CMy08150070View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMy08150070View drawing

void CMy08150070View::OnDraw(CDC* pDC)
{
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i, j;
	unsigned char R, G, B;
	// 입력 영상 출력
	for(i = 0 ; i<pDoc->m_height ; i++){
		for(j = 0 ; j<pDoc->m_width ; j++){
			R = pDoc->m_InputImage[i*pDoc->m_width+j];
			G = B = R;
			pDC->SetPixel(j+5, i+5, RGB(R, G, B));
		}
	}
	// 축소된 영상 출력
	for(i = 0 ; i<pDoc->m_Re_height ; i++){
		for(j = 0 ; j<pDoc->m_Re_width ; j++){
			R = pDoc->m_OutputImage[i*pDoc->m_Re_width+j];
			G = B = R;
			pDC->SetPixel(j+pDoc->m_width+10, i+5, RGB(R, G, B));
		}
		
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CMy08150070View printing

BOOL CMy08150070View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy08150070View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy08150070View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMy08150070View diagnostics

#ifdef _DEBUG
void CMy08150070View::AssertValid() const
{
	CView::AssertValid();
}

void CMy08150070View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy08150070Doc* CMy08150070View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy08150070Doc)));
	return (CMy08150070Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy08150070View message handlers

void CMy08150070View::OnDownSampling() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDownSampling();
	Invalidate(TRUE);
}

void CMy08150070View::OnUpSampling() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnUpSampling();
	Invalidate(TRUE);
}

void CMy08150070View::OnQuantization() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnQuantization();
	Invalidate(TRUE);
}

void CMy08150070View::OnSumConstant() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnSumConstant();
	Invalidate(TRUE);
}

void CMy08150070View::OnSubConstant() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnSubConstant();
	Invalidate(TRUE);
}

void CMy08150070View::OnMulConstant() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnMulConstant();
	Invalidate(TRUE);
}

void CMy08150070View::OnDivConstant() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnDivConstant();
	Invalidate(TRUE);
}

void CMy08150070View::OnBinarization() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnBinarization();
	Invalidate(TRUE);
}

void CMy08150070View::OnGammaCorrection() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnGammaCorrection();
	Invalidate(TRUE);
}

void CMy08150070View::OnHistoStretch() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}

void CMy08150070View::OnNegaTransform() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}

void CMy08150070View::OnStressTransform() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnStressTransform();
	Invalidate(TRUE);
}

void CMy08150070View::OnEndInSearch() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnEndInSearch();
	Invalidate(TRUE);
}

void CMy08150070View::OnHistogram() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnHistogram();
	Invalidate(TRUE);
}

void CMy08150070View::OnAndOperate() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnAndOperate();
	Invalidate(TRUE);
}

void CMy08150070View::OnOrOperate() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnOrOperate();
	Invalidate(TRUE);
}

void CMy08150070View::OnXorOperate() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnXorOperate();
	Invalidate(TRUE);
}

void CMy08150070View::OnHistoEqual() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}

void CMy08150070View::OnEmbossing() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnEmbossing();
	Invalidate(TRUE);
}

void CMy08150070View::OnBlurr() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnBlurr();
	Invalidate(TRUE);
}

void CMy08150070View::OnGaussianFilter() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnGaussianFilter();
	Invalidate(TRUE);
}

void CMy08150070View::OnHrpsharp() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnHpfSharp();
	Invalidate(TRUE);
}

void CMy08150070View::OnLpfSharp() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}

void CMy08150070View::OnSharp() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnSharpening();
	Invalidate(TRUE);
}

void CMy08150070View::OnDiffOperatorHor() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnDiffOperatorHor();
	Invalidate(TRUE);
}

void CMy08150070View::OnHomogenOperator() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnHomogenOperator();
	Invalidate(TRUE);
}

void CMy08150070View::OnLaplacian() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnLaplacian();
	Invalidate(TRUE);
}

void CMy08150070View::OnSobel() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnSobel();
	Invalidate(TRUE);
}

void CMy08150070View::OnRoberts() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnRoberts();
	Invalidate(TRUE);
}

void CMy08150070View::OnPrewitt() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnPrewitt();
	Invalidate(TRUE);
}

void CMy08150070View::OnBilinear() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnBilinear();
	Invalidate(TRUE);
}

void CMy08150070View::OnMeanSub() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnMeanSub();
	Invalidate(TRUE);
}

void CMy08150070View::OnMedianSub() 
{
	// TODO: Add your command handler code here
	CMy08150070Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnMedianSub();
	Invalidate(TRUE);
}
