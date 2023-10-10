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

vector<int> Channel::getAllMember( void ) const {
    return this->member;
}

int     Channel::sendMessage(std::string message) const {

    int sendByte = send(, capListResponse, strlen(capListResponse), 0);
}
