
#include <sfsocketclient.h>

int SFSocketClient::init() {
    maxMsgSize = 256;
    
    return 0;
}

int SFSocketClient::connectTo(std::string server_ip, int portNum) {
    // Retrieve free socket, set self.filedescriptor
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (socket_fd == -1) {
        fprintf(stderr, "SFSocketClient::connectTo: Could not get socket!\n");
        return -1;
    }
    
    // Clear and configure self.server_addr
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr);
    
    // Make the connection
    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        fprintf(stderr, "SFSocketClient::connectTo: Could not connect to server!\n");
        return -1;
    }
    
    return 0;
}

int SFSocketClient::send(std::string msg) {
    if (strlen(msg.c_str()) > maxMsgSize) {
        fprintf(stderr, "SFSocketClient::send: Warning! Message length exceeds maximum!\n");
        return -1;
    }
    
    return write(socket_fd, msg.c_str(), maxMsgSize);
}

std::string SFSocketClient::receive() {
    char line[maxMsgSize];
    recv(socket_fd, line, maxMsgSize, 0);
    
    return std::string(line);
}