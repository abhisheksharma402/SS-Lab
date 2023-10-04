#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
        //fd1[0],fd2[0] - read end of the file
        //fd1[1],fd2[1] - write end of the file
        int fd1[2],fd2[2];
        int p1 = pipe(fd1);
	int p2 = pipe(fd2);

        if(!fork()){
                // child
                close(1);
                close(fd1[0]);
		close(fd2[0]);
		close(fd2[1]);
                dup2(fd1[1], 1);
                execlp("ls", "ls", "-Rl", (char*)NULL);
        }else{
		if(!fork()){
			close(0);
			close(1);
			dup2(fd1[0],0);
			dup2(fd2[1],1);
			close(fd1[1]);
			close(fd2[0]);
			execlp("grep", "grep", "^d", (char*)NULL);
		}else{
			close(1);
			close(fd1[0]);
			close(fd2[1]);
			dup2(fd2[0],1);
			execlp("wc", "wc", (char*)NULL);
		}
		
	
	}

}

