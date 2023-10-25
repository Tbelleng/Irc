/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:39 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/25 15:19:22 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

# define DEBUG_CHANNEL 0
# define DEBUG_TOPIC 0

# define JOIN(nick, user, host, channel) (":" + nick + "!" + user + "@" + host + " JOIN :" + channel)
# define RPL_TOPIC(nickname, channel_name) (std::string(":" " 332 " + nickname + " " + channel_name + " :<topic>" + "\r\n").c_str())
# define RPL_NAMREPLY(nickname, chansymbol, channel_name, members) (std::string (":" " 353 " + nickname + " " + chansymbol + " " + channel_name + " :" + members + " \r\n"))
# define RPL_ENDOFNAMES(nickname, channel_name) (std::string(":" " 366 " + nickname + " " + channel_name + " :End of /NAMES list" + "\r\n"))

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
# include "Topic.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "Pars.hpp"
# include "irc.hpp"
# include "Message.hpp"

void    _send(const char* message, int member);

struct  s_replie {
    int nbReplie;
    std::string rplReplie;
};

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
    static void    sendReplie(std::vector<std::string> buffer, int replie, int socket_client, std::vector<struct s_replie> _replie);

};


void    setReplie(std::vector<struct s_replie>* replie);
bool    _parcing(std::string buffer, User* sender, std::vector<Channel*> channelList, std::vector<User*> userList);
//User&   getUser(int socket_client);


#endif
