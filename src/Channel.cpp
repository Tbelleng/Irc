#include "server.hpp"

Channel::Channel(std::string name, std::string username, std::string pass, User& client)
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
    this->_usersFd.push_back(client.GetUserFd());
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
    this->_usersFd.push_back(client.GetUserFd());
    this->increaseCurrentUser();
    return ;
}

void    Channel::addInvited(std::string username)
{
    this->_invitedUsers.push_back(username);
    return ;
}

void    Channel::increaseCurrentUser(void)
{
    this->_currentUsers++;
    return ;
}

std::string    Channel::getUserList(void)
{
    std::string result;
    std::vector<std::string>::iterator it;
    for (it = this->_members.begin(); it != this->_members.end(); ++it)
    {
        result = result + "@" + (*it) + " ";
    }
    std::cout << "La USER LIST =" << result << std::endl;
    return (result);
}

void    Channel::joinBroadcast(User& sender)
{
    std::string msg = ":" + sender.getNickname() + "!~" + sender.getNickname() + "@localhost" + " JOIN " + this->getName() + "\r\n";
    std::vector<int>::iterator it;
    for (it = this->_usersFd.begin(); it != this->_usersFd.end(); ++it)
    {
        if ((*it) != sender.GetUserFd())
            send((*it), msg.c_str(), msg.length(), 0);
    }
    std::cout << "broadcasting to channel users" << std::endl;
    return ;
}

void    Channel::broadcasting(std::string msg, int sender_fd)
{
    std::vector<int>::iterator it;
    for (it = this->_usersFd.begin(); it != this->_usersFd.end(); it++)
    {
        if ((*it) != sender_fd)
            send((*it), msg.c_str(), msg.length(), 0);
    }
    return ;
}

bool    Channel::opOfChannel(User& sender)
{
    std::string _userName = sender.getNickname();
    std::vector<std::string>::iterator it;
    for (it = this->_opMembers.begin(); it != this->_opMembers.end(); it++)
    {
        if ((*it) == _userName)
            return true;
    }
    return false;
}


bool    Channel::userOfChannel(User& sender)
{
    std::string _userName = sender.getNickname();
    std::vector<std::string>::iterator it;
    for (it = this->_members.begin(); it != this->_members.end(); it++)
    {
        if ((*it) == _userName)
            return true;
    }
    return false;
}

bool    Channel::checkByName(std::string name_to_check)
{
    std::vector<std::string>::iterator it;
    for (it = this->_members.begin(); it != this->_members.end(); it++)
    {
        if ((*it) == name_to_check)
            return true;
    }
    return false;
}

void    Channel::removeUser(User& sender)
{
    std::string _userName = sender.getNickname();
    int _userfd = sender.GetUserFd();
    std::vector<std::string>::iterator it;
    for (it = this->_members.begin(); it != this->_members.end(); it++)
    {
        if ((*it) == _userName)
        {
            this->_members.erase(it);
            break;
        }
    }
    std::vector<std::string>::iterator itt;
    for (itt = this->_opMembers.begin(); itt != this->_opMembers.end(); itt++)
    {
        if ((*itt) == _userName)
        {
            this->_opMembers.erase(itt);
            break;
        }
    }
    std::vector<int>::iterator ittt;
    for (ittt = this->_usersFd.begin(); ittt != this->_usersFd.end(); ittt++)
    {
        if ((*ittt) == _userfd)
        {
            this->_usersFd.erase(ittt);
            break;
        }
    }
    std::cout << "User erased" << std::endl;
    return ;
}

void    Channel::setTopic(std::string new_topic)
{
    this->_topic = new_topic;
    return ;
}

void    Channel::modeO(std::string flag, std::string target, User& sender)
{
    bool sign = false;
    if (flag[0] == '+')
        sign = true;
    if (sign == true)
    {
        for(std::vector<std::string>::iterator it = this->_opMembers.begin(); it != this->_opMembers.end(); it++)
        {
            if (*it == target)
            {
                sender.sendMsg("441 " + target + " :User already Operator\r\n");
                return ;
            }
        }
        this->_opMembers.push_back(target);
        sender.sendMsg(":" + sender.getNickname() + "!~" + sender.getNickname() + "@localhost" + " MODE " + target + " +o " + (*us)->getNickName() + "\r\n");
        this->broadcasting("381 " + target + " :Is now an Operator in this channel\r\n", sender.GetUserFd());
        return ;
    }
    else
    {
        for(std::vector<std::string>::iterator it = this->_opMembers.begin(); it != this->_opMembers.end(); it++)
        {
            if (*it == sender.getNickname())
            {
                 it->sendMsg("ERROR: You can't remove yourself from operator status\r\n");
                return ;
            }
            if (*it == target)
            {
                this->_opMembers.remove(it);
                sender.sendMsg(":" + sender.getNickname() + "!~" + sender.getNickname() + "@localhost" + " MODE " + target + " -o " + this->getName() + "\r\n");
                return ;
            }
        }
    }
    std::cout << "fin de mode o" << std::endl;
    return ;
}

void    Channel::modeSwitch(std::string flag)
{
    (void)flag;
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

