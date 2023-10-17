/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:39 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/17 16:48:45 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

# include <algorithm>
# include <vector>
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
# include "Channel.hpp"


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
	std::vector<Channel*> channelList;
	
	public :
	
	Server(int port, std::string password);
	~Server(void);
	void ServerStart(void);
	void SetPort(unsigned int port);
	int  SetSocket(unsigned int port);
	void ServerRun(void);
	

};


#endif
