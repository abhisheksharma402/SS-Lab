// program to implement cp command
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Enough arguments not provided. Source file and destination files are required\n");
		return 0;
	}
	if(argc > 3){
		printf("Too many arguments provided.\n");
		return 0;
	}
	

	int fd_read = open(argv[1], O_RDONLY);
	if(fd_read==-1){
		printf("Error number: %d",errno);
		perror("Could not open file\n");
		return 0;
	}
	
	int fd_write = open(argv[2], O_WRONLY|O_CREAT, 0744);
	
	if(fd_write==-1){
		printf("Error number: %d",errno);
                perror("Could not open file\n");
                return 0;
	}

	while(1){
		
		char buf;

		int read_byte = read(fd_read, &buf, 1);
		if(read_byte==-1){
                	printf("Error number: %d",errno);
                	perror("Could not read from file\n");
                	return 0;
		}

		if(read_byte==0)break;
		int written_byte = write(fd_write, &buf, 1);
		if(written_byte==-1){
                        printf("Error number: %d",errno);
                        perror("Could not write to file\n");
                        return 0;
                }

	
	}

	int close_fd_read = close(fd_read);
        int close_fd_write = close(fd_write);
	
	if(close_fd_read == -1 || close_fd_write == -1){
		printf("Could not close file\n");
		return 0;
	}
	
}
