/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:36 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/24 16:41:48 by tbelleng         ###   ########.fr       */
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

    // Print information about the new client
    std::cout << "New Client " << inet_ntoa(new_user._sockaddr.sin_addr) << ":"
              << ntohs(new_user._sockaddr.sin_port) << " (" << new_user.getSocket() << ")"
              << std::endl;

    // Add the new client's socket to the list of file descriptors to poll
    struct pollfd new_pollfd;
    new_pollfd.fd = new_user.getSocket();
    new_pollfd.events = POLLIN;
    new_pollfd.revents = 0;
    this->_pollfds.push_back(new_pollfd);

    // Add the new User to the map of connected clients
    // this->getConnection()[new_pollfd.fd] = new_user;
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
		// Got error or connection closed by client
		if (nbytes == 0)
			std::cout << "pollserver: socket " << user_fd << " hung up" << std::endl;
		else
			perror("recv");
		int sfd = user_fd;
		close(sfd);
		//effacer le client ici
	}
	//build a User here
	std::string message(buf, 512);
	if (this->ClientCheck(user_fd) == 0)
	{
	    this->GetUserInfo(user_fd, message);
        std::cout << "New user Added ! His fd is : " << user_fd << std::endl;
        User& sender = this->whichUser(user_fd);
        std::string message = ":" + sender.GetUserName() + " 001 " + sender.getNickname() + " " + ":Welcome to the our Server ! You are Live on Luciefer, Hel-Kame, Tbelleng Network " + "\r\n";
        send(user_fd, message.c_str(), message.size(), MSG_DONTWAIT);	
	}
    if (nbytes > 0)
	{
		// Handle buffer as a vector of messages
	    // std::string responsed = "001\r\n";
        // send(user_fd, responsed.c_str(), responsed.size(), 0);

		// If _buff contains \r\n then proceed and empty buff
		// Else do nothing
		User& sender = this->whichUser(user_fd);
		_parcing(message, sender, this->channelList, this->userList);
		// std::cout << "I got something, its " << message << std::endl;
		
	}
}

int Server::ClientCheck(int user_fd)
{
    if (userList.empty())
    {
        return 0;
    }
    
    for (std::vector<User*>::iterator it = userList.begin(); it != userList.end(); ++it)
    {
        if ((*it)->GetUserFd() == user_fd)
        {
            return 1;
        }
    }
    return 0;
}

void Server::GetUserInfo(int user_fd, std::string& buffer)
{
    std::istringstream iss(buffer);
    std::string line;
    
    std::string nickname;
    std::string password;
    std::string username;

    while (std::getline(iss, line)) {
        if (line.find("PASS ") == 0) 
        {
            password = line.substr(5);
        } 
        else if (line.find("NICK ") == 0)
        {
            nickname = line.substr(5);
        } 
        else if (line.find("USER ") == 0)
        {
            size_t startPos = line.find("USER ") + 5;
            size_t endPos = line.find(" ", startPos);
            username = line.substr(startPos, endPos - startPos);
            startPos = endPos + 1;
            endPos = line.find(" ", startPos);
            std::string hostname = line.substr(startPos, endPos - startPos);
        }
    }
    std::cout << "User info = " << password << " : " << nickname << " : " << username << std::endl;
    User* newUser = new User(nickname, password, username, user_fd);
    this->userList.push_back(newUser);
}

User& Server::whichUser(int user_fd)
{
    for (std::vector<User*>::iterator it = userList.begin(); it != userList.end(); ++it)
    {
        if ((*it)->GetUserFd() == user_fd)
        {
            return *(*it);
        }
    }
    throw std::runtime_error("User not found");
}

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
