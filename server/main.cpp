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

using namespace std;

bool license_check(char* license)
{
    
    ifstream file;
    file.open(filename, ios_base::in);
    if(file.is_open())
    {
        while(file.getline(line, 1024))
        {
            if(strcmp(line,license)==0)
            {
                return true;
            } 
            
        }   
        file.close();
    }
    else
        cout<<"failed to open file"<<endl;

    return false;
}

int main() {
    int sockfd;
    int p;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    const char* message="Reported as stolen";
    const char* message1="Not in the database";
     
   cout<<"----SERVER RUNNING----"<<endl;
   
   cout<<"Enter today's stolen cars DB name:" <<endl;
   cin>>filename;
       
   cout<<"Enter server port number" <<endl;
   cin>>p;
   if (p <1024)
   {
        cout<<"The port number is not valid, please Enter again"<<endl;
       cin>>p;
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
            cout<<"Message sent to client"<<endl;
        }
        else if(strcmp(buffer,"killsvc")==0) 
        {
            break;
        }
        else
        {
            sendto(sockfd, (const char *)message1, strlen(message1), 
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len); 
            cout<<"Message sent to client"<<endl;
        }
        
    }
    
    return 0;
}