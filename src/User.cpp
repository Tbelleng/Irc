/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:58:09 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/12 20:38:44 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../User.hpp"

User::User(std::string name, int user_fd)
{
	this->nickname = name;
	this->userFd = user_fd;
	std::cout << "User Constructor" << std::endl;
	return ;
}

User::~User(void)
{
	std::cout << "User Constructor" << std::endl;
	return ;
}

std::string User::GetUserName(void)
{
	return (this->nickname);
}