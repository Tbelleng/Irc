/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:19:46 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/22 01:12:34 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"

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
    irc->ServerStart();

    return 0;
}
