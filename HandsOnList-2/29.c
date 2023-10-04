#include<stdio.h>
#include<unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main(){
        struct msqid_ds queue_info;
        int queue_status = msgctl(9, IPC_RMID, &queue_info);
	printf("%d\n",queue_status);	

}
