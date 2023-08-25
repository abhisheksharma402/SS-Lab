#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int fd = open("example.txt", O_RDWR|O_CREAT|O_APPEND);
	int dup_fd1 = dup(fd);

	int bytes_appended = write(fd,"Hello ", 6);
	bytes_appended = write(dup_fd1, "World.", 6);
	
	int dup_fd2 = dup2(fd, 6);

	bytes_appended = write(dup_fd2, " How are you?", 13);
	
}
