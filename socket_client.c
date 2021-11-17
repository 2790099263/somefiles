#include "socket_client.h"

#define MYPORT 8010
#define BUFFER_SIZE 1024
#define MAX_LENGTH 1024

int sock_cli ; 
char ip[MAX_LENGTH]="127.0.0.1";
struct sockaddr_in servaddr;
void get_ip(char *sip)
{
    strcpy(ip,sip);
    return ;
}
 void socket_init()
{
    sock_cli=socket(AF_INET,SOCK_STREAM,0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  //sever port
    servaddr.sin_addr.s_addr = inet_addr(ip);  //sever ip

    //connect sever success 1 defeat -1;
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    return ;
}
//message send function 
 void send_msg(char *send_buff,char *rev_buff)
{
        write(sock_cli, send_buff, 1024);//send message
		int size = read(sock_cli, rev_buff, 1024);//receive
        fputs(rev_buff, stdout);
}
//change num to char
//num:the number need to change
//rech:the *char returned
//MAX CHANGE LENGTH :1024;
 void num_to_char(int num,char *rech)
{
    char rev[MAX_LENGTH]; //reverse *char
    int tot=0,rev_tot=0;
    while (num)
    {
        rech[tot++]=(num%10)+'0';
        num/=10;
    }
    tot--;
    for(int i=tot;i>=0;i--)
        rev[rev_tot++]=rech[i];
    rev[rev_tot]='\0';
    for(int i=0;i<=rev_tot;i++)rech[i]=rev[i];
}
void make_msg(char *num_code,char *msg)
{
    char li_msg[MAX_LENGTH];
    strcpy(li_msg,num_code);
    strncat(li_msg,msg,512);
    strcpy(msg,li_msg);
}
void close_it(void)
{
    close(sock_cli);
    return ;
}