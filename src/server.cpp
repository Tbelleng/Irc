/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:36 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/20 18:16:12 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.hpp"

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


//#This function will init our server as follow :
//      # Create and Bind the socket to the right port
//      # Check if there is any error during the connect
//      # In the loop, listen for any new epoll event like connection
//          # Or spread message across all clients
void Server::ServerStart(void)
{
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket == -1) 
    {
        std::cerr << "Error creating socket" << std::endl;
        return ;
    }
    
    if (!this->SetSocket(this->port))
        return ;

    this->epoll_fd = epoll_create(1);
	if (this->epoll_fd == -1)
	{
        perror("Error while creating Epoll");
        return ;
	}

	this->event.data.fd = serverSocket;
	this->event.events = EPOLLIN;

	
    if (listen(this->serverSocket, MAX_UTILISATEURS) == -1) 
    {
        std::cerr << "Error listening on socket" << std::endl;
        close(this->serverSocket);
        return ;
    }

    std::cout << "Server listening on port " << this->port << std::endl;
	
	if (epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, this->serverSocket, &this->event) == -1) 
	{
		perror("Error adding socket");
        close(this->epoll_fd);
        close(this->serverSocket);
        return ;
	}
	
	this->ServerRun();
	return ;
}

void    Server::ShowUserList(std::vector<User*> userList)
{
    for (std::vector<User*>::const_iterator it = userList.begin(); it != userList.end(); ++it)
    {
        const User* user = *it;
        // Access the nickname of each user and print it
        std::cout << "User Nickname: " << user->GetUserName() << std::endl;
    }
}

void Server::ServerRun(void)
{
    while (true) 
    {
        struct epoll_event events[MAX_UTILISATEURS];
        int new_event = epoll_wait(this->epoll_fd, events, MAX_UTILISATEURS, -1);
        if (new_event == -1) 
        {
            perror("epoll_wait");
            return;
        }

        for (int i = 0; i < new_event; ++i)
        {
            if (events[i].events & (EPOLLERR | EPOLLHUP)) {
                std::cout << "Client disconnected" << std::endl;
                //iterer dans la liste de user et le vecteur de socket pour effacer User et son fd
                close(events[i].data.fd);  // Close the socket
                // Remove the disconnected socket from  data
            }
            else if (events[i].data.fd == serverSocket) //New Connection
            {
                this->AddingNewClient(epoll_fd, events);
            }
            else //Client already connected sending data
            {
                //check if this fd exist within users
                char buffer[512];
                int bytes_read = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                std::string message(buffer, bytes_read);
                
                if (this->ClientCheck(events[i].data.fd) == 0)
                {
                    this->GetUserInfo(events[i].data.fd, message);
                }
                if (bytes_read > 0) 
                {
                    std::string message(buffer, bytes_read);

                        // Handle messages from clients
                    if (message.find("JOIN") == 0) 
                    {
                        std::string channel_title  = message.substr(5);
                        send(events[i].data.fd, channel_title.c_str(), channel_title.size(), 0);
                        std::cout << "CHANNEL CREATED" << std::endl;
                        return ;
                    }
                } 
                else 
                    write(this->clientSockets[i], "Unknown command", 15); // Handle unknown commands
                std::string responsed = "001\r\n";
                send(events[i].data.fd, responsed.c_str(), responsed.size(), 0);
            }
        }
    }
    close(serverSocket);
}

//**************************** Setters ******************************
void    Server::SetPort(unsigned int port)
{
    this->port = port;
    return ;
}

int    Server::SetSocket(unsigned int port)
{
    this->SetPort(port);
    
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(this->port);
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    if (bind(this->serverSocket, (struct sockaddr*)&this->serverAddress, sizeof(this->serverAddress)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        close(this->serverSocket);
        return 0;
    }
    return 1;
}

//************************************Clients Manager**************************

int    Server::AddingNewClient(int epoll_fd, struct epoll_event* )
{
    struct sockaddr_in clientAddress;
    socklen_t clientAddrLen = sizeof(clientAddress);
    int clientSocket = accept(this->serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);

    if (clientSocket == -1)
    {
        if (errno != EWOULDBLOCK)
        {
            perror("accept");
            return -1;
        }
    }
    
    event.events = EPOLLIN;
    event.data.fd = clientSocket;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientSocket, &event) == -1)
    {
        perror("epoll_ctl");
        return -1;
    }
    clientSockets.push_back(clientSocket);
    std::cout << "New Client Added ! listenning..." << std::endl;
    
    return 0;
}

//*********************************Users Manager*************************

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
        User* newUser = new User(nickname, password, username, user_fd);
        this->userList.push_back(newUser);
    }
}