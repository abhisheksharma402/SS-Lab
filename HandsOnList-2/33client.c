#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<stdlib.h>

int main(){

        struct sockaddr_in server;

        int sd;

        char buf[1024];

        sd = socket(AF_UNIX, SOCK_STREAM, 0);
	int reuse = 1;
        if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
                perror("setsockopt(SO_REUSEADDR) failed");
                exit(1);
        }

        server.sin_family = AF_UNIX;

        server.sin_addr.s_addr = INADDR_ANY;


        server.sin_port = htons(6888);

        connect(sd, (void*)(&server), sizeof(server));

        write(sd, "Hi, from Client\n", 16);
	
	read(sd, buf, sizeof(buf));
	printf("Message from the server: %s\n",buf);
	
	shutdown(sd,2);

} 
