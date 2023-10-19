/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:58:09 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/19 17:27:54 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.hpp"

User::User(std::string first_connection, int user_fd)
{

    std::istringstream iss(first_connection);
    std::string line;

    while (std::getline(iss, line))
    {
        if (line.find("PASS ") == 0)
        {
            std::string password = line.substr(5);
            this->password = password;
        }
        else if (line.find("NICK ") == 0)
        {
            std::string nickname = line.substr(5);
            this->nickname = nickname;
        }
        else if (line.find("USER ") == 0)
        {
            size_t startPos = line.find("USER ") + 5;
            size_t endPos = line.find(" ", startPos);
            std::string username = line.substr(startPos, endPos - startPos);
            startPos = endPos + 1;
            endPos = line.find(" ", startPos);
            std::string hostname = line.substr(startPos, endPos - startPos);
            this->hostname = hostname;
            this->username = username;
		}
    }
	std::cout << "User Constructor" << std::endl; 
	this->userFd = user_fd;
	return ;
}

User::~User(void)
{
	std::cout << "User Constructor" << std::endl;
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


