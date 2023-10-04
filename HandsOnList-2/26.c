#include<stdio.h>
#include<unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include<string.h>

struct msgbuf{
	long mtype;
	char mtext[1024];
};

int main(){
	key_t key = ftok(".",'d');
        int q = msgget(key, IPC_CREAT|0744);
        struct ipc_perm ipc;
        struct msqid_ds ds;
	struct msgbuf buf;	

        printf("Key: 0x%0x\n",key);
        printf("Message queue id: %d\n",q);

	printf("Enter the message type: ");
	scanf("%ld",&buf.mtype);
	printf("Enter the message: ");
	scanf("%s",buf.mtext);

	int size = strlen(buf.mtext);
	
	int res = msgsnd(q, &buf, size+1, 0);
	printf("%d\n",res);

	struct msgbuf recbf;
	printf("enter the message type you want to fetch: ");
	int type;
	scanf("%d",&type);
	res = msgrcv(q, &recbf, sizeof(recbf.mtext), type, 0);

	printf("message type: %ld, \t message: %s\n",recbf.mtype, recbf.mtext);


}
