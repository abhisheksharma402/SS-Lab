#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
        //fd[0] - read end of the file
        //fd[1] - write end of the file
        int fd[2];
        int p = pipe(fd);

        if(fork()){
                // parent
                close(1);
                close(fd[0]);
                dup2(fd[1],1);
                execlp("ls", "ls", "-l", (char*)NULL);
        }else{
                close(0);
                close(fd[1]);
                dup2(fd[0],0);
                execlp("wc", "wc", (char*)NULL);
        }

}

