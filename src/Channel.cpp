#include "Channel.hpp"

Channel::Channel(int opMember, int epfd, struct epoll_event& ev) : name("Default"), epfd(epfd), ev(ev) {
    this->opMember.push_back(opMember);
    if (DEBUG_CHANNEL)
        std::cout << "# Default Channel constructor call #" << std::endl;
}

Channel::Channel(std::string name, int opMember, int epfd, struct epoll_event& ev) : name(name), epfd(epfd), ev(ev) {
    this->opMember.push_back(opMember);
    if (DEBUG_CHANNEL)
        std::cout << "# String Channel constructor call #" << std::endl;
}

Channel::~Channel( void ) {
    if (DEBUG_CHANNEL)
        std::cout << "| Default Channel destructor |";
}

std::string Channel::getName( void ) const {
    return this->name;
}



void    Channel::setMember(int newMember) {
    this->member.push_back(newMember);
    return ;
}

void    Channel::setOpMember(int oldOpMember, int newOpMember) {
    if (*find(this->opMember.begin(), this->opMember.end(), oldOpMember) == oldOpMember) {
        this->opMember.push_back(newOpMember);
    } else {
        _send("Not an op!", oldOpMember, this->epfd, this->ev);
    }
    return ;
}



void    Channel::suppMember(int suppMember) {
    this->member.erase(
        std::remove(this->member.begin(), this->member.end(), suppMember),
        this->member.end()
    );
    return ;
}

void    Channel::suppOpMember(int oldOpMember, int suppOpMember) {
    if (*find(this->opMember.begin(), this->opMember.end(), oldOpMember) == oldOpMember) {
        this->opMember.erase(
            std::remove(this->opMember.begin(), this->opMember.end(), suppOpMember),
            this->opMember.end()
        );
    } else {
        _send("Not an op!", oldOpMember, this->epfd, this->ev);
    }
    return ;
}

std::vector<int> Channel::getAllMember( void ) const {
    return this->member;
}

int     Channel::sendMessage(const char* message) const {

  for(std::vector<int>::const_iterator it = member.begin(); it != member.end(); ++it) {
       _send(message, *it, this->epfd, this->ev); 
    }
    return 1;
}
