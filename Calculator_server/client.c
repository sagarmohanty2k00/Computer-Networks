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
	int num1, num2, res;
	int op;
	printf("Enter the num1: ");
	scanf("%d", &num1);
	write(sockfd, &num1, sizeof(int));

	printf("Enter the num2: ");
	scanf("%d", &num2);
	write(sockfd, &num2, sizeof(int));

	printf("Enter the operation:\n 1. Add( + )\n 2. Subtract( - )\n 3. Multiplication( * )\n 4. Division( / )\n  ");
	scanf("%d", &op);
	write(sockfd, &op, sizeof(int));

	read(sockfd, &res, sizeof(int));
	printf("result = %d\n", res);


	return 0;
}

