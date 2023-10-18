#include<stdio.h>
#include<unistd.h>
#include <sys/sem.h>
#include <fcntl.h>
#include "struct.h"


union semun{
        int val;
        struct semid_ds *buf;
        unsigned short int *array;
};


int main(){


    key_t key_sem = ftok(".",'f');
    printf("%d\n",key_sem);
    union semun arg;
    int semid = semget(key_sem, 1, IPC_CREAT|0744);
    arg.val = 1;
    semctl(semid,0,SETVAL, arg);

    struct sembuf buf;
    buf.sem_num=0;
    buf.sem_flg=0;


    key_t key_sm = ftok(".",'e');
    printf("%d\n",key_sm);
    int r = shmget(key_sm, 1024, IPC_CREAT|0744);
    printf("%d\n",r);
    if(r<0){
            perror("Error while creating shared memory: ");
            return 0;
    }

    char* data = shmat(r, 0,0);


    printf("before cs\n");

    printf("enter something to enter cs: ");
    getchar();

    buf.sem_op = -1;

    semop(semid, &buf, 1); // locking

    printf("inside cs\n");




    printf("enter someting to exit the cs: ");
    getchar();
    buf.sem_op=1;
    semop(semid, &buf, 1); // unlocking

    printf("after cs\n");

        
}
