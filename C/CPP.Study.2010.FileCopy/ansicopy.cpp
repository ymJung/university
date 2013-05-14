#include <stdio.h>
#include <stdlib.h>
void main(int argc, char *argv[])
{
	FILE *from, *to;
	char ch;
	
	if(argc!=3){   
		printf("�������� ���� ������(������)\n");
	exit(1);
	}
	
	if((from=fopen(argv[1],"rb"))==NULL){  //���� ����(������)
		printf("������ ã���� �����ϴ�.\n");
	exit(1);
	}
	
	if((to=fopen(argv[2],"wb"))==NULL){  //���� ���(������)
		printf("������ ã���� �����ϴ�.\n");
	exit(1);
	}
	
	while(!feof(from)){ //������ �� �ؽ�Ʈ�� �������� ����(�ݺ�) �ӵ�����
		ch=fgetc(from);
	if(ferror(from)){
		printf("�б⿡ �����߽��ϴ�.\n");
		exit(1);
	}
	
	if(!feof(from))fputc(ch,to);
	if(ferror(to)){
		printf("���⿡ �����߽��ϴ�.\n");
		exit(1);
	}
	}
	fclose(from);
	fclose(to);
}
