#include <stdio.h>
#include <stdlib.h>
void main(int argc, char *argv[])
{
	FILE *from, *to;
	char ch;
	
	if(argc!=3){   
		printf("실행파일 원본 복사대상(새파일)\n");
	exit(1);
	}
	
	if((from=fopen(argv[1],"rb"))==NULL){  //원본 파일(복사대상)
		printf("파일을 찾을수 없습니다.\n");
	exit(1);
	}
	
	if((to=fopen(argv[2],"wb"))==NULL){  //복사 대상(새파일)
		printf("파일을 찾을수 없습니다.\n");
	exit(1);
	}
	
	while(!feof(from)){ //파일을 한 텍스트씩 원본에서 복사(반복) 속도느림
		ch=fgetc(from);
	if(ferror(from)){
		printf("읽기에 실패했습니다.\n");
		exit(1);
	}
	
	if(!feof(from))fputc(ch,to);
	if(ferror(to)){
		printf("쓰기에 실패했습니다.\n");
		exit(1);
	}
	}
	fclose(from);
	fclose(to);
}
