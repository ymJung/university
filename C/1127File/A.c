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
		puts("파일 오픈 실패!");
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

	

	fprintf(cp, "\t\t\t 성 적 표\n");
	fprintf(cp, "\t\t\t ---------\n");
	fprintf(cp, "\t\t\t\t\t\t\t\t     총인원: %d명\n", d);
	fprintf(cp, "-------------------------------------------------------------------------------------------\n");
	fprintf(cp, "학번\t 이름  국어 국어학점  영어  영어학점  수학 수학학점     총점   평균\t석차\n");
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
			if(a[i].total < a[j].total) //?? -_-//a스트럭쳐의 total값을 비교한다. 뒤의 total값이 앞보다 클때 
			{
				s = a[i]; //앞쪽 a를 s(임시)에 넣는다.
				a[i] = a[j]; //뒤쪽 a를 앞쪽 a로 넣는다.
				a[j] = s; //보관해놓은 앞쪽 a를 뒤쪽 a에 넣는다.
								
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