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

//***********************************JOIN FUNCTION*********************
bool setNonBlocking(int socket_fd)
{
    if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl");
        return false;
    }
    return true;
}

bool sendMessage(int user_fd, const std::string& message)
{
    if (!setNonBlocking(user_fd)) {
        return false;
    }

    ssize_t bytes_sent = write(user_fd, message.c_str(), message.size());

    if (bytes_sent == -1) {
        if (errno == EAGAIN) {
            std::cout << "Message send would block." << std::endl;
            return false;
        } else {
            perror("write");
            return false;
        }
    }

    return true;
}

bool isFirstCharHash(const std::string& channel)
{
    if (!channel.empty() && channel[0] == '#') {
        return true;
    } else {
        return false;
    }
}

void    join(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList)
{
    std::string channel = buffers[1];
    std::vector<struct s_replie>    replie;

    setReplie(&replie);
    if (buffers.size() < 2) {
        std::vector<std::string>    tmp;
        tmp.push_back(buffers[0]);
        Server::sendReplie(tmp , 461, sender.GetUserFd(), replie);
        return ;
    }
    
    if (!isFirstCharHash(channel))
    {
        std::string error = ERR_BADCHANMASK(channel);
        send(sender.GetUserFd(), error.c_str(), error.size(), MSG_DONTWAIT);
        return ;
    }
    
    Channel* channel_check = Server::findChannel(channel, channelList);
    if (channel_check != NULL) //La channel existe deja
    {
        std::cout << "Channel already exist !\n" << std::endl;
        channel_check->addMember(sender);
        std::string topic_message = RPL_TOPIC(sender.getNickname(), channel_check->getName());
        send(sender.GetUserFd(), topic_message.c_str(), topic_message.size(), MSG_DONTWAIT);
        std::string name_display = RPL_NAMREPLY(sender.getNickname(), "=", channel_check->getName(), sender.getNickname());
        send(sender.GetUserFd(), name_display.c_str(), name_display.size(), MSG_DONTWAIT);
        std::string end_name = RPL_ENDOFNAMES(sender.getNickname(), channel_check->getName());
        send(sender.GetUserFd(), end_name.c_str(), end_name.size(), MSG_DONTWAIT);
    }
    else
    {
        Channel* new_channel = new Channel(channel, sender.GetUserFd());
        std::cout << "New Channel Joined : " << new_channel->getName() << std::endl;
        std::string topic_message = RPL_TOPIC(sender.getNickname(), new_channel->getName());
        send(sender.GetUserFd(), topic_message.c_str(), topic_message.size(), MSG_DONTWAIT);
        std::string name_display = RPL_NAMREPLY(sender.getNickname(), "=", new_channel->getName(), sender.getNickname());
        send(sender.GetUserFd(), name_display.c_str(), name_display.size(), MSG_DONTWAIT);
        std::string end_name = RPL_ENDOFNAMES(sender.getNickname(), new_channel->getName());
        send(sender.GetUserFd(), end_name.c_str(), end_name.size(), MSG_DONTWAIT);
        channelList.insert(std::pair<std::string, Channel*>(channel, new_channel));
        std::cout << "Channel added to the list" << std::endl;
    }
    
    // utiliser Channel ici 1/ Veirifier si channel existe, si non creer une puis partir dans une fonction channel
    
    //attention si nouvelle channel ne pas oublier de la mettre dans channelList
}
//********************************************************************

void    kick(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*> channelList,  std::map<int, User*> userList) {
    std::vector<struct s_replie>    replie;

    setReplie(&replie);
    if (buffers.size() < 3) {
        std::vector<std::string>    tmp;
        tmp.push_back(buffers[1]);
        Server::sendReplie(tmp , 461, sender.GetUserFd(), replie);
        return ;
    }
    Channel* chan = Server::findChannel(buffers[2], channelList);
    if (chan == 0) {
        std::vector<std::string>    tmp;
        tmp.push_back(buffers[2]);
        Server::sendReplie(tmp , 403, sender.GetUserFd(), replie);
        return ;
    }
    std::vector<int>    allOpMember = chan->getAllOpMember();
    if(*find(allOpMember.begin(), allOpMember.end(), sender.GetUserFd()) != sender.GetUserFd()){
        std::vector<std::string>    tmp;
        tmp.push_back(buffers[2]);
        Server::sendReplie(tmp , 403, sender.GetUserFd(), replie);
        return ;
    }
    User*    vic = Server::findMemberName(userList, buffers[3]);
    if(!chan->isInChannel(vic->GetUserFd())) {
        std::vector<std::string>    tmp;
        tmp.push_back(buffers[2]);
        Server::sendReplie(tmp , 403, sender.GetUserFd(), replie);
        return ;
    }
    chan->suppMember(sender.GetUserFd(), vic->GetUserFd());
    return ;
}

void    part(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*> channelList) {
    std::vector<struct s_replie>    replie;

    setReplie(&replie);
    if (buffers.size() < 2) {
        std::vector<std::string>    tmp;
        tmp.push_back(buffers[0]);
        Server::sendReplie(tmp , 461, sender.GetUserFd(), replie);
        return ;
    }
    for (std::vector<std::string>::iterator it = buffers.begin() + 2; it != buffers.end(); it++) {
        std::string str = *it;
        str.erase(0,1);
        str = "#" + str;
        Channel* chan = Server::findChannel(str, channelList);
        if (!chan) {
            std::string str_erro = ERR_NOSUCHCHANNEL(sender.getNickname(), str);
            send(sender.GetUserFd(), str_erro.c_str(), str_erro.size(), 0);
            continue ;
        }
        if(!chan->isInChannel(sender.GetUserFd())){
            std::vector<std::string>    tmp;
            tmp.push_back(*it);
            Server::sendReplie(tmp , 442, sender.GetUserFd(), replie);
            continue ;
        } else 
            chan->memberLeave(sender.GetUserFd());
    }
    return ;
}

void    mode(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    // return error : ERR_NEEDMOREPARAMS(461)<cmd> ERR_CHANOPRIVSNEEDED(482)<channel> ERR_NOSUCHNICK(401)<nickname> ERR_UNKNOWMODE(472)<char> ERR_NOSUCHCHANNEL(403)<channel name> ERR_USERDONTMATCH(502)
    // replie : RPL_UNMODEIS(221)<user mode string>
    //std::cout << "You are in JOIN" << std::endl;
}

void    topic(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*> channelList) {
    std::vector<struct s_replie>    replie;

    setReplie(&replie);
    if (buffers.size() < 2) {
        std::vector<std::string>    tmp;
        tmp.push_back(buffers[1]);
        Server::sendReplie(tmp , 461, sender.GetUserFd(), replie);
        return ;
    }
    Channel* chan = Server::findChannel(buffers[2], channelList);
    if (chan == 0) {
        std::vector<std::string>    tmp;
        tmp.push_back(buffers[2]);
        Server::sendReplie(tmp , 403, sender.GetUserFd(), replie);
        return ;
    }
    if(!chan->isInChannel(sender.GetUserFd())){
        std::vector<std::string>    tmp;
        tmp.push_back(chan->getName());
        Server::sendReplie(tmp , 442, sender.GetUserFd(), replie);
        return ;
    }
    std::string topic = chan->getTopic();
    if (topic == "")
    {
        if(buffers.size() >= 3) {
                std::string topic = 0;
            for(std::vector<std::string>::iterator it = buffers.begin() + 3; it != buffers.end(); it++)
               topic += *it; 
            if (!chan->setTopic(sender.GetUserFd(), topic)) {
                    std::vector<std::string>    tmp;
                    tmp.push_back(chan->getName());
                    Server::sendReplie(tmp , 482, sender.GetUserFd(), replie);
                    return ;
            }
        }
        std::vector<std::string>    tmp;
        tmp.push_back(chan->getName());
        Server::sendReplie(tmp , 331, sender.GetUserFd(), replie);
    } else {
        if(buffers.size() >= 3) {
                std::string topic = 0;
            for(std::vector<std::string>::iterator it = buffers.begin() + 3; it != buffers.end(); it++)
               topic += *it; 
            if (!chan->setTopic(sender.GetUserFd(), topic)) {
                    std::vector<std::string>    tmp;
                    tmp.push_back(chan->getName());
                    Server::sendReplie(tmp , 482, sender.GetUserFd(), replie);
                    return ;
            }
        }
        std::vector<std::string>    tmp;
        tmp.push_back(chan->getName());
        tmp.push_back(topic);
        Server::sendReplie(tmp , 332, sender.GetUserFd(), replie);
    }
}
void    privmsg(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList)
{
    if (buffers.size() > 2)
    {
        std::string channel = buffers[1];
        Channel* channel_check = Server::findChannel(channel, channelList);
        std::string msg = RPL_AWAY(channel_check->getName(), buffers[2]);
        channel_check->spreadMsg(sender, channel, buffers);
        
        //std::string end_name = RPL_ENDOFNAMES(sender.getNickname(), new_channel->getName());
        //send(sender.GetUserFd(), name_display.c_str(), name_display.size(), MSG_DONTWAIT);
    }
    else
        return ;
}

void    user(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::string argument = "PRIVMSG : Welcome to our IRC Server !";
    //"332 " + channelName + " :This is the channel topic";
    // argument += "332\r\n"; 
    //sendMessage(sender.GetUserFd(), argument);
    // return error : ERR_NEEDMOREPARAMS(461)<cmd> ERR_ALREADYREGISTRED(462)
}

void    quit(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used QUIT" << std::endl;
}


void    nick(std::vector<std::string> buffers, User& sender, std::map<int, User*> members) {
    std::vector<struct s_replie>    replie;

    setReplie(&replie);
    if (buffers.size() < 2) {
        std::vector<std::string>    tmp;
        Server::sendReplie(tmp , 431, sender.GetUserFd(), replie);
        return ;
    }
    if(Server::findMemberName(members, buffers[2])) {
        std::vector<std::string>    tmp;
        tmp.push_back(buffers[2]);
        Server::sendReplie(tmp , 433, sender.GetUserFd(), replie);
        return ;
    }
    sender.ChangeNickname(buffers[2]);
    return ;
}

void    pass(std::vector<std::string> buffers, User& sender) {
    (void) buffers, (void) sender;
    // return error : ERR_NEEDMOREPARAMS(461)<cmd> ERR_ALREADYREGISTRED(462)
}

void    sendNoCmd(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
}

