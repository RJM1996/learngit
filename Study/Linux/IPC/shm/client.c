
#include "comm.h"

int main()
{
    int shmid = getShm(4096);
    sleep(1);
    char* address = shmat(shmid, NULL, 0);
    sleep(2);
    int i = 0;

    while(i < 30)
    {
        address[i] = 'A' + i;
        i++;
        address[i] = 0;
        sleep(1);
    }

    shmdt(address);
    sleep(2);

    return 0;
}
