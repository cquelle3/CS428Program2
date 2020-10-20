#include <iostream>
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12001

using namespace std;

int main(){

    char buff[1024];
    
    int sockfd, connfd1, connfd2;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int enable = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0){
        cout << "setsockopt error..." << endl;
        exit(0);
    }
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(enable)) < 0){
        cout << "setsockopt error..." << endl;
        exit(0);
    }
    
    servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
    
    if((::bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0){
        cout << "Socket bind failed..." << endl;
    }
    
    if((listen(sockfd, 5)) != 0){
        cout << "Listen failed..." << endl;
        exit(0);
    }
    
    len = sizeof(cliaddr);
    
    connfd1 = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if(connfd1 < 0){
        cout << "Server could not accept connection..." << endl;
    }
    
    connfd2 = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if(connfd2 < 0){
        cout << "Server could not accept connection..." << endl;
    }
    
    bzero(buff, sizeof(buff));
    read(connfd1, buff, sizeof(buff));
    cout << "From Client 1: '" << buff << "'" << endl;
    string msg1 = buff;
    
    bzero(buff, sizeof(buff));
    read(connfd2, buff, sizeof(buff));
    cout << "From Client 2: '" << buff << "'" << endl;
    string msg2 = buff;
    
    string str_message = msg1 + " received before " + msg2;
    char message[1024];
    strcpy(message, str_message.c_str());
    
    write(connfd1, message, strlen(message));
    write(connfd2, message, strlen(message));
    
    cout << "Server Sending: '" << message << "'" << endl;
    
    //read(connfd1, buff, sizeof(buff));
    //cout << "From Client: " << buff << endl;
    //write(connfd1, message, strlen(message));
    //cout << "Sending: " << message << endl;
    
    //read(connfd2, buff, sizeof(buff));
    //cout << "From Client: " << buff << endl;
    //write(connfd2, message, strlen(message));
    //cout << "Sending: " << message << endl;
    
    cout << "Sent acknowledgment to both X and Y" << endl;
    
    return 0;
}