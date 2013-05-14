#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CHOICE 10
#define MAX 10
#define ALPHA 26


void generate(int *g);
void createCharter(char ch[]); // 랜덤한 문자를 만드는 함수


int main(void)
{
	FILE *fp;
	int g[CHOICE];
	char file[64];
	char ch[ALPHA+1]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'\n'};
	printf("----26(A~Z)개 랜덤한 문자열 출력\n");
	createCharter(ch);
	printf("----10개 랜덤한 수 출력\n");
	generate(g);
	
	printf("파일ID 입력 :");
	scanf("%s",file);
	fp = fopen(file,"a+");
	fwrite(ch,sizeof(char),ALPHA,fp);
	fseek(fp,0L,SEEK_SET); 
	fread(ch,sizeof(int),ALPHA,fp); 
	fclose(fp);
		
	return 0;
}



void generate(int *g)
{
	int i,j;	
	int seed;
	seed=time(NULL);
	srand(seed); 
	
	for(i=0;i<CHOICE;i++){
		do {
			g[i]=rand()%MAX+1;
			for(j=0;j<i;j++)
				if(g[i]==g[j])
					break;
		} while(i!=j);	
	}
	
	
	for(i=0;i<CHOICE;i++)
		printf("%d ",g[i]-1);			
	printf("\n");
}

void createCharter(char ch[])
{
	int i,j;
	
	int seed;
	seed=time(NULL);
	srand(seed);
	
	for(i=0; i<ALPHA; i++){
		do{
			ch[i]=rand()%26+65; // 90 - 65 + 1
			for(j=0;j<i;j++)
				if(ch[i]==ch[j])
					break;
		} while(i!=j);
	}
	for(i=0;i<ALPHA;i++)
		printf("%c ",ch[i]);			


	printf("\n");
}

