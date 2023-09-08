/*
============================================================================
Name : 24.c
Author : Abhishek Sharma
Description : Write a program to create an orphan process. 
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
               	sleep(30);
        }
        else{
                printf("%d\n",getpid());
                sleep(15);
		exit(1);
        }

}
