#include <iostream>
#include <string.h>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fstream>
#include <ostream>
   
#define MAXLINE 1024
// Driver code
char* filename = new char[64];
char* line = new char[64];

bool license_check(char* license)
{
    
    std::ifstream file;
    file.open(filename, std::ios_base::in);
    if(file.is_open())
    {
        while(file.getline(line, 1024))
        {
            if((strcmp(line,license))==0)
            {
                return true;
            } 
            
        }   
        file.close();
    }
    else
        std::cout<<"failed to open file"<<std::endl;

    return false;
}

int main() {
    int sockfd;
    int p;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    const char* message="Reported as stolen";
    const char* message1="Not in the database";
     
   std::cout<<"----SERVER RUNNING----"<<std::endl;
   
   std::cout<<"Enter today's stolen cars DB name:" <<std::endl;
   std::cin>>filename;
       
   std::cout<<"enter server port number" <<std::endl;
   std::cin>>p;
   if (p <1024)
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
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(p);
       
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
       
    socklen_t len;
  int n;
   
    len = sizeof(cliaddr);  //len is value/result
   
    while (true)
    {
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                    &len);
        buffer[n] = '\0';
        printf("Client : %s\n", buffer);
        
        if(true == license_check(buffer))
        {
            sendto(sockfd, (const char *)message, strlen(message), 
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
            std::cout<<"Message sent to client"<<std::endl;
        }
        if((strcmp(buffer,"killsvc"))==0) 
        {
            return 0; //exit?
        }
        else
        {
            sendto(sockfd, (const char *)message1, strlen(message1), 
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len); 
            std::cout<<"Message sent to client"<<std::endl;
        }
        
    }
    
    return 0;
}