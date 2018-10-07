
#include <sfsocketserver.h>

void SFSocketServer::init(int port) {
    backlog = 128;
    maxMsgLen = 256;
    
    // Create new socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Configure address
    memset(&server_addr, 0, sizeof(server_addr)); // or bzero()
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    
    // Bind the socket 
    bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(socket_fd, backlog);
    
}

int SFSocketServer::acceptConnection() {
    client_addr_len = sizeof(client_addr);
    connection_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    
    
    return connection_fd; 
}

void SFSocketServer::send(std::string msg) {
    write(connection_fd, msg.c_str(), maxMsgLen);
}

std::string SFSocketServer::receive() {
    char msg[maxMsgLen];
    if (recv(connection_fd, msg, maxMsgLen, 0) <= 0) {
        fprintf(stderr, "SFSocketServer::receive: Connection %d closed when trying to receive!\n", connection_fd);
        closeConnection();
        return "";
    }
    return std::string(msg);
}

void SFSocketServer::closeConnection() {
    close(connection_fd);
}