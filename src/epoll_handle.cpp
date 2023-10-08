/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll_handle.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:27:06 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/08 16:36:13 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

epoll_event    new_epoll(int serverSocket)
{
	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
        perror("Error while creating Epoll");
        return ;
	}
        
    struct epoll_event event;
	event.data.fd = serverSocket;
	event.events = EPOLLIN;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serverSocket, &event) == -1) 
	{
		perror("Error adding socket");
        close(epoll_fd);
        close(serverSocket);
        return ;
	}
	return (event);
}

