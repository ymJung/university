#include "Main_Function.h"

void main(){
	char m_SeedKey[BS];
	char m_KeyStream[MB];
	char m_FileMsg[MB];
	int m_FilemsgLength;
	double m_Keygentime;
	clock_t start=0,end=0;

	Main_Encryption SC; // SC -> StreamCipher
	Key_generator KG; //KG -> KeyGenerator

//	SC.Programstart();

	*m_FileMsg = SC.Filemsgpass();
	m_FilemsgLength = SC.FileLength(SC.Filemsg) ; //���� �޽��� ���̸� ����
	*m_SeedKey = SC.SeedkeySel(SC.SeedKey); // �õ�Ű���� ����.

	KG.KeygentimeStart(start);
	*m_KeyStream = KG.KeyStreamGen(m_SeedKey,m_FilemsgLength); // SC�� Seed�� ������ Ű��Ʈ��-�õ�Ű,���ϱ���
	KG.KeygentimeEnd(end);
	m_Keygentime = KG.Key_gentime(start,end);
	SC.Keygentimeprint(m_Keygentime);
	
	
}

