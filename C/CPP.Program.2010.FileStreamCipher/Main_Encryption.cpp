#include "Main_Encryption.h"

void Main_Encryption::ProgramStart(){ // --수정할것.
//	Main_Encryption::FilenameSel();
	
}

void Main_Encryption::KeyIn(){		
	cout << "키를 입력하세요"<<endl;
	cin >> SeedKey;				
	//	Main_Encryption::Keystreamprint(Main_Encryption::SeedKey); //4st
}

char* Main_Encryption::SeedkeySel(){ //KeyGen클래스에 전달할 Seed키
	char *Key;
	Key = SeedKey;
	return Key;
}

void Main_Encryption::Keystreamprint(char KeyS[]){ 	
	int i=0;
	cout<<"--키 스트림--"<<endl;
	for(i=0;i<FilemsgLength;i++){
		if(KeyS[i] == '\0')
			break;
		printf("%c",KeyS[i]);
	}

	//	Main_Encryption::Keygentimeprint(Main_Encryption::Keygentime); //5st
}

void Main_Encryption::Keygentimeprint(double Keygentime){ // 수정할것 - 키생성 함수의 인자값을 가져올것.
	cout<<"키 생성시간 : "<<Keygentime<<endl;
	
	Main_Encryption::OutFilenameSel(); //6st
}

void Main_Encryption::FilenameSel(){
	cout << "입력할 파일명을 선택하세요"<<endl;
	cin>>InFilename;
	
	Main_Encryption::Fileread(Main_Encryption::InFilename); //1st
}

void Main_Encryption::OutFilenameSel(){
	fflush(stdin);
	cout << "출력할 파일명을 선택하세요"<<endl;
	cin>>OutFilename;
	//Main_Encryption::XOROperation(Main_Encryption::Filemsg,Main_Encryption::KeyStream); //7st
}

void Main_Encryption::Fileread(char InFilename[]){ //문제점:파일이 없을시 오류발생.
	FILE *fo;
	fo = fopen(InFilename,"r");
	if(fo==NULL){
		char c;
		cout<<"파일 열기 실패 재입력 하시겠습니까?(y/else)"<<endl;
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
		fgets(Filemsg,MB,fo); //수정요망, 1줄이상 입력.
	}
	fclose(fo);
	FilemsgLength = strlen(Filemsg);
				
	//Main_Encryption::Fileprint(); //2st
}

char* Main_Encryption::Fileprint(){ //배열값을 받아야함.
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
		cout<<"파일 쓰기 실패 다시 입력하시겠습니까?(y/else)"<<endl;
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
	cout<<"XOR연산값"<<endl;
	for(int i=0;i<FilemsgLength;i++)
		printf("%c",OutputData[i]);
	
	Main_Encryption::Restart(); //9st
}
void Main_Encryption::Restart(){
	char c;
	cout<<"처음부터 다시 시작하시겠습니까? (y/else)"<<endl;
	cin>>c;
	if(c=='y')
		Main_Encryption::ProgramStart();
	
	Main_Encryption::Filewrite(Main_Encryption::OutFilename); //10st
	
}
void Main_Encryption::Exit(){//11st
	cout<<"Program-종료"<<endl;
	
}