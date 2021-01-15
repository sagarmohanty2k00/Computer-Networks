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
    char buffer1[MAXLINE], buffer2[MAXLINE], buffer[2048]; 
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
    printf("Enter messege1 : ");
    scanf("%s", buffer1);

    printf("Enter messege2 : ");
    scanf("%s", buffer2);

    sendto(sockfd, (const char *)buffer1, strlen(buffer1), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 

    printf("message1 sent.\n"); 

    sendto(sockfd, (const char *)buffer2, strlen(buffer2), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 

    printf("message1 sent.\n"); 
          
    n = recvfrom(sockfd, (char *)buffer, 2048,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
    buffer[n] = '\0'; 
    printf("Messege Recieved : %s\n", buffer); 
  
    close(sockfd); 
    return 0; 
} 
