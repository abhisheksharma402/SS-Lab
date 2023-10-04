#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	long PIPE_BUF, OPEN_MAX;
	PIPE_BUF = pathconf(".", _PC_PIPE_BUF);
	OPEN_MAX = sysconf(_SC_OPEN_MAX);
	printf("PIPE_BUF = %ld\t OPEN_MAX = %ld\n",PIPE_BUF,OPEN_MAX);
}

