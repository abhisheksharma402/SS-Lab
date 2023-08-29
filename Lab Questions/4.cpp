/*
Write a program to open an existing file with read write mode. Try O_EXCL flag also. 
*/



#include<stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(){
	int res = open("checkin.txt", O_RDWR|O_EXCL|O_CREAT);
	printf("%d\n",res);
	if(res==-1){
		printf("Error number: %d\n",errno);
		perror("Error");

	}
}
