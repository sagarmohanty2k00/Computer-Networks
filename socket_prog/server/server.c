// C program to make a server using server api
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	portno = 5001;

	/* First call to socket() function */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd<0){
		perror("***ERROR opening socket***\n");
		exit(1);
	}

	// ---Configuring settings of the server address structure---
	// Initializing socket structure elements tozero
	bzero((char*) &serv_addr, sizeof(serv_addr));
	// Set Adderss family internet
	serv_addr.sin_family = AF_INET;
	// Set IP adderss to localhost
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// Set port number, using htons function to use proper byte order
	serv_addr.sin_port = htons(portno);

	/* Now Bind the host address using bind() call. */
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))){
		perror("*** ERROR on binding ***\n");
		exit(1);
	}

	/* Now Start listening for the clients, 
	 *
	 * here process will go on sleep mode and
	 *
	 * will wait for ths incomming connection......*/
	listen(sockfd, 5);
	printf("Server Listening...");
	clilen = sizeof(cli_addr);
	// Accept actual connection from the client
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*) &clilen);

	if(n < 0){
		perror("***ERROR on accept***\n");
		exit(1);
	}

	/* If connection is established start communicating */
	bzero(buffer, 256);
	n = read( newsockfd, buffer, 255);

	if(n < 0){
		perror("***ERROR on reading from socket***\n");
		exit(1);
	}

	printf("Here is the message: %s\n",buffer);

	/* Writting some responce to the client */
	n = write(newsockfd, "Server got your message", 40);
	if(n < 0){
		perror("***ERROR on writing to socket***\n");
		exit(1);
	}


	return 0;
}
