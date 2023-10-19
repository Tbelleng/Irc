/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:39 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/19 17:06:36 by tbelleng         ###   ########.fr       */
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
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/epoll.h>
# include <arpa/inet.h>
# include <vector>
# include "Topic.hpp"
# include "Channel.hpp"
# include "User.hpp"

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
	

};

void    _send(const char* message, int member, int epfd, struct epoll_event& ev);

#endif
