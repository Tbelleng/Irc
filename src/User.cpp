/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:58:09 by tbelleng          #+#    #+#             */
/*   Updated: 2023/11/03 15:20:17 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.hpp"

User::User(std::string& Nickname, std::string& password, std::string& hostname, int user_fd)
{
	std::cout << "User Constructor Called" << std::endl; 
	this->nickname = Nickname;
	this->password = password;
	this->hostname = hostname;
	this->userFd = user_fd;

	return ;
}

User::~User(void)
{
	std::cout << "User Destructor deleted" << std::endl;
	return ;
}

std::string User::GetPassword(void)
{
	return (this->password);
}

void User::ChangeNickname(std::string new_nickname)
{
	this->nickname = new_nickname;
	return ;
}

int User::GetUserFd()
{
    return (this->userFd);
}

void User::sendMsg(std::string msg) const
{
    fcntl(this->userFd, F_SETFL, O_NONBLOCK);
    if (send(this->userFd, msg.c_str(), msg.length(), 0) < 0)
        std::cout  << "Error while sending" << std::endl;
    else
        std::cout << this->getNickname() << " " << msg;
}

