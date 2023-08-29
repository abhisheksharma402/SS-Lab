#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
	
	int fd = open("Ticket.txt", O_WRONLY|O_CREAT, 0777);
	char ticketno[10];
	
	int readBytes = read(0, &ticketno, sizeof(ticketno));
	printf("bytes read:%d\n",readBytes);
	int writeBytes = write(fd, &ticketno, strlen(ticketno));

}
