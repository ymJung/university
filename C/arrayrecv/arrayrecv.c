/*
* echo_client_win.c
* Written by SW. YOON
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUFSIZE 1024
void ErrorHandling(char *message);
void numberarray(char numarray);


int main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET hSocket;
	char message[BUFSIZE];
	int strLen;
	
	SOCKADDR_IN servAddr;


	char array[4][4]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char n,m;
	int q,w=0;
	int a= 0,s=0;
	
	
	
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) /* Load Winsock 2.2 DLL */
		ErrorHandling("WSAStartup() error!"); 
	
	hSocket=socket(PF_INET, SOCK_STREAM, 0);   
	if(hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=inet_addr(argv[1]);
	servAddr.sin_port=htons(atoi(argv[2]));
	
	if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandling("connect() error!");
	
	//접속이 성공하면 함수 시작.
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
	printf("입력한값은 %c 입니다.\n",array[a][s]);
	m = array[a][s];
	return 0;

	
	
	
	while(1) {
		fputs("전송하시겠습니까? [y/n]: ", stdout);
		fgets(message, BUFSIZE, stdin); /* 전송 할 데이터 콘솔로부터 입력 */
		
		if(!strcmp(message,"y\n")) 
			break;//차후 전송후 종료로 수정
		else if(!strcmp(message,"n\n"))
			//함수 출력 

		send(hSocket, message, strlen(message), 0); /* 메시지 전송 */
		
		strLen=recv(hSocket, message, BUFSIZE-1, 0);
		
		/* 메시지 수신 */
		message[strLen]=0;
		printf("서버로부터 전송된 메시지 : %s \n", message);
		
	}
	
	closesocket(hSocket);
	WSACleanup();
	return 0;
}


void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


