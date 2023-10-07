/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:19:46 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/06 16:05:14 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../server.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char **argv) 
{
    (void) argc;
    (void) argv;
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

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening on socket" << std::endl;
        close(serverSocket);
        return 1;
    }

    int epfd = epoll_create1(0);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = serverSocket;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serverSocket, &event);

    std::cout << "Server listening on port 5500..." << std::endl;

    // Accept incoming connections and handle messages
    while (true) {
        struct epoll_event events[10];
        int num_events = epoll_wait(epfd, events, 10, -1);
        for (int i = 0; i < num_events; i++) {
            if (events[i].data.fd == serverSocket) {
                // Nouvelle connexion
                struct sockaddr_in clientAddress;
                socklen_t clientAddrLen = sizeof(clientAddress);
                int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);

                if (clientSocket == -1) {
                    std::cerr << "Error accepting connection" << std::endl;
                    continue;
                }
                event.events = EPOLLIN;
                event.data.fd = clientSocket;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clientSocket, &event);
            } else {
                // Message d'un client
                char buffer[1024];
                int bytes = recv(events[i].data.fd, buffer, sizeof(buffer) - 1, 0);
                if (bytes <= 0) {
                    // Client déconnecté ou erreur
                    close(events[i].data.fd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                } else {
                    // Echo back
                    buffer[bytes] = '\0';
                    std::cout << buffer << std::endl;
                    const char* response = "hello world\n";
                    const char* response1 = "New user is connected\n";
                    ssize_t bytesSent = send(events[i].data.fd, response, strlen(response), 0);
                    std::cout << i << std::endl;
                    if (i > 1)
                        send(events[i].data.fd, response1, strlen(response1), 0);
                    if (bytesSent == -1) {
                        std::cerr << "Error sending response" << std::endl;
                    }
                }
            }
        }
        char buffer[1024];
       recv(events[0].data.fd, buffer, sizeof(buffer) -1, 0);
        send(events[0].data.fd,"ok\n", 3, 0);
        std::cout << buffer << std::endl;
    }
    close(epfd);
    close(serverSocket);
    return 0;
}
