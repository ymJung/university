#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX 45 //로또 숫자의 갯수
#define CHOICE 6 //선택할 숫자 갯수

void compare(int *a,int *b); // 선택한 수와 당첨번호 비교
void generate(int *g); //당첨번호 생성
void sorting(int *a); //당첨번호 내림차순으로 정렬
void print(); //맞춘 숫자 갯수 출력

int main()
{
 int seed; //rand을 사용하기 위한 시간 int
 char sel; //시작 여부 확인 char
 
 //time()을 srand에 넣어 rand() 시 랜덤한 수가 나오도록 셋팅
 seed=time(NULL);
 srand(seed);

 printf("     *****************************************************\n");
printf(" * 로또 번호 맞히기 게임 *\n");
 printf("     *****************************************************\n");
printf(" * * * * * * * \n");
printf(" * * * ***** ***** * * \n");
printf(" * * * * * * * \n");
printf(" ***** * * **** **** * * .\n");


while(1)
{
 printf("     =====================================================\n");
 printf("\n     로또 번호 맞히기 게임을 하시겠습니까(y/n):");
 sel = getche(); //게임을 할것인가 입력받기

 printf("\n");

switch(sel)
{
case 'n': //입력 받은 문자가 n 이면
 printf("     프로그램을 종료합니다\n");
 exit(0);
 break;

case 'y': //입력 받은 문자가 y 이면
 print();
 break;

default: //입력 받은 문자가 x도 아니고 y도 아니면
 printf("     잘못입력하셨습니다\n");
}
}

 system("PAUSE"); //?이건 왜 들어있는지 모르겠네요..
 return 0;
}

void print()
{
 int usr[CHOICE],i,com[CHOICE];

 printf("\n     로또 번호를 입력하세요(숫자6개)\n");

 for(i=0;i<CHOICE;i++) //유저에게 6개의 숫자 입력받기
     scanf("%d",&usr[i]);

 printf("     입력하신 로또 번호 : ");

 for(i=0;i<CHOICE;i++) //유저가 입력한 숫자 출력하기
   printf("[%d]",usr[i]);

 printf("\n\n");
 generate(com); //컴퓨터가 6개의 숫자 입력하기
 sorting(com); //컴퓨터가 입력한 숫자 정렬하기
 compare(com,usr); //유저가 입력한 숫자와 컴퓨터가 입력한 숫자 비교하기
}

//컴퓨터가 6개의 랜덤수 생성
void generate(int *g)
{
 int i,j;

 for(i=0;i<CHOICE;i++) //6개의 숫자 랜덤으로 생성
  g[i]=rand()%MAX+1;

 
//중복수가 나오면 다시 입력받기
 for(i=0;i<CHOICE;i++)
    for(j=i+1;j<CHOICE;j++)
       if(g[i]==g[j])
         g[i]=rand()%MAX+1;

}

//컴퓨터가 생성한 랜덤수를 내림차순으로 정렬
void sorting(int *a)
{
 int i,j,temp;

 //만약 앞수가 뒷수보다 크면 앞수를 뒷수와 바꿔 정렬
 for(i=0;i<CHOICE;i++)
  for(j=i+1;j<CHOICE;j++)
   if(a[j]<a[i])
   {
    temp=a[i];
    a[i]=a[j];
    a[j]=temp;
   }

 

 printf("\n     추첨된 로또 번호 : ");

 for(i=0;i<CHOICE;i++) //컴퓨터가 뽑은 6개의 수 출력하기
  printf("[%d]",a[i]);

}

void compare(int *a,int *b)
{
 int count,i,j;
 count=0; //맞힌 숫자의 갯수

 //만약 컴퓨터가 뽑은 수와 유저가 넣은 수가 같으면 count를 1 증가
 for(i=0;i<CHOICE;i++)
    for(j=0;j<CHOICE;j++)
       if(a[i]==b[j])
          count++;
 printf("\n     ------------------------------------------\n");
 printf("\n     당신은 %d개의 숫자를 맞추셨습니다!\n",count);

}

