
#pragma once

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;


const char* status_line = "HTTP/1.0 200 OK\r\n";                                                                   
const char* blank_line = "\r\n";

// 1. 获取监听套接字
int StartUp(int port); // 传入端口号

int get_line(int sock, char line[], int size);

void status_response(int sock, int status_code);

int echo_www(int sock, const char* resource_path, int size);

void handle_hander(int sock);
