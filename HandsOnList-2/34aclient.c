#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

void conn(int sockFD);

void main()
{
    int socketFileDescriptor, connectStatus;
    struct sockaddr_in serverAddress;
    struct sockaddr server;

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1)
    {
        perror("Error while creating server socket!");
        _exit(0);
    }

    printf("Enter the port number: ");
    int port;
    scanf("%d",&port);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);           
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY);

    connectStatus = connect(socketFileDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connectStatus == -1)
    {
        perror("Error while connecting to server!");
        close(socketFileDescriptor);
        _exit(0);
    }

    conn(socketFileDescriptor);

    close(socketFileDescriptor);
}


void conn(int sockFD)
{
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;

    read(sockFD, readBuffer, sizeof(readBuffer));
    
    printf("Data from server: %s\n",readBuffer);
    
    scanf("%s",writeBuffer);
    write(sockFD, writeBuffer, strlen(writeBuffer));

    close(sockFD);

}


