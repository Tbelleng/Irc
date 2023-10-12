/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:19:46 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/12 10:53:44 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "epoll_handle.cpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <map>

int MAX_UTILISATEURS = 5;

int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;
    
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }
    
	struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5500);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
        return 1;
    }

    int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
        perror("Error while creating Epoll");
        return 0;
	}
        
    struct epoll_event event;
	event.data.fd = serverSocket;
	event.events = EPOLLIN;

	
    if (listen(serverSocket, MAX_UTILISATEURS) == -1) 
    {
        std::cerr << "Error listening on socket" << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server listening on port 5500..." << std::endl;
	
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serverSocket, &event) == -1) 
	{
		perror("Error adding socket");
        close(epoll_fd);
        close(serverSocket);
        return 0;
	}
 
    while (true) 
    {
        struct epoll_event events[1];
        int new_event = epoll_wait(epoll_fd, events, MAX_UTILISATEURS, -1);
        if (new_event == -1) {
            perror("epoll_wait");
            return 0;
        }
        int i = 0;
        while (i < new_event)
        {
            if (events[i].data.fd == serverSocket)
            {
                struct sockaddr_in clientAddress;
                socklen_t clientAddrLen = sizeof(clientAddress);
                int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);
            
                if (clientSocket == -1)
                    perror("accept");
                else
                {
                    event.events = EPOLLIN;
                    event.data.fd = clientSocket;
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientSocket, &event) == -1)
                    {
                        perror("epoll_ctl");
                        return 0;
                    }
                }
            }
            else 
            {
                char buffer[512];
                int bytes_read = read(events[i].data.fd, buffer, sizeof(buffer));
                write(events[i].data.fd, buffer, bytes_read);
            }
            i++;
        }
        // if (clientSocket == -1) 
        // {
        //     std::cerr << "Error accepting connection" << std::endl;
        //     continue;
        // }
        
        // char buffer[256];
        // ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        // if (bytesRead == -1) 
        // {
        //     std::cerr << "Error receiving data" << std::endl;
        //     close(clientSocket);
        //     continue;
        // }

        // buffer[bytesRead] = '\0';

        // std::cout << "On recoit le message : " << buffer << std::endl;
        // std::cout << "Received message: " << buffer << std::endl;
    
        // if (strncmp(buffer, "CAP LS", 6) == 0) 
        // {
        // const char* capListResponse = "/USER\n";
        // ssize_t capListBytesSent = send(clientSocket, capListResponse, strlen(capListResponse), 0);
        
        // (void)capListBytesSent;
        // }
        // const char* response = "Message received\n";
        // ssize_t bytesSent = send(clientSocket, response, strlen(response), 0);
        // if (bytesSent == -1) 
        // {
        //     std::cerr << "Error sending response" << std::endl;
        // }
        //if (false)
        //    close(clientSocket);
        // std::cout << "SERVER EPOLL :" << events[0].data.fd << std::endl;
        // std::cout << "SERVER EPOLL :" << events[1].data.fd << std::endl;
    }
    close(serverSocket);
    return 0;
}