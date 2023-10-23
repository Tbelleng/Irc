#include "server.hpp"

Channel::Channel(int opMember) : _name("Default"), _topic() {
    this->_opMembers.push_back(opMember);
    if (DEBUG_CHANNEL)
        std::cout << "# Default Channel constructor call #" << std::endl;
}

Channel::Channel(std::string name, int opMember) : _name(name), _topic() {
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

std::vector<int>    Channel::getAllOpMember(void) const {
    return this->_opMembers;
}

std::string Channel::getTopic(void) const {
    // Channel::sendMessage(this->_topic.getTopic().c_str());
    return (this->_topic.getTopic());
}

void    Channel::setGrade(int member, int grade) {
    if (*find(this->_opMembers.begin(), this->_opMembers.end(), member) == member) {
        this->_topic.setGrade(grade);
    } else {
        _send("Not an op!", member);
    }
    return ;
}

bool    Channel::setTopic(int member, std::string topic) {
    std::cout << this->_topic.getGrade() << std::endl;
    if (this->_topic.getGrade() == 0){
        if (*find(this->_opMembers.begin(), this->_opMembers.end(), member) == member) {
            this->_topic.setTopic(topic);
        } else {
            return false;
        }
    } else {
        this->_topic.setTopic(topic);
    }
    return true;
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
        _send("Not an op!", oldOpMember);
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
        _send("Not an op!", opMember);
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
        _send("Not an op!", opMember);
    }
    return ;
}

void    Channel::memberLeave(int leaver) {
    if (*find(this->_members.begin(), this->_members.end(), leaver) == leaver) {
        this->_members.erase(
            std::remove(this->_members.begin(), this->_members.end(), leaver),
            this->_members.end()
        );
    } else {
        _send("Not an channel member!", leaver);
    }
    return ;
}

std::vector<int> Channel::getAllMember( void ) const {
    return this->_members;
}

void     Channel::sendMessage(const char* message) const {

    for(std::vector<int>::const_iterator it = this->_members.begin(); it != this->_members.end(); ++it) {
        _send(message, *it); 
    }
    return ;
}

bool Channel::isInChannel(int user)
{
    // std::string compare = sender.GetUserName();
    for (std::vector<int>::iterator it = this->_members.begin(); it != this->_members.end(); ++it) 
    {
         if (*it == user) {
            return true;
        }
    }
    return false;
}

// #include "server.hpp"

// Channel::Channel(User& sender, std::string channel_name)
// {
//     this->_name = channel_name;
//     this->_members.push_back(sender.GetUserName());
//     this->_opMembers.push_back(sender.GetUserName());
// }

// Channel::~Channel(void)
// {

// }

// std::string Channel::getChannelName(void)
// {
//     return (this->_name);
// }

// bool Channel::isInChannel(User &sender)
// {
//     std::string compare = sender.GetUserName();
//     for (std::vector<std::string>::iterator it = this->_members.begin(); it != this->_members.end(); ++it) 
//     {
//          if (*it == compare) {
//             return true;
//         }
//     }
//     return false;
// }

// void Channel::sendTo(User& sender, const std::string message)
// {
//     send(sender.GetUserFd(), message.c_str(), message.size(), MSG_DONTWAIT);
//     std::cout << "{info} MESSAGE TO " << sender.GetUserName() << " >" << message << "^" << std::endl;
// }

// void Channel::sendToChannel(User& sender, std::vector<std::string>buffers)
// {
//     std::string message = vectorToString(buffers);
//     this->sendTo(sender, JOIN(sender.GetUserName(), "user", "localhost", "new_chat"));
//     //send(sender.GetUserFd(), message.c_str(), message.size(), MSG_DONTWAIT);
// }


// std::string vectorToString(const std::vector<std::string>& buffer) 
// {
//     std::string result;
//     for (size_t i = 0; i < buffer.size(); ++i)
//     {
//         result += buffer[i];
//     }
//     //result += "\r\n";
//     return result;
// }

