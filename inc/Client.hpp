/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:00:09 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/21 14:25:02 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

class	Server;
class	Channel;

class	Client {

	private:
		int							_socket;
		bool						_logged;
		bool						_registered;
		std::string					_username;
		std::string					_nickname;
		std::vector<std::string>	_listInvitations;

	public:
	// Constructor
		Client(int socket);
	// Destructor
		~Client(void);
	// Public methods

	// Getters
		std::string	getUsername(void) { return (this->_username); }

		std::string	getNickname(void) { return (this->_nickname); }

		int			getSocket(void) { return (this->_socket); }

		bool		isLogged(void) { return (this->_logged); }

		bool		isRegistered(void) { return (this->_registered); }

		std::vector<std::string>	&getListInvitation(void) { return (this->_listInvitations); }

	// Setters
		void	setUsername(std::string username){ this->_username = username; }

		void	setNickname(std::string nickname){ this->_nickname = nickname; }

		void	setSocket(int socket){ this->_socket = socket; }

		void	setLogged(bool logged){ this->_logged = logged; }

		void	setRegistered(bool registered){ this->_registered = registered; }

		void	setInvitation(std::string channel) { this->_listInvitations.push_back(channel); }
};