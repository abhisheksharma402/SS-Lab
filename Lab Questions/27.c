/*
============================================================================
Name : 27.c
Author : Abhishek Sharma
Description : Write a program to execute ls -Rl by the following system calls
	a. execl
	b. execlp
	c. execle
	d. execv
	e. execvp
Date: 5th Sep, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

extern char **environ;


int main(){

	char* arg[] = {"ls", "-lr", NULL};
        printf("using execvp sys call:\n");
        execvp("/bin/ls", arg);

	//char* arg[] = {"ls", "-lr", NULL};
	//printf("using execv sys call:\n");
	//execv("/bin/ls", arg);


	printf("Using execl sys call:\n");
	int r = execl("/bin/ls", "ls", "-lr", NULL);
        printf("%d\n",r);
	sleep(10);
	printf("Using execlp sys call:\n");
	r = execlp("/bin/ls", "ls", "-lr", NULL);
        printf("%d\n",r);
	sleep(10);
	printf("Using execle sys call:\n");
	r = execle("/bin/ls", "ls", "-lr", NULL, environ);
	printf("%d\n",r);
}
