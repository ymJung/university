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
	void Programstart(){ // --�����Ұ�.
		Main_Encryption::FilenameSel();
		
	}
	
	void KeyIn(){		
		cout << "Ű�� �Է��ϼ���"<<endl;
		cin >> *SeedKey;
		fflush(stdin);
		cout<<SeedKey;
	//	Main_Encryption::Keystreamprint(Main_Encryption::SeedKey); //4st
	}

	char SeedkeySel(){ //KeyGenŬ������ ������ SeedŰ
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

	void Keygentimeprint(double Keygentime){ // �����Ұ� - Ű���� �Լ��� ���ڰ��� �����ð�.
		cout<<"Ű �����ð� : "<<Keygentime<<endl;

		Main_Encryption::OutFilenameSel(); //6st
	}

	void FilenameSel(){
		cout << "�Է��� ���ϸ��� �����ϼ���"<<endl;
		cin>>InFilename;

		Main_Encryption::Fileread(Main_Encryption::InFilename); //1st
	}

	void OutFilenameSel(){
		fflush(stdin);
		cout << "����� ���ϸ��� �����ϼ���"<<endl;
		cin>>OutFilename;
		//Main_Encryption::XOROperation(Main_Encryption::Filemsg,Main_Encryption::KeyStream); //7st
	}

	void Fileread(char InFilename[]){
		FILE *fo;
		fo = fopen(InFilename,"r");
		if(fo==NULL){
			char c;
			cout<<"���� ���� ���� ���Է� �Ͻðڽ��ϱ�?(y/else)"<<endl;
			cin>>c;
			if(c=='y')
				Main_Encryption::FilenameSel();
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

	char Fileprint(){ //�迭���� �޾ƾ���.
		printf("%s,%d\n",Filemsg,FilemsgLength);
		return *Filemsg;
		//Main_Encryption::KeyIn(); //3st
	}

	void Filewrite(char OutFilename[]){
		FILE *fp;
		fp = fopen(OutFilename,"wt");
		if(fp==NULL){
			char c;
			cout<<"���� ���� ���� �ٽ� �Է��Ͻðڽ��ϱ�?(y/else)"<<endl;
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
		cout<<"ó������ �ٽ� �����Ͻðڽ��ϱ�? (y/else)"<<endl;
		cin>>c;
		fflush(stdin);
		if(c=='y')
			Main_Encryption::Programstart();

		Main_Encryption::Filewrite(Main_Encryption::OutFilename); //10st

	}
	void Exit(){//11st
		cout<<"Program-����"<<endl;
		
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
	char KeyStreamGen(char Key[],int FilemsgLength){ //������� Ű��Ʈ�� �˰��� �����Ұ�.
		char T_SEED;
		char T_KS[MB]; //KS -> Seed Key Stream
		char T_KeyStream[MB];
		char T_SeedKey[BS];
		int p_Count=0;
		int KeyLength=strlen(Key);
		for(int kcopy=0;kcopy<KeyLength;kcopy++){
			T_SeedKey[kcopy] = Key[kcopy];			
		}
		for(int k=0;k<KeyLength;k++){ //�õ尪 �Է�
			T_SEED +=Key[k];
		}
		T_KS[0] = T_SEED; //�õ尪�� 0��
		for(int Keyround=1;Keyround<MB;Keyround++){ //Ű�� �ݺ��ؼ� �ٿ����� 1024������ Ű �ݺ�
			T_KS[Keyround]=Key[(Keyround%KeyLength)];
		}
		for(int Padding=KeyLength+1;Padding<MB;Padding++){ //Ű�� ������ ���ºκ��� �е����� ä������
			T_KS[Padding]=T_KS[Padding-1] << (T_KS[p_Count]%8);
		}		
		for(int fxkey=0;fxkey<MB;fxkey++){ //Ű�� �ݺ��ؼ� �ٿ�����
			Fx_Key[fxkey]=(T_KS[fxkey]*T_KS[fxkey+1]);
		}
		for(int kr=0;kr<FilemsgLength;kr++){ // ���� �޽��� ���̸�ŭ�� �ٿ����� 
			T_KeyStream[kr]=Fx_Key[kr];
		}
		for(int c=0;c<FilemsgLength;c++){ //���Ͻ�ų ���� �ٿ����� 
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