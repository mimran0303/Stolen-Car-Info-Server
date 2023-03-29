#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
   
#define MAXLINE 1024

   
// Driver code
int main() {
    int sockfd;
    int p;
    char buffer[MAXLINE];
    struct sockaddr_in     servaddr;
    char* hostname = new char[64];
    char* lisence = new char[64];

    std::cout<<"----CLIENT RUNNING----"<<std::endl;
   std::cout<<"enter hostname" <<std::endl; 
   std::cin>>hostname;
   if ((strcmp(hostname,"localhost"))==1)
   {
       std:: cout<<"The hostname is not correct, please enter again"<<std::endl;
       std::cin>>hostname;
   }
   
   std::cout<<"enter port number" <<std::endl;
   std::cin>>p;
   if ( p < 1024)
   {
       std:: cout<<"The port number is not valid, please enter again"<<std::endl;
       std::cin>>p;
   }
   
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
    
    
       
    // Filling server information
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(p);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int n;
    socklen_t len;
     
    while(true)
    {  
        std:: cout<<"enter lisence plate number"<<std::endl;
        std::cin>>lisence;
    
        sendto(sockfd, (char*)lisence, strlen(lisence),
         MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                sizeof(servaddr));
        std::cout<<"lisence sent."<<std::endl;
               
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    &len);
        buffer[n] = '\0';
        std::cout<<"Server :"<<buffer<<std::endl;
    }
   
    close(sockfd);
    return 0;
}