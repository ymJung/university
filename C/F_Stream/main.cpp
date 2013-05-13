#include "Main_Encryption.h"
#include "Key_generator.h"

void main(){
	char m_Choice;
//	char *m_SeedKey;
	char *m_KeyStream;
	char *m_FileMsg;
	int m_FilemsgLength;
	double m_Keygentime;
	clock_t start=0,end=0;
	
	//Ŭ���� ��ü //
	Main_Encryption SC; // SC -> StreamCipher
	Key_generator KG; //KG -> KeyGenerator

	//	SC.Programstart();
	/* ProgramStart()
	Main_Encryption::Fileread(Main_Encryption::InFilename); //1st
	Main_Encryption::Fileprint(); //2st
	Main_Encryption::KeyIn(); //3st
	Main_Encryption::Keystreamprint(Main_Encryption::SeedKey); //4st	
	Main_Encryption::Keygentimeprint(Main_Encryption::Keygentime); //5st
	Main_Encryption::OutFilenameSel(); //6st
	Main_Encryption::XOROperation(Main_Encryption::Filemsg,Main_Encryption::KeyStream); //7st
	Main_Encryption::Outputprint(); // 8st
	Main_Encryption::Restart(); //9st
	Main_Encryption::Filewrite(Main_Encryption::OutFilename); //10st
	Exit() */
	while(m_Choice !='y'){
		SC.FilenameSel();
		m_FileMsg = SC.Fileprint(); //���� �޽����� �迭�� �޾ƾ���.
		
		m_FilemsgLength = strlen(m_FileMsg); //���� �޽��� ���̸� ����
		
		SC.KeyIn();

		SC.SeedkeySel(); // �õ�Ű���� ����.
						
		start = KG.KeygentimeStart(start);
		m_KeyStream = KG.KeyStreamGen(SC.SeedKey,m_FilemsgLength); // SC�� Seed�� ������ Ű��Ʈ��-�õ�Ű,���ϱ���
		end = KG.KeygentimeEnd(end);
		m_Keygentime = KG.Key_gentime(start,end);
		
		SC.Keystreamprint(m_KeyStream);
		SC.Keygentimeprint(m_Keygentime);

		SC.XOROperation(m_FileMsg,m_KeyStream);
		
		cout<<"�����Ͻðڽ��ϱ�?(y/else)"<<endl;
		fflush(stdin);
		cin>>m_Choice;
		
	}
}