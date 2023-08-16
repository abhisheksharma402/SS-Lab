#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

int main(){
	int fd = creat("myfile2.txt", O_RDWR);

	std::cout<<"file descriptor: "<<fd<<'\n';
	if(fd==-1){
		std::cout<<"Error number: " << errno << '\n';
		perror("Program");
	}
}
