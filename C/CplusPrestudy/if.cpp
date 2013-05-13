#include <stdio.h>
#include <conio.h>

void main(){
	int k,e,m,total;
	double avg;
	char grade;

	printf("국어점수를 입력하세요\n");
	scanf("%d",&k);
	printf("영어점수를 입력하세요\n");
	scanf("%d",&e);
	printf("수학점수를 입력하세요\n");
	scanf("%d",&m);
	total = k + e + m;
	avg = (double)total/3.0;

	if (avg >= 90)
		grade = 'A';
	else if (avg >= 80)
		grade = 'B';
	else if (avg >= 60)
		grade = 'C';
	else 
		grade = 'F';

	printf("\n국어 = %d 영어 = %d 수학 = %d\n",k,e,m);
	printf("Total = %d\n",total);
	printf("Average = %.2f\n",avg);
	printf("Grade = %c\n",grade);
}
