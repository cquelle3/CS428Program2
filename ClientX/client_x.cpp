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
    const char* message = "Client X: Alice";
    char buff[1024];
    
    int sockfd;
    struct sockaddr_in servaddr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 
    
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0){
        cout << "Couldn't connect to server..." << endl;
        exit(0);
    }
    
    write(sockfd, message, strlen(message));
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    cout << "Sent to Server (Client X): '" << message << "'" << endl;
    cout << "Received from Server (Client X): '" << buff << "'" << endl;    
    
    return 0;
}
