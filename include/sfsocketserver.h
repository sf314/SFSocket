
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <iostream>
#include <string>
#include <cstring>

class SFSocketServer {
public:
    // Initialization
    void init(int port);
    
    // Main API
    int acceptConnection();
    void send(std::string msg);
    std::string receive();
    void closeConnection();
    
private:
    int socket_fd; // Socket filedescriptor
    struct sockaddr_in server_addr, client_addr;
    unsigned int client_addr_len;
    unsigned short server_port;
    int backlog;
    int maxMsgLen;
    int connection_fd;
};