/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:01:33 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/01 14:01:15 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

class	Client;
class	Channel;

class	Server {

	private:
		int									_port;
		int									_epollFd;
		int									_serverSocket;
		epoll_event							_event;
		std::string							_password;
		sockaddr_in							_serverAddr;
		std::map<int, Client *>				_listClients;
		std::map<std::string, Channel *>	_listChannels;

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
/*                                                                            */
		std::vector<std::string>	splitRequest(std::string request);
		void	handleRequest(Client &client, std::string request);
	
	// Commands
		std::string	help(void);
		void		nick(Client &client, std::vector<std::string> cmd);
		void		user(Client &client, std::vector<std::string> cmd);
		void		pass(Client &client, std::vector<std::string> cmd);
		void		join(Client &client, std::vector<std::string> cmd);
		void		mode(Client &client, std::vector<std::string> cmd);
		void		privmsg(Client &client, std::vector<std::string> cmd);
		
	// Utils
		Channel	searchNameChannel(std::string name);
		bool	searchNameClient(std::string nickname);
		void	dispLogs(std::string str, int clientFD);
		
	// Channels
//		bool	createChannel(Client &client, std::string channelName)

	// Getters
		int	getPort(void) {
			return (this->_port);
		}

		std::string	getPassword(void) {
			return (this->_password);
		}
};