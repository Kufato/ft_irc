/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:01:33 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/12 14:51:46 by gbertet          ###   ########.fr       */
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
		int									_botSocket;
		bool								_bot;
		epoll_event							_event;
		std::string							_password;
		sockaddr_in							_serverAddr;
		std::map<int, Client *>				_listClients;
		std::map<std::string, Channel *>	_listChannels;

	public:
	// Constructor / Destructor
		Server(int port, std::string password);
		~Server(void); 
	
	// Public methods
		void						lauchServer(void);
		void						showChannels(void);
		void						createServer(void);
		void						handleNewClient(void);
		void						deleteEmptyChannels(void);
		void						removeClient(Client *client);
		void						handleClient(int clientSocket);
		void						handleRequest(Client &client, std::string request);
		std::vector<std::string>	splitRequest(std::string request);
	
	// Commands
		void	bot(Client &client);
		void	help(Client &client);
		void	mode_show(Client &client, Channel &channel);
		void	nick(Client &client, std::vector<std::string> cmd);
		void	user(Client &client, std::vector<std::string> cmd);
		void	pass(Client &client, std::vector<std::string> cmd);
		void	join(Client &client, std::vector<std::string> cmd);
		void	mode(Client &client, std::vector<std::string> cmd);
		void	kick(Client &client, std::vector<std::string> cmd);
		void	topic(Client &client, std::vector<std::string> cmd);
		void	invite(Client &client, std::vector<std::string> cmd);
		void	privmsg(Client &client, std::vector<std::string> cmd);
		void	bot_msg(Client &client, Client &bot, std::vector<std::string> cmd);
		void	mode_i(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
		void	mode_k(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
		void	mode_l(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
		void	mode_o(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
		void	mode_t(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel);
	
	// Signals
		void	newSignal(int signum);
		void	newSigint(int signum);
		void	registerSignalHandler(void);
		void	handleSignalWrapper(int signum) const;

	// Utils
		Client	*searchNameClient(std::string nickname);
		Channel	*searchNameChannel(std::string name);

	// Getters
		int	getPort(void) { return (this->_port); }
		std::string	getPassword(void) { return (this->_password); }
};