// C program to create a network client
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(int args, char* argv[]){
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	portno = 5001;

	// Create a socket point
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("***ERROR on opening socket***\n");
		exit(1);
	}

	// ---Configuring settings of the server address struct---
	// Initialize socket structure elements to zero
	bzero((char *) &serv_addr, sizeof(serv_addr));
	// Address family = Internet
	serv_addr.sin_family = AF_INET;
	// Set port number, using htons function to use proper byte order 
	serv_addr.sin_port = htons(portno);
	// Set IP address to localhost
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Now try to connect to the server
	if(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("***ERROR on connectin***\n");
		exit(1);
	}
	// Now ask for message from the user, this message will be read by the server 
	

	while(1){
		
	}


	return 0;
}

