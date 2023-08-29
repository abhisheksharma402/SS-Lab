/*
Write a program to perform mandatory locking.
a. Implement write lock
b. Implement read lock
*/


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string>

using namespace std;

int main(int argc, char* argv[]){
	int fd = open("fruits.txt", O_RDWR, 0744);
	
	if(fd==-1){
		printf("Error while opening file\n");
		perror("Error");
	}

	char c;
	printf("Which lock do you want to attain on the file?\n");
	
	scanf("%c%*c",&c);
	
	struct flock fl;
	if(c=='w'){
		printf("\nBefore Critical Section\n");
			
		fl.l_type = F_WRLCK;
		fl.l_whence = SEEK_SET;
		fl.l_start = 0;
		fl.l_len = 0;
		fl.l_pid = getpid();

		fcntl(fd, F_SETLKW, &fl);
		printf("Write lock attained\n");


	}

	else if(c=='r'){
		printf("\nBefore Critical Section\n");
		
                fl.l_type = F_RDLCK;
                fl.l_whence = SEEK_SET;
                fl.l_start = 0;
                fl.l_len = 0;
                fl.l_pid = getpid();

                fcntl(fd, F_SETLKW, &fl);
		printf("Read lock attained\n");

	}
	printf("Press enter to release lock: \n");
	getchar();

	fl.l_type = F_UNLCK;


	fcntl(fd, F_SETLK, &fl);
	
	printf("Lock released\n");
	
	int fd_close = close(fd);

	if(fd_close==-1){
		printf("Could not close the file\n");
		perror("Error");
	}
	return 0;
}
