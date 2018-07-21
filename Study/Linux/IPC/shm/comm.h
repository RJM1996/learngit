
#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

//创建共享内存
int createShm(int size);

//销毁共享内存
int destroyShm(int shmid);

//获得共享内存
int getShm(int size);

