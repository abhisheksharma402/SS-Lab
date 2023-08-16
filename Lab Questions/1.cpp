#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
        int slink = symlink("hi.mp3","softLink1ToHi.mp3");
	if(slink<0) {
		perror("Failed");
		return 1;
	}
	else std::cout<<"Created Soft Link to hi.mp3 successfully\n";
	int hlink = link("hi.mp3", "hardLink1ToHi.mp3");
	if(hlink<0){
		perror("failed");
		return 1;
	}
	else std::cout<<"Created Hard link to hi.mp3 successfully\n";
	int fifo = mknod("fifo3", S_IFIFO,0);
	if(fifo<0){
		perror("failed");
		return 1;
	}
	else std::cout<<"Create a named pipe by the name fifo2\n";
        
}

