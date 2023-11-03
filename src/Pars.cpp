#include "Pars.hpp"

Command parseCommand(const std::string& cmd) {
    //std::cout << "On Va faire la commande" << cmd << std::endl;
    if (cmd == "MODE") {
        return MODE;
    } else if (cmd == "KICK") {
        return KICK;
    } else if (cmd == "PART") {
        return PART;
    } else if (cmd == "JOIN") {
        return JOIN;
    } else if (cmd == "PASS") {
        return PASS;
    } else if (cmd == "TOPIC") {
        return TOPIC;
    } else if (cmd == "USER") {
        return USER;
    } else if (cmd == "QUIT") {
        return QUIT;
    } else if (cmd == "NICK") {
        return NICK;
    } else if (cmd == "PRIVMSG") {
        return PRIVMSG;
    }
    return UNKNOWN;
}

//***********************************ALL FUNCTIONS*********************

void    nick(std::vector<std::string> buffers, User& sender, std::map<int, User*>& members)
{
    std::cout << "TAILLE = " << buffers.size() << std::endl;
    if (buffers.size() < 2) {
        sender.sendMsg(": 431 " + sender.getNickname() + " :No nickname given\r\n");
        std::cout << "not enough arg" << std::endl;
        return;
    }
    
    std::string new_nick = buffers[1];
    std::cout << "on a  = " << buffers[0] << std::endl;
    std::cout << "NICK =" << new_nick << std::endl;
    if (new_nick.find_first_of("#$:") != std::string::npos || isdigit(new_nick[0]) != 0) 
    {
        sender.sendMsg(": 432 " + sender.getNickname() + " :Invalid nickname\r\n");
        return;
    }
    for (std::map<int, User*>::const_iterator it = members.begin(); it != members.end(); ++it)
    {
        if (it->second && it->second->getNickname() == new_nick && it->second->GetUserFd() != sender.GetUserFd())
        {
            new_nick = new_nick + "_";
        }
    }
    sender.ChangeNickname(new_nick);
    sender.sendMsg(":" + sender.getNickname() + " NICK " + new_nick + "\r\n");
    std::cout << "New nickname = " << sender.getNickname() << std::endl;
    
    return ;
}


void    join(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList)
{
        if (buffers.size() < 2) 
        {
            sender.sendMsg(":" + sender.getNickname() + " 461 :Not Enough Parameters\r\n");
            return ;
        }
        std::string channel_name = buffers[1];
        if (buffers.size() > 3 || channel_name[0] != '#')
        {
            sender.sendMsg(":" + channel_name + " 476 :Bad Channel Mask\r\n");
            return ;
        }
        std::string _pass = NULL;
        if (buffers.size() == 3)
            _pass = buffers[2];
        isItNewChannel(channel_name, sender, channelList, _pass);
}

void    isItNewChannel(std::string channel_name, User& sender, std::map<std::string, Channel*>& channelList, std::string channel_pass)
{
    for (std::map<std::string, Channel*>::const_iterator it = channelList.begin(); it != channelList.end(); ++it)
    {
        if (it->first && it->first == channel_name)
        {
            
        }
    }



}