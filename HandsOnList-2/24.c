//Write a program to create a message queue and print the key and message queue id.

#include<stdio.h>
#include<unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main(){
        key_t key = ftok(".",'b');
        int q = msgget(key, IPC_CREAT| 0744);
        struct ipc_perm ipc;
	struct msqid_ds ds;
	
	printf("Permissions: %u\n",ds.msg_perm.mode);

        printf("Key: 0x%0x\n",key);
        printf("Message queue id: %d\n",q);
}
