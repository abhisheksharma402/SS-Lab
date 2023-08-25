#include<bits/stdc++.h>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Create five new files
    int fd1 = open("file1.txt",O_RDWR|O_CREAT|O_EXCL, 0744);
    std::cout<<fd1<<'\n';
    int fd2 = open("file2.txt",O_RDWR|O_CREAT|O_EXCL, 0744);
    std::cout<<fd2<<'\n';
    int fd3 = open("file3.txt",O_RDWR|O_CREAT|O_EXCL, 0744);
    std::cout<<fd3<<'\n';
    int fd4 = open("file4.txt",O_RDWR|O_CREAT|O_EXCL, 0744);
    std::cout<<fd4<<'\n';
    int fd5 = open("file5.txt",O_RDWR|O_CREAT|O_EXCL, 0744);
    std::cout<<fd5<<'\n';

    for(;;);

    return 0;
}
