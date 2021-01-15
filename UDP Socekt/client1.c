
// Server side implementation of UDP client-server model 
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
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int len, n; 
  
    len = sizeof(cliaddr);  //len is value/resuslt 
  
    //bzero(buffer1, sizeof(int));
    printf("NUM1 : ");
    //scanf("%s", buffer);
    n = 0;
    //while((buffer1[n++] = getchar()) != '\n');
    scanf("%d", &buffer1);
    sendto(sockfd, &buffer1, sizeof(int),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
    printf("NUM sent.\n");  
    //bzero(buffer2, sizeof(int));
    printf("NUM2 : ");
    //scanf("%s", buffer);
    n = 0;
    //while((buffer2[n++] = getchar()) != '\n');
    scanf("%d", &buffer2);
    sendto(sockfd, &buffer2, sizeof(int),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
    printf("NUM sent.\n");  

    n = recvfrom(sockfd, &buffer, sizeof(int),  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, (socklen_t*)&len); 
    //buffer[n] = '\0'; 
    printf("Answer : %d\n", buffer);
      
    return 0; 
} 
