#include <stdio.h>      // Import for `printf` & `perror` functions
#include <errno.h>      // Import for `errno` variable
#include <fcntl.h>      // Import for `fcntl` functions
#include <unistd.h>     // Import for `fork`, `fcntl`, `read`, `write`, `lseek, `_exit` functions
#include <sys/types.h>  // Import for `socket`, `bind`, `listen`, `connect`, `fork`, `lseek` functions
#include <sys/socket.h> // Import for `socket`, `bind`, `listen`, `connect` functions
#include <netinet/ip.h> // Import for `sockaddr_in` stucture
#include <string.h>     // Import for string functions

void connection_handler(int sockFD); // Handles the read & write operations to the server

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

    serverAddress.sin_family = AF_INET;                // IPv4
    serverAddress.sin_port = htons(8047);              // Server will listen to port 8080
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Binds the socket to all interfaces

    connectStatus = connect(socketFileDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connectStatus == -1)
    {
        perror("Error while connecting to server!");
        close(socketFileDescriptor);
        _exit(0);
    }

    connection_handler(socketFileDescriptor);

    close(socketFileDescriptor);
}

// Handles the read & write operations w the server
void connection_handler(int sockFD)
{
    char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading from / writting to the server
    ssize_t readBytes, writeBytes;            // Number of bytes read from / written to the socket

    char tempBuffer[1000];

    
    while(1){
        bzero(readBuffer, 1000); // Empty the read buffer
        // bzero(tempBuffer, sizeof(tempBuffer));
        readBytes = read(sockFD, readBuffer, sizeof(readBuffer));
        // if(readBytes==0)break;
		printf("read bytes: %ld\n",readBytes);
		// printf("rbuf: %s\n",readBuffer);
        if (readBytes == -1)
            perror("Error while reading from client socket!");
        else if (readBytes == 0)
            printf("No error received from server! Closing the connection to the server now!\n");
        // else if (strchr(readBuffer, '^') != NULL)
        // {
        //     // Skip read from client
        //     strncpy(tempBuffer, readBuffer, strlen(readBuffer) - 1);
        //     printf("%s\n", tempBuffer);
        //     writeBytes = write(sockFD, "^", strlen("^"));
        //     if (writeBytes == -1)
        //     {
        //         perror("Error while writing to client socket!");
        //         break;
        //     }
        // }
        // else if (strchr(readBuffer, '$') != NULL)
        // {
        //     // Server sent an error message and is now closing it's end of the connection
        //     strncpy(tempBuffer, readBuffer, strlen(readBuffer) - 2);
        //     printf("%s\n", tempBuffer);
        //     printf("Closing the connection to the server now!\n");
        //     break;
        // }
        else
        {
            bzero(writeBuffer, 1000); // Empty the write buffer

			// printf("%s\n", readBuffer);
            write(1, readBuffer, sizeof(readBuffer));
            int i=0;
            while(1){
                char c;
                // fflush(stdin);
                read(0, &c, 1);
                if(c=='\n')break;
                writeBuffer[i]=c;
                i++;
            }

            writeBuffer[i]='\0';
            
			// scanf(" %[^\n]s", writeBuffer);

            writeBytes = write(sockFD, writeBuffer, strlen(writeBuffer));

            if (writeBytes == -1)
            {
                perror("Error while writing to client socket!");
                printf("Closing the connection to the server now!\n");
                break;
            }
        }
    }

    close(sockFD);

}





// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/ip.h>
// #include <string.h>
// #include <errno.h>
// #include <stdbool.h>

// struct message
// {
//     int id;
//     bool type;
//     int action;
//     char body[1000];
// };

// void my_client_handle(int sfd);
// void main()
// {
//     // create socket address structure
//     struct sockaddr_in saddr;
//     int sfd, status;
//     // create socket
//     sfd = socket(AF_INET, SOCK_STREAM, 0);
//     // error
//     if (sfd == -1)
//     {
//         perror("Error while creating socket: ");
//         exit(1);
//     }
//     // successfully created socket.
//     printf("client side: socket created successfully \n");
//     // Set Address fields.
//     saddr.sin_addr.s_addr = htonl(INADDR_ANY);
//     saddr.sin_family = AF_INET;
//     saddr.sin_port = htons(8895);
//     // Connect to server.
//     status = connect(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
//     // error
//     if (status == -1)
//     {
//         perror("Error while connecting to server: ");
//         exit(1);
//     }
//     // successfully connected to server.
//     printf("client to server connection successfully established\n");

//     // Communication
//     my_client_handle(sfd);
//     // End of communication
//     close(sfd);
// }

// void my_client_handle(int sfd)
// {
//     char *exit_msg = "";
//     int readBytes, writeBytes;
//     struct message msg;
//     msg.id = 0;
//     int itr = 1;
//     while (itr)
//     {
//         readBytes = read(sfd, &msg, sizeof(msg));

//         /*
//         check if it is a (0)control Message or (1)Data Message...
//         */
//         if (msg.type == 0)
//         {
//             // control Message
//             if (msg.action == 0)
//             { // Exit Signal
//                 exit_msg = "\nExit Signal Received from Server\nExiting...\n";
//                 write(1, exit_msg, strlen(exit_msg));
//                 return;
//             }
//             else if (msg.action == 1)
//             { // Ignore Read from STDIN and write to the server...
//                 write(1, msg.body, strlen(msg.body));
//             }
//             else
//                 return;
//         }
//         else if (msg.type == 1)
//         {
//             // Data Message
//             if (msg.action == 0)
//             { // Reply Type: int/char/bool (one word)...
//                 write(1, msg.body, strlen(msg.body));
//                 msg.id = itr;
//                 char temp[1000];
//                 read(0, temp, sizeof(temp));
//                 bzero(msg.body, sizeof(msg.body));
//                 int i = 0;
//                 while (temp[i] != ' ' && temp[i] != '\n' && temp[i] != '\0')
//                 {
//                     msg.body[i] = temp[i];
//                     i++;
//                 }
//                 msg.body[i] = '\0';
//                 writeBytes = write(sfd, &msg, sizeof(msg));
//             }

//             else if (msg.action == 1)
//             { // Reply Type: string (one sentence)...
//                 write(1, msg.body, strlen(msg.body));
//                 msg.id = itr;
//                 char temp[1000];
//                 read(0, temp, sizeof(temp));
//                 bzero(msg.body, sizeof(msg.body));
//                 int i = 0;
//                 while (temp[i] != '\n' && temp[i] != '\0')
//                 {
//                     msg.body[i] = temp[i];
//                     i++;
//                 }
//                 msg.body[i] = '\0';

//                 writeBytes = write(sfd, &msg, sizeof(msg));
//             }
//             else
//             { // Reply Type: password...
//                 char temp[1000];
//                 strcpy(temp, getpass(msg.body));
//                 msg.id = itr;
//                 msg.type = 1;
//                 msg.action = 1;
//                 bzero(msg.body, sizeof(msg.body));
//                 strcpy(msg.body, temp);
//                 msg.body[strlen(temp)] == '\0';
//                 writeBytes = write(sfd, &msg, sizeof(msg));
//             }
//         }
//         else
//         {
//             exit_msg = "Invalid Message Structure sent by Server\nExiting...\n";
//             write(1, exit_msg, strlen(exit_msg));
//             return;
//         }
//         itr++;
//     } // end of infinite while loop...
// }
