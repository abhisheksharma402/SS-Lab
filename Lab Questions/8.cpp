//
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(){
	int fd = open("fruits.txt", O_RDONLY, 0744);
	
	if(fd==-1){
		printf("Error number: %d\n", errno);
		perror("Could not open file\n");
	}
	
	while(1){
		char buf[1024];
		int read_bytes = read(fd, &buf,1);
		if(read_bytes==0)break;
		printf("strlen buf: %d\n",strlen(buf));
		if(buf[strlen(buf)-1] == '\n'){
			int write_bytes = write(1,&buf,strlen(buf));
		}
	}

}

