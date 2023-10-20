/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:39 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/20 17:31:03 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

# define DEBUG_CHANNEL 0
# define DEBUG_TOPIC 0

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
# include <sys/socket.h>
# include <sys/epoll.h>
# include <arpa/inet.h>
# include <netinet/in.h> 
# include <vector>
# include "Topic.hpp"
# include "Channel.hpp"
# include "User.hpp"
# include "irc.hpp"


class Server
{
	private :
	
	std::string password;
	unsigned int port;
	int serverSocket;
	int epoll_fd;
	struct sockaddr_in serverAddress;
	struct epoll_event event;
	std::vector<int> clientSockets;
	std::vector<User*> userList;
	//std::vector<Channel*> channelList;
	
	public :
	
	Server(int port, std::string password);
	~Server(void);
	void ServerStart(void);
	void SetPort(unsigned int port);
	int  SetSocket(unsigned int port);
	void ServerRun(void);
	void ShowUserList(std::vector<User*> userList);
	int AddingNewClient(int epoll_fd, struct epoll_event* events);
	int ClientCheck(int user_fd);
	void GetUserInfo(int user_fd, std::string& buffer);

};


bool    _parcing(std::string buffer, int socket_client);
//User&   getUser(int socket_client);
void    _send(const char* message, int member, int epfd, struct epoll_event& ev);

#endif
