#include<iostream.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>

const int BS = 128;
const int MB = 1024;


class Main_Encryption 
{

public:
	char KeyStream[MB];
	char SeedKey[BS];
	char InFilename[BS];
	char OutFilename[BS];
	char Filemsg[MB];
	char OutputData[MB];
	double Keygentime;
	int FilemsgLength;
	 

public:
	void Programstart(){ // --수정할것.
		Main_Encryption::FilenameSel();
		
	}
	
	void KeyIn(){		
		cout << "키를 입력하세요"<<endl;
		cin >> *SeedKey;
		fflush(stdin);
		cout<<SeedKey;
	//	Main_Encryption::Keystreamprint(Main_Encryption::SeedKey); //4st
	}

	char SeedkeySel(){ //KeyGen클래스에 전달할 Seed키
		char Key[BS];
		for(int i=0;i<BS;i++)
			Key[i] = SeedKey[i];
		fflush(stdin);
		return *Key;
	}

	void Keystreamprint(char SeedKey[]){ 
		for(int i=0;i<BS;i++){
		//	if(SeedKey[i]=='\0')
		//		break;
			cout<<hex<<SeedKey[i]<<" ";
		}
		cout<<endl;

	//	Main_Encryption::Keygentimeprint(Main_Encryption::Keygentime); //5st
	}

	void Keygentimeprint(double Keygentime){ // 수정할것 - 키생성 함수의 인자값을 가져올것.
		cout<<"키 생성시간 : "<<Keygentime<<endl;

		Main_Encryption::OutFilenameSel(); //6st
	}

	void FilenameSel(){
		cout << "입력할 파일명을 선택하세요"<<endl;
		cin>>InFilename;

		Main_Encryption::Fileread(Main_Encryption::InFilename); //1st
	}

	void OutFilenameSel(){
		fflush(stdin);
		cout << "출력할 파일명을 선택하세요"<<endl;
		cin>>OutFilename;
		//Main_Encryption::XOROperation(Main_Encryption::Filemsg,Main_Encryption::KeyStream); //7st
	}

	void Fileread(char InFilename[]){
		FILE *fo;
		fo = fopen(InFilename,"r");
		if(fo==NULL){
			char c;
			cout<<"파일 열기 실패 재입력 하시겠습니까?(y/else)"<<endl;
			cin>>c;
			if(c=='y')
				Main_Encryption::FilenameSel();
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

	char Fileprint(){ //배열값을 받아야함.
		printf("%s,%d\n",Filemsg,FilemsgLength);
		return *Filemsg;
		//Main_Encryption::KeyIn(); //3st
	}

	void Filewrite(char OutFilename[]){
		FILE *fp;
		fp = fopen(OutFilename,"wt");
		if(fp==NULL){
			char c;
			cout<<"파일 쓰기 실패 다시 입력하시겠습니까?(y/else)"<<endl;
			cin>>c;
			if(c=='y')
				Main_Encryption::Outputprint();
			else
				Main_Encryption::Exit();
		}
		fputs(OutputData,fp); 
		fclose(fp);
		
	//	Main_Encryption::Exit();
	}
	void XOROperation(char *Filemsg,char *KeyStream){ 
		for(int i=0;i<MB;i++)
			OutputData[i]=(Filemsg[i]^KeyStream[i]);

		Main_Encryption::Outputprint(); // 8st
	}
	void Outputprint(){
		printf("%s\n",OutputData);

		Main_Encryption::Restart(); //9st
	}
	void Restart(){
		char c;
		cout<<"처음부터 다시 시작하시겠습니까? (y/else)"<<endl;
		cin>>c;
		fflush(stdin);
		if(c=='y')
			Main_Encryption::Programstart();

		Main_Encryption::Filewrite(Main_Encryption::OutFilename); //10st

	}
	void Exit(){//11st
		cout<<"Program-종료"<<endl;
		
	}

};



class Key_generator :Main_Encryption
{
public:
	char SeedKey[BS];
	char KeyStream[MB];
	char Fx_Key[MB];
	double Keygentime;
	clock_t start;
	clock_t end;
public:
	void SeedkeyIn(char SeedKeySel){
		*SeedKey=SeedKeySel;
	}
	char KeyStreamGen(char Key[],int FilemsgLength){ //수정요망 키스트림 알고리즘 적용할것.
		char T_SEED;
		char T_KS[MB]; //KS -> Seed Key Stream
		char T_KeyStream[MB];
		char T_SeedKey[BS];
		int p_Count=0;
		int KeyLength=strlen(Key);
		for(int kcopy=0;kcopy<KeyLength;kcopy++){
			T_SeedKey[kcopy] = Key[kcopy];			
		}
		for(int k=0;k<KeyLength;k++){ //시드값 입력
			T_SEED +=Key[k];
		}
		T_KS[0] = T_SEED; //시드값은 0에
		for(int Keyround=1;Keyround<MB;Keyround++){ //키를 반복해서 붙여넣음 1024공간에 키 반복
			T_KS[Keyround]=Key[(Keyround%KeyLength)];
		}
		for(int Padding=KeyLength+1;Padding<MB;Padding++){ //키를 제외한 남는부분을 패딩으로 채워넣음
			T_KS[Padding]=T_KS[Padding-1] << (T_KS[p_Count]%8);
		}		
		for(int fxkey=0;fxkey<MB;fxkey++){ //키를 반복해서 붙여넣음
			Fx_Key[fxkey]=(T_KS[fxkey]*T_KS[fxkey+1]);
		}
		for(int kr=0;kr<FilemsgLength;kr++){ // 파일 메시지 길이만큼만 붙여넣음 
			T_KeyStream[kr]=Fx_Key[kr];
		}
		for(int c=0;c<FilemsgLength;c++){ //리턴시킬 값에 붙여넣음 
			KeyStream[c] = T_KeyStream[c];
		}
		
		return *KeyStream;
	}
	void KeygentimeStart(clock_t ){
		start = clock();
//		return start;
	}
	void KeygentimeEnd(clock_t ){
		end = clock();
//		return end;
	}
	double Key_gentime(clock_t start,clock_t end){
		Keygentime=(double)(end-start);
		return Keygentime;
	}
};