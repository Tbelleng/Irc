/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:40:25 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/20 17:39:56 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef USER_HPP
# define USER_HPP

# include "server.hpp"

class User
{
	private :
	
	std::string nickname;
	std::string hostname;
	std::string password;
	std::string username;
	int userFd;
	
	public :

	User(std::string& Nickname, std::string& password, std::string&hostname, int user_fd);
	~User(void);
	std::string GetUserName(void) const;
	void ChangeNickname(std::string new_nickname);
	std::string GetPassword(void);
	int GetUserFd();

};

#endif
