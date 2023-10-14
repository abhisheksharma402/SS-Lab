// #include<stdio.h>
// #include <sys/socket.h>
// #include<unistd.h>
// #include <netinet/ip.h>
// #include <string.h>
// #include <stdbool.h> 
// #include <stdlib.h>
// #include "student.h"
// #include "faculty.h"
// #include "admin.h"

// int main(){
// 	struct sockaddr_in server_addr, client_addr;
	
// 	int sfd = socket(AF_INET, SOCK_STREAM, 0);

// 	if(sfd==-1){
// 		perror("Error while creating the server socket: \n");
// 		return 0;
// 	}

// 	server_addr.sin_family = AF_INET;
// 	server_addr.sin_port = htons(8899);
// 	server_addr.sin_addr.s_addr = INADDR_ANY;


// 	int b = bind(sfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

// 	if(b==-1){
// 		perror("Error while binding\n");
// 		return 0;
// 	}

// 	int l = listen(sfd, 5);
// 	if(l==-1){
// 		perror("Error while listening for connections\n");
// 		close(sfd);
// 		return 0;
// 	}

// 	int c;
// 	while(1){
// 		c = (int)sizeof(client_addr);
// 		int cfd = accept(sfd, (struct sockaddr*)&client_addr,  &c);
// 		if(cfd==-1){
// 			perror("Error while connecting to client\n");
// 			close(sfd);
// 		}else{
// 			int pid = fork();
// 			if(pid==0){
// 				// child
// 				printf("client has connected to the server\n");
// 				char writebf[4096] = "....................................Welcome Back to Academia :: Course Registration....................................\n\nEnter your role {1. Faculty 2. Student 3. Admin 4. Exit}\n";
// 				char readbf[1024];

// 				int wb = write(cfd, writebf, sizeof(writebf));

// 				if(wb==-1){
// 					perror("Error while sending message to client: ");
// 					printf("Closing connection with client..\n");
// 					close(cfd);
// 					return 0;
// 				}


// 				memset(readbf, 0, sizeof(readbf));

// 				int rb = read(cfd, readbf, sizeof(readbf));
// 				if(rb<0){
// 					perror("Error while receiving message from client\n");
// 					printf("Closing connection with client..\n");
// 					close(cfd);
// 					return 0;
// 				}
				
// 				int choice = atoi(readbf);
// 				printf("choice: %d\n",choice);
// 				switch(choice){
// 					case 1:
// 					{
// 						// handle faculty role
// 						facultyMenu(cfd);


// 						break;
// 					}
// 					case 2:
// 					{
// 						// handle student role
// 						studentMenu(cfd);

// 						break;
// 					}
// 					case 3:
// 					{
// 						// handle admin role
// 						adminMenu(cfd);
// 						break;
// 					}
// 					case 4:
// 					{
// 						// return;
// 						close(cfd);
// 						break;
// 					}
// 					default:
// 					{
// 						// invalid choice;
// 						break;
// 					}
// 				}

// 				printf("Closing the connection with client..\n");

// 			}



// 		}
		
		
// 	}





// }




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

#include "auth.h"
#include "student.h"
#include "faculty.h"
#include "admin.h"

void connection_handler(int connFD); // Handles the communication with the client

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

    serverAddress.sin_family = AF_INET;                // IPv4
    serverAddress.sin_port = htons(8047);              // Server will listen to port 8080
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Binds the socket to all interfaces

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
    while (1)
    {
        clientSize = (int)sizeof(clientAddress);
        connectionFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *)&clientAddress, &clientSize);
        if (connectionFileDescriptor == -1)
        {
            perror("Error while connecting to client!");
            close(socketFileDescriptor);
        }
        else
        {
            if (!fork())
            {
                // Child will enter this branch
                connection_handler(connectionFileDescriptor);
                close(connectionFileDescriptor);
                _exit(0);
            }
			
        }
    }

    close(socketFileDescriptor);
}

void connection_handler(int cfd)
{
    printf("Client has connected to the server!\n");


    


    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;
    int userChoice;

	strcpy(writeBuffer, "....................................Welcome Back to Academia :: Course Registration....................................\n\nEnter your role {1. Faculty 2. Student 3. Admin 4. Exit}\n");

    writeBytes = write(cfd, writeBuffer, strlen(writeBuffer));

    if (writeBytes == -1)
        perror("Error while sending first prompt to the user!");
    else
    {
        bzero(readBuffer, 1000);
        readBytes = read(cfd, readBuffer, sizeof(readBuffer));

        

        if (readBytes == -1)
            perror("Error while reading from client");
        else if (readBytes == 0)
            printf("No data was sent by the client");
        else
        {
            userChoice = atoi(readBuffer);
            printf("%d\n",userChoice);
            switch (userChoice)
            {
            case 1:
                facultyMenu(cfd);
                break;
            case 2:
                studentMenu(cfd);
                break;
			case 3:
				adminMenu(cfd);
				break;
			case 4:
				return;
            default:
                // Exit
                break;
            }
        }
    }
    printf("Terminating connection to client!\n");
}
