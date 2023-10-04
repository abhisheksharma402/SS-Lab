#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){

        int fd1 = open("myfifo1", O_RDONLY);
	int fd2 = open("myfifo2", O_WRONLY);
        char buf1[1024],buf2[1024];
		
        int rb = read(fd1, buf1, sizeof(buf1));
        printf("Message: %s\n",buf1);
	close(fd1);

	printf("Enter message to send: ");
	scanf("%[^\n]s",buf2);
	int wb = write(fd2, buf2, sizeof(buf2));
	close(fd2);

}

