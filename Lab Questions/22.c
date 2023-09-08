/*
============================================================================
Name : 22.c
Author : Abhishek Sharma
Description : Write a program, open a file, call fork, and then write to 
the file by both the child as well as the parent processes. 
Check output of the file.

Date: 5th Sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>

int main(){
	int fd = open("share.txt", O_WRONLY|O_CREAT, 0744);
	int pid = fork();
	//printf("%d\n",pid);
	if(pid==0){
		//printf("hi from child\n");
		//printf("%d\n",pid);
		write(fd, "hi from child\n", 14);
	}
	else{
		//printf("hi from parent\n");
		//printf("%d\n",pid);
		write(fd, "hi from parent\n", 15);
	}
}
