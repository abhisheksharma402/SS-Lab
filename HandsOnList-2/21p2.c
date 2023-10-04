#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){

        int fd1 = open("myfifo1", O_WRONLY);
        int fd2 = open("myfifo2", O_RDONLY);
        char buf1[1024],buf2[1024];


        printf("Enter message to send: ");
        scanf("%[^\n]s",buf1);
        int wb = write(fd1, buf1, sizeof(buf1));
	close(fd1);

	int rb = read(fd2, buf2, sizeof(buf2));
        printf("Message: %s\n",buf2);
	close(fd2);

}

