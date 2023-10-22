#include "Pars.hpp"

Command parseCommand(const std::string& cmd) {
    if (cmd == "MODE") {
        return MODE;
    } else if (cmd == "KICK") {
        return KICK;
    } else if (cmd == "PART") {
        return PART;
    } else if (cmd == "JOIN") {
        return JOIN;
    } else if (cmd == "NOTICE") {
        return NOTICE;
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

void    join(std::vector<std::string> buffers, User& sender, std::vector<Channel*> channelList)
{
    // utiliser Channel ici 1/ Veirifier si channel eiste, si non creer une puis partir dans une fonction channel
    // 
    (void)channelList;
    std::string channelName = buffers[1];
    
    if (buffers.size() == 1 || buffers.size() > 2)
    {
        std::string argument = "PRIVMSG " + channelName + " :This is the channel topic \r\n";
        // argument += "332\r\n"; 
        sendMessage(sender.GetUserFd(), argument);
        return ;
    }
    
    // std::string argument = "PRIVMSG " + channelName + " :Welcome to the channel\r\n";
    std::string argument = "PRIVMSG " + channelName + " :Welcome to the channel \r\n";
    sendMessage(sender.GetUserFd(), argument);

    std::cout << "You used JOIN " << channelName << std::endl;
}
//********************************************************************

void    kick(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used KICK" << std::endl;
}


void    part(std::vector<std::string> buffers, User& sender, std::vector<Channel*> channelList) {
    std::cout << "You used PART" << std::endl;
    if (buffers.size() == 2)
        return ;
    for(std::vector<Channel *>::iterator it = channelList.begin(); it == channelList.end(); it++) {
        std::vector<int>    channelMembers = (*it)->getAllMember();
        if (*find(channelMembers.begin(), channelMembers.end(), sender.GetUserFd()) == sender.GetUserFd())
            (*it)->memberLeave(sender.GetUserFd());
    }
}

void    mode(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::cout << "You are in JOIN" << std::endl;
}

void    notice(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::cout << "You are in NOTICE" << std::endl;
}

void    topic(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used TOPIC" << std::endl;
}

void    user(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::string argument = "PRIVMSG : Welcome to our IRC Server !";
    //"332 " + channelName + " :This is the channel topic";
    // argument += "332\r\n"; 
    //sendMessage(sender.GetUserFd(), argument);
}

void    quit(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used QUIT" << std::endl;
}

void    nick(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used NICK" << std::endl;
}

void    sendNoCmd(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
}

