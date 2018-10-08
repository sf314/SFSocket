
#include <sfsocketserver.h>

int SFSocketServer::init(int port) {
    backlog = 128;
    maxMsgLen = 256;
    
    // Create new socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        fprintf(stderr, "SFSocketServer::init: Could not reserve socket fd!\n");
        return -1;
    }
    
    // Configure address
    memset(&server_addr, 0, sizeof(server_addr)); // or bzero()
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    
    // Bind the socket 
    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        fprintf(stderr, "SFSocketServer::init: Could not bind socket!\n");
        return -1;
    }
    
    if (listen(socket_fd, backlog) == -1) {
        fprintf(stderr, "SFSocketServer::init: Could not listen on socket!\n");
        return -1;
    }
    
    return 0;
}

int SFSocketServer::acceptConnection() {
    client_addr_len = sizeof(client_addr);
    connection_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    
    return connection_fd; 
}

int SFSocketServer::send(std::string msg) {
    return write(connection_fd, msg.c_str(), maxMsgLen);
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

int SFSocketServer::closeConnection() {
    return close(connection_fd);
}