#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[1024];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error in socket creation");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8800);  // Port number (should match the server's port)
    server_addr.sin_addr.s_addr = inet_addr("192.168.29.36");  // Replace with the server's IP address

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error in connecting to the server");
        exit(1);
    }

    printf("Connected to the server.\n");

    while (1) {
        // Send a message to the server
        printf("Enter a message to send: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        // Receive the server's response
        char response[1024];
        ssize_t bytes_received = recv(client_socket, response, sizeof(response), 0);
        if (bytes_received <= 0) {
            perror("Error in receiving data");
            break;
        }
        response[bytes_received] = '\0';

        printf("Server Response: %s", response);
    }

    // Close the socket
    close(client_socket);

    return 0;
}

