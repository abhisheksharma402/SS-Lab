#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

int main(){
	int fd = open("file10.txt", O_RDWR|O_CREAT, 0744);
	char buf1[11] = "abcdefghij";
	char buf2[11] = "abcdefghij";
	int written_bytes = write(fd, &buf1, 10);
	int loc = lseek(fd, 10, SEEK_CUR);
	written_bytes = write(fd,&buf2,10);
	printf("lseek returned: %d\n", loc);

	
}
