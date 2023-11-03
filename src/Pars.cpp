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

                // NICK FUNCTION //
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
    
    //refresh le nickname sur les channels
    
    return ;
}

                // JOIN FUNCTION //
void    channelExist(Channel& current_channel, User& sender, std::map<std::string, Channel*>& channelList, std::string channel_pass)
{
    //Rajouter ici une fonction si la Channel est en invite Only (regarder si le User a ete add aux operators)
    if(current_channel.needPass() == true && current_channel.getPassword() != channel_pass)
    {
        sender.sendMsg("475 " + sender.getNickname() + " " + current_channel.getName() + " :Cannot join channel (+k)\r\n");
        return ;
    }
    if(current_channel.getCurrentUsers() == current_channel.getMaxUsers())
    {
        sender.sendMsg("471 " + sender.getNickname() + " " + current_channel.getName() + " :Cannot join Channel\r\n");
        return ;
    }
    current_channel.addMember(sender);
    sender.sendMsg(":" + sender.getNickname() + "!~" + sender.getNickname() + "@localhost" + " JOIN " + current_channel.getName() + "\r\n");
    
    //suite des messages 
    
    
    (void)channelList;
}

void newChannel(std::string channel_name, User& sender, std::map<std::string, Channel*>& channelList, std::string channel_pass)
{
    Channel* new_channel = new Channel(channel_name, sender.getNickname(), channel_pass);
    std::cout << "New Channel joined" << std::endl;
    channelList.insert(std::make_pair(channel_name, new_channel));
    sender.sendMsg(":" + sender.getNickname() + "!~" + sender.getNickname() + "@localhost" + " JOIN " + channel_name + "\r\n");
    if (new_channel->getTopic() != "")
        sender.sendMsg("332 " + sender.getNickname() + " " + channel_name + " :" + new_channel->getTopic() + "\r\n");
    
    sender.sendMsg(": 353 " + sender.getNickname() + " = " + channel_name + " :" + "@" + sender.getNickname() + "\r\n");
    sender.sendMsg(": 366 " + sender.getNickname() + " " + channel_name + " :End of /NAMES list.\r\n");
    
    return ;
}

void    isItNewChannel(std::string channel_name, User& sender, std::map<std::string, Channel*>& channelList, std::string channel_pass)
{
    for (std::map<std::string, Channel*>::const_iterator it = channelList.begin(); it != channelList.end(); ++it)
    {
        if (!it->first.empty() && it->first == channel_name)
        {
            channelExist(*it->second, sender, channelList, channel_pass);
            return ;
        }
    }
    newChannel(channel_name, sender, channelList, channel_pass);
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
        std::cout << "DEBUG" << std::endl;
        std::string _pass = "";
        if (buffers.size() == 3)
            _pass = buffers[2];
        isItNewChannel(channel_name, sender, channelList, _pass);
}