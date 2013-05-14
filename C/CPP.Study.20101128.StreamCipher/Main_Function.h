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
	char Filemsgpass(){
		return *Filemsg;
	}
	
	void Programstart(){
		Main_Encryption::FilenameSel();
		
	}
	
	void KeyIn(){
		cout << "키를 입력하세요"<<endl;
		cin >> SeedKey;

		
		Main_Encryption::Keystreamprint(Main_Encryption::SeedKey); //4st
	}

	char SeedkeySel(char SeedKey[]){ //KeyGen클래스에 전달할 Seed키
		return SeedKey[BS];
	}

	void Keystreamprint(char SeedKey[]){ //수정할것.-Seed -> 생성된 KeyStream으로
		for(int i=0;i<BS;i++){
			if(SeedKey[i]=='\0')
				break;
			cout<<SeedKey[i]<<" ";
		}
		cout<<endl;

		Main_Encryption::Keygentimeprint(Main_Encryption::Keygentime); //5st
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
		cout << "출력할 파일명을 선택하세요"<<endl;
		cin>>OutFilename;
		Main_Encryption::XOROperation(Main_Encryption::Filemsg,Main_Encryption::KeyStream); //7st
	}

	void Fileread(char InFilename[]){
		FILE *fo;
		int a=0;
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

		Main_Encryption::Fileprint(); //2st
	}

	int FileLength(char *Filemsg){
		int FileLength=0;
		for(int i=0;i<MB;i++){
			if(Filemsg[i]=='\0')
				break;
			FileLength++;
		}
		return FileLength;
	}

	void Fileprint(){
		printf("%s,%d\n",Filemsg,FilemsgLength);

		
		Main_Encryption::KeyIn(); //3st
	}

	void Filewrite(char OutFilename[]){
		FILE *fp;
		fp = fopen(OutFilename,"wt");
		if(fp==NULL){
			char c;
			cout<<"파일 쓰기 실패 재시작 하시겠습니까?"<<endl;
			cin>>c;
			if(c=='y')
				Main_Encryption::Programstart();
			else
				Main_Encryption::Exit();
		}
		fputs(OutputData,fp); 
		fclose(fp);
		
		Main_Encryption::Exit();
	}
	void XOROperation(char *Filemsg,char *KeyStream){ 
		for(int i=0;i<MB;i++)
			OutputData[i]=(Filemsg[i]^KeyStream[i]);

		Main_Encryption::Outputprint(); // 9st
	}
	void Outputprint(){
		printf("%s\n",OutputData);

		Main_Encryption::Restart(); //10st
	}
	void Restart(){
		char c;
		cout<<"재시작하시겠습니까 (y/else)?"<<endl;
		cin>>c;
		if(c=='y')
			Main_Encryption::Programstart();

		Main_Encryption::Filewrite(Main_Encryption::OutFilename); //11st

	}
	void Exit(){
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
		int KeyLength=0,p_Count=0;
		for(int kcopy=0;kcopy<sizeof(Key);kcopy++){
			T_SeedKey[kcopy] = Key[kcopy];
			KeyLength++;
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
		for(int c=0;c<MB;c++) //리턴시킬 값에 붙여넣음 
			KeyStream[c] = T_KeyStream[c];		
		return *KeyStream;
	}
	clock_t KeygentimeStart(clock_t ){
		start = clock();
		return start;
	}
	clock_t KeygentimeEnd(clock_t ){
		end = clock();
		return end;
	}
	double Key_gentime(clock_t start,clock_t end){
		Keygentime=(double)(end-start);
		return Keygentime;
	}
};