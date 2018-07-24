
#pragma once

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

// 1. 获取监听套接字
int StartUp(int port); // 传入端口号
