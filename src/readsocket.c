#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 25565

struct ident{
	char		packet_id;
	char  		head;// = 7;
	char		name[64];// = "COBBLE\0";
	char		motd[64];// = "Welcome to COBBLE!\n";
	char		perm;// = 0;
} typedef ident;

int main(int argc, char const* argv[])
{
		int server_fd, new_socket, valread;
	    struct sockaddr_in address;
	    int opt = 1;
	    int addrlen = sizeof(address);
	    char buffer[1024] = { 0 };
	    char* hello = "Hello from server";
	    FILE *fp;
	    fp = fopen("log.dump", "w+");

	    // Creating socket file descriptor
	    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	        perror("socket failed");
	        exit(EXIT_FAILURE);
	    }

	    // Forcefully attaching socket to the port 8080
	    if (setsockopt(server_fd, SOL_SOCKET,
	                   SO_REUSEADDR | SO_REUSEPORT, &opt,
	                   sizeof(opt))) {
	        perror("setsockopt");
	        exit(EXIT_FAILURE);
	    }
	    address.sin_family = AF_INET;
	    address.sin_addr.s_addr = INADDR_ANY;
	    address.sin_port = htons(PORT);

	    // Forcefully attaching socket to the port 8080
	    if (bind(server_fd, (struct sockaddr*)&address,
	             sizeof(address))
	        < 0) {
	        perror("bind failed");
	        exit(EXIT_FAILURE);
	    }
	    if (listen(server_fd, 3) < 0) {
	        perror("listen");
	        exit(EXIT_FAILURE);
	    }
	    if ((new_socket
	         = accept(server_fd, (struct sockaddr*)&address,
	                  (socklen_t*)&addrlen))
	        < 0) {
	        perror("accept");
	        exit(EXIT_FAILURE);
	    }
	    //signal(SIGINT, shutup);
	    for(int i = 0; i < 1024; i++){
	    	valread = read(new_socket, buffer, 8);
	    	for(int j = 0; j < 8; j++){
	    		printf("%02X.", buffer[j]);
	    		fputc(buffer[j], fp);
	    		fflush(fp);
	    	}
	    	if(i == 0){
	    		printf("|%s\n", buffer+1);
	    	}else{
	    		printf("|%s\n", buffer);
		    	send(new_socket, &read, 10, 0);
	    	}
	    }
	    read(new_socket, buffer, 200);
		ident id = {1, 7, "COBBLE", "Welcome to COBBLE!", 0};
		send(new_socket, &id, 130, 0);
	    //send(new_socket, hello, strlen(hello), 0);
	    printf("Ident sent\n");
	    /*while(valread = read(new_socket, buffer, 8) > 0){
	    	for(int j = 0; j < 10; j++){
				printf("%02X.", buffer[j]);

			}
			printf("|%s\n", buffer);
	    }*/
	    fclose(fp);
	    // closing the connected socket
	    close(new_socket);
	    // closing the listening socket
	    shutdown(server_fd, SHUT_RDWR);
	    return 0;
}

void shutup(){
}
