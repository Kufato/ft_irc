/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/30 17:27:37 by axcallet         ###   ########.fr       */
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
		int			_socket;
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
			return (this->_socket);
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
			this->_socket = socket;
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
		Server(int port, std::string password);
	// Destructor
		~Server(void); 
	// Public methods
		void	createServer(void);
		void	lauchServer(void);
		void	handleNewClient(void);
		void	handleClient(int clientSocket);
		std::vector<std::string>	splitRequest(std::string request);
		std::string	handleRequest(Client &client, std::string request);
	
	// Commands
		std::string help(void);
		void nick(Client &client, std::vector<std::string> cmd);
		void user(Client &client, std::vector<std::string> cmd);
		void pass(Client &client, std::vector<std::string> cmd);
		
	// Utils
		void	dispLogs(std::string str, int clientFD);
		bool	searchNickname(std::string nickname);

	// Getters
		int	getPort(void) {
			return (this->_port);
		}

		std::string	getPassword(void) {
			return (this->_password);
		}
};