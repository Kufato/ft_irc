/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                            	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:34:21 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/11 15:57:43 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::bot(Client &client) {
	if (this->_bot)
		return (dispLogs(ERR_BOTONLINE(client.getNickname()), client.getSocket()));
	this->_botSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_botSocket == -1) {
		std::cerr << "Error: socket creation for the bot" << std::endl;
		return ;
	}
	fcntl(this->_botSocket, F_SETFL, O_NONBLOCK);
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, this->_botSocket, &this->_event))
		throw std::logic_error("Couldn't add the new client");
	Client	*botclient = new Client(this->_botSocket);
	botclient->setNickname("bot");
	botclient->setUsername("bot");
	botclient->setLogged(true);
	botclient->setRegistered(true);
	this->_listClients.insert(std::pair<int, Client *>(botclient->getSocket(), botclient));
	this->_bot = true;
	std::srand(std::time(NULL));
	return ;
}

void	Server::bot_msg(Client &client, Client &bot, std::vector<std::string> cmd) {
	std::string randResponse[9] = {"oui", "non", "peut-etre", "Francois Bayroux", "pourquoi pas", "je trouve que tu depasses les limites", "aller !", "...", "mais t'es completement malade Timmy"};
	if (cmd[cmd.size() - 1] == "quoi")
		dispLogs(USER_MESSAGES(bot.getNickname(), client.getNickname(), "coubeh"), client.getSocket());
	else
		dispLogs(USER_MESSAGES(bot.getNickname(), client.getNickname(), randResponse[std::rand() % 9]), client.getSocket());
}