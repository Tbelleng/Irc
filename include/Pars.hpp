#ifndef PARS_HPP
# define PARS_HPP

# include "server.hpp"

enum Command {
    MODE,
    KICK,
    INVITE,
    PART,
    JOIN,
    PASS,
    TOPIC,
    USER,
    QUIT,
    NICK,
    PRIVMSG,
    NOTICE,
    UNKNOWN
};

Command parseCommand(const std::string& cmd);

void    join(std::vector<std::string> buffers, User& sender, std::vector<Channel*>& channelList);
void    kick(std::vector<std::string> buffers, User& sender, std::vector<Channel*> channelList, std::vector<User*> userList);
void    invite(std::vector<std::string> buffers, User& sender);
void    part(std::vector<std::string> buffers, User& sender, std::vector<Channel*>& channelList);
void    mode(std::vector<std::string> buffers, User& sender);
void    pass(std::vector<std::string> buffers, User& sender);
void    topic(std::vector<std::string> buffers, User& sender, std::vector<Channel*> channelList);
void    user(std::vector<std::string> buffers, User& sender);
void    quit(std::vector<std::string> buffers, User& sender);
void    nick(std::vector<std::string> buffers, User& sender, std::vector<User*> members);
void    privmsg(std::vector<std::string> buffers, User& sender, std::vector<Channel*>& channelList);
void    notice(std::vector<std::string> buffers, User& sender);
void    sendNoCmd(std::vector<std::string> buffers, User& sender);


#endif
