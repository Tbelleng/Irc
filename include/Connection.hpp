#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>


class NewConnection {
public:
    NewConnection() : _socket(-1) {
        std::memset(&_sockaddr, 0, sizeof(_sockaddr));
        _socklen = sizeof(_sockaddr);
    }

    // Get the user's socket descriptor
    int getSocket() const {
        return _socket;
    }

    // Set the user's socket descriptor
    void setSocket(int socket) {
        _socket = socket;
    }

    // Get the user's IP address as a string
    std::string getIpAddress() const {
        return inet_ntoa(_sockaddr.sin_addr);
    }

    // Get the user's port
    uint16_t getPort() const {
        return ntohs(_sockaddr.sin_port);
    }

    // Get the sockaddr structure for the user
    const sockaddr_in& getSockAddr() const {
        return _sockaddr;
    }

    int _socket;
    sockaddr_in _sockaddr;
    socklen_t _socklen;
};
