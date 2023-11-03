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

    int getSocket() const {
        return _socket;
    }

    void setSocket(int socket) {
        _socket = socket;
    }

    std::string getIpAddress() const {
        return inet_ntoa(_sockaddr.sin_addr);
    }

    uint16_t getPort() const {
        return ntohs(_sockaddr.sin_port);
    }

    const sockaddr_in& getSockAddr() const {
        return _sockaddr;
    }

    int _socket;
    sockaddr_in _sockaddr;
    socklen_t _socklen;
};
