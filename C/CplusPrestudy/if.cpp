#include <stdio.h>
#include <conio.h>

void main(){
	int k,e,m,total;
	double avg;
	char grade;

	printf("���������� �Է��ϼ���\n");
	scanf("%d",&k);
	printf("���������� �Է��ϼ���\n");
	scanf("%d",&e);
	printf("���������� �Է��ϼ���\n");
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

	printf("\n���� = %d ���� = %d ���� = %d\n",k,e,m);
	printf("Total = %d\n",total);
	printf("Average = %.2f\n",avg);
	printf("Grade = %c\n",grade);
}
