#include<stdio.h>
#include<unistd.h>
#include <sys/sem.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
};

int main(){
	key_t key = ftok(".",'f');
        printf("%d\n",key);
	union semun arg;
	int semid = semget(key, 1, IPC_CREAT|0744);
	arg.val = 4;
	semctl(semid,0,SETVAL, arg);
}


