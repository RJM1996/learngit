/*================================================================

# File Name: proto.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月21日 星期一 08时30分30秒

================================================================*/



#pragma once
// 定义通信的结构体, 两个加数 a b, 以及和 sum

typedef struct Request {
    double a;
    double b;
} Request;

typedef struct Response {
    double sum;
} Response;
