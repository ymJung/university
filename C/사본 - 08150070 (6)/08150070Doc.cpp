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
