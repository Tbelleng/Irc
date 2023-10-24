/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:19:46 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/23 22:11:08 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"

void runningServer(Server& irc)
{
    while (true)
    {
		int open_fds = poll(&irc._pollfds[0], irc._pollfds.size(), -1);
		if (open_fds == -1)
		{
			perror("poll");
			return;
		}
		for (size_t i = 0; i < irc._pollfds.size(); i++)
		{
			// std::cout << "number of open fds" << server.getClients().size() + 1 << std::endl;
			// We're checking for the POLLIN event in all the pollfds (POLLIN='new data ready-to-read')
			if (irc._pollfds[i].revents & POLLIN)
			{
		
				if (irc._pollfds[i].fd == irc.getSocket())
					irc.acceptNewClient();
				// If there is ready-to-read data in another socket, a connected client sent data
				else
					irc.handleClientRequest(irc._pollfds[i].fd);
			}
		}
	}


}


int main(int argc, char **argv) 
{
    if (argc != 3)
    {
        std::cout << " You have to input params as follow : /ircserv [port] [password] " << std::endl;
        return 1;
    }
    int port = atoi(argv[1]);
    if (port <= 0 || port > 60000)
    {
        std::cout << "Invalid Port" << std::endl;
        return 1;
    }
    std::string password = std::string(argv[2]);
    Server *irc = new Server(port, password);

    irc->createSocket();

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.s_addr = INADDR_ANY; 

	irc->binding(hint);
	irc->listening();
    
	std::cout << "server connection " << std::endl;
    irc->addingPoll();
    
    runningServer(*irc);
    
    return 0;
}
