// 08150070Doc.cpp : implementation of the CMy08150070Doc class
//

#include "stdafx.h"
#include "08150070.h"

#include "08150070Doc.h"
#include "math.h"

#include "DownSampleDlg.h"
#include "UpSampleDlg.h"
#include "QuantizationDlg.h"
#include "ConstantDlg.h"
#include "StressTransformDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy08150070Doc

IMPLEMENT_DYNCREATE(CMy08150070Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy08150070Doc, CDocument)
	//{{AFX_MSG_MAP(CMy08150070Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy08150070Doc construction/destruction

CMy08150070Doc::CMy08150070Doc()
{
	// TODO: add one-time construction code here

}

CMy08150070Doc::~CMy08150070Doc()
{
}

BOOL CMy08150070Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy08150070Doc serialization

void CMy08150070Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMy08150070Doc diagnostics

#ifdef _DEBUG
void CMy08150070Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy08150070Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy08150070Doc commands

BOOL CMy08150070Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	CFile File; //파일 객체

	File.Open(lpszPathName,CFile::modeRead|CFile::typeBinary);
	//파일 열기 대화상자에서 선택한 파일을 지정하고 읽기모드 선택

	//256*256, 512*512, 640*480 선택
	if(File.GetLength() == 256*256){ //RAW파일 해상도 결정
		m_height = 256;
		m_width = 256;
	}else if(File.GetLength() == 512*512){
		m_height = 512;
		m_width = 512;
	}else if(File.GetLength() == 640*480){
		m_height = 480;
		m_width = 640;
	}else{
		AfxMessageBox("지원하지 않는 이미지 파일!");
		return 0;
	}

	m_size = m_width * m_height;
	//영상 크기 계산
	
	m_InputImage = new unsigned char[m_size]; //멤버 변수의 포인터
	//입력영상 크기에 맞는 동적 메모리 할당

	for(int i =0;i<m_size;i++)
		m_InputImage[i] = 255; // 초기화
	File.Read(m_InputImage,m_size); //입력 영상을  m_InputImage에 담음
	File.Close(); // 파일 닫기

	return TRUE;
}

BOOL CMy08150070Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	CFile File; // 파일객체 선언 최종 출력파일
	CFileDialog SaveDlg(FALSE,"raw",NULL,OFN_HIDEREADONLY);
	//raw 파일을 다른이름으로 저장하기 위한 대화객체 선언

	if(SaveDlg.DoModal() == IDOK){
		//DoModal 멤버 함수에서 저장하기 수행
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		//파일 열기
		File.Write(m_InputImage,m_size); 
		// 파일 쓰기
		File.Close();
		//파일 닫기
	}
	return CDocument::OnSaveDocument(lpszPathName);
}

void CMy08150070Doc::OnDownSampling()
{
	int i,j;
	CDownSampleDlg dlg;
	if(dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
	{
		m_Re_height = m_height / dlg.m_DownSampleRate; //축소 영상 수직 길이 
		m_Re_width = m_width / dlg.m_DownSampleRate; // 축소 영상 수평 길이
		m_Re_size = m_Re_height * m_Re_width; // 축소 영상 크기 계산

		m_OutputImage = new unsigned char [m_Re_size]; // 축소영상 메모리 할당

		for(i=0;i<m_Re_height;i++){
			for(j=0;j<m_Re_width;j++){
				m_OutputImage[i*m_Re_width+j]
					= m_InputImage[(i*dlg.m_DownSampleRate*m_width)+dlg.m_DownSampleRate*j];
				// 축소 영상을 생성 하기 위한 계산
			}
		}
	}
}

void CMy08150070Doc::OnUpSampling()
{
	int i,j;
	CUpSampleDlg dlg;
	if(dlg.DoModal() == IDOK){ //모달대화상자
		m_Re_height = m_height * dlg.m_UpSampleRate; //확대영상 세로
		m_Re_width = m_width * dlg.m_UpSampleRate; // 확대영상 가로
		m_Re_size = m_Re_height * m_Re_width; // 확대영상 크기
		m_OutputImage = new unsigned char[m_Re_size]; // 확대영상 위한 메모리

		for(i=0;i<m_Re_size;i++)
			m_OutputImage[i] =0; //초기화
		for(i=0;i<m_height;i++){
			for(j=0;j<m_width;j++){
				m_OutputImage[i*dlg.m_UpSampleRate*m_Re_width+dlg.m_UpSampleRate*j] //출력 영상을 저장할 공간
					= m_InputImage[i*m_width+j];

				m_OutputImage[(i*dlg.m_UpSampleRate+1)*m_Re_width+(dlg.m_UpSampleRate*j)] //2배시 빈 영역을 채워줌
					= m_InputImage[i*m_width+j];

				m_OutputImage[(i*dlg.m_UpSampleRate)*m_Re_width+(dlg.m_UpSampleRate*j+1)] //2배시 빈 영역을 채워줌
					= m_InputImage[i*m_width+j];

				m_OutputImage[(i*dlg.m_UpSampleRate+1)*m_Re_width+(dlg.m_UpSampleRate*j+1)] //2배시 빈 영역을 채워줌
					= m_InputImage[i*m_width+j];
			}

		}
	}

}

void CMy08150070Doc::OnQuantization()
{
	CQuantizationDlg dlg;
	if(dlg.DoModal() == IDOK) //모달 활성화
	{
		int i,j, value,LEVEL;
		double HIGH, *TEMP;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];// 메모리할당
		TEMP = new double [m_size]; //입력영상과 동일한 메모리 할당

		LEVEL = 256; //입력영상 양자화 단계
		HIGH = 256; 

		value = (int)pow(2,dlg.m_QuantiBit);
		//양자화 단계결정

		for(i=0;i<m_size;i++){
			for(j=0;j<value;j++){
				if(m_InputImage[i] >= (LEVEL/value)*j && m_InputImage[i] < (LEVEL/value)*(j+1)){
					TEMP[i] = (double)(HIGH/value)*j; // 양자화 수행
				}
			}
		}
		for(i=0;i<m_size;i++){
			m_OutputImage[i] = (unsigned char)TEMP[i]; //결과 생성
		}
	}


}

void CMy08150070Doc::OnSumConstant()
{
	
	CConstantDlg dlg; //상수값 입력받는 대화상자
	
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0; i<m_size; i++){
			
			if(m_InputImage[i] + dlg.m_Constant >= 255) //255보다 클시 255로 고정
				m_OutputImage[i] = 255; 
			else
				m_OutputImage[i]=(unsigned char)(m_InputImage[i] + dlg.m_Constant); //덧셈
		}
	}

}

void CMy08150070Doc::OnSubConstant()
{
	
	CConstantDlg dlg; //상수값 입력받는 대화상자
	
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0; i<m_size; i++){
			
			if(m_InputImage[i] + dlg.m_Constant >= 255) //255보다 클시 255로 고정
				m_OutputImage[i] = 255; 
			else
				m_OutputImage[i]=(unsigned char)(m_InputImage[i] - dlg.m_Constant); //뺄셈
		}
	}

}

void CMy08150070Doc::OnMulConstant()
{
	
	CConstantDlg dlg; //상수값 입력받는 대화상자
	
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0; i<m_size; i++){
			
			if(m_InputImage[i] + dlg.m_Constant >= 255) //255보다 클시 255로 고정
				m_OutputImage[i] = 255; 
			else
				m_OutputImage[i]=(unsigned char)(m_InputImage[i] * dlg.m_Constant); //곱셈
		}
	}

}

void CMy08150070Doc::OnDivConstant()
{
	
	CConstantDlg dlg; //상수값 입력받는 대화상자
	
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0; i<m_size; i++){
			
			if(m_InputImage[i] + dlg.m_Constant >= 255) //255보다 클시 255로 고정
				m_OutputImage[i] = 255; 
			else
				m_OutputImage[i]=(unsigned char)(m_InputImage[i] / dlg.m_Constant); //나눗셈
		}
	}

}

void CMy08150070Doc::OnAndOperate()
{
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal()==IDOK){
		for(i=0;i<m_size;i++){
			if((m_InputImage[i] & (unsigned char)dlg.m_Constant)>=255)
				m_OutputImage[i] = 255;
			//255보다 크면 255 출력
			else if((m_InputImage[i]&(unsigned char)dlg.m_Constant)<0)
				m_OutputImage[i]=0;

			else
				m_OutputImage[i]=(m_InputImage[i]&(unsigned char)dlg.m_Constant);
		}
	}
}

void CMy08150070Doc::OnOrOperate()
{
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal()==IDOK){
		for(i=0;i<m_size;i++){
			if((m_InputImage[i]|(unsigned char)dlg.m_Constant)>=255)
				m_OutputImage[i] = 255;
			//255보다 크면 255 출력
			else if((m_InputImage[i]|(unsigned char)dlg.m_Constant)<0)
				m_OutputImage[i]=0;

			else
				m_OutputImage[i]=(m_InputImage[i]|(unsigned char)dlg.m_Constant);
		}
	}
}

void CMy08150070Doc::OnXorOperate()
{
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal()==IDOK){
		for(i=0;i<m_size;i++){
			if((m_InputImage[i] ^ (unsigned char)dlg.m_Constant)>=255)
				m_OutputImage[i] = 255;
			//255보다 크면 255 출력
			else if((m_InputImage[i]^(unsigned char)dlg.m_Constant)<0)
				m_OutputImage[i]=0;

			else
				m_OutputImage[i]=(m_InputImage[i]^(unsigned char)dlg.m_Constant);
		}
	}
}

void CMy08150070Doc::OnNegaTransform()
{
	int i;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for(i=0; i<m_size; i++)
		m_OutputImage[i] = 255 - m_InputImage[i]; //영상반전


}

void CMy08150070Doc::OnGammaCorrection()
{
	CConstantDlg dlg;

	int i;
	double temp;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0; i<m_size; i++){
			temp = pow(m_InputImage[i], 1/dlg.m_Constant); //감마값계산
			if(temp<0)
				m_OutputImage[i] = 0;
			else if(temp > 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)temp;
		}
	}
	
}

void CMy08150070Doc::OnBinarization()
{
	CConstantDlg dlg;

	int i;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0;i<m_size;i++){
			if(m_InputImage[i] >= dlg.m_Constant)
				m_OutputImage[i] = 255; //임계 값보다 크면 255 고정
			else
				m_OutputImage[i] = 0; // 임계값 보다 작으면 0 고정
		}
	}


}

void CMy08150070Doc::OnStressTransform()
{

	CStressTransformDlg dlg;
	
	int i;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	
	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0;i<m_size;i++){
			//입력값이 강조 시작값과 강조 종료 값 사이에 위치시 255 출력
			if(m_InputImage[i] >= dlg.m_StartPoint &&
				m_InputImage[i] <= dlg.m_EndPoint)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = m_InputImage[i];
		}
	}
}

void CMy08150070Doc::OnHistoStretch()
{
	int i;
	unsigned char LOW,HIGH,MAX,MIN;

	LOW =0;
	HIGH = 255;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	
	MIN = m_InputImage[0]; // 최소값을 얻기위한 초기값
	MAX = m_InputImage[0]; // 최대값을 얻기위한 초기값

	//입력영상의 최대,최소값 찾기

	for(i=0;i<m_size;i++){
		if(m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}
	for(i=0;i<m_size;i++){
		if(m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];

	//히스토그램 Stretch
	for(i=0;i<m_size;i++){
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) * HIGH / (MAX-MIN));
	}

}

void CMy08150070Doc::OnEndInSearch()
{
	int i;
	unsigned char LOW,HIGH,MAX,MIN;

	LOW =0;
	HIGH = 255;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	MIN = m_InputImage[0]; // 최소값을 얻기위한 초기값
	MAX = m_InputImage[0]; // 최대값을 얻기위한 초기값
	
	for(i=0;i<m_size;i++){
		if(m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}
	for(i=0;i<m_size;i++){
		if(m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];
	
	for(i=0;i<m_size;i++){
		//원본영상보다 작은값은 0 
		if(m_InputImage[i]<=MIN){
			m_OutputImage[i] =0;
		}
		//원본영상보다 큰값은 255
		else if(m_InputImage[i]>=MAX){
			m_OutputImage[i] =255;
		}else
			m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) * HIGH / (MAX-MIN));
	}
}

void CMy08150070Doc::OnHistogram()
{
	//히스토그램의 값은 0-255
	//MAx값은 255, 크기는 256*256

	int i,j,value;
	unsigned char LOW,HIGH;
	double MAX,MIN,DIF;

	
	m_Re_height = 256;
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;

	LOW =0;
	HIGH = 255;
	
	//초기화
	for(i=0;i<256;i++)
		m_HIST[i] = LOW;

	//빈도수 조사 <- 히스토그램 프로그램의 핵심 **
	for(i=0;i<m_size;i++){
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	//정규화
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for(i=0;i<256;i++){
		if(m_HIST[i] > MAX)
			MAX = m_HIST[i];
	}

	for(i=0;i<256;i++){
		if(m_HIST[i] < MIN)
			MIN = m_HIST[i];
	}

	DIF = MAX - MIN; // 스케일링을 키움

	//정규화된 히스토그램
	for(i=0;i<256;i++)
		m_Scale_HIST[i] = (unsigned char) ((m_HIST[i]-MIN) * HIGH/DIF);

	//히스토그램 출력
	m_OutputImage = new unsigned char[m_Re_size + (256*20)]; 
	
	// 배경 초기화
	for(i=0;i<m_Re_size;i++)
		m_OutputImage[i] = 255; //흰색

	//정규화된 히스토그램 값은 검은점으로 표현
	for(i=0;i<256;i++){
		for(j=0; j<m_Scale_HIST[i]; j++){
			m_OutputImage[m_Re_width * (m_Re_height-j-1) +i] =0;
		}
	}

	//히스토그램을 출력하고 아래부분에 히스토그램 띠 표시
	for(i=m_Re_height; i<m_Re_height+5; i++){
		for(j=0; j<256; j++){
			m_OutputImage[m_Re_height * i + j] = 255;
		}
	}

	for(i= m_Re_height+5; i<m_Re_height+20; i++){
		for(j=0; j<256; j++){
			m_OutputImage[m_Re_height * i + j] = j;
		}
	}

	m_Re_height = m_Re_height +20;
	m_Re_size = m_Re_height * m_Re_width;

}
