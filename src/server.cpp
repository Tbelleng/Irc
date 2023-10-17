/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:59:36 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/17 18:41:06 by tbelleng         ###   ########.fr       */
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

                // Remove the disconnected socket from your data structures
                // (e.g., clientSockets and userList)
            }
            else if (events[i].data.fd == serverSocket) 
            {
                // Handle new client connections
                struct sockaddr_in clientAddress;
                socklen_t clientAddrLen = sizeof(clientAddress);
                int clientSocket = accept(this->serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);

                if (clientSocket == -1)
                    perror("accept");
                else 
                {
                    event.events = EPOLLIN;
                    event.data.fd = clientSocket;
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientSocket, &event) == -1)
                    {
                        perror("epoll_ctl");
                        return;
                    }
                    // Store the new client socket in the list
                    // this->clientSockets.push_back(clientSocket);
                    // User* new_user = new User("user_1", events[i].data.fd);
                    // this->userList.push_back(new_user);
                    std::cout << "SERVER CONNECTED" << std::endl;
                }
            }
            else 
            {
                std::cout << "ALREADY CONNECTED" << std::endl;

                std::string response = "SERVER SEND YOU A MESSAGE";
                char buffer[512];
                int bytes_read = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                buffer[bytes_read] = '\0';
                std::cout << "BUFFER = " << buffer << std::endl;
                //send(events[i].data.fd, response.c_str(), response.length(), 0);
                if (bytes_read > 0) 
                {
                    std::string message(buffer, bytes_read);

                        // Handle messages from clients
                    if (message.find("JOIN") == 0) 
                    {
                        std::cout << "CHANNEL CREATED" << std::endl;
                        return ;
                    }
                    
                    // if (message.find("/cmd") != std::string::npos) {
                    // // Respond to the "/cmd" command
                    //     std::string response = "Command received: " + message;
                    //     send(events[i].data.fd, response.c_str(), response.length(), 0);
                    // }
                    
                    else if (message.find("MSG") == 0) 
                    {
                        // Handle a message
                        std::string msgContent = message.substr(5); // Extract the message content
                        User* sender = new User("the sender", events[i].data.fd);
                        //User* receiver = new User("the receiver", (events[i].data.fd) + 1);
                        // this->userList.push_back(sender);
                            // (events[i].data.fd);
                        if (sender) 
                        {
                            std::string senderName = sender->GetUserName(); 
                            std::string response = "You, (" + senderName + ") sent a message: " + msgContent;
                                    // Send the response back to the sender
                            send(events[i].data.fd, response.c_str(), response.length(), 0);
                                    // Broadcast the message to other users if needed
                                    // Iterate through the user list and send the message to others
                            std::string message = "carreeeeee";
                            send(((events[i].data.fd) + 1), message.c_str(), message.length(), 0);
                        }
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