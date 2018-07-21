
#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PATHNAME "."
#define PROJ_ID 0X6666

union semun {
    int val; 
    struct semid_ds *buf; 
    unsigned short *array; 
    struct seminfo *__buf; 
};

int commSemSet(int nums, int flags);
int createSemSet(int nums);
int getSemSet(int nums);
int initSem(int semid, int nums, int initVal);
int commPV(int semid, int who, int op);
int P(int semid, int who);
int V(int semid, int who);
int destroySemSet(int semid);
