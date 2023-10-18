#include<stdio.h>
#include<unistd.h>
#include <sys/sem.h>
#include <fcntl.h>
#include "struct.h"


union semun{
    int val;
};


int main(){

    int fd = open("ticket.txt", O_RDONLY);

    if(fd==-1){
        perror("error while opening file");
        return 0;
    }

    key_t key_sem = ftok(".",'z');
    printf("%d\n",key_sem);
    union semun arg;
    int semid = semget(key_sem, 1, IPC_CREAT|0744);
    arg.val = 2;
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

    struct ticket t;

    int rb = read(fd, &t, sizeof(struct ticket));
    if(rb==-1){
        perror("error while reading from file");
        return 0;
    }

    printf("Data: %d\n",t.n);



    printf("enter someting to exit the cs: ");
    getchar();
    buf.sem_op=1;
    semop(semid, &buf, 1); // unlocking

    printf("after cs\n");

    close(fd);

        
}
