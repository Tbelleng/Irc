#ifndef IRC_HPP
# define IRC_HPP

# define DEBUG_CHANNEL 0
# define DEBUG_TOPIC 0
# define DEBUG_MESS 0

# include <algorithm>
# include <vector>
# include <map>
# include <iostream>
# include <fcntl.h>
# include <cstring>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/epoll.h>
# include <arpa/inet.h>
# include <vector>

# include "User.hpp"
# include "Topic.hpp"
# include "Channel.hpp"
# include "server.hpp"

void    _send(const char* message, int member, int epfd, struct epoll_event& ev);
std::vector<std::string>    ft_split(std::string s1, const char token);

#endif
