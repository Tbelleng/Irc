/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:36 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/12 14:09:54 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../server.hpp"
# include <vector>

int MAX_UTILISATEURS = 10;

Server::Server(void)
{
	std::cout << "Server initialized" << std::endl;
}

Server::~Server(void)
{
	std::cout << "Server Destroyed" << std::endl;
}

void Server::ServerStart(void)
{
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return ;
    }
    
    if (!this->SetSocket(5500))
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

    std::cout << "Server listening on port 5500..." << std::endl;
	
	if (epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, this->serverSocket, &this->event) == -1) 
	{
		perror("Error adding socket");
        close(this->epoll_fd);
        close(this->serverSocket);
        return ;
	}

    while (true) {
        struct epoll_event events[MAX_UTILISATEURS];
        int new_event = epoll_wait(this->epoll_fd, events, MAX_UTILISATEURS, -1);
        if (new_event == -1) {
            perror("epoll_wait");
            return;
        }

        int i = 0;
        while (i < new_event) {
            if (events[i].data.fd == serverSocket) {
                // Handle new client connections
                struct sockaddr_in clientAddress;
                socklen_t clientAddrLen = sizeof(clientAddress);
                int clientSocket = accept(this->serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);

                if (clientSocket == -1)
                    perror("accept");
                else {
                    event.events = EPOLLIN;
                    event.data.fd = clientSocket;
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientSocket, &event) == -1) {
                        perror("epoll_ctl");
                        return;
                    }

                    // Store the new client socket in the list
                    clientSockets.push_back(clientSocket);
                }
            } else {
                // Handle messages from clients
                char buffer[512];
                int bytes_read = read(events[i].data.fd, buffer, sizeof(buffer));
                if (bytes_read > 0) {
                    // Broadcast the message to all other connected clients
                    for (unsigned long j = 0; j < this->clientSockets.size(); ++j) {
                        if (this->clientSockets[j] != events[i].data.fd) {
                            write(clientSockets[j], buffer, bytes_read);
                        }
                    }
                }
            }
            i++;
        }
    }
    close(serverSocket);
}

void    Server::SetPort(unsigned int port)
{
    this->port = port;
    return ;
}

int    Server::SetSocket(unsigned int port)
{
    this->SetPort(port);
    
	//struct sockaddr_in serverAddress;
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