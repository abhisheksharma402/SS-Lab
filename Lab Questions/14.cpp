/*
Write a program to find the type of a file.
a. Input should be taken from command line.
b. program should be able to identify any type of a file.
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    const char *filename = argv[1];
    struct stat fileStat;

    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return 2;
    }

    if (S_ISREG(fileStat.st_mode)) {
        printf("%s is a regular file.\n", filename);
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("%s is a directory.\n", filename);
    } else if (S_ISCHR(fileStat.st_mode)) {
        printf("%s is a character device.\n", filename);
    } else if (S_ISBLK(fileStat.st_mode)) {
        printf("%s is a block device.\n", filename);
    } else if (S_ISFIFO(fileStat.st_mode)) {
        printf("%s is a FIFO/pipe.\n", filename);
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("%s is a symbolic link.\n", filename);
    } else if (S_ISSOCK(fileStat.st_mode)) {
        printf("%s is a socket.\n", filename);
    } else {
        printf("%s is of unknown type.\n", filename);
    }

    return 0;
}


