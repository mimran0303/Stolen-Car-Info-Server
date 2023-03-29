#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
   
#define MAXLINE 1024
using namespace std;

// Driver code
int main() {
    int sockfd;
    int p;
    char buffer[MAXLINE];
    struct sockaddr_in     servaddr;
    char* hostname = new char[64];
    char* lisence = new char[64];

    cout<<"----CLIENT RUNNING----"<<endl;
   cout<<"Enter server name or ip address" <<endl; 
   cin>>hostname;
   //if (strcmp(hostname,"localhost")!=0)
   //{
        //cout<<"The hostname is not correct, please Enter again"<<endl;
      // cin>>hostname;
   //}
   
   cout<<"Enter port number" <<endl;
   cin>>p;
   if ( p < 1024)
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
    
    
       
    // Filling server information
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(p);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int n;
    socklen_t len;
     
    while(true)
    {  
         cout<<"Enter lisence plate number"<<endl;
        cin>>lisence;
    
        sendto(sockfd, (char*)lisence, strlen(lisence),
         MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                sizeof(servaddr));
        cout<<"lisence sent."<<endl;
               
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    &len);
        buffer[n] = '\0';
        cout<<"Server :"<<buffer<<endl;
    }
   
    close(sockfd);
    return 0;
}