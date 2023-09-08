/*
============================================================================
Name : 29.c
Author : Abhishek Sharma
Description : Write a program to get scheduling policy and modify the 
scheduling policy (SCHED_FIFO, SCHED_RR).
Date: 7th Sep, 2023.
============================================================================
*/
#include <sched.h>
#include<stdio.h>
#include <unistd.h>


void getPolicy(int policy){
	switch(policy){
                case SCHED_FIFO:
                {
                        printf("FIFO\n");
                        break;
                }
                case SCHED_RR:
                {
                        printf("Round Robin\n");
                        break;
                }
                case SCHED_OTHER:
                {
                        printf("Other\n");
                        break;
                }
                default:
                        printf("don't know!!\n");
                        break;
        }
	return;
}


int main(){
	int pid = getpid();

	int policy = sched_getscheduler(pid);
	
	printf("Scheduling policy of process with pid: %d is ",pid);

	getPolicy(policy);

	struct sched_param p;
	p.sched_priority = 99;
	policy = SCHED_RR;	
	int res = sched_setscheduler(pid, policy, &p);

	printf("%d\n",res);
	if(res==-1)perror("Error: ");
	else {
		printf("Scheduling policy of process with pid: %d has been changed to ",pid);
		getPolicy(policy);
	}
}
