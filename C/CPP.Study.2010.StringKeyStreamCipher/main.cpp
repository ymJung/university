#include "Main_Function.h"

void main(){
	char m_Choice;
	char m_SeedKey[BS];
	char m_KeyStream[MB];
	char m_FileMsg[MB];
	int m_FilemsgLength;
	double m_Keygentime;
	clock_t start=0,end=0;
	
	//클래스 객체 //
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
		*m_FileMsg = SC.Fileprint(); //파일 메시지를 배열로 받아야함.
		
		m_FilemsgLength = strlen(m_FileMsg); //파일 메시지 길이를 받음
		printf("%s,%d",m_FileMsg,m_FilemsgLength);
		SC.KeyIn();

		*m_SeedKey = SC.SeedkeySel(); // 시드키값을 받음.
				
		KG.KeygentimeStart(start);
		*m_KeyStream = KG.KeyStreamGen(m_SeedKey,m_FilemsgLength); // SC의 Seed로 생성한 키스트림-시드키,파일길이
		KG.KeygentimeEnd(end);
		m_Keygentime = KG.Key_gentime(start,end);
		
		SC.Keystreamprint(m_KeyStream);
		SC.Keygentimeprint(m_Keygentime);

		SC.XOROperation(m_FileMsg,m_KeyStream);
		
		cout<<"종료하시겠습니까?(y/else)"<<endl;
		fflush(stdin);
		cin>>m_Choice;
		
	}
	
	
}

