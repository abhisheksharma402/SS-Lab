/*
Write a program to open a file, duplicate the file descriptor and append the file with both the
descriptors and check whether the file is updated properly or not.
a. use dup
b. use dup2
c. use fcntl
*/


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int fd = open("example.txt", O_RDWR|O_CREAT|O_APPEND);
	if(fd==-1){
		printf("Error while opening file\n");
		perror("Error");
		return 0;
	}
	int dup_fd1 = dup(fd);
	
	if(dup_fd1==-1){
		printf("Error while duplicating fd\n");
		perror("Error");
	}

	int bytes_appended = write(fd,"Hello ", 6);
	if(bytes_appended==-1){
		printf("Error while writing into file\n");
		perror("Error");
	}
	bytes_appended = write(dup_fd1, "World.", 6);
	if(bytes_appended==-1){
                printf("Error while writing into file\n");
                perror("Error");
        }

	int dup_fd2 = dup2(fd, 6);

	bytes_appended = write(dup_fd2, " How are you?", 13);
	
	if(bytes_appended==-1){
                printf("Error while writing into file\n");
                perror("Error");
        }
	
	int fcntl_fd = fcntl(fd, F_DUPFD, 0);

	if(fd==-1){
		printf("Error while duplicating fd\n");
                perror("Error");
		return 0;
	}
	

	bytes_appended = write(fcntl_fd, "That sounds great!", 18);

        if(bytes_appended==-1){
                printf("Error while writing into file\n");
                perror("Error");
        }


	return 0;
	

}
