#include<stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<unistd.h>

int main(){
	//fd[0] - read end of the file
	//fd[1] - write end of the file

	int fd[2];

	int p = pipe(fd);

	int pid = fork();

	char buf[1024];

	if(pid){
		// parent
		
		printf("Enter the data for the child: ");
		scanf("%[^\n]s",buf);
		//int rb = read(0, buf, sizeof(buf));
		int wb = write(fd[1], buf, sizeof(buf));	
		printf("\n");
	}
	else{
		//printf("Data from parent: ");
		int rb = read(fd[0], buf, sizeof(buf));
	//	int wb = write(1, buf, rb);
		printf("Data from parent: %s\n",buf);

	}

}
