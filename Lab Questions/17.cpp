/*
Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to
open the file, implement write lock, read the ticket number, increment the number and print
the new ticket number then close the file.
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
	int fd = open("Ticket.txt", O_RDWR, 0777);
	
	if(fd==-1){
                printf("Error while opening file\n");
                perror("Error");
        }


        printf("\nBefore Critical Section\n");
        struct flock fl;
	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0;
        fl.l_pid = getpid();

        fcntl(fd, F_SETLKW, &fl);
	printf("Write lock attained\n");
		
	char ticketno[10];
	int bytesRead = read(fd, &ticketno, sizeof(ticketno));

	printf("bytes read:%d\n",bytesRead);	
	printf("ticket no before incrementing:%s\n",ticketno);	

	int tno=0;
	for(int i=0;i<strlen(ticketno);i++){
		if(ticketno[i] == '\n')continue;
		tno = tno*10+(ticketno[i]-'0');
	}
	printf("\n");
	tno++;
	printf("tno: %d\n",tno);
	
	for(int i=strlen(ticketno)-2;i>=0;i--){
		int r = tno%10;
		ticketno[i] = r+'0';
		tno/=10;	
	}
	
	lseek(fd, 0, SEEK_SET);

	int bytesWritten = write(fd, &ticketno, strlen(ticketno));

        printf("Press enter to release lock: \n");
	getchar();

	fl.l_type = F_UNLCK;


        fcntl(fd, F_SETLKW, &fl);

        printf("Lock released\n");



	int fd_close = close(fd);

        if(fd_close==-1){
                printf("Could not close the file\n");
                perror("Error");
        }

        return 0;


}
