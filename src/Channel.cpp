#include "server.hpp"

Channel::Channel(std::string name, std::string username, std::string pass)
{
    this->_name = name;
    this->_topic = "";
    if (pass != "")
    {
        this->_password = pass;
        this->_needPass = true;
    }
    else
    {
        this->_password = "";
        this->_needPass = false;
    }
    this->_opMembers.push_back(username);
    this->_members.push_back(username);
    this->_onlyInvite = false;
    this->_currentUsers++;
    this->_maxUsers = 10;
    this->_currentUsers = 1;
    return ;
}

Channel::~Channel(void)
{
    std::cout << "Channel Destructor Called" << std::endl;
    return ;
}

std::string    Channel::getTopic(void)
{
    return (this->_topic);
}

bool    Channel::needPass(void)
{
    return (this->_needPass);
}

std::string    Channel::getPassword(void)
{
    return (this->_password);
}

unsigned int    Channel::getMaxUsers(void)
{
    return (this->_maxUsers);
}

unsigned int    Channel::getCurrentUsers(void)
{
    return (this->_currentUsers);
}

void    Channel::addMember(User& client)
{
    this->_members.push_back(client.getNickname());
    this->increaseCurrentUser();
    return ;
}

void    Channel::increaseCurrentUser(void)
{
    this->_currentUsers++;
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

