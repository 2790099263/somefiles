#include "socket_sever.h"

#define MYPORT  8010
#define QUEUE   20
#define BUFFER_SIZE 1024
#define MAX_LENGTH 1024

int server_sockfd;
struct sockaddr_in server_sockaddr;
char buffer[BUFFER_SIZE];
char message[100] = "已成功接收！";
struct sockaddr_in client_addr;
socklen_t length = sizeof(client_addr);
int conn;

int out_message(char *rev_msg)
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
void sever_init()
{
    server_sockfd = socket(AF_INET,SOCK_STREAM,0);
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
    printf("Listening !\n");
    return ;
}
void sever_accept()
{
    conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn<0)
    {
        perror("connect");
        exit(1);
    }
    puts("connected successfully!");
    return ;
}
void sever_rev_msg()
{
    memset(buffer,0,sizeof(buffer));
    int size = read(conn,buffer,1024);
    int res=out_message(buffer);
    fputs(buffer,stdout);
    write(conn,buffer,strlen(buffer)+1);
    return ;
}
void sever_close()
{
    close(conn);
    close(server_sockfd);
    return ;
}
char * get_buffer()
{
    return buffer;
}