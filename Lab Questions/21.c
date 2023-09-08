/*
============================================================================
Name : 21.c
Author : Abhishek Sharma
Description : Write a program, call fork and print the parent and child 
process id.
Date: 1st Sep, 2023.
============================================================================
*/

#include<stdio.h>
#include <unistd.h>

int main(){
	int pid = fork();
	if(pid==-1){
		printf("no child created");
		return 0;
	}
	if(pid==0){
		printf("child pid: %d\n",getpid());
		printf("parent pid: %d\n",getppid());
	}
	else printf("parent pid: %d\n",getpid());

}
