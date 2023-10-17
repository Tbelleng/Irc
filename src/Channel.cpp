#include "Channel.hpp"

Channel::Channel(int opMember, int epfd, struct epoll_event& ev) : _name("Default"), _epfd(epfd), _ev(ev), _topic() {
    this->_opMembers.push_back(opMember);
    if (DEBUG_CHANNEL)
        std::cout << "# Default Channel constructor call #" << std::endl;
}

Channel::Channel(std::string name, int opMember, int epfd, struct epoll_event& ev) : _name(name), _epfd(epfd), _ev(ev), _topic() {
    this->_opMembers.push_back(opMember);
    if (DEBUG_CHANNEL)
        std::cout << "# String Channel constructor call #" << std::endl;
}

Channel::~Channel( void ) {
    if (DEBUG_CHANNEL)
        std::cout << "| Default Channel destructor |";
}

std::string Channel::getName( void ) const {
    return this->_name;
}

std::string Channel::getTopic(void) const {
    Channel::sendMessage(this->_topic.getTopic().c_str());
    return (this->_topic.getTopic());
}

void    Channel::setGrade(int member, int grade) {
    if (*find(this->_opMembers.begin(), this->_opMembers.end(), member) == member) {
        this->_topic.setGrade(grade);
    } else {
        _send("Not an op!", member, this->_epfd, this->_ev);
    }
    return ;
}

void    Channel::setTopic(int member, std::string topic) {
    std::cout << this->_topic.getGrade() << std::endl;
    if (this->_topic.getGrade() == 0){
        if (*find(this->_opMembers.begin(), this->_opMembers.end(), member) == member) {
            this->_topic.setTopic(topic);
        } else {
            _send("Not an op!", member, this->_epfd, this->_ev);
        }
    } else {
        this->_topic.setTopic(topic);
    }
    return ;
}

void    Channel::setMember(int newMember) {
    this->_members.push_back(newMember);
    return ;
}

void    Channel::setOpMember(int oldOpMember, int newOpMember) {
    if (oldOpMember == newOpMember)
        return ;
    if (*find(this->_opMembers.begin(), this->_opMembers.end(), oldOpMember) == oldOpMember) {
        this->_opMembers.push_back(newOpMember);
    } else {
        _send("Not an op!", oldOpMember, this->_epfd, this->_ev);
    }
    return ;
}



void    Channel::suppMember(int opMember, int suppMember) {
    if (opMember == suppMember)
        return ;
    if (*find(this->_opMembers.begin(), this->_opMembers.end(), opMember) == opMember) {
        this->_members.erase(
            std::remove(this->_members.begin(), this->_members.end(), suppMember),
            this->_members.end()
        );
    } else {
        _send("Not an op!", opMember, this->_epfd, this->_ev);
    }
    return ;
}

void    Channel::suppOpMember(int opMember, int suppOpMember) {
    if (opMember == suppOpMember)
        return ;
    if (*find(this->_opMembers.begin(), this->_opMembers.end(), opMember) == opMember) {
        this->_opMembers.erase(
            std::remove(this->_opMembers.begin(), this->_opMembers.end(), suppOpMember),
            this->_opMembers.end()
        );
    } else {
        _send("Not an op!", opMember, this->_epfd, this->_ev);
    }
    return ;
}

std::vector<int> Channel::getAllMember( void ) const {
    return this->_members;
}

void     Channel::sendMessage(const char* message) const {

    for(std::vector<int>::const_iterator it = this->_members.begin(); it != this->_members.end(); ++it) {
        _send(message, *it, this->_epfd, this->_ev); 
    }
    return ;
}
