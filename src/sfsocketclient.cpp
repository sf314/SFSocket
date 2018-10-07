
#include <sfsocketclient.h>

void SFSocketClient::init() {
    maxMsgSize = 256;
}

int SFSocketClient::connectTo(std::string server_ip, int portNum) {
    // Retrieve free socket, set self.filedescriptor
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Clear and configure self.server_addr
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr);
    
    // Make the connection
    connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    return 0;
}

void SFSocketClient::send(std::string msg) {
    if (strlen(msg.c_str()) > maxMsgSize) {
        fprintf(stderr, "SFSocket::send: Warning! Message length exceeds maximum!\n");
        return;
    }
    
    write(socket_fd, msg.c_str(), maxMsgSize);
}

std::string SFSocketClient::receive() {
    char line[maxMsgSize];
    recv(socket_fd, line, maxMsgSize, 0);
    
    return std::string(line);
}