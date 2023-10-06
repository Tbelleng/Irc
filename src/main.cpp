/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:19:46 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/05 21:38:47 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../server.hpp"

int main(int argc, char **argv) 
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) 
    {
        std::cerr << "Can't create a socket!" << std::endl;
        return -1;
    }
	
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char buffer[] = "testing IRC";
    send(client_socket, buffer, sizeof(buffer), 0);

    close(client_socket);

    return 0;
}
