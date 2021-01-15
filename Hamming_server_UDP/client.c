
// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8080 
#define MAXLINE 1024 
  
// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from client"; 
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n1, n2, len, num, n; 
    printf("Number1: ");
    scanf("%d", &n1);
    printf("Number2: ");
    scanf("%d", &n2);
      
    sendto(sockfd, &n1, sizeof(int), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    sendto(sockfd, &n2, sizeof(int), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    printf("message sent.\n"); 
          
    n = recvfrom(sockfd, &num, sizeof(int),  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
    //buffer[n] = '\0'; 
    printf("Server : %d\n", num); 
  
    close(sockfd); 
    return 0; 
} 

