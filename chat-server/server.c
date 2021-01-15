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


void dropprocess(int sock){
	int n;
	char buffer[256];
	bzero(buffer, 256);

	n = read(sock, buffer, 256);
	if(n < 0){
		perror("ERROR RECIEVING THE MESSAGE......");
		exit(1);
	}

	printf("        %s\n", buffer);
	bzero(buffer, 256);

	scanf("%s", buffer);
	n = write(sock, buffer, 256);
	if(n < 0){
		perror("ERROR on writing the message.....");
		exit(1);
	}

}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n, pid;
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
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	// Set port number, using htons function to use proper byte order
	serv_addr.sin_port = htons(portno);

	/* Now Bind the host address using bind() call. */
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
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
	while(1){
		// Accept actual connection from the client
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*) &clilen);
	
		if(newsockfd < 0){
			perror("***ERROR on accept***\n");
			exit(1);
		}
	
		pid = fork();

		if(pid < 0){
			perror("ERROR on fork");
			exit(1);
		}
		if(pid == 0){
			/* This is the client process */
			close(sockfd);
			dropprocess(newsockfd);
			exit(0);
		}
		else{
			close(newsockfd);
		}

	
	}


	return 0;
}
