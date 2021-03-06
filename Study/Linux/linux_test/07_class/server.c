
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define PATH_NAME "/tmp"
#define PROJ_ID 0X7777

int main()
{
	key_t k = ftok(PATH_NAME, PROJ_ID);
	if(k  < 0){
		printf("ftok error!\n");
		return 1;
	}
	int shmid = shmget(k, 4096, IPC_CREAT|IPC_EXCL|0666);
	if(shmid < 0){
		printf("shmget error!\n");
	}

	char *mem = (char *)shmat(shmid, NULL, 0);

	while(1){
		printf("%s\r", mem);
		fflush(stdout);
		sleep(1);
	}

	shmdt(mem);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}







