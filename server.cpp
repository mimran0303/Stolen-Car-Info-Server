#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 1024

using namespace std;

char* filename = new char[128];
char* line = new char[128];

bool license_check(char* license)
{
    ifstream file;
    file.open(filename, ios_base::in);
    if (file.is_open()) {
        while (file.getline(line, 1024)) {
            if (strcasecmp(line, license) == 0) {
                return true;
            }
        }
        file.close();
    } else
        cout << "Failed to open file" << endl;

    return false;
}

int main()
{
    int sockfd;
    int port;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    cout << "Server" << endl;
    cout << "Enter today's stolen cars DB name:" << endl;
    cin >> filename;

    cout << "Enter server port number" << endl;
    cin >> port;
    while (port < 1024) {
        cout << "The port number is not valid, please enter a port number >= 1024"
             << endl;
        cin >> port;
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len = sizeof(cliaddr);

    cout << "SERVER RUNNING ....." << endl;
    while (true) {
        int n = recvfrom(sockfd, (char*)buffer, MAXLINE, MSG_WAITALL,
            (struct sockaddr*)&cliaddr, &len);
        buffer[n] = '\0';
        cout << "Recieved from client " <<"[" <<buffer <<"]" <<endl;

        if (license_check(buffer) == true) {
            const char* message = "Reported as stolen";
            sendto(sockfd, (const char*)message, strlen(message), MSG_CONFIRM,
                (const struct sockaddr*)&cliaddr, len);
            cout << "Sent to client" << endl;
        } else {
            const char* message = "Not in the database";
            sendto(sockfd, (const char*)message, strlen(message), MSG_CONFIRM,
                (const struct sockaddr*)&cliaddr, len);
            cout << "Sent to client" << endl;
        }

        if (strcasecmp(buffer, "killsvc") == 0) {
            cout << "Server has recieved kill message" << endl;
            break;
        }
    }
    return 0;
}