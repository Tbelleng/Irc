/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:40:25 by tbelleng          #+#    #+#             */
/*   Updated: 2023/11/07 16:51:44 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef USER_HPP
# define USER_HPP


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
	User(std::string name);
	~User(void);
	void ChangeNickname(std::string new_nickname);
	std::string GetPassword(void);
	int GetUserFd();
	
	std::string getNickname(void) const
	{
		return (this->nickname);
	}

	std::string GetUserName(void)
	{
		return (this->username);
	}
	
	void sendMsg(std::string msg) const;
	
	
	std::string RPL_WELCOME() { return (":" + this->hostname + " 001 " + this->nickname + " " + ":Welcome to the our Server, " + "\r\n"); };

};

#endif
