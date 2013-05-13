#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#define ALPHA 26

#define BUFSIZE 1024
void ErrorHandling(char *message);
void createCharter(char ch[]);

int main(int argc, char **argv)
{
  WSADATA wsaData;
  SOCKET hServSock;
  SOCKET hClntSock;
  char message[BUFSIZE];
  int strLen;
  char ch[ALPHA];
  FILE *fp;

  SOCKADDR_IN servAddr;
  SOCKADDR_IN clntAddr;
  int clntAddrSize;

  if(argc!=2){
    printf("Usage : %s <port>\n", argv[0]);
    exit(1);
  }

  if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) /* Load Winsock 2.2 DLL */
		ErrorHandling("WSAStartup() error!"); 

  hServSock=socket(PF_INET, SOCK_STREAM, 0);   
  if(hServSock == INVALID_SOCKET)
    ErrorHandling("socket() error");
  
 
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family=AF_INET;
  servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servAddr.sin_port=htons(atoi(argv[1]));

  

  if(bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
    ErrorHandling("bind() error");

  if(listen(hServSock, 5)==SOCKET_ERROR)
	  ErrorHandling("listen() error");
  
  clntAddrSize=sizeof(clntAddr);    
  hClntSock=accept(hServSock, (SOCKADDR*)&clntAddr,&clntAddrSize);

  printf("%d에게 26(A~Z)개 랜덤한 문자열 전송\n",hClntSock);
  createCharter(ch);
  fp = fopen("test.txt","a+"); //파일이름 수정 요함.
  fwrite(ch,sizeof(char),ALPHA,fp);
  fseek(fp,0L,SEEK_SET); 
  fread(ch,sizeof(char),ALPHA,fp); 
  message[BUFSIZE] = ch; //만들어진 배열을 저장.. 하려고 했으나?

  send(hClntSock,message,strLen,0);
  if(hClntSock==INVALID_SOCKET)
	  ErrorHandling("accept() error");
  
  
  //차후 수정 배열을 전송.
  
  while((strLen=recv(hClntSock, message, BUFSIZE, 0)) != 0){ /* 데이터 수신 및 전송 */
	  send(hClntSock, message, strLen, 0);
	  
	  
	  
	  	  
  }
  fclose(fp);
  closesocket(hClntSock);
  WSACleanup();
  return 0;
}



void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


void createCharter(char ch[])
{
	int i,j;
	int seed;
	seed=time(NULL);
	srand(seed);
	
	for(i=0; i<ALPHA; i++){
		do{
			ch[i]=rand()%26+65; // 90 - 65 + 1
			for(j=0;j<i;j++)
				if(ch[i]==ch[j])
					break;
		} while(i!=j);
	}
	
	for(i=0;i<ALPHA;i++)
		printf("%c ",ch[i]);			
	printf("\n");
	
	
	
}

