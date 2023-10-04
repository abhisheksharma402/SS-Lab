#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
	//int p = mknod("fifo22", S_IFIFO|0744, 0);

	int fd = open("fifo22",O_NONBLOCK|O_RDWR);
	printf("fd: %d\n",fd);
	perror("fd");
	if(fd<0){
		printf("Could not open the pipe\n");
		return 0;
	}
	char data[120] = "Hello there!!";
	int wb = write(fd, data, sizeof(data));
	

	fd_set rfds;
	struct timeval  tv;
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);
        tv.tv_sec = 10;
       	tv.tv_usec = 0;
	int retval = select(fd+1, &rfds, NULL, NULL, &tv);
	printf("%d\n",retval);
	if (retval == -1)
		perror("select()");
	else if (retval){
		char data[1024];
		int readBytes = read(fd, data, sizeof(data));

        	if (readBytes == -1)
         		perror("Error while reading from FIFO!");
        	else
            		printf("Data received : %s\n", data);
	}
        else
               	printf("No data within 10 seconds.\n");

       	exit(EXIT_SUCCESS);

}
