/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:40:25 by tbelleng          #+#    #+#             */
/*   Updated: 2023/10/17 17:44:28 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef USER_HPP
# define USER_HPP

#include "server.hpp"

class User
{
	private :
	
	std::string nickname;
	std::string hostname;
	std::string password;
	int userFd;
	
	public :

	User(std::string name, int user_fd);
	~User(void);
	std::string GetUserName(void);
	void ChangeNickname(std::string new_nickname);

};

#endif