#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
        //int f = mknod("fifo1", S_FIFO|0744, 0);

        //int fd = open("myfifo", O_RDONLY);
	//while(1){
		int fd = open("myfifo", O_RDONLY);
		char buf[1024];

		int rb = read(fd, buf, sizeof(buf));
	//	if(rb==0)break;
       		printf("Message: %s\n",buf);
		//fflush(fd);
		close(fd);
	//}
	//close(fd);
	//write(1, buf, rb);
        //while(1){
         //       char ch;
         //       int rb = read(fd, &ch, 1);
          //      if(rb==0)break;
           //     int wb = write(1, &ch, rb);
        //}

}

