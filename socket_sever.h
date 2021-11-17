#ifndef _SOCKET_SEVER_H
#define _SOCKET_SEVER_H

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

int out_message(char *rev_msg);
void sever_init(void);
void sever_accept(void);
void sever_rev_msg(void);
void sever_close(void);
char * get_buffer();
#endif