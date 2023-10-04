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
	
	printf("before changing access permissions:\n");

        printf("Access Permission: %o\n", queue_info.msg_perm.mode);
	

	queue_info.msg_perm.mode = 0644;


	printf("after changing access permissions:\n");
	
	printf("Access Permission: %o\n", queue_info.msg_perm.mode);

}
