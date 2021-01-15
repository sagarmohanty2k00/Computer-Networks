// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 

int hamming(int a, int b){
	int n = 0;
	int binary_a[32], binary_b[32];
	for(int i=0; i<32; i++){
		binary_a[i] = binary_b[i] = 0;
	}
	int i = 0;
	while(a > 0){
		binary_a[i] = a%2;
		a = a/2;
		i++;
	}
	i = 0;
	while(b > 0){
		binary_b[i] = b%2;
		b = b/2;
		i++;
	}
	for(int i=0; i<32; i++){
		if(binary_a[i] != binary_b[i]){
			n++;
		}
	}
	return n;
}

int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int len, n, n1, n2; 

	len = sizeof(cliaddr); //len is value/resuslt 

	n = recvfrom(sockfd, &n1, sizeof(int), 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	n = recvfrom(sockfd, &n2, sizeof(int), 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	//buffer[n] = '\0'; 
	
	printf("Client : %d\n", n1); 
	int num = hamming(n1, n2);

	sendto(sockfd, &num, sizeof(int), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len); 
	printf("Hello message sent.\n"); 
	
	return 0; 
} 

