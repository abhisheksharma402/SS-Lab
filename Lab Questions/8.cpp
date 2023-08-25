//
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(){
	int fd = open("fruits.txt", O_RDONLY, 0744);
	char buf[1024];
	if(fd==-1){
		printf("Error number: %d\n", errno);
		perror("Could not open file\n");
	}
	
	while(1){
		int read_bytes = read(fd, &buf,1);
		if(read_bytes==0)break;
		if(buf[read_bytes-1]=='\n')
			buf[read_bytes-1]='\0';
		
		int write_bytes = write(1,&buf,strlen(buf));
	}

}

