#include "server.hpp"

Channel::Channel(std::string name, std::string topic, std::string username)
{
    this->_name = name;
    this->_topic = topic;
    this->_opMembers.push_back(username);
    return ;
}

Channel::~Channel(void)
{
    std::cout << "Channel Destructor Called" << std::endl;
    return ;
}

std::string vectorToString(const std::vector<std::string>& buffer) 
{
    std::string result;
    for (size_t i = 2; i < buffer.size(); ++i)
    {
        result += buffer[i];
    }
    //result += "\r\n";
    return result;
}

