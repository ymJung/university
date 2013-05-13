#include<stdio.h>

struct student
{
	int num;
	char name[10];
	int kor, eng, mat, total;
	char kor_hak, eng_hak, mat_hak;
	float ave;
};

typedef struct student STUDENT;

char student_grade(int a);
int student_total(int k, int e, int m);
float student_ave(int a);
void student_sharts(STUDENT *a, int n, FILE *cp);
	
int main(void)
{
	STUDENT a[50];

	int i=0, d;
	char c[10];
	int ret;

	FILE * fp;
	FILE * cp;

	fp = fopen("c:\\input.txt","rt");
	cp = fopen("c:\\output.txt","wt");

	if(fp==NULL||cp==NULL)
	{
		puts("���� ���� ����!");
		return -1;
	}


	fscanf(fp,"%d %s", &d, &c);
	
	while(1)
	{
		ret = fscanf(fp,"%d %s %d %d %d", &a[i].num, &a[i].name, &a[i].kor, &a[i].eng, &a[i].mat);
		i++;
		if(ret==EOF)
			break;
	}

	

	fprintf(cp, "\t\t\t �� �� ǥ\n");
	fprintf(cp, "\t\t\t ---------\n");
	fprintf(cp, "\t\t\t\t\t\t\t\t     ���ο�: %d��\n", d);
	fprintf(cp, "-------------------------------------------------------------------------------------------\n");
	fprintf(cp, "�й�\t �̸�  ���� ��������  ����  ��������  ���� ��������     ����   ���\t����\n");
	fprintf(cp, "-------------------------------------------------------------------------------------------\n");

	for(i=0; i<50; i++)
	{
		a[i].kor_hak = student_grade(a[i].kor);
		a[i].eng_hak = student_grade(a[i].eng);
		a[i].mat_hak = student_grade(a[i].mat);

		a[i].total = student_total(a[i].kor, a[i].eng, a[i].mat);
		
	}

	student_sharts(a, 50, cp);

	fclose(fp);
	fclose(cp);
	return 0;
}

char student_grade(int a)
{
	char h;

	if(a >= 90) h = 'A';
	else if(a >= 80) h = 'B';
	else if(a >= 70) h = 'C';
	else if(a >= 60) h = 'D';
	else h = 'f';

	return h;

}

int student_total(int k, int e, int m)
{
	return k + e + m;
}

float student_ave(int a)
{
	return (float)a / 3;
}


void student_sharts(STUDENT *a, int n, FILE *cp)
{
	int i, j, c;

	STUDENT s;

	
	for(i=0;i<n;i++)
	{
		for(j=1+i;j<n;j++)
		{
			if(a[i].total < a[j].total) //?? -_-//a��Ʈ������ total���� ���Ѵ�. ���� total���� �պ��� Ŭ�� 
			{
				s = a[i]; //���� a�� s(�ӽ�)�� �ִ´�.
				a[i] = a[j]; //���� a�� ���� a�� �ִ´�.
				a[j] = s; //�����س��� ���� a�� ���� a�� �ִ´�.
								
			}
		}	
	}
	
	for(i=0; i<50; i++)
	{
		a[i].ave = student_ave(a[i].total);
		
		c = i + 1;
		
		fprintf(cp, " %d\t%s\t%d\t%c\t%d\t%c\t%d\t%c",
			a[i].num, a[i].name, a[i].kor, a[i].kor_hak, 
			a[i].eng, a[i].eng_hak, a[i].mat, a[i].mat_hak);

		fprintf(cp, "\t %d\t%f  %d\n", a[i].total, a[i].ave, c);
	}
	
}