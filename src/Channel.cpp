#include "server.hpp"

Channel::Channel(User& sender, std::string channel_name)
{
    this->_name = channel_name;
    this->_members.push_back(sender.GetUserName());
    this->_opMembers.push_back(sender.GetUserName());
}

Channel::~Channel(void)
{

}

std::string Channel::getChannelName(void)
{
    return (this->_name);
}

bool Channel::isInChannel(User &sender)
{
    std::string compare = sender.GetUserName();
    for (std::vector<std::string>::iterator it = this->_members.begin(); it != this->_members.end(); ++it) 
    {
         if (*it == compare) {
            return true;
        }
    }
    return false;
}

void Channel::sendTo(User& sender, const std::string message)
{
    send(sender.GetUserFd(), message.c_str(), message.size(), MSG_DONTWAIT);
    std::cout << "{info} MESSAGE TO " << sender.GetUserName() << " >" << message << "^" << std::endl;
}

void Channel::sendToChannel(User& sender, std::vector<std::string>buffers)
{
    std::string message = vectorToString(buffers);
    this->sendTo(sender, JOIN(sender.GetUserName(), "user", "localhost", "new_chat"));
    //send(sender.GetUserFd(), message.c_str(), message.size(), MSG_DONTWAIT);
}


std::string vectorToString(const std::vector<std::string>& buffer) 
{
    std::string result;
    for (size_t i = 0; i < buffer.size(); ++i)
    {
        result += buffer[i];
    }
    //result += "\r\n";
    return result;
}
