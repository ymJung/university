#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define CHATDATA 1024

char escape[] = "Q";
char nickname[20];

main(int argc, char *argv[])
{
	int c_socket;
	struct sockaddr_in c_addr;
	int len;
	char chatData[CHATDATA];
	char buf[CHATDATA];
	int nfds;
	fd_set read_fds;
	int n;
	
	if(argc < 3) {
		printf("usage : %s <IP> <PORT>\n",argv[0]);
		exit(-1);
	}
	
	c_socket = socket(PF_INET,SOCK_STREAM,0);
	
	memset(&c_addr,0,sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(argv[1]);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(atoi(argv[2]));
	
	printf("Input Nickname : ");
	scanf("%s",nickname); 
	//대화명을 입력받아 저장
	
	if(connect(c_socket,(struct sockaddr *)&c_addr,sizeof(c_addr)) == -1){ //채팅참가 요청
		printf("connect error\n");
		return -1;
	}
	
	nfds = c_socket +1;
	
	while(1){
		FD_ZERO(&read_fds);
		FD_SET(0,&read_fds);
		FD_SET(c_socket,&read_fds);
		
		if(select(nfds,&read_fds, (fd_set *)0, (fd_set *)0,(struct timeval *)0)<0){ 
			//키보드로부터 채팅데이터가 입력되었는지 검사하기 위해 read_fds에 1을 설정
			printf("select error\n");
			exit(1);
		}
		
		if(FD_ISSET(c_socket, &read_fds)){ a
			//select함수로 키보드입력이나 서버로부터 채팅데이터가 도착했는지 검사하며 기다림
			memset(chatData,0,sizeof(chatData));
			if((n = read(c_socket, chatData,sizeof(chatData))) >0){  
				//키보드,연결소켓에서 읽기가 가능하면 select함수에서 깨어나 실행
				write(1,chatData,n); 
			}
		}
		
		if(FD_ISSET(0,&read_fds)){
			memset(buf,0,sizeof(buf));
			if((n=read(0,buf,sizeof(buf)))>0){
				sprintf(chatData, "[%s] %s",nickname,buf); //대화명에 채팅데이터를 붙여서 전송
				write(c_socket,chatData,strlen(chatData)); 
				
				if(!strncmp(buf,escape,strlen(escape))){
					break;
				}
			}
		}
	}
	
	close(c_socket);
}





