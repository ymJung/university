#include <stdio.h>
#include <conio.h>

int Evaluation(int *a);

void main(){
	char *singer[4]= {"티아라","브아걸","소녀시대","시크릿?"};
	char *title[4]= {"뽀삐뽀삐","아부라카부라","지지짖~","뭔노래지"};

	int eval[4];

	for(int k=0; k< 4; k++){
		int tmp;
		printf("가수 [%s] 의 점수입력 :",singer[k]);
		scanf("%d",&tmp);
		eval[k]=Evaluation(&tmp);
	}

	printf("\n**입력된 가수의 점수에 가산점 10점 부여 총점 \n");

	for(int j = 0; j< 4 ;j++){
		printf("**가수 [%s] : 노래 [%s] : 총점 [%d] \n",singer[j],title[j],eval[j]);
	}
}
int Evaluation(int *a) {
	*a = *a + 10;
	if (*a > 100){
		*a = 100;
	}
	return(*a);
}

