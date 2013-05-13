#include "Key_generator.h"

void Key_generator::SeedkeyIn(char SeedKeySel){
	*SeedKey=SeedKeySel;
}

char Key_generator::ROTR(char mat,int num){
	char rotr;
	rotr = (mat>>num) | (mat<< (8-num));
	return rotr;
}


char *Key_generator::KeyStreamGen(char Key[],int FilemsgLength){ 
	int i,KeyLen;
	char *R_KeyStream,KSKey[MB],SeedKey,SKStream[MB];
	R_KeyStream = Key;
	KeyLen = strlen(Key);
	strcpy(KSKey,Key);
	for(i=0;i<KeyLen;i++)
		SeedKey = KSKey[i]+KSKey[i+1];	
	for(i=KeyLen;i<FilemsgLength;i++)
	{
		KSKey[i] = Key[i%KeyLen];
	}
	SKStream[0] = ROTR(KSKey[0],KSKey[0]%8);
	for(i=1;i<MB;i++)
	{
		SKStream[i]=ROTR(KSKey[i],(KSKey[i-1]+KSKey[i])%8); // 알고리즘 다시 살펴볼것.
	}



	return R_KeyStream;
}
clock_t Key_generator::KeygentimeStart(clock_t ){
	start = clock();
	return start;
}
clock_t Key_generator::KeygentimeEnd(clock_t ){
	end = clock();
	return end;
}
double Key_generator::Key_gentime(clock_t start,clock_t end){
	Keygentime=(double)(end-start);
	return Keygentime;
}
