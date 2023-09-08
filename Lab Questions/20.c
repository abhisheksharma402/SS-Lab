/*
============================================================================
Name : 20.c
Author : Abhishek Sharma
Description : Find out the priority of your running program. Modify the 
priority with nice command.
Date: 1st Sep, 2023.
============================================================================
*/


#include<stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main(){
	pid_t pid = getpid();
	printf("pid %d\n",pid);
	int p = getpriority(PRIO_PROCESS, pid);
	printf("Original Priority: %d\n",p);

	int niceValue = nice(-5);
	printf("Nice Value: %d\n",p);
	int newp = getpriority(PRIO_PROCESS, pid);
	printf("New Priority: %d\n",newp);

}
