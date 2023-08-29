/*
Write a program to create five new files with infinite loop. Execute the program in the background
and check the file descriptor table at /proc/pid/fd.
*/

#include<bits/stdc++.h>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Create five new files
    int fd1 = open("file1.txt",O_RDWR|O_CREAT|O_EXCL, 0744);
    if(fd1==-1){
    	printf("Could not open the file\n");
	perror("Error");
	return 0;
    }
    printf("%d\n",fd1);
    int fd2 = open("file2.txt",O_RDWR|O_CREAT|O_EXCL, 0744);
    if(fd2==-1){
        printf("Could not open the file\n");
        perror("Error");
        return 0;
    }
    printf("%d\n",fd2);

    int fd3 = open("file3.txt",O_RDWR|O_CREAT|O_EXCL, 0744);
    if(fd3==-1){
        printf("Could not open the file\n");
        perror("Error");
        return 0;
    }
    printf("%d\n",fd3);

    int fd4 = open("file4.txt",O_RDWR|O_CREAT|O_EXCL, 0744);
    
    if(fd4==-1){
        printf("Could not open the file\n");
        perror("Error");
        return 0;
    }
    printf("%d\n",fd4);


    int fd5 = open("file5.txt",O_RDWR|O_CREAT|O_EXCL, 0744);

    if(fd5==-1){
        printf("Could not open the file\n");
        perror("Error");
        return 0;
    }
    printf("%d\n",fd5);


    for(;;);

    return 0;
}
