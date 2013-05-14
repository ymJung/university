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
	m_FilemsgLength = SC.FileLength(SC.Filemsg) ; //파일 메시지 길이를 받음
	*m_SeedKey = SC.SeedkeySel(SC.SeedKey); // 시드키값을 받음.

	KG.KeygentimeStart(start);
	*m_KeyStream = KG.KeyStreamGen(m_SeedKey,m_FilemsgLength); // SC의 Seed로 생성한 키스트림-시드키,파일길이
	KG.KeygentimeEnd(end);
	m_Keygentime = KG.Key_gentime(start,end);
	SC.Keygentimeprint(m_Keygentime);
	
	
}

