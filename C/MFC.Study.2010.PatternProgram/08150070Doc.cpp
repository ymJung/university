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
	CFile File; //���� ��ü

	File.Open(lpszPathName,CFile::modeRead|CFile::typeBinary);
	//���� ���� ��ȭ���ڿ��� ������ ������ �����ϰ� �б��� ����

	//256*256, 512*512, 640*480 ����
	if(File.GetLength() == 256*256){ //RAW���� �ػ� ����
		m_height = 256;
		m_width = 256;
	}else if(File.GetLength() == 512*512){
		m_height = 512;
		m_width = 512;
	}else if(File.GetLength() == 640*480){
		m_height = 480;
		m_width = 640;
	}else{
		AfxMessageBox("�������� �ʴ� �̹��� ����!");
		return 0;
	}

	m_size = m_width * m_height;
	//���� ũ�� ���
	
	m_InputImage = new unsigned char[m_size]; //��� ������ ������
	//�Է¿��� ũ�⿡ �´� ���� �޸� �Ҵ�

	for(int i =0;i<m_size;i++)
		m_InputImage[i] = 255; // �ʱ�ȭ
	File.Read(m_InputImage,m_size); //�Է� ������  m_InputImage�� ����
	File.Close(); // ���� �ݱ�

	return TRUE;
}

BOOL CMy08150070Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	CFile File; // ���ϰ�ü ���� ���� �������
	CFileDialog SaveDlg(FALSE,"raw",NULL,OFN_HIDEREADONLY);
	//raw ������ �ٸ��̸����� �����ϱ� ���� ��ȭ��ü ����

	if(SaveDlg.DoModal() == IDOK){
		//DoModal ��� �Լ����� �����ϱ� ����
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		//���� ����
		File.Write(m_InputImage,m_size); 
		// ���� ����
		File.Close();
		//���� �ݱ�
	}
	return CDocument::OnSaveDocument(lpszPathName);
}

void CMy08150070Doc::OnDownSampling()
{
	int i,j;
	CDownSampleDlg dlg;
	if(dlg.DoModal() == IDOK) // ��ȭ������ Ȱ��ȭ ����
	{
		m_Re_height = m_height / dlg.m_DownSampleRate; //��� ���� ���� ���� 
		m_Re_width = m_width / dlg.m_DownSampleRate; // ��� ���� ���� ����
		m_Re_size = m_Re_height * m_Re_width; // ��� ���� ũ�� ���

		m_OutputImage = new unsigned char [m_Re_size]; // ��ҿ��� �޸� �Ҵ�

		for(i=0;i<m_Re_height;i++){
			for(j=0;j<m_Re_width;j++){
				m_OutputImage[i*m_Re_width+j]
					= m_InputImage[(i*dlg.m_DownSampleRate*m_width)+dlg.m_DownSampleRate*j];
				// ��� ������ ���� �ϱ� ���� ���
			}
		}
	}
}

void CMy08150070Doc::OnUpSampling()
{
	int i,j;
	CUpSampleDlg dlg;
	if(dlg.DoModal() == IDOK){ //��޴�ȭ����
		m_Re_height = m_height * dlg.m_UpSampleRate; //Ȯ�뿵�� ����
		m_Re_width = m_width * dlg.m_UpSampleRate; // Ȯ�뿵�� ����
		m_Re_size = m_Re_height * m_Re_width; // Ȯ�뿵�� ũ��
		m_OutputImage = new unsigned char[m_Re_size]; // Ȯ�뿵�� ���� �޸�

		for(i=0;i<m_Re_size;i++)
			m_OutputImage[i] =0; //�ʱ�ȭ
		for(i=0;i<m_height;i++){
			for(j=0;j<m_width;j++){
				m_OutputImage[i*dlg.m_UpSampleRate*m_Re_width+dlg.m_UpSampleRate*j] //��� ������ ������ ����
					= m_InputImage[i*m_width+j];

				m_OutputImage[(i*dlg.m_UpSampleRate+1)*m_Re_width+(dlg.m_UpSampleRate*j)] //2��� �� ������ ä����
					= m_InputImage[i*m_width+j];

				m_OutputImage[(i*dlg.m_UpSampleRate)*m_Re_width+(dlg.m_UpSampleRate*j+1)] //2��� �� ������ ä����
					= m_InputImage[i*m_width+j];

				m_OutputImage[(i*dlg.m_UpSampleRate+1)*m_Re_width+(dlg.m_UpSampleRate*j+1)] //2��� �� ������ ä����
					= m_InputImage[i*m_width+j];
			}

		}
	}

}

void CMy08150070Doc::OnQuantization()
{
	CQuantizationDlg dlg;
	if(dlg.DoModal() == IDOK) //��� Ȱ��ȭ
	{
		int i,j, value,LEVEL;
		double HIGH, *TEMP;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];// �޸��Ҵ�
		TEMP = new double [m_size]; //�Է¿���� ������ �޸� �Ҵ�

		LEVEL = 256; //�Է¿��� ����ȭ �ܰ�
		HIGH = 256; 

		value = (int)pow(2,dlg.m_QuantiBit);
		//����ȭ �ܰ����

		for(i=0;i<m_size;i++){
			for(j=0;j<value;j++){
				if(m_InputImage[i] >= (LEVEL/value)*j && m_InputImage[i] < (LEVEL/value)*(j+1)){
					TEMP[i] = (double)(HIGH/value)*j; // ����ȭ ����
				}
			}
		}
		for(i=0;i<m_size;i++){
			m_OutputImage[i] = (unsigned char)TEMP[i]; //��� ����
		}
	}


}

void CMy08150070Doc::OnSumConstant()
{
	
	CConstantDlg dlg; //����� �Է¹޴� ��ȭ����
	
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0; i<m_size; i++){
			
			if(m_InputImage[i] + dlg.m_Constant >= 255) //255���� Ŭ�� 255�� ����
				m_OutputImage[i] = 255; 
			else
				m_OutputImage[i]=(unsigned char)(m_InputImage[i] + dlg.m_Constant); //����
		}
	}

}

void CMy08150070Doc::OnSubConstant()
{
	
	CConstantDlg dlg; //����� �Է¹޴� ��ȭ����
	
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0; i<m_size; i++){
			
			if(m_InputImage[i] + dlg.m_Constant >= 255) //255���� Ŭ�� 255�� ����
				m_OutputImage[i] = 255; 
			else
				m_OutputImage[i]=(unsigned char)(m_InputImage[i] - dlg.m_Constant); //����
		}
	}

}

void CMy08150070Doc::OnMulConstant()
{
	
	CConstantDlg dlg; //����� �Է¹޴� ��ȭ����
	
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0; i<m_size; i++){
			
			if(m_InputImage[i] + dlg.m_Constant >= 255) //255���� Ŭ�� 255�� ����
				m_OutputImage[i] = 255; 
			else
				m_OutputImage[i]=(unsigned char)(m_InputImage[i] * dlg.m_Constant); //����
		}
	}

}

void CMy08150070Doc::OnDivConstant()
{
	
	CConstantDlg dlg; //����� �Է¹޴� ��ȭ����
	
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if(dlg.DoModal() == IDOK){
		for(i=0; i<m_size; i++){
			
			if(m_InputImage[i] + dlg.m_Constant >= 255) //255���� Ŭ�� 255�� ����
				m_OutputImage[i] = 255; 
			else
				m_OutputImage[i]=(unsigned char)(m_InputImage[i] / dlg.m_Constant); //������
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
			//255���� ũ�� 255 ���
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
			//255���� ũ�� 255 ���
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
			//255���� ũ�� 255 ���
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
		m_OutputImage[i] = 255 - m_InputImage[i]; //�������


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
			temp = pow(m_InputImage[i], 1/dlg.m_Constant); //���������
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
				m_OutputImage[i] = 255; //�Ӱ� ������ ũ�� 255 ����
			else
				m_OutputImage[i] = 0; // �Ӱ谪 ���� ������ 0 ����
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
			//�Է°��� ���� ���۰��� ���� ���� �� ���̿� ��ġ�� 255 ���
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
	
	MIN = m_InputImage[0]; // �ּҰ��� ������� �ʱⰪ
	MAX = m_InputImage[0]; // �ִ밪�� ������� �ʱⰪ

	//�Է¿����� �ִ�,�ּҰ� ã��

	for(i=0;i<m_size;i++){
		if(m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}
	for(i=0;i<m_size;i++){
		if(m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];

	//������׷� Stretch
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

	MIN = m_InputImage[0]; // �ּҰ��� ������� �ʱⰪ
	MAX = m_InputImage[0]; // �ִ밪�� ������� �ʱⰪ
	
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
		//�������󺸴� �������� 0 
		if(m_InputImage[i]<=MIN){
			m_OutputImage[i] =0;
		}
		//�������󺸴� ū���� 255
		else if(m_InputImage[i]>=MAX){
			m_OutputImage[i] =255;
		}else
			m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) * HIGH / (MAX-MIN));
	}
}

void CMy08150070Doc::OnHistogram()
{
	//������׷��� ���� 0-255
	//MAx���� 255, ũ��� 256*256

	int i,j,value;
	unsigned char LOW,HIGH;
	double MAX,MIN,DIF;

	
	m_Re_height = 256;
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;

	LOW =0;
	HIGH = 255;
	
	//�ʱ�ȭ
	for(i=0;i<256;i++)
		m_HIST[i] = LOW;

	//�󵵼� ���� <- ������׷� ���α׷��� �ٽ� **
	for(i=0;i<m_size;i++){
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	//����ȭ
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

	DIF = MAX - MIN; // �����ϸ��� Ű��

	//����ȭ�� ������׷�
	for(i=0;i<256;i++)
		m_Scale_HIST[i] = (unsigned char) ((m_HIST[i]-MIN) * HIGH/DIF);

	//������׷� ���
	m_OutputImage = new unsigned char[m_Re_size + (256*20)]; 
	
	// ��� �ʱ�ȭ
	for(i=0;i<m_Re_size;i++)
		m_OutputImage[i] = 255; //���

	//����ȭ�� ������׷� ���� ���������� ǥ��
	for(i=0;i<256;i++){
		for(j=0; j<m_Scale_HIST[i]; j++){
			m_OutputImage[m_Re_width * (m_Re_height-j-1) +i] =0;
		}
	}

	//������׷��� ����ϰ� �Ʒ��κп� ������׷� �� ǥ��
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

void CMy08150070Doc::OnHistoEqual()
{
	int i,value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	//�ʱ�ȭ
	for(i=0;i<256;i++)
		m_HIST[i] = LOW;

	// �� �� ����
	for(i=0;i<m_size;i++){
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	//���� ������׷�
	for(i=0;i<256;i++){
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}

	m_OutputImage = new unsigned char[m_Re_size];
	//�Է¿����� ��Ȱȭ�� �������� ���
	for(i=0;i<m_size;i++){
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH/m_size);
	}


}

void CMy08150070Doc::OnEmbossing()
{
	int i,j;
	//double EmboMask[3][3] = {{-1.,0.,0.},{0.,0.,0.,},{0.,0.,1.}};
	//����ũ ����
	//double EmboMask[3][3] = {{0.,0.,0.},{0.,1.,0.,},{0.,0.,0.}};
	double EmboMask[3][3] = {{1.,1.,1.},{1.,-8.,1.,},{1.,1.,1.}};

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];
	
	//OnMaskProcess �Լ� ȣ���Ͽ� ȸ�� ó���� �Ѵ�.
	m_tempImage = OnMaskProcess(m_InputImage, EmboMask);

	for(i=0;i<m_Re_height; i++){
		for(j=0;j<m_Re_width;j++){
			if(m_tempImage[i][j]>255.)
				m_tempImage[i][j] = 255.;
			if(m_tempImage[i][j]<0) // ������� �����Ͻ� 0����
				m_tempImage[i][j] = 0.;
		}
	} //  ȸ��ó�� ����� 0~255 ���� ���� �ǵ��� �Ѵ�.
	
	// m_tempImage = OnScale(m_tempImage,m_Re_height,m_Re_width);
	//����ȭ�� ���

	//ȸ��ó�� ����� ����ȭ ó�� ����� 2���� �迭���� �ǹǷ�
	//2���� �迭�� 1���� �迭�� �ٲپ� ����Ѵ�.

	for(i=0;i<m_Re_height;i++){
		for(j=0;j<m_Re_width;j++){
			m_OutputImage[i*m_Re_width +j] = (unsigned char)m_tempImage[i][j];
		}
	}
}

double** CMy08150070Doc::OnMaskProcess(unsigned char *Target, double Mask[3][3])
{
	//ȸ��ó���� �Ͼ
	int i,j,n,m;
	double **tempInputImage, **tempOutputImage,s=0.0;

	//�Է°��� ���� �޸� �Ҵ�
	tempInputImage = Image2DMem(m_height + 2,m_width +2);
	//��°��� ���� �޸� �Ҵ�
	tempOutputImage = Image2DMem(m_height,m_width);

	//1���� �Է¿����� ���� 2���� �迭�� �Ҵ��Ѵ�.
	for(i=0;i<m_height;i++){
		for(j=0;j<m_width;j++){
			tempInputImage[i+1][j+1] = (double)Target[i*m_width + j];
		}
	}

	//ȸ������ ������� 1���� ����
	for(i=0;i<m_height;i++){
		for(j=0;j<m_width;j++){
			for(n=0;n<3;n++){
				for(m=0;m<3;m++){
					s+=Mask[n][m] * tempInputImage[i+n][j+m];
				}
			} //ȸ�� ����ũ�� ũ�⸸ŭ �̵��ϸ� ���� ����
			tempOutputImage[i][j] = s; //�������� ��� �޸𸮿� ����
			s = 0.0; // ���� �� �̵� ���� ���� �ʱ�ȭ
		}
	}
	return tempOutputImage; // ����� ��ȯ

}

double** CMy08150070Doc::OnScale(double **Target, int height, int width)
{
	// ����ȭ�� ���� �Լ�
	int i,j;
	double min,max;

	min = max = Target[0][0];

	for(i=0;i<height;i++){
		for(j=0;j<width; j++){
			if(Target[i][j] <= min)
				min = Target[i][j];
		}
	}
	
	for(i=0;i<height;i++){
		for(j=0;j<width; j++){
			if(Target[i][j] >= max)
				max = Target[i][j];
		}
	}

	max = max - min;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			Target[i][j] = (Target[i][j] - min) * (255. / max);
		}
	}
	return Target;

}

double** CMy08150070Doc::Image2DMem(int height,int width)
{ // 2���� �޸� �Ҵ��� ���� �Լ�
	double** temp;
	int i,j;
	temp = new double *[height];
	for(i=0;i<height;i++){
		temp[i] = new double [width];
	}
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			temp[i][j] = 0.0; //�޸� �ʱ�ȭ 
		}
	}
	return temp;

}

void CMy08150070Doc::OnBlurr()
{
	int i,j;
	double BlurrMask[3][3] = {{1./9.,1./9.,1./9.},{1./9.,1./9.,1./9.,},{1./9.,1./9.,1./9.}};
	//����ũ ����

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];
	
	//OnMaskProcess �Լ� ȣ���Ͽ� ȸ�� ó���� �Ѵ�.
	m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);

	for(i=0;i<m_Re_height; i++){
		for(j=0;j<m_Re_width;j++){
			if(m_tempImage[i][j]>255.)
				m_tempImage[i][j] = 255.;
			if(m_tempImage[i][j]<0) // ������� �����Ͻ� 0����
				m_tempImage[i][j] = 0.;
		}
	} //  ȸ��ó�� ����� 0~255 ���� ���� �ǵ��� �Ѵ�.
	
	// m_tempImage = OnScale(m_tempImage,m_Re_height,m_Re_width);
	//����ȭ�� ���

	//ȸ��ó�� ����� ����ȭ ó�� ����� 2���� �迭���� �ǹǷ�
	//2���� �迭�� 1���� �迭�� �ٲپ� ����Ѵ�.

	for(i=0;i<m_Re_height;i++){
		for(j=0;j<m_Re_width;j++){
			m_OutputImage[i*m_Re_width +j] = (unsigned char)m_tempImage[i][j];
		}
	}

}

void CMy08150070Doc::OnGaussianFilter()
{
	int i,j;
	double GaussianMask[3][3] = {{1./16.,1./8.,1./16.},{1./8.,1./4.,1./8.,},{1./16.,1./8.,1./16.}};
	//����ũ ����

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];
	
	//OnMaskProcess �Լ� ȣ���Ͽ� ȸ�� ó���� �Ѵ�.
	m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);

	for(i=0;i<m_Re_height; i++){
		for(j=0;j<m_Re_width;j++){
			if(m_tempImage[i][j]>255.)
				m_tempImage[i][j] = 255.;
			if(m_tempImage[i][j]<0) // ������� �����Ͻ� 0����
				m_tempImage[i][j] = 0.;
		}
	} //  ȸ��ó�� ����� 0~255 ���� ���� �ǵ��� �Ѵ�.
	
	// m_tempImage = OnScale(m_tempImage,m_Re_height,m_Re_width);
	//����ȭ�� ���

	//ȸ��ó�� ����� ����ȭ ó�� ����� 2���� �迭���� �ǹǷ�
	//2���� �迭�� 1���� �迭�� �ٲپ� ����Ѵ�.

	for(i=0;i<m_Re_height;i++){
		for(j=0;j<m_Re_width;j++){
			m_OutputImage[i*m_Re_width +j] = (unsigned char)m_tempImage[i][j];
		}
	}
}

void CMy08150070Doc::OnSharpening()
{
	int i,j;
	double SharpMask[3][3] = {{-1.,-1.,-1.},{-1.,9.,-1.,},{-1.,-1.,-1.}};
	//����ũ ����

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];
	
	//OnMaskProcess �Լ� ȣ���Ͽ� ȸ�� ó���� �Ѵ�.
	m_tempImage = OnMaskProcess(m_InputImage, SharpMask);

	for(i=0;i<m_Re_height; i++){
		for(j=0;j<m_Re_width;j++){
			if(m_tempImage[i][j]>255.)
				m_tempImage[i][j] = 255.;
			if(m_tempImage[i][j]<0) // ������� �����Ͻ� 0����
				m_tempImage[i][j] = 0.;
		}
	} //  ȸ��ó�� ����� 0~255 ���� ���� �ǵ��� �Ѵ�.
	
	// m_tempImage = OnScale(m_tempImage,m_Re_height,m_Re_width);
	//����ȭ�� ���

	//ȸ��ó�� ����� ����ȭ ó�� ����� 2���� �迭���� �ǹǷ�
	//2���� �迭�� 1���� �迭�� �ٲپ� ����Ѵ�.

	for(i=0;i<m_Re_height;i++){
		for(j=0;j<m_Re_width;j++){
			m_OutputImage[i*m_Re_width +j] = (unsigned char)m_tempImage[i][j];
		}
	}

}

void CMy08150070Doc::OnHpfSharp()
{
	int i,j;
	//double HpfSharpMask[3][3] = {{-1./9.,-1./9.,-1./9.},{-1./9.,8./9.,-1./9.,},{-1./9.,-1./9.,-1./9.}};
	double HpfSharpMask[3][3] = {{-1.,-1.,-1.},{-1.,8.,-1.,},{-1.,-1.,-1.}};
	//����ũ ����

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];
	
	//OnMaskProcess �Լ� ȣ���Ͽ� ȸ�� ó���� �Ѵ�.
	m_tempImage = OnMaskProcess(m_InputImage, HpfSharpMask);

	for(i=0;i<m_Re_height; i++){
		for(j=0;j<m_Re_width;j++){
			if(m_tempImage[i][j]>255.)
				m_tempImage[i][j] = 255.;
			if(m_tempImage[i][j]<0) // ������� �����Ͻ� 0����
				m_tempImage[i][j] = 0.;
		}
	} //  ȸ��ó�� ����� 0~255 ���� ���� �ǵ��� �Ѵ�.
	
	// m_tempImage = OnScale(m_tempImage,m_Re_height,m_Re_width);
	//����ȭ�� ���

	//ȸ��ó�� ����� ����ȭ ó�� ����� 2���� �迭���� �ǹǷ�
	//2���� �迭�� 1���� �迭�� �ٲپ� ����Ѵ�.

	for(i=0;i<m_Re_height;i++){
		for(j=0;j<m_Re_width;j++){
			m_OutputImage[i*m_Re_width +j] = (unsigned char)m_tempImage[i][j];
		}
	}

}

void CMy08150070Doc::OnLpfSharp()
{
	CConstantDlg dlg;
	
	int alpha;

	int i,j;
	double LpfSharpMask[3][3] = {{1./9.,1./9.,1./9.},{1./9.,1./9.,1./9.,},{1./9.,1./9.,1./9.}};
	//����ũ ����

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];

	if(dlg.DoModal() == IDOK){
		//��ȭ���� �̿� ��� �Է¹���
		alpha = (int)dlg.m_Constant;
	}
	
	//OnMaskProcess �Լ� ȣ���Ͽ� ȸ�� ó���� �Ѵ�.
	m_tempImage = OnMaskProcess(m_InputImage, LpfSharpMask);

	for(i=0;i<m_height;i++){
		for(j=0;j<m_width;j++){
			m_tempImage[i][j] = (alpha * m_InputImage [i*m_width + j]) 
				- (unsigned char) m_tempImage[i][j];
		}
	}


	for(i=0;i<m_Re_height; i++){
		for(j=0;j<m_Re_width;j++){
			if(m_tempImage[i][j]>255.)
				m_tempImage[i][j] = 255.;
			if(m_tempImage[i][j]<0) // ������� �����Ͻ� 0����
				m_tempImage[i][j] = 0.;
		}
	} //  ȸ��ó�� ����� 0~255 ���� ���� �ǵ��� �Ѵ�.
	
	// m_tempImage = OnScale(m_tempImage,m_Re_height,m_Re_width);
	//����ȭ�� ���

	//ȸ��ó�� ����� ����ȭ ó�� ����� 2���� �迭���� �ǹǷ�
	//2���� �迭�� 1���� �迭�� �ٲپ� ����Ѵ�.

	for(i=0;i<m_Re_height;i++){
		for(j=0;j<m_Re_width;j++){
			m_OutputImage[i*m_Re_width +j] = (unsigned char)m_tempImage[i][j];
		}
	}


}

void CMy08150070Doc::OnDiffOperatorHor()
{
	int i,j;
	//double DiffHorMask[3][3] = {{0.,-1.,0.},{0.,1.,0.,},{0.,0.,0.}};
	double DiffHorMask[3][3] = {{0.,0.,0.},{-1.,1.,0.,},{0.,0.,0.}};
	
	//�������� ����

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];
	
	//OnMaskProcess �Լ� ȣ���Ͽ� ȸ�� ó���� �Ѵ�.
	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for(i=0;i<m_Re_height; i++){
		for(j=0;j<m_Re_width;j++){
			if(m_tempImage[i][j]>255.)
				m_tempImage[i][j] = 255.;
			if(m_tempImage[i][j]<0) // ������� �����Ͻ� 0����
				m_tempImage[i][j] = 0.;
		}
	} //  ȸ��ó�� ����� 0~255 ���� ���� �ǵ��� �Ѵ�.
	
	

	for(i=0;i<m_Re_height;i++){
		for(j=0;j<m_Re_width;j++){
			m_OutputImage[i*m_Re_width +j] = (unsigned char)m_tempImage[i][j];
		}
	}

}

void CMy08150070Doc::OnHomogenOperator()
{
	int i,j,n,m;
	double max, **tempOutputImage;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];
	
	m_tempImage = Image2DMem(m_height + 2, m_width +2);
	tempOutputImage = Image2DMem(m_Re_height,m_Re_width);
	
	for(i=0;i<m_height;i++){
		for(j=0;j<m_width;j++){
			m_tempImage[i+1][j+1] = (double)m_InputImage[i*m_width +j];
		}
	}

	for(i=0;i<m_height;i++){
		for(j=0;j<m_width;j++){
			max = 0.0; //��� �̵��� ���� �ʱ�ȭ
			for(n =0;n<3;n++){
				for(m=0;m<3;m++){
					if(DoubleABS(m_tempImage[i+1][j+1] - m_tempImage[i+n][j+m]) >= max)
						//��� ��� �� - �ֺ��ȼ� �� �� �ִ밪 Ž��
						max = DoubleABS(m_tempImage[i+1][j+1] - m_tempImage[i+n][j+m]);
				}
			}
			tempOutputImage[i][j] = max; //ã�� �ִ밪�� ��°� ����
		}
	}

	for(i=0;i<m_Re_height; i++){
		for(j=0;j<m_Re_width;j++){
			if(tempOutputImage[i][j]>255.)
				tempOutputImage[i][j] = 255.;
			if(tempOutputImage[i][j]<0) // ������� �����Ͻ� 0����
				tempOutputImage[i][j] = 0.;
		}
	} //  ȸ��ó�� ����� 0~255 ���� ���� �ǵ��� �Ѵ�.
	

	//ȸ��ó�� ����� ����ȭ ó�� ����� 2���� �迭���� �ǹǷ�
	//2���� �迭�� 1���� �迭�� �ٲپ� ����Ѵ�.
	
	for(i=0;i<m_Re_height;i++){
		for(j=0;j<m_Re_width;j++){
			m_OutputImage[i*m_Re_width +j] = (unsigned char)tempOutputImage[i][j];
		}
	}

}
	
double CMy08150070Doc::DoubleABS(double X)
{
	if(X >=0)
		return X;
	else
		return -X;
}

void CMy08150070Doc::OnLaplacian()
{
	
	int i,j, sum=0;
	double LaplacianMask[3][3] = {{0.,-1.,0.},   {-1.,4.,-1.},   {0.,-1.,0.}};
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];

	//OnMaskProcess �Լ� ȣ���Ͽ� ȸ�� ó���� �Ѵ�.
	m_tempImage = OnMaskProcess(m_InputImage,LaplacianMask);

	 //  ȸ��ó�� ����� 0~255 ���� ���� �ǵ��� �Ѵ�.
	for(i=0; i<m_Re_height; i++){
		for(j=0; j<m_Re_width; j++){
			if(m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if(m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for(i=0; i < m_Re_height; i++){
		for(j=0; j < m_Re_width; j++){
			m_OutputImage[i*m_Re_width +j]
				=(unsigned char)m_tempImage[i][j];
		}
	} 
	
}

void CMy08150070Doc::OnSobel()
{
	int i,j,k,l, dH,dV,mag;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];

	//roberts
	// int Hmask[3][3] = {{-1,0,0},   {0,1,0},   {0,0,0}};
	//int	Vmask[3][3] = {{0,0,-1},   {0,1,0},   {0,0,0}};
	//prewitt
	//int Hmask[3][3] = {{-1,-1,-1},   {0,0,0},   {1,1,1}};
	//int	Vmask[3][3] = {{-1,0,1},   {-1,0,1},   {-1,0,1}};
	//sobel
	int Hmask[3][3] = {{-1,-2,-1},   {0,0,0},   {1,2,1}};
	int	Vmask[3][3] = {{1,0,-1},	{2,0,-2},	{1,0,-1}};
	
	for(i=1;i<m_height-1;i++)
		for(j=1;j<m_width-1;j++){
			dH =0;
			dV =0;
			for(k=-1;k<2;k++)
				for(l=-1;l<2;l++){
					dH+=m_InputImage[(i+k)*m_width+j+l]*Hmask[k+1][l+1];
					dV+=m_InputImage[(i+k)*m_width+j+l]*Vmask[k+1][l+1];
				}
			mag = (int)sqrt(dH*dH+dV*dV)*2;
		
			if(mag>255)
				m_OutputImage[(i+k)*m_width+j+l] = 255;
			else
				m_OutputImage[(i+k)*m_width+j+l] = mag;
		}

}

void CMy08150070Doc::OnRoberts()
{
	int i,j,k,l, dH,dV,mag;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];

	//roberts
	int Hmask[3][3] = {{-1,0,0},   {0,1,0},   {0,0,0}};
	int	Vmask[3][3] = {{0,0,-1},   {0,1,0},   {0,0,0}};
	//prewitt
	//int Hmask[3][3] = {{-1,-1,-1},   {0,0,0},   {1,1,1}};
	//int	Vmask[3][3] = {{-1,0,1},   {-1,0,1},   {-1,0,1}};
	//sobel
	//int Hmask[3][3] = {{-1,-2,-1},   {0,0,0},   {1,2,1}};
	//int	Vmask[3][3] = {{1,0,-1},	{2,0,-2},	{1,0,-1}};
	
	for(i=1;i<m_height-1;i++)
		for(j=1;j<m_width-1;j++){
			dH =0;
			dV =0;
			for(k=-1;k<2;k++)
				for(l=-1;l<2;l++){
					dH+=m_InputImage[(i+k)*m_width+j+l]*Hmask[k+1][l+1];
					dV+=m_InputImage[(i+k)*m_width+j+l]*Vmask[k+1][l+1];
				}
			mag = (int)sqrt(dH*dH+dV*dV)*2;
		
			if(mag>255)
				m_OutputImage[(i+k)*m_width+j+l] = 255;
			else
				m_OutputImage[(i+k)*m_width+j+l] = mag;
		}
}

void CMy08150070Doc::OnPrewitt()
{
	int i,j,k,l, dH,dV,mag;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];

	//roberts
	// int Hmask[3][3] = {{-1,0,0},   {0,1,0},   {0,0,0}};
	//int	Vmask[3][3] = {{0,0,-1},   {0,1,0},   {0,0,0}};
	//prewitt
	int Hmask[3][3] = {{-1,-1,-1},   {0,0,0},   {1,1,1}};
	int	Vmask[3][3] = {{-1,0,1},   {-1,0,1},   {-1,0,1}};
	//sobel
	//int Hmask[3][3] = {{-1,-2,-1},   {0,0,0},   {1,2,1}};
	//int	Vmask[3][3] = {{1,0,-1},	{2,0,-2},	{1,0,-1}};
	
	for(i=1;i<m_height-1;i++)
		for(j=1;j<m_width-1;j++){
			dH =0;
			dV =0;
			for(k=-1;k<2;k++)
				for(l=-1;l<2;l++){
					dH+=m_InputImage[(i+k)*m_width+j+l]*Hmask[k+1][l+1];
					dV+=m_InputImage[(i+k)*m_width+j+l]*Vmask[k+1][l+1];
				}
			mag = (int)sqrt(dH*dH+dV*dV)*2;
		
		 	if(mag>255) 
				m_OutputImage[(i+k)*m_width+j+l] = 255;
			else
				m_OutputImage[(i+k)*m_width+j+l] = mag;
		}
}

void CMy08150070Doc::OnBilinear()
{
	CConstantDlg dlg;
	double ZoomRate;
	if(dlg.DoModal() == IDOK){
		//��ȭ���� �̿� ��� �Է¹���
		ZoomRate = dlg.m_Constant;
	}
	
	int i,j,point,i_H,i_W;
	unsigned char newValue;
	
	double r_H,r_W,s_H,s_W;
	double C1,C2,C3,C4;

	
	m_Re_height = (int)(m_height * ZoomRate);
	m_Re_width = (int)(m_width * ZoomRate);
	m_Re_size = m_Re_height * m_Re_width;
	
	m_tempImage =Image2DMem(m_height, m_width);
	m_OutputImage = new unsigned char [m_Re_size];
	
	for(i=0; i<m_height; i++){
		for(j=0; j<m_width; j++){
			m_tempImage[i][j] = (double)m_InputImage[i*m_width +j];
		}
	}
	for(i=0; i<m_Re_height; i++){
		for(j=0; j<m_Re_width; j++){
			r_H = i / ZoomRate;
			r_W = j / ZoomRate;
			
			i_H = (int)floor(r_H);
			i_W = (int)floor(r_W);
			
			s_H = r_H - i_H;
			s_W = r_W - i_W;
			
			if(i_H < 0 || i_H >= (m_height-1) || i_W<0|| i_W >= (m_width-1))
			{
				point = i* m_Re_width +j;
				m_OutputImage[point] = 255;
			}
			
			else
			{
				C1 = (double)m_tempImage[i_H][i_W];
				C2 = (double)m_tempImage[i_H][i_W+1];
				C3 = (double)m_tempImage[i_H+1][i_W+1];
				C4 = (double)m_tempImage[i_H+1][i_W];
				
				newValue = (unsigned char) (C1*(1-s_H) *(1-s_W)+C2*s_W*(1-s_H) +C3*s_W*s_H+C4*(1-s_W)*s_H);
				point = i* m_Re_width+j;
				m_OutputImage[point] = newValue;
			}
		}
	}
}

void CMy08150070Doc::OnMedianSub()
{
	int M;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK){
		//��ȭ���� �̿� ��� �Է¹���
		M = (int)dlg.m_Constant;
	}

	int i,j,n,m,index=0;
	double *Mask,Value;

	Mask = new double [M*M]; // ����ũ�� ũ��

	m_Re_height = (m_height+1)/ M;
	m_Re_width = (m_width+1)/M;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage= new unsigned char [m_Re_size];
	m_tempImage = Image2DMem(m_height+1,m_width+1);

	for(i=0;i<m_height;i++){
		for(j=0;j<m_width;j++){
			m_tempImage[i][j] = (double)m_InputImage[i*m_width+j];
		}
	}
	for(i=0;i<m_height-1;i=i+M){
		for(j=0;j<m_width-1;j=j+M){
			for(n=0;n<M;n++){
				for(m=0;m<M;m++){
					Mask[n*M+m] = m_tempImage[i+n][j+m];
				}
			}
			OnBubleSort(Mask,M*M);
			Value = Mask[(int)(M*M/2)];
			m_OutputImage[index] = (unsigned char)Value;
			index++;
		}
	}
}

void CMy08150070Doc::OnBubleSort(double *A, int MAX)
{
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX-1;j++){
			if(A[j]>A[j+1]){
				OnSwap(&A[j],&A[j+1]);
			}
		}
	}
}

void CMy08150070Doc::OnSwap(double *a, double *b)
{
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void CMy08150070Doc::OnMeanSub()
{
	int M;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK){
		//��ȭ���� �̿� ��� �Է¹���
		M = (int)dlg.m_Constant;
	}

	int i,j,n,m,index=0,k;
	double *Mask,Value,Sum =0.0;

	Mask = new double [M*M];

	m_Re_height = (m_height+1)/ M;
	m_Re_width = (m_width+1)/M;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage= new unsigned char [m_Re_size];
	m_tempImage = Image2DMem(m_height+1,m_width+1);

	for(i=0;i<m_height;i++){
		for(j=0;j<m_width;j++){
			m_tempImage[i][j] = (double)m_InputImage[i*m_width+j];
		}
	}
	for(i=0;i<m_height-1;i=i+M){
		for(j=0;j<m_width-1;j=j+M){
			for(n=0;n<M;n++){
				for(m=0;m<M;m++){
					Mask[n*M+m] = m_tempImage[i+n][j+m];
				}
			}
			for(k=0;k<M*M;k++)
				Sum = Sum + Mask[k];
			Value = (Sum/(M*M));
			m_OutputImage[index] = (unsigned char)Value;
			index++;
			Sum = 0.0;
		}
			
	}

}
