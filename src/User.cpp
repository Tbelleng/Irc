/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:58:09 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/20 17:41:57 by tbelleng         ###   ########.fr       */
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


std::string User::GetUserName(void) const
{
	return (this->nickname);
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


