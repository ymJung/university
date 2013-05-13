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
	//��ȭ���� �Է¹޾� ����
	
	if(connect(c_socket,(struct sockaddr *)&c_addr,sizeof(c_addr)) == -1){ //ä������ ��û
		printf("connect error\n");
		return -1;
	}
	
	nfds = c_socket +1;
	
	while(1){
		FD_ZERO(&read_fds);
		FD_SET(0,&read_fds);
		FD_SET(c_socket,&read_fds);
		
		if(select(nfds,&read_fds, (fd_set *)0, (fd_set *)0,(struct timeval *)0)<0){ 
			//Ű����κ��� ä�õ����Ͱ� �ԷµǾ����� �˻��ϱ� ���� read_fds�� 1�� ����
			printf("select error\n");
			exit(1);
		}
		
		if(FD_ISSET(c_socket, &read_fds)){ a
			//select�Լ��� Ű�����Է��̳� �����κ��� ä�õ����Ͱ� �����ߴ��� �˻��ϸ� ��ٸ�
			memset(chatData,0,sizeof(chatData));
			if((n = read(c_socket, chatData,sizeof(chatData))) >0){  
				//Ű����,������Ͽ��� �бⰡ �����ϸ� select�Լ����� ��� ����
				write(1,chatData,n); 
			}
		}
		
		if(FD_ISSET(0,&read_fds)){
			memset(buf,0,sizeof(buf));
			if((n=read(0,buf,sizeof(buf)))>0){
				sprintf(chatData, "[%s] %s",nickname,buf); //��ȭ�� ä�õ����͸� �ٿ��� ����
				write(c_socket,chatData,strlen(chatData)); 
				
				if(!strncmp(buf,escape,strlen(escape))){
					break;
				}
			}
		}
	}
	
	close(c_socket);
}





