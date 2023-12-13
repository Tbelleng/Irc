/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:39 by tbelleng          #+#    #+#             */
/*   Updated: 2023/12/13 17:47:21 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

# include "irc.hpp"
#include <csignal>
#include <cstdlib>

struct  s_replie {
    int nbReplie;
    std::string rplReplie;
};

//int g_exitFlag = 1;

class Server
{
	private :
	
	std::string password;
	unsigned int port;
	int serverSocket;
	struct sockaddr_in serverAddress;
	std::map<int, User*> userList;
	std::map<std::string, Channel*> channelList;
	
	public :
	
	static std::string _name;
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
	int GetUserInfo(int user_fd, std::string& buffer);
	User& whichUser(int user_fd);
    static void    sendReplie(std::vector<std::string> buffer, int replie, int socket_client, std::vector<struct s_replie> _replie);
    static User*   findMemberName(std::map<int, User*> userList, std::string member_name);
    static Channel* findChannel(std::string& channelName, std::map<std::string, Channel*>& channelList);

};

void    setReplie(std::vector<struct s_replie>* replie);
bool    _parcing(std::string buffer, User* sender, std::map<std::string, Channel*> channelList, std::vector<User*> userList);
std::string trimBuffers(const std::vector<std::string>& buffer);
std::string removeSpecificSpaces(const std::string& input);
void printAsciiCharacters(const std::string& str);
#endif
