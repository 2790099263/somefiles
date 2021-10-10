#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
using namespace std;
#define MYPORT  8010
#define QUEUE   20
#define BUFFER_SIZE 1024
#define MAX_LENGTH 1024
//parsing our message
//Parse the incoming code
inline int out_message(char *rev_msg)
{
    char li_msg[MAX_LENGTH];
    int tot=0;
    int len=strlen(rev_msg);
    int re_num=0;
    for(int i=0;i<=4;i++)
        re_num=re_num*10+(rev_msg[i]-'0');
    for(int i=5;i<len;i++)
        li_msg[tot++]=rev_msg[i];
    memset(rev_msg,0,sizeof(rev_msg));
    strcpy(rev_msg,li_msg);
    return re_num;
}
int main()
{
    ///定义sockfd
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(MYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ///bind，success return 0 ,error return -1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }

    ///listen，success return 0 ,error return -1
    if(listen(server_sockfd,QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }
    cout<<"sever listening!"<<endl;
    //socket
    char buffer[BUFFER_SIZE];
	char message[100] = "已成功接收！";
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    //error return -1;
    int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn<0)
    {
        perror("connect");
        exit(1);
    }
    cout<<"connected successfully!"<<endl;
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
		int size = read(conn, buffer, 1024);
        // if(strcmp(buffer,"exit\n")==0)
        //     break;
		// strncat(buffer, message, 100); 
        cout<<"put length:"<<strlen(buffer)<<endl;
        int res=out_message(buffer);
        cout<<" return number test: "<<res<<endl;
        fputs(buffer, stdout);
        cout<<endl;
		write(conn,buffer,strlen(buffer)+1);
    }
    close(conn);
    close(server_sockfd);
    return 0;
}