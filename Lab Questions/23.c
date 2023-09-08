/*
============================================================================
Name : 23.c
Author : Abhishek Sharma
Description : Write a program to create a Zombie state of the running program.
Date: 5th Sep, 2023.
============================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

int main(){
	int pid = fork();
	//printf("%d\n",pid);
	if(pid==0){
		printf("%d\n",getpid());
		exit(0);
	}
	else{
		printf("%d\n",getpid());
		sleep(60);
	}

}
