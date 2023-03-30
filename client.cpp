#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 1024
using namespace std;

int main()
{
    int sockfd;
    int port;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    char* hostname = new char[64];
    char* license = new char[64];

    cout << "Client" << endl;
    cout << "Enter server name or ip address or localhost" << endl;
    cin >> hostname;
    if(strcasecmp("localhost",hostname)==0)
    {
        strcpy(hostname,"127.0.0.1");
    }
    cout << "Enter port number" << endl;
    cin >> port;
    while (port < 1024) {
        cout << "The port number is not valid, please enter port number >= 1024" << endl;
        cin >> port;
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(hostname);
    
    socklen_t len;

    cout << "CLIENT RUNNING ....." << endl;
    while (true) {
        cout << endl;
        cout << "Enter license plate number" << endl;
        cin >> license;
            
        sendto(sockfd, (char*)license, strlen(license),
            MSG_CONFIRM, (const struct sockaddr*)&servaddr,
            sizeof(servaddr));
            
        if(strcasecmp(license,"killsvc")==0)
            break;
            
        cout << "license sent." << endl;
        
        int n = recvfrom(sockfd, (char*)buffer, MAXLINE,
            MSG_WAITALL, (struct sockaddr*)&servaddr,
            &len);
        buffer[n] = '\0';
        cout << "Recieved from server " <<"[" <<buffer <<"]" <<endl;
    }

    close(sockfd);
    return 0;
}