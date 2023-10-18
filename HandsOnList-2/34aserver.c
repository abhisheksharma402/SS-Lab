#include <stdio.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#include <string.h> 
#include <stdbool.h> 
#include <stdlib.h> 

void conn(int connFD);

void main()
{
    int socketFileDescriptor, socketBindStatus, socketListenStatus, connectionFileDescriptor;
    struct sockaddr_in serverAddress, clientAddress;

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

    socketBindStatus = bind(socketFileDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (socketBindStatus == -1)
    {
        perror("Error while binding to server socket!");
        _exit(0);
    }

    socketListenStatus = listen(socketFileDescriptor, 10);
    if (socketListenStatus == -1)
    {
        perror("Error while listening for connections on the server socket!");
        close(socketFileDescriptor);
        _exit(0);
    }

    int clientSize;
    clientSize = (int)sizeof(clientAddress);
    connectionFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *)&clientAddress, &clientSize);
    if (connectionFileDescriptor == -1)
    {
        perror("Error while connecting to client!");
        close(socketFileDescriptor);
    }
    else
    {   
        printf("Server Listening on port %d\n",port);
        if(!fork())
        {
            conn(connectionFileDescriptor);
            close(connectionFileDescriptor);
        }
        
    }

    close(socketFileDescriptor);
}

void conn(int cfd)
{
    printf("Client has connected to the server!\n");

    char wbuf[100] = "This is server\n";
    write(cfd, wbuf, strlen(wbuf));
    char rbuf[100];
    memset(rbuf, 0, sizeof(rbuf));
    read(cfd, rbuf, sizeof(rbuf));
    printf("Data from client: %s\n",rbuf);


    printf("Terminating connection to client!\n");
}
