//Write a program to create a message queue and print the key and message queue id.

#include<stdio.h>
#include<unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main(){
	struct msqid_ds queue_info;
	key_t key = ftok(".",'c');
	int q = msgget(key, IPC_CREAT|0744);
	struct ipc_perm ipc;
	int queue_status = msgctl(q, IPC_STAT, &queue_info);
	
	printf("Access Permission: %o\n", queue_info.msg_perm.mode);
    	printf("UID: %d\n", queue_info.msg_perm.uid);
    	printf("GID: %d\n", queue_info.msg_perm.gid);
    	printf("Time of last message sent: %ld\n", queue_info.msg_stime);
    	printf("Time of last message received: %ld\n", queue_info.msg_rtime);
    	printf("Size of queue: %ld\n", queue_info.__msg_cbytes);
    	printf("Number of messages in the queue: %ld\n", queue_info.msg_qnum);
    	printf("Maximum number of bytes allowed in the queue: %ld\n", queue_info.msg_qbytes);
    	printf("PID of last sent message: %d\n", queue_info.msg_lspid);
   	printf("PID of last received message: %d\n", queue_info.msg_lrpid);

}

