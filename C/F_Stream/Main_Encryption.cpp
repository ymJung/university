#include "Main_Encryption.h"

void Main_Encryption::ProgramStart(){ // --�����Ұ�.
//	Main_Encryption::FilenameSel();
	
}

void Main_Encryption::KeyIn(){		
	cout << "Ű�� �Է��ϼ���"<<endl;
	cin >> SeedKey;				
	//	Main_Encryption::Keystreamprint(Main_Encryption::SeedKey); //4st
}

char* Main_Encryption::SeedkeySel(){ //KeyGenŬ������ ������ SeedŰ
	char *Key;
	Key = SeedKey;
	return Key;
}

void Main_Encryption::Keystreamprint(char KeyS[]){ 	
	int i=0;
	cout<<"--Ű ��Ʈ��--"<<endl;
	for(i=0;i<FilemsgLength;i++){
		if(KeyS[i] == '\0')
			break;
		printf("%c",KeyS[i]);
	}

	//	Main_Encryption::Keygentimeprint(Main_Encryption::Keygentime); //5st
}

void Main_Encryption::Keygentimeprint(double Keygentime){ // �����Ұ� - Ű���� �Լ��� ���ڰ��� �����ð�.
	cout<<"Ű �����ð� : "<<Keygentime<<endl;
	
	Main_Encryption::OutFilenameSel(); //6st
}

void Main_Encryption::FilenameSel(){
	cout << "�Է��� ���ϸ��� �����ϼ���"<<endl;
	cin>>InFilename;
	
	Main_Encryption::Fileread(Main_Encryption::InFilename); //1st
}

void Main_Encryption::OutFilenameSel(){
	fflush(stdin);
	cout << "����� ���ϸ��� �����ϼ���"<<endl;
	cin>>OutFilename;
	//Main_Encryption::XOROperation(Main_Encryption::Filemsg,Main_Encryption::KeyStream); //7st
}

void Main_Encryption::Fileread(char InFilename[]){ //������:������ ������ �����߻�.
	FILE *fo;
	fo = fopen(InFilename,"r");
	if(fo==NULL){
		char c;
		cout<<"���� ���� ���� ���Է� �Ͻðڽ��ϱ�?(y/else)"<<endl;
		cin>>c;
		if(c=='y'){
			fclose(fo);
			Main_Encryption::FilenameSel();
		}
		else{
			fclose(fo);
			Main_Encryption::Exit();
		}
	}
	while(!feof(fo)){
		fgets(Filemsg,MB,fo); //�������, 1���̻� �Է�.
	}
	fclose(fo);
	FilemsgLength = strlen(Filemsg);
				
	//Main_Encryption::Fileprint(); //2st
}

char* Main_Encryption::Fileprint(){ //�迭���� �޾ƾ���.
	char *fp;
	fp = Filemsg;
	printf("%s,%d\n",fp,FilemsgLength);
	return fp;
	//Main_Encryption::KeyIn(); //3st
}

void Main_Encryption::Filewrite(char OutFilename[]){
	FILE *fp;
	fp = fopen(OutFilename,"wt");
	if(fp==NULL){
		char c;
		cout<<"���� ���� ���� �ٽ� �Է��Ͻðڽ��ϱ�?(y/else)"<<endl;
		cin>>c;
		if(c=='y'){
			Main_Encryption::Outputprint();
			fclose(fp);
		}
		else{
			Main_Encryption::Exit();
			fclose(fp);
		}
	}
	fputs(OutputData,fp); 
	fclose(fp);
	
	//	Main_Encryption::Exit();
}
void Main_Encryption::XOROperation(char *Filemsg,char *KeyStream){ 
	for(int i=0;i<MB;i++)
		OutputData[i]=(Filemsg[i]^KeyStream[i]);
	
	Main_Encryption::Outputprint(); // 8st
}
void Main_Encryption::Outputprint(){
	cout<<"XOR���갪"<<endl;
	for(int i=0;i<FilemsgLength;i++)
		printf("%c",OutputData[i]);
	
	Main_Encryption::Restart(); //9st
}
void Main_Encryption::Restart(){
	char c;
	cout<<"ó������ �ٽ� �����Ͻðڽ��ϱ�? (y/else)"<<endl;
	cin>>c;
	if(c=='y')
		Main_Encryption::ProgramStart();
	
	Main_Encryption::Filewrite(Main_Encryption::OutFilename); //10st
	
}
void Main_Encryption::Exit(){//11st
	cout<<"Program-����"<<endl;
	
}