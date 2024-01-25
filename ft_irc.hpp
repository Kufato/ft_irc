/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/25 13:15:03 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

class	Client {

	private:
		const std::string	_username;
		const std::string	_nickname;

	public:
	// Constructor
		Client(std::string username, std::string nickname);
	// Destructor
		~Client(void);
	// Public methods

};

class	Server {

	private:
		int			_port;
		int			_serverSocket;
		int			_epollFd;
		epoll_event	_event;
		std::string	_password;
		sockaddr_in	_serverAddr;

	public:
	// Constructor
		Server(void);
	// Destructor
		~Server(void);
	// Public methods
		void	launchServer();
	// Getters
		const int	getPort(void) {
			return (this->_port);
		}

		const std::string	getPassword(void) {
			return (this->_password);
		}
};