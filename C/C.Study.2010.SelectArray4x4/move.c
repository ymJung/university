#include <stdio.h>

int main()
{
	

	
	char array[4][4]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char n;
	int q,w=0;
	int a= 0,s=0;
	
	
	for(q=0;q<4;q++){
		for(w=0;w<3;w++){
			printf("%c  ",array[q][w]);
		}
		printf("%c\n",array[q][w]);
		printf("\n");
	}
	printf("왼쪽 상단부터 좌표시작 숫자패드로 이동\n");
	printf("숫자패드를 보고 8462만 입력하세요\n");
	while((n=getchar()) != '\n')
	{
		switch(n)
		{
		case '8': 
			a--;
			break;
		case '2': 
			a++;
			break;
		case '4': 
			s--;
			break;
		case '6': 
			s++;
			break;
		default : 
			printf("잘못된 값을 넣었음\n");
			
			break;
			
		}
	}
	printf("%c ",array[a][s]);
	
	return 0;
	
}

