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
    std::cout << "LA CHANNEL EXISTE" << std::endl;
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
    current_channel.joinBroadcast(sender);
    
    if (current_channel.getTopic() != "")
        sender.sendMsg("332 " + sender.getNickname() + " " + current_channel.getName() + " :" + current_channel.getTopic() + "\r\n");
    
    std::string user_list = current_channel.getUserList();
    
    sender.sendMsg(": 353 " + sender.getNickname() + " = " + current_channel.getName() + " :" + user_list + "\r\n");
    sender.sendMsg(": 366 " + sender.getNickname() + " " + current_channel.getName() + " :End of /NAMES list.\r\n");
    
    
    (void)channelList;
    return ;
}

void newChannel(std::string channel_name, User& sender, std::map<std::string, Channel*>& channelList, std::string channel_pass)
{
    std::cout << "NOUVELLE CHANNEL" << std::endl;
    Channel* new_channel = new Channel(channel_name, sender.getNickname(), channel_pass, sender);
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
        std::string channel_name = removeSpecificSpaces(buffers[1]);
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

                    //PRIVMSG 
void    privmsg(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList, std::map<int, User*>& userList)
{
    if (buffers.size() == 1) {
        sender.sendMsg("461 " + buffers[0] + " :Not Enough Parameters\r\n");
        return;
    }
    if (buffers.size() == 2) {
        sender.sendMsg(": 412 :No text to send\r\n");
        return;
    }
    if (buffers[2][0] != ':') {
        sender.sendMsg("ERROR :Invalid message format\r\n");
        return;
    }
    std::string clean_msg = trimBuffers(buffers);
    if (buffers[1][0] == '#') //Si la cible est une channel
    {
        std::map<std::string, Channel*>::iterator it;
        for (it = channelList.begin(); it != channelList.end(); ++it)
        {
            if (it->first == buffers[1])
            {
                it->second->broadcasting((":" + sender.getNickname() + " PRIVMSG " + buffers[1] + " :" + clean_msg + "\r\n"), sender.GetUserFd());
                return ;
            }
        }
        sender.sendMsg(": 403 " + buffers[1] + ": No such CHANNEL\r\n");
    }
    else
    {
        std::map<int, User*>::iterator it;
        for (it = userList.begin(); it != userList.end(); ++it)
        {
            //std::cout << "Nickname de l'iterateur " << std::endl;
            //printAsciiCharacters(it->second->getNickname());
            //std::cout << std::endl << "Le nickname du buffeur " << std::endl;
            //printAsciiCharacters(buffers[1]);
            if (it->second->getNickname() == buffers[1])
            {
                //std::cout << "J'ai trouver l'utilisateur" << std::endl;
                it->second->sendMsg(":" + sender.getNickname() + " PRIVMSG " + it->second->getNickname() + " : " + clean_msg + "\r\n");
                return;
            }
        }
        sender.sendMsg(": 401 " + sender.getNickname() + ": No such NICK\r\n");
        return;
    }
    return ;
}

                // PART FUNCTION //
void    part(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList)
{
    if (buffers.size() != 2) {
        sender.sendMsg(":" + sender.getNickname() + " 461 :Not Enough Parameters\r\n");
        return;
    }
    if (buffers[1][0] != '#') {
        sender.sendMsg(": 403 " + sender.getNickname() + " " + buffers[1] + " :No such channel\r\n");
        return;
    }
    std::string channel_name = removeSpecificSpaces(buffers[1]);
    std::cout << "Le nom de la channel = " << channel_name << std::endl;
    printAsciiCharacters(channel_name);
    
    for (std::map<std::string, Channel*>::const_iterator it = channelList.begin(); it != channelList.end(); ++it)
    {
        if (!it->first.empty() && it->first == channel_name)
        {
            if (it->second->userOfChannel(sender))
            {
                it->second->broadcasting((":" + sender.getNickname() + "!~" + sender.getNickname() + "@localhost" + " PART " + channel_name + "\r\n"), sender.GetUserFd());
                sender.sendMsg(":" + sender.getNickname() + "!~" + sender.getNickname() + "@localhost" + " PART " + channel_name + "\r\n");
                it->second->removeUser(sender);
                return ;
            }
        }
    }
    sender.sendMsg("442 " + sender.getNickname() + " :You're not on that channel\r\n");
    return ;
}