/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:10:15 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/24 18:26:08 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

// Constructor/Destructor
Server::Server(void) {
	this->_port = 6969;
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket == -1)
		throw SocketCreationException();
	this->_serverAddr.sin_family = AF_INET;
	this->_serverAddr.sin_port = htons(6969);
	this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
}

Server::~Server(void) {
	close(_socket);
	return ;
}

// Public methods
void	Server::launchServer() {
	if (bind(this->_socket, (struct sockaddr*)&this->_serverAddr, sizeof(this->_serverAddr)))
		throw SocketBindingException();
	if (listen(this->_socket, 69))
		throw ListenConnectionException();
	return ;
}

// Execptions
const char	*Server::SocketCreationException::what() const
{
	return ("Couldn't create socket.");
}

const char	*Server::SocketBindingException::what() const
{
	return ("Couldn't bind socket.");
}

const char	*Server::ListenConnectionException::what() const
{
	return ("Couldn't listen for connections.");
}