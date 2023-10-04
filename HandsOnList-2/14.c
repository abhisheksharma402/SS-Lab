#include<stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>

int main(){
	
	int fd[2];
	int p = pipe(fd);
	if(p<0){
		printf("pipe failed\n");
		return 0;
	}
	// write to the pipe
	printf("Enter data into the pipe: ");
	char buf[1024];
	scanf("%[^\n]s",buf);
	//int rb = read(0, buf, sizeof(buf));
	int wb = write(fd[0], buf, sizeof(buf));
		
	// read from the pipe
	printf("\nData from the pipe: ");
	int rb = read(fd[1], buf, sizeof(buf));
	printf("%s\n",buf);
	//wb = write(1, buf, rb);

	return 0;


}


