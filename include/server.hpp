/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:39 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/23 22:07:29 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

# define DEBUG_CHANNEL 0
# define DEBUG_TOPIC 0

# define RPL_TOPIC 332
# define JOIN(nick, user, host, channel) (":" + nick + "!" + user + "@" + host + " JOIN :" + channel)

# include <algorithm>
# include <vector>
# include <map>
# include <iostream>
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
# include "Topic.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "Pars.hpp"
# include "irc.hpp"
# include "Message.hpp"


class Server
{
	private :
	
	std::string password;
	unsigned int port;
	int serverSocket;
	struct sockaddr_in serverAddress;
	//struct epoll_event event;
	
	std::vector<int> clientSockets;
	std::vector<User*> userList;
	std::vector<Channel*> channelList;
	
	public :
	
	//new
	Server(int port, std::string password);
	~Server(void);	
	
	void	createSocket(void);
	void	binding(sockaddr_in hint);
	void	listening(void);
	void	addingPoll(void);

	void	acceptNewClient();
	void	handleClientRequest(int user_fd);
	int     getSocket(void);
	std::string     getPassword(void);
	
	std::vector<struct pollfd>	_pollfds;
	
	//Old
	void SetPort(unsigned int port);
	int  SetSocket(unsigned int port);
	void ServerRun(void);
	void ShowUserList(std::vector<User*> userList);
	int AddingNewClient(int epoll_fd, struct epoll_event* events);
	int ClientCheck(int user_fd);
	void GetUserInfo(int user_fd, std::string& buffer);
	User& whichUser(int user_fd);

};


bool    _parcing(std::string buffer, User* sender, std::vector<Channel*> channelList);
//User&   getUser(int socket_client);
void    _send(const char* message, int member, int epfd, struct epoll_event& ev);

#endif
