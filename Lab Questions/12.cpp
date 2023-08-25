#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

int main(){
	int fd = open("fruits.txt",O_RDWR, 0744);
	int status = fcntl(fd, F_GETFL);
	printf("Status: %d\n",status);

	int accessMode = status & O_ACCMODE;
    	printf("File %s is opened with mode: ", "fruits.txt");
    	switch (accessMode) {
        	case O_RDONLY:
			printf("Read-only\n");
            		break;
        	case O_WRONLY:
            		printf("Write-only\n");
            		break;
        	case O_RDWR:
            		printf("Read-write\n");
            		break;
		default:
	    		printf("Unknown\n");
	       		break;
    	}
	
	if (close(fd) == -1) {
        	perror("close");
        	return 4;
    	}

}
