/*
Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
*/

#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <errno.h>


int main(){
	char buf[50];
	int bytes_read = read(0, buf, 15);
	if(bytes_read==-1){
		printf("%d\n",errno);
		perror("Could not read the file\n");
	}
	int bytes_wrote = write(1, buf, 15);
	if(bytes_wrote==-1){
                printf("%d\n",errno);
                perror("Could not write to the file\n");
        }
	return 0;
	
	
}
