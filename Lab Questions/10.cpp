/*
Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
bytes (use lseek) and write again 10 bytes.
a. check the return value of lseek
b. open the file with od and check the empty spaces in between the data.
*/


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

int main(){
	int fd = open("file10.txt", O_RDWR|O_CREAT, 0744);
	if(fd==-1){
		perror("Could not open the file\n");
		return 0;
	}
	char buf1[11] = "abcdefghij";
	char buf2[11] = "abcdefghij";
	int written_bytes = write(fd, &buf1, 10);
	if(written_bytes == -1){
		perror("Could not write into file\n");
		return 0;
	}
	int loc = lseek(fd, 10, SEEK_CUR);
	written_bytes = write(fd,&buf2,10);
	if(written_bytes == -1){
                perror("Could not write into file\n");
                return 0;
        }
	printf("lseek returned: %d\n", loc);


	
}
