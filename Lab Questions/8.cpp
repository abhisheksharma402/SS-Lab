/*
Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> 

int main(int argc, char *argv[])
{
    if (argc != 2){
        printf("Pass the file to be read as the argumenti");
	return 0;
    }
    int fd = open(argv[1], O_RDONLY);
    char buf;
    
    if (fd == -1){
    	perror("Could not open the file!!");
    	return 0;
    }
    
    while (1)
    {
	    int bytesRead = read(fd, &buf, 1);
	    if(bytesRead==0)break;
	    
	    if (buf == '\n')
		    write(1, "\n", 1);
	    else
		    write(1, &buf, 1);
    }
    
    int fd_close = close(fd);
    
    if(fd_close==-1){
	    printf("Error while closing the file\n");
	    perror("Error");
    }
    
    
}
