#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <string.h>
#define BUF_SIZE 1024
void ErrorHandling(char *message);

int main(int argc, char **argv)
{
	WSADATA	wsaData;
	SOCKET hServSock;		
	SOCKET hClntSock;		
	SOCKADDR_IN servAddr;	
	SOCKADDR_IN clntAddr;
	
	int szClntAddr;
	char dataarray[][4]={"0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F"};
	
	char message[BUF_SIZE];

	int strlen,i,datalong;

	int a,b;

	
	printf("출력\n");
	for(a=0;a<4;a++){
		for(b=0;b<4;b++){
			printf("%c ",dataarray[a][b]);
		}
		printf("\n");
	}
		
		return 0;




	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
  
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) /* Load Winsock 2.2 DLL */
		ErrorHandling("WSAStartup() error!"); 
	
	hServSock=socket(PF_INET, SOCK_STREAM, 0); /* 서버 소켓 생성 */
	if(hServSock==INVALID_SOCKET)
		ErrorHandling("socket() error");
  
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=htons(atoi(argv[1]));
	
	if( bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR ) /* 소켓에 주소 할당 */
		ErrorHandling("bind() error");  
	
	if( listen(hServSock, 5)==SOCKET_ERROR) /* 연결 요청 대기 상태 */
		ErrorHandling("listen() error");

	szClntAddr=sizeof(clntAddr);    	

	for (i=0; i<5; i++)
	{
		hClntSock=accept(hServSock, (SOCKADDR*)&clntAddr,&szClntAddr); /* 연결 요청 수락 */
		if(hClntSock==INVALID_SOCKET)
			ErrorHandling("accept() error");  
		else
			printf("Connected client %d \n",i+1);
		
		while((strlen=recv(hClntSock,message,BUF_SIZE,0))!=0)send(hClntSock,message,strlen,0);

		while((strlen=recv(hClntSock,dataarray[4][4],BUF_SIZE,0))!=0)send(hClntSock,dataarray[4][4],datalong,0);

		
		

		closesocket(hClntSock);		/* 연결 종료 */
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

