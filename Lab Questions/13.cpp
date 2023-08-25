#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
	fd_set rd;
	struct timeval tv;
	int err;
	FD_ZERO(&rd);
	FD_SET(0,&rd);
	tv.tv_sec = 10;
	err = select(1, &rd, NULL, NULL, &tv);
	if(err==0){
		printf("No data was available for 10 seconds\n");
	}
	else{

		printf("Data was available within 10 seconds\n");
	}
	exit(EXIT_SUCCESS);
}
