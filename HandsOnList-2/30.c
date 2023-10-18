#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(){
	key_t key = ftok(".",'e');
	printf("%d\n",key);
	int r = shmget(key, 1024, IPC_CREAT|0744);
	printf("%d\n",r);
	if(r<0){
		perror("Error while creating shared memory: ");
		return 0;
	}

	char* data = shmat(r, 0,0);
	//printf("%d\n",ret);
	
	printf("Enter a message: ");
	scanf("%[^\n]",data);

	//removing the shared memory
	
	int ret = shmctl(r, IPC_RMID, NULL);
	if(ret<0){
		printf("Shared memory couldn't be removed\n");
		return 0;
	}
	printf("Shared memory removed with return value: %d\n",ret);

}
