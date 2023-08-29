/*
Write a program to create a file and print the file descriptor value. Use creat ( ) system call
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int fd = creat("myfile2.txt", O_RDWR);
	
	printf("file descriptor: %d\n",fd);
	
	if(fd==-1){
                perror("Could not Create the file\n");
                return 0;
       	}
}
