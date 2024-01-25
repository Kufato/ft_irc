/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:10:15 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/25 13:15:21 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

// Constructor/Destructor
Server::Server(void) {
	this->_port = 6969;
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocket == -1)
		throw std::logic_error("Couldn't create socket.");
	this->_serverAddr.sin_family = AF_INET;
	this->_serverAddr.sin_port = htons(6969);
	this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
}

Server::~Server(void) {
	close(_serverSocket);
	return ;
}

// Public methods
void	Server::launchServer() {
	if (bind(this->_serverSocket, (struct sockaddr*)&this->_serverAddr, sizeof(this->_serverAddr))) {
		close (this->_serverSocket);
		throw std::logic_error("Couldn't bind socket.");
	}
	if (listen(this->_serverSocket, 69)) {
		close (this->_serverSocket);
		throw std::logic_error("Couldn't listen for connections.");
	}
	if (this->_epollFd = epoll_create1(0)) {
		close (this->_serverSocket);
		throw std::logic_error("Couldn't create the epoll instance.");
	}
	this->_event.events = EPOLLIN;
	this->_event.data.fd = this->_serverSocket;
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, this->_serverSocket, &this->_event)) {
		close (this->_epollFd);
		close (this->_serverSocket);
		throw std::logic_error("Couldn't add the server socket to the epoll instance.");
	}
	return ;
}