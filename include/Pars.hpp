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

void    join(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList);
void    kick(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList, std::map<int, User*>& userList);
void    invite(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList, std::map<int, User*>& userList);
void    part(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList);
void    mode(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList, std::map<int, User*>& userList);
void    pass(std::vector<std::string> buffers, User& sender);
void    topic(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelList);
void    user(std::vector<std::string> buffers, User& sender);
void    quit(std::vector<std::string> buffers, User& sender);
void    nick(std::vector<std::string> buffers, User& sender, std::map<int, User*>& members);
void    privmsg(std::vector<std::string> buffers, User& sender, std::map<std::string, Channel*>& channelLis, std::map<int, User*>& userList);
void    notice(std::vector<std::string> buffers, User& sender);
void    sendNoCmd(std::vector<std::string> buffers, User& sender);


#endif
