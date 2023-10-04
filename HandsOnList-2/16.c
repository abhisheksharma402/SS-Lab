#include<stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<unistd.h>

int main(){

        //int p1 = mknod("pipe1", S_IFIFO|0744, 0);
	//int p2 = mknod("pipe2", S_IFIFO|0744, 0);
	
	int fd1[2], fd2[2];
	pipe(fd1);
	pipe(fd2);
	char buf1[1024],buf2[1024];
        //printf("%d %d\n",p1,p2);
        
	//int fd1,fd2,fd3,fd4;
        
	if(!fork()){
                close(fd1[0]);
		close(fd2[1]);
		
		printf("inside child\n");
		//buf[1024];
		printf("enter the message to parent:\n");	

                //while(1){
                 //       char ch;
                 //       int rb = read(0, &ch, 1);
                   //     if(ch=='\n')break;
                     //   int wb = write(fd1[1], &ch,  1);
                //}
		scanf("%s",buf1);
		int wb = write(fd1[1],buf1,sizeof(buf1));
		
		int rb = read(fd2[0],buf2,sizeof(buf2));

		printf("\nchild received - %s",buf2);

		//while(1){
                  //      char ch;
                   //     int rb = read(fd2[0], &ch, 1);
                    //    //printf("rb child: %d\n", rb);
                    //    if(rb==0)break;
                    //    int wb = write(1, &ch,  1);
                        //printf("wb child: %d\n", wb);
                //}

		//close(fd2);


        }else{
		close(fd1[1]);
		close(fd2[0]);
		printf("inside parent\n");

                printf("\nmessage from child: ");
		
		int rb = read(fd1[0],buf1,sizeof(buf1));
		
		printf("%s\n",buf1);

               // while(1){
                 //       char ch;
                   //     int rb = read(fd1[0], &ch, 1);
                     //   if(rb==0)break;
                       // int wb = write(1, &ch,  1);
                //}

                printf("\nenter message to child - ");
		scanf("%s",buf2);
		int wb = write(fd2[1],buf2,sizeof(buf2));
		

                //while(1){
                  //      char ch;
                    //    int rb = read(0, &ch, 1);
                        //printf("rb child: %d\n", rb);
                      //  if(ch=='\n')break;
                        //int wb = write(fd2[1], &ch,  1);
                        //printf("wb child: %d\n", wb);
                //}


	}

}

