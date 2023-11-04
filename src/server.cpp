/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:36 by tbelleng          #+#    #+#             */
/*   Updated: 2023/11/04 17:35:01 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.hpp"
# include "utils_server.cpp"

int MAX_UTILISATEURS = 10;

//******************************Class Constructor***************************
Server::Server(int port, std::string password)
{
    this->port = port;
    this->password = password;
	std::cout << "Server initialized" << std::endl;
}


//******************************Class Destructor***************************
Server::~Server(void)
{
	std::cout << "Server Destroyed" << std::endl;
}
//*************************************************************************

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		((char *)s)[n - 1] = 0;
		n--;
	}
}

void	Server::addingPoll(void) 
{
    if (_pollfds.empty())
    {

        struct pollfd server_pollfd;
        server_pollfd.fd = serverSocket;
        server_pollfd.events = POLLIN; 
        server_pollfd.revents = 0;
       
        _pollfds.push_back(server_pollfd);
    } 
    else
    {
       
        _pollfds[0].fd = serverSocket;
        _pollfds[0].events = POLLIN;
        _pollfds[0].revents = 0;
    }

}

void	Server::createSocket(void) 
{

	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->serverSocket == -1)
		std::cerr << "Can't create socket." << std::endl;
}

void	Server::binding(sockaddr_in hint) 
{

	int yes = 1;
	setsockopt(this->serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)); 
	if (bind(this->serverSocket, (sockaddr*)&hint, sizeof(hint)) == -1)
		std::cerr << "Can't bind to IP/port." << std::endl;
}

void	Server::listening(void)
{

	if (listen(this->serverSocket, SOMAXCONN) == -1)
		std::cerr << "Can't listen." << std::endl;
	if (this->serverSocket == -1)
		std::cerr << "error getting listening socket" << std::endl;
}

void Server::acceptNewClient() 
{
    // Create a new User object to represent the incoming client
    NewConnection new_user;

    // Accept the new client connection
    int new_socket = accept(this->getSocket(), (struct sockaddr*)&new_user._sockaddr, &new_user._socklen);

    if (new_socket == -1) {
        perror("accept");
        return;
    }

    // Set the new socket for the User
    new_user.setSocket(new_socket);

    std::cout << "New Client " << inet_ntoa(new_user._sockaddr.sin_addr) << ":"
              << ntohs(new_user._sockaddr.sin_port) << " (" << new_user.getSocket() << ")"
              << std::endl;

    struct pollfd new_pollfd;
    new_pollfd.fd = new_user.getSocket();
    new_pollfd.events = POLLIN;
    new_pollfd.revents = 0;
    this->_pollfds.push_back(new_pollfd);
}

int     Server::getSocket(void) 
{
	return (this->serverSocket);
}

std::string	    Server::getPassword(void)
{
	return (this->password);
}

void	Server::handleClientRequest(int user_fd)
{
    char buf[512];
	memset(buf, 0, 512);
	int nbytes = recv(user_fd, buf, sizeof(buf), 0);
	std::string testing (buf, 512);
	std::cout << "BUFF = " << testing << std::endl;
	if (nbytes <= 0)
	{
		if (nbytes == 0)
			std::cout << "pollserver: socket " << user_fd << " hung up" << std::endl;
		else
			perror("recv");
		int sfd = user_fd;
		close(sfd);
	}

	std::string message(buf, 512);
	if (this->ClientCheck(user_fd) == 0)
	{
	    fcntl(user_fd, F_SETFL, O_NONBLOCK);
	    if (!this->GetUserInfo(user_fd, message))
	    {
	            std::string error = "Wrong format for registration, you cant connect";
	            send(user_fd, error.c_str(), error.size(), MSG_DONTWAIT);
	            close(user_fd);
	            return ;
	    }
        std::cout << "New user Added ! His fd is : " << user_fd << std::endl;
        User& sender = this->whichUser(user_fd);
        std::string message = "001 " + sender.GetUserName() + sender.getNickname() + " " + ":Welcome to our Server ! You are Live on Luciefer, Hel-Kame, Tbelleng Network " + "\r\n";
        send(user_fd, message.c_str(), message.size(), MSG_DONTWAIT);	
        return ;
	}
    if (nbytes > 0)
	{
		User& sender = this->whichUser(user_fd);
		_parcing(message, sender, this->channelList, this->userList);
	}
	message.clear();
}

int Server::ClientCheck(int user_fd) {
    if (this->userList.find(user_fd) == this->userList.end())
        return 0;
    return 1;
}

int Server::GetUserInfo(int user_fd, std::string& buffer)
{
    std::istringstream iss(buffer);
    std::string line;
    
    std::string password;
    std::string nickname;
    std::string username;

    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string word;
        std::string prevKeyword;

        while (lineStream >> word) {
            if (prevKeyword == "PASS") {
                if (!word.empty() && word != "NICK" && word != "USER") {
                    std::cout << "Word after PASS: " << word << std::endl;
                    password = word;
                } else {
                    std::cout << "FAIL AT PASS" << std::endl;
                    return 0;
                }
            } else if (prevKeyword == "NICK") {
                if (!word.empty() && word != "PASS" && word != "USER") {
                    std::cout << "Word after NICK: " << word << std::endl;
                    nickname = word;
                } else {
                    std::cout << "FAIL AT NICK" << std::endl;
                    return 0;
                }
            } else if (prevKeyword == "USER") {
                if (!word.empty() && word != "PASS" && word != "NICK") {
                    std::cout << "Word after USER: " << word << std::endl;
                    username = word;
                } else {
                    std::cout << "FAIL AT USER" << std::endl;
                    return 0;
                }
            }

            prevKeyword = word;
        }
    }
    
    if (username.empty())
        username = "stud42";
    
    if (nickname.empty() || password.empty() || username.empty()) 
    {
        return 0;
    }
    nickname.erase(std::remove(nickname.begin(), nickname.end(), ' '), nickname.end());
    password.erase(std::remove(password.begin(), password.end(), ' '), password.end());
    username.erase(std::remove(username.begin(), username.end(), ' '), username.end());
    User* newUser = new User(nickname, password, username, user_fd);
    this->userList.insert(std::pair<int, User*>(user_fd, newUser));
    return 1;
}

User& Server::whichUser(int user_fd) {return *this->userList[user_fd];}

std::string find_replie(int replie, std::vector<struct s_replie> _replie) {
    for (std::vector<struct s_replie>::iterator it = _replie.begin(); it != _replie.end(); it++) {
        if (it->nbReplie == replie)
            return it->rplReplie;
    }
    return 0;
}

void    Server::sendReplie(std::vector<std::string> buffer, int replie, int socket_client, std::vector<struct s_replie> _replie) {
    std::stringstream   ss;

    ss << replie;
    std::string replie_str = ss.str();
    if (find_replie(replie, _replie) == "")
        return ;
    if (replie == 331 || replie == 368) {
        std::string str_replie = replie_str + " " + buffer[0] + find_replie(replie, _replie);
        _send(str_replie.c_str(), socket_client);
    } else if (replie == 221 || replie == 324){
        std::string str_replie = replie_str + " ";
        for(std::vector<std::string>::iterator it = buffer.begin(); it != buffer.end(); it++)
            str_replie += *it;
        str_replie += find_replie(replie, _replie);
        _send(str_replie.c_str(), socket_client);
    } else if (replie == 301 || replie == 332) {
        std::string str_replie = replie_str + " " + buffer[0] + find_replie(replie, _replie) + buffer[1] + "\r\n";
        _send(str_replie.c_str(), socket_client);
    } else if (replie == 412 || replie == 431 || replie == 462) {
        std::string str_replie = replie_str + " " + find_replie(replie, _replie);
        _send(str_replie.c_str(), socket_client);
        return ;
    } else if (replie == 411) {
        std::string str_replie = replie_str + " " + find_replie(replie, _replie) + "(" + buffer[0] + ")\r\n";
        _send(str_replie.c_str(), socket_client);
        return ;
    } else {
        std::string str_replie = replie_str + " " + buffer[0]  + find_replie(replie, _replie);
        _send(str_replie.c_str(), socket_client);
    }
    return ;
}

User*     Server::findMemberName( std::map<int, User*> userList, std::string member_name) {
    if (userList.empty())
        return NULL;
    for(std::map<int, User*>::iterator it = userList.begin(); it != userList.end(); it++) {
        if(it->second->GetUserName() == member_name)
            return it->second;
    }
    return NULL;
}

Channel* Server::findChannel(std::string& channelName, std::map<std::string, Channel*>& channelList)
{
    if (channelList.empty())
        return NULL;
    if(channelList.find(channelName) == channelList.end())
        return NULL; 
    return channelList[channelName];
}
