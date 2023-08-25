#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string>

using namespace std;

int main(int argc, char* argv[]){
	int fd = open("fruits.txt", O_RDWR, 0744);
	char c;
	printf("Which lock do you want to attain on thee file?\n");
	
	scanf("%c%*c",&c);
	
	printf("\nBefore Critical Section\n");
	struct flock fl;
	if(c=='w'){
			
		fl.l_type = F_WRLCK;
		fl.l_whence = SEEK_SET;
		fl.l_start = 0;
		fl.l_len = 0;
		fl.l_pid = getpid();

		fcntl(fd, F_SETLKW, &fl);
		printf("Write lock attained\n");


		printf("Press enter to release lock: \n");
		getchar();
	}

	else if(c=='r'){
		
                fl.l_type = F_RDLCK;
                fl.l_whence = SEEK_SET;
                fl.l_start = 0;
                fl.l_len = 0;
                fl.l_pid = getpid();

                fcntl(fd, F_SETLKW, &fl);
		printf("Read lock attained\n");

                printf("Press enter to release lock: \n");
                getchar();


	}
	

	fl.l_type = F_UNLCK;


	fcntl(fd, F_SETLK, &fl);
	
	printf("Lock released\n");


}
