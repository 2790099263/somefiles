/*
    Author  :LSC
    Time    :2021/11/27
    copyright@LSC 
*/
#ifndef  _SOCKET_CLIENT_H
#define  _SOCKET_CLIENT_H
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
//get your ip//sip is the ip of the sever
void get_ip(char *sip);
//init a socket
void socket_init(void);
//send_msg function 
void send_msg(char *send_buff,char *rev_buff);
//turn number to char 
void num_to_char(int num,char *rech);
//get msg behind the num_code
void make_msg(char *num_code,char *msg);
//close it
void close_it(void);
#endif