/*
============================================================================
Name : 25.c
Author : Abhishek Sharma
Description : Write a program to create three child processes. The parent 
should wait for a particular child (use waitpid system call).
Date: 6th Sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int wstatus;
	int pids[3];
        int child1 = fork();
	if(child1>0){
		printf("Process id of child 1: %d\n",child1);
		pids[0] = child1;
		int child2 = fork();
		if(child2>0){
			printf("Process id of child 2: %d\n",child2);
			pids[1] = child2;
			int child3 = fork();
			if(child3>0){
				printf("Process id of child 3: %d\n",child3);
				pids[2] = child3;
				printf("Waiting for child process with id %d to be terminated\n",child3);
				int p = waitpid(pids[2], &wstatus, WUNTRACED);
				
                		printf("Child process with process %d got terminated\n",p);
			}
			else if(child3==0){
				sleep(30);
			}
		}
	}
}

