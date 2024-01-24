/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/24 18:28:50 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

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
		const int			_port;
		const int			_socket;
		const std::string	_password;
		const sockaddr_in	_serverAddr;

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
	// Exceptions
		class	SocketCreationException : public std::exception
		{
			public:
				const char	*what() const throw();
		};

		class	SocketBindingException : public std::exception
		{
			public:
				const char	*what() const throw();
		};

		class	ListenConnectionException : public std::exception
		{
			public:
				const char	*what() const throw();
		};
};