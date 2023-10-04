#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/stat.h>
#include<string.h>

int main(){
	//int fd = open("myfifo", O_WRONLY);
	//while(1){
		int fd = open("myfifo", O_WRONLY);
		printf("Enter the message (or 'exit' to quit): ");
		
		char buff[1024];
		scanf("%[^\n]s", buff);
		
		//if(strcmp(buff, "exit")==0)break;
		
		write(fd, buff, sizeof(buff));
		close(fd);
		//continue;
	//}
	//close(fd);
	//int f = mknod("fifo1", S_IFIFO|0744, 0);
	//printf("%d",f);	
	//int fd = open("myfifo", O_WRONLY, 0744);
	//printf("%d\n",fd);
	//printf("Enter the data: ");

	//char buf[1024];
	//scanf("%[^\n]s",buf);
	//int wb = write(fd, buf, sizeof(buf));
}
