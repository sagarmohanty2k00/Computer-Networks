
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
    int buffer1, buffer2, buffer; 
    //char *hello = "Hello from client"; 
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
      
    int n, len; 
    //bzero(buffer1, sizeof(int));
          
    n = recvfrom(sockfd, &buffer1, sizeof(int),  
                MSG_WAITALL, (struct sockaddr *) &servaddr, (socklen_t*)&len); 
    //buffer1[n] = '\0'; 
    printf("recieved : %d\n", buffer1); 

    //bzero(buffer2, 256);
          
    n = recvfrom(sockfd, &buffer2, sizeof(int),  
                MSG_WAITALL, (struct sockaddr *) &servaddr, (socklen_t*)&len); 
    //buffer2[n] = '\0'; 
    printf("recieved : %d\n", buffer2); 

    buffer = buffer1 + buffer2;
    n = 0;
    //while((buffer[n++] = getchar()) != '\n');
    sendto(sockfd, &buffer, sizeof(int), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    printf("ANS sent.\n"); 
  
    close(sockfd); 
    return 0; 
} 
