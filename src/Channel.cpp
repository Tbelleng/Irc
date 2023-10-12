#include "Channel.hpp"

Channel::Channel( void ) : name("Default") {
    if (DEBUG)
        std::cout < < "# Default Channel constructor call #" << std::endl;
}

Channel::Channel(std::string name) : name(name) {
    if (DEBUG)
        std::cout < < "# String Channel constructor call #" << std::endl;
}

Channel::~Channel( void ) {
    if (DEBUG)
        std::cout << "| Default Channel destructor |"
}

std::string Channel::getName( void ) const {
    return this->name;
}

void    Channel::addMember(int newMember) {
    this->member.push_back(newMember);
    return ;
}

void    Channel::suppMember(int suppMember) {
    this->member.erase(
        std::remove(this->member.begin(), this->member.end(), suppMember),
        this->member.end()
    );
    return ;
}

vector<int> Channel::getAllMember( void ) const {
    return this->member;
}

int     Channel::sendMessage(std::string message, const int epoll_fd) const {

    for (int clientSock : clients) {
        struct epoll_event event;
        event.events = EPOLLOUT;
        event.data.fd = clientSock;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientSock, &event) == -1) {
            //check to protect error
            return 0;
        }
    }

    struct epoll_event events[MAX_EVENTS];
    int numReady = epoll_wait(epoll_fd, events, MAX_EVENTS, TIMEOUT);
    if (numReady == -1) {
        //check to protect error
        return 0;
    }

    for (int i = 0; i < numReady; i++) {
        int readySock = events[i].data.fd;
        if (events[i].events & EPOLLOUT) {
            ssize_t bytesSent = send(readySock, message, strlen(message), 0);
            if (bytesSent == -1) {
                //check to protect error
                return 0;
            }
        }
    }
}
