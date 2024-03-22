/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:00:09 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/22 10:35:41 by axcallet         ###   ########.fr       */
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
		std::string					_cmdBuffer;
		std::string					_username;
		std::string					_nickname;
		std::vector<std::string>	_listInvitations;

	public:
	// Constructor / Destructor
		Client(int socket);
		~Client(void);

	// Getters
		int							getSocket(void) { return (this->_socket); }
		bool						isLogged(void) { return (this->_logged); }
		bool						isRegistered(void) { return (this->_registered); }
		std::string					getNickname(void) { return (this->_nickname); }
		std::string					getUsername(void) { return (this->_username); }
		std::string					&getBuffer(void) { return (this->_cmdBuffer); }
		std::vector<std::string>	&getListInvitation(void) { return (this->_listInvitations); }

	// Setters
		void	setSocket(int socket){ this->_socket = socket; }
		void	setLogged(bool logged){ this->_logged = logged; }
		void	addBuffer(const std::string &str) { this->_cmdBuffer += str; }
		void	setBuffer(const std::string &str) { _cmdBuffer = str; }
		void	setUsername(std::string username){ this->_username = username; }
		void	setNickname(std::string nickname){ this->_nickname = nickname; }
		void	setRegistered(bool registered){ this->_registered = registered; }
		void	setInvitation(std::string channel) { this->_listInvitations.push_back(channel); }
};