#include <stdio.h>
#include <conio.h>

int Evaluation(int *a);

void main(){
	char *singer[4]= {"Ƽ�ƶ�","��ư�","�ҳ�ô�","��ũ��?"};
	char *title[4]= {"�ǻ߻ǻ�","�ƺζ�ī�ζ�","����¢~","���뷡��"};

	int eval[4];

	for(int k=0; k< 4; k++){
		int tmp;
		printf("���� [%s] �� �����Է� :",singer[k]);
		scanf("%d",&tmp);
		eval[k]=Evaluation(&tmp);
	}

	printf("\n**�Էµ� ������ ������ ������ 10�� �ο� ���� \n");

	for(int j = 0; j< 4 ;j++){
		printf("**���� [%s] : �뷡 [%s] : ���� [%d] \n",singer[j],title[j],eval[j]);
	}
}
int Evaluation(int *a) {
	*a = *a + 10;
	if (*a > 100){
		*a = 100;
	}
	return(*a);
}

