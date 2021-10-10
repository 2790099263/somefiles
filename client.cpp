#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
using namespace std;
#define MYPORT  8010
#define BUFFER_SIZE 1024
#define MAX_LENGTH 1024

//define the sockfd
int sock_cli = socket(AF_INET,SOCK_STREAM, 0);
//define sockaddr_in
struct sockaddr_in servaddr;
inline void sock_init()
{
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  //sever port
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //sever ip

    //connect sever success 1 defeat -1;
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    // cout<<"sever connected successfully!"<<endl;
}
//message send function
inline void send_msg(char *send_buff,char *rev_buff)
{
        write(sock_cli, send_buff, 1024);//send message
		int size = read(sock_cli, rev_buff, 1024);//receive
        fputs(rev_buff, stdout);
}

//change num to char
//num:the number need to change
//rech:the *char returned
//MAX CHANGE LENGTH :1024;
inline void num_to_char(int num,char *rech)
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
//make the num code and our message to massage char*
//The first five digits of the encoding format are the number code, followed by the message
inline void make_msg(char *num_code,char *msg)
{
    char li_msg[MAX_LENGTH];
    strcpy(li_msg,num_code);
    strncat(li_msg,msg,512);
    strcpy(msg,li_msg);
}
int main()
{
    
    char sendbuf[BUFFER_SIZE]="lsc";
    char recvbuf[BUFFER_SIZE];
    sock_init();
    // fgets(sendbuf, sizeof(sendbuf), stdin);
    make_msg("10001",sendbuf);
    fputs(sendbuf,stdout);
    send_msg(sendbuf,recvbuf);
    close(sock_cli);
    return 0;
}