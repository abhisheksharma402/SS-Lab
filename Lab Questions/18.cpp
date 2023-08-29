/*Write a program to perform Record locking.
a. Implement write lock
b. Implement read lock
Create three records in a file. Whenever you access a particular record, first lock it then modify/access
to avoid race condition.*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char* argv[]){
	if(argc!=3){
		printf("Required number of arguments not present\n");
		return 0;
	}
	
	int fd = open("Records.txt", O_RDWR, 0777);

	if(fd==-1){
		printf("Could not open the file\n");
		perror("Error");
		return 0;
	}

	int record = (int)*argv[2] - 48;

	int lock_type;
	if(strcmp(argv[1],"write")==0) lock_type=1;
	else if(strcmp(argv[1],"read")==0)lock_type=2;
	else{
		printf("Please provide valid lock type to be attained\n");
		return 0;
	}



	if(record>=1 && record <=3){

		struct flock fl;
	
		switch (lock_type){
			case 1:{
				printf("Before Critical Section\n");
                		fl.l_type = F_WRLCK;
                		fl.l_whence = SEEK_SET;
                		fl.l_start = 10*(record-1);
                		fl.l_len = 10;
                		fl.l_pid = getpid();

                		fcntl(fd, F_SETLKW, &fl);
				printf("Attaining Write Lock on Record %d...\n",record);
				
				sleep(2);

                		printf("Write lock on record %d attained\n",record);
				
				sleep(2);
		
				printf("Update the record by providing input below:\n");

				char buf[10];
				lseek(fd, 10*(record-1), SEEK_SET);
				int bytes_read = read(0,&buf,10);
				lseek(fd, -10*(record-1), SEEK_SET);
				
				printf("Writing Record %d....\n",record);
				sleep(2);
				int bytes_written = write(fd,&buf,10);

				printf("Record %d edited succesfully.",record);
				break;
			}
			case 2:
			{
				printf("Before Critical Section\n");
                                fl.l_type = F_RDLCK;
                                fl.l_whence = SEEK_SET;
                                fl.l_start = 11*(record-1);
                                fl.l_len = 10;
                                fl.l_pid = getpid();
				
				fcntl(fd, F_SETLKW, &fl);

				printf("\nAttaining lock on Record %d....\n",record);
				sleep(2);
                                
				printf("\nRead lock on record %d attained\n",record);
				
				sleep(2);

				printf("\nReading Data of Record %d....\n",record);
				sleep(2);

				printf("\nData of Record %d: \n",record);
				
				char buf[10];
				lseek(fd, 10*(record-1), SEEK_SET);
                                int bytes_read = read(fd,&buf,10);

				//printf("\nData of Record %d: ",record);

				int bytes_written_stdout = write(1,&buf,10);
				break;
			}
			default:
				printf("Please provide valid lock type to be attained\n");
				break;

		}

		printf("\nEnter to release lock\n");
		getchar();
		fl.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &fl);

		printf("%s Lock Released on record %d\n",argv[1],record);

		int fd_close = close(fd);
		if(fd_close==-1){
			printf("Could not close the file\n");
			perror("Error");
		}
	}

}

