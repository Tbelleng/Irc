#ifndef IRC_HPP
# define IRC_HPP

# define DEBUG_CHANNEL 0
# define DEBUG_TOPIC 0
# define DEBUG_MESS 0

# define JOIN(nick, user, host, channel) (std::string(":" + nick + "!" + user + "@" + host + " JOIN :" + channel))

# define RPL_TOPIC(nickname, channel_name) (std::string(":" " 332 " + nickname + " " + channel_name + " :<topic>" + "\r\n"))
# define RPL_NAMREPLY(channel, nick, user, host, users) (std::string (": 353 " + nick + "!" + user + "@" + host + " = " + channel + " :" + users + "\r\n"))
# define RPL_ENDOFNAMES(channel, nick, user, host) (std::string(": 366 " + nick + "!" + user + "@" + host + " " + channel + " :End of /NAMES list." + "\r\n"))
# define RPL_AWAY(chan_nickname, message) (std::string(":" " 301 " + chan_nickname + " :" + message + "\r\n"))
# define CREATEDCHANNEL(channel) (std::string(channel + " channel created\r\n"))


# define ERR_BADCHANMASK(channel) (std::string(": 476 " + channel + " :Bad Channel Mask\r\n"))
# define ERR_NOSUCHCHANNEL(nick, channel) (": 403 " + nick + " " + channel + " :No such channel\r\n")

# include <algorithm>
# include <vector>
# include <map>
# include <iostream>
# include <string>
# include <fcntl.h>
# include <cstring>
# include <sstream>
# include <stdio.h>
# include <iomanip>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <poll.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <netinet/in.h> 
# include <vector>

# include "Connection.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "Pars.hpp"
# include "server.hpp"

void    _send(const char* message, int member);
std::vector<std::string>    ft_split(const std::string& inputString);
bool    userInServer(std::string userName, std::map<int, User*>& userList);
User* whichUser(std::string userName, std::map<int, User*>& userList);

#endif
