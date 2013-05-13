#include <stdio.h>
void main(){
	int num[10]={10,20,30,40,50,60,70,80,90,100};
	int *a,*b,temp;
	a = &num[2];
	b = &num[4];
	temp = *a;
	*a = *b;
	*b = temp;
	printf("num[] = %d num[] = %d \n",num[2],num[4]);
}

