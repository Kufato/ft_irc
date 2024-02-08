/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:01:33 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/08 14:06:39 by axcallet         ###   ########.fr       */
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
		void						lauchServer(void);
		void						createServer(void);
		void						handleNewClient(void);
		void						removeClient(Client &client);
		void						handleClient(int clientSocket);
		void						handleRequest(Client &client, std::string request);
		std::vector<std::string>	splitRequest(std::string request);
	
	// Commands
		void		help(Client &client);
		void		nick(Client &client, std::vector<std::string> cmd);
		void		user(Client &client, std::vector<std::string> cmd);
		void		pass(Client &client, std::vector<std::string> cmd);
		void		join(Client &client, std::vector<std::string> cmd);
		void		mode(Client &client, std::vector<std::string> cmd);
		void		kick(Client &client, std::vector<std::string> cmd);
		void		topic(Client &client, std::vector<std::string> cmd);
		void		invite(Client &client, std::vector<std::string> cmd);
		void		privmsg(Client &client, std::vector<std::string> cmd);
		void		mode_i(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
		void		mode_t(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
		void		mode_k(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
		void		mode_o(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
		void		mode_l(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
		
	// Utils
		Channel	*searchNameChannel(std::string name);
		Client	*searchNameClient(std::string nickname);
		bool	clientExist(std::string nickname);
		void	dispLogs(std::string str, int clientFD, void *param);
		
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