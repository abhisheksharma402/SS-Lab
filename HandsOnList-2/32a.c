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
    key_t key = ftok(".",'f');
    printf("%d\n",key);
    union semun arg;
    int semid = semget(key, 1, IPC_CREAT|0744);
    arg.val = 1;
    semctl(semid,0,SETVAL, arg);

    struct sembuf buf;
    buf.sem_num=0;
    buf.sem_flg=0;

    printf("before cs\n");

    printf("enter something to enter cs: ");
    getchar();

    buf.sem_op = -1;

    semop(semid, &buf, 1); // locking

    printf("inside cs\n");

    int fd = open("ticket.txt", O_RDWR);

    struct ticket t;
    int rb = read(fd, &t, sizeof(struct ticket));

    t.n++;

    int offset = lseek(fd, 0, SEEK_SET);

    int wb = write(fd, &t, sizeof(struct ticket));

    printf("enter someting to exit the cs: ");
    getchar();
    buf.sem_op=1;
    semop(semid, &buf, 1); // unlocking

    printf("after cs\n");

        
}
