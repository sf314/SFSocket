
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

class SFSocketClient {
public:
    // Initialization
    void init();
    
    // Main API
    int connectTo(std::string server_ip, int portNum);
    void send(std::string msg);
    std::string receive();
    
    // Configuration
    
private:
    int socket_fd; // Socket filedescriptor
    struct sockaddr_in server_addr; // Server address 
    int maxMsgSize; // For safety?
};
