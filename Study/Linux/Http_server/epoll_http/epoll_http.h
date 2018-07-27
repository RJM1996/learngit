
#pragma once

#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/wait.h>

using namespace std;

#define MAX 20
#define MAX_SIZE 1024


// 状态行
extern const char* status_line;                                                               
// 空行
extern const char* blank_line;

// 1. 获取监听套接字
int StartUp(int port); // 传入端口号

int get_line(int sock, char line[], int size);

void status_response(int sock, int status_code);

int echo_www(int sock, const char* resource_path, int size);

void handle_hander(int sock);

void setNoBlock(int fd);

void getConnect(int listen_fd, int epoll_fd);

ssize_t noBlockRead(int fd, char* buf, int size);

void service(int client, int epoll_fd);

static int exe_cgi(int sock, char* method, char* resource_path, char* query_string);
