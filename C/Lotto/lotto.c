#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX 45 //�ζ� ������ ����
#define CHOICE 6 //������ ���� ����

void compare(int *a,int *b); // ������ ���� ��÷��ȣ ��
void generate(int *g); //��÷��ȣ ����
void sorting(int *a); //��÷��ȣ ������������ ����
void print(); //���� ���� ���� ���

int main()
{
 int seed; //rand�� ����ϱ� ���� �ð� int
 char sel; //���� ���� Ȯ�� char
 
 //time()�� srand�� �־� rand() �� ������ ���� �������� ����
 seed=time(NULL);
 srand(seed);

 printf("     *****************************************************\n");
printf(" * �ζ� ��ȣ ������ ���� *\n");
 printf("     *****************************************************\n");
printf(" * * * * * * * \n");
printf(" * * * ***** ***** * * \n");
printf(" * * * * * * * \n");
printf(" ***** * * **** **** * * .\n");


while(1)
{
 printf("     =====================================================\n");
 printf("\n     �ζ� ��ȣ ������ ������ �Ͻðڽ��ϱ�(y/n):");
 sel = getche(); //������ �Ұ��ΰ� �Է¹ޱ�

 printf("\n");

switch(sel)
{
case 'n': //�Է� ���� ���ڰ� n �̸�
 printf("     ���α׷��� �����մϴ�\n");
 exit(0);
 break;

case 'y': //�Է� ���� ���ڰ� y �̸�
 print();
 break;

default: //�Է� ���� ���ڰ� x�� �ƴϰ� y�� �ƴϸ�
 printf("     �߸��Է��ϼ̽��ϴ�\n");
}
}

 system("PAUSE"); //?�̰� �� ����ִ��� �𸣰ڳ׿�..
 return 0;
}

void print()
{
 int usr[CHOICE],i,com[CHOICE];

 printf("\n     �ζ� ��ȣ�� �Է��ϼ���(����6��)\n");

 for(i=0;i<CHOICE;i++) //�������� 6���� ���� �Է¹ޱ�
     scanf("%d",&usr[i]);

 printf("     �Է��Ͻ� �ζ� ��ȣ : ");

 for(i=0;i<CHOICE;i++) //������ �Է��� ���� ����ϱ�
   printf("[%d]",usr[i]);

 printf("\n\n");
 generate(com); //��ǻ�Ͱ� 6���� ���� �Է��ϱ�
 sorting(com); //��ǻ�Ͱ� �Է��� ���� �����ϱ�
 compare(com,usr); //������ �Է��� ���ڿ� ��ǻ�Ͱ� �Է��� ���� ���ϱ�
}

//��ǻ�Ͱ� 6���� ������ ����
void generate(int *g)
{
 int i,j;

 for(i=0;i<CHOICE;i++) //6���� ���� �������� ����
  g[i]=rand()%MAX+1;

 
//�ߺ����� ������ �ٽ� �Է¹ޱ�
 for(i=0;i<CHOICE;i++)
    for(j=i+1;j<CHOICE;j++)
       if(g[i]==g[j])
         g[i]=rand()%MAX+1;

}

//��ǻ�Ͱ� ������ �������� ������������ ����
void sorting(int *a)
{
 int i,j,temp;

 //���� �ռ��� �޼����� ũ�� �ռ��� �޼��� �ٲ� ����
 for(i=0;i<CHOICE;i++)
  for(j=i+1;j<CHOICE;j++)
   if(a[j]<a[i])
   {
    temp=a[i];
    a[i]=a[j];
    a[j]=temp;
   }

 

 printf("\n     ��÷�� �ζ� ��ȣ : ");

 for(i=0;i<CHOICE;i++) //��ǻ�Ͱ� ���� 6���� �� ����ϱ�
  printf("[%d]",a[i]);

}

void compare(int *a,int *b)
{
 int count,i,j;
 count=0; //���� ������ ����

 //���� ��ǻ�Ͱ� ���� ���� ������ ���� ���� ������ count�� 1 ����
 for(i=0;i<CHOICE;i++)
    for(j=0;j<CHOICE;j++)
       if(a[i]==b[j])
          count++;
 printf("\n     ------------------------------------------\n");
 printf("\n     ����� %d���� ���ڸ� ���߼̽��ϴ�!\n",count);

}

