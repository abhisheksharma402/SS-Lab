#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<stdlib.h>

int main(){
	
	struct sockaddr_in server, client;

	int sd,newsd;

	char buf[1024];

	sd = socket(AF_UNIX, SOCK_STREAM, 0);
	
	int reuse = 1;
    	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        	perror("setsockopt(SO_REUSEADDR) failed");
        	exit(1);
    	}

	printf("server sd: %d\n",sd);
	server.sin_family = AF_UNIX;

	server.sin_addr.s_addr = INADDR_ANY;

	server.sin_port = htons(6888);

	int bindv = bind(sd, (void*)(&server), sizeof(server));
	printf("bind returned: %d\n",bindv);
	if(bindv<0){
		perror("Error:");
		return 0;
	}

	listen(sd,5);

	int sz = sizeof(client);

	newsd = accept(sd, (void*)(&client), &sz);
	
	read(newsd, buf, sizeof(buf));

	printf("Message from Client: %s\n",buf);
	write(newsd, "Hi, from server\n", 16);
	
	shutdown(sd,2);
	shutdown(newsd,2);
}
