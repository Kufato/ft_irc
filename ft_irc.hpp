/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/30 11:25:08 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

 #include <stdio.h>

class	Client {

	private:
		int			_clientSocket;
		bool		_logged;
		bool		_registered;
		std::string	_username;
		std::string	_nickname;

	public:
	// Constructor
		Client(int socket);
	// Destructor
		~Client(void);
	// Public methods

	// Getters
		std::string	getUsername(void) {
			return (this->_username);
		}

		std::string getNickname(void) {
			return (this->_nickname);
		}

		int			getSocket(void) {
			return (this->_clientSocket);
		}

		bool		isLogged(void) {
			return (this->_logged);
		}

		bool		isRegistered(void) {
			return (this->_registered);
		}

	// Setters
		void	setUsername(std::string username){
			this->_username = username;
		}
		
		void	setNickname(std::string nickname){
			this->_nickname = nickname;
		}

		void	setSocket(int socket){
			this->_clientSocket = socket;
		}

		void	setLogged(bool logged){
			this->_logged = logged;
		}

		void	setRegistered(bool registered){
			this->_registered = registered;
		}
};

class	Server {

	private:
		int						_port;
		int						_epollFd;
		int						_serverSocket;
		epoll_event				_event;
		std::string				_password;
		sockaddr_in				_serverAddr;
		std::map<int, Client *>	_listClients;

	public:
	// Constructor
		Server(void);
	// Destructor
		~Server(void);
	// Public methods
		void	createServer(void);
		void	lauchServer(void);
		void	handleNewClient(void);
		void	handleClient(int clientSocket);
		std::string	handleRequest(Client &client, std::string request);
		std::vector<std::string>	splitRequest(std::string request);
		std::string	logClient(Client &client, std::vector<std::string> cmd);
		
	// Getters
		int	getPort(void) {
			return (this->_port);
		}

		std::string	getPassword(void) {
			return (this->_password);
		}
};