#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char buffer[1024];

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error in socket creation");
        exit(1);
    }

    //int reuse = 1;


    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8800);  // Port number (you can change this)
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error in binding");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Error in listening");
        exit(1);
    }

    //int ret = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    //printf("setsockopt returned: %d\n",ret);
    //if(ret<0){
     //   perror("setsockopt failed: ");
       // return 0;
    //}

    printf("Server is listening...\n");

    // Accept a connection
    client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == -1) {
        perror("Error in accepting connection");
        exit(1);
    }

    printf("Connection established with client.\n");

    while (1) {
        // Receive data from client
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            perror("Error in receiving data");
            break;
        }
        buffer[bytes_received] = '\0';

        printf("Received: %s", buffer);

        // Send a response back to the client
        char response[] = "Message received!";
        send(client_socket, response, strlen(response), 0);
    }

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}

